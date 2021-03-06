#include <stdio.h>
#include <stdlib.h>

//Inicio definiciones del arbol en si (TDA)
typedef int tElem;

typedef struct tNodoABB typeNodoABB;

struct tNodoABB
{
    tElem item;
    struct tNodoABB *right;
    struct tNodoABB *left;

    //* El arbol es un struct, en el cual sus elementos no estan conectados, no dependen unos del otro, al ser un struct, solo estan
    //* refernciados entre si para denotar la estructura de arbol, pero si se borrara uno, sin ligarlos, no se perderia ningun dato, 
    //* como si pasa en las estructuras enlazadas. Por eso es que cada nodo tiene un identificador, para notar su valor.
};

typedef struct
{
    typeNodoABB *root;
    int nElems;
} tABB;


void initTree(tABB *T) //? Inicializar un ABB
{ //Inicializa el arbol
    T->root = NULL;
    T->nElems = 0;
}

void initNode(typeNodoABB *N, tElem item) //? Inicializar un nodo
{ 
    N->item = item;
    N->left = N->right = NULL;
}

int findHelp(typeNodoABB *nodo, tElem item)//? Auxiliar para find, el cual esta abajo
{
    if (nodo == NULL)
        return 1; //* OPCION 1: Arbol vacio. OPCION 2: Item no encontrado
    if (getValue(nodo) == item)
        return 0; //* Nodo encontrado
    if (item < getValue(nodo))
        return findHelp(nodo->left, item);//* Si es que el item que buscamos, es menor que en el que estabamos, buscamos por la izquierda
    else
        return findHelp(nodo->right, item); //* Si es que el item que buscamos, es mayor que en el que estabamos, buscamos por la iderecha
}

int find(tABB *T, tElem item) //? Revisa si hay un "item" en un ABB T, retorna 0 si encuentra, 1 en caso de no encontrarlo
{
    return findHelp(T->root, item);
}

int getValue(typeNodoABB *N)//*Obtiene el item de un nodo
{ 
    return N->item;
}

void insertHelp(typeNodoABB **N, typeNodoABB *initem) //? Auxiliar para insert, la cual esta abajo
{
    if (*N == NULL) //* OPCION 1: El arbol esta vacio y por eso es NULL y lo insertamos en la raiz. OPCION 2: Llegamos a la hoja correspondiente donde se debe insertar
        *N = initem; 
    else if (initem->item < getValue(*N))//
        return insertHelp(&(*N)->left, initem);//* Si es que el item del nodo a insertar es menor que el item del nodo actual, avanzamos a la izquierda
    else if (initem->item > getValue(*N))
        return insertHelp(&(*N)->right, initem);//* Si es que el item del nodo a insertar es mayor que el item del nodo actual, avanzamos a la derecha
}

void insert(tABB *T, tElem item)//? Insertar un nodo, queda en posicion de hoja
{
    //* Creamos un nodo, y le damos la memoria que necesita 
    typeNodoABB *newNode = (typeNodoABB *)malloc(sizeof(typeNodoABB)); //! ¿Seria mejor darle la memoria dentro de la funcion initNode?
    initNode(newNode, item); //* Aqui guardamos la info. en el nodo recien creado

    if (T->root == NULL)//* Si es que no hay ningun nodo en el arbol, el nodo recien creado, sera la raiz
    {
        T->root = newNode;
        T->nElems++;
    }
    else if (find(T, item)==0)//* Revisa si es que el item ya esta en el ABB
    {
        return;
    }
    else
    {
        insertHelp(&T->root, newNode);//* Si es que el arbol no esta vacio, ni contiene ya al item, se inserta el item
    }
}

void delHelp(typeNodoABB *nodo) //? Auxiliar para eliminar, clear y del mas abajo.
{
    if (nodo == NULL) //* Si es que el árbol esta vacío, no hay nada que hacer
        return;           
    delHelp(nodo->left);  //* Visita subárbol izquierdo del nodo actual, recursivamente
    delHelp(nodo->right); //* Visita subárbol derecho del nodo actual, recursivamente
    free(nodo);//* Después de borrar subárboles, se borra a sí mismo el nodo
}

void clear(tABB *T) //* Reinicializa el arbol, como vacio
{                     
    delHelp(T->root); //* Función auxiliar para eliminar todos los nodos
    T->root = NULL; //* Seteamos el ABB como vacio
    T->nElems = 0;
}

void del(tABB *T)
{
    delHelp(T->root); //* Borramos el arbol, lo dejamos sin inicializar
}

//! +*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*HASTA AQUI ESTA CHECKEADO +*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*+*

void inOrderHelp(typeNodoABB *nodo)
{
    if (nodo == NULL)
        return;
    inOrderHelp(nodo->left);    // visita hijo izquierdo en in-orden
    printf("%d, ", nodo->item); // procesa nodo actual
    inOrderHelp(nodo->right);   // visita hijo derecho en in-orden
}

void inOrden(tABB *T)
{ //Imprime en inOrden
    printf("[");
    inOrderHelp(T->root);
    printf("]\n");
}

void preOrderHelp(typeNodoABB *nodo)
{
    if (nodo == NULL)
        return;
    printf("%d, ", nodo->item); // procesa nodo actual
    preOrderHelp(nodo->left);   // visita hijo izquierdo en in-orden
    preOrderHelp(nodo->right);  // visita hijo derecho en in-orden
}

void preOrden(tABB *T)
{ //Imprime en preOrden
    printf("[");
    preOrderHelp(T->root);
    printf("]\n");
}

void postOrderHelp(typeNodoABB *nodo)
{
    if (nodo == NULL)
        return;
    postOrderHelp(nodo->left);  // visita hijo izquierdo en in-orden
    postOrderHelp(nodo->right); // visita hijo derecho en in-orden
    printf("%d, ", nodo->item); // procesa nodo actual
}

void postOrden(tABB *T)
{ //Imprime en postOrden
    printf("[");
    postOrderHelp(T->root);
    printf("]\n");
}



