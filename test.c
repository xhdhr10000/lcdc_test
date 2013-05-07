#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <malloc.h>
#include <string.h>
#include <linux/ioctl.h>
#include "test.h"

#define ACTION_UI		0x101
#define ACTION_VIDEO		0x102
#define ACTION_UV		0x103
#define ACTION_CAPTURE		0x104
#define ACTION_CLEAR		0x105
#define ACTION_LOAD		0x106
#define ACTION_PARAM		0x107
#define ACTION_WRITEBACK	0x108
#define ACTION_RESET		0x109
#define ACTION_PRI_REGS 	0x10a
#define ACTION_OFFSET		0x10b
#define ACTION_UPDATE		0x10c
#define ACTION_WRITEBACKC	0x110
#define ACTION_PS		0x111

#define BI_RGB		0
#define BI_BITFIELDS	3

#define SET_RESOLUTION_RATIO _IOW('F', 0x24, struct fb_videomode)
#define FB_UI_PARAM _IOW('F', 0x25, struct gc_spec)
#define FB_VID_PARAM _IOW('F', 0x26, struct gc_spec)
#define FB_CAP_PARAM _IOW('F', 0x27, struct gc_spec)
#define FB_RESET_PARAM _IOW('F', 0x28, struct gc_spec)
#define FB_PRI_REGS _IOW('F', 0x29, struct gc_spec)
#define FB_SET_ALPHA _IOW('F', 0x2a, unsigned int)
#define FB_SET_PCLK _IOW('F', 0x2b, unsigned int)
#define FB_GET_INTSTAT _IOR('F', 0x2c, unsigned int*)
#define FB_SET_BPP _IOW('F', 0x2e, unsigned int)
#define FB_UV_PS _IOW('F', 0x2f, unsigned int) //cgl
#define FB_SET_BURST_LEN _IOW('F', 0x30, unsigned int) //cgl
#define FB_UPDATE_TEST _IOW('F', 0x31, unsigned int)
#define FB_UI_MEM_SIZE 0x2000000
#define FB_VID_MEM_SIZE 0x1000000
#define FB_CAP_MEM_SIZE 0x1000000
#define FB_UPDATE_MEM_OFFSET 0x400000

#define DEBUG

/*** typedef ***/
struct bmp_header {
	unsigned short	magic_number;
	unsigned int	file_size;
	unsigned short	reserved[2];
	unsigned int	offset;
}__attribute__((packed));

struct dib_header {
	unsigned int	header_size;
	int		bitmap_width;
	int		bitmap_height;
	unsigned short	num_color_planes;
	unsigned short	bits_per_pixel;
	unsigned int	compression;
	unsigned int	image_size;
	int		horizontal_resolution;	//pixel per meter
	int		vertical_resolution;	//pixel per meter
	unsigned int	num_colors_in_palette;
	unsigned int	num_important_colors;
};


/*** global viriables ***/
int fd = -1;
struct fb_var_screeninfo vi;
struct fb_fix_screeninfo fi;
void *ui_buffer, *vi_buffer, *wb_buffer[3];
int wb_cur = 0;

FILE *fpbmp;
struct bmp_header bmp_header;
struct dib_header dib_header;

char logfile[256];
FILE *fplog;

int open_log_flag = 0;

/*** functions ***/

int help()
{
	printf("Help of lcdc_test\n");
	printf("\nParameters:\n");
	printf("UI | VIDEO | UV | CAP | CLEAR | LOAD | PARAM | WB | WBC | RESET | PRI | OFFSET\n");
	printf("\nUI|VIDEO|UV [case]:\n");
	printf("    UI|VIDEO|UV [case]: [case] is the index of cases\n");
	printf("                        Without [case]: Run all cases in a row\n");
	printf("\nCAP:\n");
	printf("    Capture from ui buffer\n");
	printf("\nCLEAR [UI|VIDEO]:\n");
	printf("    Clear ui/video buffer to black\n");
	printf("\nLOAD [UI|VIDEO] [FILE]:\n");
	printf("    Load FILE into UI/VIDEO buffer\n");
	printf("\nPARAM [UI|VIDEO]:\n");
	printf("    Set UI/VIDEO param in param.txt\n");
	printf("\nWB:\n");
	printf("    Writeback single frame\n");
	printf("\nWBC [TIMES] [DELAY]:\n");
	printf("    Writeback TIMES frames with DELAY seconds after each action\n");
	printf("\nRESET:\n");
	printf("    Reset lcdc\n");
	printf("\nPRI:\n");
	printf("    Print registers\n");
	printf("\nOFFSET [UI|VIDEO|UV] [case] [times]:\n");
	printf("    Run offset case, offset [times]\n");
	return 0;
}

/**
 * Funcion open_framebuffer(char *fb)
 *	Open framebuffer for later usage
 * Parameter:
 *	fb: Full path of framebuffer
 * Return value:
 *	 0: Success
 *	-1: Open failed
 */
int open_framebuffer(char *fb)
{
	fd = open(fb, O_RDWR);
	if (fd < 0) {
		printf("[E:xiehang] Cannot open fb0, %d\n", fd);
		return -1;
	}
	return 0;
}

/**
 * Function get_screen_info()
 *
 * Return value:
 *	 0: Success
 *	-1: Framebuffer not open
 *	-2: Get VSCREENINFO failed
 *	-3: Get FSCREENINFO failed
 */
int get_screen_info()
{
	if (fd < 0) return -1;

	if (ioctl(fd, FBIOGET_VSCREENINFO, &vi) < 0) {
		printf("[E:xiehang] Get vScreenInfo failed\n");
		return -2;
	}

	if (ioctl(fd, FBIOGET_FSCREENINFO, &fi) < 0) {
		printf("[E:xiehang] Get fScreenInfo failed\n");
		return -3;
	}

	return 0;
}

int set_screen_info()
{
	if (vi.bits_per_pixel == 16) {
		vi.bits_per_pixel = 32;
		vi.red.offset = 24;
		vi.red.length = 8;
		vi.green.offset = 16;
		vi.green.length = 8;
		vi.blue.offset = 8;
		vi.blue.length = 8;
		vi.transp.offset = 0;
		vi.transp.length = 8;
	} else {
		vi.bits_per_pixel = 16;
		vi.red.offset = 11;
		vi.red.length = 5;
		vi.green.offset = 5;
		vi.green.length = 6;
		vi.blue.offset = 0;
		vi.blue.length = 5;
		vi.transp.offset = 0;
		vi.transp.length = 0;
	}
	if (ioctl(fd, FBIOPUT_VSCREENINFO, &vi) < 0) {
		printf("[E:xiehang] Put vScreenInfo failed\n");
	}
	return 0;
}

/**
 * Function dump_screen_info()
 */
