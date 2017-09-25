/*
	Estructura usada para representar al grafo de coautorias
*/

#define MAX_NODES 1500001
#define MAX_STRING 50

typedef struct grafo{
	ListaPair* adj[MAX_NODES]; //Lista de adyacencia
	char name[MAX_NODES][MAX_STRING]; //Arreglo de strings (Guardara los nombres)
	double pagerankAnt[MAX_NODES], pagerankNew[MAX_NODES]; //Arreglos utiles para el calculo del pagerank
	double degree[MAX_NODES]; //Arreglo que almacena el degree de cada nodo
	double closeness[MAX_NODES]; //Arreglo que almacena el closeness de cada nodo
	int numNodos; //Numero de nodos en el grafo
}TGrafo;

void grafo_crear(TGrafo* G){
	for(int i = 0; i < MAX_NODES; i ++){
		G->adj[i] = malloc(sizeof(ListaPair*)); //Reservamos memoria para cada lista
		lista_crear(G->adj[i]); //Y la creamos
	}
	G->numNodos = 0;
}

void grafo_insertarArista(TGrafo *G, int u, int v, double w){
	pair p1; p1.fst = w; p1.snd = v;
	lista_insertarElemento(G->adj[u], p1 ); 
	/*Se inserta el par (w,v) a la lista de adyacencia de u, lo cual significa que existira
	  una arista dirigida desde u hacia v con peso w*/
}
