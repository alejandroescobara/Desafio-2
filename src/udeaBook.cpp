#include "udeaBook.hpp"
#include <string>
#include <iostream>
#include <random>

#include "Usr.hpp"
#include "Album.hpp"
#include "Chat.hpp"
#include "Photo.hpp"
#include "Msg.hpp"
#include "Date.hpp"

namespace udeaBook{

    namespace{

    //aqui iran las funciones auxiliares

        Usr * usrNameSearch(Usr ** totalUsr, std::string usrName, size_t numUsr){
            size_t init = 0;
            size_t end = numUsr - 1;
            size_t mid = 0;
            while(init <= end){
                mid = init + ((end - init)/ 2);
                if((totalUsr[mid])->getUsrname() == usrName){
                    return totalUsr[mid];
                    break;
                }
                if((totalUsr[mid])->getUsrname() < usrName){
                    init = mid + 1;
                }
                else{
                    end = mid - 1;
                }
            }
            return nullptr;
        }

        void carousel(const Album * album, Usr*currentUsr, const Usr * albumUser){
            char election = ' ';
            size_t numPhotos = album->getPhotoCount();
            if(numPhotos > 1){
                const Photo * const * Photos = album->getPhotos();
                size_t indexPhoto = 0;
                while(election != '1'){

                    std::cout<<"        /users/(sub-ruta-X-fija)/"<<albumUser->getUsrname()<<"/albums/"<<album->getTitle()<<"/"<<Photos[indexPhoto]->getTitle()<<"\n\n";
                    std::cout<<"                         menu de opciones:\n\n"
                             <<"                        1.-salir del album\n"
                             <<"                         2.-siguiente foto\n"
                             <<"                           3.-foto previa\n"
                             <<"                          4.-dar/quitar like\n"
                             <<"                            su opcion: ";
                    std::cin>>election;
                    switch (election) {
                    case '1':
                        //solo apelamos a que se rompa el while
                        break;
                    case '2':

                        ((indexPhoto == numPhotos - 1)? indexPhoto = 0 : indexPhoto++);
                        break;
                    case '3':

                        ((indexPhoto == 0)? indexPhoto = numPhotos - 1 : indexPhoto--);
                        break;
                    case '4':
                        //Photos[indexPhoto]->toggleLike(currentUsr);<----- corregir conflicto de referencias
                        break;
                    default:
                        std::cout<<"\n\n                ---ingrese un valor valido---\n\n";
                        break;
                    }
                }
            }
            else{
                std::cout<<"\n\n                ---no hay fotos en el album---\n\n";
            }
        }

