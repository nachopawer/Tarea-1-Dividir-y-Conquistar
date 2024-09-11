#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>   // Para medir el tiempo
#include <algorithm> // Para swap()

using namespace std;
using namespace std::chrono;

int partition(vector<int> &vec, int low, int high) {
    int pivot = vec[high]; // Selecciona el último elemento como pivote
    int i = (low - 1); // Índice del elemento más pequeño

    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]); // Intercambia vec[i] con vec[j]
        }
    }

    swap(vec[i + 1], vec[high]); // Coloca el pivote en su lugar correcto
    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high); // Índice de partición

        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

void ordenarDatosDesdeArchivo(const string& archivoEntrada, const string& archivoSalida) {
    ifstream entrada(archivoEntrada);
    if (!entrada) {
        cerr << "Error al abrir el archivo de entrada." << endl;
        return;
    }

    vector<int> numeros;
    int numero;
    while (entrada >> numero) {
        numeros.push_back(numero);
    }
    entrada.close();

    auto inicioTotal = high_resolution_clock::now();

    auto inicioOrdenamiento = high_resolution_clock::now();

    quickSort(numeros, 0, numeros.size() - 1);

    auto finOrdenamiento = high_resolution_clock::now();
    auto duracionOrdenamiento = duration_cast<nanoseconds>(finOrdenamiento - inicioOrdenamiento);

    ofstream salida(archivoSalida);
    if (!salida) {
        cerr << "Error al crear el archivo de salida." << endl;
        return;
    }

    for (size_t i = 0; i < numeros.size(); i++) {
        salida << numeros[i];
        if (i < numeros.size() - 1) {
            salida << endl;
        }
    }
    salida.close();

    auto finTotal = high_resolution_clock::now();
    auto duracionTotal = duration_cast<nanoseconds>(finTotal - inicioTotal);

    cout << "Los números ordenados del archivo " << archivoEntrada << " han sido guardados en el archivo '" << archivoSalida << "'." << endl;
    cout << "Tiempo de ordenamiento: " << double((duracionOrdenamiento.count())/1e9) << " segundos." << endl;
    cout << endl;
}

int main() {

    ordenarDatosDesdeArchivo("DatosInvertidos999.txt", "DatosOrdenados1.txt");
    ordenarDatosDesdeArchivo("DatosInvertidos9999.txt", "DatosOrdenados2.txt");
    ordenarDatosDesdeArchivo("DatosInvertidos99999.txt", "DatosOrdenados3.txt");
    ordenarDatosDesdeArchivo("DatosInvertidos999999.txt", "DatosOrdenados4.txt");
    cout << endl; 

    ordenarDatosDesdeArchivo("DatosAleatorios999.txt", "DatosOrdenados5.txt");
    ordenarDatosDesdeArchivo("DatosAleatorios9999.txt", "DatosOrdenados6.txt");
    ordenarDatosDesdeArchivo("DatosAleatorios99999.txt", "DatosOrdenados7.txt");
    ordenarDatosDesdeArchivo("DatosAleatorios999999.txt", "DatosOrdenados8.txt");
    cout << endl;
    

    ordenarDatosDesdeArchivo("DatosOrdenados999.txt", "DatosOrdenados9.txt");
    ordenarDatosDesdeArchivo("DatosOrdenados9999.txt", "DatosOrdenados10.txt");
    ordenarDatosDesdeArchivo("DatosOrdenados99999.txt", "DatosOrdenados11.txt");
    ordenarDatosDesdeArchivo("DatosOrdenados999999.txt", "DatosOrdenados12.txt");

    return 0;
}
