#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define JUGADORESMAX 500
#define NOMBREMAX 25

typedef struct
{
    char nombre[NOMBREMAX];
    int puntuacion;

}Jugador;

int leerNumero(void);
void creaJugador(Jugador nuevoJugador);
int buscaJugador(char* nombre); //puntero es mas eficiente 
void muestraPuntuacion(void);//no toma argumento de entrada
int extraePuntuacion(char* nombre);
void borrarJugador(char* nombre);

int numJugadores = 0;
Jugador jugadores[JUGADORESMAX];

int main(void)
{
    char tecla;
    int op;
    int nueva_puntuacion,antigua_puntuacion;
    printf("\t\t=====PANTALLA INICIO=====\n\n\t\tpulse cuaquiler tecla para continuar\n\n");

    tecla = _getch();

    system("cls");


    do
    {
        system("cls");

        printf("1.JUGAR\n");
        printf("2.VER PUNTUACIONES\n");
        printf("3.SALIR\n");

        op = leerNumero();
        char nombre[NOMBREMAX];
        char nombre1[NOMBREMAX];
        int existe;

        switch (op)
        {
        case 1:
            system("cls");
            //char nombre[NOMBREMAX];
            
            do //pide que introduzcas el nombre de nuevo si introduces solo un intro como nombre
            {
                
                printf("Introduzca su nombre: ");
                fgets(nombre, NOMBREMAX, stdin);//lee nombre con espacios
                if (nombre[0] == '\n')
                {
                    printf("introduzca un nombre valido\n");
                    tecla = _getch;
                    system("cls");
                }
            } while (nombre[0] == '\n');
            nombre[strcspn(nombre, "\n")] = 0;//elimina el salto de linea del fgets

            existe = buscaJugador(nombre);

            if (existe == -1)
            {
                Jugador nuevoJugador;
                strcpy_s(nuevoJugador.nombre,NOMBREMAX, nombre); //copia el contenido de nombre en el nuevo jugador 
                nuevoJugador.puntuacion = 0; //establece su puntuacion en cero
                creaJugador(nuevoJugador); //lo agrega al fichero
                printf("%s", nombre);
            }
            else
            {
                printf("%s ", nombre);

                scanf_s("%d", &nueva_puntuacion);

                antigua_puntuacion = extraePuntuacion(nombre);

                if (nueva_puntuacion >= antigua_puntuacion) 
                {
                    borrarJugador(nombre);

                    strcpy_s(nombre1, NOMBREMAX, nombre);

                    Jugador nuevoJugador;
                    strcpy_s(nuevoJugador.nombre, NOMBREMAX, nombre1); //copia el contenido de nombre en el nuevo jugador 
                    nuevoJugador.puntuacion = nueva_puntuacion; //establece su puntuacion en cero
                    creaJugador(nuevoJugador); //lo agrega al fichero
                    printf("%s\n", nombre1);
                    printf("pulsa cualquier tecla para volver al menu\n");
                    tecla = _getch();


                }
                else 
                {
                    printf("pulsa cualquier tecla para volver al menu\n");
                    tecla = _getch();

                }
            }
            printf("pulsa cualquier tecla para volver al menu\n");
            tecla = _getch();
            break;
        case 2:
            system("cls");
            muestraPuntuacion();
            printf("pulsa cualquier tecla para volver al menu\n");
            tecla = _getch();
            break;
        default:
            if (op != 3)
            {
                printf("opcion incorrecta\n");
                printf("pulsa cualquier tecla para volver al menu\n");
                tecla = _getch();
            }
            break;
        }
    } while (op != 3);

}



int leerNumero(void) //funcion para leer enteros
{
    char cadena[2];
    int num;
    char intro;
    fgets(cadena, 2, stdin);
    num = atoi(cadena);
    scanf_s("%c", &intro);
    return (num);
}

