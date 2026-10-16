#pragma once
#include "Usr.hpp"
#include "Date.hpp"
#include <string>


class Photo{
  public:
    Photo() = delete;

    Photo(const std::string& title, const Date& date, const std::string& albumPath, size_t fileSize, size_t initialLikeCapacity = 16);

    Photo(const Photo& other) = delete;

    ~Photo();

    const std::string& getTitle() const {
      return title;
    }

    const std::string& getPath() const {
      return path;
    }

    bool isInLikes(const Usr* targetUsr) const;
    void toggleLike(Usr* targetUsr);
    size_t getLikeCount() const;


    Usr** getLikes() {
      return likes;
    }

    const Usr* const* getLikes() const {
      return likes;
    }

    const Date& getDate() const {
      return date;
    }

    size_t getFileSize() const {
      return fileSize;
    }

    static size_t getTotalMemoryAllocated() {
      return totalMemoryAllocated;
    }

    Photo& operator=(const Photo& other) = delete;

  private:
    std::string title;
    std::string path;

    Date date;

    size_t fileSize;

    Usr ** likes;
    size_t likeCount;
    size_t likeCapacity;

    static size_t totalMemoryAllocated;

    void removeLike(Usr* targetLike);

    void resizeLikes();
};
