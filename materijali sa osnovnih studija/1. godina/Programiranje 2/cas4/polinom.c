#include <stdio.h>
#include <stdlib.h>
#include "polinom.h"

void greska()
{
	fprintf(stderr, "-1\n");
	exit(EXIT_FAILURE);
}

int* unos_polinoma(int *n)
{
    //Ucitavanje stepena
    scanf("%d", n);
    
    //Alokacija polinoma
    int* p = calloc(*n+1, sizeof(int));
    if(p == NULL)
        greska();

    //Ucitavanje koeficijenata
    int i;
    printf("Ucitaj polinom:\n");
    for(i=0; i<=*n; i++)
        scanf("%d", &p[i]);
    
    return p;
}

void ispis_polinoma(int *p, int n)
{
    if(p[0])
        printf("%d ", p[0]);
    
    if(n > 0 && p[1])
        printf("%c %d*x ", p[1]>0 ? '+' : '-', p[1]);
    
    int i;
    for(i=2; i<=n; i++)
    {
        if(p[i])
            printf("%c %d*x^%d ", p[i]>0 ? '+' : '-', p[i], i);
    }
    printf("\n");
}

int suma_polinoma(int* a, int n, int* b, int m, int** r)
{
  
    int* c = NULL;
    
    if(n > m)
        c = calloc(n+1, sizeof(int));
    else
        c = calloc(m+1, sizeof(int));

    int i = 0;
    while(i<=n && i<=m)
    {
        c[i] = a[i] + b[i];
        i++;
    }

    while(i<=n)
    {
        c[i] = a[i];
        i++;
    }

    while(i<=m)
    {
        c[i]=b[i];
        i++;
    } 
    
    *r = c;
    if (n > m) 
        return n;
    else 
        return m;
}

void mnoz_skalarom(int* a, int n, int c)
{
    int i;
    for(i=0; i<=n; i++)
        a[i] = c*a[i];
}

int vr_poly(int* a, int n, int x)
{
    int s=0, i;

    for(i=n; i>=0; i--)
        s = s*x + a[i];

    return s;
}

int mul_poly(int* a, int n, int* b, int m, int** c)
{
    int* rez = calloc(m+n+1, sizeof(int));
    if(rez == NULL)
        greska();
    
    int i,j;

    for(i=0; i<=n; i++)
        for(j=0; j<=m; j++)
            rez[i+j] += a[i]*b[j];
    
    *c = rez;
    return m+n;
}









