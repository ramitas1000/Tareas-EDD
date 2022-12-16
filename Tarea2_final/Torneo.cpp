#include "Torneo.hpp"
#include <iostream>
#include <string>


/***
 * Funcion auxiliar (no es de la clase Torneo) que recibe dos equipos por referencia y retorna false si el equipo
 * b tiene mas poder que el equipo a y retorna true en caso contrario
*/

bool batallar(Equipo &a, Equipo &b){
    if (b.calcular_poder() > a.calcular_poder()){
        return false;
    }
    else{
        return true;
    }
}

/***
 * Constructor de la clase
 * Es solo para crear un objeto de la clase
*/

Torneo::Torneo(){    
}

/***
 * Funcion crear torneo
 * Recibe un arreglo de los equipos participantes junto con la cantidad de estos
 * Luego crea el bracket completo (incluido el ganador), ya que esa info se puede saber
 * antes de las partidas
 * No retorna nada
*/

void Torneo::crear_torneo(Equipo* equipos,int n){
    nEquipos = n;
    nRondas = log2(n);
    ronda_actual = 1;
    arreglo_original = equipos;
    bracket = new Equipo*[nRondas+1];
    Equipo* arreglo_teams;
    int help;

    //crea el bracket completo
    for (int i = 0; i < nRondas+1; i++){
        help = nEquipos/pow(2,i);
        arreglo_teams = new Equipo[help];
        bracket[i] = arreglo_teams;
        delete [] arreglo_teams;
    }

    //añade todos los teams al las "hojas"
    for (int j = 0; j < nEquipos; j++){
        bracket[0][j] = equipos[j];
    }

    //añadir los teams que ganan (ya que desde el pricipio se sabe eso)
    for (int k = 1; k <= nRondas; k++){
        help = nEquipos/pow(2,k);
        for (int l = 0; l < help; l++){
            bracket[k][l] = bracket[k-1][l];
        }
    }
}   

/***
 * Funcion que imprime el bracke de la ronda actual
 * Recorre el arreglo de arreglos de Equipo y lo imprime dependiendo de la ronda actual
*/

void Torneo::imprimir_bracket(){
    int help,par_equipo;
    if (ronda_actual > nRondas){
        std::cout << bracket[nRondas][0].get_capitan() << " " << bracket[nRondas][0].calcular_poder() << "\n";
    }    
    for (int i = ronda_actual-1; i >= 0; i--){
        par_equipo = 0;
        help = nEquipos/pow(2,i+1);
        std::cout << "| ";
        for (int j = 0; j < help; j++){
            std::cout << bracket[i][par_equipo].get_capitan() << " " << bracket[i][par_equipo].calcular_poder() << " vs " << 
            bracket[i][par_equipo+1].get_capitan() << " " << bracket[i][par_equipo+1].calcular_poder();
            std::cout << " | ";
            par_equipo += 2;
        }
        std::cout << "\n";
    }
}

/***
 * Avanza una ronda en el torneo
*/

void Torneo::avanzar_ronda(){
    ronda_actual += 1;
}

/***
 * Funcion que verifica si el torneo puede continuar
*/

bool Torneo::terminado(){
    if (ronda_actual > (nRondas)){
        return true;
    }
    else{
        return false;
    }
}

/***
 * Funcion que recibe un entero y que imprime todos los equipos con
 * un poder mayor o igual a ese entero
*/

void Torneo::poder_mayor_k(int k){
    for (int i = 0; i < nEquipos; i++){
        if(arreglo_original[i].calcular_poder() >= k){
            arreglo_original[i].imprimir_equipo();
        }
    }
}