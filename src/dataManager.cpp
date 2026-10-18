#include "dataManager.hpp"

#include <string>
#include <sstream>
#include <fstream>

#include <cstddef>

#include "Usr.hpp"
#include "Msg.hpp"
#include "Album.hpp"
#include "Photo.hpp"
#include "Date.hpp"
#include "core.hpp"
#include "validators.hpp"

namespace dataManager {

  namespace { 

    constexpr const char* USERS_FILEPATH = "systemData/users.csv";
     
    constexpr const char* ALBUMS_FILEPATH = "systemData/albums.txt";
     
    constexpr const char* CHATS_FILEPATH = "systemData/chats.txt";

    bool checkFilesExist() {
      if (!validators::fileExists(USERS_FILEPATH)) return false;
      if (!validators::fileExists(ALBUMS_FILEPATH)) return false;
      if (!validators::fileExists(CHATS_FILEPATH)) return false;
      return true;
    }

    bool loadUsers(Usr**& masterArrayUsrs,
                   size_t& masterUsrCount,
                   size_t& masterUsrCapacity,
                   const char* filePath) {
    //---------
      std::ifstream file(filePath);
      if (!file.is_open()) return false;

      std::string line;
      while (std::getline(file, line)) {

        std::stringstream ss(line);

        std::string usrname, email, pwd, city, country, dobStr, joinDateStr;

        std::getline(ss, usrname, ';');
        std::getline(ss, email, ';');
        std::getline(ss, pwd, ';');
        std::getline(ss, city, ';');
        std::getline(ss, country, ';');

        std::getline(ss, dobStr, ';');
        Date dob(dobStr, false);
        std::getline(ss, joinDateStr, ';');
        Date joinDate(joinDateStr, false);


        Usr* currentUsr = new Usr(usrname, email, pwd, city, country, dob, joinDate);
        if (masterUsrCount >= masterUsrCapacity) core::resizeMasterArrayUsrs(masterArrayUsrs,masterUsrCapacity,masterUsrCount); //TODO: <- core.cpp
        masterArrayUsrs[masterUsrCount++] = currentUsr;

      }

      file.clear();
      file.seekg(0, std::ios::beg);

      size_t i = 0;

      while (std::getline(file, line)) {
        
        Usr* currentUsr = masterArrayUsrs[i++];

        std::stringstream ss(line);
        std::string dummy, friendsStr, requestsStr;

        for (int k = 0; k < 7; ++k) std::getline(ss, dummy, ';');

        std::getline(ss, friendsStr, ';');
        std::stringstream ssFriends(friendsStr);

        std::string friendUsrname;

        while (std::getline(ssFriends, friendUsrname, ',')) {
          Usr* friendPtr = core::usrNameSearch(masterArrayUsrs,friendUsrname,masterUsrCount);
        }

        std::getline(ss, requestsStr);
        std::stringstream ssRequests(requestsStr);

        std::string requestUsrname;

        while (std::getline(ssRequests, requestUsrname, ',')) {
          Usr* requestPtr = core::usrNameSearch(masterArrayUsrs,requestUsrname,masterUsrCount);
          currentUsr->addRequest(requestPtr);
        }
      }
      file.close();
      return true;
    }

    bool loadAlbums(Usr**& masterArrayUsrs,
                    const size_t masterUsrCount,
                    const char* filePath) {
    //---------
      std::ifstream file(filePath);
      if (!file.is_open()) return false;

      std::string line;
      std::stringstream ss;

      std::string ownerUsrname, albumTitle, albumPath;
      bool hasAlbums = true;

      std::string photoTitle, photoDateStr, likesStr;
      size_t photoFileSize;

      size_t usrIdx = 0;
      Usr* currentUsr = nullptr;
      Album* currentAlbum = nullptr;
      Photo* currentPhoto = nullptr;

      while (std::getline(file, line)) {
        
        ss.clear();
        ss.str(line);



        switch(line[0]) {
          case '#':
            ss.ignore(1);
            std::getline(ss, ownerUsrname);
            if (ownerUsrname == masterArrayUsrs[usrIdx] -> getUsrname()) {
              hasAlbums = true;
            }
            else {
              hasAlbums = false;
              continue;
            }
            currentUsr = masterArrayUsrs[usrIdx++];
            currentAlbum = nullptr;
            break;

          case '@':

            if (!hasAlbums) break;

            ss.ignore(1);
            std::getline(ss, albumTitle, ';');

            char visibility;
            ss >> visibility;

            currentAlbum = new Album(albumTitle, ownerUsrname, visibility);
            currentUsr->addAlbum(currentAlbum);
            break;

          default:

            if (!hasAlbums) break;

            std::getline(ss, photoTitle, ';');
            std::getline(ss, photoDateStr, ';');
            Date photoDate(photoDateStr, false);

            ss >> photoFileSize;
            ss.ignore(1);

            albumPath = currentAlbum->getPath();
            currentPhoto = new Photo(photoTitle, photoDate, albumPath, photoFileSize);

            *currentAlbum += currentPhoto;

            std::getline(ss, likesStr);

            std::stringstream ssLikes(likesStr);

            std::string likeUsrname;

            while (std::getline(ssLikes, likeUsrname, ',')) {
              Usr* likePtr = core::usrNameSearch(masterArrayUsrs,likeUsrname,masterUsrCount);
              currentPhoto->toggleLike(likePtr);
            }
        }
      } 
      return true;
    }

