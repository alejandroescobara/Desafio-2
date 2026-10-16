#pragma once

#include <string>
#include <cstddef>

#include "Date.hpp"
#include "dataManager.hpp"

class Chat;

class Album;

class Photo;

class Usr {
  public:
    Usr() = delete;
    Usr(const Usr& other) = delete;

    Usr(const std::string& usrname,
        const std::string& email,
        const std::string& pwd,
        const std::string& city,
        const std::string& country,
        const Date& dob,
        const Date& joinDate = Date::now(),
        size_t initialFriendCapacity = 16,
        size_t initialRequestCapacity = 4,
        size_t initialChatCapacity = 8,
        size_t initialAlbumCapacity = 4);

    ~Usr();

    const std::string& getUsrname() const {
      return usrname;
    }

    const std::string& getPfpPath() const {
      return pfpPath;
    }

    const std::string& getEmail() const {
      return email;
    }

    bool checkPwd(const std::string& inputPwd) const;

    const std::string& getCity() const {
      return city;
    }

    const std::string& getCountry() const {
      return country;
    }

    const Date& getDob() const {
      return dob;
    }
    
    const Date& getJoinDate() const {
      return joinDate;
    }

    Usr** getFriends() {
      return friends;
    }

    const Usr* const* getFriends() const {
      return friends;
    }

    size_t getFriendCount() const {
      return friendCount;
    }

    void addFriend(Usr* newFriend);

    bool isFriend(const Usr* targetUsr) const; 

    Chat** getChats() {
      return chats;
    }

    const Chat* const* getChats() const {
      return chats;
    }

    size_t getChatCount() const {
      return chatCount;
    }

    void addChat(Chat* newChat);

    Usr** getRequests() {
      return requests;
    }

    const Usr* const* getRequests() const {
      return requests;
    }

    size_t getRequestCount() const {
      return requestCount;
    }

    void addRequest(Usr* newRequest);

    void processRequest(Usr* targetRequest, bool accept);
    void removeRequest(Usr* targetRequest);

    Album** getAlbums() {
      return albums;
    }

    const Album* const* getAlbums() const {
      return albums;
    }

    size_t getAlbumCount() const {
      return albumCount;
    }

    void addAlbum(Album* newAlbum);

    size_t countCommonFriends(const Usr* otherUsr) const; //NOTE: printRandFriend->udeaBook

    bool hasPendingRequest(const Usr* targetUsr) const;

    void toggleLike(Photo* targetPhoto);

    Usr& operator=(const Usr& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, const Usr& usr); //<- printProfile
                                                                       
    friend bool dataManager::writeUsers(Usr** masterArrayUsrs, const size_t masterUsrCount, const char* filePath);

    static size_t getTotalMemoryAllocated() {
      return totalMemoryAllocated;
    }

    //NOTE: el modulo core o udeaBook queda encargado de: sendMsg y sendRequest
    
    //NOTE: el modulo udeaBook queda encargado de: printRequests, printRandFriend,
    //printSuggestions

  private:
    std::string usrname;
    std::string pfpPath;
    std::string email;
    std::string pwd;
    std::string city;
    std::string country;

    Date dob;
    Date joinDate;

    Usr** friends;
    size_t friendCount;
    size_t friendCapacity;

    Chat** chats;
    size_t chatCount;
    size_t chatCapacity;

    Usr** requests;
    size_t requestCount;
    size_t requestCapacity;

    Album** albums;
    size_t albumCount;
    size_t albumCapacity;

    static size_t totalMemoryAllocated;

    const std::string& getPwd() const {
      return pwd;
    }

    void resizeFriends();

    void resizeChats();

    void resizeRequests();

    void resizeAlbums();
};
