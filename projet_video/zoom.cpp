#include "zoom.h"

/**
 * @brief THREAD for the reception of the pixels. It stores them in an
 * image structure. It computes the frecuency of the synchronization
 * signals.
 * 
 */
void ZOOM::reception(){
    /* Reset */
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
        /* If we received a whole image, we restart everything */
        if (count_in == image.height*image.width){
            count_in = 0;
            idx_recep = 0;
        }
        else{
            /* We read only if href_in is active and only the pixels that will be zoomed */
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
                /* We take into account the first time that href_in and vref_in were true for synchro */
                vhref_was_true = (!vhref_was_true)?true:vhref_was_true;
            }
            else
                /* we store the fact that href_in was false */
                href_was_false = (!href_was_false && vhref_was_true)?true:href_was_false;
            
            /* we store the fact that vref_in was false */
            if (vref_in == false)
                vref_was_false = (!vref_was_false && vhref_was_true)?true:vref_was_false;

            /* If href_in was true and false in that order, and then again true, 
            that means that a cycle was complete. So we store the result */
            if (href_was_false && href_in && vhref_was_true && !href_found){
                href_found = true;
                MAX_WIDTH = counter_reception;
            }

            /* If vref_in was true and false in that order, and then again true, 
            that means that a cycle was complete. So we store the result */
            if (vref_was_false && vref_in && vhref_was_true && !vref_found){
                vref_found = true;
                MAX_HEIGHT = counter_reception/MAX_WIDTH;
            }
            /* We count only if vref was not found and we received a href */
            counter_reception = (!vref_found && vhref_was_true) ? counter_reception+1:counter_reception;

        }  
    }
}

/**
 * @brief THREAD to zoom of the image and to send the pixels
 * through the outport.
 * 
 */
void ZOOM::zoom_out(){
    if (reset_n == false){
        count_h = 0;
        idx = 0;
        pixel_sent = row_sent = false;
        href_out = vref_out= false;
        pixel_out = 0;
    }
    else {
        /* We start the treatment only if the bits for the first treatment were read */
        if ( count_h > 0 || 
            count_in == image.width*image.height/4 + image.width/4){
            /* If we are treating a pixel of the image, we apply the filter
            otherwise the send nothing. We ensure that the counter always increases*/
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
                
            /* We restart everything when we finished the whole transmission of a sequence */
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