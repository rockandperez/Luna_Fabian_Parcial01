#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <string.h>
#include <cstdio>
#include <iostream>
#include "Funciones.h"
#include "Tarjetas.h"
#include "Viajes.h"

using namespace std;


/// -------- PROTOTIPOS DE LAS FUNCIONES ----------

int menuPpal();
void viajesSegunTarjeta();
void viajeMenorImporte();
void mesMaxSubte();
void viajesMayoColectivo();
void viajeMayorimporte();
void viajesTarjetasActivas();
bool validarTarjeta(char *);


/// -------- DESARROLLO DE LAS FUNCIONES ----------

int menuPpal()
{
    int opcion;

    while(true)
    {
        system("cls");
        cout << endl;
        cout << "---------------------" << endl;
        cout << "-- MENU PRINCIPAL --" << endl;
        cout << "---------------------" << endl;
        cout << "1) VIAJES SEGÚN TARJETA" << endl;
        cout << "2) VIAJE MENOR IMPORTE" << endl;
        cout << "3) VIAJE EN SUBTE MAYOR IMPORTE" << endl;
        cout << "4) VIAJES EN MAYO COLECTIVO SEGÚN TARJETA" << endl;
        cout << "5) VIAJE MAYOR IMPORTE" << endl;
        cout << "6) VIAJES DE TARJETAS ACTIVAS" << endl;
        cout << endl;
        cout << "0) SALIR DEL PROGRAMA" << endl;
        cout << "---------------------" << endl;
        cout << endl;
        cout << "OPCION: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion)
        {
        case 1:
        {
            system("cls");
            viajesSegunTarjeta();
            system("pause");
            break;
        }
        case 2:
        {
            system("cls");
            cout << endl;
            cout << "   ------------------------" << endl;
            cout << "   -  VIAJE MENOR IMPORTE -" << endl;
            cout << "   ------------------------" << endl;
            viajeMenorImporte();
            system("pause");
            break;
        }
        case 3:
        {
            system("cls");
            cout << endl;
            cout << "   ----------------------------------" << endl;
            cout << "   -  VIAJE EN SUBTE MAYOR IMPORTE  -" << endl;
            cout << "   ----------------------------------" << endl;
            mesMaxSubte();
            system("pause");
            break;
        }
        case 4:
        {
            system("cls");
            cout << endl;
            cout << "   -----------------------------------------------" << endl;
            cout << "   -  VIAJES DE MAYO EN COLECTIVO SEGÚN TARJETA  -" << endl;
            cout << "   -----------------------------------------------" << endl;
            viajesMayoColectivo();
            system("pause");
            break;
        }
        case 5:
        {
            system("cls");
            cout << endl;
            cout << "   --------------------------" << endl;
            cout << "   -   VIAJE MAYOR IMPORTE  -" << endl;
            cout << "   --------------------------" << endl;
            viajeMayorimporte();
            system("pause");
            break;
        }
        case 6:
        {
            system("cls");
            cout << endl;
            cout << "   --------------------------------" << endl;
            cout << "   -  VIAJES DE TARJETAS ACTIVAS  -" << endl;
            cout << "   --------------------------------" << endl;
            viajesTarjetasActivas();
            system("pause");
            break;
        }

        case 0:
        {
            system("cls");
            cout << endl;
            cout << "   ----------------------------------" << endl;
            cout << "   - GRACIAS POR USAR ESTE PROGRAMA -" << endl;
            cout << "   ----------------------------------" << endl;
            return 0;
            break;
        }

        default:
        {
            cout << "   Opción incorrecta" << endl;
            system("pause");
            break;
        }
        }
    }
}

///PUNTO 1-------- VIAJES SEGÚN TARJETA -------------------------------

