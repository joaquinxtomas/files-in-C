#include <stdio.h>
#include <string.h>

typedef struct {
    char codAerolinea[11];
    int dia;
    int nVuelo;
    float costoPasaje;
    int Pasajeros;
}Vuelo;

typedef struct {
    int DNI;
    int nVuelo;
}Pasajero;

int main(){
    Vuelo vuelo1;
    Pasajero pasajero1;

    FILE *fVuelos, *fPasajeros, *fExportar;

    fVuelos = fopen("VUELOS.dat", "r+b");
    fPasajeros = fopen("PASAJEROS.dat", "rb");
    fExportar = fopen("Aero1.csv", "wb");

    if(fVuelos == NULL || fPasajeros == NULL || fExportar == NULL){
        perror("error al abrir el archivo.");
        getch();
        exit(1);
    }

    fread(&vuelo1,sizeof(Vuelo), 1 , fVuelos);
    while(!feof(fVuelos)){
        printf("%-15s%-5d%-5d%-10.2f%-20d\n", vuelo1.codAerolinea, vuelo1.dia, vuelo1.nVuelo, vuelo1.costoPasaje, vuelo1.Pasajeros);
        fread(&vuelo1,sizeof(Vuelo), 1 , fVuelos);
    }

    printf("\n\nPASAJEROS\n");

    fread(&pasajero1,sizeof(Pasajero), 1 , fPasajeros);
    while(!feof(fPasajeros)){
        printf("%-15d%-5d\n", pasajero1.DNI, pasajero1.nVuelo);
        fread(&pasajero1,sizeof(Pasajero), 1 , fPasajeros);
    }

    fprintf(fExportar, "Codigo;Dia;nVuelo;DNI\n");
    rewind(fVuelos);
    rewind(fPasajeros);
    fread(&vuelo1,sizeof(Vuelo), 1 , fVuelos);
    while(!feof(fVuelos)){
        rewind(fPasajeros);
        fread(&pasajero1, sizeof(Pasajero), 1, fPasajeros);
        while(!feof(fPasajeros)){
            if((strcmp(vuelo1.codAerolinea, "AERO1") == 0) && vuelo1.nVuelo == pasajero1.nVuelo){
                vuelo1.Pasajeros += 1;
                fseek(fVuelos, sizeof(Vuelo)*-1, SEEK_CUR);
                fwrite(&vuelo1, sizeof(Vuelo), 1, fVuelos);
                fflush(fVuelos);

                fprintf(fExportar, "%s;%d;%d;%d\n", vuelo1.codAerolinea, vuelo1.dia, vuelo1.nVuelo, pasajero1.DNI);
            }
            fread(&pasajero1, sizeof(Pasajero), 1, fPasajeros);
        }
        fread(&vuelo1, sizeof(Vuelo), 1, fVuelos);
    }


    fclose(fVuelos);
    fclose(fPasajeros);
    fclose(fExportar);

    fVuelos = fopen("VUELOS.dat", "r+b");


    if(fVuelos == NULL){
        perror("error al abrir el archivo.");
        getch();
        exit(1);
    }

    fread(&vuelo1,sizeof(Vuelo), 1 , fVuelos);
    while(!feof(fVuelos)){
        printf("%-15s%-5d%-5d%-10.2f%-20d\n", vuelo1.codAerolinea, vuelo1.dia, vuelo1.nVuelo, vuelo1.costoPasaje, vuelo1.Pasajeros);
        fread(&vuelo1,sizeof(Vuelo), 1 , fVuelos);
    }


}
