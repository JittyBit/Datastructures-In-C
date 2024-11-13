#include <stdio.h>
#define noop (void)0

void my_swap(int* a, int* b) {
  int c = *a;
  *a = *b;
  *b = c;
}

int partition(int* arr, int len) {
  int p = len-1;
  int i = 0;
  int j = p-1;
  while (1) {
    for (; arr[i] <= arr[p] && i < p; ++i);
    for (; arr[j] >= arr[p] && j > 0; --j);
    if (i >= j) {
      break;
    }
    my_swap(arr+i, arr+j);
  }
  my_swap(arr+i, arr+p);
  return i;
}

void quicksort(int* arr, int len) {
  if (len < 2) return;
  int pivot = partition(arr, len); // arr became null???
  quicksort(arr,pivot);
  quicksort(arr+pivot+1,len-pivot-1);
}

int main() {
  int arr[] = {2, 6, 4, 3, 5, 7, 0};
  int arrlen = sizeof(arr)/sizeof(int);
  printf("Unsorted List: ");
  for (int i = 0; i < arrlen; ++i) {
    printf("%d ", arr[i]);
  }
  quicksort(arr, arrlen);
  printf("\nSorted List: ");
  for (int i = 0; i < arrlen; ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}
