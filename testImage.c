#include <stdio.h>
#include <stdlib.h>
#include "pngwrap.h"
#include "correlation.h"

//pour les test
bwimage_t *init(){
    bwimage_t *image = malloc(sizeof(bwimage_t));
    image->width =4;
    image->height =4;
    image->rawdata = malloc(image->height*image->width*sizeof(unsigned char));
    for(int i=0; i<image->height*image->width; i++)
        image->rawdata[i] = i<=8? 1 : 0;
    image->data=0;
    return image;
}



//affiche images pour les test
void affiche_im_c(image_c* imC){
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

void create_im(int x, int y, int n){
    bwimage_t  *image = malloc(sizeof(bwimage_t));
    //bwimage_t *image = E3ACreateImage();
    image->height=8;
    image->width=8;
    image->rawdata=malloc(image->height*image->width*sizeof(unsigned long));
    for (int i=0;i<image->height*image->width;i++){
        image->rawdata[i]=0;
    }
    for(int i=0; i<n;i++){
        for(int j=0;j<n;j++){
            image->rawdata[(y+i)*image->width + x+j] = 255;
        }
    }
    data(image);
    affiche_im(image);
    E3ADumpImage("../PROJET/noa.png", image);
    E3AFreeImage(image);
}


int main(){
    create_im(1, 5, 2);

    bwimage_t *image = E3ACreateImage();
    bwimage_t *motif = E3ACreateImage();
    E3ALoadImage("../PROJET/noa.png", image);
    E3ALoadImage("../PROJET/motif_8.png", motif);

    /*
    image_c *imageC = imReel2Complex(image);
    fourier(imageC, 1);
    derive(imageC);
    fourier(imageC, -1);
    bwimage_t *retour = imComplex2Reel(imageC);
    

    affiche_im(retour);
    E3ADumpImage("../PROJET/retour.png", retour);
    */

    image_c* imC = imReel2Complex(image);
    image_c* motifC = imReel2Complex(motif);
    correlation(imC, motifC);
    bwimage_t *retour = imComplex2Reel(imC);
    affiche_im(retour);


    E3AFreeImage(image);
    E3AFreeImage(motif);
    E3AFreeImage(retour);

    /*
    image_c* imC = imReel2Complex(image);
    image_c* motifC = imReel2Complex(motif);
    */

    /*
    affiche_im_c(imC);
    printf("\n");
    affiche_im_c(motifC);
    */
    /*fourier(testC, 1);
    fourier(testC, -1);*/



    
}