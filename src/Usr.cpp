#include "Usr.hpp"

#include <stdexcept>

#include "Chat.hpp"
#include "Album.hpp"
#include "Photo.hpp"

size_t Usr::totalMemoryAllocated = 0;

//NOTE: las validaciones de los atributos triviales pfpPath, usrname, etc, se haran afuera de la clase
Usr::Usr(const std::string& usrname,
         const std::string& email,
         const std::string& pwd,
         const std::string& city,
         const std::string& country,
         const Date& dob,
         const Date& joinDate,
         size_t initialFriendCapacity,
         size_t initialRequestCapacity,
         size_t initialChatCapacity,
         size_t initialAlbumCapacity)
   :usrname(usrname),
    pfpPath("/users/systemData/" + this->usrname + "/albums/profile.png"),
    email(email),
    pwd(pwd),
    city(city),
    country(country),
    dob(dob),
    joinDate(joinDate),
    friends(nullptr),  friendCount(0),
    friendCapacity(initialFriendCapacity),
    chats(nullptr),    chatCount(0),
    chatCapacity(initialChatCapacity),
    requests(nullptr), requestCount(0),
    requestCapacity(initialRequestCapacity),
    albums(nullptr),   albumCount(0),
    albumCapacity(initialAlbumCapacity) {
//-------
  
  try {
    friends  = new Usr*[initialFriendCapacity];
    albums   = new Album*[initialAlbumCapacity];
    chats    = new Chat*[initialChatCapacity];
    requests = new Usr*[initialRequestCapacity];
  } catch (const std::bad_alloc&) {

    delete[] friends;
    delete[] chats;
    delete[] requests;
    delete[] albums;
    throw;
  }

  for (size_t i = 0; i < initialFriendCapacity; ++i) friends[i] = nullptr;
  for (size_t i = 0; i < initialChatCapacity; ++i) chats[i] = nullptr;
  for (size_t i = 0; i < initialRequestCapacity; ++i) requests[i] = nullptr;
  for (size_t i = 0; i < initialAlbumCapacity; ++i) albums[i] = nullptr;
  

  totalMemoryAllocated += sizeof(Usr);

  totalMemoryAllocated += (friendCapacity * sizeof(Usr*));
  totalMemoryAllocated += (chatCapacity * sizeof(Chat*));
  totalMemoryAllocated += (requestCapacity * sizeof(Usr*));
  totalMemoryAllocated += (albumCapacity * sizeof(Album*));
}

Usr::~Usr() {
  delete[] friends;
  friends = nullptr;
  delete[] chats;
  chats = nullptr;
  delete[] requests;
  requests = nullptr;
  for (size_t i = 0; i < albumCount; ++i) {
    delete albums[i];
    albums[i] = nullptr;
  }
  delete[] albums;
  albums = nullptr;

  totalMemoryAllocated -= sizeof(Usr);
  totalMemoryAllocated -= (friendCapacity * sizeof(Usr*));
  totalMemoryAllocated -= (requestCapacity * sizeof(Usr*));
  totalMemoryAllocated -= (chatCapacity * sizeof(Chat*));
  totalMemoryAllocated -= (albumCapacity * sizeof(Album*));
}

const std::string& Usr::getPfpPath() const {
  return pfpPath;
}

const std::string& Usr::getUsrname() const {
  return usrname;
}

const std::string& Usr::getEmail() const {
  return email;
}

bool Usr::checkPwd(const std::string& inputPwd) const {
  return inputPwd == pwd;
}

const std::string& Usr::getPwd() const {
  return pwd;
}


const std::string& Usr::getCity() const {
  return city;
}

const std::string& Usr::getCountry() const {
  return country;
}

const Date& Usr::getDob() const {
  return dob;
}

const Date& Usr::getJoinDate() const {
  return joinDate;
}

const Usr* const* Usr::getFriends() const {
  return friends;
}

size_t Usr::getFriendCount() const {
  return friendCount;
}

void Usr::addFriend(Usr* newFriend) { 
  if (friendCount >= friendCapacity) {
    resizeFriends();
  }
  friends[friendCount++] = newFriend;
}

bool Usr::isFriend(const Usr* targetUsr) const {
  for (size_t i = 0; i < friendCount; ++i) {
    if (friends[i] == targetUsr) return true;
  }
  return false;
}

void Usr::resizeFriends() {
  size_t newCapacity = friendCapacity * 2;

  Usr** auxFriends = nullptr;

  try {
    auxFriends = new Usr*[newCapacity]; 
  } catch (const std::bad_alloc&) {
    delete[] auxFriends;
    throw;
  }

  for (size_t i = 0; i < friendCount; ++i)           auxFriends[i] = friends[i];
  for (size_t i = friendCount; i < newCapacity; ++i) auxFriends[i] = nullptr;

  delete[] friends;
  friends = auxFriends;

  totalMemoryAllocated += ((newCapacity - friendCapacity)* sizeof(Usr*));
  friendCapacity = newCapacity;
}

const Chat* const* Usr::getChats() const {
  return chats;
}

size_t Usr::getChatCount() const {
  return chatCount;
}

void Usr::addChat(Chat* newChat) {
  if (chatCount >= chatCapacity) {
    resizeChats();
  }
  chats[chatCount++] = newChat;
}

