#include <stdio.h>
#include <stdlib.h>
#include "FOURN.C"
#include "correlation.h"

complex produit(complex x, complex y){
    complex z;
    z.re = x.re*y.re + x.im*y.im;
    z.im = x.re*y.im - x.im*y.re;
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


int power(int x, unsigned int n){
    return n==1? 1 : x*power(x, n-=1);
}

//verifie que le tableau est de taille 2 puissance n, renvoie la puissance de 2 supérieur ou égale
unsigned int* verif_taille(bwimage_t image){
    unsigned int* n = malloc(2*sizeof(unsigned int));
    n[0]=1; n[1]=1;
    while (power(2, n[0]) < image.width){
        n[0]++;
    }
    while (power(2, n[1]) < image.height){
        n[1]++;
    }
    n[0]=power(2, n[0]);
    n[1]=power(2, n[1]);
    return n;
}

//revoie l'image complexe agrandit pour une taille puissance de 2
image_c* imReel2Complex(bwimage_t *image){
    image_c* imC = malloc(sizeof(image_c));
    int* n = verif_taille(*image);
    imC->width=n[0];
    imC->height=n[1];
    imC->rawdata=malloc(n[0]*n[1]*sizeof(complex));
    for(int i=0; i<n[1]; i++){
        for (int j=0; j<n[0]; j++){
            if(j<image->width && i<image->height)
                imC->rawdata[i*n[1]+j]=reel2complex((float)image->rawdata[i*image->height+j]);
            else
                imC->rawdata[i*n[1]+j]=reel2complex(0);
        }
    }
    return imC;
}

//imComplex2Reel (et normalise entre 0 et 255)
bwimage_t* imComplex2Reel(image_c *imc)
{
    bwimage_t  *im = malloc(sizeof(bwimage_t));
    im->width = imc->width;
    im->height = imc->height;
    im->rawdata=malloc(im->width*im->height*sizeof(unsigned long));
    int j=0, k=0;
    for (int i=0; i<imc->width*imc->height;i++){;
        im->rawdata[i]=complex2reel(imc->rawdata[i])/(im->height*im->width);
    }
    //on normalise les valeurs entre 0 et 255
    float max=im->rawdata[cherchermax(*im)];
    float min=im->rawdata[cherchermin(*im)];
    float a=255/(max-min);
    for (int i=0;i<im->height*im->width;i++)
    {
        im->rawdata[i]=a*(im->rawdata[i]-min);
    }
    data(im);
    return im;
    
}

void data(bwimage_t *im){
    im->data=malloc(im->height*sizeof(unsigned long*));
    for(int i=0; i<im->height; i++)
        im->data[i]=malloc(im->width*sizeof(unsigned long));
    int k=0;
    for(int i=0; i<im->height; i++){
        for(int j=0; j<im->width; j++){
            im->data[i][j] = im->rawdata[k];
            k++;
        }
    }
}






int cherchermax(bwimage_t im){
    int position=0;
    int n=im.width*im.height;
    float max=im.rawdata[0];
    for (int i = 0;i<n;i++)
    {
            if(im.rawdata[i]>max){
                max=im.rawdata[i];
                position = i;
            }
            else;
        }
        return position;
}

int cherchermin(bwimage_t im){
    int position=0;
    int n=im.width*im.height;
    float min=im.rawdata[0];
    for (int i = 0;i<n;i++)
    {
            if(im.rawdata[i]<min){
                min=im.rawdata[i];
                position = i;
            }
            else;
        }
        return position;
}





void fourier(image_c* imc,  int isign){
    unsigned long nn[2]={imc->height,imc->width};
    fourn( (float*)imc->rawdata, nn,  2, isign);
}


void correlation(image_c *imc1, image_c *imc2){   //on enregistre les valeurs après la convolution dans 'imc1'
    for (int i=0;i<imc1->height*imc1->width; i++){
        conjugue(&imc2->rawdata[i]);
        imc1->rawdata[i] = produit((complex)imc1->rawdata[i], (complex)imc2->rawdata[i]);
    }
}


/*
//on normalise les valeurs entre 0 et 255
    int max=(int)imc->rawdata[cherchermax( (float*)imc->rawdata)];
    int min=(int)imc->rawdata[cherchermin( (float*)imc->rawdata)];
    float a=255/(max-min);
    float b=-a*min;
    for (int i=0;i<imc->height*imc->width;i++)
    {
        imc->rawdata[i]=a*(float)imc->rawdata[i]+b;
*/