#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <math.h>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>


std::vector<std::thread> v_hilos;
int salir = 0;

std::string tipoClave(int tipo){
  std::string todos = "abcdefghijklmnñopqrstuvwxyz0123456789";
  std::string minusculas = "abcdefghijklmnñopqrstuvwxyz";
  std::string numeros = "0123456789";
  if(tipo==1){
      return minusculas;
  }else if(tipo == 2){
      return numeros;
  }else if(tipo == 0){
      return todos;
  }
}

void probarClaves(std::string pass, std::string espacio_clave, int base, int inicio, int fin, int a){

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
        //std::cout<<"Clave " << i << ":" << clave << std::endl;
        if(pass.compare(clave)==0){
            std::cout << "Clave encontrada!: " << clave << std::endl;
            salir=1;
            break;
        }
    }

}

int main(int argc, char const *argv[]) {
    std::string pass;
    int tipo, i;
    int num_hilos = atoi(argv[1]);
 
    std::cout<<"Dime la contraseña a crackear:" << std::endl;
    std::cin>> pass;
    std::cout<<"Dime el espacio de claves a probar (Minusculas -> 1, Numeros -> 2, Todo -> 0):" << std::endl;
    std::cin>> tipo;


    std::string espacio_clave = tipoClave(tipo);
    int base = espacio_clave.length();
    int tamanio_clave = pass.length();
    long espacio_prueba = pow(base, tamanio_clave);
    int tamanio_prueba = espacio_prueba/num_hilos;

    for(i=0; i<num_hilos-1; i++){
        v_hilos.push_back(std::thread(probarClaves, pass, espacio_clave, base, tamanio_prueba*i, tamanio_prueba*(i+1)-1, i));
        std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }
    if(i==num_hilos-1){
        v_hilos.push_back(std::thread(probarClaves, pass, espacio_clave, base, tamanio_prueba*i, espacio_prueba, i));
    }

    for_each(v_hilos.begin(), v_hilos.end(), std::mem_fn(&std::thread::join));
  
    return 0;
} 
