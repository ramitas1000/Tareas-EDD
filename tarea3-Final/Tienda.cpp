#include "Tienda.hpp"
#include <string>


/*
 * Constructor de la clase Tienda
*/

Tienda::Tienda(){
    return;
}



/*
 * Funcion de hasheo
 * Recibe un entero id y lo transforma en una posicion de un arreglo
*/

int Tienda::hasheo(int id){
    return (id*id + 1);
}



/***
 * Funcion de resolicion de colisiones de la tabla de cartas
 * Recibe un enteri id y la cantidad de veces que ha colisionado el elemento a insertar
 * Retorna un entero con la posicion de un arreglo
*/

int Tienda::resolucion_de_colisiones_Cartas(int id, int n_colisiones){
    return (id + n_colisiones + 1);
}



/***
 * Funcion de resolicion de colisiones de la tabla de sobres
 * Recibe un enteri id y la cantidad de veces que ha colisionado el elemento a insertar
 * Retorna un entero con la posicion de un arreglo
*/

int Tienda::resolucion_de_colisiones_Sobres(int id, int n_colisiones){
    return (id + n_colisiones + 1);
}



/***
 * Funcion que crea la tabla de hashing de cartas de tamano M
 * Recibe un entero con la cantidad de elementos a insertar
 * No retorna nada
*/

void Tienda::crear_Tabla_Cartas(int size){
    n_cartas = size;
    for (int i = 0; i < M; i++){
        tabla_cartas[i].id = NUNCA_USADA;
    }    
}



/***
 * Funcion que crea la tabla de hashing de sobres de tamano M
 * Recibe un entero con la cantidad de elementos a insertar
 * No retorna nada
*/

void Tienda::crear_Tabla_Sobres(int size){
    n_sobres = size;
    for (int i = 0; i < M; i++){
        tabla_sobres[i].id = NUNCA_USADA;
    }
}



/***
 * Funcion que inserta una carta a la tabla de hashing
 * Recibe un elemento del tipo Carta, la hashea y luego la inserta en la tabla
 * No retorna nada
*/

void Tienda::agregar_Carta(Carta nueva){
    int posicion = hasheo(nueva.id)%M;
    int inicio = posicion;
    //El i del for es el numero de colisiones
    for (int i = 0; tabla_cartas[posicion].id != NUNCA_USADA && tabla_cartas[posicion].id != nueva.id; i++){
        posicion = (inicio + resolucion_de_colisiones_Cartas(nueva.id, i))%M;
    }
    if (tabla_cartas[posicion].id == nueva.id){
        tabla_cartas[posicion].cantidad +=1;
    }
    else{
        tabla_cartas[posicion].id = nueva.id;
        tabla_cartas[posicion].nombre = nueva.nombre;
        tabla_cartas[posicion].ataque = nueva.ataque;
        tabla_cartas[posicion].defensa = nueva.defensa;
        tabla_cartas[posicion].precio = nueva.precio;
        tabla_cartas[posicion].cantidad += 1;
    }
}



/***
 * Funcion que inserta un sobre a la tabla de hashing
 * Recibe un elemento del tipo Sobre, lo hashea y luego lo inserta en la tabla
 * No retorna nada
*/

void Tienda::agregar_Sobre(Sobre nuevo){
    int posicion = hasheo(nuevo.id)%M;
    int inicio = posicion;

    for (int i = 0; tabla_sobres[posicion].id != NUNCA_USADA && tabla_sobres[posicion].id != nuevo.id; i++){
        posicion = (inicio + resolucion_de_colisiones_Sobres(nuevo.id, i))%M;
    }   
    if (tabla_cartas[posicion].id == nuevo.id){
        tabla_sobres[posicion].cantidad += 1;
    }
    else{
        tabla_sobres[posicion].id = nuevo.id;
        tabla_sobres[posicion].cantidad += 1;
        for (int j = 0; j < 10; j++){
            tabla_sobres[posicion].cartas[j] = nuevo.cartas[j];
        }
    } 
}



/***
 * Funcion verifica si existe una determinada carta en la tabla
 * Recibe un entero id 
 * Retorna la cantidad de cartas de la tabla con el id ingresado
*/

