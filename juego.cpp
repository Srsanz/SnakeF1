#include "Juego.hpp"
#include <stdio.h>

//Jimbo mamahuevo
//JaviPeruano

SDL_Texture* jugadorTex; //Variable de textura del primer personaje
SDL_Texture* jugador2Tex; //Variable de textura del segundo personaje
SDL_Texture* background;
SDL_Texture* background2;
SDL_Texture* jugar;
SDL_Texture* opciones;
SDL_Texture* logros;
SDL_Texture* salir;
SDL_Texture* copaPiston;

SDL_Rect srcR, destR; //Parámetros: ancho, altura y coordenadas en el plano (primer peronaje)
SDL_Rect srcR2, destR2;//"                                                  "(Segundo personaje)
SDL_Rect srcR3, destR3;
SDL_Rect dstRect = { 0, 0,1500, 800 };

enum estados {NO,SI};


//Juego* p = nullptr;
int main(int argc, char*argv[]) { //PUTOS ANORMALES
	TTF_Init();

	
	Frame fps;
	Juego init;
	Arduino hardware;

	ard(&hardware);
	init.isRunning = true;
	destR2.y = 70;

	fps.FPS = 35; //Con esto limitamos los FPS a un valor normal de ordenador, variable constante
	fps.frameDelay = 1000 / fps.FPS; //Tiempo máximo entre los frames
	int flags = 0;
	
	init = { "Juego", 1500, 800, NO };

	init.window = SDL_CreateWindow(init.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, init.width, init.height, flags);
	init.renderer = SDL_CreateRenderer(init.window, -1, 0);
	init.surface = SDL_GetWindowSurface(init.window);
	

	//Creamos los rectángulos para las opciones con sus medidas
	SDL_Rect opcion1Rect = { 100, 100, 152, 38 };
	SDL_Rect opcion2Rect = { 100, 150, 230, 38 };
	SDL_Rect opcion3Rect = { 100, 200, 190, 38 };
	SDL_Rect opcion4Rect = { 100, 250, 134, 38 };

	
	SDL_Event event;
	SDL_UpdateWindowSurface(init.window);

	SDL_PollEvent(&event);
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			SDL_Surface* surface2 = IMG_Load("Personajes/fondo3.png");
			background2 = SDL_CreateTextureFromSurface(init.renderer, surface2);

			SDL_Surface* Sjugar = IMG_Load("Imagenes/JUGAR.png");
			jugar = SDL_CreateTextureFromSurface(init.renderer, Sjugar);
			//SDL_FreeSurface(Sjugar);

			SDL_Surface* Sopciones = IMG_Load("Imagenes/OPCIONES.png");
			opciones = SDL_CreateTextureFromSurface(init.renderer, Sopciones);
			//SDL_FreeSurface(Sopciones);

			SDL_Surface* Slogros = IMG_Load("Imagenes/LOGROS.png");
			logros = SDL_CreateTextureFromSurface(init.renderer, Slogros);
			//SDL_FreeSurface(Slogros);

			SDL_Surface* Ssalir = IMG_Load("Imagenes/SALIR.png");
			salir = SDL_CreateTextureFromSurface(init.renderer, Ssalir);
			//SDL_FreeSurface(Ssalir);

			SDL_RenderCopy(init.renderer, background2, NULL, &dstRect);
			SDL_RenderCopy(init.renderer, jugar, NULL, &opcion1Rect);
			SDL_RenderCopy(init.renderer, opciones, NULL, &opcion2Rect);
			SDL_RenderCopy(init.renderer, logros, NULL, &opcion3Rect);
			SDL_RenderCopy(init.renderer, salir, NULL, &opcion4Rect);
			SDL_RenderPresent(init.renderer);

			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {


				int x = event.button.x;
				int y = event.button.y;
				if (x >= opcion1Rect.x && x <= opcion1Rect.x + opcion1Rect.w && y >= opcion1Rect.y && y <= opcion1Rect.y + opcion1Rect.h) {
					printf("Ha elegido JUGAR\n");
					
					SDL_DestroyWindow(init.window);
					SDL_Quit();
					//init = { "Juego", 1500, 800, NO };

					inici(&init);

					init.isRunning = true;

					do {
						init.isRunning = true;
						fps.inicioFrame = SDL_GetTicks();
						handleEvents(&init);
						update(&init);
						//update2(&init);
						render(&init);
						fps.tiempoFrame = SDL_GetTicks() - fps.inicioFrame; //en milisegundos

						if (fps.frameDelay > fps.tiempoFrame) //Con este if, limitamos los update a una velocidad que queremos para ajustar las velocidades del personaje
						{
							SDL_Delay(fps.frameDelay - fps.tiempoFrame);
						}

					} while (init.isRunning == true);
					clean(init);
				}
				else if (x >= opcion2Rect.x && x <= opcion2Rect.x + opcion2Rect.w && y >= opcion2Rect.y && y <= opcion2Rect.y + opcion2Rect.h) {
					printf("Ha eligido OPCIONES\n");
				}
				else if (x >= opcion3Rect.x && x <= opcion3Rect.x + opcion3Rect.w && y >= opcion3Rect.y && y <= opcion3Rect.y + opcion3Rect.h) {
					printf("Ha eligido LOGROS\n");
				}
				else if (x >= opcion4Rect.x && x <= opcion4Rect.x + opcion4Rect.w && y >= opcion4Rect.y && y <= opcion4Rect.y + opcion4Rect.h) {
					printf("Ha eligido SALIR\n");
					SDL_Quit();
				}

			}
		}
	}//clean(init);
	return 0;
}

