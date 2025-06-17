[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/mi1WNrHU)
# Proyecto de C++ The Lost City

## Descripción del Proyecto

Un aventurero explora una pirámide en busca de una ciudad perdida y su tesoro legendario. El jugador debe superar cuatro niveles llenos de trampas, acertijos y enemigos elementales, usando solo tres vidas. A medida que avanza, desbloquea mejoras y habilidades que lo ayudan a sobrevivir. El objetivo es llegar al corazón de la pirámide, donde un antiguo misterio lo espera.

## Distribución de estructuras de control en el juego:

## For: 
Controla el avance por los 4 niveles, cargando entorno, enemigos y eventos. También gestiona las acciones de los enemigos (ataque, movimiento, patrullaje).
## Switch: 
Maneja decisiones en acertijos, combates y diálogos.
## Do-While: 
Ejecuta menús o acciones obligatorias al menos una vez (como selección de armas o aceptar ayuda).
## While: 
Repite intentos en acertijos hasta una respuesta correcta o agotar oportunidades.
## If-Else:
Evalúa decisiones del jugador, uso de comodines y comportamiento de enemigos.
##Arreglos: 
Almacenan estadísticas del jugador, habilidades, armas y enemigos por nivel para su actualización y control.

## Equipo

- **Nombre del equipo:** Ideatic

### Integrantes del equipo

1. **Nombre completo:** Amy Ariadna Barraza Villacorta  
   **Carnet:** 00012725

2. **Nombre completo:** Jaqueline Nicole Cardoza Maldonado  
   **Carnet:** 000252125

3. **Nombre completo:** Diana Rebeca Ayala Jandres  
   **Carnet:** 00021325

4. **Nombre completo:** Gabriel Alejandro Guevara Rodríguez  
   **Carnet:** 00252225

## Instrucciones de Ejecución

1. Clona este repositorio en tu máquina local:
   ```bash
   git clone [URL del repositorio]







# Nivel 2: El Derrumbe

El aventurero sigue dentro de una pirámide, debe resolver acertijos y escapar mientras la pirámide se derrumba y enfrentar al Hombre de arena, evitando obstáculos y su perdida.

## Mecánica principal
- Movimiento con flechas.
- Esquivar rocas y enredaderas, y liberarse de ellas.
- Resolver acertijos que afectan el desarrollo del nivel.
- Combatir enemigos, especialmente al principal Hombre de Arena.

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

## Instrucciones para compilar y ejecutar

Para compilar el proyecto, ejecutar:

g++ main.cpp src/*.cpp(cuando  se cree la carpeta, sino nivel2.cpp) -o EscapeDelDerrumbe