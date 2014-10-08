#include <fcntl.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <linux/fb.h>
#include <linux/ioctl.h>
#include <sys/mman.h>
#include "nu10_lcdc_test.h"

#define ASSERT(X, PR)	do { if (!(X)) {\
				printf("ASSERT %s:%d %s\n", __func__, __LINE__, PR);\
				return -1;}\
			} while(0);
#define TRACE		if (verbose) printf("%s\n", __func__);

/*** global viriables ***/
int verbose = 0;
char *test_case = NULL;
char *ui_img = NULL;
char *vi_img = NULL;
int mclock = 0, pixclock = 0;
struct nu10_lcdc_config lcdc_config;
int fb;
void *ui_buffer, *vi_buffer, *wb_buffer[2];

/*** functions ***/
int help(void)
{
}

long flength(FILE *fp)
{
	long ret;

	ASSERT(fp, "fp is NULL");
	ASSERT(!fseek(fp, 0, SEEK_END), "fseek failed");
	ret = ftell(fp);
	ASSERT(!fseek(fp, 0, SEEK_SET), "fseek failed");

	return ret;
}

char* get_strsample(enum Sample in)
{
	switch (in) {
		case ARGB8888: return "ARGB8888";
		case ABGR8888: return "ABGR8888";
		case XRGB8888: return "XRGB8888";
		case XBGR8888: return "XBGR8888";
		case ABGR1555: return "ABGR1555";
		case RGBA5551: return "RGBA5551";
		case ARGB4444: return "ARGB4444";
		case RGB565: return "RGB565";
		case BGR565: return "BGR565";
		case YUV420: return "YUV420";
		case YUV420T: return "TILEMODE";
		default: return "ARGB8888";
	}
}

int open_framebuffer(void)
{
	TRACE;

	fb = open("/dev/fb0", O_RDWR);
	ASSERT(fb >= 0, "Open framebuffer failed");

	return 0;
}

int create_memory_map(void)
{
	TRACE;

	ui_buffer = mmap(0, FB_UI_MEM_SIZE + FB_VI_MEM_SIZE + FB_WB_MEM_SIZE*2, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
	ASSERT(ui_buffer != MAP_FAILED, "mmap failed");

	vi_buffer = ui_buffer + FB_UI_MEM_SIZE;
	wb_buffer[0] = vi_buffer + FB_VI_MEM_SIZE;
	wb_buffer[1] = wb_buffer[0] + FB_WB_MEM_SIZE;

	return 0;
}

int get_args(int argc, char *argv[])
{
	int i;

	for (i=1; i<argc; i++) {
		if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "--case")) {
			i++;
			test_case = strdup(argv[i]);
			printf("case: %s\n", test_case);
		}
		else if (!strcmp(argv[i], "-ui") || !strcmp(argv[i], "--ui")) {
			i++;
			ui_img = strdup(argv[i]);
			printf("ui_img: %s\n", ui_img);
		}
		else if (!strcmp(argv[i], "-vi") || !strcmp(argv[i], "--video")) {
			i++;
			vi_img = strdup(argv[i]);
			printf("vi_img: %s\n", vi_img);
		}
		else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")) {
			verbose = 1;
		}
		else if (!strcmp(argv[i], "-pixclk") || !strcmp(argv[i], "--pixclk")) {
			i++;
			sscanf(argv[i], "%x", &pixclock);
		}
		else if (!strcmp(argv[i], "-mclk") || !strcmp(argv[i], "--mclk")) {
			i++;
			sscanf(argv[i], "%x", &mclock);
		}
	}

	return 0;
}

