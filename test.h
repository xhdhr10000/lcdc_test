struct fb_videomode {
        const char *name;     /* optional */
        unsigned int refresh; /* optional */
        unsigned int xres;
        unsigned int yres;
        unsigned int pixclock;
        unsigned int left_margin;
        unsigned int right_margin;
        unsigned int upper_margin;
        unsigned int lower_margin;
        unsigned int hsync_len;
        unsigned int vsync_len;
        unsigned int sync;
        unsigned int vmode;
        unsigned int flag;
};

struct rect_t {
        unsigned int left;
        unsigned int top;
        unsigned int right;
        unsigned int bottom;
};

struct gc_params {
        unsigned int physAddr;
        unsigned int width;
        unsigned int height;
        unsigned int format;
        unsigned int stride;
        struct rect_t rect;
};

struct gc_spec {
        struct gc_params src;
        struct gc_params dst;
        unsigned int swtch;
        unsigned int upd;
};

struct ui_case {
	struct fb_videomode vm;
	struct gc_spec ui;
	unsigned int clr;
	char srcfile[64];
};

struct vi_case {
	struct fb_videomode vm;
	struct gc_spec vi;
	unsigned int clr;
	char srcfile[64];
};

struct uv_case {
	struct fb_videomode vm;
	struct gc_spec ui;
	struct gc_spec vi;
	unsigned int ui_clr;
	unsigned int vi_clr;
	unsigned int format; // 0x00:rgb555 0x01:rgb565 0x02:rgb8888
	char ui_srcfile[64];
	char vi_srcfile[64];
};

#if 1
struct ui_case ui_cases[] = {
/** Display part **/
{ //0
	{
		NULL,60, 640, 480, 4, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 640, 480, 0, 0, {0,0,640,480}},
		1, 1
	},
	1, "32_8888_640x480.bmp"
},
{ //1
	{
		NULL, 60, 1024, 768, 10, 56, 24, 33, 8, 160, 8,
		0, FB_VMODE_INTERLACED
	},
	{
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		1, 1,
	},
	1, "32_8888_1024x768.bmp"
},
{ //2
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		1, 1,
	},
	1, "32_8888_1280x720.bmp"
},
{ //3
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		1, 1,
	},
	1, "32_8888_1920x1080.bmp"
},
/** Scaling part **/
/* Source: 1920x1080 rgb888 */
{ //4
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {1920*0.1,1080*0.1,1920*0.9,1080*0.9}},
		1, 1,
	},
	1, "32_8888_1920x1080.bmp"
},
{ //5
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.8, 720*0.8, 0, 0, {1280*0.1,720*0.1,1280*0.9,720*0.9}},
		1, 1,
	},
	1, "24_888_1920x1080.bmp"
},
{ //6
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.05,1080*0.05,1920*0.95,1080*0.95}},
		1, 1,
	},
	1, "24_888_1920x1080.bmp"
},
{ //7
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.05,720*0.05,1280*0.95,720*0.95}},
		1, 1,
	},
	1, "24_888_1920x1080.bmp"
},
{ //8
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,1080*0.05,1920*0.95,1080}},
		1, 1,
	},
	1, "24_888_1920x1080.bmp"
},
{ //9
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,720*0.05,1280*0.95,720}},
		1, 1,
	},
	1, "24_888_1920x1080.bmp"
},
{ //10
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.1,0,1920,1080*0.9}},
		1, 1,
	},
	1, "24_888_1920x1080.bmp"
},
{ //11
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.1,0,1280,720*0.9}},
		1, 1,
	},
	1, "24_888_1920x1080.bmp"
},
{ //12
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.98, 0, 0, {1920*0.05,0,1920,1080*0.98}},
		1, 1,
	},
	1, "24_888_1920x1080.bmp"
},
{ //13
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.95, 720*0.98, 0, 0, {1280*0.05,0,1280,720*0.98}},
		1, 1,
	},
	1, "24_888_1920x1080.bmp"
},
{ //14
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,1080*0.1,1920*0.9,1080}},
		1, 1,
	},
	1, "24_888_1920x1080.bmp"
},
{ //15
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,720*0.1,1280*0.9,720}},
		1, 1,
	},
	1, "24_888_1920x1080.bmp"
},
/* Source: 1280x720 rgb888 */
{ //16
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.8, 720*0.8, 0, 0, {1280*0.1,720*0.1,1280*0.9,720*0.9}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
{ //17
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {1920*0.1,1080*0.1,1920*0.9,1080*0.9}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
{ //18
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.05,720*0.05,1280*0.95,720*0.95}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
{ //19
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.05,1080*0.05,1920*0.95,1080*0.95}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
{ //20
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,720*0.05,1280*0.95,720}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
{ //21
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,1080*0.05,1920*0.95,1080}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
{ //22
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.1,0,1280,720*0.9}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
{ //23
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.1,0,1920,1080*0.9}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
{ //24
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.95, 720*0.95, 0, 0, {1280*0.05,0,1280,720*0.95}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
{ //25
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {1920*0.05,0,1920,1080*0.95}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
{ //26
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,720*0.1,1280*0.9,720}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
{ //27
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,1080*0.1,1920*0.9,1080}},
		1, 1,
	},
	1, "24_888_1280x720.bmp"
},
/* Source: 960x540 rgb888 */
{ //28
	{
		NULL, 60, 960, 540, 8, 142, 98, 15, 7, 48, 1,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 960*0.8, 540*0.8, 0, 0, {960*0.1,540*0.1,960*0.9,540*0.9}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //29
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1280*0.8, 720*0.8, 0, 0, {1280*0.1,720*0.1,1280*0.9,720*0.9}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //30
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {1920*0.1,1080*0.1,1920*0.9,1080*0.9}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //31
	{
		NULL, 60, 960, 540, 8, 142, 98, 15, 7, 48, 1,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 960*0.9, 540*0.9, 0, 0, {960*0.05,540*0.05,960*0.95,540*0.95}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //32
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.05,720*0.05,1280*0.95,720*0.95}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //33
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.05,1080*0.05,1920*0.95,1080*0.95}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //34
	{
		NULL, 60, 960, 540, 8, 142, 98, 15, 7, 48, 1,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 960*0.95, 540*0.95, 0, 0, {0,540*0.05,960*0.95,540}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //35
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,720*0.05,1280*0.95,720}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //36
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,1080*0.05,1920*0.95,1080}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //37
	{
		NULL, 60, 960, 540, 8, 142, 98, 15, 7, 48, 1,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 960*0.9, 540*0.9, 0, 0, {960*0.1,0,960,540*0.9}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //38
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.1,0,1280,720*0.9}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //39
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.1,0,1920,1080*0.9}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //40
	{
		NULL, 60, 960, 540, 8, 142, 98, 15, 7, 48, 1,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 960*0.95, 540*0.95, 0, 0, {960*0.05,0,960,540*0.95}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //41
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1280*0.95, 720*0.95, 0, 0, {1280*0.05,0,1280,720*0.95}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //42
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {1920*0.05,0,1920,1080*0.95}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //43
	{
		NULL, 60, 960, 540, 8, 142, 98, 15, 7, 48, 1,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 960*0.9, 540*0.9, 0, 0, {0,540*0.1,960*0.9,540}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //44
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,720*0.1,1280*0.9,720}},
		1, 1,
	},
	1, "960x540.bmp"
},
{ //45
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,1080*0.1,1920*0.9,1080}},
		1, 1,
	},
	1, "960x540.bmp"
},
/* Source: 800x600 rgb888 */
{ //46
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.8, 600*0.8, 0, 0, {800*0.1,600*0.1,800*0.9,600*0.9}},
		1, 1,
	},
	1, "800x600_1.bmp"
},
{ //47
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.9, 600*0.9, 0, 0, {800*0.05,600*0.05,800*0.95,600*0.95}},
		1, 1,
	},
	1, "800x600_1.bmp"
},
{ //48
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.95, 600*0.95, 0, 0, {0,600*0.05,800*0.95,600}},
		1, 1,
	},
	1, "800x600_1.bmp"
},
{ //49
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.9, 600*0.9, 0, 0, {800*0.1,0,800,600*0.9}},
		1, 1,
	},
	1, "800x600_1.bmp"
},
{ //50
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.95, 600*0.95, 0, 0, {800*0.05,0,800,600*0.95}},
		1, 1,
	},
	1, "800x600_1.bmp"
},
{ //51
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.9, 600*0.9, 0, 0, {0,600*0.1,800*0.9,600}},
		1, 1,
	},
	1, "800x600_1.bmp"
},

