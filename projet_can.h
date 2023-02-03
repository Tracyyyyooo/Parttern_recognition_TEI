#ifndef __PROJET_H__
#define __PROJET_H__
#include "pngwrap.h"

#ifdef __cplusplus
extern "C"
{
#endif


  typedef struct
  {
    unsigned int width;
    unsigned int height;
    complexe *rawdata;
  } image_c;


  typedef struct
  {
      float  re;
      float  im;
  }complex;

  //chercher le maximum dans le tableau et retourne la position du max
  int cherchermax(float *data);   

  //chercher le minimum dans le tableau et retourne la position du min 
  int cherchermin(float *data);


  //conversions:  fini
  image_c* imReel2Complex(bwimage_t *image);
  bwimage_t  imComplex2Reel(image_c *imc);

  //calculs: fini
  void fourier(image_c *imc, int isgne); 
  complex produit(complex x, complex y);

  // imagecomplexe correlation(imagecomplexe imc1, imagecomplexe imc2);   //correlation simple sur amplitude; images de même taille
  complex convolution(image_c imc1, image_c imc2);

  //imagecomplexe correlation_contour(imagecomplexe imc1, imagecomplexe imc2);  //correlation avec dérivée


#ifdef __cplusplus
}
#endif

#endif //__PROJET_CAN_H__
