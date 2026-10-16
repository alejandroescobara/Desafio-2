#pragma once
#include "Photo.hpp"
#include <string>

class Album{
  public:
    
    Album(const std::string& title, const std::string& ownerUsrname, char visibility = 'P', size_t initialPhotoCapacity = 8);
    
    ~Album();

    Photo** getPhotos() {
      return photos;
    }

    const Photo* const* getPhotos() const {
      return photos;
    }

    size_t getPhotoCount() const {
      return photoCount;
    }

    const std::string& getTitle() const {
      return title;
    }

    char getVisibility() const {
      return visibility;
    }

    const std::string& getPath() const {
      return path;
    }

    static size_t getTotalMemoryAllocated() {
      return totalMemoryAllocated;
    }

    Album& operator+=(Photo* newPhotoo);

private:
    std::string title;
    std::string path;

    char visibility;

    Photo ** photos;
    size_t photoCount;
    size_t photoCapacity;
    
    static size_t totalMemoryAllocated;

    void resizePhotos();
};
