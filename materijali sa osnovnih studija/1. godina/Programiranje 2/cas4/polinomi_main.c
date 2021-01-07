#include <stdio.h>
#include <stdlib.h>

#include "polinom.h"

int main()
{
    int*a, *b, *c, *d;
    int m, n, k, x, s, k2;

    a = unos_polinoma(&n);
    ispis_polinoma(a, n);

    b = unos_polinoma(&m);
    ispis_polinoma(b, n);

    k = suma_polinoma(a, n, b, m, &c);
    ispis_polinoma(c, k);

    printf("Unesi skalar:\n");
    scanf("%d", &s);
    mnoz_skalarom(a, n, s);
    ispis_polinoma(a,n);

    printf("Unesi x: ");
    scanf("%d", &x);
    printf("Vrednost polinoma je %d\n", vr_poly(a, n, x));

    k2 = mul_poly(a, n, b, m, &d);
    ispis_polinoma(d, k2);
  
    free(a);
    free(b);
    free(c);
    free(d);
  
    return 0;
}