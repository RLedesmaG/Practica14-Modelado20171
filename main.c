#include "main.h"

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
    //el principio de la lista
    Elemento* it = *lista;
    int arreglo[len];
    for(int i=0;i<len;i++){
        //ponemos en la posicion i del arreglo el valor del i-esimo elemento de la lista
        arreglo[i] = *(int *)it->valor;
        //avanzamos
        it = it->siguiente;
    }
    //se hace qsort con la función de comparación que sea
    qsort(arreglo, len, sizeof(int), (*cmp));
    it = *lista;
    for(int i=0;i<len;i++){
        //se cambia el valor del i-esimo elemento de la lista por el i-esimo del arreglo ordenado
        *(int *)it->valor = arreglo[i];
        it = it->siguiente;
    }
}

void borra_lista(Lista lista){
    Elemento* it = *lista;
    for(int i=0;i<longitud(lista);i++){
        //aux es necesario, pues liberamos it antes de poder hacer it = it->siguiente
        Elemento* aux = it->siguiente;
        //se libera el valor
        free(it->valor);
        //se libera el elemento
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
        //el siguiente del siguiente, para poder saltarnoslo
        Elemento* aux2 = aux1->siguiente;
        //se salta
        it->siguiente = aux2;
        //ya que el elemento aux no es siguiente de nadie, no está en la lista. lo liberamos a el y su valor
        free(aux1->valor);
        free(aux1);
        //se tiene que regresar un Elemento
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
    //se reserva el espacio para la Lista
    Lista lista = malloc(sizeof(Lista));
    return lista;
}

int inserta_elemento(Lista lista, void *valor){
    //se reserva el espacio del Elemento
    Elemento* nuevo = malloc(sizeof(Elemento));
    //se inserta un elemento al inicio de la lista. Sólo se insertó al inicio por simplicidad, se pudo insertar tambien al final
    nuevo->siguiente = *lista;
    nuevo->valor = valor;
    //el nuevo primer elemento de la lista es nuevo
    *lista = nuevo;
    return longitud(lista)+1;   
}

size_t longitud(Lista lista){
    if(*lista == NULL)
        return 0;

    size_t len = 1;
    Elemento* cabeza = *lista;
    Elemento* it = cabeza->siguiente;
    while(it != NULL){
        it = it->siguiente;
        len++;
    }
    return len;
}