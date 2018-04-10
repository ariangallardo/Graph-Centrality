/*
	Lista enlazada de pares, util para la representacion del grafo
*/

typedef pair TElemLista;

typedef struct nodo {
    TElemLista info;
    struct nodo *sig;
}Nodo;

typedef struct lista{
    Nodo *ini;
    Nodo *fin;
    int nElementos;
}ListaPair;

//Creacion de la lista
void lista_crear(ListaPair *L) {
    L->ini = NULL;
    L->fin = NULL;
    L->nElementos = 0;
}

//Retorna si la lista esta vacia
int lista_estaVacia(ListaPair *L) {
    return (L->nElementos == 0);
}

//Insertar elemento a la lista
void lista_insertarElemento(ListaPair *L, TElemLista e) {
    Nodo *nodo = malloc(sizeof(Nodo));	
	 assert(nodo); //Se verifica que no hubo error al reservar memoria para el nodo
    //Asignar los valores al nodo
    nodo->info = e;
    nodo->sig = NULL;
    if(lista_estaVacia(L)) { //Si la lista esta vacia, asignar el inicio al nodo entrante
	   L->ini = nodo;
    } 
    else { //Sino, asignar el siguiente del final al nodo entrante
        L->fin->sig = nodo;
	}        
    L->fin = nodo;
    (L->nElementos)++; //Incrementar el numero de elementos de la lista
}

//Finalizar la lista (limpiar memoria)
void lista_finalize(ListaPair* L){
    Nodo* cur = L->ini;
    while(cur){
        Nodo* tmp = cur->sig;
        free(cur);
        cur = tmp;
    }
}
