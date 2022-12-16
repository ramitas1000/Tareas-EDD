#include "Torneo.hpp"
#include "Equipo.hpp"
#include <iostream>
#include <fstream>

using namespace std;


/***
 * Funcion que recibe un entero por referencia y luego lee la informacion de Equipos.txt
 * retorna un arreglo de equipos
*/

Equipo* leertxt(int &n_equipos){
    int n_personas;
    ifstream in;
    in.open("Equipos.txt");
    if (!in.is_open()){
        cerr << "No se pudo abrir el archivo" << endl;
    }
    in >> n_equipos;
    Equipo* arreglo_teams = new Equipo[n_equipos];
    string nombre, nombre_cap;
    int poder;
    for (int i = 0; i < n_equipos; i++){
        in >> n_personas;
        for (int j = 0; j < n_personas; j++){
            in >> nombre;
            in >> poder;
            arreglo_teams[i].agregar_companero(nombre,poder);
        }       
        in >> nombre_cap;
        arreglo_teams[i].definir_capitan(nombre_cap);
    }
    in.close();
    return arreglo_teams;
}






int main(){
    int n_equipos;
    Equipo* equipos = leertxt(n_equipos);
    Torneo Datos_Pro_Tour;
    int poder_preguntado;
    int entrada;

    Datos_Pro_Tour.crear_torneo(equipos,n_equipos);

    

    
    /***
     * Ciclo que recibe inputs por entrada estandar para ir avanzando en el torneo
    */

    while(!Datos_Pro_Tour.terminado()){
        cin >> entrada;
        if(entrada == 1){
            Datos_Pro_Tour.avanzar_ronda();
        } else if(entrada == 2){
            Datos_Pro_Tour.imprimir_bracket();
        } else if(entrada == 3){
            cin >> poder_preguntado;
            Datos_Pro_Tour.poder_mayor_k(poder_preguntado);
        } else{
            cout << "Entrada invalida." << endl;
        }
    }
    //Torneo terminado.
    Datos_Pro_Tour.imprimir_bracket();
    return 0;
}