int dump_config(struct nu10_lcdc_config *config)
{
	int i;

	printf("id=%d_%d\n", config->id_major, config->id_minor);
	printf("ui ori size=%dx%d\n", config->ui_ori_h, config->ui_ori_v);
	printf("ui crop size=%dx%d\n", config->ui_crop_h, config->ui_crop_v);
	printf("ui crop offset=%dx%d\n", config->ui_crop_off_h, config->ui_crop_off_v);
	printf("ui scale size=%dx%d\n", config->ui_scale_h, config->ui_scale_v);
	printf("ui sample=%d\n", config->ui_sample);
	printf("ui filter=%d filt0=%d filt1=%d filt2=%d\n", config->ui_filt_en,
		config->ui_filt0, config->ui_filt1, config->ui_filt2);
	printf("ui alpha src=%d\n", config->ui_alpha_src);
	printf("ui z=%d\n", config->ui_z);
	printf("ui gm en=%d\n", config->ui_gm_en);
	if (config->ui_gm_en) {
		for (i=0; i<16; i++)
			printf("a[%d]=%d b[%d]=%d\n", i, config->ui_gm_a[i], i, config->ui_gm_b[i]);
	}
	printf("ui dth en=%d\n", config->ui_dth_en);

	printf("vi ori size=%dx%d\n", config->vi_ori_h, config->vi_ori_v);
	printf("vi crop size=%dx%d\n", config->vi_crop_h, config->vi_crop_v);
	printf("vi crop offset=%d,%d\n", config->vi_crop_off_h, config->vi_crop_off_v);
	printf("vi stride=%d\n", config->vi_stride);
	printf("vi scale size=%dx%d\n", config->vi_scale_h, config->vi_scale_v);
	printf("vi sample=%d\n", config->vi_sample);
	printf("vi rotation=%d\n", config->vi_rotation);
	printf("vi filter=%d filt0=%d filt1=%d filt2=%d\n", config->vi_filt_en,
		config->vi_filt0, config->vi_filt1, config->vi_filt2);
	printf("vi alpha src=%d\n", config->vi_alpha_src);
	printf("vi z=%d\n", config->vi_z);
	printf("vi gm en=%d\n", config->vi_gm_en);
	if (config->vi_gm_en) {
		for (i=0; i<16; i++)
			printf("a[%d]=%d b[%d]=%d\n", i, config->vi_gm_a[i], i, config->vi_gm_b[i]);
	}
	printf("vi dth en=%d\n", config->vi_dth_en);

	printf("common path size=%dx%d\n", config->comp_size_h, config->comp_size_v);
	printf("common path ui off=%d,%d\n", config->comp_ui_off_h, config->comp_ui_off_v);
	printf("common path vi off=%d,%d\n", config->comp_vi_off_h, config->comp_vi_off_v);
	printf("common path gm en=%d\n", config->comp_gm_en);
	if (config->comp_gm_en) {
		for (i=0; i<16; i++)
			printf("a[%d]=%d b[%d]=%d\n", i, config->comp_gm_a[i], i, config->comp_gm_b[i]);
	}
	printf("common path dth en=%d dpi md=%d\n", config->comp_dth_en, config->dpi_md);

	printf("burst len=%d\n", config->burst_len);

	printf("cursor=%dx%d, %d,%d z=%d\n", config->cursor_size_h, config->cursor_size_v,
		config->cursor_off_h, config->cursor_off_v, config->cursor_z);
}

int read_config(void)
{
	FILE *fpcase;

	TRACE;

	ASSERT(test_case, "Test case not specified");

	fpcase = fopen(test_case, "r");
	ASSERT(fpcase, "Cannot open case");

	ASSERT(fread(&lcdc_config, sizeof(lcdc_config), 1, fpcase), "Read config failed");

	if (verbose) dump_config(&lcdc_config);

	fclose(fpcase);

	return 0;
}

int load_image(char *path, char *which)
{
	FILE *fpimg;
	long length;

	TRACE;

	if (path) {
		fpimg = fopen(path, "r");
		ASSERT(fpimg, "open path failed");

		length = flength(fpimg);
		ASSERT(length >= 0, "flength failed");

		if (!strcmp(which, "ui")) {
			ASSERT(fread(ui_buffer, length, 1, fpimg), "fread failed");
		} else if (!strcmp(which, "vi")) {
			ASSERT(fread(vi_buffer, length, 1, fpimg), "fread failed");
		}
		fclose(fpimg);

		return 0;
	}

	if (lcdc_config.ui_ori_h && lcdc_config.ui_ori_v) {
		fpimg = fopen(ui_img, "r");
		ASSERT(fpimg, "open ui image failed");

		length = flength(fpimg);
		ASSERT(length >= 0, "flength failed");

		ASSERT(fread(ui_buffer, length, 1, fpimg), "fread failed");
		fclose(fpimg);
	}

	if (lcdc_config.vi_ori_h && lcdc_config.vi_ori_v) {
		fpimg = fopen(vi_img, "r");
		ASSERT(fpimg, "open vi image failed");

		length = flength(fpimg);
		ASSERT(length >= 0, "flength failed");

		ASSERT(fread(vi_buffer, length, 1, fpimg), "fread failed");
		fclose(fpimg);
	}

	return 0;
}

