#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
   //base case
   if(n == 0) {
      return 1;
   } else {
      return n * factorial(n-1);
   }
}

int fibbonacci(int n) {
   if(n == 0){
      return 0;
   } else if(n == 1) {
      return 1;
   } else {
      return (fibbonacci(n-1) + fibbonacci(n-2));
   }
}

int main() {
   int n = 30;
   int i;

   int *a = malloc(sizeof(int));
   *a = factorial(10);
	
   printf("a(%x): %d\n", a, *a);
   printf("Factorial of %d: %d\n" , n , factorial(n));
   printf("Fibbonacci of %d: " , n);
	
   for(i = 0;i<n;i++) {
      printf("%d ",fibbonacci(i));            
   }
}
