#include "mean.h"
#include <math.h>
/**
 * @brief THREAD for the reception of the pixels. It stores them in an
 * image structure.
 * 
 */
void MEAN::reception(){
    /* Reset */
    if (reset_n == false){
        for (int i=0; i<count_in;i++)
            image.pixel[i]=0;
        count_in = 0;

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
        }
        else{
            /* We read only if href_in is active and only the pixels that will be zoomed */
            if (href_in == true){
                image.pixel[count_in] = pixel_in;
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
 * @brief THREAD to do the treatment of the image and to send the pixels
 * through the outport.
 * 
 */
void MEAN::filter_out(){
    if (reset_n == false){
        count_fltr = count_h = 0;
        href_out = vref_out = false;
        pixel_out = 0;
    }
    else {
        /* We start the treatment only if the bits for the first treatment were read */
        if ( count_h > 0 || (count_in == image.width + 1)){
            /* If we are treating a pixel of the image, we apply the filter
            otherwise the send nothing. We ensure that the counter always increases*/
            if (    count_h % (MAX_WIDTH) < image.width &&
                    count_h < image.height*MAX_WIDTH){
                
                switch (filter)
                {
                case AVG:
                    pixel_out = compute_mean(count_fltr);
                    break;
                case GAUSS:
                    pixel_out = compute_gauss(count_fltr);
                    break;
                case SOBEL:
                    pixel_out = compute_sobel(count_fltr);
                    break;
                default:
                    pixel_out = image.pixel[count_fltr];
                }
                
                href_out  = true;
                count_fltr++;
            }
            else{
                href_out = false;
                pixel_out = 0;
            }
            /* We restart everything when we finished the whole transmission of a sequence */
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
/**
 * @brief This function applies a softening function of a 3x3 matrix by
 * taking the mean over this points.
 * 
 * @param position 
 * @return int 
 */
int MEAN::compute_mean(int position){
    int sum = 0;
    int n   = 0;
    int idx;
    for (int i=-1 ; i<2 ; i++){
        if (position + i*image.width < 0 || 
            position + i*image.width >= image.width*image.height)
            continue;
        for (int j=-1 ; j<2 ; j++){
            idx = position + i*image.width + j;
            if (position%image.width + i < 0 ||
                position%image.width + i >= image.width || 
                idx == position)
                continue;
            sum += image.pixel[idx];
            n   += 1;
        }
    }
    return sum/n;
}

/**
 * @brief This function applies a gaussian softening filter to a 3x3 matrix
 * in function of a convolutional kernel.
 * 
 */
const int static conv_kern[] = {1,2,1,2,4,2,1,2,1};
int MEAN::compute_gauss(int position){
    int sum = 0;
    int n   = 0;
    int idx;
    for (int i=-1 ; i<2 ; i++){
        if (position + i*image.width < 0 || 
            position + i*image.width >= image.width*image.height)
            continue;
        for (int j=-1 ; j<2 ; j++){
            idx = position + i*image.width + j;
            if (position%image.width + i < 0 ||
                position%image.width + i >= image.width)
                continue;
            sum += image.pixel[idx] * conv_kern[4+ i*3 + j];
            n   += conv_kern[4+ i*3 + j];
        }
    }
    return sum/n;
}

/**
 * @brief This function applies a sobel filtering to a 3x3 matrix given two 
 * convolutional kernel mat_gx and mat_gy. It gives the simplified norm of Gx and Gy
 * 
 */
const int static mat_gx[] = {1,0,-1,2,0,-2,1,0,-1};
const int static mat_gy[] = {1,2,1,0,0,0,-1,-2,-1};
int MEAN::compute_sobel(int position){
    int idx, idx2;
    int gx = 0;
    int gy = 0;
    for (int i=-1 ; i<2 ; i++){
        if (position + i*image.width < 0 || 
            position + i*image.width >= image.width*image.height)
            continue;
        for (int j=-1 ; j<2 ; j++){
            idx = position + i*image.width + j;
            idx2 = 4+ i*3 + j;
            if (position%image.width + i < 0 ||
                position%image.width + i >= image.width)
                continue;
            gx += image.pixel[idx] * mat_gx[idx2];
            gy += image.pixel[idx] * mat_gy[idx2];
        }
    }
    return abs(gx) + abs(gy);
    //return sqrt(pow(gx,2) + pow(gy,2));
}