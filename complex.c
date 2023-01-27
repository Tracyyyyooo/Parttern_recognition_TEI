#include "complex.h"
#include <stdio.h>
#include <stdlib.h>
#include "pngwrap.h"

complex produit(complex x, complex y){
    complex z;
    z.re = x.re*y.re - x.im*y.im;
    z.im = x.re*y.im + x.im*y.re;
    return z;
}

void conjugue(complex* z){
    z->im= -(z->im);
}

complex reel2complex(float r){
    complex z;
    z.re = r;
    z.im=0;
    return z;
}

float complex2reel(complex z){
    float r=z.re;
    return r;
}

image_c* imReel2Complex(bwimage_t *image){
    image_c *imC = malloc(sizeof(image_c));
    imC->width=image->width;
    imC->height=image->height;
    imC->rawdata=malloc(imC->width*imC->height*sizeof(complex));
    for(int i=0; i<imC->width*imC->height; i++){
        imC->rawdata[i]=reel2complex((float)image->rawdata[i]);
    }
    return imC;
}