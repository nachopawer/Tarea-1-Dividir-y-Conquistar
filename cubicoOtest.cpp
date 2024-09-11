#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para leer una matriz desde un archivo
vector<vector<int>> leerMatrizDesdeArchivo(const string& archivo) {
    ifstream entrada(archivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo " << archivo << endl;
        exit(1);
    }

    vector<vector<int>> matriz;
    int valor;
    string linea;

    while (getline(entrada, linea)) {
        vector<int> fila;
        istringstream ss(linea);
        while (ss >> valor) {
            fila.push_back(valor);
        }
        matriz.push_back(fila);
    }

    entrada.close();
    return matriz;
}

// Función para multiplicar dos matrices usando un algoritmo iterativo cúbico optimizado
vector<vector<int>> multiplicarMatricesOptimizado(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    // Multiplicación de matrices con optimización para el acceso a memoria
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int suma = 0;
            for (int k = 0; k < n; ++k) {
                suma += A[i][k] * B[k][j];
            }
            C[i][j] = suma;
        }
    }

    return C;
}

// Función para guardar una matriz en un archivo
void guardarMatrizEnArchivo(const string& archivo, const vector<vector<int>>& matriz) {
    ofstream salida(archivo);
    if (!salida) {
        cerr << "Error al crear el archivo " << archivo << endl;
        exit(1);
    }

    for (const auto& fila : matriz) {
        for (size_t i = 0; i < fila.size(); ++i) {
            salida << fila[i];
            if (i < fila.size() - 1) salida << " ";
        }
        salida << endl;
    }

    salida.close();
}

int main() {
    // Nombres de los archivos de entrada y salida
    vector<int> tamaños = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

    for (int tamaño : tamaños) {
        string archivoA = "Matriz." + to_string(tamaño) + "x" + to_string(tamaño) + ".n1.txt";
        string archivoB = "Matriz." + to_string(tamaño) + "x" + to_string(tamaño) + ".n2.txt";
        string archivoResultado = "MatrizMultiplicada." + to_string(tamaño) + "x" + to_string(tamaño) + ".txt";

        // Leer las matrices desde los archivos
        auto A = leerMatrizDesdeArchivo(archivoA);
        auto B = leerMatrizDesdeArchivo(archivoB);

        // Medir el tiempo de multiplicación
        auto inicio = high_resolution_clock::now();
        auto C = multiplicarMatricesOptimizado(A, B);
        auto fin = high_resolution_clock::now();

        // Guardar el resultado en un archivo
        guardarMatrizEnArchivo(archivoResultado, C);

        // Calcular y mostrar el tiempo de multiplicación
        auto duracion = duration_cast<nanoseconds>(fin - inicio);
        cout << "Tiempo de multiplicación para matrices de " << tamaño << "x" << tamaño << ": " 
             << double((duracion.count())/1e9) << " segundos." << endl;
    }

    return 0;
}