#ifndef DEBUG
#define dump_screen_info()
#else
int dump_screen_info()
{
	if(open_log_flag == 1) {
		printf("[I:xiehang] vScreenInfo:\n");
		printf("    xres=%d yres=%d\n", vi.xres, vi.yres);
		printf("    xres_virtual=%d yres_virtual=%d\n", vi.xres_virtual, vi.yres_virtual);
		printf("    xoffset=%d yoffset=%d\n", vi.xoffset, vi.yoffset);
		printf("    bits_per_pixel=%d grayscale=%d\n", vi.bits_per_pixel, vi.grayscale);
		printf("    fb_bitfield info:\n");
		printf("        red:   offset=%d length=%d msb_right=%d\n", vi.red.offset, vi.red.length, vi.red.msb_right);
		printf("        green: offset=%d length=%d msb_right=%d\n", vi.green.offset, vi.green.length, vi.green.msb_right);
		printf("        blue:  offset=%d length=%d msb_right=%d\n", vi.blue.offset, vi.blue.length, vi.blue.msb_right);
		printf("        transp:offset=%d length=%d msb_right=%d\n", vi.transp.offset, vi.transp.length, vi.transp.msb_right);
		printf("    nonstd=%d\n", vi.nonstd);
		printf("    activate=%d\n", vi.activate);
		printf("    height=%d\n", vi.height);
		printf("    width=%d\n", vi.width);
		printf("    accel_flags=%d\n", vi.accel_flags);
		printf("    pixclock=%d\n", vi.pixclock);
		printf("    left_margin=%d\n", vi.left_margin);
		printf("    right_margin=%d\n", vi.right_margin);
		printf("    upper_margin=%d\n", vi.upper_margin);
		printf("    lower_margin=%d\n", vi.lower_margin);
		printf("    hsync_len=%d\n", vi.hsync_len);
		printf("    vsync_len=%d\n", vi.vsync_len);
		printf("    sync=%d\n", vi.sync);
		printf("    vmode=%d\n", vi.vmode);
		printf("    rotate=%d\n", vi.rotate);

		printf("[I:xiehang] fScreenInfo:\n");
		printf("    id=%s\n", fi.id);
		printf("    smem_start=0x%x\n", fi.smem_start);
		printf("    smem_len=0x%x\n", fi.smem_len);
		printf("    type=%d\n", fi.type);
		printf("    type_aux=%d\n", fi.type_aux);
		printf("    visual=%d\n", fi.visual);
		printf("    xpanstep=%d\n", fi.xpanstep);
		printf("    ypanstep=%d\n", fi.ypanstep);
		printf("    ywrapstep=%d\n", fi.ywrapstep);
		printf("    line_length=%d\n", fi.line_length);
		printf("    mmio_start=0x%x\n", fi.mmio_start);
		printf("    mmio_len=%d\n", fi.mmio_len);
		printf("    accel=%d\n", fi.accel);
	}
	return 0;
}
#endif

