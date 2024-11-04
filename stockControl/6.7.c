#include <stdio.h>

typedef struct
{
    int codigo;
    char descripcion[51];
    int stock;
} Prod;

typedef struct {
    int codProducto;
    int faltante;
}Faltantes;

int main()
{
    int codProducto, cant, cantFaltante;

    Prod producto;
    Faltantes faltante1;

    FILE *fproductos, *faltantes;

    fproductos = fopen("stock.dat", "r+b");
    faltantes = fopen("faltantes.dat", "w+b");

    if(fproductos == NULL || faltantes == NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }

    printf("%-10s%-15s%-4s\n","Codigo","Desc", "Stock");
    fread(&producto, sizeof(Prod), 1, fproductos);
    while(!feof(fproductos)){
        printf("%-10d%-15s%-4d\n",producto.codigo,producto.descripcion, producto.stock);
        fread(&producto, sizeof(Prod), 1, fproductos);
    }

    printf("Ingrese el codigo del producto a vender: ");
    scanf("%d", &codProducto);

    while(codProducto != 0)
    {
        rewind(fproductos);
        fread(&producto, sizeof(Prod), 1, fproductos);
        while(!feof(fproductos))
        {
            if(codProducto == producto.codigo)
            {
                printf("Ingrese la cantidad vendida: ");
                scanf("%d", &cant);

                if(producto.stock >= cant)
                {
                    producto.stock = producto.stock - cant;

                    fseek(fproductos, sizeof(Prod)*-1, SEEK_CUR);
                    fwrite(&producto, sizeof(Prod), 1, fproductos);
                    fflush(fproductos);
                }
                else
                {
                    cantFaltante = cant - producto.stock;
                    producto.stock = 0;

                    fseek(fproductos, sizeof(Prod)*-1, SEEK_CUR);
                    fwrite(&producto, sizeof(Prod), 1, fproductos);
                    fflush(fproductos);

                    int encontrado = 0;
                    rewind(faltantes);
                    fread(&faltante1, sizeof(Faltantes), 1, faltantes);
                    while(!feof(faltantes)){
                        if(faltante1.codProducto == producto.codigo){
                            faltante1.faltante += cantFaltante;
                            encontrado = 1;
                        }
                        fwrite(&faltante1, sizeof(Faltantes), 1, faltantes);
                        fread(&faltante1, sizeof(Faltantes), 1, faltantes);
                    }

                    if(!encontrado){
                        faltante1.codProducto = producto.codigo;
                        faltante1.faltante = cantFaltante;
                        fwrite(&faltante1, sizeof(Faltantes), 1, faltantes);
                    }

                }

            }
            fread(&producto, sizeof(Prod), 1, fproductos);
        }
        printf("Ingrese el codigo del producto a vender: ");
        scanf("%d", &codProducto);
    }

    fclose(fproductos);
    fclose(faltantes);

    faltantes = fopen("faltantes.dat", "r");
    if (faltantes == NULL)
    {
        printf("Error al abrir el archivo 'faltantes.dat' para lectura.\n");
        exit(1);
    }

    printf("\nProductos con faltantes:\n");
    while(fread(&faltante1, sizeof(Faltantes), 1, faltantes))
    {
        printf("Codigo: %d  - Faltantes: %d\n", faltante1.codProducto, faltante1.faltante);
    }

    fclose(faltantes);

}
