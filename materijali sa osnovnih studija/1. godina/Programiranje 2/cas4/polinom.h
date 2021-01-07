#ifndef _POLINOM_H_
#define _POLINOM_H_

void greska();

/* 
 * Funkcija pravi novi polinom 
 * U n treba da se smesti stepen ispis_polinoma
 * Kao povratnu vrednost vraca pokazivac na pocetak niza koji cuva koeficijente polinoma
 */
int* unos_polinoma(int* n);

/*
 * Funkcija koja ispisuje polinom u formatu:
 * c0 + c1*x + c2*x^2 - c3*x^3 ...
 */
void ispis_polinoma(int* a, int n);

/*
 * Funkcija koja racuna sumu polinoma a i b
 * Rezultujuci polinom je c 
 * (pre smestanja rezultata u c, treba alocirati potreban prostor)
 * 
 * Kao povratnu vrednost vraca stepen rezultujuceg polinoma.
 */
int suma_polinoma(int* a, int n, int* b, int m, int** c);

/*
 * Polinom a se mnozi skalarom c
 */
void mnoz_skalarom(int* a, int n, int c);

/*
 * Racunanje vrednosti polinoma a u tacki x koriscenjem Hornerove seme
 */
int vr_poly(int* a, int n, int x);

/*
 * Funkcija koja mnozi polinome a i b i rezultujuci polinom smesta u c.
 */
int mul_poly(int* a, int n, int* b, int m, int** c);

#endif