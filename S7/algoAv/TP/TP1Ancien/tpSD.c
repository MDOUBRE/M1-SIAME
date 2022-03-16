#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fixHeap(int* heap, const int size,int node);
void buildHeap(int* heap, const int size);
void heapsort(int* heap,int size);
void swap(int* a,int* b);
void createRandomHeap(int* heap, int* currentHeapSize, const int maxHeapSize);
void addToHeap(int* heap, int* currentHeapSize, const int maxHeapSize, int elemToAdd);
int removemax( int* tas, int* heapSize );
void printTas(const int* tas, const int* size);
int* read_data( FILE *datain, int *n, int *k );

void percolateDown(int* heap, int indice, const int size);
int left(int i);
int right(int i);


void quicksort(int* tab,int left,int right);
void mergesort(int* tab,int limInf,int limSup);

void triabulle(int* data, int n, int k);

//=======================
void startMeasuringTime();
void stopMeasuringTime();
void showElapsedTime();
clock_t ti,tf;
double duree_ms, duree_s;
//=======================

int main( int argc, char **argv ) {
	int *data;
	int n, k;
	FILE *f_in;

	if ( argc > 1 )
		f_in = fopen(argv[1], "r");
	else
		f_in = stdin;
	
	/* read the dataset */
	data = read_data( f_in, &n, &k );

	/* output the dataset red */
	//printTas(data, &n);
	
	/* utiliser une fonction qui modifie data*/
	/*exo1 */
	//triabulle(data,n,k);

	/*exo2 */
	/*quicksort(data,0,n-1);*/

	/*exo3*/
	buildHeap(data,n);
	printTas(data, &n);
	
	/* output result. */
        /* à écrire */

	/* affichage */
	/*int m;
	for( int i=1; i<=k; i++)
	{
	    m=removemax(data,n-i+1);

	    if (m!=-1)
		{
			printf("%d ",m );
		}
		else
		{
			//printf("plus d'elements");
		};
	}
	printf("\n");*/
	
	/* exos 1 et 2*/
	/*	
	for( int i=1; i<=k; i++)  
	    printf( "%d ", data[n-i] );  
	printf("\n"); 

	free(data);
	return 0;
	*/
}

/**
 * Read heap data from text file
 */
int* read_data( FILE *datain, int *n, int *k )
{
	int *data=0;
	int elem;
	fscanf(datain, "%d", n);
	fscanf(datain, "%d", k);
	data = (int *)malloc( (*n) * sizeof(int) );
	for ( int i=0; i< *n; ++i)
	{
		fscanf( datain, "%d", &elem );
		data[i] = elem;
	}
	return data;
}

void startMeasuringTime()
{
	ti = clock();
}

void stopMeasuringTime()
{
	tf = clock() - ti;
	duree_ms = tf/(double)CLOCKS_PER_SEC*1000 ;
	duree_s = tf/(double)CLOCKS_PER_SEC ;
}

void showElapsedTime()
{
	printf("duree (ms): ~%f\n",duree_ms);
	printf("duree (s): ~%f\n",duree_s);
}

/*
	affichage d'un tas binaire
*/
void printTas(const int* tas, const int* size)
{
	int i=0;

	printf("[taille du tas: %d]-> ",(*size));
	for(i=0;i<*size;i++)
		printf("%d,",tas[i]);
	printf("\n");
}

/*
    echange deux valeurs
*/
void swap(int* a,int* b)
{
	*a = *a ^ *b;
	*b = *b ^ *a;
	*a = *a ^ *b;
}

int removemax( int* heap, int* heapSize )
{
    //printf("[appel a removemax]\n");
	return -1;
}

/*
	ajoute un element à un tas. Puis, la fonction heapify est appele pour garantir que le tableau est un tas
*/
void addToHeap(int* heap, int* currentHeapSize, const int maxHeapSize, int elemToAdd)
{
    printf("[appel a addToHeap]\n");
}

void createRandomHeap(int* heap, int* currentHeapSize, const int maxHeapSize)
{
    printf("[appel a createRandomHeap]\n");
}

/*
	tri du tas
*/
void heapsort(int* heap, int size)
{
    printf("[appel a heapSort]\n");
}

/*
 modifie le tableau a tel qu'il respecte le proprietes du tas binaire MAX (pere > fils)
 */
void buildHeap(int* heap, const int size)
{
	int i;    
	for(i=(size/2);i>0;i--){
		percolateDown(heap, i, size);
	}
	
}

void percolateDown(int* heap, int indice, const int size){
	int l=left(indice);
	int r=right(indice);
	int m, tmp;
	if(l<size && (heap[indice-1]<heap[l-1])){
		m=l;
	}
	else{
		m=indice;
	}
	if(r<size && (heap[m-1]<heap[r-1])){
		m=r;
	}
	if(m!=indice){
		swap(heap+indice-1, heap+m-1);	
		percolateDown(heap, indice, size);
	}
}

int left(int indice){
	return 2*indice;
}

int right(int indice){
	return (2*indice)+1;
}

/*
	- node = index courant
	- size = taille du tas
*/
void fixHeap(int* heap, const int size, int node)
{
    printf("[appel a fixHeap]\n");
}


//==========================================

/* écrire une fonction qui traite un tableau*/
/* exo 1*/
void triabulle(int *data, int n, int k)
{
	int i, j;
	int tmp;
	for(i=n-1;i>=1;i--){
		for(j=0;j<i;j++){
			if(data[j+1]<data[j]){
				tmp=data[j+1];
				data[j+1]=data[j];
				data[j]=tmp;
			}
		}
	}
}

//==========================================

void quicksort(int* tab,int left,int right)
{
	printf("[appel a quicksort]\n");
}

void mergesort(int* tab,int limInf,int limSup)
{
	printf("[appel a mergesort]\n");
}

