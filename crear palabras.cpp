#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Estructura para guardar los datos de cada palabra
struct Palabra {
    string palabra;
    string traduccion;
    string funcionalidad;
};

// Función para cargar palabras desde el archivo
vector<Palabra> cargarPalabrasDesdeArchivo(const string& nombreArchivo) {
    vector<Palabra> palabras;
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string palabra, traduccion, funcionalidad;

        getline(ss, palabra, ';');
        getline(ss, traduccion, ';');
        getline(ss, funcionalidad);

        palabras.push_back({palabra, traduccion, funcionalidad});
    }

    archivo.close();
    return palabras;
}

// Función para verificar si la palabra ya existe
bool palabraExiste(const vector<Palabra>& palabras, const string& palabraNueva) {
    for (const auto& p : palabras) {
        if (p.palabra == palabraNueva) {
            return true;
        }
    }
    return false;
}

// Función para guardar una palabra en el archivo
void guardarPalabraEnArchivo(const string& nombreArchivo, const Palabra& nuevaPalabra) {
    ofstream archivo(nombreArchivo, ios::app);
    archivo << nuevaPalabra.palabra << ";" 
            << nuevaPalabra.traduccion << ";" 
            << nuevaPalabra.funcionalidad << endl;
    archivo.close();
}

int main() {
    string nombreArchivo = "diccionario.txt";
    vector<Palabra> palabras = cargarPalabrasDesdeArchivo(nombreArchivo);

    Palabra nuevaPalabra;
    cout << "Ingrese la palabra: ";
    getline(cin, nuevaPalabra.palabra);

    if (palabraExiste(palabras, nuevaPalabra.palabra)) {
        cout << "La palabra ya existe en el diccionario.\n";
    } else {
        cout << "Ingrese la traduccion: ";
        getline(cin, nuevaPalabra.traduccion);

        cout << "Ingrese la funcionalidad: ";
        getline(cin, nuevaPalabra.funcionalidad);

        guardarPalabraEnArchivo(nombreArchivo, nuevaPalabra);
        cout << "Palabra guardada exitosamente.\n";
    }

    return 0;
}