    bool loadChats(Usr**& masterArrayUsrs,
                   size_t& masterUsrCount, 
                   Chat**& masterArrayChats,
                   size_t& masterChatCount,
                   size_t& masterChatCapacity,
                   const char* filePath) {
    //---------
      std::ifstream file(filePath);
      if (!file.is_open()) return false;

      Chat* currentChat = nullptr;
      Msg* currentMsg = nullptr;
      Usr* currentUsrA = nullptr;
      Usr* currentUsrB = nullptr;

      Usr* currentSender = nullptr;

      std::string usrnameA, usrnameB;

      std::string senderUsrname, msgDateStr, msgText;

      std::string line;
      std::stringstream ss;

      while (std::getline(file, line)) {
        
        ss.clear();
        ss.str(line);

        if (line[0] == '#') {
          std::getline(ss, usrnameA, ';');
          currentUsrA = core::usrNameSearch(masterArrayUsrs, usrnameA, masterUsrCount); //TODO <- core.cpp
          std::getline(ss, usrnameB); 
          currentUsrB = core::usrNameSearch(masterArrayUsrs, usrnameB, masterUsrCount); //TODO <- core.cpp

          currentChat = new Chat(currentUsrA, currentUsrB);

          currentUsrA->addChat(currentChat);
          currentUsrB->addChat(currentChat);


          if (masterChatCount >= masterChatCapacity) core::resizeMasterArrayChats(masterArrayChats,masterChatCapacity,masterChatCount); //TODO: <- core.cpp
          masterArrayChats[masterChatCount++] = currentChat;
        }
        else {
          std::getline(ss, senderUsrname, ';');
          
          currentSender = (senderUsrname == usrnameA)? currentUsrA : currentUsrB;

          std::getline(ss, msgDateStr, ';');
          Date msgDate(msgDateStr, true);

          bool isRead = false;
          ss >> isRead;
          ss.ignore(1);

          ss >> msgText;

          currentMsg = new Msg(currentSender, msgDate, msgText, isRead);

          *currentChat += currentMsg;
        }
      }
      return true;
    }

    bool writeAlbums(Usr**& masterArrayUsrs,
                     size_t& masterUsrCount,
                     const char* filePath) {
    //---------
      std::ofstream file(filePath);
      if (!file.is_open()) return false;

      Usr*         currentUsr   = nullptr;
      const Album* currentAlbum = nullptr;
      const Photo* currentPhoto = nullptr;

      for (size_t i = 0; i < masterUsrCount; ++i) {
        currentUsr = masterArrayUsrs[i];
        
        if (currentUsr->getAlbumCount() == 0) continue;

        file << '#' << currentUsr->getUsrname() << '\n';

        for (size_t j = 0; j < currentUsr->getAlbumCount(); ++j) {
          currentAlbum = currentUsr->getAlbums()[j];

          file << '@' << currentAlbum->getTitle() << ';' << currentAlbum->getVisibility() << '\n';

          if (currentAlbum->getPhotoCount() == 0) continue;

          for (size_t k = 0; k < currentAlbum->getPhotoCount(); ++k) {
            if (k > 0) file << '\n';
            
            currentPhoto = currentAlbum->getPhotos()[k];

            file << currentPhoto->getTitle()                << ';'
                 << currentPhoto->getDate().toString(false) << ';'
                 << currentPhoto->getFileSize()             << ';';
            
            for (size_t w = 0; w < currentPhoto->getLikeCount(); ++w) {
              if (w > 0) file << ',';
              file << currentPhoto->getLikes()[w];
            }
          }
        }
      }
      return true;
    }
    
