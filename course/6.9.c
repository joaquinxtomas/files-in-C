#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int dni;
    char nombreCompleto[21];
    int pagado;
} Alumno;

Alumno Busqueda(int alumno, FILE *archInscriptos);
Alumno InscribirAlumno();

int main(){

    FILE *archInscriptos, *archInteresados;

    archInscriptos = fopen("INSCRIPTOS.dat", "r+b");
    archInteresados = fopen("interesados.dat", "wb");

    if(archInscriptos == NULL || archInteresados == NULL){
        printf("error al abrir el archivo.");
        getch();
        exit(1);
    }

    Proceso(archInscriptos, archInteresados);
    verArchivo(archInscriptos);

    fclose(archInscriptos);
    fclose(archInteresados);
}

void Proceso(FILE *archInscriptos, FILE *archInteresados){
    int dni, pagar, cantRegistros = 0;
    Alumno alumno;

    do{
        printf("Ingrese el dni del alumno: ");
        scanf("%d", &dni);
        if((dni < 10000000 || dni > 99999999) && dni >= 0){
            printf("dni incorrecto, ingreselo nuevamente.\n");
        }
    } while((dni < 10000000 || dni > 99999999) && dni >= 0);

    while(dni > 0){

        alumno = Busqueda(dni, archInscriptos);
        if(alumno.dni != -1){
            do{
                system("cls");
                printf("Desea pagar la inscripcion? (1 si - 0 no): ");
                scanf("%d", &pagar);
                if(pagar < 0 || pagar > 1){
                    printf("Solo puede presionar 1 o 0\n");
                }
            } while(pagar < 0 || pagar > 1);

            if(pagar == 1 && alumno.pagado == 0){
                alumno.pagado = 1;
            } else {
                alumno.pagado = 0;
            }

            fseek(archInscriptos, sizeof(Alumno)*-1, SEEK_CUR);
        } else {
            if(cantRegistros < 60){
                alumno = InscribirAlumno();
                fseek(archInscriptos, 0 ,SEEK_END);
            } else {
                AnotarEnInteresados(archInteresados);
            }
        }

        fwrite(&alumno, sizeof(Alumno), 1, archInscriptos);
        fflush(archInscriptos);

        system("cls");
        cantRegistros = contarRegistros(archInscriptos);
        printf("cantidad de registros: %d\n", cantRegistros);

        do{
            printf("Ingrese el dni del alumno: ");
            scanf("%d", &dni);
            if((dni < 10000000 || dni > 99999999) && dni >= 0){
                printf("dni incorrecto, ingreselo nuevamente.\n");
            }
        } while((dni < 10000000 || dni > 99999999) && dni >= 0);
    }
}

int contarRegistros(FILE *archInscriptos){
    int cant = 0;
    rewind(archInscriptos);
    Alumno alumno;
    fread(&alumno,sizeof(Alumno), 1, archInscriptos);
    while(!feof(archInscriptos)){
        cant++;
        fread(&alumno, sizeof(Alumno), 1, archInscriptos);
    }
    return cant;
}

Alumno Busqueda(int dni, FILE *archInscriptos){
    Alumno alumno;
    int encontrado = 0;
    rewind(archInscriptos);
    fread(&alumno, sizeof(Alumno), 1, archInscriptos);
    while(!feof(archInscriptos) && !encontrado){
        if(alumno.dni == dni){
            encontrado = 1;
        } else {
            fread(&alumno, sizeof(Alumno), 1, archInscriptos);
        }
    }
    if(!encontrado){
        alumno.dni = -1;
    }

    return alumno;
}

Alumno InscribirAlumno(){
    char nombre[21];
    int dni;
    Alumno alumno;
    system("cls");
    printf("Vamos a inscribirte en el curso!\n");
    getchar();
    printf("Ingrese el nombre del alumno: ");
    LeerTexto(nombre, 21);

    do{
        printf("Ingrese el dni del alumno: ");
        scanf("%d", &dni);
        if(dni < 10000000 || dni > 99999999){
            printf("el dni es incorrecto, ingreselo nuevamente.\n");
        }
    }while(dni < 10000000 || dni > 99999999);

    alumno.dni = dni;
    strcpy(alumno.nombreCompleto,nombre);
    alumno.pagado = 0;

    return alumno;
}

void LeerTexto(char texto[], int largo){
    int i;
    fgets(texto, largo, stdin);
    i = 0;
    while(texto[i] != '\0'){
        if(texto[i] == '\n'){
            texto[i] = '\0';
        } else {
            i++;
        }
    }
}

void AnotarEnInteresados(FILE *archInteresados){
    char nombre[21];
    int dni;
    Alumno alumno;

    printf("Te anotaremos para futuros cursos!\n");
    printf("Ingrese el nombre del alumno: ");
    LeerTexto(nombre, 21);

    do{
        printf("Ingrese el dni del alumno: ");
        scanf("%d", &dni);
        if(dni < 10000000 || dni > 99999999){
            printf("el dni es incorrecto, ingreselo nuevamente.\n");
        }
    }while(dni < 10000000 || dni > 99999999);

    alumno.dni = dni;
    strcpy(alumno.nombreCompleto,nombre);
    alumno.pagado = 0;

    fwrite(&alumno, sizeof(Alumno), 1, archInteresados);
}

void verArchivo(FILE *arch){
    Alumno alumno;

    fread(&alumno, sizeof(Alumno), 1, arch);
    while(!feof(arch)){
        printf("%-10d%-21s%-2d\n", alumno.dni, alumno.nombreCompleto, alumno.pagado);
        fread(&alumno,sizeof(Alumno), 1, arch);
    }
}
