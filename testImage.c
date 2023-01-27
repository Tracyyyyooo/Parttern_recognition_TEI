#include <stdio.h>
#include "complex.h"
#include "pngwrap.h"
#include <stdlib.h>

bwimage_t *init(){
    bwimage_t *image = malloc(sizeof(bwimage_t));
    image->width =3;
    image->height =3;
    image->rawdata = malloc(9*sizeof(unsigned char));
    for(int i=0; i<9; i++)
        image->rawdata[i] = i;
    image->data=0;
    
    return image;
}

//affiche image comlpexe
void affiche_im_c(image_c* imC){
    for(int i=0; i<imC->width*imC->height; i++){
        printf("%.1f +i%.1f ; ", imC->rawdata[i].re, imC->rawdata[i].im);
        if((i+1)%imC->width==0)
            printf("\n");
    }
}



int main(){
    bwimage_t *image=init();
    /*for(int i=0; i<9; i++)
        printf("%f ", (float)image->rawdata[i]);
    printf(" \n");*/

    image_c* imC = imReel2Complex(image);

    affiche_im_c(imC);
    
}