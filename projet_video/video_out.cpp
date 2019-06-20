#include "video_out.h"
#include <sstream>
#include <cstdio>

void VIDEO_OUT::read_pixels(){
    if (reset_n == false){
        for (int i=0; i<counter;i++)
            image.pixel[i]=0;
        counter = 0;
        nb_images = 0;
    }
    else{
        if (counter == image.height*image.width){
            counter = 0;
            print_image(image);
            nb_images++;
        }
        else{
            if (href.read()==true){
                image.pixel[counter] = pixel_in;
                counter++;
            }
        }  
    }
}

void VIDEO_OUT::print_image(Image image){
    std::ostringstream file_name;
    file_name<<this->name()<<nb_images<<".png";
    image_write(&image,file_name.str().c_str());
}