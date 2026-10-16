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

    void setTitle(const std::string& title);
    const std::string& getTitle() const;

    void setPath(const std::string& path);
    const std::string& getPath() const;

    bool isInLikes(const Usr* targetUsr) const;
    void toggleLike(Usr* targetUsr);
    size_t getLikeCount() const;
    const Usr* const* getLikes() const;

    void setDate(const Date& date);
    const Date& getDate() const;

    void setFileSize(size_t fileSize);
    size_t getFileSize() const;

    size_t getTotalMemoryAllocated() const;

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