/** End of ui_cases **/
{
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		-1, -1,
	},
	-1, ""
}
};


struct vi_case vi_cases[] = {
{ //0
	{
		NULL,60, 320, 240, 3, 59, 32, 11, 11, 9, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 320, 240, 0, 0, {0,0,320,240}},
		1, 1
	},
	1, "320.yuv_semi"
},
{ //1
	{
		NULL,60, 640, 480, 4, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 640, 480, 0, 0, {0,0,640,480}},
		1, 1
	},
	1, "640.yuv_semi"
},
{ //2
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800, 600, 0, 0, {0,0,800,600}},
		1, 1
	},
	1, "800.yuv_semi"
},
{ //3
	{
		NULL, 60, 1024, 768, 10, 56, 24, 33, 8, 160, 8,
		0, FB_VMODE_INTERLACED
	},
	{
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		1, 1
	},
	1, "1024.yuv_semi"
},
{ //4
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		1, 1
	},
	1, "1280.yuv_semi"
},
{ //5
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		1, 1
	},
	1, "1920.yuv_semi"
},
/** Video Crop & Scaling **/
/* Source: 1920x1080 YUV420 Semi-planar */
{ //6
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,176,144}},
		{0, 176, 144, 0, 0, {0,0,176,144}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //7
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,320,240}},
		{0, 320, 240, 0, 0, {0,0,320,240}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //8
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,400,300}},
		{0, 400, 300, 0, 0, {0,0,400,300}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //9
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,640,300}},
		{0, 640, 300, 0, 0, {0,0,640,300}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //10
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,400,480}},
		{0, 400, 480, 0, 0, {0,0,400,480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //11
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,480,320,240+480}},
		{0, 240, 320, 0, 0, {0,480,240,320+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //12
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,480,320,240+480}},
		{0, 960, 720, 0, 0, {0,480,960,720+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //13
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,480,400,300+480}},
		{0, 300, 400, 0, 0, {0,480,300,400+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //14
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,480,400,300+480}},
		{0, 800, 160, 0, 0, {0,480,800,160+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //15
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,480,640,300+480}},
		{0, 300, 640, 0, 0, {0,480,300,640+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //16
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,480,640,300+480}},
		{0, 960, 540, 0, 0, {0,480,960,540+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //17
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,480,400,480+480}},
		{0, 400, 480, 0, 0, {0,480,400,480+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //18
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,480,400,480+480}},
		{0, 200, 240, 0, 0, {0,480,200,240+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //19
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {640,0,320+640,240}},
		{0, 320, 240, 0, 0, {640,480,320+640,240+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //20
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {640,0,400+640,300}},
		{0, 400, 300, 0, 0, {640,480,400+640,300+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //21
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {640,0,640+640,300}},
		{0, 640, 300, 0, 0, {640,480,640+640,300+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //22
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {640,0,400+640,480}},
		{0, 400, 480, 0, 0, {640,480,400+640,480+480}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //23
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {640,480,320+640,240+480}},
		{0, 1440, 1080, 0, 0, {240,0,1440+240,1080}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //24
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {640,480,400+640,300+480}},
		{0, 1440, 1080, 0, 0, {240,0,1440+240,1080}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //25
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {640,480,640+640,300+480}},
		{0, 1920, 900, 0, 0, {0,90,1920,900+90}},
		1, 1
	},
	1, "1920.yuv_semi"
},
{ //26
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {640,480,400+640,480+480}},
		{0, 900, 1080, 0, 0, {510,0,900+510,1080}},
		1, 1
	},
	1, "1920.yuv_semi"
},
/* Source: 640x480 YUV420 semi-planar */
{ //27
	{
		/* 1280x720 @ 60 Hz */
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		1, 1
	},
	1, "640.yuv_semi"
},
{ //28
	{
		/* 1280x720 @ 60 Hz */
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 320, 240, 0, 0, {0,0,320,240}},
		1, 1
	},
	1, "640.yuv_semi"
},
{ //29
	{
		/* 1280x720 @ 60 Hz */
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 640, 480, 0, 0, {0,480,640,480+480}},
		1, 1
	},
	1, "640.yuv_semi"
},
{ //30
	{
		/* 1280x720 @ 60 Hz */
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 320, 240, 0, 0, {0,480,320,240+480}},
		1, 1
	},
	1, "640.yuv_semi"
},
{ //31
	{
		/* 1280x720 @ 60 Hz */
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 640, 480, 0, 0, {640,0,640+640,480}},
		1, 1
	},
	1, "640.yuv_semi"
},
{ //32
	{
		/* 1280x720 @ 60 Hz */
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 320, 240, 0, 0, {640,0,320+640,240}},
		1, 1
	},
	1, "640.yuv_semi"
},
{ //33
	{
		/* 1280x720 @ 60 Hz */
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 640, 480, 0, 0, {640,480,640+640,480+480}},
		1, 1
	},
	1, "640.yuv_semi"
},
{ //34
	{
		/* 1280x720 @ 60 Hz */
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 320, 240, 0, 0, {640,480,320+640,240+480}},
		1, 1
	},
	1, "640.yuv_semi"
},
/** Scaling part **/
/* Source: 1920x1080 rgb888 */
{ //35
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {1920*0.1,1080*0.1,1920*0.9,1080*0.9}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
{ //36
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.8, 720*0.8, 0, 0, {1280*0.1,720*0.1,1280*0.9,720*0.9}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
{ //37
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.05,1080*0.05,1920*0.95,1080*0.95}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
{ //38
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.05,720*0.05,1280*0.95,720*0.95}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
{ //39
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,1080*0.05,1920*0.95,1080}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
{ //40
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,720*0.05,1280*0.95,720}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
{ //41
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.1,0,1920,1080*0.9}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
{ //42
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.1,0,1280,720*0.9}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
{ //43
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.98, 0, 0, {1920*0.05,0,1920,1080*0.98}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
{ //44
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.95, 720*0.98, 0, 0, {1280*0.05,0,1280,720*0.98}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
{ //45
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,1080*0.1,1920*0.9,1080}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
{ //46
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,720*0.1,1280*0.9,720}},
		1, 1,
	},
	1, "1920.yuv_semi"
},
/* Source: 1280x720 YUV420 Semi-planar */
{ //47
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.8, 720*0.8, 0, 0, {1280*0.1,720*0.1,1280*0.9,720*0.9}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
{ //48
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {1920*0.1,1080*0.1,1920*0.9,1080*0.9}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
{ //49
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.05,720*0.05,1280*0.95,720*0.95}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
{ //50
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.05,1080*0.05,1920*0.95,1080*0.95}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
{ //51
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,720*0.05,1280*0.95,720}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
{ //52
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,1080*0.05,1920*0.95,1080}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
{ //53
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.1,0,1280,720*0.9}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
{ //54
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.1,0,1920,1080*0.9}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
{ //55
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.95, 720*0.95, 0, 0, {1280*0.05,0,1280,720*0.95}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
{ //56
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {1920*0.05,0,1920,1080*0.95}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
{ //57
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,720*0.1,1280*0.9,720}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
{ //58
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,1080*0.1,1920*0.9,1080}},
		1, 1,
	},
	1, "1280.yuv_semi"
},
/* Source: 720x480 yuv420 */
{ //59
	{
		NULL, 60, 720, 480, 4, 80, 48, 6, 3, 32, 10,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 720*0.8, 480*0.8, 0, 0, {720*0.1,480*0.1,720*0.9,480*0.9}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //60
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1280*0.8, 720*0.8, 0, 0, {1280*0.1,720*0.1,1280*0.9,720*0.9}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //61
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {1920*0.1,1080*0.1,1920*0.9,1080*0.9}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //62
	{
		NULL, 60, 720, 480, 4, 80, 48, 6, 3, 32, 10,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 720*0.9, 480*0.9, 0, 0, {720*0.05,480*0.05,720*0.95,480*0.95}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //63
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.05,720*0.05,1280*0.95,720*0.95}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //64
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.05,1080*0.05,1920*0.95,1080*0.95}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //65
	{
		NULL, 60, 720, 480, 4, 80, 48, 6, 3, 32, 10,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 720*0.95, 480*0.95, 0, 0, {0,480*0.05,720*0.95,480}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //66
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,720*0.05,1280*0.95,720}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //67
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,1080*0.05,1920*0.95,1080}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //68
	{
		NULL, 60, 720, 480, 4, 80, 48, 6, 3, 32, 10,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 720*0.9, 480*0.9, 0, 0, {720*0.1,0,720,480*0.9}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //69
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.1,0,1280,720*0.9}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //70
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.1,0,1920,1080*0.9}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //71
	{
		NULL, 60, 720, 480, 4, 80, 48, 6, 3, 32, 10,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 720*0.95, 480*0.95, 0, 0, {720*0.05,0,720,480*0.95}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //72
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1280*0.95, 720*0.95, 0, 0, {1280*0.05,0,1280,720*0.95}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //73
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {1920*0.05,0,1920,1080*0.95}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //74
	{
		NULL, 60, 720, 480, 4, 80, 48, 6, 3, 32, 10,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 720*0.9, 480*0.9, 0, 0, {0,480*0.1,720*0.9,480}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //75
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,720*0.1,1280*0.9,720}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
{ //76
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 480, 0, 0, {0,0,720,480}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,1080*0.1,1920*0.9,1080}},
		1, 1,
	},
	1, "720x480_Y_UV20.yuv"
},
/* Source: 800x600 rgb888 */
{ //77
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.8, 600*0.8, 0, 0, {800*0.1,600*0.1,800*0.9,600*0.9}},
		1, 1,
	},
	1, "800x600_1_Y_UV20.yuv"
},
{ //78
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.9, 600*0.9, 0, 0, {800*0.05,600*0.05,800*0.95,600*0.95}},
		1, 1,
	},
	1, "800x600_1_Y_UV20.yuv"
},
{ //79
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.95, 600*0.95, 0, 0, {0,600*0.05,800*0.95,600}},
		1, 1,
	},
	1, "800x600_1_Y_UV20.yuv"
},
{ //80
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.9, 600*0.9, 0, 0, {800*0.1,0,800,600*0.9}},
		1, 1,
	},
	1, "800x600_1_Y_UV20.yuv"
},
{ //81
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.95, 600*0.95, 0, 0, {800*0.05,0,800,600*0.95}},
		1, 1,
	},
	1, "800x600_1_Y_UV20.yuv"
},
{ //82
	{
		NULL, 60, 800, 600, 3, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800*0.9, 600*0.9, 0, 0, {0,600*0.1,800*0.9,600}},
		1, 1,
	},
	1, "800x600_1_Y_UV20.yuv"
},

