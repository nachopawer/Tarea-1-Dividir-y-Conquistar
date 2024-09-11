#include <iostream>
#include <fstream>
#include <cstdlib>   // Para la función rand() y srand()
#include <ctime>     // Para la función time()
#include <cmath>     // Para la función pow()


void generar_y_guardar_matriz(int n, int parte) {

    std::ofstream archivo;
    archivo.open("Matriz." + std::to_string(n) + "x" + std::to_string(n) + ".n" + std::to_string(parte) + ".txt");

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int numero_aleatorio = rand() % 100; 
            archivo << numero_aleatorio << " ";
        }
        archivo << std::endl; 
    }

    archivo.close(); 
    std::cout << "Matriz " << n << "x" << n << " n" << parte << " creada." << std::endl;
}

int main() {

    srand(time(0));

    for (int i = 1; i <= 10; ++i) {  
        int n = pow(2, i);
        for (int j = 1; j <= 2; ++j) {  
            generar_y_guardar_matriz(n, j);
        }
    }

    return 0;
}
