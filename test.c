#include <stdio.h>
#include <stdlib.h>
#include "pngwrap.h"
#include "correlation.h"

int main(){
int n=3;
int x=10,y=3;
bwimage_t  *image = malloc(sizeof(bwimage_t));
//bwimage_t *image = E3ACreateImage();
image->rawdata=malloc(image->height*image->width*sizeof(unsigned char));
image->height=16;
image->width=16;
for (int i=0;i<image->height*image->width;i++){
    image->rawdata[i]=0;
}

data(image);
for(int i=0; i<n;i++){
  for(int j=0;j<n;j++){
    image->data[y+i][x+j]=255;
  }
}
//E3ADumpImage("../projet2/noa.png", image);
E3AFreeImage(image);

}