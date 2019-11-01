#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <math.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <gpgme.h>
#include <openssl/ssl.h>


std::vector<std::thread> v_hilos;
int salir = 0;

std::string tipoClave(std::string tipo){
  std::string todos = "abcdefghijklmnñopqrstuvwxyz0123456789";
  std::string minusculas = "abcdefghijklmnñopqrstuvwxyz";
  std::string numeros = "0123456789";
  if(tipo == "minus"){
      return minusculas;
  }else if(tipo == "num"){
      return numeros;
  }else if(tipo == "todo"){
      return todos;
  }
}

void probarClave(std::string clave, std::string nombre_documento){

    std::string comando = "gpg --batch --passphrase " + clave + " --yes -d " + nombre_documento + " >> resultado.txt";
    int status = system(comando.c_str());
    if (status == 0){
        std::cout << "\n************* Clave encontrada!: " << clave << " *************\n" << std::endl;
        salir=1;
    }
}

void generarClaves(std::string nombre_documento, std::string espacio_clave, int base, int inicio, int fin){

    int int_entera=0;
    int int_resto=0;
    std::string clave;

    for(int i = inicio; i<= fin & !salir; i++){
        int_entera = i;
        int_resto = i%base;
        clave = espacio_clave[int_resto];     
            while(int_entera > base){
                int_entera = int_entera/base;
                int_resto = int_entera%base;
                clave = espacio_clave[int_resto]+clave;            
            }
        probarClave(clave, nombre_documento);
    }
}

int main(int argc, char const *argv[]) {

    if(argc != 5) {
        std::cout << "ERROR, se debe ejecutar con las opciones <tamaño_clave> <nombre_documento> <caracteres_usar> <num_hilos>" <<std::endl;
        exit(EXIT_FAILURE);
    }

    int i;
    int tamanio_clave = atoi(argv[1]);
    std::string nombre_documento = argv[2];
    std::string tipo = argv[3];
    int num_hilos = atoi(argv[4]);    

    std::string espacio_clave = tipoClave(tipo);
    int base = espacio_clave.length();
    long espacio_prueba = pow(base, tamanio_clave);
    int tamanio_prueba = espacio_prueba/num_hilos;

    for(i=0; i<num_hilos-1; i++){
        v_hilos.push_back(std::thread(generarClaves, nombre_documento, espacio_clave, base, tamanio_prueba*i, tamanio_prueba*(i+1)-1));
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }
    if(i==num_hilos-1){
        v_hilos.push_back(std::thread(generarClaves, nombre_documento, espacio_clave, base, tamanio_prueba*i, espacio_prueba));
    }

    for_each(v_hilos.begin(), v_hilos.end(), std::mem_fn(&std::thread::join));
  
    return 0;
} 