int set_clk(void)
{
	if (pixclock) {
		printf("pixclock=0x%x\n", pixclock);
		ASSERT(ioctl(fb, FB_LCDC_SET_PIXCLK, &pixclock) >= 0, "ioctl FB_LCDC_SET_PIXCLK failed");
	}
	if (mclock) {
		printf("mclock=0x%x\n", mclock);
		ASSERT(ioctl(fb, FB_LCDC_SET_MCLK, &mclock) >= 0, "ioctl FB_LCDC_SET_MCLK failed");
	}

	return 0;
}

int set_config(void)
{
	TRACE;

	ASSERT(ioctl(fb, FB_LCDC_DISABLE, NULL) >= 0, "ioctl FB_LCDC_DISABLE failed");

	ASSERT(ioctl(fb, FB_LCDC_SET_CONFIG, &lcdc_config) >= 0, "ioctl FB_SET_CONFIG failed");
	ASSERT(!set_clk(), "set_clk failed");

	ASSERT(ioctl(fb, FB_LCDC_ENABLE, NULL) >= 0, "ioctl FB_LCDC_ENABLE failed");
	return 0;
}

int update_config(struct nu10_lcdc_config *config)
{
	TRACE;

	ASSERT(ioctl(fb, FB_LCDC_UPDATE_CONFIG, config) >= 0, "ioctl FB_LCDC_UPDATE_CONFIG failed");

	return 0;
}

int check_status(int *irq)
{
	TRACE;

	*irq = 0x10;
	ASSERT(ioctl(fb, FB_LCDC_GET_REG, irq) >= 0, "ioctl FB_LCDC_GET_REG failed");

	if ((*irq & BIT(0)) || (*irq & BIT(8)) || (*irq & BIT(9)) ||
	    (*irq & BIT(10)) || (*irq & BIT(11)) || (*irq & BIT(12)))
		return -1;
	else
		return 0;
}

int writeback(struct nu10_lcdc_config *config)
{
	FILE *fpimg;
	char name[MAX_PATH];
	int i, length, irq = 0, time = 0;
	struct bmp_header bmp_header;
	struct dib_header dib_header;

	TRACE;

	ASSERT(ioctl(fb, FB_LCDC_WRITEBACK, NULL) >= 0, "ioctl FB_LCDC_WRITEBACK failed");

	while (!(irq & BIT(1))) {
		sleep(1);
		time++;
		irq = 0x10;
		ASSERT(ioctl(fb, FB_LCDC_GET_REG, irq) >= 0, "ioctl FB_LCDC_GET_REG failed");
		if (time >= 5) break;
	}

#ifdef SCENE_CHANGE
	if (config)
		sprintf(name, "output/%d_%d-%d_%d.bmp", lcdc_config.id_major, lcdc_config.id_minor, config->id_major, config->id_minor);
	else
#endif
		sprintf(name, "output/%d_%d.bmp", lcdc_config.id_major, lcdc_config.id_minor);
	fpimg = fopen(name, "w");
	ASSERT(fpimg, "open wb image failed");

	dib_header.header_size = sizeof(dib_header);
	dib_header.bitmap_width = lcdc_config.comp_size_h;
	dib_header.bitmap_height = lcdc_config.comp_size_v;
	dib_header.num_color_planes = 1;
	dib_header.bits_per_pixel = 32;
	dib_header.compression = BI_RGB;
	dib_header.image_size = lcdc_config.comp_size_h*lcdc_config.comp_size_v*32/8;
	dib_header.horizontal_resolution = 0xb13;
	dib_header.vertical_resolution = 0xb13;
	dib_header.num_colors_in_palette = 0;
	dib_header.num_important_colors = 0;

	bmp_header.magic_number = 0x4d42;
	bmp_header.offset = sizeof(bmp_header)+sizeof(dib_header);
	bmp_header.file_size = dib_header.image_size+bmp_header.offset;
	bmp_header.reserved[0] = bmp_header.reserved[1] = 0;

	length = bmp_header.file_size;
	ASSERT(fwrite(&bmp_header, 1, sizeof(bmp_header), fpimg), "fwrite bmp_header failed");
	ASSERT(fwrite(&dib_header, 1, sizeof(dib_header), fpimg), "fwrite dib_header failed");
	ASSERT(fwrite(wb_buffer[0], 1, length, fpimg), "fwrite image failed");

	fclose(fpimg);

	return 0;
}

