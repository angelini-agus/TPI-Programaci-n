#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define maxPasajeros 240

void cargaPasajeros(char dnis[][99], char nombreApellido[maxPasajeros][99], int edad[maxPasajeros], char codDestino[maxPasajeros][99], int cantDestino[4], int *cantPasajeros, char esCredito[maxPasajeros][99]);
int validarDNI(char dni[]);
void mostrarPasajerosAyN(char nombreApellido[maxPasajeros][99], char dni[maxPasajeros][99], int edad[maxPasajeros], char codDestino[maxPasajeros][99], int *cantPasajeros);
void mostrarPasajerosCod(char nombreApellido[maxPasajeros][99], char dni[maxPasajeros][99], int edad[maxPasajeros], char codDestino[maxPasajeros][99], int *cantPasajeros);
void mostrarDestinos(char codDestino[maxPasajeros][99], int cantDestino[4], int preciosDestinos[4], char esCredito[maxPasajeros][99], int *cantPasajeros, int edad[maxPasajeros]);
void buscarPasajero(char nombreApellido[maxPasajeros][99], char dni[maxPasajeros][99], int edad[maxPasajeros], char codDestino[maxPasajeros][99], int *cantPasajeros, int preciosDestinos[4], char esCredito[maxPasajeros][99]);
void mostrarEstadisticas(int cantDestino[4], int *cantPasajeros, char codDestino[maxPasajeros][99], int edad[maxPasajeros]);

int main()
{
    int op;
    char dni[maxPasajeros][99];
    char nombreApellido[maxPasajeros][99];
    int edad[maxPasajeros];
    char codDestino[maxPasajeros][99];
    int cantPasajeros;
    int cantDestino[4] = {0};
    int preciosDestinos[4] = {25000, 14000, 19000, 23000};
    // cantDestino[0]= "BRA"
    // cantDestino[1]= "MDQ"
    // cantDestino[2]= "MZA"
    // cantDestino[3]= "BRC"

    char esCredito[maxPasajeros][99];

    cargaPasajeros(dni, nombreApellido, edad, codDestino, cantDestino, &cantPasajeros, esCredito);

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
            mostrarDestinos(codDestino, cantDestino, preciosDestinos, esCredito, &cantPasajeros, edad);
            break;
        case 4:
            buscarPasajero(nombreApellido, dni, edad, codDestino, &cantPasajeros, preciosDestinos, esCredito);
            break;
        case 5:
            mostrarEstadisticas(cantDestino, &cantPasajeros, codDestino, edad);
            break;
        case 6:
            printf("Saliendo del programa...\nMuchas gracias!");
            break;
        default:
            printf("Opcion invalida\n");
            break;
        }
    } while (op != 6);

    return 0;
}

