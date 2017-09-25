/******************************************************************
				  Pontificia Universidad Catolica del Peru
				    Facultad de Ciencias e Ingenieria
							Ingenieria Informatica
							
		 Tarea Academica No.2 del curso de Algoritmia (INF263)						
	
	Tema: "Algoritmos de Centralidad aplicados a Red de autorias"
	
	Integrantes:
		Gallardo Callalli Arian
		Avila Flores Patricio
		Gilvonio Oscanoa Neus
		Guillen Zapata Handry

	Horario: 0582
	Profesor: Msc. Marco Sobrevilla Cabezudo
	
									2017-1

														Desarrollado en ANSI C
							SO: Linux Mint, Ubuntu Mate, Windows 7 y 10
******************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "pair.h" //Pair structure
#include "listaPair.h" //Linked list of pair
#include "graph.h" //Graph structure
#include "priority_queue.h" //Min Heap structure

/*---Declaracion de constantes usadas en los procedimientos siguientes---*/

#define INF 1e18 //Infinito (double)
#define oo 1e9 //Infinito (int)

/*-----------------------------------------------------------------------*/

FILE* logfile; //Archivo en el que se guardara el proceso de ejecucion del programa

/*---Algoritmo de Dijkstra---*/

/*
	En esta funcion se hace uso de la TAD llamada Cola de Prioridad (priority_queue), implementada
	anteriormente en la libreria auxiliar "priority_queue.h". Esta TAD nos permitira manejar las
	distancias minimas y el nodo destino en tiempo aproximado a O(log(n)).
	
	OJO: La cola de prioridad almacena PARES (duplas) de elementos.
	
	La cola de prioridad ordenara los elementos de menor a mayor, en orden lexicografico. Es decir:
		P(x1,y1) < Q(x2,y2) <-> (x1 < x2) || (x1 == x2) && (y1 < y2)
		
	Asi, al extraer la cabeza contaremos con la dupla con menor "x", cuyo valor corresponde a la distancia.
	
	Variables importantes:
		
		-> double dist[MAX_NODES]: Almacenara la distancia con la que se ha llegado a cada nodo en cada momento
								  de la ejecucion del algoritmo.
		
		-> priority_queue pq: Cola de prioridad utilizada para poder encontrar el nodo con menor distancia en tiempo
									 logaritmico.	
									 
		-> int src: Nodo inicial. 
*/

double dist[MAX_NODES];

double dijkstra(TGrafo* G, int src){
	for(int i = 1; i < G->numNodos +1; i++) dist[i] = INF;
	pair source; source.fst = 0; source.snd = src; //La distancia al nodo source es 0
	priority_queue pq;
	pq_init(&pq);
	pq_push(&pq, source); dist[src] = 0;
	while(pq.count != 0){
		pair front = pq_top(&pq);
		double d = front.fst; int u = front.snd;
		if(d > dist[u]) continue; //De haber llegado a este nodo con una distancia menor a la que se esta analizando, no continuar
		Nodo* cur = G->adj[u]->ini;
		while(cur){
			double peso = cur->info.fst; int v = cur->info.snd;
			if(dist[u] + peso < dist[v]){ //Si podemos llegar a este nodo con una distancia menor a la previamente calculada, ingresar
				dist[v] = dist[u] + peso;
				pair np;
				np.fst = dist[v]; np.snd = v;
				pq_push(&pq, np); //Insertar en la cola la nueva distancia junto a su nodo correspondiente
			}
			cur = cur->sig;
		}
	}
	
	// En el siguiente bucle, se calcula la suma de distancias totales en la isla correspondiente al nodo src.
	double ret = 0;
	for(int i = 1; i < G->numNodos + 1; i++){
		if(dist[i] != INF){
			ret += dist[i];
		}
	}
	pq_finalize(&pq); //Finalizamos la cola de prioridad
	return ret;
}

/*-----------------------------------------------------------------------*/