int writelog(int irq, struct nu10_lcdc_config *config)
{
	FILE *fplog;
	char name[MAX_PATH];
	int i, data;

	TRACE;

#ifdef SCENE_CHANGE
	if (config)
		sprintf(name, "output/%d_%d-%d_%d.txt", lcdc_config.id_major, lcdc_config.id_minor, config->id_major, config->id_minor);
	else
#endif
		sprintf(name, "output/%d_%d.txt", lcdc_config.id_major, lcdc_config.id_minor);
	fplog = fopen(name, "w");
	ASSERT(fplog, "open log file failed");

	fprintf(fplog, "Interrupt = 0x%x\n", irq);
	if (irq & BIT(0)) fprintf(fplog, "capture overflow\n");
	if (irq & BIT(8)) fprintf(fplog, "common path underflow\n");
	if (irq & BIT(9)) fprintf(fplog, "uv underflow\n");
	if (irq & BIT(10)) fprintf(fplog, "y underflow\n");
	if (irq & BIT(11)) fprintf(fplog, "rgb underflow\n");
	if (irq & BIT(12)) fprintf(fplog, "overall underflow\n");

	for (i=0; i<3205; i+=4) {
		if (i%16 == 0) fprintf(fplog, "\n0x%08x: ", i);
		data = i;
		if (ioctl(fb, FB_LCDC_GET_REG, &data) >= 0)
			fprintf(fplog, "0x%08x ", data);
		else
			fprintf(fplog, "0xXXXXXXXX ");
	}

	fclose(fplog);
	return 0;
}

