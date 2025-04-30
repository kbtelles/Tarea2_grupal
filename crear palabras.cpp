#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

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
	ifstream archivo(nombreArchivo.c_str());
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

// Función leer que imprime el contenido del archivo
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

// Función para sobrescribir todas las palabras
void guardarTodasLasPalabras(const string& nombreArchivo, const vector<Palabra>& palabras) {
    ofstream archivo(nombreArchivo, ios::trunc); // Sobrescribe el archivo completo
    for (const auto& p : palabras) {
        archivo << p.palabra << ";" << p.traduccion << ";" << p.funcionalidad << endl;
    }
    archivo.close();
}

// Función para editar una palabra existente
void editarPalabra(vector<Palabra>& palabras, const string& nombreArchivo) {
    string palabraBuscada;
    cout << "Ingrese la palabra que desea editar: ";
    getline(cin, palabraBuscada);

    bool encontrada = false;

    for (auto& p : palabras) {
        if (p.palabra == palabraBuscada) {
            encontrada = true;
            cout << "Palabra encontrada.\n";
            cout << "Traduccion actual: " << p.traduccion << endl;
            cout << "Funcionalidad actual: " << p.funcionalidad << endl;

            cout << "Ingrese la nueva traducción (o presione Enter para no cambiar): ";
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
        cout << "La palabra no se encontró en el diccionario.\n";
    }
}


// Función para eliminar una palabra
void eliminarPalabra(vector<Palabra>& palabras, const string& nombreArchivo) {
    string palabraBuscada;
    cout << "Ingrese la palabra que desea eliminar: ";
    getline(cin, palabraBuscada);

    auto it = remove_if(palabras.begin(), palabras.end(), [&palabraBuscada](const Palabra& p) {
        return p.palabra == palabraBuscada;
    });

    if (it != palabras.end()) {
        palabras.erase(it, palabras.end());
        guardarTodasLasPalabras(nombreArchivo, palabras);
        cout << "Palabra eliminada exitosamente.\n";
    } else {
        cout << "La palabra no se encontró en el diccionario.\n";
    }
}
/*mi parte David*//////////////////////////////////////////////////////////////////////////////////
void traducirTexto(const vector<Palabra>& palabras) {
    cout << "Ingrese el texto a traducir (finalice con una línea vacía):\n";

    string linea;
    vector<string> textoOriginal;
    while (true) {
        getline(cin, linea);
        if (linea.empty()) break;
        textoOriginal.push_back(linea);
    }

  
    vector<string> estructurasControl = {"if", "for", "while", "switch"};


    vector<string> pilaEstructuras;

    cout << "\nTexto traducido:\n";

    for (string& linea : textoOriginal) {
        stringstream ss(linea);
        string palabra;
        string lineaTraducida;

        while (ss >> palabra) {
            string palabraLimpia = palabra;
           
            palabraLimpia.erase(remove_if(palabraLimpia.begin(), palabraLimpia.end(), ::ispunct), palabraLimpia.end());

            // Buscar la traducción
            auto it = find_if(palabras.begin(), palabras.end(), [&palabraLimpia](const Palabra& p) {
                return p.palabra == palabraLimpia;
            });

          
            if (it != palabras.end()) {
                string traduccion = it->traduccion;

                if (find(estructurasControl.begin(), estructurasControl.end(), palabraLimpia) != estructurasControl.end()
                    && linea.find("{") != string::npos) {
                    lineaTraducida += traduccion + " ";
                    lineaTraducida += "inicio_" + palabraLimpia + " ";
                    pilaEstructuras.push_back(palabraLimpia);
                    continue;
                }

              
                lineaTraducida += traduccion + " ";
            } else {
                lineaTraducida += palabra + " ";
            }
        }

    
        if (linea.find("}") != string::npos) {
            if (!pilaEstructuras.empty()) {
                string estructura = pilaEstructuras.back();
                pilaEstructuras.pop_back();
                lineaTraducida += "fin_" + estructura;
            } else {
                lineaTraducida += "}";
            }
        }

        cout << lineaTraducida << endl;
    }
}


int main() {
    string nombreArchivo = "diccionario.txt";
    vector<Palabra> palabras = cargarPalabrasDesdeArchivo(nombreArchivo);

    int opcion;
    do {
        cout << "\nMenu de opciones:\n";
        cout << "1. Crear\n";
        cout << "2. Leer\n";
        cout << "3. Actualizar\n";
        cout << "4. Eliminar\n";
        cout << "5. Traducir texto\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); 

        switch (opcion) {
            case 1: {
                // Agregar palabra
                Palabra nuevaPalabra;
                cout << "Ingrese la palabra: ";
                getline(cin, nuevaPalabra.palabra);

                if (palabraExiste(palabras, nuevaPalabra.palabra)) {
                    cout << "La palabra ya existe en el diccionario.\n";
                    // No se edita, simplemente se vuelve a mostrar el menú
                } else {
                    cout << "Ingrese la traduccion: ";
                    getline(cin, nuevaPalabra.traduccion);

                    cout << "Ingrese la funcionalidad: ";
                    getline(cin, nuevaPalabra.funcionalidad);

                    guardarPalabraEnArchivo(nombreArchivo, nuevaPalabra);
                    palabras.push_back(nuevaPalabra);
                    cout << "Palabra guardada exitosamente.\n";
                }
                break;
            }
            case 2:
                // Ver todas las palabras
                leer(nombreArchivo);
                break;
            case 3:
                // Editar palabra
                editarPalabra(palabras, nombreArchivo);
                break;
            case 4:
                // Eliminar palabra
                eliminarPalabra(palabras, nombreArchivo);
                break;
                
                case 5:
                // Traduciendo el texto
                traducirTexto(palabras);
                break;
            case 6:
                // Salir
                cout << "Saliendo del programa\n";
                break;
            default:
                cout << "Opción no válida, intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}