/*---Algoritmo de Closeness Centrality---*/

/*
	Este algoritmo calcula el coeficiente Closeness para cada nodo, de la siguiente manera (pseudocodigo):
	
	idImportante <- -1
	maximo_closeness <- 0
	Para cada nodo N en G:
		closeness <- suma de Dijkstras desde nodo N
		Si closeness > maximoCloseness:
			idImportante <- N
			maximo_closeness <- closeness
		Fin Si
	Fin Para
	
	retornar idImportante
	
	Variables Importantes:
		-> double close: Variable que almacenara el closeness por cada nodo
		
		-> double closeMax: Variable que almacenara el MAXIMO closeness de todos los nodos
		
		-> int idImp: Almacenara el ID del nodo con mayor closeness.
		
*/

int getCloseness(TGrafo* G){
	double close, closeMax = 0;
	int idImp;
	for(int id = 1; id < G->numNodos+1; id++){
		close = dijkstra(G, id); //Aqui, close almacenara la suma de todas las distancias minimas desde el nodo con ID igual a "id".
		if(close > closeMax){ //Si el valor calculado es mayor, actualizar al id mas importante
			idImp = id;
			closeMax = close;
		}
		G->closeness[id]  = close;
		if(id%100 == 0){ //Imprimir resultado cada 100 nodos para verificar que el programa se esta ejecutando
			fprintf(logfile, "Closeness terminado para el nodo %d\n", id);
			fprintf(logfile, "Resultado-> Closeness = %.2f\n",close);
			fprintf(logfile,"----------------------------------------\n");
		}
	}
	return idImp;
}

/*-----------------------------------------------------------------------*/

/*---Algoritmo de Degree Centrality---*/

/*
	Se calcula el degree Centrality de cada nodo de la siguiente manera:
		
	Para cada nodo, se miran a las aristas que salen de dicho nodo y se suman sus pesos. Este valor resultante
	es el valor del degree centrality del nodo en cuestion.
	
	Variables Importantes:
		
		-> double maxDegree: Variable que almacenara el maximo degree centrality de todos los nodos
		
		-> int idImp: Almacenara el ID del nodo con mayor degree centrality
		
		-> double degree: Acumulara el degree centrality por cada nodo a analizar.

*/

int getDegree(TGrafo* G){
	double maxDegree = -1;
	int idImp;
	for(int id = 1; id < G->numNodos+1; id++){
		double degree = 0;
		Nodo* u = G->adj[id]->ini;
		while(u){
			degree += u->info.fst;
			u = u->sig;
		}
		G->degree[id] = degree;
		if(maxDegree < degree){
			idImp = id;
			maxDegree = degree;
		}
		if(id %100 == 0) fprintf(logfile, "Degree for node %d: %lf\n",id, degree);
	}
	return idImp;
}

/*-----------------------------------------------------------------------*/

/*---Algoritmo de PageRank Centrality---*/

/*
	Este algoritmo calculara el PageRank Centrality para cada nodo, siguiendo la teoria de este Algoritmo,
	explicada en el paper adjunto. 
	
	Se inicializan todos los pagerank de los nodos como 1/N siendo N la cantidad de nodos del grafo. Ademas,
	se almacenaran los valores de pagerank calculados previamente en un arreglo llamado PageRankAnt en alusion al pagerank
	antiguo ya calculado. Este arreglo servira para posterior calculo de los nuevos pagerank en el arreglo
	pagerankNew.
	
	En este caso, hemos tomado las siguientes consideraciones:
	
	* Numero de iteraciones: 30
	* Valor del coeficiente de amortiguamiento (d): 0.85
	
	Ademas, se ha simulado el comportamiento de una cola en un arreglo llamado queue, con la tecnica de
	"Two Pointers".
	
	Variables Importantes:
	
		-> int vis[MAX_NODES]: Arreglo que indicara si el nodo que queremos analizar ya se encuentra visitado
		
		-> int queue[MAX_NODES]: Arreglo que servira para la simulacion de la cola con Two Pointers. Almacenara
										 los ids de los nodos en cuestion.
		
		-> int front: Frente de la cola
		
		-> int rear: Parte trasera de la cola
		
		-> double pr: Almacenara el pagerank de cada nodo siguiendo la formula explicada en el paper.
*/