/** End of vi_cases **/
{
	{
                NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
                FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
                FB_VMODE_NONINTERLACED
        },
	{
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		-1, -1,
	},
	-1, ""
}
};

struct uv_case uv_cases[] = {
/* Input UI 1920x1080 & VIDEO 1920x1080 YUV420 */
{ //0
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {1920*0.1,1080*0.1,1920*0.9,1080*0.9}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {1920*0.1,1080*0.1,1920*0.9,1080*0.9}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //1
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.8, 720*0.8, 0, 0, {1280*0.1,720*0.1,1280*0.9,720*0.9}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.8, 1080*0.8, 0, 0, {1280*0.1,1080*0.1,1280*0.9,1080*0.9}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //2
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.05,1080*0.05,1920*0.95,1080*0.95}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.05,1080*0.05,1920*0.95,1080*0.95}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //3
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.05,720*0.05,1280*0.95,720*0.95}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 1080*0.9, 0, 0, {1280*0.05,1080*0.05,1280*0.95,1080*0.95}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //4
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,1080*0.05,1920*0.95,1080}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,1080*0.05,1920*0.95,1080}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //5
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,720*0.05,1280*0.95,720}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,720*0.05,1280*0.95,720}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //6
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.1,0,1920,1080*0.9}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.1,0,1920,1080*0.9}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //7
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.1,0,1280,720*0.9}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.1,0,1280,720*0.9}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //8
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {1920*0.05,0,1920,1080*0.95}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {1920*0.05,0,1920,1080*0.95}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //9
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.95, 720*0.95, 0, 0, {1280*0.05,0,1280,720*0.95}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.95, 720*0.95, 0, 0, {1280*0.05,0,1280,720*0.95}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //10
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,1080*0.1,1920*0.9,1080}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,1080*0.1,1920*0.9,1080}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //11
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,720*0.1,1280*0.9,720}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,720*0.1,1280*0.9,720}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
/* Input UI 1920x1080 & VIDEO 1280x720 YUV420 */
{ //12
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {1920*0.1,1080*0.1,1920*0.9,1080*0.9}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {1920*0.1,1080*0.1,1920*0.9,1080*0.9}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
{ //13
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.8, 720*0.8, 0, 0, {1280*0.1,720*0.1,1280*0.9,720*0.9}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.8, 1080*0.8, 0, 0, {1280*0.1,1080*0.1,1280*0.9,1080*0.9}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
{ //14
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.05,1080*0.05,1920*0.95,1080*0.95}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.05,1080*0.05,1920*0.95,1080*0.95}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
{ //15
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.05,720*0.05,1280*0.95,720*0.95}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.9, 1080*0.9, 0, 0, {1280*0.05,1080*0.05,1280*0.95,1080*0.95}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
{ //16
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,1080*0.05,1920*0.95,1080}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,1080*0.05,1920*0.95,1080}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
{ //17
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,720*0.05,1280*0.95,720}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,720*0.05,1280*0.95,720}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
{ //18
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.1,0,1920,1080*0.9}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {1920*0.1,0,1920,1080*0.9}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
{ //19
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.1,0,1280,720*0.9}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.9, 720*0.9, 0, 0, {1280*0.1,0,1280,720*0.9}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
{ //20
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {1920*0.05,0,1920,1080*0.95}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {1920*0.05,0,1920,1080*0.95}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
{ //21
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.95, 720*0.95, 0, 0, {1280*0.05,0,1280,720*0.95}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.95, 720*0.95, 0, 0, {1280*0.05,0,1280,720*0.95}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
{ //22
	{
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,1080*0.1,1920*0.9,1080}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,1080*0.1,1920*0.9,1080}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
{ //23
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,720*0.1,1280*0.9,720}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,720*0.1,1280*0.9,720}},
		1, 1
	},
	0x2, 1, 1, "1920x1080_1.bmp", "1280x720_2_Y_UV20.yuv"
},
/* 800x480 cases ui:800x480 video:1920x1080 */
{ //24
	{
		NULL, 60, 800, 480, 5, 26, 210, 13, 22, 20, 10,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 480, 0, 0, {0,0,800,480}},
		{0, 800, 480, 0, 0, {0,0,800,480}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 800, 480, 0, 0, {0,0,800,480}},
		1, 1
	},
	0x1, 1, 1, "800x480.bmp", "1920x1080_1_Y_UV20.yuv"
},
{ //25
	{
		NULL, 60, 800, 480, 5, 26, 210, 13, 22, 20, 10,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 480, 0, 0, {0,0,800,480}},
		{0, 800*0.9, 480*0.9, 0, 0, {800*0.05,480*0.05,800*0.95,480*0.95}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 800*0.9, 480*0.9, 0, 0, {800*0.05,480*0.05,800*0.95,480*0.95}},
		1, 1
	},
	0x1, 1, 1, "800x480.bmp", "1920x1080_1_Y_UV20.yuv"
},
{ //26
	{
		NULL, 60, 800, 480, 5, 26, 210, 13, 22, 20, 10,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 480, 0, 0, {0,0,800,480}},
		{0, 800*0.8, 480*0.8, 0, 0, {800*0.1,480*0.1,800*0.9,480*0.9}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 800*0.8, 480*0.8, 0, 0, {800*0.1,480*0.1,800*0.9,480*0.9}},
		1, 1
	},
	0x1, 1, 1, "800x480.bmp", "1920x1080_1_Y_UV20.yuv"
},
{ //27
	{
		NULL, 60, 800, 480, 5, 26, 210, 13, 22, 20, 10,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 480, 0, 0, {0,0,800,480}},
		{0, 800*0.7, 480*0.7, 0, 0, {800*0.15,480*0.15,800*0.85,480*0.85}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 800*0.7, 480*0.7, 0, 0, {800*0.15,480*0.15,800*0.85,480*0.85}},
		1, 1
	},
	0x1, 1, 1, "800x480.bmp", "1920x1080_1_Y_UV20.yuv"
},
{ //28
	{
		NULL, 60, 800, 480, 5, 26, 210, 13, 22, 20, 10,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 480, 0, 0, {0,0,800,480}},
		{0, 800*0.6, 480*0.6, 0, 0, {800*0.2,480*0.2,800*0.8,480*0.8}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 800*0.6, 480*0.6, 0, 0, {800*0.2,480*0.2,800*0.8,480*0.8}},
		1, 1
	},
	0x1, 1, 1, "800x480.bmp", "1920x1080_1_Y_UV20.yuv"
},
{ //29
	{
		NULL, 60, 800, 480, 5, 26, 210, 13, 22, 20, 10,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 480, 0, 0, {0,0,800,480}},
		{0, 800, 480, 0, 0, {0,0,800,480}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 800, 480, 0, 0, {0,0,800,480}},
		1, 1
	},
	0x0, 1, 1, "800x480.bmp", "1920x1080_1_Y_UV20.yuv"
},
{ //30
	{
		NULL, 60, 800, 480, 5, 26, 210, 13, 22, 20, 10,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 480, 0, 0, {0,0,800,480}},
		{0, 800*0.9, 480*0.9, 0, 0, {800*0.05,480*0.05,800*0.95,480*0.95}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 800*0.9, 480*0.9, 0, 0, {800*0.05,480*0.05,800*0.95,480*0.95}},
		1, 1
	},
	0x0, 1, 1, "800x480.bmp", "1920x1080_1_Y_UV20.yuv"
},
{ //31
	{
		NULL, 60, 800, 480, 5, 26, 210, 13, 22, 20, 10,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 480, 0, 0, {0,0,800,480}},
		{0, 800*0.8, 480*0.8, 0, 0, {800*0.1,480*0.1,800*0.9,480*0.9}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 800*0.8, 480*0.8, 0, 0, {800*0.1,480*0.1,800*0.9,480*0.9}},
		1, 1
	},
	0x0, 1, 1, "800x480.bmp", "1920x1080_1_Y_UV20.yuv"
},
{ //32
	{
		NULL, 60, 800, 480, 5, 26, 210, 13, 22, 20, 10,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 480, 0, 0, {0,0,800,480}},
		{0, 800*0.7, 480*0.7, 0, 0, {800*0.15,480*0.15,800*0.85,480*0.85}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 800*0.7, 480*0.7, 0, 0, {800*0.15,480*0.15,800*0.85,480*0.85}},
		1, 1
	},
	0x0, 1, 1, "800x480.bmp", "1920x1080_1_Y_UV20.yuv"
},
{ //33
	{
		NULL, 60, 800, 480, 5, 26, 210, 13, 22, 20, 10,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 480, 0, 0, {0,0,800,480}},
		{0, 800*0.6, 480*0.6, 0, 0, {800*0.2,480*0.2,800*0.8,480*0.8}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 800*0.6, 480*0.6, 0, 0, {800*0.2,480*0.2,800*0.8,480*0.8}},
		1, 1
	},
	0x0, 1, 1, "800x480.bmp", "1920x1080_1_Y_UV20.yuv"
},
/** End of uv_cases **/
{
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		-1, -1
	},
	{
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		-1, -1
	},
	-1, -1, -1, "", ""
}
};

