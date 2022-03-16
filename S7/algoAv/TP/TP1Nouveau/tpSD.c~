#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//*************** Structure des tas binaire ******************

typedef struct Heap {
    int *array;
    int length; // max size
    int size;
} Heap;


//*************** Fonctions données ******************

//**** Fonctions pour le temps d'execution ****
clock_t ti,tf;
double duree_ms;

void startMeasuringTime()
{
    ti = clock();
}

void stopMeasuringTime()
{
    tf = clock() - ti;
    duree_ms = tf/(double)CLOCKS_PER_SEC*1000 ;
}

void showElapsedTime()
{
    printf("duree (ms): ~%f\n",duree_ms);
}




//**** Fonction lecture des donnees ****
void read_data( FILE *datain, int **dataout, int *n, int *k ) {
	int *data;

	fscanf(datain, "%d", n);
	fscanf(datain, "%d", k);
	*dataout = (int *)malloc( (*n) * sizeof(int) );
	data=*dataout;

	for ( int i=0; i< *n; ++i, ++data )
		fscanf( datain, "%d", data );
}


//**** Affichage des donnees ****
void print_array(int * array, int length) {
    for (int i=0; i<20; ++i) //length à la place de 20
        printf("%d ", array[i]);
    printf("\n");
}

//**** Permutation ****
void permut(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//**** Permutation entre deux indices d'un tas binaire ****
void permut_heap(Heap heap, int ind1, int ind2) {
    permut(&heap.array[ind1], &heap.array[ind2]);
}








//*************** Exercice 1 ******************



void bubble_sort(int * array, int n, int k) {
	int i, j;
	int tmp;
	for(i=0;i<k;i++){
		for(j=0;j<n-i-1;j++){
			if(array[j+1]<array[j]){
				tmp=array[j+1];
				array[j+1]=array[j];
				array[j]=tmp;
			}
		}
	}
}




//*************** Exercice 2 ******************


int left(int i) {
    return 2*i+1;
}

int right(int i) { 
    return (2*i)+2;
}

void percolate_down(Heap heap, int i){
    int l=left(i);
    int r=right(i);
    int m;
    int tmp;
    if(l<=heap.length && heap.array[i]<heap.array[l]){
    	m=l;
    }
    else{
    	m=i;
    }
    if(r<=heap.length && heap.array[m]<heap.array[r]){
    	m=r;
    }
    if(m!=i){
    	//permut_heap(heap,heap.array[i],heap.array[m]);
    	tmp=heap.array[i];
    	heap.array[i]=heap.array[m];
    	heap.array[m]=tmp;
    	percolate_down(heap,m);
    }
}

void build_heap(Heap heap) {
	heap.size=heap.length;
    for(int i=heap.size/2;i>=0;i--){
    	percolate_down(heap,i);
    }
}





int parent(int i) {
    return (i-1)/2;   
}

void percolate_up(Heap * heap, int i) {
    printf("on est dans percolate up\n");
    int j=parent(i);
    int tmp;
    while(j>0 && ((*heap).array[j]<(*heap).array[i])){
    	print_array((*heap).array,(*heap).size);
    	printf("hop %d\n",j);
    	tmp=(*heap).array[j];
    	(*heap).array[j]=(*heap).array[i];
    	(*heap).array[i]=tmp;
    	i=j;
    	j=parent(i);
    }
}

void add(Heap * heap, int element) {
	printf("on est dans add\n");
	printf("%d\n",element);
	print_array((*heap).array,(*heap).size);
	//(*heap).size=(*heap).size+1;
	(*heap).array[(*heap).size]=element;
	percolate_up(heap,(*heap).size);
}





int remove_max(Heap * heap) {
    // TO DO
    printf("To Do remove_max \n");
    return 0;
}





//*************** Exercice 3 ******************

int remove_bis(Heap * heap) {
    // TO DO
    return 0;
}

void heap_sort(int * array) {
    // TO DO
    printf("To Do heap_sort \n");
}

void quick_sort(int * array, int firstIndex, int lastIndex) {
    // TO DO
    printf("To Do quick_sort \n");
}

void merge(int * array, int p, int q, int r) {
	// avant: array est tel que array[p..q] et array[q+1..r] sont tries
    // apres: array[p..q] trie'
    // TO DO
    printf("To Do merge \n");
}

void merge_sort(int * array, int firstIndex, int lastIndex) {
    // recursif relance merge_sort sur les deux moities de tableau
    // puis merge les deux resultats
    // TO DO
    printf("To Do merge_sort \n");
}





/* Main Program*/

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// En fonction de l'exercice, adaptez le main
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int main( int argc, char **argv ) {
	int *data;
	int n, k;
	FILE *f_in;

	if ( argc > 1 )
		f_in = fopen(argv[1], "r");
	else
		f_in = stdin;

	/* read the data from the file given in arg or from stdin */
	read_data( f_in, &data, &n, &k );
    fclose(f_in);

    startMeasuringTime();

    Heap heap = {data, n, n};

    printf("Données initiales:\n");
    print_array(data, n);
    
    // ***** Exercice 1 *****
    //bubble_sort(data, n, k);
    //print_array(data, n);
    
    // ***** Exercice 2 *****
    build_heap(heap);
    print_array(data,n);

    /*
    int array[n];
    Heap heap2={array,0,n}; int element;
    print_array(array,0);
    for(int i=0;i<n;i++){
    	element=data[i];
    	printf("%d\n",element);
    	add(&heap2, element);
    }
    print_array(array,n);
	*/
	
    int max;
    max = remove_max(&heap);
    
    // ***** Exercice 3 *****

    heap_sort(data);

    int firstIndex, lastIndex;

    quick_sort(data, firstIndex, lastIndex);
    
    merge_sort(heap.array, firstIndex, lastIndex);

    

    // ******** Affichage du temps d'execution ********

    stopMeasuringTime();

    showElapsedTime();

	/* end of the program*/
    free(data);
	return 0;
}

