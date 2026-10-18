#include "Photo.hpp"
#include "Date.hpp"
#include "core.hpp"

#include <string>
#include <stdexcept>

size_t Photo::totalMemoryAllocated = 0;

Photo::Photo(const std::string& title, const Date& date, const std::string& albumPath, size_t fileSize, size_t initialLikeCapacity)
    :title(title),
    path(albumPath+"/"+title),
    date(date),
    fileSize(fileSize),
    likes(nullptr),
    likeCount(0),
    likeCapacity(initialLikeCapacity) {

  try {
    likes = new Usr*[initialLikeCapacity]; 
  } catch (const std::bad_alloc&) {
    delete[] likes;
    throw;
  }

  for (size_t i = 0; i < likeCapacity; ++i){ likes[i] = nullptr;core::countIteration();}

  totalMemoryAllocated += sizeof(Photo)+(likeCapacity * sizeof(Usr*));
}

Photo::~Photo(){
    delete[] likes;
    totalMemoryAllocated -= sizeof(Photo)+(likeCapacity * sizeof(Usr*));
};

bool Photo::isInLikes(const Usr* targetUsr) const{
  for(size_t i = 0; i < likeCount; i++){
    core::countIteration();
    if (likes[i] == targetUsr) {
      return true;
    }
  }
  return false;
}

void Photo::resizeLikes() {
  size_t newCapacity = likeCapacity * 2;

  Usr** auxLikes = nullptr;

  try {
    auxLikes = new Usr*[newCapacity]; 
  } catch (const std::bad_alloc&) {
    delete[] auxLikes;
    throw;
  }

  for (size_t i = 0; i < likeCount; ++i){           auxLikes[i] = likes[i];core::countIteration();}
  for (size_t i = likeCount; i < newCapacity; ++i){ auxLikes[i] = nullptr;core::countIteration();}

  delete[] likes;
  likes = auxLikes;

  totalMemoryAllocated += ((newCapacity - likeCapacity)* sizeof(Usr*));
  likeCapacity = newCapacity;
}

void Photo::removeLike(Usr* targetLike) {
  if (targetLike == nullptr || likes == nullptr || likeCount == 0) {
    return;
  }

  for (size_t i = 0; i < likeCount; ++i) {
    core::countIteration();
    if (likes[i] == targetLike) {
      for (size_t j = i; j < likeCount - 1; ++j) {
        core::countIteration();
        likes[j] = likes[j + 1];
      }
      likes[likeCount - 1] = nullptr;
      --likeCount;
      return;
    }
  }
}

void Photo::toggleLike(Usr* targetUsr){
  if (isInLikes(targetUsr)) {
    removeLike(targetUsr);    
  }
  else {
    if (likeCount >= likeCapacity) {
      resizeLikes();
    }
    likes[likeCount++] = targetUsr;
  }
}

size_t Photo::getLikeCount() const {
  return likeCount;
}