struct uv_case offset_cases[] = {
{ //0
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		1, 1
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 640, 480, 0, 0, {0,0,640,480}},
		1, 1
	},
	0x1, 1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //1
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		1, 1
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		1, 1
	},
	0x1, 1, 1, "1280x720_1.bmp", "1280x720_2_Y_UV20.yuv"
},
/** End of offset_cases **/
{
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		-1, -1
	},
	{
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		-1, -1
	},
	-1, -1, -1, "", ""
}
};
#endif

#if 0
/** UI **/
struct ui_case ui_cases[] = {
/* 320x240 None */
{ //0
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 320, 240, 0, 0, {0,0,320,240}},
		1, 1
	},
	1, "32_8888_320x240.bmp"
},

/* 320x240 Offset */
{ //1
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 160, 120, 0, 0, {160,120,320,240}},
		1, 1
	},
	1, "32_8888_160x120.bmp"
},

/* 320x240 Scale up */
{ //2
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 320, 240, 0, 0, {0,0,320,240}},
		1, 1
	},
	1, "32_8888_160x120.bmp"
},

/* 320x240 Scale down */
{ //3
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1
	},
	1, "32_8888_320x240.bmp"
},

/* 320x240 Offset+Scale up */
{ //4
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 240, 180, 0, 0, {40,30,280,210}},
		1, 1
	},
	1, "32_8888_160x120.bmp"
},

/* 320x240 Offset+Scale down */
{ //5
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 280, 200, 0, 0, {40,40,320,240}},
		1, 1
	},
	1, "32_8888_320x240.bmp"
},


/* 640x480 None */
{ //6
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 640, 480, 0, 0, {0,0,640,480}},
		1, 1
	},
	1, "32_8888_640x480.bmp"
},

/* 640x480 Offset */
{ //7
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 320, 240, 0, 0, {320,240,640,480}},
		1, 1
	},
	1, "32_8888_320x240.bmp"
},

/* 640x480 Scale up */
{ //8
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 640, 480, 0, 0, {0,0,640,480}},
		1, 1
	},
	1, "32_8888_160x120.bmp"
},

/* 640x480 Scale down */
{ //9
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1
	},
	1, "32_8888_640x480.bmp"
},

