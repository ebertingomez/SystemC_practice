#include "zoom.h"

#define MAX_WIDTH 874
#define MAX_HEIGHT 576

void ZOOM::reception(){
    if (reset_n == false){
        for (int i=0; i<idx_recep;i++)
            image.pixel[i]=0;
        count_in = 0;
        idx_recep = 0;
    }
    else{
        if (count_in == image.height*image.width){
            count_in = 0;
            idx_recep = 0;
        }
        else{
            if (href_in == true){
                if (    count_in%image.width >= image.width/4 &&
                        count_in%image.width < image.width*3/4 &&
                        count_in/image.width >= image.height/4 &&
                        count_in/image.width < image.height*3/4)
                {
                    image.pixel[idx_recep] = pixel_in;
                    idx_recep++;
                }
                count_in++;
            }
        }  
    }
}

void ZOOM::zoom_out(){
    if (reset_n == false){
        count_h = 0;
        idx = 0;
        pixel_sent = row_sent = false;
        href_out = vref_out= false;
        pixel_out = 0;
    }
    else {
        if ( count_h > 0 || 
            count_in == image.width*image.height/4 + image.width/4){
            if ( count_h % (MAX_WIDTH) < image.width ){
                pixel_out = image.pixel[idx];
                if (pixel_sent)
                    idx++;
                pixel_sent = !pixel_sent;

                if (idx%(image.width/2+1) >= image.width/2 &&  !pixel_sent){
                    if (!row_sent)
                        idx = idx-image.width/2;
                        
                    row_sent = !row_sent;
                }

                href_out  = true;
            }
            else{
                href_out = false;
                pixel_out = 0;
            }
                
            vref_out = ( (int)count_h/MAX_WIDTH < 3) ? 1 : 0;
            idx = (count_h+1<MAX_WIDTH*MAX_HEIGHT) ? idx : 0;
            count_h = (count_h+1<MAX_WIDTH*MAX_HEIGHT)? count_h+1 : 0;
        }
        else{
            href_out = false;
            pixel_out = 0;
        }
    }
}