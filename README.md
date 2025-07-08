[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mi1WNrHU)
# Proyecto de C++ The Lost City

## Descripción y ambientacion del Proyecto

Un aventurero explora una pirámide en busca de una ciudad perdida y su tesoro legendario, el jugador debe superar cuatro niveles para poder salir de la piramide. A medida que avanza, tendrá que recoger monedas y esquivar a los enemigos para poder pasar al siguiente nivel.

Las monedas aydurán al jugador a poder avanzar en cada nivel. :D

Nivel 1: El jugador deberá de recoger una moneda esquivando a los enemigos para poder pasar al siguiente nivel.

Nivel 2: En este nivel deberá de recoger dos monedas esquivando a los enemigos para poder pasar al siguiente nivel.

Nivel 3 – El jugador deberá de recoger 3 monedas esquivando a los enemigos para poder pasar al siguiente nivel.

Nivel 4: En este ultimo nivel, el jugador deberá de recoger las ultimas monedas que lo ayudarán a poder vencer al ultimo nivel.


## Mecánica principal
- Movimiento con flechas: El jugador se mueve usando las flechas del teclado (↑ ↓ ← →) esquivando trampas y buscando salidas.
- Combatir enemigos, especialmente al principal el escarabajo de oro.
- El jugador debera salir de los laberintos para poder salir a la de la piramide y ganar
-Movimiento libre: Se controla al personaje con las flechas del teclado (↑ ↓ ← →) para avanzar entre los niveles, evitando muros, trampas o enemigos.
-A lo largo del laberinto hay monedas y mejoras. Son necesarias para avanzar, mejorar habilidades o desbloquear caminos especiales.


## Aplicación de temas 

- **Variables:** Se utilizan para almacenar y actualizar datos clave como la posición (coordenadas X, Y) del jugador y su vida actual y el tiempo transcurrido durante el nivel.

- **Condicionales:** Controlan la lógica de colisiones entre el jugador y los obstáculos o enemigos, además de manejar las diferentes respuestas según el resultado del acertijo (activar el derrumbe leve o fuerte).

- **Bucles:** Se implementan los bucles principales del juego para mantener el menú activo y controlar la ejecución continua del nivel hasta que se cumpla alguna condición de finalización (derrota, victoria o salida).

- **Funciones:** Se utilizan funciones específicas para dibujar el mapa, procesar movimientos, verificar colisiones, resolver acertijos y actualizar estados del juego, facilitando mantenimiento.

- **Strcuts:** Se definen estructuras para organizar mejor la información de los personajes y elementos del juego,como el jugador y los enemigos, almacenando datos como posición, vida, y estado.

- **Manejo de Archivos:** Se implementa para guardar los puntajes o el progreso del jugador en un archivo de texto, esto permite que al cerrar el juego la información no se pierda y pueda ser cargada la próxima vez que el jugador quiera seguir jugando o revisar sus resultados anteriores.

- **Manejo de Errores:** Se valida la entrada del usuario en menús y acertijos, asegurando que solo se acepten opciones válidas y evitando comportamientos inesperados o caídas del programa.

## Consideraciones técnicas
- El mapa se representa con matrices de caracteres, usando símbolos para tierra, rocas, enredaderas y enemigos.
- El acertijo se presenta como una pregunta con opciones múltiples, la cual el resultado afecta la intensidad del derrumbe.
- El Hombre de Arena lanza objetos arrojados que dañan al jugador y se mueve con patrones definidos.
- El derrumbe modifica el mapa en tiempo real, simulando caída de escombros y grietas.

## Consideraciones tecnicas de desarollo 
--Uso de PDCurses: El juego utiliza la biblioteca PDCurses para crear una interfaz gráfica en consola con ventanas, movimientos fluidos del personaje, y simulaciones visuales como ataques, laberintos y muros.  

## Imagen 

## Equipo

Integrantes del equipo
Nombre completo: Amy Ariadna Barraza Villacorta
Carnet: 00012725

Nombre completo: Jaqueline Nicole Cardoza Maldonado
Carnet: 000252125

Nombre completo: Diana Rebeca Ayala Jandres
Carnet: 00021325

Nombre completo: Gabriel Alejandro Guevara Rodríguez
Carnet: 00252225

## Instrucciones de Ejecución
Clona este repositorio en tu máquina local:
git clone [URL del repositorio]
[Portada del juego](Captura de pantalla 2025-07-07 233548.png)














