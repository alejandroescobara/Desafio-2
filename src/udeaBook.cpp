#include "udeaBook.hpp"
#include <string>
#include <iostream>
#include <random>

#include "core.hpp"
#include "Usr.hpp"
#include "Album.hpp"
#include "Chat.hpp"
#include "Photo.hpp"
#include "Msg.hpp"
#include "Date.hpp"

namespace udeaBook{

    namespace{

    //aqui iran las funciones auxiliares



        void carousel(Album * album, Usr*currentUsr, const Usr * albumUser){
            char election = ' ';
            size_t numPhotos = album->getPhotoCount();
            if(numPhotos > 0){
                Photo ** Photos = album->getPhotos();
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
                        Photos[indexPhoto]->toggleLike(currentUsr);//<----- corregir conflicto de referencias
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



        void sendMsg(Usr * currentUsr, Chat * chat){

            std::string newMsgText;
            std::cout<<"ingrese el mensaje a mandar -- 512 caracteres max--:\n ";
            std::getline(std::cin, newMsgText);
            if(newMsgText.length()<513 && newMsgText.length() > 0){
                Msg * newMsg = new Msg(currentUsr, Date::now(),newMsgText,false);
                *chat += newMsg;
            }
            else{
                std::cout<<"\n\n---el mensaje sobrepasa el maximo o no pose contenido---\n\n";
            }
        }

        void seeMsgByDate(Usr * currentUsr, Chat * currentChat){
            std::string date1,date2,dateAux;
            std::cout<<"ingrese la fecha inicial:\nAño: ";
            std::getline(std::cin, dateAux);
            date1 += dateAux;
            std::cout<<"Mes: ";
            std::getline(std::cin, dateAux);
            date1 += dateAux;
            std::cout<<"Dia: ";
            std::getline(std::cin, dateAux);
            date1 += dateAux;
            std::cout<<"Hora: ";
            std::getline(std::cin, dateAux);
            date1 += dateAux;
            std::cout<<"Minuto: ";
            std::getline(std::cin, dateAux);
            date1 += dateAux;
            std::cout<<"segundo: ";
            std::getline(std::cin, dateAux);
            date1 += dateAux;

            std::cout<<"\ningrese la fecha final:\nAño: ";
            std::getline(std::cin, dateAux);
            date2 += dateAux;
            std::cout<<"Mes: ";
            std::getline(std::cin, dateAux);
            date2 += dateAux;
            std::cout<<"Dia: ";
            std::getline(std::cin, dateAux);
            date2 += dateAux;
            std::cout<<"Hora: ";
            std::getline(std::cin, dateAux);
            date2 += dateAux;
            std::cout<<"Minuto: ";
            std::getline(std::cin, dateAux);
            date2 += dateAux;
            std::cout<<"Segundo: ";
            std::getline(std::cin, dateAux);
            date2 += dateAux;

            currentChat->printAndMarkMsgs(currentUsr,Date(date1,true),Date(date2,true));
        }

        void interfaceSugestions(size_t k, Usr ** listaUsr,Usr * currentUsr){
            std::string usrName;
            char election = '0';
            while(election != '2'){
                bool isSend = false;
                std::cout<<"sugerencias de amistad: ";
                for(short i = 0; i < k; i++){
                    std::cout<<i+1<<".-"<<listaUsr[i]->getUsrname()<<"\n";
                }
                std::cout<<"                         menu de opciones:\n\n"
                         <<"                 1.-enviar solicituded de amistad\n"
                         <<"                           2.-retroceder\n"
                         <<"                            su opcion: ";
                std::cin>>election;
                if(election == '1'){
                    std::cout<<"\n\ningrese el usuario al que enviar la solicitud: ";
                    std::cin.ignore();
                    std::getline(std::cin, usrName);
                    for(short i = 0; i < k; i++){
                        if(listaUsr[i]->getUsrname() == usrName){
                            listaUsr[i]->addRequest(currentUsr);
                            isSend = true;
                            break;
                        }
                    }
                    if(isSend){
                        std::cout<<"\n\n+++se envio la solicitud+++\n\n";
                    }
                    else{
                        std::cout<<"\n\n---no se encontro el usuario en las sugerencias---\n\n";
                    }
                }
                else{
                    if(election != '2'){
                        std::cout<<"\n\n---ingrese un valor valido---\n\n";
                    }
                }
            }
        }

        bool alreadyApear(Usr * suggestion, Usr *** comunFriends, size_t used){
            for(size_t i = 0; i < used; i++){
                if(comunFriends[i/8][i%8] == suggestion){
                    return true;
                }
            }
            return false;
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
        std::getline(std::cin, usrNameTry);
        std::cout<<"    ingrese la contraseña: ";
        std::getline(std::cin, pwdTry);

        currentUser = core::usrNameSearch(totalUsr,usrNameTry,numUsr);
        if(currentUser == nullptr || !(currentUser->checkPwd(pwdTry))){
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
                            std::cout<<"foto de perfil "<<ptrFriends[i]->getUsrname()<<":"<<ptrFriends[i]->getPfpPath()<<"\n";
                        }
                    }
                    else{
                        if(numFriendsAux > 0){
                            for(unsigned char i = 0; i < numFriends; i++){
                                if(ponderedFriends[i] != 0){
                                    std::cout<<"foto de perfil "<<ptrFriends[i]->getUsrname()<<":"<<ptrFriends[i]->getPfpPath()<<"\n";
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
                      <<"             .- ingrese 'E' o 'e' para cerrar el programa"
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
                requestUsr = core::usrNameSearch(totalUsr,usrName,numUsr);

                if(requestUsr != nullptr){
                    requestUsr->addRequest(currentUsr);
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
        Usr ** friends = currentUsr->getFriends();
        Usr * friend_ = nullptr;
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
            Album ** albums = friend_->getAlbums();
            std::string privacity;
            char election = '3';

            for(size_t i = 0; i < numAlbums; i++){
                std::cout<<"\n\nalbum no."<<i+1<<".-"<<albums[i]->getTitle()<<" "<<((albums[i]->getVisibility()=='P')?("public"):("amigos"))<<"\n";
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

    void msgManager(Usr* currentUsr, Chat ** &totalChats, size_t &numChats, size_t &chatsCapacity){
        char election = ' ';
        while(election != '4'){
            std::cout<<"                         menu de opciones:\n\n"
                      <<"                        1.-enviar mensaje\n"
                      <<"                     2.-leer nuevos mensajes\n"
                      <<"                 3.buscar mensajes por rango de fecha\n"
                      <<"                           4.-retroceder\n"
                      <<"                            su opcion: ";
            std::cin>>election;
            std::cin.ignore();

            std::string usrName;
            Usr ** friends = currentUsr->getFriends();
            Usr * friend_ = nullptr;
            size_t numFriends = currentUsr->getFriendCount();



            switch(election){
            case'1':{
                std::cout<<"\n\ningrese el amigo con el que desea mensajear: ";
                std::getline(std::cin, usrName);

                for(size_t i = 0; i < numFriends; i++){
                    if(friends[i]->getUsrname() == usrName){
                        friend_ = friends[i];
                        break;
                    }
                }

                if (friend_ != nullptr){
                    Chat * currentChat = core::chatSearch(currentUsr->getUsrname(),friend_->getUsrname(),totalChats, numChats);
                    if(currentChat != nullptr){
                        sendMsg(currentUsr, currentChat);
                    }
                    else{
                        std::cout<<"\n\n---no se encontro el chat; se procedera a crear---\n\n";
                        Chat * newChat = new Chat(currentUsr,friend_);

                        totalChats = core::chatIncrust(chatsCapacity,numChats,totalChats,newChat);
                        numChats++;

                        currentUsr->addChat(newChat);
                        friend_->addChat(newChat);
                        sendMsg(currentUsr, newChat);
                    }
                }
                else{
                    std::cout<<"\n\n---el usuario ingresado no esta entre tus amigos---\n\n";
                }
                break;
            }
            case'2':{
                Usr ** totalFriends = currentUsr->getFriends();
                for(size_t i = 0; i < numFriends; i++ ){
                    Chat * chat = core::chatSearch(currentUsr->getUsrname(),totalFriends[i]->getUsrname(),totalChats,numChats);
                    if(chat != nullptr){
                        chat->consumeUnread(currentUsr);
                    }
                }
                break;
            }
            case'3':
                std::cout<<"\n\ningrese el amigo con el que desea mensajear: ";
                std::getline(std::cin, usrName);

                for(size_t i = 0; i < numFriends; i++){
                    if(friends[i]->getUsrname() == usrName){
                        friend_ = friends[i];
                        break;
                    }
                }

                if (friend_ != nullptr){
                    Chat * currentChat = core::chatSearch(currentUsr->getUsrname(),friend_->getUsrname(),totalChats, numChats);
                    if(currentChat != nullptr){
                        seeMsgByDate(currentUsr,currentChat);
                    }
                    else{
                        std::cout<<"\n\n---no se encontro el chat--\n\n";
                    }
                }
                else{
                    std::cout<<"\n\n---el usuario ingresado no esta entre tus amigos---\n\n";
                }
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

    void viewSugestions(Usr * currentUsr, Usr ** totalUsr, size_t numUsr){
        size_t k;
        std::cout<<"\n\ningrese el numero de sugerencias: ";
        std::cin>>k;

        int ** comunFriendsNum = new int*[2];
        comunFriendsNum[0] = new int[8];
        comunFriendsNum[1] = new int[8];

        Usr *** comunFriends = new Usr**[2];
        comunFriends[0] = new Usr*[8];
        comunFriends[1] = new Usr*[8];

        size_t countCapacity =  16;
        size_t used = 0;
        size_t blockCapacity = 2;

        Usr ** friendsList = currentUsr->getFriends();
        size_t numFriends = currentUsr->getFriendCount();

        for(size_t amigo = 0; amigo< numFriends; amigo++){
            size_t numFriends2 = friendsList[amigo]->getFriendCount();
            Usr ** friendsList2 = friendsList[amigo]->getFriends();

            for(size_t amigo2 = 0; amigo2< numFriends2; amigo2++){
                size_t numComunFriends = currentUsr->countCommonFriends(friendsList2[amigo2]);
                Usr *friend_ = friendsList2[amigo2];

                if(numComunFriends != 0
                    && !(friend_->isFriend(currentUsr))
                    && !(alreadyApear(friend_,comunFriends,used))
                    && friend_ != currentUsr){
                    if(used == countCapacity){
                        size_t newBlockCapacity = blockCapacity + 1;

                        Usr*** aux1 = new Usr**[newBlockCapacity];
                        int** aux2 = new int*[newBlockCapacity];

                        for(size_t i = 0; i < blockCapacity; i++){
                            aux1[i] = comunFriends[i];
                            aux2[i] = comunFriendsNum[i];
                        }

                        aux1[blockCapacity] = new Usr*[8];
                        aux2[blockCapacity] = new int[8];

                        delete[] comunFriends;
                        delete[] comunFriendsNum;

                        comunFriends = aux1;
                        comunFriendsNum = aux2;
                        blockCapacity = newBlockCapacity;
                        countCapacity = blockCapacity * 8;
                    }

                    comunFriends[used/8][used%8] = friend_;
                    comunFriendsNum[used/8][used%8] = numComunFriends;
                    used++;
                }
            }
        }
        if (k > used){
            k = used;
        }
        Usr ** listaUsr = new Usr*[k];
        for(size_t i = 0;i < k;i++){
            int indexMax = 0;
            Usr * usrMax = nullptr;
            size_t position;

            for(size_t j = 0;j<used;j++){
                int currentNum = comunFriendsNum[j/8][j%8];
                if(currentNum > indexMax){
                    indexMax = currentNum;
                    usrMax = comunFriends[j/8][j%8];
                    position = j;
                }
            }
            listaUsr[i] = usrMax;
            comunFriendsNum[position/8][position%8] = 0;
        }
        for(size_t i = 0; i < blockCapacity; i++){
            delete[] comunFriends[i];
            delete[] comunFriendsNum[i];
        }

        interfaceSugestions(k, listaUsr,currentUsr);
        delete [] listaUsr;
        delete[] comunFriends;
        delete[] comunFriendsNum;

    }
}


