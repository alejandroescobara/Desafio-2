#pragma once
#include "Album.hpp"
#include <string>

size_t Album::totalMemoryAllocated = 0;

Album::Album(const std::string& title ,const std::string& ownerUsrname, char visibility, size_t initialPhotoCapacity)
     :title(title),
      path("/users/systemData/"+ownerUsrname+"/albums/"+title),
      visibility(visibility),
      photos(nullptr),
      photoCount(0),
      photoCapacity(initialPhotoCapacity) {
//---------

  try {
    photos = new Photo*[initialPhotoCapacity]; 
  } catch (const std::bad_alloc&) {
    delete[] photos;
    throw;
  }

  for (size_t i = 0; i < photoCapacity; ++i) photos[i] = nullptr;

  totalMemoryAllocated += sizeof(Album)+(photoCapacity * sizeof(Photo*));
}

Album::~Album() {
  if(photoCount != 0){
    for(size_t i = 0; i < photoCount; i++){
      delete photos[i];
      photos[i] = nullptr;
    }
  }
  delete[] photos;
  photos = nullptr;

  totalMemoryAllocated -= sizeof(Album)+(photoCapacity * sizeof(Photo*));
}

const Photo* const* Album::getPhotos() const {
    return photos;
}

void Album::resizePhotos() {
  size_t newCapacity = photoCapacity * 2;

  Photo** auxPhotos = nullptr;

  try {
    auxPhotos = new Photo*[newCapacity]; 
  } catch (const std::bad_alloc&) {
    delete[] auxPhotos;
    throw;
  }

  for (size_t i = 0; i < photoCount; ++i)           auxPhotos[i] = photos[i];
  for (size_t i = photoCount; i < newCapacity; ++i) auxPhotos[i] = nullptr;

  delete[] photos;
  photos = auxPhotos;

  totalMemoryAllocated += ((newCapacity - photoCapacity)* sizeof(Photo*));
  photoCapacity = newCapacity;
}

size_t Album::getPhotoCount() const {
    return photoCount;
}

const std::string& Album::getTitle() const {
    return title;
}

char Album::getVisibility() const {
    return visibility;
}

const std::string& Album::getPath() const {
    return path;
}

Album& Album::operator+=(Photo* newPhoto) {
  if (photoCount >= photoCapacity) {
    resizePhotos();
  }
  photos[photoCount++] = newPhoto;
  return *this;
}

size_t Album::getTotalMemoryAllocated() const {
    return totalMemoryAllocated;
}
