#include "zoom.h"


void ZOOM::reception(){
    if (reset_n == false){
        for (int i=0; i<idx_recep;i++)
            image.pixel[i]=0;
        count_in = 0;
        idx_recep = 0;

        MAX_WIDTH = 10000000;
        MAX_HEIGHT = 10000000;
        counter_reception = 0;
        href_was_false = vhref_was_true = href_found = false;
        vref_was_false = vref_found = false;
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
                vhref_was_true = (!vhref_was_true)?true:vhref_was_true;
            }
            else
                href_was_false = (!href_was_false && vhref_was_true)?true:href_was_false;

            if (vref_in == false)
                vref_was_false = (!vref_was_false && vhref_was_true)?true:vref_was_false;

            if (href_was_false && href_in && vhref_was_true && !href_found){
                href_found = true;
                MAX_WIDTH = counter_reception;
            }

            if (vref_was_false && vref_in && vhref_was_true && !vref_found){
                vref_found = true;
                MAX_HEIGHT = counter_reception/MAX_WIDTH;
            }
            counter_reception = (!vref_found && vhref_was_true) ? counter_reception+1:counter_reception;

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
            if (    count_h % (MAX_WIDTH) < image.width && 
                    count_h < image.height*MAX_WIDTH){
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