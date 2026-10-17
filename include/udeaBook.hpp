#pragma once
#include "Usr.hpp"
#include "Album.hpp"
#include "Chat.hpp"
#include "Photo.hpp"
#include "Msg.hpp"
#include "Date.hpp"

namespace udeaBook{

    /*ok, plasmemos aqui el orden de los susesos:
    1. ingreso y verificacion de usr: para esto hay que tener un arreglo con los objetos de los usuarios y un algoritmo de busqueda para el usr
    2. interfaz de los usuarios al autenticarse: para esto ya se trabaja con el orden dentro de la clase usuario se requiere
        ademas lo de la visualizacion de los amigos dependiendo de los amigos en comun
    3. administrar amistades: aqui trabajamos con busqueda de un usr, impresion de sus albumes y decidir si enviar o aceptar solicitud y sus respectivos procesos
    4. visitar perfil de un AMIGO por lo que hay verificacion de si es un amigo , despues los albumes segun su privasidad
        una busqueda del album ingresado y el carrucel
    5. ver sugerencias de amistad, la parte de planteamiento mas complejo no veo otra forma mas que buscar en los amigos y hacer dos arreglos redimencionables
        en paralelo uno de los no amigos de nuestro usr que aparescan y el otro de las veces que se repiten y los que mas se repitan imprimirlos
    6. administrar mensajes, la interfas de si se va a leer o a enviar y de lo demas la clase msg
    */

    Usr * initSessionInterface(Usr ** totalUsr, size_t numUsr);

    char usrInterface(Usr * currentUsr);

    void friendsManage(Usr * currentUsr, Usr ** totalUsr, size_t numUsr);

    void profileViewer(Usr * currentUsr);

    void msgManager(Usr* currentUsr, Chat ** totalChats, size_t numChats);
}