    bool writeChats(Chat**& masterArrayChats,
                    size_t& masterChatCount,
                    const char* filePath) {
    //---------
      std::ofstream file(filePath);
      if(!file.is_open()) return false;

      Chat*       currentChat = nullptr;
      const Msg*  currentMsg  = nullptr;

      for (size_t i = 0; i < masterChatCount; ++i) {
        currentChat = masterArrayChats[i];

        file << '#' << currentChat->getUsrA()->getUsrname()
             << ';' << currentChat->getUsrB()->getUsrname() << '\n';
        for (size_t j = 0; j < currentChat->getMsgCount(); ++j) { 
          currentMsg = currentChat->getMsgs()[j];

          file << currentMsg->getSender()     << ';'
               << currentMsg->getSentDate()   << ';'
               << currentMsg->getIsRead()     << ';'
               << currentMsg->getText()       << '\n';
        }
      }
      return true;
    } 
  }

  bool writeUsers(Usr** masterArrayUsrs,
                  const size_t masterUsrCount,
                  const char* filePath) {
  //---------
    std::ofstream file(filePath);
    if (!file.is_open()) return false;

    Usr* currentUsr = nullptr;

    for (size_t i = 0; i < masterUsrCount; ++i) {
      currentUsr = masterArrayUsrs[i];

      if (i > 0) file << '\n';

      file << currentUsr->usrname                  << ';'
           << currentUsr->email                    << ';'
           << currentUsr->pwd                      << ';'
           << currentUsr->city                     << ';'
           << currentUsr->country                  << ';'
           << currentUsr->dob.toString(false)      << ';'
           << currentUsr->joinDate.toString(false) << ';';

      for (size_t j = 0; j < currentUsr->friendCount; ++j) {
        if (j > 0) file << ',';
        file << currentUsr->friends[j]->usrname;
      }
      
      file << ';';

      for (size_t j = 0; j < currentUsr->requestCount; ++j) {
        if (j > 0) file << ',';
        file << currentUsr->requests[j]->usrname;
      }
    }
    return true;
  }

  bool loadSystemData(Usr**& masterArrayUsrs, size_t& masterUsrCount, size_t& masterUsrCapacity,
                      Chat**& masterArrayChats, size_t& masterChatCount, size_t& masterChatCapacity) {
  //-------
    if (!checkFilesExist()) return false;

    if (!loadUsers(masterArrayUsrs, masterUsrCount, masterUsrCapacity, "systemData/users.csv"))                                     return false;
    if (!loadAlbums(masterArrayUsrs, masterUsrCount, "systemData/albums.txt"))                                                      return false;
    if (!loadChats(masterArrayUsrs, masterUsrCount, masterArrayChats, masterChatCount, masterChatCapacity, "systemData/chats.txt")) return false;
    return true;
  }

  bool saveSystemData(Usr** masterArrayUsrs,   size_t masterUsrCount,
                      Chat** masterArrayChats, size_t masterChatCount) {
  //------- 
    if (!checkFilesExist()) return false;

    if (!writeUsers(masterArrayUsrs, masterUsrCount, "systemData/users.csv")) return false;
    if (!writeAlbums(masterArrayUsrs, masterUsrCount, "systemData/albums.txt")) return false;
    if (!writeChats(masterArrayChats, masterChatCount, "systemData/chats.txt")) return false;
    return true;
  }

  void freeSystemData(Usr**& masterArrayUsrs,   size_t& masterUsrCount,
                      Chat**& masterArrayChats, size_t& masterChatCount) {
  //-------
    if (masterArrayUsrs != nullptr) {
      for (size_t i = 0; i < masterUsrCount; ++i) {
        delete masterArrayUsrs[i];
        masterArrayUsrs[i] = nullptr;
      }
      delete[] masterArrayUsrs;
      masterArrayUsrs = nullptr;
    }
    masterUsrCount = 0;

    if (masterArrayChats != nullptr) {
      for (size_t i = 0; i < masterChatCount; ++i) {
        delete masterArrayChats[i];
        masterArrayChats[i] = nullptr;
      }
      delete[] masterArrayChats;
      masterArrayChats = nullptr;
    }
    masterChatCount = 0;
  }

  //void shutdownSystemData() {} TODO <- core.cpp esta funcion contiene save como free
}
