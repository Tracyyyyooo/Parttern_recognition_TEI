#include <stdio.h>
#include "pngwrap.h"
#include <stdlib.h>

int cherchermax(float) *data)   //n est la taille du talbeau 
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
