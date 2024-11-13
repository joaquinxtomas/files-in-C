/*
6.9 Se dispone de un archivo denominado INSCRIPTOS.dat que contiene la informacion de los inscriptos a un
curso de programacion. El archivo aun no esta completo ya que la inscripcion se realiza por partes. Por cada
inscripto se tiene la siguiente informacion:
- DNI (entero)
- Apellido y Nombres (texto de 20 caracteres maximo)
- Pagado (campo entero donde 1 indica que pago y 0 que aun adeuda la matricula)
Se desea realizar un programa que cumpla con dos funciones:
a. Registrar los pagos de los alumnos ya inscriptos.
b. SI hay cupo, agregar nuevos inscriptos (el cupo maximo es de 60 alumnos).
El programa solicitara el ingreso del DNI y lo buscara entre los inscriptos, en caso de que lo encuentre dara
la opcion para registrar el pago (si es que no esta pago ya). En caso de que no lo encuentre dara la opcion
para inscribirlo al curso (el pago se realiza luego). En el momento que ya no quede cupo en el curso si llega
un nuevo inscripto se le preguntara si desea quedar registrado para un curso futuro, y en caso afirmativo
se le solicitara el telefono y se guardara el nombre, DNI y telefono en un archivo Interesados.dat.
El ingreso de datos finaliza con un DNI negativo.
*/

#include <stdio.h>
#include <string.h>

struct Alumno
{
    int dni;
    char nombreApellido[21];
    int pagado;
};

struct AlumnoInteresado
{
    int dni;
    char nombreApellido[21];
    int telefono;
};

struct Alumno buscarInscripto(FILE*, int);
struct Alumno InscribirAlumno(int);

int main()
{

    int dni, paga, conteoRegistros = 0;
    struct Alumno alu, alu2;
    struct AlumnoInteresado aluint;

    FILE *archInscriptos, *archInteresados;
    archInscriptos = fopen("INSCRIPTOS.DAT", "r+b");
    archInteresados = fopen("INTERESADOS.DAT", "wb");

    if(archInscriptos == NULL || archInteresados == NULL)
    {
        printf("Error al abrir el archivo.\n");
        getch();
        exit(1);
    }

    LeerArchivoInscriptos(archInscriptos);



    do
    {
        printf("Ingrese el DNI del alumno: ");
        scanf("%d", &dni);

        if((dni < 9999999 || dni > 99999999) && dni > 0)
        {
            printf("DNI fuera de rango.\n");
        }
    }
    while((dni < 9999999 || dni > 99999999) && dni > 0);


    while(dni > 0)
    {
        conteoRegistros = ftell(archInscriptos) / sizeof(struct Alumno);

        if(conteoRegistros < 15)
        {
            alu = buscarInscripto(archInscriptos, dni);

            if(alu.dni != -1)
            {
                printf("Desea realizar el pago?\n1-SI\n2-NO\n");
                scanf("%d", &paga);
                if(paga == 1)
                {
                    alu.pagado = 1;
                    fseek(archInscriptos, sizeof(struct Alumno)*-1, SEEK_CUR);
                    fwrite(&alu, sizeof(struct Alumno), 1, archInscriptos);
                }
                else
                {
                    printf("Este alumno ya ha pagado.\n");
                }
            }
            else
            {
                printf("\nVamos a inscribir al alumno.\n");
                alu2 = InscribirAlumno(dni);
                fseek(archInscriptos, 0, SEEK_END);
                fwrite(&alu2, sizeof(struct Alumno), 1, archInscriptos);
            }
        } else {
            printf("\n\nCUPOS LLENOS. Vamos a inscribirte en un listado de nuestros interesados.\n");
            printf("Ingresa tu nombre: ");
            fflush(stdin);
            LeerTexto(aluint.nombreApellido, 21);

            printf("Ingrese su numero de telefono: ");
            scanf("%d", &aluint.telefono);

            aluint.dni = dni;


            fseek(archInteresados, 0, SEEK_END);
            fwrite(&aluint, sizeof(struct AlumnoInteresado), 1, archInteresados);

        }



        do
        {
            printf("Ingrese el DNI del alumno: ");
            scanf("%d", &dni);

            if((dni < 9999999 || dni > 99999999) && dni > 0)
            {
                printf("DNI fuera de rango.\n");
            }
        }
        while((dni < 9999999 || dni > 99999999) && dni > 0);
    }

    fclose(archInscriptos);
    fclose(archInteresados);

    LeerInteresados();




}


struct Alumno buscarInscripto(FILE *arch, int dni)
{
    struct Alumno alu;
    int encontrado = 0;

    fseek(arch, 0, SEEK_SET);
    fread(&alu, sizeof(struct Alumno), 1, arch);
    while (!feof(arch) && !encontrado)
    {
        if (alu.dni == dni)
        {
            encontrado = 1;
        }
        else
        {
            fread(&alu, sizeof(struct Alumno), 1, arch);
        }
    }
    if (!encontrado)
    {
        alu.dni = -1;
    }
    return alu;
}



struct Alumno InscribirAlumno(int dni)
{
    struct Alumno alu;

    printf("Ingrese el nombre y apellido del alumno: ");
    fflush(stdin);
    LeerTexto(alu.nombreApellido, 21);

    alu.dni = dni;
    alu.pagado = 0;

    return alu;

};

void LeerTexto(char texto[], int largo)
{
    int i;
    fgets(texto, largo, stdin);
    i = 0;
    while(texto[i] != '\0')
    {
        if(texto[i] == '\n')
        {
            texto[i] = '\0';
        }
        else
        {
            i++;
        }
    }
}

void LeerArchivoInscriptos(FILE *arch)
{

    struct Alumno alu;

    fread(&alu, sizeof(struct Alumno), 1, arch);
    while(!feof(arch))
    {
        printf("DNI: %d\n", alu.dni);
        printf("Nombre y apellido: %s\n", alu.nombreApellido);
        printf("Pagado: %d\n", alu.pagado);
        fread(&alu, sizeof(struct Alumno), 1, arch);
    }


}

void LeerInteresados(){
    struct AlumnoInteresado aluint;
    FILE *archInteresados;
    archInteresados = fopen("INTERESADOS.DAT", "rb");

    if(archInteresados == NULL){
        printf("Error al abrir el archivo.\n");
        getch();
        exit(1);
    }

    printf("%10s%21s%10s\n", "DNI", "NOMBRE Y APELLIDO", "TELEFONO");
    fread(&aluint, sizeof(struct AlumnoInteresado),1,archInteresados);
    while(!feof(archInteresados)){
        printf("%10d%21s%10d\n", aluint.dni, aluint.nombreApellido, aluint.telefono);
        fread(&aluint, sizeof(struct AlumnoInteresado), 1, archInteresados);
    }
    fclose(archInteresados);
}


