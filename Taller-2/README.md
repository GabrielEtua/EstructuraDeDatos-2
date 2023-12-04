# EstructuraDeDatos-2

Compilar: 
cd "Taller-2"
g++ main.cpp -o compilador
./compilador


Elegir Dificultad:
Ingresa '1' para Fácil.
Ingresa '2' para Medio.
Ingresa '3' para Difícil.

Jugabilidad:
El jugador ("1") y la CPU ("-1") se turnan.
El jugador elige una columna para soltar una ficha, y la CPU realiza su movimiento correspondiente.
El juego termina cuando hay un ganador, un empate.

Archivo CSV:
El juego utiliza un archivo CSV llamado "matriz.csv" para almacenar el estado del juego.
Si el archivo no existe, crea uno con una matriz vacía.
Si el archivo está corrupto o no coincide con el formato esperado, reinicia el estado del juego.

Algoritmo de Inteligencia Artificial (Minimax):
El algoritmo Minimax se utiliza para los movimientos de la CPU.
Fácil: Selecciona aleatoriamente una columna.
Medio: Evalúa gracias a un algoritmo simple un buen movimiento.
Difícil: Aplica un algoritmo más complejo para elegir el mejor lugar.

Estado del Juego:
El estado del juego se muestra durante el proceso del juego.
El programa indica al ganador, un empate o el final del juego.

Limpieza:
El codigo borra ("delete") tanto las matrices como el arbol creado.
Muestra estadísticas sobre la cantidad de movimientos del jugador y la CPU.