void viajesSegunTarjeta()
{
    FILE* archivoViajes = fopen("Viajes.dat", "rb"); // Abre el archivo de viajes en modo lectura binaria
    if (archivoViajes==NULL)
    {
        cout << "No se pudo abrir el archivo Viajes.dat" << endl;
    }

    FILE* archivoTarjetas = fopen("Tarjetas.dat", "rb"); // Abre el archivo de tarjetas en modo lectura binaria
    if (archivoTarjetas==NULL)
    {
        cout << "No se pudo abrir el archivo Tarjetas.dat" << endl;
        fclose(archivoViajes); // Cierra el archivo de viajes antes de salir
    }

    char numeroTarjetaUsuario[6];

    // Solicitar al usuario un número de tarjeta
    cout << endl;
    cout << "   ------------------------" << endl;
    cout << "   - VIAJES SEGÚN TARJETA -" << endl;
    cout << "   ------------------------" << endl;
    cout << endl;
    cout << "Ingrese el número de tarjeta: ";
    cin.getline(numeroTarjetaUsuario,6);

    // Comprobar validez de la tarjeta ingresada
    if (validarTarjeta(numeroTarjetaUsuario)==true)
    {
        Viajes viaje;
        int cantidadColectivo = 0;
        int cantidadSubte = 0;
        int cantidadTren = 0;

        // Leer cada registro en el archivo de viajes
        while (fread(&viaje, sizeof(Viajes), 1, archivoViajes) == 1)
        {
            // Verificar si el número de tarjeta coincide con el ingresado por el usuario
            if (strcmp(viaje.numeroTarjeta, numeroTarjetaUsuario) == 0)
            {
                // Incrementar el contador correspondiente al medio de transporte
                switch (viaje.medioTransporte)
                {
                case 1:
                    cantidadColectivo++;
                    break;
                case 2:
                    cantidadSubte++;
                    break;
                case 3:
                    cantidadTren++;
                    break;
                }
            }
        }
        // Mostrar la cantidad de viajes discriminada por medio de transporte
        cout << endl;
        cout << "Cantidad de viajes en Colectivo: " << cantidadColectivo << endl;
        cout << "Cantidad de viajes en Subte: " << cantidadSubte << endl;
        cout << "Cantidad de viajes en Tren: " << cantidadTren << endl;
        cout << endl;
    }
    else
    {
        cout << "Numero de tarjeta inexistente" << endl;
        cout << endl;
    }

    fclose(archivoTarjetas); // Cierra el archivo de tarjetas
    fclose(archivoViajes);   // Cierra el archivo de viajes
}


///PUNTO 2--------- VIAJE MENOR IMPORTE ------------------------------

void viajeMenorImporte()
{
    FILE* archivo = fopen("Viajes.dat", "rb"); // Abre el archivo en modo lectura binaria
    if(archivo==NULL)
    {
        cout << "No se pudo abrir el archivo Viajes.dat" << endl;
    }
    else
    {
        Viajes viaje;
        bool primerViaje = true; // Variable bandera para el primer viaje
        float importeMinimo;    // Almacenará el importe mínimo encontrado

        while (fread(&viaje, sizeof(Viajes), 1, archivo) == 1)
        {
            // La primera vez se inicializa importeMinimo con el importe del primer viaje
            if (primerViaje)
            {
                importeMinimo = viaje.importeViaje;
                primerViaje = false;
            }
            else
            {
                // Si se encuentra un importe menor, se actualiza importeMinimo
                if (viaje.importeViaje < importeMinimo)
                {
                    importeMinimo = viaje.importeViaje;
                }
            }
        }

        fclose(archivo); // Cierra el archivo

        if (primerViaje)
        {
            cout << "No se encontraron registros en el archivo" << endl;
        }
        else
        {
            cout << "El Viaje con el importe mínimo encontrado es: $" << importeMinimo << endl;
        }
        cout << endl;

    }
}


///PUNTO 3-------- VIAJE EN SUBTE MAYOR IMPORTE  ----------------------------