Juego inici(Juego* init) {
	int flags = 0;
	if (init->fullscreen == SI) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), NULL);
		SDL_Quit();
		
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		init->window = SDL_CreateWindow(init->title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, init->width, init->height, flags);
		init->renderer = SDL_CreateRenderer(init->window, -1, 0);
		/*if (init->renderer)
		{
			SDL_SetRenderDrawColor(init->renderer, 255, 255, 255, 255);
		}*/

		init->isRunning = true;
	}

	//Cargamos los fondos del juego
	SDL_Surface* surface = IMG_Load("Personajes/fondo.png");
	background = SDL_CreateTextureFromSurface(init->renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Surface* temporalsurface = IMG_Load("Personajes/Alonso.png"); //Temporal: llamada a la imagen del personaje
	jugadorTex = SDL_CreateTextureFromSurface(init->renderer, temporalsurface);
	SDL_FreeSurface(temporalsurface);

	SDL_Surface* temporalsurface2 = IMG_Load("Personajes/verstappen.png"); //Temporal: llamada a la imagen del personaje
	jugador2Tex = SDL_CreateTextureFromSurface(init->renderer, temporalsurface2);
	SDL_FreeSurface(temporalsurface2);

	SDL_Surface* temporalsurface3 = IMG_Load("Personajes/copapiston.png"); //Temporal: llamada a la imagen del personaje
	copaPiston = SDL_CreateTextureFromSurface(init->renderer, temporalsurface3);
	SDL_FreeSurface(temporalsurface3);
	return *init;
}

Juego handleEvents(Juego* init) {//Si detecta que cerramos la ventana, se acaba el programa
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		init->isRunning = false;
		break;
	default:
		break;
	}
	return *init;
}

Juego update(Juego* init) {
	init->contador = init->contador + 1;
	printf("\n%d", init->contador);
	destR.w = 180;
	destR.h = 180;
	
	destR3.w = 50;
	destR3.h = 50;

	destR3.x = 300;
	destR3.y = 300;

	//destR.x = init->contador;

	//Primeras pruebas de movilidad
	SDL_Event event3;
	SDL_PollEvent(&event3);
	switch (event3.type) {
	case SDL_KEYDOWN:
		if (event3.key.keysym.sym == SDL_QUIT) {
			SDL_Quit();
		}
		if (event3.key.keysym.sym == SDLK_w) {
			destR.y = destR.y - 10;
		}
		if (event3.key.keysym.sym == SDLK_s) {
			destR.y = destR.y + 10;
		}
		if (event3.key.keysym.sym == SDLK_a) {
			destR.x = destR.x - 10;
		}
		if (event3.key.keysym.sym == SDLK_d) {
			destR.x = destR.x + 10;
		}
		break;
	}

	/*
	switch (event3.type) {
	case SDL_KEYDOWN:
		switch (event3.key.keysym.sym) {
		case SDL_QUIT:
			SDL_Quit();
		case SDLK_w:
			destR.y = destR.y - 5;
			printf("Movimiento arriba");
			break;
		case SDLK_a:
			destR.x = destR.x - 5;
			printf("Movimiento izquierda");
			break;
		case SDLK_s:
			destR.y = destR.y + 5;
			printf("Movimiento abajo");
			break;
		case SDLK_d:
			destR.x = destR.x + 10;
			printf("Movimiento derecha");
			break;
		default:
			break;
		}
		break;
		
	default:
	break;
	}

	*/

	

	
	//destR2.x = init->contador;
	//destR.y = init->contador;

	return *init;
}

Juego update2(Juego* init) {
	init->contador2 = init->contador2 + 1;
	printf("\n\t\t%d", init->contador2);
	destR2.w = 180;
	destR2.h = 180;
	
	SDL_Event event4;
	SDL_PollEvent(&event4);

	switch (event4.type) {
	case SDL_KEYDOWN:
		switch (event4.key.keysym.sym) {
		case SDL_QUIT:
			SDL_Quit();
		case SDLK_i:
			destR2.y = destR2.y - 5;
			printf("Movimiento arriba");
			break;
		case SDLK_j:
			destR2.x = destR2.x - 5;
			printf("Movimiento izquierda");
			break;
		case SDLK_k:
			destR2.y = destR2.y + 5;
			printf("Movimiento abajo");
			break;
		case SDLK_l:
			destR2.x = destR2.x + 10;
			printf("Movimiento derecha");
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}

	return *init;
}


Juego render(Juego* init) {
	SDL_RenderClear(init->renderer);
	SDL_RenderCopy(init->renderer, background, NULL, &dstRect);
	SDL_RenderCopy(init->renderer, jugadorTex, NULL, &destR);//los null indican aqui que la imagen va a cogerse entera y va ocupar lo máximo posible
	SDL_RenderCopy(init->renderer, jugador2Tex, NULL, &destR2);
	SDL_RenderCopy(init->renderer, copaPiston, NULL, &destR3);
	
	SDL_RenderPresent(init->renderer);
	return *init;
}

void clean(Juego init) { //limpiamos la memoria y las ventanas creadas
	SDL_DestroyWindow(init.window);
	SDL_DestroyRenderer(init.renderer);
	SDL_Quit();
}

