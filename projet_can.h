#ifndef __PROJET_H__
#define __PROJET_H__

#ifdef __cplusplus
extern "C"
{
#endif


  typedef struct
  {
    unsigned int width;
    unsigned int height;
    complexe *rawdata;
  } imagecomplexe;


  typedef struct
  {
      float  re;
      float  im;
  }complexe;

  //chercher le maximum dans le tableau et retourne la position du max
  int cherchermax(float *data);



//conversions:
 // imagecomplexe    
//  bwimage_t  ()

//calculs

//void fourier(imagecomplexe, isgne)

// imagecomplexe correlation(imagecomplexe imc1, imagecomplexe imc2);   //correlation simple sur amplitude; images de même taille

//imagecomplexe correlation_contour(imagecomplexe imc1, imagecomplexe imc2);  //correlation avec dérivée

#ifdef __cplusplus
}
#endif

#endif //__PROJET_H__


