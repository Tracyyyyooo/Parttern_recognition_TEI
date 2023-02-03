#include <stdio.h>
#include "pngwrap.h"
#include "projet_can.h"
#include <stdlib.h>

int cherchermax(float *data)
{
    int position;
    int n=sizeof(data)/sizeof(data[0]);
    float max=data[0];
    for (int i = 0;i<n;i++)
    {
            if(data[i]>max){
                max=data[i];
                position = i;
            }
            else;
        }
        return position;
}

int cherchermin(float *data)
{
    int position;
    int n=sizeof(data)/sizeof(data[0]);
    float min=data[0];
    for (int i = 0;i<n;i++)
    {
            if(data[i]<min){
                min=data[i];
                position = i;
            }
            else;
        }
        return position;
}


void fourier(image_c *imc,  int isign)
{
unsigned long nn[2]={imc->height,imc->width};
fourn( (float*)imc->rawdata, nn,  2, isign);
}


bwimage_t  imComplex2Reel(image_c *imc)
{
    bwimage_t  *im = malloc(sizeof(bwimage_t));
    im->width = imc->width;
    im->height = imc->height;
    im->rawdata=malloc(im->width*im->height*sizeof(unsigned char));
    for (int i=0; i<im->width*im->height;i++){
        im->rawdata[i]=complex2reel((float)imc->rawdata[i]);
    }
    //on normalise les valeurs entre 0 et 255
    float max=im->rawdata[cherchermax(*im->rawdata)];
    float min=im->rawdata[cherchermin(*im->rawdata)];
    float a=255/(max-min);
    float b=-a*min;
    for (int i=0;i<im->height*im->width;i++)
    {
        im->rawdata[i]=a*im->rawdata[i]+b;
    }
    return im;
}

complex produit(complex x, complex y){
    complex z;
    z.re = x.re*y.re + x.im*y.im;
    z.im = x.im*y.re - x.re*y.im;
    return z;
}

complex convolution(image_c imc1, image_c imc2){   //on enregistre les valeurs après la convolution dans 'apres_conv'
    complex *apresconv = malloc(imc1->height*imc1->width*sizeof(complex));
    for (int i=0;i<imc1->heigh*imc1->width){
        apresconv[i]=produit(imc1->rawdata[i], imc2->rawdata[i]);
    }
    return apresconv;
}
