#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int cargaPasajeros(char dnis[][999], char nombreApellido[240][99], int edad[240], char codDestino[240][99], int cantDestino[4], int *cantPasajeros);
int validarDNI(char dni[]);
void mostrarPasajerosAyN(char nombreApellido[240][99], char dni[240][999], int edad[240], char codDestino[240][99], int *cantPasajeros);

int main()
{
    int op;
    char dni[240][999];
    char nombreApellido[240][99];
    int edad[240];
    char codDestino[240][99];
    int cantDestino[4];
    int cantPasajeros;
    // cantDestino[0]="BRA";
    // cantDestino[1]="MDQ";
    // cantDestino[2]="MZA";
    // cantDestino[3]="BRC";
    cargaPasajeros(dni, nombreApellido, edad, codDestino, cantDestino, &cantPasajeros);
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
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion invalida\n");
            break;
        }
    } while (op != 6);

    return 0;
}

int cargaPasajeros(char dnis[][999], char nombreApellido[240][99], int edad[240], char codDestino[240][99], int cantDestino[4], int *cantPasajeros)
{
    int validDni;
    do
    {
        printf("Ingrese la cantidad de pasajeros que desea ingresar (Max. 240)\n");
        scanf("%d", cantPasajeros);
        if(*cantPasajeros < 0 || *cantPasajeros > 240)
        {
            printf("Excedio el limite.\n");
        }
    } while (*cantPasajeros < 0 || *cantPasajeros > 240);

    for (int i = 0; i < *cantPasajeros; i++)
    {
        do
        {
            printf("Ingrese el DNI: ");
            scanf("%s", dnis[i]);
            while (getchar() != '\n')
                ;
            // IMPORTANTE LIMPIAR EL BUFFER
            validDni = validarDNI(dnis[i]);
            if (validDni == 1)
            {
                printf("DNI Invalido\n");
            }
            else
            {
                printf("DNI Validado correctamente\n");
                printf("Ingrese el Apellido y Nombre: ");
                fgets(nombreApellido[i], 99, stdin);
                nombreApellido[i][strcspn(nombreApellido[i], "\n")] = '\0';
                printf("Ingrese la edad: ");
                scanf("%d", &edad[i]);
                // Limpiar buffer de entrada
                while (getchar() != '\n')
                    ;
                int destinoValido = 0;

                do
                {
                    printf("Ingrese el codigo del destino al que se dirige\nBRA - MDQ - MZA - BRC: ");
                    fgets(codDestino[i], 5, stdin);
                    codDestino[i][strcspn(codDestino[i], "\n")] = '\0';

                    // Convertir a minusculas para comparar
                    for (int k = 0; codDestino[i][k]; k++)
                    {
                        codDestino[i][k] = tolower(codDestino[i][k]);
                    }

                    if (strcmp(codDestino[i], "bra") == 0)
                    {
                        if (cantDestino[0] < 60)
                        {
                            cantDestino[0]++;
                            destinoValido = 1;
                        }
                        else
                        {
                            printf("Ya se alcanzo el maximo de 60 pasajeros para BRA.\n");
                        }
                    }
                    else if (strcmp(codDestino[i], "mdq") == 0)
                    {
                        if (cantDestino[1] < 60)
                        {
                            cantDestino[1]++;
                            destinoValido = 1;
                        }
                        else
                        {
                            printf("Ya se alcanzo el maximo de 60 pasajeros para MDQ.\n");
                        }
                    }
                    else if (strcmp(codDestino[i], "mza") == 0)
                    {
                        if (cantDestino[2] < 60)
                        {
                            cantDestino[2]++;
                            destinoValido = 1;
                        }
                        else
                        {
                            printf("Ya se alcanzo el maximo de 60 pasajeros para MZA.\n");
                        }
                    }
                    else if (strcmp(codDestino[i], "brc") == 0)
                    {
                        if (cantDestino[3] < 60)
                        {
                            cantDestino[3]++;
                            destinoValido = 1;
                        }
                        else
                        {
                            printf("Ya se alcanzo el maximo de 60 pasajeros para BRC.\n");
                        }
                    }
                    else
                    {
                        printf("El codigo que ingreso no es correcto.\n");
                    }
                } while (destinoValido == 0);
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
                printf("El DNI solo debe contener numeros\n");
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

void mostrarPasajerosAyN(char nombreApellido[240][99], char dni[240][999], int edad[240], char codDestino[240][99], int *cantPasajeros)
{
    int totalPasajeros = 0;

    // Primero contamos cuántos pasajeros hay según que el dni esté cargado (asumiendo que si dni[0] es '\0', no hay pasajero)
    for (int i = 0; i < 240; i++)
    {
        if (strlen(dni[i]) > 0)
            totalPasajeros++;
        else
            break; // Si llegamos a uno vacío, paramos el conteo
    }

    // Selection Sort por nombreApellido
    for (int i = 0; i < totalPasajeros - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < totalPasajeros; j++)
        {
            if (strcmp(nombreApellido[j], nombreApellido[minIndex]) < 0)
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            // Intercambiar nombreApellido
            char tempNombre[99];
            strcpy(tempNombre, nombreApellido[i]);
            strcpy(nombreApellido[i], nombreApellido[minIndex]);
            strcpy(nombreApellido[minIndex], tempNombre);

            // Intercambiar dni
            char tempDni[999];
            strcpy(tempDni, dni[i]);
            strcpy(dni[i], dni[minIndex]);
            strcpy(dni[minIndex], tempDni);

            // Intercambiar edad
            int tempEdad = edad[i];
            edad[i] = edad[minIndex];
            edad[minIndex] = tempEdad;

            // Intercambiar codDestino
            char tempCod[5];
            strcpy(tempCod, codDestino[i]);
            strcpy(codDestino[i], codDestino[minIndex]);
            strcpy(codDestino[minIndex], tempCod);
        }
    }

    // Mostrar pasajeros ordenados
    printf("Pasajeros ordenados por Apellido y Nombre:\n");
    for (int i = 0; i < totalPasajeros; i++)
    {
        printf("%d) Nombre y Apellido: %s, DNI: %s, Edad: %d, Codigo Destino: %s\n", i + 1, nombreApellido[i], dni[i], edad[i], codDestino[i]);
    }
}
