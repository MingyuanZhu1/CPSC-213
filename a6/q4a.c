#include <stdio.h>

int arr[10] = {0,0,0,0,0,0,0,0,0,0};
int* c = arr;

void puu (int a, int b) {
   c[b] = a + c[b];
}

void fn1() {
    int a_local = 1;
    int b_local = 2;
    puu(3,4);
    puu(a_local,b_local);
}

void main() {
    fn1();
    for (int i = 0; i < 10; i++)
    {
       printf("%d\n", arr[i]);
    }
    
}