/* 640x480 Offset+Scale up */
{ //10
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 480, 360, 0, 0, {80,60,560,420}},
		1, 1
	},
	1, "32_8888_320x240.bmp"
},

/* 640x480 Offset+Scale down */
{ //11
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 320, 240, 0, 0, {160,120,480,360}},
		1, 1
	},
	1, "32_8888_640x480.bmp"
},


/* 800x600 None */
{ //12
	/* 800x600 @ 60 Hz, 37.8 kHz hsync */
	{
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800, 600, 0, 0, {0,0,800,600}},
		1, 1
	},
	1, "32_8888_800x600.bmp"
},

/* 800x600 Offset */
{ //13
	/* 800x600 @ 60 Hz, 37.8 kHz hsync */
	{
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 640, 480, 0, 0, {160,120,800,600}},
		1, 1
	},
	1, "32_8888_640x480.bmp"
},

/* 800x600 Scale up */
{ //14
	/* 800x600 @ 60 Hz, 37.8 kHz hsync */
	{
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 800, 600, 0, 0, {0,0,800,600}},
		1, 1
	},
	1, "32_8888_160x120.bmp"
},

/* 800x600 Scale down */
{ //15
	/* 800x600 @ 60 Hz, 37.8 kHz hsync */
	{
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1
	},
	1, "32_8888_800x600.bmp"
},

/* 800x600 Offset+Scale up */
{ //16
	/* 800x600 @ 60 Hz, 37.8 kHz hsync */
	{
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 600, 450, 0, 0, {100,75,700,525}},
		1, 1
	},
	1, "32_8888_320x240.bmp"
},

/* 800x600 Offset+Scale down */
{ //17
	/* 800x600 @ 60 Hz, 37.8 kHz hsync */
	{
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 640, 480, 0, 0, {80,60,720,540}},
		1, 1
	},
	1, "32_8888_800x600.bmp"
},


/* 1024x600 None */
{ //18
	/* 1024x600 @ 60 Hz  50.4MHz */
	{
		NULL, 60, 1024, 600, 19841, 240, 48, 12, 3, 32, 10,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 1024, 600, 0, 0, {0,0,1024,600}},
		{0, 1024, 600, 0, 0, {0,0,1024,600}},
		1, 1
	},
	1, "32_8888_1024x600.bmp"
},

/* 1024x600 Offset */
{ //19
	/* 1024x600 @ 60 Hz  50.4MHz */
	{
		NULL, 60, 1024, 600, 19841, 240, 48, 12, 3, 32, 10,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 640, 480, 0, 0, {384,120,1024,600}},
		1, 1
	},
	1, "32_8888_640x480.bmp"
},

/* 1024x600 Scale up */
{ //20
	/* 1024x600 @ 60 Hz  50.4MHz */
	{
		NULL, 60, 1024, 600, 19841, 240, 48, 12, 3, 32, 10,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 1024, 600, 0, 0, {0,0,1024,600}},
		1, 1
	},
	1, "32_8888_160x120.bmp"
},

/* 1024x600 Scale down */
{ //21
	/* 1024x600 @ 60 Hz  50.4MHz */
	{
		NULL, 60, 1024, 600, 19841, 240, 48, 12, 3, 32, 10,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 1024, 600, 0, 0, {0,0,1024,600}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1
	},
	1, "32_8888_1024x600.bmp"
},

/* 1024x600 Offset+Scale up */
{ //22
	/* 1024x600 @ 60 Hz  50.4MHz */
	{
		NULL, 60, 1024, 600, 19841, 240, 48, 12, 3, 32, 10,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 768, 450, 0, 0, {128,75,896,525}},
		1, 1
	},
	1, "32_8888_320x240.bmp"
},

/* 1024x600 Offset+Scale down */
{ //23
	/* 1024x600 @ 60 Hz  50.4MHz */
	{
		NULL, 60, 1024, 600, 19841, 240, 48, 12, 3, 32, 10,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 1024, 600, 0, 0, {0,0,1024,600}},
		{0, 640, 480, 0, 0, {192,60,832,540}},
		1, 1
	},
	1, "32_8888_1024x600.bmp"
},


/* 1024x768 None */
{ //24
	{
		/* 1024x768 @ 87 Hz interlaced, 35.5 kHz hsync */
		NULL, 60, 1024, 768, 22271, 56, 24, 33, 8, 160, 8,
		0, FB_VMODE_INTERLACED
	},
	{
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		1, 1,
	},
	1, "32_8888_1024x768.bmp"
},

/* 1024x768 Offset */
{ //25
	{
		/* 1024x768 @ 87 Hz interlaced, 35.5 kHz hsync */
		NULL, 60, 1024, 768, 22271, 56, 24, 33, 8, 160, 8,
		0, FB_VMODE_INTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800, 600, 0, 0, {224,168,1024,768}},
		1, 1,
	},
	1, "32_8888_800x600.bmp"
},

/* 1024x768 Scale up */
{ //26
	{
		/* 1024x768 @ 87 Hz interlaced, 35.5 kHz hsync */
		NULL, 60, 1024, 768, 22271, 56, 24, 33, 8, 160, 8,
		0, FB_VMODE_INTERLACED
	},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		1, 1,
	},
	1, "32_8888_160x120.bmp"
},

/* 1024x768 Scale down */
{ //27
	{
		/* 1024x768 @ 87 Hz interlaced, 35.5 kHz hsync */
		NULL, 60, 1024, 768, 22271, 56, 24, 33, 8, 160, 8,
		0, FB_VMODE_INTERLACED
	},
	{
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1,
	},
	1, "32_8888_1024x768.bmp"
},

/* 1024x768 Offset+Scale up */
{ //28
	{
		/* 1024x768 @ 87 Hz interlaced, 35.5 kHz hsync */
		NULL, 60, 1024, 768, 22271, 56, 24, 33, 8, 160, 8,
		0, FB_VMODE_INTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 768, 576, 0, 0, {128,96,896,672}},
		1, 1,
	},
	1, "32_8888_640x480.bmp"
},

/* 1024x768 Offset+Scale down */
{ //29
	{
		/* 1024x768 @ 87 Hz interlaced, 35.5 kHz hsync */
		NULL, 60, 1024, 768, 22271, 56, 24, 33, 8, 160, 8,
		0, FB_VMODE_INTERLACED
	},
	{
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		{0, 800, 600, 0, 0, {112,84,912,684}},
		1, 1,
	},
	1, "32_8888_1024x768.bmp"
},


/* 1280x720 None */
{ //30
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		1, 1,
	},
	1, "32_8888_1280x720.bmp"
},

/* 1280x720 Offset */
{ //31
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1024, 600, 0, 0, {0,0,1024,600}},
		{0, 1024, 600, 0, 0, {256,120,1280,720}},
		1, 1,
	},
	1, "32_8888_1024x600.bmp"
},

/* 1280x720 Scale up */
{ //32
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		1, 1,
	},
	1, "32_8888_160x120.bmp"
},

/* 1280x720 Scale down */
{ //33
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1,
	},
	1, "32_8888_1280x720.bmp"
},

/* 1280x720 Offset+Scale up */
{ //34
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 960, 540, 0, 0, {160,90,1120,630}},
		1, 1,
	},
	1, "32_8888_640x480.bmp"
},

/* 1280x720 Offset+Scale down */
{ //35
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1024, 600, 0, 0, {128,60,1152,660}},
		1, 1,
	},
	1, "32_8888_1280x720.bmp"
},


/* 1920x1080 None */
{ //36
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		1, 1,
	},
	1, "32_8888_1920x1080.bmp"
},

