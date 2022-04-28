#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>

//Estructura que almacena los datos ingresados por el usuario
struct inType{
    int origen, destino, hora;
};

//Pide los datos al usuario y se comunica por medio de una tubería nombrada con búsqueda
// la cual recibe los datos del usuario y responde con el tiempo medio de viaje para imprimirlos,también
//se imprime su PID
int main(){
    struct inType *ingreso;
    ingreso = malloc(sizeof(struct inType));

    printf("PID INTERFAZ %d\n",getpid());

    printf("BIENVENIDO\nIngresar origen:");
    scanf("%i", &ingreso->origen);
    printf("Ingresar destino:");
    scanf("%i", &ingreso->destino);
    printf("Ingresar hora:");
    scanf("%i", &ingreso->hora);

    
    long inicio= clock();

    int fd;
//ESCRITURA EN TUBERÍA
    mkfifo("/tmp/mi_fifo",0666);

    fd=open("/tmp/mi_fifo",O_WRONLY);
    
    
    write(fd,ingreso,sizeof(struct inType));
    
    close(fd);    

///LECTURA DE TUBERIA

    float media;
    fd=open("/tmp/mi_fifo",O_RDONLY);

    read(fd,&media,sizeof(float));
    
    if (media == -1)
    {
        printf("NA\n");
    }
    else
    {
        printf("Tiempo de viaje medio:%f\n", media);
    }
    free(ingreso);
    close(fd);    
    long fin = clock();


    double tiempoTotal = (double)(fin-inicio)/CLOCKS_PER_SEC;
    printf("Tiempo total de ejecución:%lf Segundos\n",tiempoTotal);
}
