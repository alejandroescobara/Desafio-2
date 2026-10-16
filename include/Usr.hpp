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

    const std::string& getUsrname() const;

    const std::string& getPfpPath() const;

    const std::string& getEmail() const;

    bool checkPwd(const std::string& inputPwd) const;

    const std::string& getCity() const;

    const std::string& getCountry() const;

    const Date& getDob() const;
    
    const Date& getJoinDate() const;

    const Usr* const* getFriends() const;
    size_t getFriendCount() const;
    void addFriend(Usr* newFriend);

    bool isFriend(const Usr* targetUsr) const; 

    const Chat* const* getChats() const;
    size_t getChatCount() const;
    void addChat(Chat* newChat);

    const Usr* const* getRequests() const;
    size_t getRequestCount() const;
    void addRequest(Usr* newRequest);

    void processRequest(Usr* targetRequest, bool accept);
    void removeRequest(Usr* targetRequest);

    const Album* const* getAlbums() const;
    size_t getAlbumCount() const;
    void addAlbum(Album* newAlbum);

    size_t countCommonFriends(const Usr* otherUsr) const; //NOTE: printRandFriend->udeaBook

    bool hasPendingRequest(const Usr* targetUsr) const;

    void toggleLike(Photo* targetPhoto);

    Usr& operator=(const Usr& other) = delete;

    friend std::ostream& operator<<(std::ostream& os, const Usr& usr); //<- printProfile
                                                                       
    friend bool dataManager::writeUsers(Usr** masterArrayUsrs, const size_t masterUsrCount, const char* filePath);

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

    //TODO: volver friends y requests constantes, cambiar resizes y etc para este cambio futuro
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

    const std::string& getPwd() const;

    void resizeFriends();

    void resizeChats();

    void resizeRequests();

    void resizeAlbums();
};
