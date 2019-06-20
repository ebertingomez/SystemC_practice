#include "mean.h"

#define MAX_WIDTH 874
#define MAX_HEIGHT 576

void MEAN::filter_in(){
    if (reset_n == false){
        for (int i=0; i<count_in;i++)
            image.pixel[i]=0;
        count_in = 0;
    }
    else{
        if (count_in == image.height*image.width){
            count_in = 0;
        }
        else{
            if (href_in == true){
                image.pixel[count_in] = pixel_in;
                count_in++;
            }
        }  
    }
}

void MEAN::filter_out(){
    if (reset_n == false){
        count_fltr = count_h = 0;
        href_out = false;
        vref_out = false;
        pixel_out = 0;
    }
    else {
        if ( count_h > 0 || (count_in == image.width + 1)){
            if ( count_h % (MAX_WIDTH) < image.width ){
                sum = 0;
                n   = 0;
                for (int i=-1 ; i<2 ; i++){
                    if (count_fltr + i*image.width < 0 || 
                        count_fltr + i*image.width >= image.width*image.height)
                        continue;
                    for (int j=-1 ; j<2 ; j++){
                        idx = count_fltr + i*image.width + j;
                        if (count_fltr%image.width +i < 0 ||
                            count_fltr%image.width +i >= image.width || 
                            idx != count_fltr)
                            continue;
                        sum += image.pixel[idx];
                        n   += 1;
                    }
                }
                pixel_out = (int)(sum/n);
                href_out  = true;
                count_fltr++;
            }
            else{
                href_out = false;
                pixel_out = 0;
            }
                
            vref_out = ( (int)count_h/MAX_WIDTH < 3) ? 1 : 0;
            count_fltr = (count_h+1<MAX_WIDTH*MAX_HEIGHT)? count_fltr : 0;
            count_h = (count_h+1<MAX_WIDTH*MAX_HEIGHT)? count_h+1 : 0;
        }
        else{
            href_out = false;
            pixel_out = 0;
        }
    }
}