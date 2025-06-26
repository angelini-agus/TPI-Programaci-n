#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    int op;
    char dni[240][999];
    cargaPasajeros(dni);
    do
    {
        printf("Ingrese op sistema \n1. Mostrar lista de pasajeros ordenada por Apellido y Nombre \n2. Mostrar lista de pasajeros ordenada por Código Destino y Apellido - Nombre \n3. Mostrar lista de Destinos \n4. Buscar por pasajero \n5. Mostrar estadísticas \n6. Salir\n");
        scanf("%d",op);
        switch (op)
        {
        case 1:
            mostrarPasajerosAyN();
            break;
        case 2:
            mostrarPasajerosCod();
            break;
        case 3:
            mostrarDestinos();
            break;
        case 4:
            buscarPasajero();
            break;
        case 5:
            mostrarEstadisticas();
            break;
        case 6:
            printf("Chau");
            break;
        default:
            printf("Opcion invalida");
            break;
        }
    } while (op!=6);
    
    return 0;
}

int cargaPasajeros(char dnis[][999]){
    int cant=0;
    int validDni;
    do
    {
        printf("Ingrese la cantidad de pasajeros que desea ingresar");
        scanf("%d",cant);
    } while (cant<0 || cant>240);
    for(int i=0; i<cant; i++){
        do
        {
            printf("Ingrese el DNI");
            scanf("%s",dnis[i]);
            validDni=validarDNI(dnis[i]);
            if(validDni==1){
                printf("DNI Invalido");
            }
            else{

            }
        } while ();
    }
    
    
    return 0;
}

int validarDNI(char dni[]){
    int longitud=0;
    longitud=strlen(dni);
    while (longitud>8 || longitud<7); 
    /*PRUEBA*/
    
    return 0;
}
