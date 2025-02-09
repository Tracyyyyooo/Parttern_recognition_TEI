#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "FOURN.C"
#include "correlation.h"

complex produit(complex x, complex y){
    complex z;
    z.re = x.re*y.re - x.im*y.im;
    z.im = x.re*y.im + x.im*y.re;
    return z;
}

void conjugue(complex* z){
    z->im= -(z->im);
}

complex reel2complex(float a){
    complex z;
    z.re = a;
    z.im=0;
    return z;
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
    im->rawdata=malloc(im->width*im->height*sizeof(unsigned char));
    float min, max;
    min=imc->rawdata[cherchermin(*imc)].re;
    max=imc->rawdata[cherchermax(*imc)].re;
    for (int i=0; i<imc->width*imc->height;i++){;
        im->rawdata[i] = (imc->rawdata[i].re - min) * 255/(max-min);
    }
    data(im);
    return im;
    
}

void data(bwimage_t *im){
    im->data=malloc(im->height*sizeof(unsigned char*));
    for(int i=0; i<im->height; i++)
        im->data[i]=malloc(im->width*sizeof(unsigned char));
    int k=0;
    for(int i=0; i<im->height; i++){
        for(int j=0; j<im->width; j++){
            im->data[i][j] = im->rawdata[k];
            k++;
        }
    }
}

int cherchermax(image_c imc){
    int position=0;
    int n=imc.width*imc.height;
    float max=imc.rawdata[0].re;
    for (int i = 0;i<n;i++)
    {
        if(imc.rawdata[i].re>max){
            max=imc.rawdata[i].re;
            position = i;
        }
        else;
    }
    return position;
}

int cherchermin(image_c imc){
    int position=0;
    int n=imc.width*imc.height;
    float min=imc.rawdata[0].re;
    for (int i = 0;i<n;i++)
    {
        if(imc.rawdata[i].re<min){
            min=imc.rawdata[i].re;
            position = i;
        }
        else;
    }
    return position;
}

int chercher_proche(image_c imc, float a){
    int position=0;
    int n=imc.width*imc.height;
    float min=a, d;
    for (int i = 0;i<n;i++)
    {
        d = imc.rawdata[i].re - a;
        if(d<0) d=-d;
        if(d < min){
            min=d;
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


image_c* correlation(image_c *imc1, image_c *imc2){ //produit de correlation
    image_c* corr = malloc(sizeof(image_c));
    corr->height = imc1->height;
    corr->width = imc1->width;
    corr->rawdata = malloc(imc1->height*imc1->width*sizeof(complex));
    for (int i=0;i<imc1->height*imc1->width; i++){
        conjugue(&imc2->rawdata[i]);
        corr->rawdata[i] = produit((complex)imc1->rawdata[i], (complex)imc2->rawdata[i]);
    }
    return corr;
}




void derive(image_c *imc){
    int H=imc->height, W=imc->width;
    float w1, w2;
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            if(i<H/2) w1 = (float)i ; else w1 = (float)(i-H);
            if(j<W/2) w2 = (float)j ; else w2 = (float)(j-W);
            iwZ((complex*)&imc->rawdata[i*W+j], w1, w2);
        }
    }
}

void iwZ(complex *z, float w1, float w2){
    float temp=z->re;
    float sigma=10; //on multuplie par une gaussienne pour le flou
    z->re = -z->im * (w1+w2) * exp(-(w1*w1+w2*w2)/(2*sigma*sigma));
    z->im = temp * (w1+w2) * exp(-(w1*w1+w2*w2)/(2*sigma*sigma));
}






//pour les test et génerer les images

//affiche images pour les test
void affiche_imc(image_c* imC){
    printf("\n");
    for(int i=0; i<imC->width*imC->height; i++){
        printf("%.1f +i%.1f : ", imC->rawdata[i].re, imC->rawdata[i].im);
        if((i+1)%imC->width==0)
            printf("\n");
    }
    printf("\n");
}

void affiche_im(bwimage_t* im){
    for(int i=0; i<im->width*im->height; i++){
        printf("%3d :\t", im->rawdata[i]);
        if((i+1)%im->width==0)
            printf("\n");
    }
    printf("\n");
}

void affiche_data(bwimage_t *im){
    for(int i=0; i<im->height; i++){
        for(int j=0; j<im->width; j++)
            printf("%3d :\t", im->data[i][j]);
        printf("\n;");
    }
    printf("\n");
}


//crée une image de pixels noir ou aléatoires
void create_im(int size, char* adresse, int color){
    bwimage_t  *image = malloc(sizeof(bwimage_t));
    //image = E3ACreateImage();
    image->height=size;
    image->width=size;
    image->rawdata=malloc(image->height*image->width*sizeof(unsigned char));
    for (int i=0;i<image->height*image->width;i++){
        if(color)
            image->rawdata[i]=rand()%255;
        else
            image->rawdata[i]=0;
    }
    data(image);
    E3ADumpImage(adresse, image);
    E3AFreeImage(image);
}

void add_square(bwimage_t* image, int x, int y, int n, int color, char* adresse){
    for(int i=0; i<n;i++){
        for(int j=0;j<n;j++){
            image->rawdata[(y+i)*image->width + x+j] = color;
        }
    }
    data(image);
    E3ADumpImage(adresse, image);
}


void *motif(bwimage_t *im){
    bwimage_t *motif = malloc(sizeof(bwimage_t));
    int H=im->height, W=im->width ,i2, j2;
    motif->height = H;
    motif->width = W;
    motif->rawdata=malloc(H*W*sizeof(unsigned char));
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            if(i<H/2) i2 = i+(H/2) ; else i2 = i-(H/2);
            if(j<W/2) j2 = j+(W/2) ; else j2 = j-(W/2);
            motif->rawdata[i*W+j] = im->rawdata[i2*W+j2];
        }
    }
    data(motif);
    *im=*motif;
}