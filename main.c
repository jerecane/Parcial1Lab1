#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pila.h"
#include <conio.h>


#define ESC 27
#define DIM_TEMPERATURAS 50


void muestraPila (Pila p, char titulo[]);
void cargaPilaUsuario (Pila *p, char titulo[]);
void muestraArray(int t[], int validos, char titulo[]);
void pasaPila (Pila *origen, Pila *destino);
void cargaPilaRandom (Pila *p, int cant);
void copiaMenoresMayores (Pila ORIGEN, Pila *MENORES, Pila *MAYORES);
int buscaMenor (Pila *p);
int cuentaTEMP (Pila p, int valor);
int cuentaPila (Pila p);
int sumaTemp (Pila TEMP, int mayores);
int cargaArrayOrdenado (int t[], int dim, Pila TEMP);





int main()
{
    srand(time(NULL));

    Pila TEMPERATURAS;
    Pila MENORES;
    Pila MAYORES;

    inicpila(&TEMPERATURAS);
    inicpila(&MENORES);
    inicpila(&MAYORES);

    int arrayTemperaturas [DIM_TEMPERATURAS];

    int valTemp = 0;

    int valor = 14;
    int tempMayor = 10;

    cargaPilaRandom(&TEMPERATURAS, 40);

    muestraPila(TEMPERATURAS, "Pila [TEMPERATURAS]");
    system("pause");
    system("cls");

    copiaMenoresMayores(TEMPERATURAS, &MENORES, &MAYORES);
    printf("Se pasaron los elementos menores a 0 a la pila [MENORES] y el resto a [MAYORES]");
    muestraPila(TEMPERATURAS, "Pila [TEMPERATURAS]");
    muestraPila(MENORES, "Pila [MENORES]");
    muestraPila(MAYORES, "Pila [MAYORES]");

    printf("---La temperatura menor es: <%02d>\n\n", buscaMenor(&TEMPERATURAS));
    system("pause");
    system("cls");

    printf("---La cantidad de temperaturas mayores a <%02d> es: <%02d>", valor, cuentaTEMP(TEMPERATURAS, valor));
    muestraPila(TEMPERATURAS, "Pila [TEMPERATURAS]");
    system("pause");
    system("cls");

    printf("---La suma de las temperaturas mayores a <%02d> es: <%02d>", tempMayor, sumaTemp(TEMPERATURAS, tempMayor));
    muestraPila(TEMPERATURAS, "Pila [TEMPERATURAS]");
    system("pause");
    system("cls");

    valTemp = cargaArrayOrdenado(arrayTemperaturas, DIM_TEMPERATURAS, TEMPERATURAS);

    muestraArray(arrayTemperaturas, valTemp, "Se ordenaron los elementos de la pila al Array de forma ordenada");
    printf("\n\n");

    return 0;
}


int rangoNumeros (int min, int max)
{
    return rand() % (max-min) + min;
}

void cargaPilaRandom (Pila *p, int cant)
{
    int min;
    int max;

    printf("---Ingrese el valor minimo de TEMPeraturas>>> ");
    scanf("%d", &min);
    system("cls");

    printf("---Ingrese el valor maximo de TEMPeraturas>>> ");
    scanf("%d", &max);
    system("cls");
    for (int i=0; i<cant; i++)
    {
        apilar(p, rangoNumeros(min, max));
    }
}


void muestraPila (Pila p, char titulo[])
{
    Pila AUX;

    inicpila(&AUX);
    int i = 0;

    pasaPila(&p, &AUX);

    printf("\n\n\t\t%s", titulo);
    printf("\n");
    while (!pilavacia(&AUX))
    {
        printf(" %02d |", tope(&AUX));
        apilar(&p, desapilar(&AUX));
        i++;
        if (i%15 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}

void cargaPilaUsuario (Pila *p, char titulo[])
{
    char opcion = 0;
    int num;
    do
    {

        if(opcion != ESC)
        {
            printf("\n\n%s", titulo);
            scanf("%d", &num);
            apilar(p, num);
        }
        printf("Presione <ENTER> para agregar un valor a la pila o <ESC> para salir");
        opcion = getch();
        system("cls");
    }
    while (opcion != ESC);
}

void muestraArray(int t[], int validos, char titulo[])
{
    printf("\n\n%s", titulo);
    for(int i=0; i<validos; i++)
    {
        if (i % 20 == 0)
        {
            printf("\n\n");
        }
        printf("[%02d]~", t[i]);
    }
}

void pasaPila (Pila *origen, Pila *destino)
{
    while (!pilavacia(origen))
    {
        apilar(destino, desapilar(origen));
    }
}

void copiaMenoresMayores (Pila ORIGEN, Pila *MENORES, Pila *MAYORES)
{
    while (!pilavacia(&ORIGEN))
    {
        if (tope(&ORIGEN) <= 0)
        {
            apilar(MENORES, desapilar(&ORIGEN));
        }
        else
        {
            apilar(MAYORES, desapilar(&ORIGEN));
        }
    }
}


int buscaMenor (Pila *p)
{
    Pila AUX;
    inicpila(&AUX);

    int menor;

    if (!pilavacia(p))
    {
        menor = desapilar(p);
        while (!pilavacia(p))
        {
            if (tope(p) < menor)
            {
                apilar(&AUX, menor);
                menor = desapilar(p);
            }
            else
            {
                apilar(&AUX, desapilar(p));
            }
        }
    }
    pasaPila(&AUX, p);
    return menor;
}

int cuentaTEMP (Pila p, int valor)
{
    Pila AUX;
    inicpila(&AUX);

    int cont = 0;

    while (!pilavacia(&p))
    {
        if (tope(&p) > valor)
        {
            cont++;
        }
        apilar(&AUX, desapilar(&p));
    }
    return cont;
}


int sumaTemp (Pila TEMP, int mayores)
{
    Pila AUX;
    inicpila(&AUX);

    int acum = 0;

    while (!pilavacia(&TEMP))
    {
        if (tope(&TEMP) > mayores)
        {
            acum = acum + tope(&TEMP);
        }
        apilar(&AUX, desapilar(&TEMP));
    }
    return acum;
}


int cuentaPila (Pila p)
{
    Pila AUX;
    inicpila(&AUX);

    int i = 0;

    while (!pilavacia(&p))
    {
        apilar(&AUX, desapilar(&p));
        i++;
    }
    return i;
}

int cargaArrayOrdenado (int t[], int dim, Pila TEMP)
{

    int val = 0;

    while (!pilavacia(&TEMP) && val < dim)
    {
        t[val] = buscaMenor(&TEMP);
        val++;
    }
    return val;
}
