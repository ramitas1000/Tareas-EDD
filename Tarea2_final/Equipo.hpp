#ifndef Equipo_hpp
#define Equipo_hpp
#include <string>

class Persona{
    public:
        std::string nombre;
        bool capitan;
        int poder;
        Persona* sig;

        Persona(){
            sig = NULL;
        }

        Persona(std::string nombre, int poder){
            this->nombre = nombre;
            this->poder = poder;
            this->capitan = false;
            this->sig = NULL;
        }
};

class Equipo{
    private:
        Persona* head;
        Persona* tail;
        Persona* curr;
        unsigned int listSize;
        unsigned int pos;
    public:
        Equipo();
        int tamano();
        int agregar_companero(std::string nombre, int poder);
        void definir_capitan(std::string nombre);
        void moveToStart();
        void moveToEnd();
        void prev();
        void next();
        int posActual();
        std::string nombreActual();
        std::string get_capitan();
        int poderActual();
        int calcular_poder();
        void imprimir_equipo();
};

#endif