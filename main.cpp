#include <iostream>
#include <Windows.h>
#include "SerialClass.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 200
#define PAUSA_MS 50

void cambio(char[4], float*);
void change(char[4], float*);
int Enviar_y_Recibir(Serial* Arduino, const char* mensaje_enviar, char* mensaje_recibir);
int leer_angulo(Serial* Arduino, const char* comando);


void main() {
	float numer1 = 0.0;
	char puerto[] = "COM3";
	int angulo_x, angulo_y;
	Serial* Arduino = new Serial((char*)puerto);
	while (Arduino->IsConnected()) {
		printf_s("Arduino conectado\n");
		
		angulo_x = leer_angulo(Arduino, "GET_ANGULOX\n");
		angulo_y = leer_angulo(Arduino, "GET_ANGULOY\n");
		//Arduino->ReadData(angulox, sizeof(angulox)-2);
		//Arduino->ReadData(anguloy, sizeof(anguloy)-1);
		
		//printf_s("%s\n", anguloy);
		

		/*if (angulox[1] == '.') {
			change(angulox, &numer1);
		}
		*/
		/*
		if (angulox[2] >= 48 && angulox[2] <= 57) {
			cambio(angulox, &numer1);
		}
		else {
			change(angulox, &numer1);
		}



		printf("%.2f", numer1);
		*/
	}


		
}




void cambio(char cadena[4], float* numero)
{
	float decenas = 0.00;
	float unidades = 0.00;
	float centenas = 0.00;

	centenas = cadena[0] - '0';
	decenas = cadena[1] - '0';
	unidades = cadena[2] - '0';
	

	*numero = (decenas * 10) + (unidades)+(centenas * 100);

}


void change(char cadena[4], float* numero)
{
	float unidades = 0.00;
	float decenas = 0.00;

	unidades = cadena[1] - '0';
	decenas = cadena[0] - '0';

	*numero = (unidades)+(decenas * 10);
}



int leer_angulo(Serial* Arduino, const char* comando)
{
	int angulo;
	int bytesRecibidos;
	char mensaje_recibido[MAX_BUFFER];

	bytesRecibidos = Enviar_y_Recibir(Arduino, comando, mensaje_recibido);
	if (bytesRecibidos <= 0)
	{
		printf("\nNo se ha recibido respuesta a la petición\n");
		angulo = -1;
	}
	else
	{
		printf("\nLa respuesta recibida tiene %d bytes. Recibido=%s\n", bytesRecibidos,
			mensaje_recibido);
		angulo = atoi(mensaje_recibido);
	}
	return angulo;
}



int Enviar_y_Recibir(Serial* Arduino, const char* mensaje_enviar, char* mensaje_recibir)
{
	int bytes_recibidos = 0, total = 0;
	int intentos = 0, fin_linea = 0;
	Arduino->WriteData((char*)mensaje_enviar, strlen(mensaje_enviar));
	Sleep(PAUSA_MS);
	bytes_recibidos = Arduino->ReadData(mensaje_recibir, sizeof(char) * MAX_BUFFER - 1);
	while ((bytes_recibidos > 0 || intentos < 1) && fin_linea == 0)
	{
		if (bytes_recibidos > 0)
		{
			total += bytes_recibidos;
			if (mensaje_recibir[total - 1] == 13 || mensaje_recibir[total - 1] == 10)
				fin_linea = 1;
		}
		else
			intentos++;
		Sleep(PAUSA_MS);
		bytes_recibidos = Arduino->ReadData(mensaje_recibir + total, sizeof(char) * MAX_BUFFER - 1);
	}
	if (total > 0)
		mensaje_recibir[total - 1] = '\0';
	return total;
}