#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <unistd.h>

using namespace std;

// DECLARACION
class Nodo;
int algoritmoMinimax(int** matriz, int filas, int columnas, Nodo* aux, int alpha, int beta, int profundidad, bool esMaximizador, bool dificultad);

// Clase Nodos
class Nodo {
public:
    int valor;
    int columna;
    vector<Nodo*> lista;

    // Constructor con parámetros para inicializar el valor del nodo
    Nodo(int valorExtra) : valor(valorExtra) {}

    // Función para agregar un hijo al nodo
    void agregarHijo(Nodo* nodoEntregado) {
        lista.push_back(nodoEntregado);
    }
    int getValor(){
        return valor;
    }
    void setValor(int n){
        valor = n;
    }
    int getColumna(){
        return columna;
    }
    void setColumna(int col){
        columna = col;
    }

};
// Función para crear el árbol
Nodo* crearArbol() {
    Nodo* raiz = new Nodo(0);

    Nodo* hijo1 = new Nodo(0);
    Nodo* hijo2 = new Nodo(0);
    Nodo* hijo3 = new Nodo(0);

    Nodo* nieto1 = new Nodo(0);
    Nodo* nieto2 = new Nodo(0);
    Nodo* nieto3 = new Nodo(0);

    Nodo* nieto4 = new Nodo(0);
    Nodo* nieto5 = new Nodo(0);

    Nodo* nieto6 = new Nodo(0);
    Nodo* nieto7 = new Nodo(0);

    raiz->agregarHijo(hijo1);
    raiz->agregarHijo(hijo2);
    raiz->agregarHijo(hijo3);

    hijo1->agregarHijo(nieto1);
    hijo1->agregarHijo(nieto2);
    hijo1->agregarHijo(nieto3);

    hijo2->agregarHijo(nieto4);
    hijo2->agregarHijo(nieto5);

    hijo3->agregarHijo(nieto6);
    hijo3->agregarHijo(nieto7);

    return raiz;
}
// Función para liberar la memoria del árbol
void borrarArbol(Nodo* raiz) {
    for (Nodo* hijo : raiz->lista) {
        for (Nodo* nieto : hijo->lista) {
            // Mensaje de impresión para depuración
            delete nieto;
        }
        // Mensaje de impresión para depuración
        delete hijo;
    }
    // Mensaje de impresión para depuración
    cout << "...Se ha borrado el arbol..." << endl;
    delete raiz;
}
// Función imprimir menú
void imprimirMenu(){
    cout << "---------------------------------" << endl;
    cout << "         Juego Conecta 4" << endl;
    cout << "---------------------------------" << endl;
    cout << "Ingrese la dificultad" << endl;
    cout << "1) Facil" << endl;
    cout << "2) Medio" << endl;
    cout << "3) Dificil" << endl;
    cout << "---------------------------------" << endl;
}
// Función crearMatriz
int** crearMatriz(int filas, int columnas){
    int** matriz = new int*[filas];
    for (int i = 0; i < filas; ++i) {
        matriz[i] = new int[columnas];
    }
    return matriz;
}
// Función rellenar matriz
void rellenarMatriz(int** matriz, int filas, int columnas) {
    for (int i = filas - 1; i >= 0; --i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = 0;
        }
    }
}
// Función mostrar matriz
void mostrarMatriz(int** matriz, int filas, int columnas) {
    cout << string(columnas * 4, '-') << endl;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << "   ";
        }
        cout << endl;
    }
    cout << string(columnas * 4, '-') << endl;
}
// Función borrar matriz
void borrarMatriz(int** matriz, int filas){
    for (int i = 0; i < filas; ++i) {
        delete[] matriz[i];
    }
    delete[] matriz;
    cout << "...Matriz borrada..." << endl;
}
// ---------------------------------------------------------------------------------------------
//                                          CSV
// ---------------------------------------------------------------------------------------------
void guardarCSV(const string& nombreArchivo, int** matriz, int filas, int columnas) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            archivo << matriz[i][j];

            // Si no es el último elemento de la fila, agregar una coma como separador
            if (j < columnas - 1) {
                archivo << ",";
            }
        }

        // Nueva línea al final de cada fila
        archivo << endl;
    }
    archivo.close();
}
void crearZeroCSV(const string& nombreArchivo, int filas, int columnas) {
    int** matriz = crearMatriz(filas, columnas);

    // Llenar matriz con ceros
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = 0;
        }
    }

    // Guardar la matriz en el CSV
    guardarCSV(nombreArchivo, matriz, filas, columnas);

    // Liberar memoria
    borrarMatriz(matriz, filas);
}
void leerCSV(const string& nombreArchivo, int** matriz, int filas, int columnas) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    for (int i = 0; i < filas; ++i) {
        if (getline(archivo, linea)) {
            istringstream ss(linea);
            string valor;
            for (int j = 0; j < columnas; ++j) {
                if (getline(ss, valor, ',')) {
                    matriz[i][j] = stoi(valor);
                } else {
                    cerr << "Error al leer el archivo CSV." << endl;
                    borrarMatriz(matriz, filas);
                    return;
                }
            }
        } else {
            cerr << "Error al leer el archivo CSV." << endl;
            borrarMatriz(matriz, filas);
            return;
        }
    }
    archivo.close();
}
bool hayCSV(const string& nombreArchivo) {
    return access(nombreArchivo.c_str(), F_OK) != -1;
}
bool hayMatriz(const string& nombreArchivo, int filas, int columnas) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        return false;
    }

    string linea;
    for (int i = 0; i < filas; ++i) {
        if (getline(archivo, linea)) {
            istringstream ss(linea);
            string valor;
            for (int j = 0; j < columnas; ++j) {
                if (!getline(ss, valor, ',')) {
                    archivo.close();
                    return false;
                }
            }
        } else {
            archivo.close();
            return false;
        }
    }

    archivo.close();
    return true;
}
// ---------------------------------------------------------------------------------------------
//                                 Confirmar Tablero
// ---------------------------------------------------------------------------------------------
// Función mostrar piezas
int mostrarPiezas(int** matriz, int filas, int columnas, int numero){
    int valor = 0;
    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            if(matriz[i][j] == numero){
                valor++;
            }
        }
    }
    return valor;
}
// Función confirmar el ganador
bool confirmarGanador(int** matriz, int filas, int columnas, int jugador) {
    // Verificar horizontalmente
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas - 3; j++) {
            if (matriz[i][j] == jugador && matriz[i][j + 1] == jugador &&
                matriz[i][j + 2] == jugador && matriz[i][j + 3] == jugador) {
                return true;
            }
        }
    }
    // Verificar verticalmente
    for (int i = 0; i < filas - 3; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] == jugador && matriz[i + 1][j] == jugador &&
                matriz[i + 2][j] == jugador && matriz[i + 3][j] == jugador) {
                return true;
            }
        }
    }
    // Verificar diagonalmente (de izquierda a derecha)
    for (int i = 0; i < filas - 3; i++) {
        for (int j = 0; j < columnas - 3; j++) {
            if (matriz[i][j] == jugador && matriz[i + 1][j + 1] == jugador &&
                matriz[i + 2][j + 2] == jugador && matriz[i + 3][j + 3] == jugador) {
                return true;
            }
        }
    }
    // Verificar diagonalmente (de derecha a izquierda)
    for (int i = 0; i < filas - 3; i++) {
        for (int j = 3; j < columnas; j++) {
            if (matriz[i][j] == jugador && matriz[i + 1][j - 1] == jugador &&
                matriz[i + 2][j - 2] == jugador && matriz[i + 3][j - 3] == jugador) {
                return true;
            }
        }
    }
    return false;
}
// Función termino de partida
bool terminoPartida(int** matriz, int filas, int columnas) {
    if (confirmarGanador(matriz, filas, columnas, 1) || confirmarGanador(matriz, filas, columnas, -1)) {
        return true;
    }
    return false;
}
// Función empate
bool empate(int** matriz, int filas, int columnas){
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            if(matriz[i][j] == 0){
                return false;  // Hay al menos una posición jugable
            }
        }
    }
    return true; // No hay posiciones jugables
}
// Función aleatorio
int generarNumeroAleatorio() {
    return rand() % 7; // Genera un número entre 0 y 6
}
// Función jugar la pieza
void jugarPieza(int** matriz, int filas, int columnas, int columnaDeseada,bool esJugador){  
    bool juega = true;
    while (juega){
        if(columnaDeseada < columnas && columnaDeseada >= 0){
            //ES JUGADOR
            if(esJugador){
                for(int i=filas - 1;i>=0;i--){
                    if(matriz[i][columnaDeseada] == 0){
                        matriz[i][columnaDeseada] = 1;
                        cout << "Jugador coloca una ficha en la columna " << columnaDeseada << endl;
                        juega = false;
                        break;
                    }
                }
            }
            //ES CPU
            else{
                for(int i=filas - 1;i>=0;i--){
                    if(matriz[i][columnaDeseada] == 0){
                        matriz[i][columnaDeseada] = -1;
                        cout << "CPU coloca una ficha en la columna " << columnaDeseada << endl;
                        juega = false;
                        break;
                    }
                }
            }
        }
        else{
            cout << "Se ha generado una columna aleatoria!" << endl;
            columnaDeseada = generarNumeroAleatorio();
        }
    }
}
// ---------------------------------------------------------------------------------------------
//                                 Algoritmo MiniMax
// ---------------------------------------------------------------------------------------------
// Función Valor
int valorPieza(int** matriz, int filas, int columnas, int iteracion) {
    int valorTotal = 0;

    // Evaluación en la columna específica
    for (int i = 0; i < filas; ++i) {
        // Verificar hacia abajo
        if (i + 1 < filas && matriz[i][iteracion] == matriz[i + 1][iteracion]) {
            valorTotal += 1;  // Suma 1 si hay una ficha adyacente hacia abajo
        }
        
        // Verificar en diagonal hacia abajo y a la derecha
        if (i + 1 < filas && iteracion + 1 < columnas && matriz[i][iteracion] == matriz[i + 1][iteracion + 1]) {
            valorTotal += 1;  // Suma 1 si hay una ficha adyacente en diagonal hacia abajo y a la derecha
        }

        // Verificar en diagonal hacia abajo e izquierda
        if (i + 1 < filas && iteracion - 1 >= 0 && matriz[i][iteracion] == matriz[i + 1][iteracion - 1]) {
            valorTotal += 1;  // Suma 1 si hay una ficha adyacente en diagonal hacia abajo e izquierda
        }
    }
    
    return valorTotal;
}
// Función que verifica si puede ganar
bool esGanadora(int** matriz, int filas, int columnas, int fila, int columna, int jugador) {
    // Verificar la fila
    int contador = 0;
    for (int j = 0; j < columnas; ++j) {
        if (matriz[fila][j] == jugador) {
            contador++;
            if (contador == 4) {
                return true;  // Cuatro fichas consecutivas en la fila
            }
        } else {
            contador = 0;
        }
    }

    // Verificar la columna
    contador = 0;
    for (int i = 0; i < filas; ++i) {
        if (matriz[i][columna] == jugador) {
            contador++;
            if (contador == 4) {
                return true;  // Cuatro fichas consecutivas en la columna
            }
        } else {
            contador = 0;
        }
    }

    // Verificar diagonal principal (izquierda a derecha)
    contador = 0;
    int inicioFila = fila - std::min(fila, columna);
    int inicioColumna = columna - std::min(fila, columna);
    while (inicioFila < filas && inicioColumna < columnas) {
        if (matriz[inicioFila][inicioColumna] == jugador) {
            contador++;
            if (contador == 4) {
                return true;  // Cuatro fichas consecutivas en la diagonal principal
            }
        } else {
            contador = 0;
        }
        inicioFila++;
        inicioColumna++;
    }

    // Verificar diagonal principal (derecha a izquierda)
    contador = 0;
    inicioFila = fila + std::min(filas - 1 - fila, columna);
    inicioColumna = columna - std::min(filas - 1 - fila, columna);
    while (inicioFila >= 0 && inicioColumna < columnas) {
        if (matriz[inicioFila][inicioColumna] == jugador) {
            contador++;
            if (contador == 4) {
                return true;  // Cuatro fichas consecutivas en la diagonal secundaria
            }
        } else {
            contador = 0;
        }
        inicioFila--;
        inicioColumna++;
    }

    return false;  // No hay cuatro fichas consecutivas en ninguna dirección
}
// Función si puede bloquear
bool bloqueo(int** matriz, int filas, int columnas, int iteracion) {
    // Verificar si la columna está llena
    if (matriz[0][iteracion] != 0) {
        return false;  // La columna está llena, no se puede bloquear
    }

    // Analizar la columna para bloquear al oponente
    for (int i = filas - 1; i >= 0; --i) {
        if (matriz[i][iteracion] == 0) {
            // Simular colocar una ficha del jugador en la posición actual
            matriz[i][iteracion] = 1;

            // Verificar si esta jugada bloquea al oponente
            if (esGanadora(matriz, filas, columnas, i, iteracion, -1)) {
                // Deshacer la simulación antes de devolver el resultado
                matriz[i][iteracion] = 0;
                return true;  // La jugada bloquea al oponente
            }

            // Deshacer la simulación antes de continuar
            matriz[i][iteracion] = 0;
        }
    }

    return false;  // La jugada no bloquea al oponente
}
// Función valor pieza pero dificil
int valorDificil(int** matriz, int filas, int columnas, int iteracion) {
    int valorTotal = 0;

    // Verificar si la columna está llena
    if (matriz[0][iteracion] != 0) {
        return valorTotal;  // La columna está llena, no se puede jugar aquí
    }

    // Evaluar la columna específica
    for (int i = filas - 1; i >= 0; --i) {
        if (matriz[i][iteracion] == 0) {
            // Simular colocar una ficha del bot en la posición actual
            matriz[i][iteracion] = -1;

            // Verificar si esta jugada puede llevar a la victoria del bot
            if (esGanadora(matriz, filas, columnas, i, iteracion, -1)) {
                valorTotal += 100;  // Asignar un valor alto si puede ganar en esta jugada
            }

            // Verificar si esta jugada bloquea al oponente
            if (bloqueo(matriz, filas, columnas, iteracion)) {
                valorTotal += 10;  // Asignar un valor para bloquear al oponente
            }
            // Deshacer la simulación antes de continuar
            matriz[i][iteracion] = 0;
        }
    }
    return valorTotal;
}
// Función insertar
void insertarValores(Nodo* aux, bool dificultad, int** matriz, int filas, int columnas){ // "False" = dificultad media, "True" = dificultad dificil.
    int numero;
    int iteracion = -1;
    if(!dificultad){
        for(Nodo* hijo : aux->lista){
            for(Nodo* nieto : hijo->lista){
                iteracion++;
                numero = valorPieza(matriz, filas, columnas, iteracion); // valor pieza
                nieto->setValor(numero);
                nieto->setColumna(iteracion);
            }
        }
    }
    else{
        for(Nodo* hijo : aux->lista){
            for(Nodo* nieto : hijo->lista){
                iteracion++;
                numero = valorDificil(matriz, filas, columnas, iteracion); // valor dificil
                nieto->setValor(numero);
                nieto->setColumna(iteracion);
            }
        }
    }
}
// Función MiniMax
int algoritmoMinimax(int** matriz, int filas, int columnas, Nodo* aux, int alpha, int beta, int profundidad, bool esMaximizador) {

    if (profundidad == 0 || aux->lista.empty()) {
        return aux->getValor();
    }

    if (esMaximizador) {
        for (Nodo* hijo : aux->lista) {
            int numero = algoritmoMinimax(matriz, filas, columnas, hijo, alpha, beta, profundidad - 1, false);
            alpha = max(alpha, numero);
            if (beta <= alpha) {
                break; // Poda alfa-beta
            }
        }
        return alpha;
    } else {
        for (Nodo* hijo : aux->lista) {
            int numero = algoritmoMinimax(matriz, filas, columnas, hijo, alpha, beta, profundidad - 1, true);
            beta = min(beta,numero);
            if (beta <= alpha) {
                break; // Poda alfa-beta
            }
        }
        return beta;
    }
}

