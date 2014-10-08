#pragma once

/*** Macros ***/
#define MAX_PATH		512
#define BIT(nr)			(1UL << (nr))

#define FB_UI_MEM_SIZE		0x2000000
#define FB_VI_MEM_SIZE		0x2000000
#define FB_WB_MEM_SIZE		0x2000000

#define FB_LCDC_SET_CONFIG	_IOW('F', 0x21, struct nu10_lcdc_config)
#define FB_LCDC_DISABLE 	_IOW('F', 0x22, int)
#define FB_LCDC_ENABLE		_IOW('F', 0x23, int)
#define FB_LCDC_WRITEBACK	_IOW('F', 0x24, int)
#define FB_LCDC_GET_REG		_IOR('F', 0x25, int)
#define FB_LCDC_SET_MCLK	_IOW('F', 0x26, int)
#define FB_LCDC_SET_PIXCLK	_IOW('F', 0x27, int)
#define FB_LCDC_UPDATE_CONFIG	_IOW('F', 0x28, struct nu10_lcdc_config)

#define BI_RGB			0

/*** typedefs ***/
enum Sample {
	ARGB8888 = 0,
	ABGR8888,
	XRGB8888,
	XBGR8888,
	ABGR1555,
	RGBA5551,
	ARGB4444,
	RGB565,
	BGR565,
	YUV420,
	YUV420T,
};

struct nu10_lcdc_config
{
	int id_major;
	int id_minor;

	/* RGB layer */
	int ui_ori_h, ui_ori_v;
	int ui_crop_h, ui_crop_v;
	int ui_crop_off_h, ui_crop_off_v;
	int ui_scale_h, ui_scale_v;
	enum Sample ui_sample;
	int ui_filt_en;
	int ui_filt0, ui_filt1, ui_filt2;
	int ui_alpha_src;
	int ui_z;
	int ui_gm_en;
	short ui_gm_a[16], ui_gm_b[16];
	int ui_dth_en;

	/* Video layer */
	int vi_ori_h, vi_ori_v;
	int vi_crop_h, vi_crop_v;
	int vi_crop_off_h, vi_crop_off_v;
	int vi_stride;
	int vi_scale_h, vi_scale_v;
	enum Sample vi_sample;
	int vi_rotation;
	int vi_filt_en;
	int vi_filt0, vi_filt1, vi_filt2;
	int vi_alpha_src;
	int vi_z;
	int vi_gm_en;
	short vi_gm_a[16], vi_gm_b[16];
	int vi_dth_en;

	/* Common path */
	int comp_size_h, comp_size_v;
	int comp_ui_off_h, comp_ui_off_v;
	int comp_vi_off_h, comp_vi_off_v;
	int comp_gm_en;
	short comp_gm_a[16], comp_gm_b[16];
	int comp_dth_en, dpi_md;

	int burst_len;

	/* Cursor layer */
	int cursor_size_h, cursor_size_v;
	int cursor_off_h, cursor_off_v;
	int cursor_z;
};

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