/* 1920x1080 Offset */
{ //37
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280, 720, 0, 0, {640,360,1920,1080}},
		1, 1,
	},
	1, "32_8888_1920x1080.bmp"
},

/* 1920x1080 Scale up */
{ //38
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		1, 1,
	},
	1, "32_8888_160x120.bmp"
},

/* 1920x1080 Scale down */
{ //39
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1,
	},
	1, "32_8888_1920x1080.bmp"
},

/* 1920x1080 Offset+Scale up */
{ //40
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1440, 810, 0, 0, {240,135,1680,945}},
		1, 1,
	},
	1, "32_8888_1280x720.bmp"
},

/* 1920x1080 Offset+Scale down */
{ //41
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280, 720, 0, 0, {320,180,1600,900}},
		1, 1,
	},
	1, "32_8888_1920x1080.bmp"
},

/** End of ui_cases **/
{
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		-1, -1,
	},
	-1, ""
}
};

/** VIDEO **/
struct vi_case vi_cases[] = {
/* 320x240 None */
{ //0
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 320, 240, 0, 0, {0,0,320,240}},
		1, 1
	},
	1, "320.yuv_semi"
},

/* 320x240 Crop */
{ //1
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 320, 240, 0, 0, {160,120,320,240}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1
	},
	1, "320.yuv_semi"
},

/* 320x240 Offset */
{ //2
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 160, 120, 0, 0, {160,120,320,240}},
		1, 1
	},
	1, "160.yuv_semi"
},

/* 320x240 Scale up */
{ //3
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 320, 240, 0, 0, {0,0,320,240}},
		1, 1
	},
	1, "160.yuv_semi"
},

/* 320x240 Scale down */
{ //4
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1
	},
	1, "320.yuv_semi"
},

/* 320x240 Crop+Offset */
{ //5
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 320, 240, 0, 0, {0,0,160,120}},
		{0, 160, 120, 0, 0, {160,120,320,240}},
		1, 1
	},
	1, "320.yuv_semi"
},

/* 320x240 Crop+Scale up */
{ //6
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 320, 240, 0, 0, {80,60,240,180}},
		{0, 320, 240, 0, 0, {0,0,320,240}},
		1, 1
	},
	1, "320.yuv_semi"
},

/* 320x240 Crop+Scale down */
{ //7
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 640, 480, 0, 0, {320,240,640,480}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1
	},
	1, "640.yuv_semi"
},

/* 320x240 Offset+Scale up */
{ //8
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 240, 180, 0, 0, {40,30,280,210}},
		1, 1
	},
	1, "160.yuv_semi"
},

/* 320x240 Offset+Scale down */
{ //9
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 280, 210, 0, 0, {20,15,300,225}},
		1, 1
	},
	1, "320.yuv_semi"
},

/* 320x240 Crop+Offset+Scale up */
{ //10
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 320, 240, 0, 0, {80,60,240,180}},
		{0, 300, 220, 0, 0, {10,10,310,230}},
		1, 1
	},
	1, "320.yuv_semi"
},

/* 320x240 Crop+Offset+Scale down */
{ //11
	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect ratio */
	{
		NULL, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1,
		0, FB_VMODE_DOUBLE
	},
	{
		{0, 320, 240, 0, 0, {40,30,280,210}},
		{0, 160, 120, 0, 0, {80,60,240,180}},
		1, 1
	},
	1, "320.yuv_semi"
},


/* 640x480 None */
{ //12
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 640, 480, 0, 0, {0,0,640,480}},
		1, 1
	},
	1, "640.yuv_semi"
},

/* 640x480 Crop */
{ //13
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {320,240,640,480}},
		{0, 320, 240, 0, 0, {0,0,320,240}},
		1, 1
	},
	1, "640.yuv_semi"
},

/* 640x480 Offset */
{ //14
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 320, 240, 0, 0, {320,240,640,480}},
		1, 1
	},
	1, "320.yuv_semi"
},

/* 640x480 Scale up */
{ //15
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 640, 480, 0, 0, {0,0,640,480}},
		1, 1
	},
	1, "160.yuv_semi"
},

/* 640x480 Scale down */
{ //16
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1
	},
	1, "640.yuv_semi"
},

/* 640x480 Crop+Offset */
{ //17
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,320,240}},
		{0, 320, 240, 0, 0, {320,240,640,480}},
		1, 1
	},
	1, "640.yuv_semi"
},

/* 640x480 Crop+Scale up */
{ //18
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {160,120,480,360}},
		{0, 640, 480, 0, 0, {0,0,640,480}},
		1, 1
	},
	1, "640.yuv_semi"
},

/* 640x480 Crop+Scale down */
{ //19
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {160,120,800,600}},
		{0, 320, 240, 0, 0, {0,0,320,240}},
		1, 1
	},
	1, "800.yuv_semi"
},

/* 640x480 Offset+Scale up */
{ //20
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 480, 360, 0, 0, {80,60,560,420}},
		1, 1
	},
	1, "320.yuv_semi"
},

/* 640x480 Offset+Scale down */
{ //21
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 560, 420, 0, 0, {40,30,600,450}},
		1, 1
	},
	1, "640.yuv_semi"
},

/* 640x480 Crop+Offset+Scale up */
{ //22
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {160,120,480,360}},
		{0, 600, 440, 0, 0, {20,20,620,460}},
		1, 1
	},
	1, "640.yuv_semi"
},

/* 640x480 Crop+Offset+Scale down */
{ //23
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {80,60,560,420}},
		{0, 320, 240, 0, 0, {160,120,480,360}},
		1, 1
	},
	1, "640.yuv_semi"
},


/* 800x600 None */
{ //24
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 800, 600, 0, 0, {0,0,800,600}},
		1, 1
	},
	1, "800.yuv_semi"
},

/* 800x600 Crop */
{ //25
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {400,300,800,600}},
		{0, 400, 300, 0, 0, {0,0,400,300}},
		1, 1
	},
	1, "800.yuv_semi"
},

/* 800x600 Offset */
{ //26
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 640, 480, 0, 0, {160,120,800,600}},
		1, 1
	},
	1, "640.yuv_semi"
},

/* 800x600 Scale up */
{ //27
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 160, 120, 0, 0, {0,0,160,120}},
		{0, 800, 600, 0, 0, {0,0,800,600}},
		1, 1
	},
	1, "160.yuv_semi"
},

/* 800x600 Scale down */
{ //28
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 160, 120, 0, 0, {0,0,160,120}},
		1, 1
	},
	1, "800.yuv_semi"
},

/* 800x600 Crop+Offset */
{ //29
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,400,300}},
		{0, 400, 300, 0, 0, {400,300,800,600}},
		1, 1
	},
	1, "800.yuv_semi"
},

/* 800x600 Crop+Scale up */
{ //30
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {200,150,600,450}},
		{0, 800, 600, 0, 0, {0,0,800,600}},
		1, 1
	},
	1, "800.yuv_semi"
},

/* 800x600 Crop+Scale down */
{ //31
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 1024, 768, 0, 0, {512,384,1024,768}},
		{0, 320, 240, 0, 0, {0,0,320,240}},
		1, 1
	},
	1, "1024.yuv_semi"
},

/* 800x600 Offset+Scale up */
{ //32
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 320, 240, 0, 0, {0,0,320,240}},
		{0, 600, 450, 0, 0, {100,75,700,525}},
		1, 1
	},
	1, "320.yuv_semi"
},

/* 800x600 Offset+Scale down */
{ //33
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {0,0,800,600}},
		{0, 680, 510, 0, 0, {60,45,740,555}},
		1, 1
	},
	1, "800.yuv_semi"
},

