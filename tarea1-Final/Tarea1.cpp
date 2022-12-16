#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*****
 * Structura Resgistro
 *      Contiene enteros con el dia, mes , año y palabras por minuto (ppm), un float con la precision y 
 *      un arreglo de caracteres con el rol de la persona que realizo ese registro 
 *****/
struct Registro {
    int dia, mes, anio;
    char rol[12];
    int ppm;
    float presicion;
};

/*****
 * Structura Estudiante
 *       contiene un arreglo de caracteres con el rol de un estudiante, dos strings con el nombre y el apellido del estudiante
 *       y un entero con su paralelo
 *****/

struct Estudiante {
    char rol[12];
    string nombre;
    string apellido;
    int paralelo;
};

/*****
 * Structura Consulta
 *       Contiene cuatro enteros que son pedidos en una consulta
 *       Esta estructura se utiliza para hacer multuiples consultas
 *****/

struct Consultas{
    int tipo,mes,dia,anio;
};

/*****
 * Structura Salida
 *       Contiene dos strings con el nombre y el apellido de un estudiante
 *       Esta estructura se utiliza para imprimir correctamente la salida del programa
 *****/

struct Salida{
    string nombre;
    string apellido;
};


/*****
 * Funcion leerbinario
 *       Recibe un entero por referencia, luego abre un archivo y guarda los datos leidos en un arreglo de registros
 *       Retorna dicho arreglo de Registros y tambien modifica el entero entregado para saber el tamaño de ese arreglo
 *****/


Registro *leerbinario(int &n) {
    ifstream in;
    in.open("registros.dat", ios::binary); //Se abre el archivo y se verifica que se abrio correctamente
    if(!in.is_open()){
        cerr << "Error al abrir el archivo" << endl;
        return NULL;
    }

    in.read((char *)&n, sizeof(int));

    Registro *arr_reg = new Registro[n]; //se pide memoria dinamica ya que el tamaño de este arreglo es variable
    in.read((char *)arr_reg, n * sizeof(Registro));
    in.close(); // Se cierra el archivo

    return arr_reg;
}

/*****
 * Funcion leertxt
 *       Recibe un entero por referencia al que se le asignaran la canteidad de lineas del archivo que debe leer
 *       Luego vuelve a abrir y leer el archivo para almacenar sus datos en un arreglo de estudiantes, sabiendo cuantas lineas tiene el archivo
 *       Retorna un arreglo de Estudiantes y modifica el entero entregado para saber el tamaño del arreglo que retorna
 *****/

Estudiante *leertxt(int &cant_lineas) {
    ifstream in;
    in.open("estudiantes.txt"); // leer cantidad de lineas
    //Se abre el archivo y se verifica que se abrio correctamente
    if(!in.is_open()){
        cerr << "Error al abrir el archivo" << endl;
        return NULL;
    }
    string linea;
    
    while (in.peek() != EOF){
        getline(in,linea);
        cant_lineas++;
    }    
    in.close();

    Estudiante *arr_est = new Estudiante[cant_lineas]; //se pide memoria dinamica ya que el tamaño de este arreglo es variable

    ifstream in_dos; 
    //Se vuelve a abrir el archivo, se verifica que se abrio correctamente y se lee la info sabiendo lacantida de lineas
    // del archivo
    in_dos.open("estudiantes.txt");    
    if(!in_dos.is_open()){
        cerr << "Error al abrir el archivo" << endl;
        return NULL;
    }

    for (int i = 0; i < cant_lineas; i++){
        in_dos >> arr_est[i].rol;
        in_dos >> arr_est[i].nombre;
        in_dos >> arr_est[i].apellido;
        in_dos >> arr_est[i].paralelo;
    }

    in_dos.close();
    return arr_est;
}




