#include "Tienda.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>


using namespace std;

/***
 * Funcion lee la informacion de un archivo de texto
 * No recibe ningun parametro
 * Retorna un objeto de la clase tienda al cual se le asigno la
 * informacion del archivo de texto
*/


Tienda leertxt (){
    Tienda tienda;
    Carta temp_carta;
    Sobre temp_sobre;
    int nCartas,nSobres;
    ifstream in;

    
    in.open("Tienda.txt");
    if (!in.is_open()){
        cerr << "error al abrir el archivo" << endl;
    }
    
    //Leer y agregar cartas
    in >> nCartas;
    tienda.crear_Tabla_Cartas(nCartas);
    for (int i = 0; i < nCartas; i++){
        in >> temp_carta.id;
        in >> temp_carta.nombre;
        in >> temp_carta.ataque;
        in >> temp_carta.defensa;
        in >> temp_carta.precio;
        tienda.agregar_Carta(temp_carta);
    }


    //Leer y agregar sobres
    in >> nSobres;
    
    tienda.crear_Tabla_Sobres(nSobres);
    for (int j = 0; j < nSobres; j++){
        in >> temp_sobre.id;
        for (int k = 0; k < 10; k++){
            in >> temp_sobre.cartas[k].id;
            in >> temp_sobre.cartas[k].nombre;
            in >> temp_sobre.cartas[k].ataque;
            in >> temp_sobre.cartas[k].defensa;
            in >> temp_sobre.cartas[k].precio;
            temp_sobre.cartas[k].cantidad = 1;
        }
        tienda.agregar_Sobre(temp_sobre);
    }
    in.close();
    return tienda;
}






int main(){

    //Variable con la cual se manejan ambas tablas de hashing

    Tienda tienda;
    tienda = leertxt();

    //Variables que el programa recibira por consola
    int entrada;
    int id;


    //Ciclo de consultas de la tienda
    //Puede mostrar el dinero recaudado, las cartas y los sobres,
    //tambien puede vender las cartas y los sobres
    while (entrada != 6){
        cin >> entrada;
        if (entrada == 1){
            tienda.mostrar_dinero();
        }
        else if (entrada == 2){
            tienda.mostrar_cartas();
        }
        else if (entrada == 3){
            tienda.mostrar_sobres();
        }
        else if (entrada == 4){
            cin >> id;
            tienda.vender_carta(id);
        }
        else if (entrada == 5){
            cin >> id;
            tienda.vender_sobre(id);
        }
    }
    
    cout << "Fin del programa\n";
    return 0;
}