void mesMaxSubte()
{
    FILE* archivo = fopen("Viajes.dat", "rb"); // Abre el archivo en modo lectura binaria
    if(archivo==NULL)
    {
        cout << "No se pudo abrir el archivo Viajes.dat" << endl;
    }
    float totalesPorMes[12] = {0.0}; // Inicializa un vector con totales por mes
    Viajes viaje;
    while (fread(&viaje, sizeof(Viajes), 1, archivo) == 1)
    {
        if (viaje.medioTransporte == 2)
        {
            totalesPorMes[viaje.mesViaje - 1] += viaje.importeViaje; // Suma el importe al mes correspondiente
        }
    }
    fclose(archivo); // Cierra el archivo

    // Encuentra el mes con el importe máximo
    float importeMaximo = totalesPorMes[0];
    int mesMaximo = 1;
    for (int i = 1; i < 12; ++i)
    {
        if (totalesPorMes[i] > importeMaximo)
        {
            importeMaximo = totalesPorMes[i];
            mesMaximo = i + 1;
        }
    }
    if (importeMaximo == 0)
    {
        cout << "No se encontraron registros en Subte" << endl;
    }
    else
    {
        cout << "El mes " << mesMaximo << " fue el de mayor recaudación por viajes en Subte, con un total de $" << importeMaximo << endl;
    }
    cout <<""<<endl;
}


///PUNTO 4-------  VIAJES DE MAYO EN COLECTIVO SEGÚN TARJETA  --------------------------

void viajesMayoColectivo()
{

    FILE* archivoViajes = fopen("Viajes.dat", "rb"); // Abre el archivo de viajes en modo lectura binaria
    FILE* archivoTarjetas = fopen("Tarjetas.dat", "rb"); // Abre el archivo de tarjetas en modo lectura binaria
    if (archivoViajes==NULL || archivoTarjetas==NULL)
    {
        cout << "No se pudieron abrir los archivos" << endl;
    }
    cout << endl;
    Viajes viaje;
    Tarjetas tarjeta;

    // Leer cada registro en el archivo de tarjetas
    while (fread(&tarjeta, sizeof(Tarjetas), 1, archivoTarjetas) == 1)
    {
        int cantidadViajes = 0;
        // Leer cada registro en el archivo de viajes
        while (fread(&viaje, sizeof(Viajes), 1, archivoViajes) == 1)
        {
            // Verificar si el número de tarjeta coincide y si el medio de transporte es 1 y el mes es mayo (mes 5)
            if (strcmp(viaje.numeroTarjeta, tarjeta.numeroTarjeta) == 0 &&
                    viaje.medioTransporte == 1 &&
                    viaje.mesViaje == 5)
            {
                cantidadViajes++;
            }
        }
        // Mostrar la cantidad de viajes para la tarjeta actual
        cout << "Número de tarjeta: " << tarjeta.numeroTarjeta << endl;
        cout << "Cantidad de viajes en Mayo en colectivo: " << cantidadViajes << endl;
        cout << endl;
        // Volver al inicio del archivo de viajes para la siguiente tarjeta
        fseek(archivoViajes, 0, SEEK_SET);
    }

    fclose(archivoTarjetas); // Cierra el archivo de tarjetas
    fclose(archivoViajes);   // Cierra el archivo de viajes
}


///PUNTO 5-------  VIAJE MAYOR IMPORTE  --------------------------------