int create_memory_map(int action)
{
#ifdef DEV_ANDROID
	if (fi.smem_len <= 0) return -1;
	ui_buffer = mmap(0, fi.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ui_buffer == MAP_FAILED) {
		printf("[E:xiehang] ui mmap failed\n");
		return -2;
	}
#else
	switch (action) {
	case ACTION_UPDATE:
		ui_buffer = mmap(0, FB_UI_MEM_SIZE + FB_VID_MEM_SIZE + FB_CAP_MEM_SIZE*2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if (ui_buffer == MAP_FAILED) {
			printf("[E:xiehang] ui mmap failed\n");
			return -2;
		}

		vi_buffer = ui_buffer + FB_UI_MEM_SIZE;
		wb_buffer[0] = vi_buffer + FB_VID_MEM_SIZE;
		wb_buffer[1] = wb_buffer[0] + FB_UPDATE_MEM_OFFSET;
		wb_buffer[2] = wb_buffer[1] + FB_UPDATE_MEM_OFFSET;
		break;
	default:
		ui_buffer = mmap(0, FB_UI_MEM_SIZE + FB_VID_MEM_SIZE + FB_CAP_MEM_SIZE*2, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if (ui_buffer == MAP_FAILED) {
			printf("[E:xiehang] ui mmap failed\n");
			return -2;
		}

		vi_buffer = ui_buffer + FB_UI_MEM_SIZE;
		wb_buffer[0] = vi_buffer + FB_VID_MEM_SIZE;
		wb_buffer[1] = wb_buffer[0] + FB_CAP_MEM_SIZE;
		break;
	}
#endif
	return 0;
}

int open_bmp_file(char *path)
{
	size_t bytesRead;

	fpbmp = fopen(path, "rb");
	if (fpbmp == NULL) {
		printf("[E:xiehang] open bmp file failed: %s\n", path);
		return -1;
	}

	bytesRead = fread(&bmp_header, 1, sizeof(bmp_header), fpbmp);
	if (bytesRead != sizeof(bmp_header)) {
		printf("[E:xiehang] Read bmp header failed, returned %d bytes\n", bytesRead);
		goto e_open_bmp_file;
	}

	bytesRead = fread(&dib_header, 1, sizeof(dib_header), fpbmp);
	if (bytesRead != sizeof(dib_header)) {
		printf("[E:xiehang] Read dib header failed, returned %d bytes\n", bytesRead);
		goto e_open_bmp_file;
	}

	return 0;

e_open_bmp_file:
	fclose(fpbmp);
	return -1;
}

#ifndef DEBUG
#define dump_bmp_info()
#else
int dump_bmp_info()
{
	if(open_log_flag == 1) {
		printf("[I:xiehang] bmp header info:\n");
		printf("    size=%d\n", sizeof(bmp_header));
		printf("    magic_number=0x%x\n", bmp_header.magic_number);
		printf("    file_size=%d\n", bmp_header.file_size);
		printf("    reserved=%d %d\n", bmp_header.reserved[0], bmp_header.reserved[1]);
		printf("    offset=0x%x\n", bmp_header.offset);

		printf("[I:xiehang] dib header info:\n");
		printf("    header_size=%d\n", dib_header.header_size);
		printf("    bitmap_width=%d\n", dib_header.bitmap_width);
		printf("    bitmap_height=%d\n", dib_header.bitmap_height);
		printf("    num_color_planes=%d\n", dib_header.num_color_planes);
		printf("    bits_per_pixel=%d\n", dib_header.bits_per_pixel);
		printf("    compression=%d\n", dib_header.compression);
		printf("    image_size=%d\n", dib_header.image_size);
		printf("    horizontal_resolution=%d\n", dib_header.horizontal_resolution);
		printf("    vertical_resolution=%d\n", dib_header.vertical_resolution);
		printf("    num_colors_in_palette=%d\n", dib_header.num_colors_in_palette);
		printf("    num_important_colors=%d\n", dib_header.num_important_colors);
	}

	return 0;
}
#endif

int load_bitmap(char *path, void *buffer)
{
	int i, j;
	int *out;
	int in;
	int r, g, b, black;
	char *tmp;

	if (buffer == NULL) {
		printf("[E:xiehang] framebuffer == NULL\n");
		return -1;
	}
	if (path == NULL) {
		tmp = buffer;
		for (i=0; i<FB_UI_MEM_SIZE; i++) {
			tmp = 0;
			tmp++;
		}
		return 0;
	}
	if (open_bmp_file(path)) {
		printf("[E:xiehang] open bmp failed\n");
		return -1;
	}
	dump_bmp_info();
	if (fseek(fpbmp, bmp_header.offset, SEEK_SET) != 0) {
		printf("[E:xiehang] fseek pfbmp failed\n");
		return -1;
	}

	out = buffer + vi.yoffset*(vi.xres*vi.bits_per_pixel/8);
	if (vi.bits_per_pixel == 32) {
		if (dib_header.bits_per_pixel == 32) {
			for (i=dib_header.bitmap_height-1; i>=0; i--)
			for (j=0; j<dib_header.bitmap_width; j++) {
				fread(&in, 1, sizeof(int), fpbmp);
//				out[i*vi.xres+j] = in;
				out[i*dib_header.bitmap_width+j] = in;
			}
		}
		else if (dib_header.bits_per_pixel == 24) {
			for (i=dib_header.bitmap_height-1; i>=0; i--) {
				for (j=0; j<dib_header.bitmap_width; j++) {
					fread(&in, 1, sizeof(char)*3, fpbmp);
//					out[i*vi.xres+j] = in;
					out[i*dib_header.bitmap_width+j] = in;
				}
				if (dib_header.bitmap_width*3%4 != 0)
					fread(&in, 1, sizeof(char)*(dib_header.bitmap_width*3%4), fpbmp);
			}
		}
		else if (dib_header.bits_per_pixel == 16) {
			if (dib_header.compression == BI_RGB) {
				r = 0x7c00;
				g = 0x03e0;
				b = 0x001f;
				black = 0x8000;
			} else {
				if (fseek(fpbmp, sizeof(bmp_header)+sizeof(dib_header), SEEK_SET) != 0) {
			                printf("[E:xiehang] fseek fpbmp for 16bit failed\n");
			                return -1;
			        }
				fread(&r, 1, sizeof(int), fpbmp); // read mask
				fread(&g, 1, sizeof(int), fpbmp); // green mask
				fread(&b, 1, sizeof(int), fpbmp); // blue mask
				fread(&black, 1, sizeof(int), fpbmp); // black mask
			}
			if (fseek(fpbmp, bmp_header.offset, SEEK_SET) != 0) {
 				printf("[E:xiehang] fseek pfbmp failed\n");
				return -1;
			}
			for (i=dib_header.bitmap_height-1; i>=0; i--) {
	                        for (j=0; j<dib_header.bitmap_width; j++) {
					fread(&in, 1, sizeof(char)*2, fpbmp);
					in &= ~black;
					if (g == 0x03e0) {// rgb555
						out[i*dib_header.bitmap_width+j]  = ((in & r) << 6) << 3;
						out[i*dib_header.bitmap_width+j] |= ((in & g) << 3) << 3;
					} else {
						out[i*dib_header.bitmap_width+j]  = ((in & r) << 5) << 3;
						out[i*dib_header.bitmap_width+j] |= ((in & g) << 3) << 2;
					}
					out[i*dib_header.bitmap_width+j] |= (in & b) << 3;
				}
				if (dib_header.bitmap_width*2%4 != 0)
					fread(&in, 1, sizeof(char)*(dib_header.bitmap_width*2%4), fpbmp);
			}
		}
		else {
			printf("[E:xiehang] bmp.bits_per_pixel=%d, not supported\n", dib_header.bits_per_pixel);
		}
	}
/*
	else if (vi.bits_per_pixel == 24) {
		if (dib_header.bits_per_pixel == 32) {
			for (i=dib_header.bitmap_height-1; i>=0; i--)
			for (j=0; j<dib_header.bitmap_width/4*3; ) {
				fread(&in, 1, sizeof(int), fpbmp);
				out[i*vi.xres*3/4+j]  = (in & 0x00ffffff) << 8;
				fread(&in, 1, sizeof(int), fpbmp);
				out[i*vi.xres*3/4+j] |= (in & 0x00ff0000) >> 16;
				j++;
				out[i*vi.xres*3/4+j]  = (in & 0x0000ffff) << 16;
				fread(&in, 1, sizeof(int), fpbmp);
				out[i*vi.xres*3/4+j] |= (in & 0x00ffff00) >> 8;
				j++;
				out[i*vi.xres*3/4+j]  = (in & 0x000000ff) << 24;
				fread(&in, 1, sizeof(int), fpbmp);
				out[i*vi.xres*3/4+j] |= (in & 0x00ffffff);
				j++;
			}
		}
		else if (dib_header.bits_per_pixel == 24) {
			for (i=dib_header.bitmap_height-1; i>=0; i--) {
				for (j=0; j<dib_header.bitmap_width/4*3; ) {
					fread(&in, 1, sizeof(char)*3, fpbmp);
					out[i*vi.xres*3/4+j]  = in << 8;
					fread(&in, 1, sizeof(char)*3, fpbmp);
					out[i*vi.xres*3/4+j] |= (in & 0x00ff0000) >> 16;
					j++;
					out[i*vi.xres*3/4+j]  = (in & 0x0000ffff) << 16;
					fread(&in, 1, sizeof(char)*3, fpbmp);
					out[i*vi.xres*3/4+j] |= (in & 0x00ffff00) >> 8;
					j++;
					out[i*vi.xres*3/4+j]  = (in & 0x000000ff) << 24;
					fread(&in, 1, sizeof(char)*3, fpbmp);
					out[i*vi.xres*3/4+j] |= (in & 0x00ffffff);
					j++;
				}
				if (dib_header.bitmap_width*3%4 != 0)
					fread(&in, 1, sizeof(char)*(dib_header.bitmap_width*3%4), fpbmp);
			}
		}
		else if (dib_header.bits_per_pixel == 16) {
			if (dib_header.compression == BI_RGB) {
				r = 0x7c00;
				g = 0x03e0;
				b = 0x001f;
				black = 0x8000;
			} else {
				if (fseek(fpbmp, sizeof(bmp_header)+sizeof(dib_header), SEEK_SET) != 0) {
			                printf("[E:xiehang] fseek fpbmp for 16bit failed\n");
			                return -1;
			        }
				fread(&r, 1, sizeof(int), fpbmp); // read mask
				fread(&g, 1, sizeof(int), fpbmp); // green mask
				fread(&b, 1, sizeof(int), fpbmp); // blue mask
				fread(&black, 1, sizeof(int), fpbmp); // black mask
			}
			if (fseek(fpbmp, bmp_header.offset, SEEK_SET) != 0) {
 				printf("[E:xiehang] fseek pfbmp failed\n");
				return -1;
			}
			for (i=dib_header.bitmap_height-1; i>=0; i--) {
				for (j=0; j<dib_header.bitmap_width/4*3; ) {
					fread(&in, 1, sizeof(char)*2, fpbmp);
					in &= ~black;
					if (g == 0x3e0) { // rgb555
						out[i*vi.xres*3/4+j]  = (in & r) << 17;
						out[i*vi.xres*3/4+j] |= (in & g) << 14;
					} else {
						out[i*vi.xres*3/4+j]  = (in & r) << 16;
						out[i*vi.xres*3/4+j] |= (in & g) << 13;
					}
					out[i*vi.xres*3/4+j] |= (in & b) << 11;
					fread(&in, 1, sizeof(char)*2, fpbmp);
					in &= ~black;
					if (g == 0x3e0) {
						out[i*vi.xres*3/4+j] |= (in & r) >> 7;
					} else {
						out[i*vi.xres*3/4+j] |= (in & r) >> 8;
					}
					j++;
					if (g == 0x3e0) {
						out[i*vi.xres*3/4+j]  = (in & g) << 22;
					} else {
						out[i*vi.xres*3/4+j]  = (in & g) << 21;
					}
					out[i*vi.xres*3/4+j] |= (in & b) << 19;
					fread(&in, 1, sizeof(char)*2, fpbmp);
					in &= ~black;
					if (g == 0x3e0) {
						out[i*vi.xres*3/4+j] |= (in & r) << 1;
						out[i*vi.xres*3/4+j] |= (in & g) >> 2;
					} else {
						out[i*vi.xres*3/4+j] |= (in & r);
						out[i*vi.xres*3/4+j] |= (in & g) >> 3;
					}
					j++;
					out[i*vi.xres*3/4+j]  = (in & b) << 27;
					fread(&in, 1, sizeof(char)*2, fpbmp);
					in &= ~black;
					if (g == 0x3e0) {
						out[i*vi.xres*3/4+j] |= (in & r) << 9;
						out[i*vi.xres*3/4+j] |= (in & g) << 6;
					} else {
						out[i*vi.xres*3/4+j] |= (in & r) << 8;
						out[i*vi.xres*3/4+j] |= (in & g) << 5;
					}
					out[i*vi.xres*3/4+j] |= (in & b);
					j++;
				}
				if (dib_header.bitmap_width*2%4 != 0)
                                        fread(&in, 1, sizeof(char)*(dib_header.bitmap_width*2%4), fpbmp);
			}
		} else {
			printf("[E:xiehang] bmp.bits_per_pixel=%d, not supported\n", dib_header.bits_per_pixel);
		}
	}
*/
	else if (vi.bits_per_pixel == 16) {
		if (dib_header.bits_per_pixel == 32) {
			for (i=dib_header.bitmap_height-1; i>=0; i--)
			for (j=0; j<dib_header.bitmap_width/2; j++) {
				fread(&in, 1, sizeof(int), fpbmp);
				out[i*dib_header.bitmap_width/2+j]  = (in & 0x00f80000) << 8;
				out[i*dib_header.bitmap_width/2+j] |= (in & 0x0000fc00) << 11;
				out[i*dib_header.bitmap_width/2+j] |= (in & 0x000000f8) << 13;
				fread(&in, 1, sizeof(int), fpbmp);
				out[i*dib_header.bitmap_width/2+j] |= (in & 0x00f80000) >> 8;
				out[i*dib_header.bitmap_width/2+j] |= (in & 0x0000fc00) >> 5;
				out[i*dib_header.bitmap_width/2+j] |= (in & 0x000000f8) >> 3;
			}
		}
		else if (dib_header.bits_per_pixel == 24) {
			for (i=dib_header.bitmap_height-1; i>=0; i--) {
				for (j=0; j<dib_header.bitmap_width/2; j++) {
					fread(&in, 1, sizeof(char)*3, fpbmp);
					out[i*dib_header.bitmap_width/2+j]  = (in & 0x00f80000) << 8;
					out[i*dib_header.bitmap_width/2+j] |= (in & 0x0000fc00) << 11;
					out[i*dib_header.bitmap_width/2+j] |= (in & 0x000000f8) << 13;
					fread(&in, 1, sizeof(char)*3, fpbmp);
					out[i*dib_header.bitmap_width/2+j] |= (in & 0x00f80000) >> 8;
					out[i*dib_header.bitmap_width/2+j] |= (in & 0x0000fc00) >> 5;
					out[i*dib_header.bitmap_width/2+j] |= (in & 0x000000f8) >> 3;
				}
				if (dib_header.bitmap_width*3%4 != 0)
					fread(&in, 1, sizeof(char)*(dib_header.bitmap_width*3%4), fpbmp);
			}
		}
		else if (dib_header.bits_per_pixel == 16) {
			if (dib_header.compression == BI_RGB) {
                                r = 0x7c00;
                                g = 0x03e0;
                                b = 0x001f;
                                black = 0x8000;
                        } else {
                                if (fseek(fpbmp, sizeof(bmp_header)+sizeof(dib_header), SEEK_SET) != 0) {
                                        printf("[E:xiehang] fseek fpbmp for 16bit failed\n");
                                        return -1;
                                }
                                fread(&r, 1, sizeof(int), fpbmp); // read mask
                                fread(&g, 1, sizeof(int), fpbmp); // green mask
                                fread(&b, 1, sizeof(int), fpbmp); // blue mask
                                fread(&black, 1, sizeof(int), fpbmp); // black mask
                        }
                        if (fseek(fpbmp, bmp_header.offset, SEEK_SET) != 0) {
                                printf("[E:xiehang] fseek pfbmp failed\n");
                                return -1;
                        }
			for (i=dib_header.bitmap_height-1; i>=0; i--) {
				for (j=0; j<dib_header.bitmap_width/2; j++) {
					fread(&in, 1, sizeof(char)*2, fpbmp);
					in &= ~black;
					if (g == 0x3e0) { //rgb555
						out[i*dib_header.bitmap_width/2+j]  = (in & r) << 17;
						out[i*dib_header.bitmap_width/2+j] |= (in & g) << 17;
						out[i*dib_header.bitmap_width/2+j] |= (in & b) << 16;
					} else {
						out[i*dib_header.bitmap_width/2+j]  = (in & 0xffff) << 16;
					}
					fread(&in, 1, sizeof(char)*2, fpbmp);
					in &= ~black;
					if (g == 0x3e0) {
						out[i*dib_header.bitmap_width/2+j] |= (in & r) << 1;
						out[i*dib_header.bitmap_width/2+j] |= (in & g) << 1;
						out[i*dib_header.bitmap_width/2+j] |= (in & b);
					} else {
						out[i*dib_header.bitmap_width/2+j] |= (in & 0xffff);
					}
				}
				if (dib_header.bitmap_width*2%4 != 0)
					fread(&in, 1, sizeof(char)*(dib_header.bitmap_width*2%4), fpbmp);
			}
		} else {
			printf("[E:xiehang] bmp.bits_per_pixel=%d, not supported\n", dib_header.bits_per_pixel);
		}
	}
	else if (vi.bits_per_pixel == 15) {
		if (dib_header.bits_per_pixel == 32) {
			for (i=dib_header.bitmap_height-1; i>=0; i--)
			for (j=0; j<dib_header.bitmap_width/2; j++) {
				fread(&in, 1, sizeof(int), fpbmp);
				out[i*dib_header.bitmap_width/2+j]  = (in & 0x00f80000) << 7;
				out[i*dib_header.bitmap_width/2+j] |= (in & 0x0000f800) << 10;
				out[i*dib_header.bitmap_width/2+j] |= (in & 0x000000f8) << 13;
				fread(&in, 1, sizeof(int), fpbmp);
				out[i*dib_header.bitmap_width/2+j] |= (in & 0x00f80000) >> 9;
				out[i*dib_header.bitmap_width/2+j] |= (in & 0x0000f800) >> 6;
				out[i*dib_header.bitmap_width/2+j] |= (in & 0x000000f8) >> 3;
			}
		}
		else if (dib_header.bits_per_pixel == 24) {
			for (i=dib_header.bitmap_height-1; i>=0; i--) {
				for (j=0; j<dib_header.bitmap_width/2; j++) {
					fread(&in, 1, sizeof(char)*3, fpbmp);
					out[i*dib_header.bitmap_width/2+j]  = (in & 0x00f80000) << 7;
					out[i*dib_header.bitmap_width/2+j] |= (in & 0x0000f800) << 10;
					out[i*dib_header.bitmap_width/2+j] |= (in & 0x000000f8) << 13;
					fread(&in, 1, sizeof(char)*3, fpbmp);
					out[i*dib_header.bitmap_width/2+j] |= (in & 0x00f80000) >> 9;
					out[i*dib_header.bitmap_width/2+j] |= (in & 0x0000f800) >> 6;
					out[i*dib_header.bitmap_width/2+j] |= (in & 0x000000f8) >> 3;
				}
				if (dib_header.bitmap_width*3%4 != 0)
					fread(&in, 1, sizeof(char)*(dib_header.bitmap_width*3%4), fpbmp);
			}
		}
		else if (dib_header.bits_per_pixel == 16) {
			if (dib_header.compression == BI_RGB) {
                                r = 0x7c00;
                                g = 0x03e0;
                                b = 0x001f;
                                black = 0x8000;
                        } else {
                                if (fseek(fpbmp, sizeof(bmp_header)+sizeof(dib_header), SEEK_SET) != 0) {
                                        printf("[E:xiehang] fseek fpbmp for 16bit failed\n");
                                        return -1;
                                }
                                fread(&r, 1, sizeof(int), fpbmp); // read mask
                                fread(&g, 1, sizeof(int), fpbmp); // green mask
                                fread(&b, 1, sizeof(int), fpbmp); // blue mask
                                fread(&black, 1, sizeof(int), fpbmp); // black mask
                        }
                        if (fseek(fpbmp, bmp_header.offset, SEEK_SET) != 0) {
                                printf("[E:xiehang] fseek pfbmp failed\n");
                                return -1;
                        }
			for (i=dib_header.bitmap_height-1; i>=0; i--) {
				for (j=0; j<dib_header.bitmap_width/2; j++) {
					fread(&in, 1, sizeof(char)*2, fpbmp);
					in &= ~black;
					if (g == 0x3e0) { //rgb555
						out[i*dib_header.bitmap_width/2+j]  = (in & 0xffff) << 16;
					} else {
						out[i*dib_header.bitmap_width/2+j]  = (in & r) << 15;
						out[i*dib_header.bitmap_width/2+j] |= ((in & g) & 0x3e0) << 15;
						out[i*dib_header.bitmap_width/2+j] |= (in & b) << 16;
					}
					fread(&in, 1, sizeof(char)*2, fpbmp);
					in &= ~black;
					if (g == 0x3e0) {
						out[i*dib_header.bitmap_width/2+j] |= (in & 0xffff);
					} else {
						out[i*dib_header.bitmap_width/2+j] |= (in & r) >> 1;
						out[i*dib_header.bitmap_width/2+j] |= ((in & g) & 0x3e0) >> 1;
						out[i*dib_header.bitmap_width/2+j] |= (in & b);
					}
				}
				if (dib_header.bitmap_width*2%4 != 0)
					fread(&in, 1, sizeof(char)*(dib_header.bitmap_width*2%4), fpbmp);
			}
		} else {
			printf("[E:xiehang] bmp.bits_per_pixel=%d, not supported\n", dib_header.bits_per_pixel);
		}
	} else {
		printf("[E:xiehang] vScreenInfo.bits_per_pixel = %d\n", vi.bits_per_pixel);
	}

	fclose(fpbmp);
	return 0;
}

int load_yuv(char *path, void *buffer)
{
	FILE *fpyuv;
	char *buf = buffer;
	int i;

	if (path == NULL) {
		for (i=0; i<FB_VID_MEM_SIZE; i++) {
			*buf = 0;
			buf++;
		}
	} else {
		fpyuv = fopen(path, "rb");
		if (fpyuv == NULL) {
			printf("[E:xiehang] open %s failed\n", path);
			return -1;
		}
		while (!feof(fpyuv)) {
			fread(buf, 1, sizeof(char), fpyuv);
			buf++;
		}

		fclose(fpyuv);
	}

	return 0;
}

int save_yuv(char *path, void *buffer)
{
	FILE *fpyuv;
	char *buf = buffer;
	int i;

	fpyuv = fopen(path, "wb");
	if (fpyuv == NULL) {
		printf("[E:xiehang] open %s failed\n", path);
		return -1;
	}
	fwrite(buf, 1, sizeof(char)*FB_VID_MEM_SIZE, fpyuv);

	fclose(fpyuv);
	return 0;
}

int save_output(char *path, void *buffer)
{
	FILE *fpout;
	char *bmpout;
	int *in, *out;
	int i, j;
	int r, g, b;

	dib_header.header_size = sizeof(dib_header);
	dib_header.bitmap_width = vi.xres;
	dib_header.bitmap_height = vi.yres;
	dib_header.num_color_planes = 1;
	dib_header.bits_per_pixel = 32;
	dib_header.compression = BI_RGB;
	dib_header.image_size = vi.xres*vi.yres*32/8;

	bmp_header.magic_number = 0x4d42;
	bmp_header.offset = sizeof(bmp_header)+sizeof(dib_header);
	bmp_header.file_size = dib_header.image_size+bmp_header.offset;
	bmpout = (char*)malloc(bmp_header.file_size*sizeof(char));
	if (bmpout == NULL) return -1;
	memcpy(bmpout, &bmp_header, sizeof(bmp_header));
	memcpy(bmpout+sizeof(bmp_header), &dib_header, sizeof(dib_header));
	in = buffer + vi.yoffset*(vi.xres*vi.bits_per_pixel/8);
	out = (int*)(bmpout + bmp_header.offset);
//	if (vi.bits_per_pixel == 32) {
		for (i=vi.yres-1; i>=0; i--)
		for (j=0; j<vi.xres; j++)
			*out++ = (in[i*vi.xres+j] | 0xff000000);
//	}
/*
	else if (vi.bits_per_pixel == 24) {
		for (i=vi.yres-1; i>=0; i--)
		for (j=0; j<vi.xres*3/4; ) {
			*out  = 0xff000000;
			*out |= in[i*vi.xres*3/4+j] >> 8;
			out++;
			*out  = 0xff000000;
			*out |= (in[i*vi.xres*3/4+j] & 0x000000ff) << 16;
			j++;
			*out |= (in[i*vi.xres*3/4+j] & 0xffff0000) >> 16;
			out++;
			*out  = 0xff000000;
			*out |= (in[i*vi.xres*3/4+j] & 0x0000ffff) << 8;
			j++;
			*out |= (in[i*vi.xres*3/4+j] & 0xff000000) >> 24;
			out++;
			*out  = 0xff000000;
			*out |= (in[i*vi.xres*3/4+j] & 0x00ffffff);
			j++;
		}
	}
	else if (vi.bits_per_pixel == 16) {
		r = 0xf8000000;
		g = 0x07e00000;
		b = 0x001f0000;
		for (i=vi.yres-1; i>=0; i--)
		for (j=0; j<vi.xres/2; j++) {
			*out  = (in[i*vi.xres/2+j] & r) >> 8;
			*out |= (in[i*vi.xres/2+j] & g) >> 11;
			*out |= (in[i*vi.xres/2+j] & b) >> 13;
			out++;
			*out  = ( (in[i*vi.xres/2+j]<<16) & r) >> 8;
			*out |= ( (in[i*vi.xres/2+j]<<16) & g) >> 11;
			*out |= ( (in[i*vi.xres/2+j]<<16) & b) >> 13;
			out++;
		}
	}
	else if (vi.bits_per_pixel == 15) {
		r = 0x7c000000;
		g = 0x03e00000;
		b = 0x001f0000;
		for (i=vi.yres-1; i>=0; i--)
		for (j=0; j<vi.xres/2; j++) {
			*out  = (in[i*vi.xres/2+j] & r) >> 7;
			*out |= (in[i*vi.xres/2+j] & g) >> 10;
			*out |= (in[i*vi.xres/2+j] & b) >> 13;
			out++;
			*out  = ( (in[i*vi.xres/2+j]<<16) & r) >> 7;
			*out |= ( (in[i*vi.xres/2+j]<<16) & g) >> 11;
			*out |= ( (in[i*vi.xres/2+j]<<16) & b) >> 13;
			out++;
		}
	} else {
		printf("[E:xiehang] Unsupported bpp:%d\n", vi.bits_per_pixel);
	}
*/
	fpout = fopen(path, "wb");
	if (fpout == NULL) {
		printf("[E:xiehang] open %s failed\n", path);
		goto e_free_bmpout;
	}
	int bytesWrite = fwrite(bmpout, 1, bmp_header.file_size, fpout);
	if (bytesWrite != bmp_header.file_size) {
		printf("[E:xiehang] fwrite failed, wrote %d bytes\n", bytesWrite);
		goto e_close_fpout;
	}

	fclose(fpout);
	free(bmpout);
	return 0;

e_close_fpout:
	fclose(fpout);
e_free_bmpout:
	free(bmpout);
	return -1;
}

int write_back(int flag)
{
	int param = flag;
	if (ioctl(fd, FB_CAP_PARAM, &param) < 0) {
		printf("[E:xiehang] ioctl FB_CAP_PARAM failed\n");
		return -1;
	}
	return 0;
}

int reset()
{
	if (ioctl(fd, FB_RESET_PARAM, NULL) < 0) {
		printf("[E:xiehang] ioctl FB_RESET_PARAM failed\n");
		return -1;
	}
	return 0;
}

int pri_regs()
{
	if (ioctl(fd, FB_PRI_REGS, NULL) < 0) {
		printf("[E:xiehang] ioctl FB_PRI_REGS failed\n");
		return -1;
	}
	return 0;
}

int set_resolution_ratio(struct fb_videomode *vm)
{
	if (ioctl(fd, SET_RESOLUTION_RATIO, vm) < 0) {
		printf("[E:xiehang] ioctl set_resolution_ratio failed\n");
		return -1;
	}
	return 0;
}

int set_alpha(unsigned int alpha)
{
	unsigned int a = alpha;
	if (ioctl(fd, FB_SET_ALPHA, &a) < 0) {
		printf("[E:xiehang] ioctl FB_SET_ALPHA, failed\n");
		return -1;
	}
	return 0;
}

int set_pclk(unsigned int pclk)
{
	unsigned int p = pclk;
	if (ioctl(fd, FB_SET_PCLK, &p) < 0) {
		printf("[E:xiehang] ioctl FB_SET_PCLK, failed\n");
		return -1;
	}
	return 0;
}

int ui_param(struct gc_spec *spec)
{
	if (ioctl(fd, FB_UI_PARAM, spec) < 0) {
		printf("[E:xiehang] ioctl FB_UI_PARAM failed\n");
		return -1;
	}
	return 0;
}

int get_intstat(unsigned int *stat)
{
	if (ioctl(fd, FB_GET_INTSTAT, stat) < 0) {
		printf("[E:xiehang] ioctl FB_GET_INTSTAT failed\n");
		return -1;
	}
	return 0;
}

int set_bpp(unsigned int format)
{
	switch (format) {
	case RGB8888:
		format = 32;
		break;
	case RGB555:
		format = 15;
		break;
	case RGB565:
		format = 16;
		break;
	}

	if (ioctl(fd, FB_SET_BPP, &format) < 0) {
		printf("[E:xiehang] ioctl FB_SET_BPP failed\n");
		return -1;
	}
	return 0;
}

int uv_ptr_sw(unsigned int seq)
{
	unsigned int n = seq;
	if (ioctl(fd, FB_UV_PS, &seq) < 0) {
		printf("[E:Xiehang]ioctl FB_UV_PS failed\n");
		return -1;
	}

	return 0;

}

int set_burst_len(unsigned int len)
{
	unsigned int i = 0;
	//if(len < 1 || len > 16) {
	//	printf("[E:] burst length err!!\n");
	//	return -1;
	//}
	if(ioctl(fd, FB_SET_BURST_LEN, &len) < 0) {
		printf("[E:] ioctl FB_SET_BURST_LEN failed!\n");
		return -1;
	}
	return 0;
}

int do_update()
{
	if (ioctl(fd, FB_UPDATE_TEST, NULL) < 0) {
		printf("[E:xiehang] ioctl * failed!\n");
		return -1;
	}
	return 0;
}

int ui_process(int index)
{
	char outfile[64];
	unsigned int intstat;

	set_bpp(ui_cases[index].ui.src.format); //cgl
	printf("[cgl_info] ui_case[%d].ui.src.format=%d\n", index, ui_cases[index].ui.src.format);
	set_resolution_ratio(&(ui_cases[index].vm));

	//set_burst_len(ui_cases[index].burst_length);

	if (get_screen_info()) return 2;
	dump_screen_info();

	if ( (ui_cases[index].clr) && (load_bitmap(NULL, ui_buffer)) ) return -1;
	if (load_bitmap(ui_cases[index].srcfile, ui_buffer)) return -1;

	vi_param(&(vi_close_layer.vi));
	ui_param(&(ui_cases[index].ui));
	set_pclk(ui_cases[index].vm.pixclock);
	set_alpha(0xff00);
	sleep(1);
	reset();
	sleep(1);

	sprintf(outfile, "out_ui_case%d.bmp", index);
#ifdef DEV_ANDROID
	if (save_output(outfile, ui_buffer)) return -1;
#else
	if (write_back(0)) return -1;
	if (save_output(outfile, wb_buffer[wb_cur])) return -1;
	//wb_cur = 1-wb_cur;
#endif
	get_intstat(&intstat);
	fplog = fopen(logfile, "a");
	fprintf(fplog, "ui case%d intstat: 0x%x\n", index, intstat);
	fclose(fplog);
	sleep(1);

	return 0;
}

int vi_param(struct gc_spec *spec)
{
	if (ioctl(fd, FB_VID_PARAM, spec) < 0) {
		printf("[E:xiehang] ioctl FB_VID_PARAM failed\n");
		return -1;
	}
	return 0;
}

int vi_process(int index)
{
	char outfile[64];
	unsigned int intstat;

//	if (write_back(0)) return -1;
//	sleep(1);

	set_bpp(vi_cases[index].vi.src.format); //cgl
	printf("[cgl_info] vi_case[%d].vi.src.format=%d\n", index, vi_cases[index].vi.src.format);
	set_resolution_ratio(&(vi_cases[index].vm));

	if (get_screen_info()) return 2;
	dump_screen_info();

	if ( (vi_cases[index].clr) && (load_yuv(NULL, vi_buffer)) ) return -1;
	if (load_yuv(vi_cases[index].srcfile, vi_buffer)) return -1;

	ui_param(&(ui_close_layer.ui));
	vi_param(&(vi_cases[index].vi));
	set_pclk(vi_cases[index].vm.pixclock);
	set_alpha(0xff0000);
	sleep(1);
	reset();
	sleep(1);

	sprintf(outfile, "out_vid_case%d.bmp", index);
#ifdef DEV_ANDROID
	if (save_output(outfile, vi_buffer)) return -1;
#else
	if (write_back(0)) return -1;
	sleep(1);
	if (save_output(outfile, wb_buffer[wb_cur])) return -1;
	//wb_cur = 1-wb_cur;
#endif
	get_intstat(&intstat);
	fplog = fopen(logfile, "a");
	fprintf(fplog, "vi case%d intstat: 0x%x\n", index, intstat);
	fclose(fplog);
	sleep(1);

	return 0;
}

int uv_process(int index)
{
	char outfile[64];
	unsigned int intstat;

//	if (write_back(0)) return -1;
//	sleep(1);

	set_bpp(uv_cases[index].ui.src.format);
	set_resolution_ratio(&(uv_cases[index].vm));
	set_pclk(uv_cases[index].vm.pixclock);

	if (get_screen_info()) return 2;
	dump_screen_info();

	if ( (uv_cases[index].ui_clr) && (load_bitmap(NULL, ui_buffer)) ) return -1;
	if ( (uv_cases[index].vi_clr) && (load_yuv(NULL, vi_buffer)) ) return -1;
	if (load_bitmap(uv_cases[index].ui_srcfile, ui_buffer)) return -1;
	if (load_yuv(uv_cases[index].vi_srcfile, vi_buffer)) return -1;
	sleep(1);

	ui_param(&(uv_cases[index].ui));
	vi_param(&(uv_cases[index].vi));
	set_alpha(0x7f7f00);
	sleep(1);
	reset();
	sleep(1);

	sprintf(outfile, "out_uv_case%d.bmp", index);
	if (write_back(0)) return -1;
	sleep(1);
	if (save_output(outfile, wb_buffer[wb_cur])) return -1;
	//wb_cur = 1-wb_cur;
	get_intstat(&intstat);
	fplog = fopen(logfile, "a");
	fprintf(fplog, "compose case%d intstat: 0x%x\n", index, intstat);
	fclose(fplog);
	sleep(1);

	return 0;
}

/**
 * Function main
 */
int main(int argc, char *argv[])
{
	int ret, i, j, action=-1;
	char outfile[64];
	unsigned int intstat;

	if (argc == 1) {
		help();
		return 0;
	}

	if(!strcmp(argv[argc - 1], "O")) {
		open_log_flag = 1;

	}

	if (!strcmp(argv[1], "UI"))		action = ACTION_UI;
	else if (!strcmp(argv[1], "VIDEO"))	action = ACTION_VIDEO;
	else if (!strcmp(argv[1], "UV"))	action = ACTION_UV;
	else if (!strcmp(argv[1], "CAP"))	action = ACTION_CAPTURE;
	else if (!strcmp(argv[1], "CLEAR"))	action = ACTION_CLEAR;
	else if (!strcmp(argv[1], "LOAD"))	action = ACTION_LOAD;
	else if (!strcmp(argv[1], "PARAM"))	action = ACTION_PARAM;
	else if (!strcmp(argv[1], "WB"))	action = ACTION_WRITEBACK;
	else if (!strcmp(argv[1], "WBC"))	action = ACTION_WRITEBACKC;
	else if (!strcmp(argv[1], "RESET"))	action = ACTION_RESET;
	else if (!strcmp(argv[1], "PRI"))	action = ACTION_PRI_REGS;
	else if (!strcmp(argv[1], "OFFSET"))	action = ACTION_OFFSET;
	else if (!strcmp(argv[1], "PS"))	action = ACTION_PS;
	else if (!strcmp(argv[1], "UPDATE"))	action = ACTION_UPDATE;
	else {
		printf("[E:xiehang] Invalid args\n");
		goto out;
	}

#ifdef DEV_ANDROID
	ret = open_framebuffer("/dev/graphics/fb0");
#else
	ret = open_framebuffer("/dev/fb0");
#endif
	if (ret < 0) return -1;

	i=0;
	sprintf(logfile, "out%d.log", i);
	fplog = fopen(logfile, "r");
	while (fplog != NULL) {
		fclose(fplog);
		i++;
		sprintf(logfile, "out%d.log", i);
		fplog = fopen(logfile, "r");
	}

	if (get_screen_info()) goto out;
	dump_screen_info();

	if (create_memory_map(action)) goto out;

//	if (set_screen_info()) goto out;

	if (action == ACTION_UI) {
		if (argc > 2) {
			// Select one case
			i = atoi(argv[2]);
			if (i >= sizeof(ui_cases)/sizeof(struct ui_case)-1) {
				printf("[E:xiehang] case index out of range\n");
				goto out;
			}
			printf("[I:xiehang] Start of ui case %d\n", i);
			if (ui_process(i)) goto out;
		} else {
			// Run all cases
			for (i=0; ui_cases[i].clr!=-1; i++) {
				printf("[I:xiehang] Start of ui case %d\n", i);
				if (ui_process(i)) goto out;
			}
		}
	}
	else if (action == ACTION_VIDEO) {
		if (argc > 2) {
			i = atoi(argv[2]);
			if (i >= sizeof(vi_cases)/sizeof(struct vi_case)-1) {
				printf("[E:xiehang] case index out of range\n");
				goto out;
			}
			printf("[I:xiehang] Start of vi case %d\n", i);
			if (vi_process(i)) goto out;
		} else {
			for (i=0; vi_cases[i].clr!=-1; i++) {
				printf("[I:xiehang] Start of vi case %d\n", i);
				if (vi_process(i)) goto out;
			}
		}
	}
	else if (action == ACTION_UV) {
		if (argc > 2) {
			i = atoi(argv[2]);
			if (i >= sizeof(uv_cases)/sizeof(struct uv_case)-1) {
				printf("[E:xiehang] case index out of range\n");
				goto out;
			}
			printf("[I:xiehang] Start of uv case %d\n", i);
			if (uv_process(i)) goto out;
		} else {
			for (i=0; uv_cases[i].ui_clr!=-1; i++) {
				printf("[I:xiehang] Start of uv case %d\n", i);
				if (uv_process(i)) goto out;
			}
		}
	}
	else if (action == ACTION_CAPTURE) {
#ifndef DEV_ANDROID
		save_output("out_capture.bmp", ui_buffer);
#else
		if (!write_back(0)) {
			save_output("out_capture.bmp", wb_buffer[wb_cur]);
			//wb_cur = 1-wb_cur;
		}
#endif
		sleep(1);
	}
	else if (action == ACTION_CLEAR) {
		if ( (argc>=3) && (strcmp(argv[2], "VIDEO") == 0) )
			load_yuv(NULL, vi_buffer);
		else
			load_bitmap(NULL, ui_buffer);
	}
	else if (action == ACTION_LOAD) {
		if ( (argc>=3) && (strcmp(argv[2], "VIDEO") == 0) )
			load_yuv(argv[3], vi_buffer);
		else
			load_bitmap(argv[3], ui_buffer);
	}
	else if (action == ACTION_PARAM) {
		FILE *fparam = fopen("param.txt", "rw");
		if (fparam == NULL) {
			printf("[E:xiehang] open param.txt failed\n");
			goto out;
		}
		struct gc_spec param = {0};
		fscanf(fparam, "%d%d%d%d%d%d", &param.src.width, &param.src.height, &param.src.rect.left,
			&param.src.rect.top, &param.src.rect.right, &param.src.rect.bottom);
		fscanf(fparam, "%d%d%d%d%d%d", &param.dst.width, &param.dst.height, &param.dst.rect.left,
			&param.dst.rect.top, &param.dst.rect.right, &param.dst.rect.bottom);
		fclose(fparam);
		param.swtch = 1;
		param.upd = 1;
		if ( (argc>=3) && (strcmp(argv[2], "VIDEO") == 0) )
			vi_param(&param);
		else
			ui_param(&param);
	}
	else if (action == ACTION_WRITEBACK) {
		write_back(0);
		sleep(1);
		save_output("out_wb.bmp", wb_buffer[wb_cur]);
		//wb_cur = 1-wb_cur;
	}
	else if (action == ACTION_WRITEBACKC) {
		int times, delay;
		char outfile[64];

		write_back(1);
		sleep(1);
		if (argc>=3) times=atoi(argv[2]);
		times = (times<=0)?5:times;
		if (argc>=4) delay=atoi(argv[3]);
		delay = (delay<=0)?1:delay;
		for (i=0; i<times; i++) {
			sprintf(outfile, "out_wbc%d.bmp", i);
			save_output(outfile, wb_buffer[wb_cur]);
			//wb_cur = 1-wb_cur;
			sleep(delay);
		}
	}
	else if (action == ACTION_RESET) {
		reset();
		sleep(1);
	}
	else if (action == ACTION_PRI_REGS) {
		sleep(1);
		pri_regs();
	}
	else if (action == ACTION_OFFSET) {
		int uilayer=0, vilayer=0, times, xinc=8, yinc=8;
		if (!strcmp(argv[2], "UI")) uilayer = 1;
		else if (!strcmp(argv[2], "VIDEO")) vilayer = 1;
		else if (!strcmp(argv[2], "UV")) uilayer = vilayer = 1;
		else {
			printf("[E:xiehang] Please select UI|VIDEO|UV after OFFSET\n");
			goto out;
		}
		i = atoi(argv[3]);
		i = (i<0)?0:i;
		times = atoi(argv[4]);
		times = (times<=0)?5:times;
		set_bpp(offset_cases[i].ui.src.format);
		set_resolution_ratio(&(offset_cases[i].vm));
		set_pclk(offset_cases[i].vm.pixclock);
		if ( (uilayer) && (vilayer) ) set_alpha(0x7f7f00);
		else if (uilayer) set_alpha(0x00ff00);
		else if (vilayer) set_alpha(0xff0000);
		if (get_screen_info()) goto out;
		if (uilayer) {
			if ( (offset_cases[i].ui_clr) && (load_bitmap(NULL, ui_buffer)) ) goto out;
			if (load_bitmap(offset_cases[i].ui_srcfile, ui_buffer)) goto out;
		}
		if (vilayer) {
			if ( (offset_cases[i].vi_clr) && (load_yuv(NULL, vi_buffer)) ) goto out;
			if (load_yuv(offset_cases[i].vi_srcfile, vi_buffer)) goto out;
		}
		j = 0;
		do {
			if (uilayer) ui_param(&(offset_cases[i].ui));
			if (vilayer) vi_param(&(offset_cases[i].vi));
			reset();
			sleep(1);
			sprintf(outfile, "out_offset%d.bmp", j);
			if (write_back(0)) continue;
			if (save_output(outfile, wb_buffer[wb_cur])) continue;
			//wb_cur = 1-wb_cur;
			get_intstat(&intstat);
			fplog = fopen(logfile, "a");
			fprintf(fplog, "offset case%d intstatus:0x%x uipos:%d,%d,%d,%d vipos:%d,%d,%d,%d\n",
				j, intstat, offset_cases[i].ui.dst.rect.left, offset_cases[i].ui.dst.rect.top,
				offset_cases[i].ui.dst.rect.right, offset_cases[i].ui.dst.rect.bottom,
				offset_cases[i].vi.dst.rect.left, offset_cases[i].vi.dst.rect.top,
				offset_cases[i].vi.dst.rect.right, offset_cases[i].vi.dst.rect.bottom);
			fclose(fplog);
			sleep(1);
			if ( ( (uilayer) && (((int)offset_cases[i].ui.dst.rect.left + xinc < 0) ||
			     ((int)offset_cases[i].ui.dst.rect.right + xinc >= offset_cases[i].vm.xres)) ) ||
			     ( (vilayer) && (((int)offset_cases[i].vi.dst.rect.left + xinc < 0) ||
			     ((int)offset_cases[i].vi.dst.rect.right + xinc >= offset_cases[i].vm.xres)) ) )
				xinc = -xinc;
			if ( ( (uilayer) && (((int)offset_cases[i].ui.dst.rect.top + yinc < 0) ||
			     ((int)offset_cases[i].ui.dst.rect.bottom + yinc >= offset_cases[i].vm.yres)) ) ||
			     ( (vilayer) && (((int)offset_cases[i].vi.dst.rect.top + yinc < 0) ||
			     ((int)offset_cases[i].vi.dst.rect.bottom + yinc >= offset_cases[i].vm.yres)) ) )
				yinc = -yinc;
			if (uilayer) {
				offset_cases[i].ui.dst.rect.left   += xinc;
				offset_cases[i].ui.dst.rect.top    += yinc;
				offset_cases[i].ui.dst.rect.right  += xinc;
				offset_cases[i].ui.dst.rect.bottom += yinc;
/*
				offset_cases[i].ui.dst.width       -= 8;
				offset_cases[i].ui.dst.height      -= 8;
*/
			}
			if (vilayer) {
				offset_cases[i].vi.dst.rect.left   += xinc;
				offset_cases[i].vi.dst.rect.top    += yinc;
				offset_cases[i].vi.dst.rect.right  += xinc;
				offset_cases[i].vi.dst.rect.bottom += yinc;
/*
				offset_cases[i].vi.dst.width       -= 8;
				offset_cases[i].vi.dst.height      -= 8;
*/
			}
			j++;
		} while ( (j<times) &&
			  (offset_cases[i].ui.dst.rect.right < offset_cases[i].vm.xres) &&
			  (offset_cases[i].ui.dst.rect.bottom < offset_cases[i].vm.yres) &&
			  (offset_cases[i].vi.dst.rect.right < offset_cases[i].vm.xres) &&
			  (offset_cases[i].vi.dst.rect.bottom < offset_cases[i].vm.yres) );
	}else if(action == ACTION_PS) {
		unsigned int i, seq;

		for(seq = 1; seq < 4; seq++) {
			//load_yuv(NULL, vi_buffer);
			//load_bitmap(NULL, ui_buffer);
			uv_ptr_sw(seq);
			ui_process(seq);
			vi_process(seq);
			//uv_process(seq);
			//load_yuv(NULL, vi_buffer);
			//load_bitmap(NULL, ui_buffer);
		}
	}
	else if (action == ACTION_UPDATE) {
		load_bitmap("1280x720_1.bmp", ui_buffer);
		load_bitmap("1280x720_2.bmp", ui_buffer+FB_UPDATE_MEM_OFFSET);
		load_bitmap("1280x720_3.bmp", ui_buffer+FB_UPDATE_MEM_OFFSET*2);
		load_yuv("1280x720_4_Y_UV20.yuv", vi_buffer);
		load_yuv("1280x720_5_Y_UV20.yuv", vi_buffer+FB_UPDATE_MEM_OFFSET);
		load_yuv("1280x720_6_Y_UV20.yuv", vi_buffer+FB_UPDATE_MEM_OFFSET*2);
		set_alpha(0x7f7f00);
		do_update();

		for (i=0; i<3; i++) {
			sprintf(outfile, "out_update%d.bmp", wb_cur);
			save_output(outfile, wb_buffer[wb_cur]);
			wb_cur = (wb_cur+1)%3;
		}

	}

out:
	close(fd);
	return 0;
}