int vis[MAX_NODES];
int queue[MAX_NODES]; //Este arreglo servira tanto para el PageRank como para el calculo del numero de erdos

int getPageRank(TGrafo* G){
	for(int id = 1; id < G->numNodos+1; id++) G->pagerankAnt[id] = 1.0/(G->numNodos);
	for(int iter = 0; iter < 30; iter ++){
		int front = 0, rear = 0;
		fprintf(logfile, "Iteracion: %d\n",iter);
		for(int i = 1; i < G->numNodos+1; i++) vis[i] = 0;
		int src = rand()%(G->numNodos) + 1; queue[rear++] = src;
		fprintf(logfile, "Source: %d\n", src);
		vis[src] = 1;
		while(front != rear){
			int u = queue[front++];
			Nodo* cur = G->adj[u]->ini;
			double pr = 0;
			while(cur){
				int v = cur->info.snd, w = cur->info.fst;
				pr += ( G->pagerankAnt[v]*(w*1.0/ G->degree[v])); 
				if(!vis[v]){
					vis[v] = 1;
					queue[rear++] = v;
				}	
				cur = cur->sig;
			}
			pr = 0.85*pr + 0.15;
			G->pagerankNew[u] = pr;
		}
		for(int i = 1; i < G->numNodos+1; i++) G->pagerankAnt[i] = G->pagerankNew[i];
	}
	double maxPr = -1;
	int idImp;
	for(int id = 1; id < G->numNodos+1; id++){
		if(G->pagerankNew[id] > maxPr){
			idImp = id; maxPr = G->pagerankNew[id];
		}
	}
	return idImp;
}

/*-----------------------------------------------------------------------*/

/*---Calculo del Numero de Erdos---*/

/*
	Luego de haber encontrado al erdos de nuestra red de coautoria, es importante saber
	el erdos de cada uno de los demas autores. Es asi, que procedemos a calcular estos 
	valores con una busqueda en anchura. Por que? Pues para el calculo de este valor no
	se consideran los pesos en las aristas, y el BFS calcula la distancia minima desde un
	nodo a todos los demas cuando el grafo presenta ponderacion 1.
	
	Al igual que en el PageRank Centrality, se ha simulado el comportamiento de una cola en 
	un arreglo llamado queue, con la tecnica de "Two Pointers".
	
	Variables Importantes:
	
		-> int erdosNumber[MAX_NODES]: Almacenara el numero de erdos para cada autor.
		
*/

int erdosNumber[MAX_NODES];

void bfs(TGrafo* G, int erdos){
	for(int i = 1; i< G->numNodos + 1; i++) erdosNumber[i] = oo; //Se inicializa en infinito
	int front = 0, rear = 0;
	erdosNumber[erdos] = 0;
	queue[rear ++] = erdos;
	while(front != rear){
		int head = queue[front ++];
		Nodo* cur = G->adj[head]->ini;
		while(cur){
			int id = cur->info.snd;
			if(erdosNumber[id] == oo){ //Si aun no ha sido visitado, entrar
				erdosNumber[id] = erdosNumber[head] + 1;
				queue[rear ++] = id;
			}
			cur = cur->sig;
		}
	}
}

/*-----------------------------------------------------------------------*/

/*--Impresion del reporte---*/

/*
	Se imprimiran los resultados en el archivo correspondiente a cada algoritmo,
	con un formato muy amigable.
*/

