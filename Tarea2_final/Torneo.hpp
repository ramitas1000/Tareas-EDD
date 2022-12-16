#ifndef Torneo_hpp
#define Torneo_hpp
#include <cmath>
#include <math.h>
#include "Equipo.hpp"


class Torneo{
    private:
        int nEquipos,nRondas,ronda_actual;
        Equipo* arreglo_original;
        Equipo** bracket;
    public:
        Torneo();
        void crear_torneo(Equipo* equipos,int n);
        void imprimir_bracket();
        void avanzar_ronda();
        bool terminado();
        void poder_mayor_k(int k);
};
#endif