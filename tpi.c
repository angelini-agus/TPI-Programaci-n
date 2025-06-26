#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int cargaPasajeros(char dnis[][999], char nombreApellido[240][99], int edad[240], char codDestino[240][5], int cantDestino[4]);
int validarDNI(char dni[]);

int main()
{
    int op;
    char dni[240][999];
    char nombreApellido[240][99];
    int edad[240];
    char codDestino[240][5];
    int cantDestino[4];
    //cantDestino[0]="BRA";
    //cantDestino[1]="MDQ";
    //cantDestino[2]="MDQ";
    //cantDestino[3]="MZA";
    //cantDestino[4]="BRC";
    cargaPasajeros(dni, nombreApellido, edad, codDestino, cantDestino);
    do
    {
        printf("Ingrese op sistema \n1. Mostrar lista de pasajeros ordenada por Apellido y Nombre \n2. Mostrar lista de pasajeros ordenada por Código Destino y Apellido - Nombre \n3. Mostrar lista de Destinos \n4. Buscar por pasajero \n5. Mostrar estadísticas \n6. Salir\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            // mostrarPasajerosAyN();
            break;
        case 2:
            // mostrarPasajerosCod();
            break;
        case 3:
            // mostrarDestinos();
            break;
        case 4:
            // buscarPasajero();
            break;
        case 5:
            // mostrarEstadisticas();
            break;
        case 6:
            printf("Chau");
            break;
        default:
            printf("Opcion invalida");
            break;
        }
    } while (op != 6);

    return 0;
}

int cargaPasajeros(char dnis[][999], char nombreApellido[240][99], int edad[240], char codDestino[240][5], int cantDestino[])
{
    int cant = 0;
    int validDni;
    do
    {
        printf("Ingrese la cantidad de pasajeros que desea ingresar (Max. 240)");
        scanf("%d", &cant);
    } while (cant < 0 || cant > 240);

    for (int i = 0; i < cant; i++)
    {
        do
        {
            printf("Ingrese el DNI");
            scanf("%s", dnis[i]);
            while (getchar() != '\n');//IMPORTANTE LIMPIAR EL BUFFER
            validDni = validarDNI(dnis[i]);
            if (validDni == 1)
            {
                printf("DNI Invalido");
            }
            else
            {
                printf("DNI Validado correctamente");
                printf("Ingrese el Apellido y Nombre");
                fgets(nombreApellido[i], 99, stdin);
                nombreApellido[i][strcspn(nombreApellido[i], "\n")] = '\0';
                printf("Ingrese la edad");
                scanf("%d",&edad[i]);
                // Limpiar buffer de entrada
                while (getchar() != '\n');
                int destinoValido = 0;
                do
                {
                    printf("Ingrese el codigo del destino al que se dirige\nBRA - MDQ - MZA - BRC: ");
                    fgets(codDestino[i], 5, stdin);
                    codDestino[i][strcspn(codDestino[i], "\n")] = '\0';

                    // Convertir a minusculas para comparar
                    for (int k = 0; codDestino[i][k]; k++) {
                        codDestino[i][k] = tolower(codDestino[i][k]);
                    }

                    if (strcmp(codDestino[i], "bra") == 0 && cantDestino[0] < 60) {
                        cantDestino[0]++;
                        destinoValido = 1;
                    } else if (strcmp(codDestino[i], "mdq") == 0 && cantDestino[1] < 60) {
                        cantDestino[1]++;
                        destinoValido = 1;
                    } else if (strcmp(codDestino[i], "mza") == 0 && cantDestino[2] < 60) {
                        cantDestino[2]++;
                        destinoValido = 1;
                    } else if (strcmp(codDestino[i], "brc") == 0 && cantDestino[3] < 60) {
                        cantDestino[3]++;
                        destinoValido = 1;
                    } else {
                        printf("El codigo que ingreso no es correcto o ya se alcanzo el maximo de 60 pasajeros para ese destino.\n");
                    }
                } while (destinoValido==0);
            }
        } while (validDni == 1);
    }
    return 0;
}

int validarDNI(char dni[])
{
    int longitud = 0;
    longitud = strlen(dni);
    if (longitud > 0)
    {
        for (int i = 0; i < longitud; i++)
        {
            if (!isdigit((unsigned char)dni[i]))
            {
                printf("El DNI solo debe contener números\n");
                return 1;
            }
        }
    }

    if (longitud == 7)
    {
        // Debe empezar con 5 o 6
        if (dni[0] == '5' || dni[0] == '6')
        {
            return 0;
        }
        else
        {
            printf("DNI de longitud 7 debe empezar con 5 o con 6\n");
            return 1;
        }
    }
    else if (longitud == 8)
    {
        // Debe empezar entre 10 y 60
        int primerosDos = (dni[0] - '0') * 10 + (dni[1] - '0');
        if (primerosDos >= 10 && primerosDos <= 60)
        {
            return 0;
        }
        else
        {
            printf("DNI de longitud 8 debe empezar con valores de 10-60\n");
            return 1;
        }
    }
    else
    {
        printf("Longitud de DNI debe ser de 7 u 8 caracteres\n");
        return 1;
    }
}