void viajeMayorimporte()
{
    FILE* archivoViajes = fopen("Viajes.dat", "rb"); // Abre el archivo de viajes en modo lectura binaria
    if (archivoViajes==NULL)
    {
        cout << "No se pudo abrir el archivo Viajes.dat" << endl;
    }

    FILE* archivoTarjetas = fopen("Tarjetas.dat", "rb"); // Abre el archivo de tarjetas en modo lectura binaria
    if (archivoTarjetas==NULL)
    {
        cout << "No se pudo abrir el archivo Tarjetas.dat" << endl;
        fclose(archivoViajes); // Cierra el archivo de viajes antes de salir
    }

    Viajes viaje;
    Tarjetas tarjeta;

    float importeMaximo = 0;
    char numeroTarjetaMaximo[6];
    char dniDuenioMaximo[9];
    char numeroViajeMaximo[5];

    // Leer cada registro en el archivo de viajes
    while (fread(&viaje, sizeof(Viajes), 1, archivoViajes) == 1)
    {
        if (viaje.importeViaje > importeMaximo)
        {
            importeMaximo = viaje.importeViaje;
            strcpy(numeroViajeMaximo, viaje.numeroViaje);
        }
    }

    // Volver al inicio del archivo de viajes
    fseek(archivoViajes, 0, SEEK_SET);

    // Buscar el número de tarjeta y el DNI del dueño correspondiente al número de viaje con el importe máximo
    while (fread(&viaje, sizeof(Viajes), 1, archivoViajes) == 1)
    {
        if (strcmp(viaje.numeroViaje, numeroViajeMaximo) == 0)
        {
            strcpy(numeroTarjetaMaximo, viaje.numeroTarjeta);
            // Buscar la tarjeta correspondiente en el archivo de tarjetas
            fseek(archivoTarjetas, 0, SEEK_SET);
            while (fread(&tarjeta, sizeof(Tarjetas), 1, archivoTarjetas) == 1)
            {
                if (strcmp(tarjeta.numeroTarjeta, numeroTarjetaMaximo) == 0)
                {
                    strcpy(dniDuenioMaximo, tarjeta.dniDuenio);
                    break;
                }
            }
            break; // Detener la búsqueda, ya se encontró la tarjeta
        }
    }
    fclose(archivoTarjetas); // Cierra el archivo de tarjetas
    fclose(archivoViajes);   // Cierra el archivo de viajes

    // Mostrar los resultados
    cout <<endl;
    cout << "Número de Viaje con Mayor Importe: " << numeroViajeMaximo << endl;
    cout << "Número de Tarjeta: " << numeroTarjetaMaximo << endl;
    cout << "DNI del Dueño: " << dniDuenioMaximo << endl;
    cout <<endl;
}

///PUNTO 6--------  VIAJES DE TARJETAS ACTIVAS  -------------------------------

void viajesTarjetasActivas()
{
    FILE* archivoViajes = fopen("Viajes.dat", "rb"); // Abre el archivo de viajes en modo lectura binaria
    if (archivoViajes==NULL)
    {
        cout << "No se pudo abrir el archivo Viajes.dat" << endl;
    }

    FILE* archivoTarjetas = fopen("Tarjetas.dat", "rb"); // Abre el archivo de tarjetas en modo lectura binaria
    if (archivoTarjetas==NULL)
    {
        cout << "No se pudo abrir el archivo Tarjetas.dat" << endl;
        fclose(archivoViajes); // Cierra el archivo de viajes antes de salir
    }

    Viajes viaje;
    Tarjetas tarjeta;

    // Leer cada registro en el archivo de tarjetas
    while (fread(&tarjeta, sizeof(Tarjetas), 1, archivoTarjetas) == 1)
    {
        if (tarjeta.estado == 1) // Verificar si el estado es 1
        {
            float importeTotal = 0;
            // Leer cada registro en el archivo de viajes
            while (fread(&viaje, sizeof(Viajes), 1, archivoViajes) == 1)
            {
                // Verificar si el número de tarjeta coincide
                if (strcmp(viaje.numeroTarjeta,tarjeta.numeroTarjeta) == 0)
                {
                    importeTotal += viaje.importeViaje; // Sumar el importe al total
                }
            }
            // Mostrar el importe total gastado para la tarjeta actual
            cout << "Número de Tarjeta: " << tarjeta.numeroTarjeta <<endl;
            cout << "Importe Total Gastado: " << importeTotal << endl;
            cout << endl;
            // Volver al inicio del archivo de viajes para la siguiente tarjeta
            fseek(archivoViajes, 0, SEEK_SET);
        }
    }
    fclose(archivoViajes);   // Cierra el archivo de viajes
    fclose(archivoTarjetas); // Cierra el archivo de tarjetas
}

///FUNCIONES AUXILIARES -------------------------


bool validarTarjeta (char *tarjeta)
{
    FILE* archivoTarjetas = fopen("Tarjetas.dat","rb");;
    Tarjetas numTarjeta;

    if(archivoTarjetas==NULL)
    {
        cout << "Error de Archivo" << endl;
    }
    else
    {
        while(fread(&numTarjeta,sizeof(Tarjetas),1,archivoTarjetas)==1)
        {
            if (strcmp(tarjeta,numTarjeta.numeroTarjeta)==0)
            {
                fclose(archivoTarjetas);
                return true;
            }
        }
    }
    fclose(archivoTarjetas);
    return false;
}

#endif // FUNCIONES_H_INCLUDED
