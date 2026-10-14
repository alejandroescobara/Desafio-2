#pragma once
#include "Photo.hpp"
#include <string>

class Album{
public:

    Album(const std::string& title , const std::string& path ,  char visibility = 'P');
    ~Album();

    const Photo* const* getPhotos();
    Photo * getTargetPhoto(const std::string& targetTitle);
    short getPhotoCount();

    const std::string& getTitle();
    char getVisibility();
    const std::string& getPath();

    size_t getMemory();
    //Album& operator+=(Photo* Photo); debido a que como usr no añadimos mas fotos de esto se encarga el sistema

private:
    std::string title;
    std::string path;

    char visibility;

    Photo ** photos;
    short photoCount;
    //size_t photoCapacity; por el momento no lo veo necesario
    //static size_t totalMemoryAllocated;

    //void resizePhotos();//posiblemente este no se use, pues no hay que añadir fotos

};