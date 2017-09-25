/*
	Priority queue for pair structures, implemented with Heap
	Allows insertion (ordered), deletion (top)
	Fix the initial_size as convenient

	Extracted from: https://gist.github.com/aatishnn/8265656

	Modified by: Arian Gallardo
*/

typedef pair T;

typedef struct TPQ {
	int size; //Tamanho del heap
	int count; //Cantidad de elementos presentes actualmente en el heap
	T *heaparr; //Arreglo que guarda los valores del heap
}priority_queue;

int initial_size = 64;


//Inicializar (alojar memoria)
void pq_init(priority_queue *h){
	h->count = 0;
	h->size = initial_size;
	h->heaparr = (T *) malloc(sizeof(T) * initial_size);
}

//Balanceo del heap
void min_heapify(T *data, int loc, int count){
	int left, right, smallest;
	T temp;
	left = 2*(loc) + 1;
	right = left + 1;
	smallest = loc;

	if (left <= count && isLess(data[left],data[smallest])) {
		smallest = left;
	} 
	if (right <= count && isLess(data[right], data[smallest])) {
		smallest = right;
	} 
	
	if(smallest != loc) {
		temp = data[loc];
		data[loc] = data[smallest];
		data[smallest] = temp;
		min_heapify(data, smallest, count);
	}
}

//Insercion de elementos en el heap
void pq_push(priority_queue *h, T value){
	int index, parent;
	
	if (h->count == h->size){
		h->size *=2;
		h->heaparr = realloc(h->heaparr, sizeof(T) * h->size);
		if (!h->heaparr) exit(-1);
	}
 	
 	index = h->count++;

	for(;index; index = parent){
		parent = (index - 1) / 2;
		if (isLessorEqual((h->heaparr[parent]), value)) break;
		h->heaparr[index] = h->heaparr[parent];
	}
	h->heaparr[index] = value;
}

//Funcion que remueve y retorna el tope de la cola
T pq_top(priority_queue *h){
	T removed;
	T temp = h->heaparr[--h->count];
 		
	if ((h->count < (h->size/2)) && (h->size > initial_size))
	{
		h->size /= 2;
		h->heaparr = realloc(h->heaparr, sizeof(T) * h->size);
		if (!h->heaparr) exit(-1);
	}
 	removed = h->heaparr[0];
 	h->heaparr[0] = temp;
 	min_heapify(h->heaparr, 0, h->count);
 	return removed;
}


//Finalizar la cola
void pq_finalize(priority_queue *pq) {
	while(pq->count != 0) {
		pq_top(pq);
	}
}
