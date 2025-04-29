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

// Funci�n para cargar palabras desde el archivo
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

// Funci�n para verificar si la palabra ya existe
bool palabraExiste(const vector<Palabra>& palabras, const string& palabraNueva) {
    for (const auto& p : palabras) {
        if (p.palabra == palabraNueva) {
            return true;
        }
    }
    return false;
}

// Funci�n para guardar una palabra en el archivo
void guardarPalabraEnArchivo(const string& nombreArchivo, const Palabra& nuevaPalabra) {
    ofstream archivo(nombreArchivo, ios::app);
    archivo << nuevaPalabra.palabra << ";" 
            << nuevaPalabra.traduccion << ";" 
            << nuevaPalabra.funcionalidad << endl;
    archivo.close();
}

// Funci�n leer que imprime el contenido del archivo
 void leer(const string& nombreArchivo) {
     ifstream archivo(nombreArchivo);
 
     // Verificar si el archivo se abre correctamente
     if (!archivo.is_open()) {
         cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
         return;  // Si no se puede abrir, retorna
     }
 
     string linea;
     cout << "\nContenido del archivo:\n";
     while (getline(archivo, linea)) {
         stringstream ss(linea);
         string palabra, traduccion, funcionalidad;
 
         getline(ss, palabra, ';');
         getline(ss, traduccion, ';');
         getline(ss, funcionalidad);
 
         cout << "Palabra: " << palabra << ", Traduccion: " << traduccion << ", Funcionalidad: " << funcionalidad << endl;
     }
 
     archivo.close();
 }

// Funci�n para sobrescribir todas las palabras
void guardarTodasLasPalabras(const string& nombreArchivo, const vector<Palabra>& palabras) {
    ofstream archivo(nombreArchivo, ios::trunc); // Sobrescribe el archivo completo
    for (const auto& p : palabras) {
        archivo << p.palabra << ";" << p.traduccion << ";" << p.funcionalidad << endl;
    }
    archivo.close();
}

// Funci�n para editar una palabra existente
void editarPalabra(vector<Palabra>& palabras, const string& nombreArchivo) {
    string palabraBuscada;
    cout << "Ingrese la palabra que desea editar: ";
    getline(cin, palabraBuscada);

    bool encontrada = false;

    for (auto& p : palabras) {
        if (p.palabra == palabraBuscada) {
            encontrada = true;
            cout << "Palabra encontrada.\n";
            cout << "Traducci�n actual: " << p.traduccion << endl;
            cout << "Funcionalidad actual: " << p.funcionalidad << endl;

            cout << "Ingrese la nueva traducci�n (o presione Enter para no cambiar): ";
            string nuevaTraduccion;
            getline(cin, nuevaTraduccion);
            if (!nuevaTraduccion.empty()) {
                p.traduccion = nuevaTraduccion;
            }

            cout << "Ingrese la nueva funcionalidad (o presione Enter para no cambiar): ";
            string nuevaFuncionalidad;
            getline(cin, nuevaFuncionalidad);
            if (!nuevaFuncionalidad.empty()) {
                p.funcionalidad = nuevaFuncionalidad;
            }

            guardarTodasLasPalabras(nombreArchivo, palabras);
            cout << "Palabra actualizada exitosamente.\n";
            break;
        }
    }

    if (!encontrada) {
        cout << "La palabra no se encontr� en el diccionario.\n";
    }
}

int main() {
    string nombreArchivo = "diccionario.txt";
    vector<Palabra> palabras = cargarPalabrasDesdeArchivo(nombreArchivo);

    Palabra nuevaPalabra;
    cout << "Ingrese la palabra: ";
    getline(cin, nuevaPalabra.palabra);

    if (palabraExiste(palabras, nuevaPalabra.palabra)) {
        cout << "La palabra ya existe en el diccionario.\n";
        // Si ya existe, damos opci�n de editar
        editarPalabra(palabras, nombreArchivo);
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
