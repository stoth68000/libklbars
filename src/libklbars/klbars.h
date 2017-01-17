//
//  klbars.h
//  Kernel Labs Color bar generator
//
//  Created by Devin Heitmueller
//  Copyright (c) 2016 Kernel Labs Inc. All rights reserved.
//

#ifndef klbars_h
#define klbars_h

#ifdef __cplusplus
extern "C" {
#endif

#define KL_COLORBAR_8BIT  0
#define KL_COLORBAR_10BIT 1

struct kl_colorbar_context
{
    unsigned char *frame, *ptr; /* top left of render image and a working ptr */
    unsigned int width, height; /* width/height in pixels */
    unsigned int stride;

    int plotwidth, plotheight, plotctrl;
    int colorspace;

    int currx, curry;

    /* Rendered font fg and bg colors */
    unsigned char bg[2], fg[2];
};

/* Initialize a colorbar context */
int kl_colorbar_init(struct kl_colorbar_context *ctx, unsigned int width,
		     unsigned int height, int bitDepth);

/* Last step to perform: put the fully composited colorbar frame into a final
   buffer in the requested colorspace and stride */
int kl_colorbar_finalize(struct kl_colorbar_context *ctx, unsigned char *buf,
			 unsigned int byteStride);

/* Free an initialized colorbars context */
void kl_colorbar_free(struct kl_colorbar_context *ctx);

int kl_colorbar_render_reset(struct kl_colorbar_context *ctx, unsigned char *ptr, long width);
int kl_colorbar_render_string(struct kl_colorbar_context *ctx, unsigned char *s, int len, int x, int y);

void kl_colorbar_fill_colorbars (struct kl_colorbar_context *ctx);
void kl_colorbar_fill_black (struct kl_colorbar_context *ctx);

#ifdef __cplusplus
};
#endif

#endif