int scene_change(void)
{
	FILE *fpcase;
	char test_case2[MAX_PATH], *tmp, case_name[MAX_PATH], image[MAX_PATH];
	int rand_major, rand_minor;
	struct nu10_lcdc_config lcdc_config2;
	int irq;

	srand(time(0));

	/* lcdc config 1 */
	do {
		rand_major = rand()%13+1;
		rand_minor = rand()%288+1;
		if (verbose) printf("Got random id: %d_%d\n", rand_major, rand_minor);
		sprintf(case_name, "case/%d_%d.bin", rand_major, rand_minor);
		fpcase = fopen(case_name, "r");
	} while (!fpcase);
	test_case = strdup(case_name);

	ASSERT(fread(&lcdc_config, sizeof(lcdc_config), 1, fpcase), "Read config failed");
	if (verbose) dump_config(&lcdc_config);
	fclose(fpcase);

	printf("Got case %d_%d with resolution %dx%d\n",
		lcdc_config.id_major, lcdc_config.id_minor,
		lcdc_config.comp_size_h, lcdc_config.comp_size_v);

	if (lcdc_config.ui_ori_h && lcdc_config.ui_ori_v) {
		sprintf(image, "pic/%s/%dx%d_1_%s.%s",
			(lcdc_config.ui_ori_h>=lcdc_config.ui_ori_v)?"horizontal":"vertical",
			lcdc_config.ui_ori_h, lcdc_config.ui_ori_v,
			get_strsample(lcdc_config.ui_sample),
			(lcdc_config.ui_sample>=YUV420)?"yuv":"rgb");
		ASSERT(!load_image(image, "ui"), "load_image failed");
	}

	if (lcdc_config.vi_ori_h && lcdc_config.vi_ori_v) {
		sprintf(image, "pic/%s/%dx%d_1_%s.%s",
			(lcdc_config.vi_ori_h>=lcdc_config.vi_ori_v)?"horizontal":"vertical",
			lcdc_config.vi_ori_h, lcdc_config.vi_ori_v,
			get_strsample(lcdc_config.vi_sample),
			(lcdc_config.vi_sample>=YUV420)?"yuv":"rgb");
		ASSERT(!load_image(image, "vi"), "load_image failed");
	}

	ASSERT(!set_config(), "set_config failed");
	sleep(2);
	ASSERT(!writeback(NULL), "writeback failed");
	if (check_status(&irq)) {
		printf("Case %d_%d FAILED: 0x%08x\n", lcdc_config.id_major, lcdc_config.id_minor, irq);
		ASSERT(!writelog(irq, NULL), "writelog failed");
	}

	/* lcdc config 2 */
	do {
		do {
			rand_major = rand()%13+1;
			rand_minor = rand()%288+1;
			if (verbose) printf("Got random id: %d_%d\n", rand_major, rand_minor);
			sprintf(case_name, "%d_%d", lcdc_config.id_major, lcdc_config.id_minor);
			tmp = strstr(test_case, case_name);
			memset(test_case2, 0, sizeof(test_case2));
			strncpy(test_case2, test_case, tmp-test_case);
			sprintf(case_name, "%d_%d.bin", rand_major, rand_minor);
			strcat(test_case2, case_name);
			fpcase = fopen(test_case2, "r");
		} while (!fpcase);

		ASSERT(fread(&lcdc_config2, sizeof(lcdc_config2), 1, fpcase), "Read config failed");

		if (verbose) dump_config(&lcdc_config2);

		fclose(fpcase);
	} while (lcdc_config2.comp_size_h != lcdc_config.comp_size_h ||
		 lcdc_config2.comp_size_v != lcdc_config.comp_size_v);

	printf("Got case %d_%d with resolution %dx%d\n",
		lcdc_config2.id_major, lcdc_config2.id_minor,
		lcdc_config2.comp_size_h, lcdc_config2.comp_size_v);

	if (lcdc_config2.ui_ori_h && lcdc_config2.ui_ori_v) {
		sprintf(image, "pic/%s/%dx%d_1_%s.%s",
			(lcdc_config2.ui_ori_h>=lcdc_config2.ui_ori_v)?"horizontal":"vertical",
			lcdc_config2.ui_ori_h, lcdc_config2.ui_ori_v,
			get_strsample(lcdc_config2.ui_sample),
			(lcdc_config2.ui_sample>=YUV420)?"yuv":"rgb");
		ASSERT(!load_image(image, "ui"), "load_image failed");
	}

	if (lcdc_config2.vi_ori_h && lcdc_config2.vi_ori_v) {
		sprintf(image, "pic/%s/%dx%d_1_%s.%s",
			(lcdc_config2.vi_ori_h>=lcdc_config2.vi_ori_v)?"horizontal":"vertical",
			lcdc_config2.vi_ori_h, lcdc_config2.vi_ori_v,
			get_strsample(lcdc_config2.vi_sample),
			(lcdc_config2.vi_sample>=YUV420)?"yuv":"rgb");
		ASSERT(!load_image(image, "vi"), "load_image failed");
	}

	ASSERT(!update_config(&lcdc_config2), "update_config failed");
	sleep(2);

	ASSERT(!writeback(&lcdc_config2), "writeback failed");
	if (check_status(&irq)) {
		printf("Case %d_%d FAILED: 0x%08x\n", lcdc_config2.id_major, lcdc_config2.id_minor, irq);
		ASSERT(!writelog(irq, &lcdc_config2), "writelog failed");
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int irq;

	ASSERT(!get_args(argc, argv), "get_args failed");
	ASSERT(!open_framebuffer(), "open_framebuffer failed");
	ASSERT(!create_memory_map(), "create_memory_map failed");

#ifdef SCENE_CHANGE
	ASSERT(!scene_change(), "scene_change failed");
#else
	ASSERT(!read_config(), "read_config failed");
	ASSERT(!load_image(NULL, NULL), "load_image failed");
	ASSERT(!set_config(), "set_config failed");
	sleep(2);
	ASSERT(!writeback(NULL), "writeback failed");
	if (check_status(&irq)) {
		printf("Case %d_%d FAILED: 0x%08x\n", lcdc_config.id_major, lcdc_config.id_minor, irq);
		ASSERT(!writelog(irq, NULL), "writelog failed");
	}
#endif

	close(fb);

	sleep(5);
}
