#include <stdlib.h>
#include <stdio.h>

typedef int tElemLista;

typedef struct nodo{ //? TDA de un nodo
    tElemLista info; //* info de este elemento de la lista
    struct nodo *sig; //* Este es un puntero a un elemento tipo tNodo, pero omo aunn no le damos ese nombre, tenemos que llamarlo por struct nodo, que es el nombre real
}tNodo;

typedef struct //? TDA de una lista enlazada
{
    tNodo *head; //* Apunta al primer elemento de la lista
    tNodo *tail; //* Apunta al ultimo elemento de la lista
    tNodo *curr; //* Apunta al nodo actual en el que estamos en la lista
    unsigned int listSize; //* tamaño de la lista
    unsigned int pos; //* Indice del curr dentro de la lista (util por ejemplo para el getpos)
} tLinkedList;

void initList(tLinkedList *L)//? Inicializa una lista enlazada vacia 
{
    L->head = L->tail = L->curr = (*tNodo)malloc(sizeof(tNodo)); //* Se asigna el espacio necesario para que podamos incluir un puntero de tipo tNodo, en cada uno de los elementos del struct
    L->listSize = L->pos = 0;                                        //* Ambos se inicializan en 0 porque no tiene elementos aun, y si es que fueramos a agregar algo, se agregaria en la posicion 0
} 

void clear(tLinkedList *L) //? Vacia una lista, dejandola inicializada, pero vacia
{
    tNodo *next;
L->curr = L->head;
while (L->curr != NULL)
{
    next = L->curr->sig; //* Aqui decimos que el puntero tipo tNodo next almacenara el siguiente elemento de la lista, al que estamos revisando en este momento
    free(L->curr);
    L->curr = next;
    }
    L->head = L->tail = L->curr = (tNodo *)malloc(sizeof(tNodo));
    L->listSize = 0;
    L->pos = 0;
}

int insert(tLinkedList *L, tElemLista item) //? inserta un elemento en la poscion actual, y retorna la poscion en la que el elemento quedo
{
    tNodo *aux = L->curr->sig;
    L->curr->sig = (tNodo *)malloc(sizeof(tNodo)); //* En caso de crear un nuevo nodo en la lisa, hay que asignarle memoria suficiente para guardar la cantidad de datos que se le dara
    L->curr->sig->info = item;
    L->curr->sig->sig = aux;
    if (L->curr == L->tail)
        L->tail = L->curr->sig;
    L->listSize++;
    return L->pos;
}

int erase(tLinkedList *L) //? Elimina el elemento que esta en la posicion actual
{
    tNodo *aux; //* Puntero a nodo, auxiliar
    aux=L->curr->sig; //*
    L->curr->sig=L->curr->sig->sig;
    free(aux);//* Queremos liberar la memoria de aquello a lo que apunta aux
    L->listSize--;
    return 0; //* Retorna 0 si es que la eliminacion fue exitosa
}//? Elimina el elemento que esta en la posicion actual

void deleteList(tLinkedList *L) //? Elimina todos los elementos de la lista, borrando incluso la inicializacion de la lista
{
    tNodo *next;
    L->curr = L->head;
    while (L->curr != NULL)
    {
        next = L->curr->sig;
        free(L->curr);
        L->curr = next;
    }
}

void moveToStart(tLinkedList *L)//? Mueve el cursor de la lista al primer elemento (Hace que el curr que en la primera posicion)
{
    L->curr = L->head;
    L->pos = 0;
}

void moveToEnd(tLinkedList *L)//? Mueve el cursor de la lista al ultimo elemento (Hace que el curr que en la ultima posicion)
{
    L->curr = L->tail;
    L->pos = L->listSize;
}

void prev(tLinkedList *L) //? Mueve el cursor al elemento anterior de la lista
{
    if (L->curr == L->head)
        return; //* Si es que estabamos en el primer elemento, no hay nada mas que hacer a si que retornamos
    tNodo *temp = L->head; //* Colocamos un cursor auxiliar, para recorrer hata la posicion buscada desde el inicio
    while (temp->sig != L->curr){
        temp = temp->sig;}
    L->curr = temp; //* Ahora que ya alcanzamos con el cursor auxiliar la poscion anterior, cambiamos el curr a la posicion del cursor auxiliar
    L->pos--;//* Al retroceder un espacio, el numero del cursor disminuye en 1
}

int next(tLinkedList *L) //? Mueve el cursor a la posicion siguiente, si es que el actual es el tail, no hace nada
{
    if (L->curr != L->tail)
    {
        L->curr = L->curr->sig;
        L->pos++;
    }
    return L->pos;
}

void moveToPos(tLinkedList *L, unsigned int posicion)//? Mueve el cursor a una posicion, mientras que esta exista en la lista
{
    if (posicion < 0 || posicion > L->listSize)
        return; //* Si es que se entrega una posicion negativa, o mas grande que la lista, no es valido
    
    if (posicion == L->pos){//* CAMBIO PERSONAL: Si es que es igual, retorna, ya que no hay nada que hacer
        return;}

    else if (posicion > L->pos){ //* CAMBIO PERSONAL: Si es que es mayor que la posicion actual, avanza hasta llegar a la posicion
        posicion= next(L);}

    else{//* Si es que es menor, comienza a buscar desde el principio
        unsigned int i;
        L->curr = L->head;
        L->pos = 0;
        for (i = 0; i < posicion; i++){
            L->curr = L->curr->sig;
            L->pos++;
        }
    }
}

void printList(tLinkedList *L) //? Para printear una lista, funcion de la Gabi
{
    moveToStart(L);
    printf("[");
    int n = L->listSize;
    n--;
    for (int i = 0; i < n; i++)
    {
        printf("%d ,", L->curr->info);
        L->pos++;
        L->curr = L->curr->sig;
    }
    printf("%d]\n", L->curr->sig->info);
    moveToEnd(L);
}