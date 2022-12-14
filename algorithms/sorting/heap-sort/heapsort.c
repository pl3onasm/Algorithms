/* file: heapsort.c
* author: David De Potter
* description: heap sort
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Heap {int size; int *array;} Heap;

void *safeMalloc (int n) {
  /* allocates n bytes of memory and checks whether the allocation
     was successful */
  void *ptr = malloc(n);
  if (ptr == NULL) {
    printf("Error: malloc(%d) failed. Out of memory?\n", n);
    exit(EXIT_FAILURE);
  }
  return ptr;
}

Heap *newHeap(int size) {
  /* creates a new heap of size size */
  Heap *hp = safeMalloc(sizeof(Heap)); 
  hp->size = size;
  hp->array = safeMalloc(size*sizeof(int));
  return hp;
}

void freeHeap(Heap *hp) {
  /* frees the heap hp */
  free(hp->array);
  free(hp);
}

void showHeap(Heap *hp){
  /* prints the heap */
  printf("[");
  for (int i = 0; i < hp->size; i++) {
    printf("%d", hp->array[i]);
    if (i < hp->size-1) printf(", ");
  }
  printf("]\n");
}

void swap (Heap *hp, int a, int b) {
  /* swaps the elements at indices a and b in the heap */
  int temp = hp->array[a]; 
  hp->array[a] = hp->array[b]; 
  hp->array[b] = temp;
}

void maxHeapify(Heap *hp, int i){
  /* restores the max heap property for the heap */
  int max = i, left = i<<1, right = (i<<1) + 1;
  if (left < hp->size && hp->array[left] > hp->array[max])
    max = left;
  if (right < hp->size && hp->array[right] > hp->array[max])
    max = right;
  if (max != i) {
    swap(hp, i, max); 
    maxHeapify(hp, max);
  }
}

void initMaxHeap(Heap *hp){
  /* initializes the max heap */
  for (int i = (hp->size>>1)-1; i >= 0; --i) maxHeapify(hp, i);
}

void heapsort(Heap *hp){
  /* sorts the heap */
  int size = hp->size;
  initMaxHeap(hp);
  for (int i = hp->size - 1; i > 0; --i) {
    swap(hp, 0, i);
    hp->size--;
    maxHeapify(hp, 0);
  }
  hp->size = size;
}

Heap *readHeap (int arr[], int size) {
  /* reads a heap from an array */
  Heap *hp = newHeap(size);
  for (int i = 0; i < size; i++) hp->array[i] = arr[i];
  return hp;
}

int main (int argc, char *argv[]){
  int intExample[] = {5, 6, 7, 8, 9, 10, 2, -1, 3, 4, 1, 2, 
                     -35, 78, -10, 13, 7, -11, 20, 1, 15, 7, 
                     16, 0, 1, 2, 5, 6, 100, 23};
  Heap *hp = readHeap(intExample, 30);
  printf("Unsorted:\n");
  showHeap (hp);
  heapsort(hp);
  printf("Sorted:\n");
  showHeap(hp);
  freeHeap(hp);
  return 0;
}