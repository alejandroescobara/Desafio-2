#include "Photo.hpp"
#include "Date.hpp"
#include <string>


Photo::Photo(const std::string& title, const std::string& path, const Date& date, size_t fileSize)
    :title(title),path(path),date(date),fileSize(fileSize){}

Photo::~Photo(){
    delete[]likes;
};

void Photo::setTitle(const std::string& title){
    this->title = title;
}

const std::string& Photo::getTitle()const{
    return title;
}

void Photo::setPath(const std::string& path){
    this->path = path;
}

const std::string& Photo::getPath()const{
    return path;
}

bool Photo::isInLikes(const Usr& refUsrname) const{
    bool isIn = false;
    Usr *  ptrUsrLike;
    for(size_t i = 0; i < likeCount; i++){
       ptrUsrLike = likes[i];
        if (ptrUsrLike == &refUsrname){
            isIn = true;
        }
    }
    return isIn;
}

void Photo::toggleLike(Usr& refUsrname){//aqui hay que ver bien cual es el parametro // ok ya listo

    bool Ilike = Photo::isInLikes(refUsrname);
    Usr *  ptrUsrLike;
    Usr ** allLikes;
    if (Ilike){
        allLikes = new Usr*[likeCount-1];
        for(size_t i = 0; i < likeCount; i++){
            ptrUsrLike = likes[i];
            if(ptrUsrLike == &refUsrname){
                //aqui va el borrado y redimencionamiento de los likes
                for(size_t j = 0; j<i;j++){
                    allLikes[j] = likes[j];
                }
                for(size_t j = i; j<likeCount-1;j++){
                    allLikes[j] = likes[j+1];
                }
                break;
            }
        }
        likeCount--;
    }
    else{
        allLikes = new Usr*[likeCount+1];
        for(size_t j = 0; j<likeCount;j++){
            allLikes[j] = likes[j];
        }
        allLikes[likeCount] = &refUsrname;
        likeCount++;
    }
    delete[] likes;
    likes = allLikes;

}
/*
size_t Photo::getLikeCount() const{

}
*/

void Photo::setDate(const Date& date){
    this->date = date;
}

const Date& Photo::getDate()const{
    return date;
}

void Photo::setFileSize(size_t fileSize){
    this->fileSize = fileSize;
}

size_t Photo::getFileSize() const{
    return fileSize;
}

size_t Photo::getMemoryUsage() const{ //pensar bien como sacar el calculo de la memoria usada

    return 8*likeCount + sizeof(*this);// cada like son un puntero que ocupa 8 bytes mas el ptr del arreglo principal

}












