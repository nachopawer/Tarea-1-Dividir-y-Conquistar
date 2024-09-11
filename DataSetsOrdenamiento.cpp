#include <bits/stdc++.h>
using namespace std;

void generarDatosAleatorios(const string& nombreArchivo, int rangoInferior, int rangoSuperior, int cantidad) {
    int totalNumeros = rangoSuperior - rangoInferior + 1; // Total de números posibles en el rango
    if (cantidad > totalNumeros) {
        cerr << "Error: La cantidad solicitada excede el rango de números posibles." << endl;
        return;
    }

    int* numeros = new int[totalNumeros];

    for (int i = 0; i < totalNumeros; i++) {
        numeros[i] = rangoInferior + i;
    }

    srand(time(0));

    random_shuffle(numeros, numeros + totalNumeros);

    ofstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "Error al crear el archivo." << endl;
        delete[] numeros;  // Liberamos el arreglo dinámico en caso de error
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        archivo << numeros[i];  // Escribimos el número

        if (i < cantidad - 1) {
            archivo << endl;
        }
    }

    archivo.close();

    delete[] numeros;

    cout << "Los números han sido guardados en el archivo '" << nombreArchivo << "'." << endl;
}


void generarDatosOrdenados(const string& nombreArchivo, int cantidad, int rangoInferior, int rangoSuperior) {

    vector<int> numeros(cantidad);

    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < cantidad; i++) {
        numeros[i] = rangoInferior + rand() % (rangoSuperior - rangoInferior + 1);
    }

    sort(numeros.begin(), numeros.end());

    ofstream archivo(nombreArchivo);

    if (!archivo) {
        cout << "Error al crear el archivo." << endl;
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        archivo << numeros[i];  // Escribir el número
        if (i < cantidad - 1) {
            archivo << endl;    // Añadir un salto de línea solo si no es el último número
        }
    }

    archivo.close();

    cout << "Los números aleatorios ordenados han sido guardados en el archivo '" << nombreArchivo << "'." << endl;
}


void generarDatosOrdenadosInverso(const string& nombreArchivo, int totalNumeros, int rangoInferior, int rangoSuperior) {
    int* numeros = new int[totalNumeros];

    srand(time(0));

    for (int i = 0; i < totalNumeros; i++) {
        numeros[i] = rangoInferior + rand() % (rangoSuperior - rangoInferior + 1);
    }

    sort(numeros, numeros + totalNumeros, greater<int>());

    ofstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "Error al crear el archivo." << endl;
        delete[] numeros;  // Liberamos el arreglo dinámico en caso de error
        return;
    }

    for (int i = 0; i < totalNumeros; i++) {
        archivo << numeros[i];
        if (i < totalNumeros - 1) {
            archivo << endl;
        }
    }

    archivo.close();

    delete[] numeros;

    cout << "Los números ordenados en orden inverso han sido guardados en el archivo '" << nombreArchivo << "'." << endl;
}

int main() {
    generarDatosAleatorios("DatosAleatorios999.txt", 1, 9999999, 999); 
    generarDatosAleatorios("DatosAleatorios9999.txt", 1, 9999999, 9999);
    generarDatosAleatorios("DatosAleatorios99999.txt", 1, 9999999, 99999);
    generarDatosAleatorios("DatosAleatorios999999.txt", 1, 9999999, 999999);

    generarDatosOrdenados("DatosOrdenados999.txt", 999, 1, 9999999);
    generarDatosOrdenados("DatosOrdenados9999.txt", 9999, 1, 9999999);
    generarDatosOrdenados("DatosOrdenados99999.txt", 99999, 1, 9999999);
    generarDatosOrdenados("DatosOrdenados999999.txt", 999999, 1, 9999999);

    generarDatosOrdenadosInverso("DatosInvertidos999.txt", 999, 1, 9999999);
    generarDatosOrdenadosInverso("DatosInvertidos9999.txt", 9999, 1, 9999999);
    generarDatosOrdenadosInverso("DatosInvertidos99999.txt", 99999, 1, 9999999);
    generarDatosOrdenadosInverso("DatosInvertidos999999.txt", 999999, 1, 9999999);

    return 0;
}
