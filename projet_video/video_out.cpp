#include "video_out.h"
#include <sstream>
#include <cstdio>

/**
 * @brief This function read a whole image pixel per pixel and stores them in 
 *        a image structure.
 * 
 */
void VIDEO_OUT::read_pixels(){
    if (reset_n == false){
        for (int i=0; i<counter;i++)
            image.pixel[i]=0;
        counter = 0;
        nb_images = 0;
    }
    else{
        /* We print the image and restart the counter when we received a whole image */
        if (counter == image.height*image.width){
            counter = 0;
            print_image(image);
            nb_images++;
        }
        else{
            /* We read only if href is active */
            if (href.read()==true){
                image.pixel[counter] = pixel_in;
                counter++;
            }
        }  
    }
}

/**
 * @brief Stores the image structure in a png file with the name of the module 
 *          as the name of the file
 * 
 * @param image 
 */
void VIDEO_OUT::print_image(Image image){
    std::ostringstream file_name;
    file_name<<this->name()<<nb_images<<".png";
    image_write(&image,file_name.str().c_str());
}