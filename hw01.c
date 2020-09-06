#include <stdio.h>

int translation ( int x );

int translation ( int x ) {

    int i = 1, res = 0;
    if ( x == 0 )
        return x;
    else {
        while ( x > 1 ) {
            res += i * ( x % 2 );
            i *= 10;
            x /= 2;
        }
        res += i;
    return res;
    }
}

int main () {
    int x, result;
    scanf ("%d", &x);
    result = translation (x);
    printf ("%d", result);
    return 0;
}

