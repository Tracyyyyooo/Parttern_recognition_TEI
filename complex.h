#ifndef __COMPLEX_H
#define __COMPLEX_H

#include "pngwrap.h"


typedef struct{
    float re;
    float im;
} complex;

typedef struct{
    unsigned int width;
    unsigned int height;
    complex *rawdata;
} image_c;

//fait le produit de 2 nombres complexes
complex produit(complex x, complex y);

//conjugue un nobmre complexe
void conjugue(complex* z);

//initialise les float en complex avec une partie imaginaire nulle
complex reel2complex(float r);

//prend la partie reel
float complex2reel(complex z);

//revoie une image complex a partir de l'image reel
image_c* imReel2Complex(bwimage_t *image);



#endif