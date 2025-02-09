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

//conjugue un nombre complexe
void conjugue(complex* z);

//initialise les float en complex avec une partie imaginaire nulle
complex reel2complex(float r);



int power(int x, unsigned int n);


//verifie que le tableau est de taille 2 puissance n
unsigned int* verif_taille(bwimage_t image);


//convertit une image reel en complexe et inversement
image_c* imReel2Complex(bwimage_t *image); // si la taille n'est pas une puissance de 2, l'image est agrandie
bwimage_t* imComplex2Reel(image_c *imc); // et normalise
void data(bwimage_t *im); //remplie le data d'une image


//dans une image complexe
int cherchermax(image_c imc);
int cherchermin(image_c imc);
int chercher_proche(image_c imc, float a);


//applique la fft
void fourier(image_c* imc,  int isign);

//produit de correlation avec le conjugue
image_c* correlation(image_c *imc1, image_c *imc2);


//derive dans fourier
void derive(image_c *imc);
void iwZ (complex *z, float w1, float  w2); // z*iw



//pour les test et générer les images

void affiche_imc(image_c* imC);
void affiche_im(bwimage_t* im);
void affiche_data(bwimage_t *im);

void create_im(int size, char* adresse, int color); //crée une image de pixels aléatoires
void add_square(bwimage_t* image, int x, int y, int n, int color, char* adresse);
void *motif(bwimage_t *im);   //met le motif à corréler sous le bon format

#ifdef __cplusplus
}
#endif

#endif