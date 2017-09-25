/*
	Pair structure
	Very useful in Dijkstra's algorithm implementation
	
	Author: Arian Gallardo
*/

#define EPS 1e-5

typedef struct TPair{
	double fst; //Peso
	int snd; //ID del nodo
}pair;

void init(pair p){
	p.fst = 0;
	p.snd = 0;
}

//Funciones de orden

// >
int isGreater(pair x, pair y){
	if(x.fst > y.fst) return 1;
	else if(abs(x.fst - y.fst) < EPS && x.snd > y.snd) return 1;
	else return 0;
}

// >=
int isGreaterorEqual(pair x, pair y){
	if(x.fst >= y.fst) return 1;
	else if(abs(x.fst - y.fst) < EPS && x.snd >= y.snd) return 1;
	else return 0;
}

// <
int isLess(pair x, pair y){
	if(x.fst < y.fst) return 1;
	else if(abs(x.fst - y.fst) < EPS && x.snd < y.snd) return 1;
	else return 0;
}

// <=
int isLessorEqual(pair x, pair y){
	if(x.fst <= y.fst) return 1;
	else if(abs(x.fst - y.fst) < EPS && x.snd <= y.snd) return 1;
	else return 0;
}

// ==
int isEqual(pair x, pair y){
	if(abs(x.fst - y.fst) < EPS && x.snd == y.snd) return 1;
	else return 0;
}
