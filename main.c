#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %lu elementos\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %lu elementos\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento *borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %lu elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %lu elementos\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}

int cmp_int(const void* a, const void* b){
    int val1 = *(int *) a;
    int val2 = *(int *) b;

    if(val1 > val2)
        return 1;
    else if(val2 > val1)
        return -1;
    else return 0;
}

void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)){
    int len = longitud(lista);
    Elemento* it = *lista;
    int arreglo[len];
    for(int i=0;i<len;i++){
        arreglo[i] = *(int *)it->valor;
        it = it->siguiente;
    }
    qsort(arreglo, len, sizeof(int), (*cmp));
    it = *lista;
    for(int i=0;i<len;i++){
        *(int *)it->valor = arreglo[i];
        it = it->siguiente;
    }
}

void borra_lista(Lista lista){
    Elemento* it = *lista;
    for(int i=0;i<longitud(lista);i++){
        Elemento* aux = it->siguiente;
        free(it->valor);
        free(it);
        it = aux;
    }
}

Elemento *quita_elemento(Lista lista, size_t posicion){
    if(posicion >= longitud(lista))
        return NULL;
    Elemento *it = *lista;
    for(int i=1;i<posicion;i++){
        it = it->siguiente;
    }
        Elemento* aux1 = it->siguiente;
        Elemento* aux2 = aux1->siguiente;
        it->siguiente = aux2;
        free(aux1->valor);
        free(aux1);
        return NULL;
}

void imprime_lista_int(Lista lista){
    Elemento *it = *lista;
    for(int i=0;i<longitud(lista);i++){
        int aux = *(int *)it->valor;
        printf("%d ", aux);
        it = it->siguiente;
    }
    printf("\n");
}

Lista crea_lista(){
    Lista lista = malloc(sizeof(Lista));
    return lista;
}

int inserta_elemento(Lista lista, void *valor){
    Elemento* nuevo = malloc(sizeof(Elemento));
    nuevo->siguiente = *lista;
    nuevo->valor = valor;
    *lista = nuevo;
    return longitud(lista)+1;   
}

size_t longitud(Lista lista){
    if(*lista == NULL)
        return 0;

    int len = 1;
    Elemento* cabeza = *lista;
    Elemento* it = cabeza->siguiente;
    while(it != NULL){
        it = it->siguiente;
        len++;
    }
    return len;
}