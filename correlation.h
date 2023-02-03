#ifndef __CORRELATION_H__
#define __CORRELATION_H__

#include "pngwrap.h"


#ifdef __cplusplus
extern "C"
{
#endif


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


int power(int x, unsigned int n);


//verifie que le tableau est de taille 2 puissance n
unsigned int* verif_taille(bwimage_t image);


//convertit une image reel en complexe et inversement
image_c* imReel2Complex(bwimage_t *image); // si la taille n'est pas une puissance de 2, l'image est agrandie
bwimage_t* imComplex2Reel(image_c *imc); // et normalise


int cherchermax(bwimage_t im);
int cherchermin(bwimage_t im);


//applique la fft
void fourier(image_c* imc,  int isign);

//produit de correlation avec le conjugue
void correlation(image_c imc1, image_c imc2);




#ifdef __cplusplus
}
#endif

#endif