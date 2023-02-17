//imComplex2Reel (et normalise entre 0 et 255)
bwimage_t* imComplex2Reel(image_c *imc)
{
    bwimage_t  *im = malloc(sizeof(bwimage_t));
    im->width = imc->width;
    im->height = imc->height;
    im->rawdata=malloc(im->width*im->height*sizeof(unsigned long));
    float max=imc->rawdata[cherchermax(*imc)].re;
    float min=imc->rawdata[cherchermin(*imc)].re;
    int j=0, k=0;
    for (int i=0; i<imc->width*imc->height;i++){;
        im->(rawdata[i]=imc->rawdata[i].re-min)/(max-min)*255;
    }
    /*
    //on normalise les valeurs entre 0 et 255
    float max=im->rawdata[cherchermax(*im)];
    float min=im->rawdata[cherchermin(*im)];
    float a=255/(max-min);
    for (int i=0;i<im->height*im->width;i++)
    {
        im->rawdata[i]=a*(im->rawdata[i]-min);
    }*/
    data(im);
    return im;
    
}


int cherchermax(image_c *imc){
    int position=0;
    int n=imc->width*imc->height;
    float max=imc->rawdata[0].re;
    for (int i = 0;i<n;i++)
    {
            if(imc->rawdata[i].re>max){
                max=im->rawdata[i].re;
                position = i;
            }
            else;
        }
        return position;
}

int cherchermin(image_c *imc){
    int position=0;
    int n=imc->width*imc->height;
    float min=imc->rawdata[0].re;
    for (int i = 0;i<n;i++)
    {
            if(imc->rawdata[i].re<min){
                min=imc->rawdata[i].re;
                position = i;
            }
            else;
        }
        return position;
}
