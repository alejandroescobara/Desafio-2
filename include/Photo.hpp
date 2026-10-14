#pragma once
#include "Usr.hpp"
#include "Date.hpp"
#include <string>


class Photo{
public:
        Photo();
        Photo(const std::string& title, const std::string& path,
              const Date& date, size_t fileSize = 0);
        Photo(const Photo& other);
        ~Photo();

        void setTitle(const std::string& title);
        const std::string& getTitle() const;

        void setPath(const std::string& path);
        const std::string& getPath() const;

        bool isInLikes(const Usr& refUsrname) const;
        void toggleLike(Usr& refUsrname);//aqui hay que ver bien cual es el parametro
        size_t getLikeCount() const;


        void setDate(const Date& date);
        const Date& getDate() const;

        void setFileSize(size_t fileSize);
        size_t getFileSize() const;

        size_t getMemoryUsage() const;

        Photo& operator=(const Photo& other);
private:
    std::string title;
    std::string path;

    Usr ** likes;
    size_t likeCount;
    size_t likeCapacity;
    Date date;

    size_t fileSize;

    void resizeLikes();// al final este lo inclui dentro de toggle like
};