void report(TGrafo* G, int erdos, int type){
	printf("Erdos calculated by ");
	if(type == 0) printf("Degree");
	else if(type == 1) printf("Closeness");
	else printf("PageRank");
	printf(" Centrality: ");
	puts(G->name[erdos]);
	if(type == 0) printf("Degree ");
	else if(type == 1) printf("Closeness ");
	else printf("PageRank ");
	printf("obtenido: ");
	if(type == 0) printf("%lf\n", G->degree[erdos]);
	else if(type == 1) printf("%lf\n", G->closeness[erdos]);
	else printf("%lf\n", G->pagerankNew[erdos]);
	for(int i = 0; i < 30; i++) printf("-");
	printf("\n");

	bfs(G, erdos);

	printf("Please check the Erdos number of each author below: \n\n");
	for(int i = 1; i <= G->numNodos; i++){
		printf("Author %d: ",i); 
		puts(G->name[i]);
		printf("Erdos number: ");
		if(erdosNumber[i] == oo) printf("This author is disconnected from Erdos!\n");
		else printf("%d\n", erdosNumber[i]);
		if(type == 0){
			printf("Degree: %lf\n", G->degree[i]);
		}
		else if(type == 1){
			printf("Closeness: %lf\n", G->closeness[i]);
		}
		else printf("PageRank: %lf\n", G->pagerankNew[i]);
		printf("\n");
	}

}

/*-----------------------------------------------------------------------*/

/*---Asignacion de archivos y posterior impresion de reportes---*/

/*
	Se usaran 4 archivos para imprimir los reportes:
		-> degreeOutput.txt: Imprimira los resultados del degree centrality
		-> closenessOutput.txt: Imprimira los resultados del closeness centrality
		-> pagerankOutput.txt: Imprimira los resultados del pagerank centrality
		-> log.txt: Imprimira paso a paso la ejecucion del programa
*/

void printResults(TGrafo *G){
	
	FILE * archivo;

	/*Reporting Degree Centrality*/

	int degreeErdos = getDegree(G);
	archivo = freopen("degreeOutput.txt", "w", stdout);
	report(G, degreeErdos, 0);
	fclose(archivo);
	
	fprintf(logfile, "Degree Centrality Algorithm terminado!\n");

	/*Reporting Closeness Centrality*/

	int closenessErdos = getCloseness(G);
	archivo = freopen("closenessOutput.txt", "w", stdout);
	report(G,closenessErdos,1);
	fclose(archivo);

	fprintf(logfile, "Closeness Centrality Algorithm terminado!\n");

	/*Reporting PageRank Centrality*/

	int pagerankErdos = getPageRank(G);
	archivo = freopen("pagerankOutput.txt", "w", stdout);
	report(G, pagerankErdos, 2);
	fclose(archivo);
	
	fprintf(logfile, "PageRank Centrality Algorithm terminado!\n");
}

TGrafo G; //Grafo usado en todo el programa

/*---Main function---*/

int main(){
	srand(time(NULL));
	clock_t tStart = clock(); //Util para medir el tiempo
	int n,m; scanf("%d %d\n",&n,&m); //Lectura de numero de nodos y numero de aristas
	grafo_crear(&G); //Creacion del grafo
	G.numNodos = n; //Asignacion de numero de nodos
	for(int i = 1 ; i <= n ;i ++){
		gets(G.name[i]);	//Lectura de nombres
	}
	
	//Insercion de aristas
	for(int i = 0 ; i< m; i++){
		int u,v,w; scanf("%d %d %d\n",&u,&v,&w);
		grafo_insertarArista(&G,u,v,w); grafo_insertarArista(&G,v,u,w);	
	}

	logfile = freopen("log.txt", "w", stderr); //Abrimos el archivo de reporte
	
	fprintf(logfile, "Grafo Cargado en %lfs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC); //Imprimimos el tiempo que demoro en cargar el grafo

	printResults(&G); //Se lanza la funcion que calculara todo
	fprintf(logfile, "\nTime taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC); //Imprimimos el tiempo total
	fclose(logfile);
	return 0;
}