        Chat chatSearch(std::string usrName1, std::string usrName2, size_t numChats){
            std::string names = ((usrName1 > usrName2) ? (usrName1+'#'+usrName2) : (usrName2+'#'+usrName1));
            size_t init = 0;
            size_t end = numChats - 1;
            size_t mid = 0;
            while(init <= end){
                mid = init + ((end - init)/ 2);
                if((() == names){
                    return totalUsr[mid];
                    break;
                }
                if((totalUsr[mid])->getUsrname() < usrName){
                    init = mid + 1;
                }
                else{
                    end = mid - 1;
                }
            }
            return nullptr;
        }

    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    Usr * initSessionInterface(Usr ** totalUsr, size_t numUsr){
        //se uso busqueda binaria
        std::string pwdTry;
        std::string usrNameTry;
        Usr * currentUser;
        std::cout<<"            bienvenido a Ude@book\n\n"
                  <<"    ingrese el nombre de usuario: ";
        std::cin.ignore();
        std::getline(std::cin, usrNameTry);
        std::cout<<"    ingrese la contraseña: ";
        std::cin.ignore();
        std::getline(std::cin, pwdTry);

        currentUser = usrNameSearch(totalUsr,usrNameTry,numUsr);
        if(currentUser == nullptr){
            std::cout<<"\n\n----nombre de usuario o contraseña erroneos---\n\n";
            return nullptr;
        }
        return currentUser;
    }

    char usrInterface(Usr * currentUsr){
        //el algoritmo de impresion de las fotos lo base en el algorimo de ruleta

        size_t numFriends = currentUsr->getFriendCount();
        long long numFriendsAux = numFriends;//<-------

        std::random_device semilla;
        std::mt19937 generador(semilla());
        short ciclos = 0;
        unsigned char * ponderedFriends = new unsigned char[numFriends];
        char election = 'N';

        while(election == 'N' || election == 'n'){
            const Usr * const  * ptrFriends = currentUsr->getFriends();
            if(ciclos < 2){
                if(numFriendsAux > 3){

                    if(ciclos == 0){
                        for(size_t i = 0; i < numFriends; i++){
                            size_t communFriends = currentUsr->countCommonFriends(ptrFriends[i]);
                            if(communFriends<=10){
                                ponderedFriends[i] = 2;
                            }
                            if(communFriends>10 && communFriends<=20){
                                ponderedFriends[i] = 5;
                            }
                            if(communFriends>20){
                                ponderedFriends[i] = 7;
                            }
                        }
                    }

                    for(int i = 0; i< 3; i++){
                        int totalWeigth = 0;
                        int acumulation = 0;
                        int k = 0;

                        for(size_t j = 0; j < numFriends; j++){
                            totalWeigth += ponderedFriends[j];
                        }

                        std::uniform_int_distribution<int> distribucion(1, totalWeigth);
                        int ramdonNum = distribucion(generador);
                        while(acumulation < ramdonNum){
                            acumulation += ponderedFriends[k];
                            if (acumulation < ramdonNum){++k;}// habia problemas si ramdomnum == 0
                        }

                        switch(i){
                        case 0:
                            std::cout<<"foto de perfil "<<ptrFriends[k]->getUsrname()<<":"<<ptrFriends[k]->getPfpPath()<<"\n";
                            ponderedFriends[k] = 0;
                            break;
                        case 1:
                            std::cout<<"foto de perfil "<<ptrFriends[k]->getUsrname()<<":"<<ptrFriends[k]->getPfpPath()<<"\n";
                            ponderedFriends[k] = 0;
                            break;
                        case 2:
                            std::cout<<"foto de perfil "<<ptrFriends[k]->getUsrname()<<":"<<ptrFriends[k]->getPfpPath()<<"\n";
                            ponderedFriends[k] = 0;
                            break;
                        }
                    }
                }
                else{
                    if (ciclos == 0){
                        for(unsigned char i = 0; i<numFriends; i++){
                            std::cout<<"foto de perfil "<<ptrFriends[i]->getUsrname()<<":"<<ptrFriends[i]->getPfpPath();
                        }
                    }
                    else{
                        if(numFriendsAux > 0){
                            for(unsigned char i = 0; i < numFriends; i++){
                                if(ponderedFriends[i] != 0){
                                    std::cout<<"foto de perfil "<<ptrFriends[i]->getUsrname()<<":"<<ptrFriends[i]->getPfpPath();
                                }
                            }
                        }
                        else{std::cout<<"\n---no hay amigos para alternar---\n\n";}
                    }
                }
            }
            else{std::cout<<"---solo se puede alternar el grupo de fotos una vez---";}

            std::cout<<"                Bienvenido a UdeABook//"<<currentUsr->getUsrname()<<"\n\n\n";
            std::cout<<"                        menu de opciones:\n\n"
                      <<"                     1.-administrar amistades\n"
                      <<"                   2.-visitar perfil de un amigo\n"
                      <<"                   3.-ver sugerencias de amistad\n"
                      <<"                      4.-administar mensajes\n"
                      <<".-ingrese 'N' o 'n' para alternar el grupo de fotos de perfil de amigos."
                      <<"              .- ingrese 'S' o 's' para cerrar su sesion"
                      <<"                            su opcion: ";
            std::cin>>election;
            if(election == 'N' || election == 'n'){
                ciclos++;
                numFriendsAux -= 3;
            }
            else{ciclos = 3;}
        }
        delete[] ponderedFriends;
        return election;
    }

    // la funcion anterior nos dice que quiere el usuario faltan la respectivas funciones

    void friendsManage(Usr * currentUsr, Usr ** totalUsr, size_t numUsr){
        char election = '4';
        while(election == '4'){
            std::cout<<"                         menu de opciones:\n\n"
                     <<"                 1.-enviar solicitudes de amistad\n"
                     <<"                 2.-revisar solicitudes de amistad\n"
                     <<"                           3.-retroceder\n"
                     <<"                            su opcion: ";
            std::cin>>election;
            std::string usrName;
            bool aux = false;

            size_t  numRequests;
            Usr ** requests;
            Usr * requestUsr;

            switch (election) {
            case '1':
                std::cout<<"ingrese el nombre de usuario al que desea mandar la solicitud: ";
                std::cin.ignore();
                std::getline(std::cin, usrName);
                requestUsr = usrNameSearch(totalUsr,usrName,numUsr);

                if(requestUsr != nullptr){
                    std::cout<<"\n\n+++se mando la solicitud de amistad con exito+++\n\n";
                }
                else{
                    std::cout<<"\n\n---no se encontro al usuario ingresado---\n\n";
                }
                election = '4';

                break;
            case '2':
                numRequests = currentUsr->getRequestCount();
                requests = currentUsr->getRequests();
                std::cout<<"solicitudes recibidas: ";
                for(size_t i = 0; i < numRequests; i++){
                    std::cout<<"-"<<requests[i]->getUsrname()<<"\n";
                }
                std::cout<<"\n\ningrese el usuario al que desea aceptar la solicitud: ";
                std::cin.ignore();
                std::getline(std::cin, usrName);

                for(size_t i = 0; i < numRequests; i++){
                    if((requests[i]->getUsrname()) == usrName){
                        currentUsr->addFriend(requests[i]);
                        requests[i]->addFriend(currentUsr);
                        currentUsr->removeRequest(requests[i]);
                        aux = true;
                        break;
                    }
                }
                if(aux){
                    std::cout<<"\n\n+++se acepto la solicitud de amistad con exito+++\n\n";
                }
                else{
                    std::cout<<"\n\n---no se encontro al usuario ingresado---\n\n";
                }
                election = '4';
                break;
            case '3':
                //la idea es que no haga nada para que salga de while
                break;
            default:
                election = '4';
                std::cout<<"---ingrese un valor valido---";
                break;
            }
        }
    }

    void profileViewer(Usr * currentUsr){

        std::string usrName;
        const Usr * const * friends = currentUsr->getFriends();
        const Usr * friend_ = nullptr;
        size_t numFriends = currentUsr->getFriendCount();
        std::cout<<"\n\ningrese el amigo al que desea visitar el perfil: ";
        std::cin.ignore();
        std::getline(std::cin, usrName);

        for(size_t i = 0; i < numFriends; i++){
            if(friends[i]->getUsrname() == usrName){
                friend_ = friends[i];
                break;
            }
        }
        if (friend_ != nullptr){
            size_t numAlbums = friend_->getAlbumCount();
            const Album * const * albums = friend_->getAlbums();
            std::string privacity;
            char election = '3';

            for(size_t i = 0; i < numAlbums; i++){
                std::cout<<"\n\nalbum no."<<i+1<<".-"<<albums[i]->getTitle()<<" "<<((albums[i]->getVisibility()=='p')?("public"):("amigos"))<<"\n";
            }
            while(election != '2'){
                std::cout<<"                         menu de opciones:\n\n"
                         <<"                          1.-ver un album\n"
                         <<"                           2.-retroceder\n"
                         <<"                            su opcion: ";
                std::cin>>election;

                switch(election){
                case'1':{
                    bool found = false;
                    std::string albumName;
                    std::cout<<"escriba el nombre del album: ";
                    std::cin.ignore();
                    std::getline(std::cin, albumName);

                    for(size_t i = 0; i < numAlbums; i++){
                        if (albums[i]->getTitle() == albumName){
                            carousel(albums[i],currentUsr,friend_);
                            found = true;
                            break;
                        }
                    }
                    if(!found){
                        std::cout<<"---el album escrito no esta entre el grupo de albums de "<<friend_->getUsrname()<<"---";
                    }
                    break;
                }
                case'2':
                    //esto esta solo pa romper switch
                    break;
                default:
                    election = '3';
                    std::cout<<"\n\n---ingrese un valor valido---\n\n";
                    break;
                }
            }
        }
        else{
            std::cout<<"\n\n---el usuario ingresado no esta entre tus amigos---\n\n";
        }
    }

    void msgManager(Usr* currentUsr){
        char election = ' ';
        while(election != '4'){
            std::cout<<"                         menu de opciones:\n\n"
                      <<"                        1.-enviar mensaje\n"
                      <<"                     2.-leer nuevos mensajes\n"
                      <<"                 3.buscar mensajes por rango de fecha\n"
                      <<"                           4.-retroceder\n"
                      <<"                            su opcion: ";
            std::cin>>election;

            switch(election){
            case'1':{

                std::string usrName;
                const Usr * const * friends = currentUsr->getFriends();
                const Usr * friend_ = nullptr;
                size_t numFriends = currentUsr->getFriendCount();
                std::cout<<"\n\ningrese el amigo al que desea visitar el perfil: ";
                std::cin.ignore();
                std::getline(std::cin, usrName);

                for(size_t i = 0; i < numFriends; i++){
                    if(friends[i]->getUsrname() == usrName){
                        friend_ = friends[i];
                        break;
                    }
                }
                if (friend_ != nullptr){
                    Date * currentDate = new Date;
                    *currentDate = Date::now();

                }
                else{
                    std::cout<<"\n\n---el usuario ingresado no esta entre tus amigos---\n\n";
                }
                break;
            }
            case'2':

                break;
            case'3':

                break;
            case'4':
                //esto esta solo pa romper switch
                break;
            default:
                std::cout<<"\n\n---ingrese un valor valido---\n\n";
                break;
            }
        }
    }
}







