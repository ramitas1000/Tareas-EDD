#ifndef Tienda_hpp
#define Tienda_hpp
#define OCUPADA 0
#define NUNCA_USADA -1
#define LIBERADA -2
#define M 1000

#include <iostream>
#include <string>

struct Carta{
    int id; //clave
    std::string nombre;
    int ataque;
    int defensa;
    int precio;
    int cantidad;
};

struct Sobre{
    int id; //clave
    Carta cartas[10];
    int cantidad;
};

class Tienda{
    private:
        int dinero_recaudado;

        Carta tabla_cartas[M];
        Sobre tabla_sobres[M];

        int n_cartas,size_cartas;
        int n_sobres,size_sobres;

        float carga_cartas;
        float carga_sobres;

        float carga = 3/5;

    public:
        Tienda();
        int hasheo(int id);
        int resolucion_de_colisiones_Cartas(int id, int n_colisiones);
        int resolucion_de_colisiones_Sobres(int id, int n_colisiones);
        void crear_Tabla_Cartas(int size);
        void crear_Tabla_Sobres(int size);
        void agregar_Carta(Carta nueva);
        void agregar_Sobre(Sobre nuevo);
        int tengo_la_carta(int id);
        void mostrar_cartas();
        void mostrar_sobres();
        void vender_carta(int id);
        void vender_sobre(int id);
        void mostrar_dinero();
};

#endif