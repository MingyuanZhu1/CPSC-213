#include <stdio.h>


int q2(int a, int b, int c) {
    switch (a) {
        case 10:
        return (b + c); 
        break;
        
        case 12: 
        return (b - c); 
        break;
        
        case 14: 
        return (b > c);
        break;
        
        case 16:
        return (b < c);
        break;
        
        case 18:
        return (b == c);
        break;

        default:
        return 0;
    }
}
