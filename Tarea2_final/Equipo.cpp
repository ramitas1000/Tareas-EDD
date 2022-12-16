#include "Equipo.hpp"
#include <iostream>
#include <string>

/***
 * Constructor de la clase Equipo
 * 
 * 
*/

Equipo::Equipo(){
    head = curr = NULL;
    tail = NULL;
    listSize = 0;
    pos = 0;
}

/***
 * Funcion para retornar un entero con el tamaño del equipo
*/

int Equipo::tamano(){
    return listSize;
}
/***
 * Funcion que agrega Personas a al equipo
 * Recibe el nombre de la persona y su poder
 * Retorna un entero con la posicion en la que fue insertada la persona
*/

int Equipo::agregar_companero(std::string nombre, int poder){
    Persona* newCompanero = new Persona(nombre,poder);
    if (head == NULL){
        head = newCompanero;
        listSize++;
        pos++;
        return listSize-1;
    }
    Persona* temp = head;
    while (temp->sig != NULL){
        temp = temp->sig;
    }
    temp->sig = newCompanero;
    listSize++;
    pos++;
    return listSize-1;    
}

/***
 * Funcion que desingna al capitan de un equipo
 * Recibe un stringcon el nombre de la persona y su poder
*/

void Equipo::definir_capitan(std::string nombre){
    moveToStart();
    while (curr != NULL){
        if (curr->nombre == nombre){
            curr->capitan = true;
            return;
        }
        next();
    }
    
}

/***
 * Funcion para mover el curr a la cabeza de la lista
*/

void Equipo::moveToStart(){
    curr = head;
    pos = 0;
}

/***
 * Funcion para mover el curr a la cola de la lista
*/

void Equipo::moveToEnd(){
    curr = tail;
    pos = listSize;
}

/***
 * Funcion para mover el curr a la posicion anterior de este
*/

void Equipo::prev(){
    Persona* temp;
    if (curr == head){
        return;
    }
    temp = head;
    while (temp->sig != curr){
        temp = temp->sig;
    }
    curr = temp;
    pos--; 
}

/***
 * Funcion para mover el curr a la posicion siguiente
*/

void Equipo::next(){
    if (curr != NULL){
        curr = curr->sig;
        pos++;
    }
}

/***
 * Funcion que retorna la posicion actual del curr
*/

int Equipo::posActual(){
    return pos;
}

/***
 * Funcion que retorna el nombre de la persona de la posicion actual
*/
std::string Equipo::nombreActual(){
    return curr->nombre;
}

/***
 * Funcion que retorna el capitan de la posicion actual
*/

std::string Equipo::get_capitan(){
    moveToStart();
    while (curr != NULL){
        if (curr->capitan == true){
            return curr->nombre;
        }
        next();
    }
    return head->nombre;
}

/***
 * Funcion que retorna el poder de la persona de la posicion actual
*/
int Equipo::poderActual(){
    return curr->poder;
}

/***
 * Funcion que retorna el poder TOTAL del equipo
*/

int Equipo::calcular_poder(){
    moveToStart();
    int suma_poderes = 0;
    while(curr != NULL){
        suma_poderes += poderActual();
        next();
    }
    return suma_poderes;
}

/**
 * Funcion que imprime por pantalla el equipo completo
*/

void Equipo::imprimir_equipo(){
    moveToStart();
    if (curr == NULL){
        std::cout << "Equipo sin miembros" << std::endl;
        return;
    }
    std::cout << "Equipo:" << std::endl;
    while(curr != NULL){
        if (curr->capitan == true){
            std::cout << "Persona " << pos << ": " << curr->nombre << " " << "true" << " " << curr->poder << std::endl;
            next();
        }
        else{
            std::cout << "Persona " << pos << ": " << curr->nombre << " " << "false" << " " << curr->poder << std::endl;
            next();
        }
        
    }
    return;
}