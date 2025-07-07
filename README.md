[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mi1WNrHU)
# Proyecto de C++ The Lost City

## Descripción y ambientacion del Proyecto

Un aventurero explora una pirámide en busca de una ciudad perdida y su tesoro legendario, el jugador debe superar cuatro niveles llenos de trampas, acertijos y enemigos elementales, usando solo tres vidas. A medida que avanza, desbloquea mejoras y habilidades que lo ayudan a sobrevivir. El objetivo es llegar al corazón de la pirámide, donde un antiguo misterio lo espera.

Nivel 1 – Guardián del Agua: El jugador se enfrenta a un entorno húmedo y traicionero, donde deberá esquivar trampas, recolectar monedas y derrotar a un enemigo hecho de agua para avanzar.

Nivel 2 – Derrumbe: La pirámide comienza a colapsar. El jugador debe escapar entre escombros mientras enfrenta al Hombre de Arena para poder pasar de nivel.

Nivel 3 – Lava: El jugador debe recolectar más monedas y sobrevivir a un terreno volcánico para seguir y pelear con el villano para poder pasar de nivel.

Nivel 4 – Escarabajo de Oro: En el gran final, el jugador atraviesa un recorrido que reúne todos los peligros anteriores.Solo si el jugador usa correctamente los objetos recolectados y actúa con inteligencia, podrá alcanzar el tesoro oculto al final de la pirámide.

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