int main() {
    // Nombre del archivo CSV
    string nombreArchivo = "matriz.csv";
    // Variable aleatoria
    srand(static_cast<unsigned int>(time(0)));
    // Crear arbol para algoritmo minimax
    Nodo* raiz = crearArbol();
    // Crear variables para algoritmo minimax
    int alpha = -500;
    int beta = 500;
    int profundidad = 3;
    // Crear matriz llena de 0s.
    int filas = 6;
    int columnas = 7;
    int** matriz = crearMatriz(filas,columnas);
    // Rellena la matriz con 0
    rellenarMatriz(matriz,filas,columnas);
    // Menú dificultad del juego
    imprimirMenu();
    // Elección de dificultad
    int dificultad;
    cin >> dificultad;
    // Booleano "verdadero" mientras dure la partida
    bool juegoPartida = true;
    // Empieza siempre el jugador "Tú"
    bool participante = true;

    cout << "00000000000" << endl;

    // Verificar si hay un archivo CSV existente
    if(!hayCSV(nombreArchivo)){
        cout << "1111111111" << endl;
        // Caso 1: No existe CSV, crear uno con matriz de ceros
        crearZeroCSV(nombreArchivo,filas,columnas);
    }
    else{
        // Caso 2: Existe CSV
        if(hayMatriz(nombreArchivo,filas,columnas)){
            cout << "2222222222" << endl;
            // Caso 2.1: Existe CSV pero no hay matriz, crear uno con matriz de ceros
            crearZeroCSV(nombreArchivo,filas,columnas);
        }
        else{
            cout << "3333333333" << endl;
            // Caso 2.2: Existe CSV y hay matriz, iniciar el juego
            while(juegoPartida){
                // Se crea la variable MÁS IMPORTANTE la que decide en que columna se jugara
                int columnaDeseada = -1;
                mostrarMatriz(matriz,filas,columnas);

                // Verificar si la partida ha terminado "Empate" o "Ganador"
                if(empate(matriz,filas,columnas)){
                    cout << "Hay empate" << endl;
                    juegoPartida = false;
                    crearZeroCSV(nombreArchivo,filas,columnas);
                }
                if (terminoPartida(matriz, filas, columnas)) {
                    juegoPartida = false;
                    cout << "La partida ha terminado" << endl;
                    if(!participante){ // Ultima jugada "true" = jugador, "false" = CPU
                        cout << "Ha ganado el Jugador!!" << endl;
                    }else{
                        cout << "Ha ganado la CPU!!" << endl;
                    }
                    crearZeroCSV(nombreArchivo,filas,columnas);
                }
                else{
                    switch (dificultad)
                    {
                    case 1: // Modo de juego Fácil
                        if (participante) {
                            cout << "Juegan las: Cruces (JUGADOR)" << endl;
                            cout << "Elija la columna deseada!" << endl;
                            cin >> columnaDeseada;
                            jugarPieza(matriz, filas, columnas, columnaDeseada, true);
                            participante = false;
                            guardarCSV(nombreArchivo,matriz,filas,columnas);
                        } else {
                            cout << "Juegan los: Circulos (CPU)" << endl;
                            // RANDOM
                            columnaDeseada = generarNumeroAleatorio();  // Dificultad "Facil" es un random
                            jugarPieza(matriz, filas, columnas, columnaDeseada, false);
                            participante = true;
                            guardarCSV(nombreArchivo,matriz,filas,columnas);
                        }
                        break;
                    
                    case 2: // Modo de juego Medio
                        if (participante) {
                            cout << "Juegan las: Cruces (JUGADOR)" << endl;
                            cout << "Elija la columna deseada!" << endl;
                            cin >> columnaDeseada;
                            jugarPieza(matriz, filas, columnas, columnaDeseada, true);
                            participante = false;
                            guardarCSV(nombreArchivo,matriz,filas,columnas);
                        } else {
                            cout << "Juegan los: Circulos (CPU)" << endl;
                            // MINIMAX MEDIA
                            insertarValores(raiz,false,matriz,filas,columnas); // "False" = dificultad media
                            columnaDeseada = algoritmoMinimax(matriz,filas,columnas,raiz,alpha,beta,profundidad,true);
                            for(Nodo* hijo : raiz->lista){
                                for(Nodo* nieto : hijo->lista){
                                    if(nieto->getValor() == columnaDeseada){
                                        columnaDeseada = nieto->getColumna();
                                    }
                                }
                            }
                            jugarPieza(matriz, filas, columnas, columnaDeseada, false);
                            participante = true;
                            guardarCSV(nombreArchivo,matriz,filas,columnas);
                        }
                        break;

                    case 3: // Modo de juego Dificil
                        if (participante) {
                            cout << "Juegan las: Cruces (JUGADOR)" << endl;
                            cout << "Elija la columna deseada!" << endl;
                            cin >> columnaDeseada;
                            jugarPieza(matriz, filas, columnas, columnaDeseada, true);
                            participante = false;
                            guardarCSV(nombreArchivo,matriz,filas,columnas);
                        } else {
                            cout << "Juegan los: Circulos (CPU)" << endl;
                            // MINIMAX DIFICIL
                            insertarValores(raiz,true,matriz,filas,columnas); // "true" = dificultad dificil
                            columnaDeseada = algoritmoMinimax(matriz,filas,columnas,raiz,alpha,beta,profundidad,true);
                            for(Nodo* hijo : raiz->lista){
                                for(Nodo* nieto : hijo->lista){
                                    if(nieto->getValor() == columnaDeseada){
                                        columnaDeseada = nieto->getColumna();
                                    }
                                }
                            }
                            jugarPieza(matriz, filas, columnas, columnaDeseada, false);
                            participante = true;
                            guardarCSV(nombreArchivo,matriz,filas,columnas);
                        }
                        break;
                    
                    default: // Error al seleccionar
                        juegoPartida = false;
                        break;
                    }
                }
            }

        }
    }

    // Información al final de la partida
    cout << "Termino de partida" << endl;
    cout << "---------------------------------" << endl;
    cout << "Numero de ( 1 ) jugados: "<< mostrarPiezas(matriz,filas,columnas,1) << endl;
    cout << "Numero de ( -1 ) jugados: "<< mostrarPiezas(matriz,filas,columnas,-1) << endl;
    cout << "---------------------------------" << endl;
    // Borrar matriz
    borrarMatriz(matriz,filas);
    // Borrar arbol
    borrarArbol(raiz);
    cout << "---------------------------------" << endl;
    return 0;
}