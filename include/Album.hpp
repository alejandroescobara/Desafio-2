#pragma once
#include "Photo.hpp"
#include <string>

class Album{
  public:
    
    Album(const std::string& title, const std::string& ownerUsrname, char visibility = 'P', size_t initialPhotoCapacity = 8);
    
    ~Album();

    const Photo* const* getPhotos() const;

    size_t getPhotoCount() const;

    const std::string& getTitle() const;

    char getVisibility() const;

    const std::string& getPath() const;

    size_t getTotalMemoryAllocated() const;

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
