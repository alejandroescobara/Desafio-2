#pragma once
#include "Album.hpp"
#include <string>

//size_t Album::totalMemoryAllocated = 0;

Album::Album(const std::string& title , const std::string& path ,  char visibility)
    :title(title),
    path(path),
    visibility(visibility),
    photos(nullptr),
    photoCount(0){}

Album::~Album(){
    if(photoCount != 0){
        for(short i = 0; i < photoCount; i++){
            delete photos[i];
        }
    }
    delete[]photos;
}

const Photo* const* Album::getPhotos(){
    return photos;
}
/*
Photo * getTargetPhoto(const std::string& targetTitle){ //no creo que lo usemos

}
*/
short Album::getPhotoCount(){
    return photoCount;
}

const std::string& Album::getTitle(){
    return title;
}

char Album::getVisibility(){
    return visibility;
}

const std::string& Album::getPath(){
    return path;
}
size_t Album::getMemory(){
    return 8*(size_t(photoCount))+sizeof(*this); //cada foto en el album es un ptr que pesa 8 bytes
}