void cargaPasajeros(char dni[][99], char nombreApellido[maxPasajeros][99], int edad[maxPasajeros], char codDestino[maxPasajeros][99], int cantDestino[4], int *cantPasajeros, char esCredito[maxPasajeros][99])
{
    int validDni;
    do
    {
        printf("Ingrese la cantidad de pasajeros que desea ingresar (Max. 240)\n");
        scanf("%d", cantPasajeros);
        while (getchar() != '\n')
            ;
        if (*cantPasajeros < 0 || *cantPasajeros > maxPasajeros)
        {
            printf("Excedio el limite.\n");
        }
    } while (*cantPasajeros < 0 || *cantPasajeros > maxPasajeros);

    for (int i = 0; i < *cantPasajeros; i++)
    {
        do
        {
            printf("\n%d) Ingrese el DNI: ", i + 1);
            scanf("%s", dni[i]);
            while (getchar() != '\n')
                ;
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
                    printf("Abona con tarjeta de credito? (s/n): ");
                    fgets(esCredito[i], 5, stdin);
                    esCredito[i][strcspn(esCredito[i], "\n")] = '\0';
                    if (esCredito[i][0] != 's' && esCredito[i][0] != 'n' && esCredito[i][0] != 'S' && esCredito[i][0] != 'N')
                    {
                        printf("Respuesta invalida. Ingrese 's' o 'n'.\n");
                    }
                } while (esCredito[i][0] != 's' && esCredito[i][0] != 'n' && esCredito[i][0] != 'S' && esCredito[i][0] != 'N');

                do
                {
                    printf("Ingrese la edad: ");
                    scanf("%d", &edad[i]);
                    while (getchar() != '\n')
                        ;
                    if (edad[i] < 0 || edad[i] > 120)
                    {
                        printf("Edad invalida. Debe ser entre 0 y 120.\n");
                    }
                } while (edad[i] < 0 || edad[i] > 120);

                int destinoValido = 0;
                do
                {
                    printf("Ingrese el codigo del destino al que se dirige\nBRA - MDQ - MZA - BRC: ");
                    fgets(codDestino[i], 99, stdin);
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
}

int validarDNI(char dni[])
{
    int longitud = 0;
    longitud = strlen(dni);
    if (longitud > 0)
    {
        for (int i = 0; i < longitud; i++)
        {
            if (!isdigit((unsigned char)dni[i])) // Comprueba que lo que se ingresa sean solo numero (entra el if si no es un digito)
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
        int primerosDos = (dni[0] - '0') * 10 + (dni[1] - '0'); // restarle el 0 lo pasa de caracter a valor numerico
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

void mostrarPasajerosAyN(char nombreApellido[maxPasajeros][99], char dni[maxPasajeros][99], int edad[maxPasajeros], char codDestino[maxPasajeros][99], int *cantPasajeros)
{
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

void mostrarPasajerosCod(char nombreApellido[maxPasajeros][99], char dni[maxPasajeros][99], int edad[maxPasajeros], char codDestino[maxPasajeros][99], int *cantPasajeros)
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

void mostrarDestinos(char codDestino[maxPasajeros][99], int cantDestino[4], int preciosDestinos[4], char esCredito[maxPasajeros][99], int *cantPasajeros, int edad[maxPasajeros])
{
    float importeTotalDestinos = 0;
    float importeDestino[4] = {0, 0, 0, 0};

    for (int i = 0; i < *cantPasajeros; i++)
    {
        int idDestino = -1;
        if (strcmp(codDestino[i], "bra") == 0)
            idDestino = 0;
        else if (strcmp(codDestino[i], "mdq") == 0)
            idDestino = 1;
        else if (strcmp(codDestino[i], "mza") == 0)
            idDestino = 2;
        else if (strcmp(codDestino[i], "brc") == 0)
            idDestino = 3;

        if (idDestino != -1)
        {
            float importe;
            if (edad[i] < 5) {
                importe = 2000.0; // Seguro para menores de 5 años
            } else {
                importe = preciosDestinos[idDestino];
                if (esCredito[i][0] == 's' || esCredito[i][0] == 'S')
                {
                    importe = (importe * 1.05); // recargo 5%
                }
            }
            importeDestino[idDestino] += importe;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        float impDestino = importeDestino[i];
        importeTotalDestinos += importeDestino[i];
        if (i == 0)
        {
            printf("BRA\tCantidad de pasajeros: %d\tImporte total del destino: %.2f\n", cantDestino[i], impDestino);
        }
        if (i == 1)
        {
            printf("MDQ\tCantidad de pasajeros: %d\tImporte total del destino: %.2f\n", cantDestino[i], impDestino);
        }
        if (i == 2)
        {
            printf("MZA\tCantidad de pasajeros: %d\tImporte total del destino: %.2f\n", cantDestino[i], impDestino);
        }
        if (i == 3)
        {
            printf("BRC\tCantidad de pasajeros: %d\tImporte total del destino: %.2f\n", cantDestino[i], impDestino);
        }
    }
    printf("El importe total de todos los destinos es: %.2f\n", importeTotalDestinos);
}

void buscarPasajero(char nombreApellido[maxPasajeros][99], char dni[maxPasajeros][99], int edad[maxPasajeros], char codDestino[maxPasajeros][99], int *cantPasajeros, int preciosDestinos[4], char esCredito[maxPasajeros][99])
{
    char dniBuscado[99];
    int validDni, encontrado = 0;

    do
    {
        printf("Ingrese el DNI del pasajero a buscar: ");
        scanf("%s", dniBuscado);
        while (getchar() != '\n')
            ; // Limpiar buffer

        validDni = validarDNI(dniBuscado);
        if (validDni == 1)
        {
            printf("DNI invalido. Intente nuevamente.\n");
        }
    } while (validDni == 1);

    for (int i = 0; i < *cantPasajeros; i++)
    {
        if (strcmp(dni[i], dniBuscado) == 0)
        {
            printf("\nPasajero encontrado:\n");
            printf("Apellido y nombre: %s\n", nombreApellido[i]);
            printf("DNI: %s\n", dni[i]);
            printf("Edad: %d\n", edad[i]);
            printf("Codigo de Destino: %s\n", codDestino[i]);

            float importe = 0;

            if (edad[i] < 5) {
                importe = 2000.0;
                printf("Forma de pago: Seguro para menores de 5 años\n");
            } else {
                if (strcmp(codDestino[i], "bra") == 0)
                    importe = preciosDestinos[0];
                else if (strcmp(codDestino[i], "mdq") == 0)
                    importe = preciosDestinos[1];
                else if (strcmp(codDestino[i], "mza") == 0)
                    importe = preciosDestinos[2];
                else if (strcmp(codDestino[i], "brc") == 0)
                    importe = preciosDestinos[3];

                if (esCredito[i][0] == 's' || esCredito[i][0] == 'S')
                {
                    importe = (importe * 1.05);
                    printf("Forma de pago: Tarjeta de credito (5%% recargo)\n");
                }
                else
                {
                    printf("Forma de pago: Efectivo\n");
                }
            }

            printf("Importe a abonar: $%.2f\n", importe);

            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("No existe pasajero con ese DNI.\n");
    }
}

void mostrarEstadisticas(int cantDestino[4], int *cantPasajeros, char codDestino[maxPasajeros][99], int edad[maxPasajeros])
{
    char *nombresDestinos[4] = {"BRA", "MDQ", "MZA", "BRC"};
    int menoresPorDestino[4] = {0, 0, 0, 0};

    // Porcentaje pasajeros x destino
    printf("\n--- Estadisticas ---\n");
    printf("a) Porcentaje de pasajeros por destino:\n");

    for (int i = 0; i < 4; i++)
    {
        float porcentaje;
        if (*cantPasajeros > 0)
        {
            porcentaje = (cantDestino[i] * 100.0 / *cantPasajeros);
        }
        else
        {
            porcentaje = 0;
        }
        printf("%s: %.2f%%\n", nombresDestinos[i], porcentaje);
    }

    // Destino +solicitado
    int max = cantDestino[0];
    int iMax = 0;
    for (int i = 1; i < 4; i++)
    {
        if (cantDestino[i] > max)
        {
            max = cantDestino[i];
            iMax = i;
        }
    }
    printf("\nb) Destino mas solicitado: %s con %d pasajeros\n", nombresDestinos[iMax], max);

    // c) Porcentaje de menores 5 años por destino + acum
    for (int i = 0; i < *cantPasajeros; i++)
    {
        if (edad[i] < 5)
        {
            if (strcmp(codDestino[i], "bra") == 0)
                menoresPorDestino[0]++;
            else if (strcmp(codDestino[i], "mdq") == 0)
                menoresPorDestino[1]++;
            else if (strcmp(codDestino[i], "mza") == 0)
                menoresPorDestino[2]++;
            else if (strcmp(codDestino[i], "brc") == 0)
                menoresPorDestino[3]++;
        }
    }

    printf("\nc) Porcentaje de menores de 5 anios por destino:\n");
    for (int i = 0; i < 4; i++)
    {
        float porcentajeMenores;
        if (cantDestino[i] > 0)
        {
            porcentajeMenores = (menoresPorDestino[i] * 100.0 / cantDestino[i]);
        }
        else
        {
            porcentajeMenores = 0;
        }
        printf("%s: %.2f%% de menores de 5 anios\n", nombresDestinos[i], porcentajeMenores);
    }
}