void creaJugador(Jugador nuevoJugador)
{
#pragma warning(suppress : 4996)
    FILE* archivo = fopen("jugadores.txt", "a");//a es append, si existe el archivo lo agregara al final del mismo, asi no se sobreescribe
#pragma warning(default:4996)
    if (archivo == NULL)
    {
        printf("No se ha podido abrir el archivo.\n");
        return;
    }

    fprintf(archivo, "%s %d\n", nuevoJugador.nombre, nuevoJugador.puntuacion);//imprime en el fichero nombre y puntuación
    fclose(archivo);

    jugadores[numJugadores] = nuevoJugador; //añade nuevo jugador a la posicion numJugadores del array jugadores
    numJugadores++;//aumenta la posición para el siguiente que se cree
}
int buscaJugador(char* nombre)
{
    FILE* archivo = fopen("jugadores.txt", "r");
    if (archivo == NULL) {
        printf("No se ha podido abrir el archivo.\n");
        return -1;
    }

    char nombreArchivo[NOMBREMAX];
    int puntuacion;

    while (fscanf(archivo, "%s %d", nombreArchivo, &puntuacion) == 2) {
        if (strcmp(nombreArchivo, nombre) == 0) {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return -1;
}

void muestraPuntuacion(void)
{
#pragma warning(suppress : 4996)
    FILE* archivo = fopen("jugadores.txt", "r");//r de read, abre el archivo en modo lectura
#pragma warning(default:4996)
    if (archivo == NULL)
    {
        printf("No se ha podido abrir el archivo.\n");
        return;
    }

    // Leer los jugadores y sus puntuaciones 
    Jugador jugadores[JUGADORESMAX];
    int numJugadores = 0;

    char nombre[NOMBREMAX];
    int puntuacion;
    while (fscanf(archivo, "%s %d", nombre, &puntuacion) == 2) //se ejecuta mientras cada jugador tenga un par de variables, nombre y puntuacion
    {
        Jugador j; //este bucle lee y asigna puntuaciones y nombres a los jugadores para posteriormente ordenarlos
        strcpy(j.nombre, nombre);//copia el nombre en j.nombre
        j.puntuacion = puntuacion;
        jugadores[numJugadores++] = j;//el contador aumenta para luego saber cuantas veces recorrer el bucle
    }

    fclose(archivo);

    // Ordenar el array de jugadores por puntuación
    for (int i = 0; i < numJugadores - 1; i++) //este doble bucle compara la puntuacion de un jugador con la del siguiente y si la del actual es menor intercambian posicion, ordenandolas en orden descendente
    {
        for (int j = i + 1; j < numJugadores; j++)
        {
            if (jugadores[j].puntuacion > jugadores[i].puntuacion)
            {
                Jugador aux = jugadores[i];
                jugadores[i] = jugadores[j];
                jugadores[j] = aux;
            }
        }
    }

    // Imprimir los 10 primeros jugadores ordenados por puntuación o los que haya si hay menos de 10
    if (numJugadores < 10) 
    {
        for (int i = 0; i < numJugadores; i++) 
        {
            printf("%d. %s: %d\n", i + 1, jugadores[i].nombre, jugadores[i].puntuacion);
        }
    }
    else 
    {
        for (int i = 0; i < 10; i++)
        {
            printf("%d. %s: %d\n", i + 1, jugadores[i].nombre, jugadores[i].puntuacion);
        }
    }
}
int extraePuntuacion(char* nombre)
{
    FILE* archivo = fopen("jugadores.txt", "r");
    if (archivo == NULL) {
        printf("No se ha podido abrir el archivo.\n");
        return -1;
    }

    char nombreArchivo[NOMBREMAX];
    int puntuacion;

    while (fscanf(archivo, "%s %d", nombreArchivo, &puntuacion) == 2) {
        if (strcmp(nombreArchivo, nombre) == 0) {
            fclose(archivo);
            return puntuacion;
        }
    }

    fclose(archivo);
    return -1;
}
void borrarJugador(char* nombre)
{
    FILE* archivo = fopen("jugadores.txt", "r");
    if (archivo == NULL) {
        printf("No se ha podido abrir el archivo.\n");
        return;
    }

    FILE* archivoTemp = fopen("temp.txt", "w");
    if (archivoTemp == NULL) {
        printf("No se ha podido crear el archivo temporal.\n");
        fclose(archivo);
        return;
    }

    char nombreArchivo[NOMBREMAX];
    int puntuacion;

    while (fscanf(archivo, "%s %d", nombreArchivo, &puntuacion) == 2) {
        if (strcmp(nombreArchivo, nombre) != 0) {
            fprintf(archivoTemp, "%s %d\n", nombreArchivo, puntuacion);
        }
    }

    fclose(archivo);
    fclose(archivoTemp);

    remove("jugadores.txt");
    rename("temp.txt", "jugadores.txt");

    printf("Jugador borrado exitosamente.\n");
}