/* 800x600 Crop+Offset+Scale up */
{ //34
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {200,150,600,450}},
		{0, 740, 540, 0, 0, {30,30,770,570}},
		1, 1
	},
	1, "800.yuv_semi"
},

/* 800x600 Crop+Offset+Scale down */
{ //35
	{
		/* 800*600@60 HZ */
		NULL, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		0, FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 600, 0, 0, {100,75,700,525}},
		{0, 320, 240, 0, 0, {240,180,560,420}},
		1, 1
	},
	1, "800.yuv_semi"
},


/* 1024x600 None */
/* 1024x600 Crop */
/* 1024x600 Offset */
/* 1024x600 Scale up */
/* 1024x600 Scale down */
/* 1024x600 Crop+Offset */
/* 1024x600 Crop+Scale up */
/* 1024x600 Crop+Scale down */
/* 1024x600 Offset+Scale up */
/* 1024x600 Offset+Scale down */
/* 1024x600 Crop+Offset+Scale up */
/* 1024x600 Crop+Offset+Scale down */

/* 1024x768 None */
/* 1024x768 Crop */
/* 1024x768 Offset */
/* 1024x768 Scale up */
/* 1024x768 Scale down */
/* 1024x768 Crop+Offset */
/* 1024x768 Crop+Scale up */
/* 1024x768 Crop+Scale down */
/* 1024x768 Offset+Scale up */
/* 1024x768 Offset+Scale down */
/* 1024x768 Crop+Offset+Scale up */
/* 1024x768 Crop+Offset+Scale down */

/* 1280x720 None */
/* 1280x720 Crop */
/* 1280x720 Offset */
/* 1280x720 Scale up */
/* 1280x720 Scale down */
/* 1280x720 Crop+Offset */
/* 1280x720 Crop+Scale up */
/* 1280x720 Crop+Scale down */
/* 1280x720 Offset+Scale up */
/* 1280x720 Offset+Scale down */
/* 1280x720 Crop+Offset+Scale up */
/* 1280x720 Crop+Offset+Scale down */

/* 1920x1080 None */
/* 1920x1080 Crop */
/* 1920x1080 Offset */
/* 1920x1080 Scale up */
/* 1920x1080 Scale down */
/* 1920x1080 Crop+Offset */
/* 1920x1080 Crop+Scale up */
/* 1920x1080 Crop+Scale down */
/* 1920x1080 Offset+Scale up */
/* 1920x1080 Offset+Scale down */
/* 1920x1080 Crop+Offset+Scale up */
/* 1920x1080 Crop+Offset+Scale down */

/** End of vi_cases **/
{
	{
                /* 1920x1080 @ 60 Hz */
                NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
                FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
                FB_VMODE_NONINTERLACED
        },
	{
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		-1, -1,
	},
	-1, ""
}
};

/** Compose **/
struct uv_case uv_cases[] = {
/* 320x240 None */
/* 320x240 Crop */
/* 320x240 Offset */
/* 320x240 Scale up */
/* 320x240 Scale down */
/* 320x240 Crop+Offset */
/* 320x240 Crop+Scale up */
/* 320x240 Crop+Scale down */
/* 320x240 Offset+Scale up */
/* 320x240 Offset+Scale down */
/* 320x240 Crop+Offset+Scale up */
/* 320x240 Crop+Offset+Scale down */

/* 640x480 None */
/* 640x480 Crop */
/* 640x480 Offset */
/* 640x480 Scale up */
/* 640x480 Scale down */
/* 640x480 Crop+Offset */
/* 640x480 Crop+Scale up */
/* 640x480 Crop+Scale down */
/* 640x480 Offset+Scale up */
/* 640x480 Offset+Scale down */
/* 640x480 Crop+Offset+Scale up */
/* 640x480 Crop+Offset+Scale down */

/* 800x600 None */
/* 800x600 Crop */
/* 800x600 Offset */
/* 800x600 Scale up */
/* 800x600 Scale down */
/* 800x600 Crop+Offset */
/* 800x600 Crop+Scale up */
/* 800x600 Crop+Scale down */
/* 800x600 Offset+Scale up */
/* 800x600 Offset+Scale down */
/* 800x600 Crop+Offset+Scale up */
/* 800x600 Crop+Offset+Scale down */

/* 1024x600 None */
/* 1024x600 Crop */
/* 1024x600 Offset */
/* 1024x600 Scale up */
/* 1024x600 Scale down */
/* 1024x600 Crop+Offset */
/* 1024x600 Crop+Scale up */
/* 1024x600 Crop+Scale down */
/* 1024x600 Offset+Scale up */
/* 1024x600 Offset+Scale down */
/* 1024x600 Crop+Offset+Scale up */
/* 1024x600 Crop+Offset+Scale down */

/* 1024x768 None */
/* 1024x768 Crop */
/* 1024x768 Offset */
/* 1024x768 Scale up */
/* 1024x768 Scale down */
/* 1024x768 Crop+Offset */
/* 1024x768 Crop+Scale up */
/* 1024x768 Crop+Scale down */
/* 1024x768 Offset+Scale up */
/* 1024x768 Offset+Scale down */
/* 1024x768 Crop+Offset+Scale up */
/* 1024x768 Crop+Offset+Scale down */

/* 1280x720 None */
/* 1280x720 Crop */
/* 1280x720 Offset */
/* 1280x720 Scale up */
/* 1280x720 Scale down */
/* 1280x720 Crop+Offset */
/* 1280x720 Crop+Scale up */
/* 1280x720 Crop+Scale down */
/* 1280x720 Offset+Scale up */
/* 1280x720 Offset+Scale down */
/* 1280x720 Crop+Offset+Scale up */
/* 1280x720 Crop+Offset+Scale down */

/* 1920x1080 None */
{ //0
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		1, 1,
	},
	0, 0, "32_8888_1920x1080.bmp", "1920.yuv_semi"
},

/* 1920x1080 Crop */
/* 1920x1080 Offset */
/* 1920x1080 Scale up */ /* 1920x1080 Scale down */
/* 1920x1080 Crop+Offset */
/* 1920x1080 Crop+Scale up */
/* 1920x1080 Crop+Scale down */
/* 1920x1080 Offset+Scale up */
/* 1920x1080 Offset+Scale down */
/* 1920x1080 Crop+Offset+Scale up */
/* 1920x1080 Crop+Offset+Scale down */

