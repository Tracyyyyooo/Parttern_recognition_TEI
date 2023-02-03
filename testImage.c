#include <stdio.h>
#include <stdlib.h>
#include "pngwrap.h"
#include "correlation.h"

//pour les test
bwimage_t *init(){
    bwimage_t *image = malloc(sizeof(bwimage_t));
    image->width =3;
    image->height =3;
    image->rawdata = malloc(9*sizeof(unsigned char));
    for(int i=0; i<9; i++)
        image->rawdata[i] = i+1;
    image->data=0;
    
    return image;
}

//affiche image
void affiche_im_c(image_c* imC){
    for(int i=0; i<imC->width*imC->height; i++){
        printf("%.1f +i%.1f : ", imC->rawdata[i].re, imC->rawdata[i].im);
        if((i+1)%imC->width==0)
            printf("\n");
    }
}

void affiche_im(bwimage_t* im){
    for(int i=0; i<im->width*im->height; i++){
        printf("%3d :\t", im->rawdata[i]);
        if((i+1)%im->width==0)
            printf("\n");
    }
}



int main(){
    bwimage_t *image = E3ACreateImage();
    bwimage_t *motif = E3ACreateImage();
    E3ALoadImage("../PROJET/square_8.png", image);
    E3ALoadImage("../PROJET/motif_8.png", motif);


    bwimage_t *test=init();

    affiche_im(test);


    image_c *testC=imReel2Complex(test);

    affiche_im_c(testC);


    bwimage_t *retour = imComplex2Reel(testC);
    
    affiche_im(retour);

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