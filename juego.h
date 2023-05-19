#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include <iostream>
#include "SerialClass.h"
#include "SerialClass.cpp"

#define TAM 4



typedef struct { //Estructura con las variables en uso
	const char* title;
	int width;
	int height;
	int fullscreen;
	int contador;
	int contador2;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
}Juego;

typedef struct {
	int FPS; //Con esto limitamos los FPS a un valor normal de ordenador, variable constante
	int frameDelay; //Tiempo máximo entre los frames
	Uint32 inicioFrame; //Variable que consta solo de números enteros
	int tiempoFrame;
}Frame;

/*typedef struct {
	char angulox[TAM];
	char anguloy[TAM];

}Arduino;*/

//Declaración de funciones 
//Juego menu (Juego* init);
Juego inici(Juego* init); //función de iniciación
Juego handleEvents(Juego* init); //Organiza los eventos consecutivamente
Juego update(Juego* init); //Actualiza lo que se ve en pantalla
Juego update2(Juego* init);
Juego render(Juego* init); //Manda a la pantalla lo que queremos que se vea
void clean(Juego init); //Limpia lo que hay en pantalla y lo reinicia 
