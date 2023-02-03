#include <stdio.h>
#include "pngwrap.h"
#include "projet.h"
#include <stdlib.h>

int cherchermax(float *data)
{
    int position;
    int n=sizeof(data)/sizeof(data[0]);
    float max=data[1];
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


void fourier(imagecomplexe  imc,  int isign)
{
unsigned long nn[2]={imc.height,imc.width};


//fourn(float data[], unsigned long nn[], n=2, int isign)

fourn( (float*)imc.rawdata, nn,  2, isign);


}