int main(){

    //Variables para saber cuantos estudiantes y registros hay, respectivamente
    int n_estudiantes = 0;
    int n_registros = 0;


    //Se llama a las funciones para leer los archivos
    Estudiante *arreglo_estudiante = leertxt(n_estudiantes);
    Registro *arreglo_registro = leerbinario(n_registros);

    
    //Se crea un entero de la cantidad de consultas que se realizaran y se pide por entrada estandar
    int cant_consultas;
    cin >> cant_consultas;

    //Se crean arreglos de consultas y salida luego de saber cuantas consultas se realizaran
    Consultas arreglo_consultas[cant_consultas];
    Salida salida[cant_consultas];

    //Se piden los datos de cada consulta
    for (int n = 0; n < cant_consultas;n++){
        cin >> arreglo_consultas[n].tipo >> arreglo_consultas[n].dia >> arreglo_consultas[n].mes >> arreglo_consultas[n].anio;
    }

    //variables que ayudaran a encontrar los datos que se piden en la consulta
    float mejor_acc;
    int mejor_ppm;
    int pos_acc, pos_ppm;


    //Este ciclo for se repite por cada consulta y en cada repeticion reinicializa las variables que ayudaran a determinar los resultados ded las consultas
    for(int cont = 0; cont < cant_consultas; cont++){
        mejor_ppm = 0;
        mejor_acc = 0;
        pos_acc = 0;
        pos_ppm = 0;

        //Se entra a esta condicion si en la consulta se desea ignorar el dia y el mes de los registros
        if (arreglo_consultas[cont].mes == -1 && arreglo_consultas[cont].dia == -1){
            //Esta condicion verifica si se esta preguntando por la precision o por las ppm
            if(arreglo_consultas[cont].tipo == 0){   
                //Se recorre el arreglo de registros para buscar la mejor presicion y se almacena la posicion de la mejor presicion en los registros    
                for (int i = 0; i < n_registros; i++){
                    if(arreglo_registro[i].presicion > mejor_acc && arreglo_registro[i].anio == arreglo_consultas[cont].anio){             
                        mejor_acc = arreglo_registro[i].presicion;
                        pos_acc = i;
                    }
                }
                //este ciclo hace el cruce de datos del estudiante que realizo el registro con su nombre
                //luego guarda esos nombres en el arreglo de salida
                for (int j = 0; j < n_estudiantes; j++){
                    if (strcmp(arreglo_registro[pos_acc].rol, arreglo_estudiante[j].rol) == 0) { 
                        salida[cont].nombre = arreglo_estudiante[j].nombre;
                        salida[cont].apellido = arreglo_estudiante[j].apellido;
                    }
                }
            }   
            //Se entra a este else si en la consulta se pide la mayor cantidad de palabras por minuto
            //Luego se repiten los pasos de buscar y almacenar la mejor presicion pero con las ppm   
            else{   
                for (int i = 0; i < n_registros; i++){
                    if(arreglo_registro[i].ppm > mejor_ppm && arreglo_registro[i].anio == arreglo_consultas[cont].anio){            
                        mejor_ppm = arreglo_registro[i].ppm;
                        pos_ppm = i;
                    }
                }
                for (int j = 0; j < n_estudiantes; j++){
                    if (strcmp(arreglo_registro[pos_ppm].rol, arreglo_estudiante[j].rol) == 0) {

                        salida[cont].nombre = arreglo_estudiante[j].nombre;
                        salida[cont].apellido = arreglo_estudiante[j].apellido;
                    }
                }            
            }
        }

        //se entra a esta condicion si se desea saber los mejores registros de un mes especifico
        else if (arreglo_consultas[cont].dia == -1){
            //se verifica si en la consulta se desea saber la mejor presicion o la mayor cantidad de palabras por minuto
            if (arreglo_consultas[cont].tipo == 0){
                //Se repiten los pasos de busqueda escritos mas arriba
                for (int i = 0; i < n_registros; i++){
                    if(arreglo_registro[i].presicion > mejor_acc && arreglo_registro[i].mes == arreglo_consultas[cont].mes && arreglo_registro[i].anio == arreglo_consultas[cont].anio){
  
                        mejor_acc = arreglo_registro[i].presicion;
                        pos_acc = i;
                    }
                }
                for (int j = 0; j < n_estudiantes; j++){
                    if (strcmp(arreglo_registro[pos_acc].rol, arreglo_estudiante[j].rol) == 0) {
                        salida[cont].nombre = arreglo_estudiante[j].nombre;
                        salida[cont].apellido = arreglo_estudiante[j].apellido;
                    }
                }
            }


            //se entra a esta condicion si se desea saber la mayor cantidad de palabras por minuto de una consulta
            //y se repiten los pasos de busqueda y cruce de datos detallados mas arriba
            else{
                for (int i = 0; i < n_registros; i++){
                    if(arreglo_registro[i].ppm > mejor_ppm && arreglo_registro[i].mes == arreglo_consultas[cont].mes && arreglo_registro[i].anio == arreglo_consultas[cont].anio){
                        mejor_ppm = arreglo_registro[i].ppm;
                        pos_ppm = i;
                    }
                }
                for (int j = 0; j < n_estudiantes; j++){
                    if (strcmp(arreglo_registro[pos_ppm].rol, arreglo_estudiante[j].rol) == 0) {
                        salida[cont].nombre = arreglo_estudiante[j].nombre;
                        salida[cont].apellido = arreglo_estudiante[j].apellido;
                    }
                }
            }
        }
        
        //Se entra a este else si la consulta desea saber el mejor registro de un dia y mes especificos
        else{
            //primero se verifica el tipo de consulta y luego se realiza la busqueda usandolos mismos pasos 
            //dichos anteriormente
            if (arreglo_consultas[cont].tipo == 0){ 
                for (int i = 0; i < n_registros; i++){
                    if(arreglo_registro[i].presicion > mejor_ppm && (arreglo_registro[i].dia == arreglo_consultas[cont].dia && arreglo_registro[i].mes == arreglo_consultas[cont].mes && arreglo_registro[i].anio == arreglo_consultas[cont].anio)){
                        mejor_acc = arreglo_registro[i].presicion;
                        pos_acc = i;
                    }
                }
                for (int j = 0; j < n_estudiantes; j++){
                    if (strcmp(arreglo_registro[pos_acc].rol, arreglo_estudiante[j].rol) == 0){//arreglo_registro[pos_acc].rol == arreglo_estudiante[j].rol) {
                        
                        salida[cont].nombre = arreglo_estudiante[j].nombre;
                        salida[cont].apellido = arreglo_estudiante[j].apellido;
                    }
                }
            }

            //Se entra en esta condicion si la consulta pide la mayor cantidad de ppm
            else{
                for (int i = 0; i < n_registros; i++){
                    if(arreglo_registro[i].ppm > mejor_ppm && arreglo_registro[i].dia == arreglo_consultas[cont].dia && arreglo_registro[i].mes ==arreglo_consultas[cont]. mes && arreglo_registro[i].anio == arreglo_consultas[cont].anio){
                        mejor_ppm = arreglo_registro[i].ppm;
                        pos_ppm = i;
                    }
                }
                for (int j = 0; j < n_estudiantes; j++){
                    if (strcmp(arreglo_registro[pos_ppm].rol, arreglo_estudiante[j].rol) == 0) {
                        
                        salida[cont].nombre = arreglo_estudiante[j].nombre;
                        salida[cont].apellido = arreglo_estudiante[j].apellido;
                    }
                }
            }
        }  
    }//fin del ciclo de buscar los datos pedidos en las consultas

    //Este ciclo imprime los nombres y apellidos de los estudiantes que fueron alamcenados en el ciclo anterior
    for (int fc = 0; fc < cant_consultas; fc++){
        cout << salida[fc].nombre << " " << salida[fc].apellido << endl;
    }


    //Se libera la memoria dinamica solicitada anteriormente
    delete[] arreglo_registro;
    delete[] arreglo_estudiante;


    //fin del programa
    return 0;
}