void Usr::resizeChats() {
  size_t newCapacity = chatCapacity * 2;

  Chat** auxChats = nullptr;

  try {
    auxChats = new Chat*[newCapacity]; 
  } catch (const std::bad_alloc&) {
    delete[] auxChats;
    throw;
  }

  for (size_t i = 0; i < chatCount; ++i)              auxChats[i] = chats[i];
  for (size_t i = chatCount; i < newCapacity; ++i)   auxChats[i] = nullptr;

  delete[] chats;
  chats = auxChats;

  totalMemoryAllocated += ((newCapacity - chatCapacity)* sizeof(Chat*));
  chatCapacity = newCapacity;
}

Usr ** Usr::getRequests(){
  return requests;
}

size_t Usr::getRequestCount() const {
  return requestCount;
}

void Usr::addRequest(Usr* newRequest) {
  if (requestCount >= requestCapacity) {
    resizeRequests();
  }
  requests[requestCount++] = newRequest;
}

void Usr::resizeRequests() {
  size_t newCapacity = requestCapacity * 2;

  Usr** auxRequests = nullptr;

  try {
    auxRequests = new Usr*[newCapacity]; 
  } catch (const std::bad_alloc&) {
    delete[] auxRequests;
    throw;
  }

  for (size_t i = 0; i < requestCount; ++i)               auxRequests[i] = requests[i];
  for (size_t i = requestCount; i < newCapacity; ++i) auxRequests[i] = nullptr;

  delete[] requests;
  requests = auxRequests;

  totalMemoryAllocated += ((newCapacity - requestCapacity)* sizeof(Usr*));
  requestCapacity = newCapacity;
}

void Usr::processRequest(Usr* targetRequest, bool accept) {
  if (targetRequest == nullptr) return;

  if (accept) {
    addFriend(targetRequest);
  }

  removeRequest(targetRequest);
}

void Usr::removeRequest(Usr* targetRequest) {
  if (targetRequest == nullptr || requests == nullptr || requestCount == 0) {
    return;
  }

  for (size_t i = 0; i < requestCount; ++i) {
    if (requests[i] == targetRequest) {
      for (size_t j = i; j < requestCount - 1; ++j) {
        requests[j] = requests[j + 1];
      }
      requests[requestCount - 1] = nullptr;
      --requestCount;
      return;
    }
  }
}

const Album* const* Usr::getAlbums() const {
  return albums;
}

size_t Usr::getAlbumCount() const {
  return albumCount;
}

void Usr::addAlbum(Album* newAlbum) {
  if (albumCount >= albumCapacity) {
    resizeAlbums();
  }
  albums[albumCount++] = newAlbum;
}

void Usr::resizeAlbums() {
  size_t newCapacity = albumCapacity * 2;

  Album** auxAlbums = nullptr;

  try {
    auxAlbums = new Album*[newCapacity]; 
  } catch (const std::bad_alloc&) {
    delete[] auxAlbums;
    throw;
  }

  for (size_t i = 0; i < albumCount; ++i)              auxAlbums[i] = albums[i];
  for (size_t i = albumCount; i < newCapacity; ++i)  auxAlbums[i] = nullptr;

  delete[] albums;
  albums = auxAlbums;

  totalMemoryAllocated += ((newCapacity - albumCapacity)* sizeof(Album*));
  albumCapacity = newCapacity;
}

size_t Usr::countCommonFriends(const Usr* otherUsr) const {
  if (otherUsr == nullptr || otherUsr == this) return 0;

  size_t otherCount = otherUsr->getFriendCount();
  if (friendCount == 0 || otherCount == 0) return 0;

  const Usr* const* otherFriends = otherUsr->getFriends();

  size_t commonLimit = (friendCount < otherCount)? friendCount: otherCount;
  size_t foundCommon = 0;

  for (size_t i = 0; i < friendCount; ++i) {

    if (foundCommon == commonLimit) break;

    for (size_t j = 0; j < otherCount; ++j) {
      if (friends[i] == otherFriends[j]) {
        ++foundCommon;
        break;
      }
    }
  }
  return foundCommon;
}

bool Usr::hasPendingRequest(const Usr* targetUsr) const {
  for (size_t i = 0; i < requestCount; ++i) {
    if (requests[i] == targetUsr) return true;
  }
  return false;
}

void Usr::toggleLike(Photo* targetPhoto) {
  if(targetPhoto == nullptr) return;
  targetPhoto->toggleLike(this);
}

std::ostream& operator<<(std::ostream& os, const Usr& targetUsr) {
  os << "==================================================\n"
     << " "<< targetUsr.usrname << "\n"
     << "==================================================\n"
     << " Foto de Perfil:   " << targetUsr.pfpPath << "\n"
     << " Correo:           " << targetUsr.email << "\n"
     << " Ubicacion:        " << targetUsr.city << ", " << targetUsr.country << "\n"
     << " Fecha Nacimiento: " << targetUsr.dob << "\n"
     << " Fecha Registro:   " << targetUsr.joinDate << "\n"
     << "--------------------------------------------------\n"
     << " Amigos: " << targetUsr.friendCount << " | Albumes: " << targetUsr.albumCount << "\n"
     << "==================================================";
  return os;
}