/* 4.18 FPGA_test_plan.xls */
{ //1
	{
		/* 1920x1080 @ 60 Hz */
		NULL, 60, 1920, 1080, 23, 220, 110, 4, 44, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		1, 1,
	},
	1, 1, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //2
	{
		/* 1280x720 @ 60 Hz */
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		1, 1,
	},
	1, 1, "1280x720_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //3
	{
		/* 1024x768 @ 60 Hz */
		NULL, 60, 1024, 768, 10, 168, 8, 29, 3, 144, 6,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1024, 768, 0, 0, {0,0,1024,768}},
		1, 1,
	},
	0, 0, "1024x768_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //4
	{
		/* 1024x600 @ 60 Hz */
		NULL, 60, 1024, 600, 8, 240, 48, 12, 3, 32, 10,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1024, 600, 0, 0, {0,0,1024,600}},
		{0, 1024, 600, 0, 0, {0,0,1024,600}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1024, 600, 0, 0, {0,0,1024,600}},
		1, 1,
	},
	0, 0, "1024x600.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //5
	{
		/* 960x540 @ 60 Hz */
		NULL, 60, 960, 540, 8, 142, 98, 15, 7, 48, 1,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 960, 540, 0, 0, {0,0,960,540}},
		{0, 960, 540, 0, 0, {0,0,960,540}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 960, 540, 0, 0, {0,0,960,540}},
		1, 1,
	},
	0, 0, "960x540.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //6
	{
		/* 800x480 @ 60 Hz */
		NULL, 60, 800, 480, 6, 8, 13, 7, 5, 3, 1,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 800, 480, 0, 0, {0,0,800,480}},
		{0, 800, 480, 0, 0, {0,0,800,480}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 800, 480, 0, 0, {0,0,800,480}},
		1, 1,
	},
	0, 0, "800x480.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //7
	{
		NULL, 60, 640, 480, 4, 16, 48, 10, 33, 96, 2,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 640, 480, 0, 0, {0,0,640,480}},
		{0, 640, 480, 0, 0, {0,0,640,480}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 640, 480, 0, 0, {0,0,640,480}},
		1, 1,
	},
	0, 0, "640x480.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //8
	{
		NULL, 60, 1080, 1920, 24, 148, 88, 4, 36, 44, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1080, 1920, 0, 0, {0,0,1080,1920}},
		{0, 1080, 1920, 0, 0, {0,0,1080,1920}},
		1, 1,
	},
	{
		{0, 1080, 1920, 0, 0, {0,0,1080,1920}},
		{0, 1080, 1920, 0, 0, {0,0,1080,1920}},
		1, 1,
	},
	0, 0, "1080x1920.bmp", "video_1080x1920_Y_UV20.yuv"
},
{ //9
	{
		NULL, 60, 720, 1280, 10, 18, 20, 20, 198, 2, 2,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 720, 1280, 0, 0, {0,0,720,1280}},
		{0, 720, 1280, 0, 0, {0,0,720,1280}},
		1, 1,
	},
	{
		{0, 1080, 1920, 0, 0, {0,0,1080,1920}},
		{0, 720, 1280, 0, 0, {0,0,720,1280}},
		1, 1,
	},
	0, 0, "720x1280.bmp", "video_1080x1920_Y_UV20.yuv"
},
{ //10
	{
		NULL, 60, 768, 1024, 10, 29, 3, 168, 8, 6, 144,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 768, 1024, 0, 0, {0,0,768,1024}},
		{0, 768, 1024, 0, 0, {0,0,768,1024}},
		1, 1,
	},
	{
		{0, 1080, 1920, 0, 0, {0,0,1080,1920}},
		{0, 768, 1024, 0, 0, {0,0,768,1024}},
		1, 1,
	},
	0, 0, "768x1024.bmp", "video_1080x1920_Y_UV20.yuv"
},
{ //11
	{
		NULL, 60, 600, 1024, 8, 12, 3, 240, 48, 10, 32,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 600, 1024, 0, 0, {0,0,600,1024}},
		{0, 600, 1024, 0, 0, {0,0,600,1024}},
		1, 1,
	},
	{
		{0, 1080, 1920, 0, 0, {0,0,1080,1920}},
		{0, 600, 1024, 0, 0, {0,0,600,1024}},
		1, 1,
	},
	0, 0, "600x1024.bmp", "video_1080x1920_Y_UV20.yuv"
},
{ //12
	{
		NULL, 60, 540, 960, 8, 15, 7, 142, 98, 1, 48,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 540, 960, 0, 0, {0,0,540,960}},
		{0, 540, 960, 0, 0, {0,0,540,960}},
		1, 1,
	},
	{
		{0, 1080, 1920, 0, 0, {0,0,1080,1920}},
		{0, 540, 960, 0, 0, {0,0,540,960}},
		1, 1,
	},
	0, 0, "540x960.bmp", "video_1080x1920_Y_UV20.yuv"
},
{ //13
	{
		NULL, 60, 480, 800, 5, 8, 13, 7, 5, 3, 1,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 480, 800, 0, 0, {0,0,480,800}},
		{0, 480, 800, 0, 0, {0,0,480,800}},
		1, 1,
	},
	{
		{0, 1080, 1920, 0, 0, {0,0,1080,1920}},
		{0, 480, 800, 0, 0, {0,0,480,800}},
		1, 1,
	},
	0, 0, "480x800.bmp", "video_1080x1920_Y_UV20.yuv"
},
{ //14
	{
		NULL, 60, 480, 640, 4, 10, 33, 16, 48, 2, 96,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 480, 640, 0, 0, {0,0,480,640}},
		{0, 480, 640, 0, 0, {0,0,480,640}},
		1, 1,
	},
	{
		{0, 1080, 1920, 0, 0, {0,0,1080,1920}},
		{0, 480, 640, 0, 0, {0,0,480,640}},
		1, 1,
	},
	0, 0, "480x640.bmp", "video_1080x1920_Y_UV20.yuv"
},
{ //15
	{
		NULL, 60, 1920, 1080, 23, 220, 110, 4, 44, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,0,1920*0.95,1080*0.95}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.95, 1080*0.95, 0, 0, {0,0,1920*0.95,1080*0.95}},
		1, 1,
	},
	0, 0, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //16
	{
		NULL, 60, 1920, 1080, 23, 220, 110, 4, 44, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,0,1920*0.9,1080*0.9}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.9, 1080*0.9, 0, 0, {0,0,1920*0.9,1080*0.9}},
		1, 1,
	},
	0, 0, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //17
	{
		NULL, 60, 1920, 1080, 23, 220, 110, 4, 44, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.85, 1080*0.85, 0, 0, {0,0,1920*0.85,1080*0.85}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.85, 1080*0.85, 0, 0, {0,0,1920*0.85,1080*0.85}},
		1, 1,
	},
	0, 0, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //18
	{
		NULL, 60, 1920, 1080, 23, 220, 110, 4, 44, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {0,0,1920*0.8,1080*0.8}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1920*0.8, 1080*0.8, 0, 0, {0,0,1920*0.8,1080*0.8}},
		1, 1,
	},
	0, 0, "1920x1080_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //19
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,0,1280*0.95,720*0.95}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.95, 720*0.95, 0, 0, {0,0,1280*0.95,720*0.95}},
		1, 1,
	},
	0, 0, "1280x720_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //20
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,0,1280*0.9,720*0.9}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.9, 720*0.9, 0, 0, {0,0,1280*0.9,720*0.9}},
		1, 1,
	},
	0, 0, "1280x720_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //21
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.85, 720*0.85, 0, 0, {0,0,1280*0.85,720*0.85}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.85, 720*0.85, 0, 0, {0,0,1280*0.85,720*0.85}},
		1, 1,
	},
	0, 0, "1280x720_1.bmp", "1920x1080_2_Y_UV20.yuv"
},
{ //22
	{
		NULL, 60, 1280, 720, 12, 220, 110, 20, 5, 40, 5,
		FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		FB_VMODE_NONINTERLACED
	},
	{
		{0, 1280, 720, 0, 0, {0,0,1280,720}},
		{0, 1280*0.8, 720*0.8, 0, 0, {0,0,1280*0.8,720*0.8}},
		1, 1,
	},
	{
		{0, 1920, 1080, 0, 0, {0,0,1920,1080}},
		{0, 1280*0.8, 720*0.8, 0, 0, {0,0,1280*0.8,720*0.8}},
		1, 1,
	},
	0, 0, "1280x720_1.bmp", "1920x1080_2_Y_UV20.yuv"
},


/** End of uv_cases **/
{
	{
		/* 640x480 25175000 Hz */
		NULL,60, 640, 480, 39721, 16, 48, 10, 33, 96, 2,
		0,FB_VMODE_NONINTERLACED
	},
	{
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		-1, -1
	},
	{
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		{-1, -1, -1, -1, -1, {-1,-1,-1,-1}},
		-1, -1
	},
	-1, -1, "", ""
}
};
#endif