int Tienda::tengo_la_carta(int id){
    int posicion = hasheo(id)%M;
    int inicio = posicion;
    for (int i = 0; tabla_cartas[posicion].id != NUNCA_USADA && tabla_cartas[posicion].id != id; i++){
        posicion = (inicio + resolucion_de_colisiones_Cartas(id, i))%M;
    }
    if (tabla_cartas[posicion].id == id){
       return tabla_cartas[posicion].cantidad;
    }
    else{
        return 0;
    }
}



/***
 * Funcion que imprime por pantalla las cartas que tiene la tabla
 * No recibe ningun parametro
 * No retorna nada
*/

void Tienda::mostrar_cartas(){
    for (int i = 0; i < M; i++){
        if (tabla_cartas[i].id != NUNCA_USADA){
            if (tabla_cartas[i].cantidad > 0){
                std::cout << tabla_cartas[i].id << " " << tabla_cartas[i].nombre << " " << tabla_cartas[i].ataque << " " 
                << tabla_cartas[i].defensa << " " << tabla_cartas[i].precio << " " << tabla_cartas[i].cantidad << "\n";
            }            
        }
    }
}



/***
 * Funcion que imprime por pantalla las id de los sobres que tiene la tabla
 * No recibe ningun parametro
 * No retorna nada
*/

void Tienda::mostrar_sobres(){
    for (int i = 0; i < M; i++){
        if (tabla_sobres[i].id != NUNCA_USADA){
            for (int j = 0; j < tabla_sobres[i].cantidad; j++){
                std::cout << tabla_sobres[i].id << "\n";
            }            
        }
    }
}



/***
 * Funcion que vende una carta de la tabla, dado una id
 * Recibe un entero id y si encuentra una carta con esa id la vende
 * en caso contrario, imprime por pantalla: "Ese id no se encuentra!"
 * No retorna nada
*/

void Tienda::vender_carta(int id){
    int posicion = hasheo(id)%M;
    int inicio = posicion;
    for (int i = 0; tabla_cartas[posicion].id != NUNCA_USADA && tabla_cartas[posicion].id != id; i++){
        posicion = (inicio + resolucion_de_colisiones_Cartas(id, i))%M;
    }
    if (tabla_cartas[posicion].id == id && tabla_cartas[posicion].cantidad > 0){
        tabla_cartas[posicion].cantidad -= 1;
        n_cartas -= 1;
        dinero_recaudado += tabla_cartas[posicion].precio;
        std::cout << "Vendida la carta!\n";
    }
    else{
        std::cout << "Ese id no se encuentra!\n";
    }
}



/***
 * Funcion que vende un sobre de la tabla, dado una id
 * Recibe un entero id y si encuentra un sobre con esa id lo vende
 * en caso contrario, imprime por pantalla: "Ese id no se encuentra!"
 * No retorna nada
*/

void Tienda::vender_sobre(int id){
    int posicion = hasheo(id)%M;
    int inicio = posicion;
    for (int i = 0; tabla_sobres[posicion].id != NUNCA_USADA && tabla_sobres[posicion].id != id; i++){
        posicion = (inicio + resolucion_de_colisiones_Sobres(id, i))%M;
    }
    if (tabla_sobres[posicion].id == id && tabla_sobres[posicion].cantidad > 0){
        tabla_sobres[posicion].cantidad -= 1;
        n_sobres -= 1;
        dinero_recaudado += 1000;
        for (int j = 0; j < 10; j++){
            std::cout << tabla_sobres[posicion].cartas[j].id << " " << tabla_sobres[posicion].cartas[j].nombre << " " 
            << tabla_sobres[posicion].cartas[j].ataque << " " << tabla_sobres[posicion].cartas[j].defensa << " " 
            << tabla_sobres[posicion].cartas[j].precio << "\n";
        }
        std::cout << "Vendido el sobre!\n";
    }
    else{
        std::cout << "Ese id no se encuentra!\n";
    }
}



/***
 * Funcion que imprime por pantalla el dinero recaudado hasta ese momento
 * No recibe ningun parametro
 * No retorna nada
*/

void Tienda::mostrar_dinero(){
    std::cout << dinero_recaudado << "\n";
}