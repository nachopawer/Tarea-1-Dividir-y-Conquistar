#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para leer una matriz desde un archivo
void leerMatrizDesdeArchivo(const string& nombreArchivo, int**& matriz, int tamaño) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }
    
    matriz = new int*[tamaño];
    for (int i = 0; i < tamaño; ++i) {
        matriz[i] = new int[tamaño];
        for (int j = 0; j < tamaño; ++j) {
            archivo >> matriz[i][j];
        }
    }
    archivo.close();
}

// Función para guardar una matriz en un archivo
void guardarMatrizEnArchivo(const string& nombreArchivo, int** matriz, int tamaño) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        exit(1);
    }

    for (int i = 0; i < tamaño; ++i) {
        for (int j = 0; j < tamaño; ++j) {
            archivo << matriz[i][j] << " ";
        }
        archivo << endl;
    }
    archivo.close();
}

// Función para multiplicar matrices
void multiplicarMatricesOptimizado(int** A, int** B, int**& C, int tamaño) {
    C = new int*[tamaño];
    for (int i = 0; i < tamaño; ++i) {
        C[i] = new int[tamaño]();
    }

    for (int i = 0; i < tamaño; ++i) {
        for (int j = 0; j < tamaño; ++j) {
            for (int k = 0; k < tamaño; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // Nombres de los archivos de entrada y salida
    int tamaños[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int cantidadTamaños = sizeof(tamaños) / sizeof(tamaños[0]);

    for (int i = 0; i < cantidadTamaños; ++i) {
        int tamaño = tamaños[i];
        string archivoA = "Matriz." + to_string(tamaño) + "x" + to_string(tamaño) + ".n1.txt";
        string archivoB = "Matriz." + to_string(tamaño) + "x" + to_string(tamaño) + ".n2.txt";
        string archivoResultado = "MatrizMultiplicada." + to_string(tamaño) + "x" + to_string(tamaño) + ".txt";

        // Leer las matrices desde los archivos
        int** A;
        int** B;
        leerMatrizDesdeArchivo(archivoA, A, tamaño);
        leerMatrizDesdeArchivo(archivoB, B, tamaño);

        // Crear la matriz de resultado
        int** C;

        // Medir el tiempo de multiplicación
        auto inicio = high_resolution_clock::now();
        multiplicarMatricesOptimizado(A, B, C, tamaño);
        auto fin = high_resolution_clock::now();

        // Guardar el resultado en un archivo
        guardarMatrizEnArchivo(archivoResultado, C, tamaño);

        // Calcular y mostrar el tiempo de multiplicación
        auto duracion = duration_cast<nanoseconds>(fin - inicio);
        cout << "Tiempo de multiplicación para matrices de " << tamaño << "x" << tamaño << ": " 
             << double((duracion.count())/1e9) << " segundos." << endl;

        // Liberar la memoria
        for (int i = 0; i < tamaño; ++i) {
            delete[] A[i];
            delete[] B[i];
            delete[] C[i];
        }
        delete[] A;
        delete[] B;
        delete[] C;
    }

    return 0;
}
