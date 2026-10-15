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



Usr * initSessionInterface(Usr ** totalUsr, int numUsr){
    //se uso busqueda binaria
    std::string pwdTry;
    std::string usrNameTry;
    std::cout<<"            bienvenido a Ude@book\n\n"
             <<"    ingrese el nombre de usuario: ";
    std::getline(std::cin, usrNameTry);
    std::cout<<"    ingrese la contraseña: ";
    std::getline(std::cin, pwdTry);
    int init = 0;
    int end = numUsr - 1;
    int mid = 0;
    while(init <= end){
        mid = init + ((end - init)/ 2);
        if((totalUsr[mid])->getUsrname() == usrNameTry){
            if(totalUsr[mid]->checkPwd(pwdTry)){
                return totalUsr[mid];
            }
            break;
        }
        if((totalUsr[mid])->getUsrname() < usrNameTry){
            init = mid + 1;
        }
        else{
            end = mid - 1;
        }
    }
    std::cout<<"    nombre de usuario o contraseña erroneos\n";
    return nullptr;
}

char usrInterface(Usr * currentUsr){
    //el algoritmo de impresion de las fotos lo base en el algorimo de ruleta

    size_t numFriends = currentUsr->getFriendCount();
    long long numFriendsAux = numFriends;

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
                    for(int i = 0; i < numFriends; i++){
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

                    for(int j = 0; j < numFriends; j++){
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

char friendsManage(Usr * currentUsr, Usr ** totalUsr, int numUsr){ //funcion incompleta <--------------
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
        int init; // todo lo del switch case lo dividire en funciones
        int end;
        int mid;

        size_t  numRequests;
        const Usr * const * requests;
        std::string usrNameRequest;


        switch (election) {
        case '1':
            std::cout<<"ingrese el nombre de usuario: ";
            std::getline(std::cin, usrName);

            init = 0;
            end = numUsr - 1;
            mid = 0;
            while(init <= end){
                mid = init + ((end - init)/ 2);
                if((totalUsr[mid])->getUsrname() == usrName){
                    currentUsr->addFriend(totalUsr[mid]);
                    aux = true;
                    break;
                }
                if((totalUsr[mid])->getUsrname() < usrName){
                    init = mid + 1;
                }
                else{
                    end = mid - 1;
                }
            }
            if(aux){
                std::cout<<"\n\n+++se mando la solicitud de amistad con exito+++\n\n";
            }
            else{
                std::cout<<"\n\n---no se encontro al usuario ingresado---\n\n";
                election = '4';
            }

            break;
        case '2':
            numRequests = currentUsr->getRequestCount();
            requests = currentUsr->getRequests();
            std::cout<<"solicitudes recibidas: ";
            for(short i = 0; i < numRequests; i++){
                std::cout<<"-"<<requests[i]->getUsrname()<<"\n";
            }
            std::cout<<"\n\n";
            std::cout<<"ingrese el usuario al que desea enviar la solicitud: ";
            std::getline(std::cin, usrNameRequest);
            init = 0;
            end = numUsr - 1;
            mid = 0;
            while(init <= end){
                mid = init + ((end - init)/ 2);
                if((totalUsr[mid])->getUsrname() == usrName){
                    currentUsr->;
                    aux = true;
                    break;
                }
                if((totalUsr[mid])->getUsrname() < usrName){
                    init = mid + 1;
                }
                else{
                    end = mid - 1;
                }
            }


            break;
        case '4':
            std::cout<<"---ingrese un valor valido---";
            break;
        }
    }
}












