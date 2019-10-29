#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <math.h>

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

int cambioBase(std::string pass, int tipo_clave){
    std::string espacio_clave = tipoClave(tipo_clave);
    int base = espacio_clave.length();
    int tamanio_clave = pass.length();
    long espacio_prueba = pow(base, tamanio_clave);
    std::cout<<"Espacio_prueba: "<< espacio_prueba << " Longitud contraseña " << tamanio_clave << " base "<< base;
    int int_entera=0;
    int int_resto=0;
    std::string clave;

    for(int i = 0; i< espacio_prueba; i++){
        int_resto = i%base;
        clave = espacio_clave[int_resto];
        int_entera = i/base;
        if(int_entera <=base){
            clave = espacio_clave[int_entera]+clave;
        }else{
            while(int_entera > base){
                int_entera = int_entera/base;
                int_resto = int_entera%base;
                clave = espacio_clave[int_resto]+clave;            
            }
            clave = espacio_clave[int_entera]+clave;
        }
        std::cout<<"Clave " << i << ":" << clave << std::endl;    

    }

}

int main(int argc, char const *argv[]) {
    std::string pass;
    int tipo;

    std::cout<<"Dime la contraseña a crackear:" << std::endl;
    std::cin>> pass;
    std::cout<<"Dime el espacio de claves a probar (Minusculas -> 1, Numeros -> 2, Todo -> 0):" << std::endl;
    std::cin>> tipo;
    cambioBase(pass, tipo);

  
    return 0;
} 
