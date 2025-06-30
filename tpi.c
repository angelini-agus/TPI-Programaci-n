#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int cargaPasajeros(char dnis[][99], char nombreApellido[240][99], int edad[240], char codDestino[240][99], int cantDestino[4], int *cantPasajeros, int esCredito);
int validarDNI(char dni[]);
void mostrarPasajerosAyN(char nombreApellido[240][99], char dni[240][99], int edad[240], char codDestino[240][99], int *cantPasajeros);
void mostrarPasajerosCod(char nombreApellido[240][99], char dni[240][99], int edad[240], char codDestino[240][99], int *cantPasajeros);

int main()
{
    int op;
    char dni[240][99];
    char nombreApellido[240][99];
    int edad[240];
    char codDestino[240][99];
    int cantPasajeros;
    int cantDestino[4];
    int preciosDestinos[4] = {25000, 14000, 19000, 23000};
    // cantDestino[0]= "BRA"
    // cantDestino[1]= "MDQ"
    // cantDestino[2]= "MZA"
    // cantDestino[3]= "BRC"

    char esCredito[240][99];

    cargaPasajeros(dni, nombreApellido, edad, codDestino, cantDestino, &cantPasajeros, esCredito);

    //Menú
    do
    {
        printf("\n1. Mostrar lista de pasajeros ordenada por Apellido y Nombre \n2. Mostrar lista de pasajeros ordenada por Codigo Destino y Apellido - Nombre \n3. Mostrar lista de Destinos \n4. Buscar por pasajero \n5. Mostrar estadisticas \n6. Salir\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            mostrarPasajerosAyN(nombreApellido, dni, edad, codDestino, &cantPasajeros);
            break;
        case 2:
            mostrarPasajerosCod(nombreApellido, dni, edad, codDestino, &cantPasajeros);
            break;
        case 3:
            mostrarDestinos(codDestino, cantDestino, preciosDestinos, esCredito);
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

int cargaPasajeros(char dni[][99], char nombreApellido[240][99], int edad[240], char codDestino[240][99], int cantDestino[4], int *cantPasajeros, int esCredito)
{
    int validDni;
    do
    {
        printf("Ingrese la cantidad de pasajeros que desea ingresar (Max. 240)\n");
        scanf("%d", cantPasajeros);
        while (getchar() != '\n')
            ; // Limpiar buffer
        if (*cantPasajeros < 0 || *cantPasajeros > 240)
        {
            printf("Excedio el limite.\n");
        }
    } while (*cantPasajeros < 0 || *cantPasajeros > 240);

    for (int i = 0; i < *cantPasajeros; i++)
    {
        do
        {
            printf("\n%d) Ingrese el DNI: ", i + 1);
            scanf("%s", dni[i]);
            while (getchar() != '\n')
                ; // Limpiar buffer
            validDni = validarDNI(dni[i]);
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

                do
                {
                    printf("Ingrese la edad: ");
                    scanf("%d", &edad[i]);
                    while (getchar() != '\n')
                        ; // Limpiar buffer
                    if (edad[i] < 0 || edad[i] > 120)
                    {
                        printf("Edad invalida. Debe ser entre 0 y 120.\n");
                    }
                } while (edad[i] < 0 || edad[i] > 120);

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

void mostrarPasajerosAyN(char nombreApellido[240][99], char dni[240][99], int edad[240], char codDestino[240][99], int *cantPasajeros)
{
<<<<<<< Updated upstream
=======
    int totalPasajeros = 0;

    // Primero contamos cuántos pasajeros hay según que el dni esté cargado (asumiendo que si dni[0] es '\0', no hay pasajero)
    for (int i = 0; i < *cantPasajeros; i++)
    {
        if (strlen(dni[i]) > 0)
            totalPasajeros++;
        else
            break; // Si llegamos a uno vacío, paramos el conteo
    }

>>>>>>> Stashed changes
    // Selection Sort por nombreApellido
    for (int i = 0; i < *cantPasajeros - 1; i++)
    {
        int indiceMen = i;
        for (int j = i + 1; j < *cantPasajeros; j++)
        {
            if (strcmp(nombreApellido[j], nombreApellido[indiceMen]) < 0)
            {
                indiceMen = j;
            }
        }

        if (indiceMen != i)
        {
            char tempNombre[99];
            strcpy(tempNombre, nombreApellido[i]);
            strcpy(nombreApellido[i], nombreApellido[indiceMen]);
            strcpy(nombreApellido[indiceMen], tempNombre);

            char tempDni[99];
            strcpy(tempDni, dni[i]);
            strcpy(dni[i], dni[indiceMen]);
            strcpy(dni[indiceMen], tempDni);

            int tempEdad = edad[i];
            edad[i] = edad[indiceMen];
            edad[indiceMen] = tempEdad;

            char tempCod[5];
            strcpy(tempCod, codDestino[i]);
            strcpy(codDestino[i], codDestino[indiceMen]);
            strcpy(codDestino[indiceMen], tempCod);
        }
    }

    printf("Pasajeros ordenados por Apellido y Nombre:\n");
    for (int i = 0; i < *cantPasajeros; i++)
    {
        printf("%d) Nombre y Apellido: %s\tDNI: %s\tEdad: %d\tCodigo Destino: %s\n", i + 1, nombreApellido[i], dni[i], edad[i], codDestino[i]);
    }
}

void mostrarPasajerosCod(char nombreApellido[240][99], char dni[240][99], int edad[240], char codDestino[240][99], int *cantPasajeros)
{
    // Selection Sort por codDestino y luego por nombreApellido
    for (int i = 0; i < *cantPasajeros - 1; i++)
    {
        int indiceMen = i;
        for (int j = i + 1; j < *cantPasajeros; j++)
        {
            int cmpCod = strcmp(codDestino[j], codDestino[indiceMen]);
            if (cmpCod < 0 || (cmpCod == 0 && strcmp(nombreApellido[j], nombreApellido[indiceMen]) < 0))
            {
                indiceMen = j;
            }
        }

        if (indiceMen != i)
        {
            char tempNombre[99];
            strcpy(tempNombre, nombreApellido[i]);
            strcpy(nombreApellido[i], nombreApellido[indiceMen]);
            strcpy(nombreApellido[indiceMen], tempNombre);

            char tempDni[99];
            strcpy(tempDni, dni[i]);
            strcpy(dni[i], dni[indiceMen]);
            strcpy(dni[indiceMen], tempDni);

            int tempEdad = edad[i];
            edad[i] = edad[indiceMen];
            edad[indiceMen] = tempEdad;

            char tempCod[5];
            strcpy(tempCod, codDestino[i]);
            strcpy(codDestino[i], codDestino[indiceMen]);
            strcpy(codDestino[indiceMen], tempCod);
        }
    }

    printf("Pasajeros ordenados por Codigo Destino y Apellido-Nombre:\n");
    for (int i = 0; i < *cantPasajeros; i++)
    {
        printf("%d) Codigo Destino: %s\tApellido y Nombre: %s\tDNI: %s\tEdad: %d\n", i + 1, codDestino[i], nombreApellido[i], dni[i], edad[i]);
    }
}

void mostrarDestinos(char codDestino[240][99], int cantDestino[4], int preciosDestinos[4], char esCredito[240][99])
{
    int importeTotalDestinos = 0;
    for (int i = 0; i < 4; i++)
    {
        int importeDestino = 0;
        importeDestino = cantDestino[i] * preciosDestinos[i];
        importeTotalDestinos += cantDestino[i] * preciosDestinos[i];
        if (i == 0)
        {
            printf("BRA\tCantidad de pasajeros: %d\tImporte total del destino: %d\n", cantDestino[i], importeDestino);
        }
        if (i == 1)
        {
            printf("MDQ\tCantidad de pasajeros: %d\tImporte total del destino: %d\n", cantDestino[i], importeDestino);
        }
        if (i == 2)
        {
            printf("MZA\tCantidad de pasajeros: %d\tImporte total del destino: %d\n", cantDestino[i], importeDestino);
        }
        if (i == 3)
        {
            printf("BRC\tCantidad de pasajeros: %d\tImporte total del destino: %d\n", cantDestino[i], importeDestino);
        }
    }
    printf("El importe total de todos los destinos es: %d", importeTotalDestinos);
}