/* Napisati program koji koristi vise niti da pomnozi 2 matrice 
 * dimenzija NxM i MxK. Sa standardnog ulaza se ucitavaju N i M, pa 
 * zatim NxM celih brojeva. Nakon toga ucitavaju se M i K, pa zatim 
 * MxK celih brojeva. Potrebno je pokrenuti NxK niti tako da svaka nit 
 * racuna jedan element rezultujuce matrice. Tokom izracunavanja, 
 * potrebno je cuvati maksimalni element rezultujuce matrice (za 
 * sinhronizaciju koristiti muteks, nije dozvoljena staticka alokacija). 
 * Iz main()-a ispisati rezultujucu matricu, razdvojiti elemente belinom, 
 * i kao poslednji broj ispisati i maksimalni element. 
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#include <pthread.h>

#define check_error(expr, userMsg)\
	do { \
		if (!(expr)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE); \
		}\
	} while (0)

#define check_errorP(threadErr, userMsg)\
	do {\
		int _threadErr = threadErr; \
		if (_threadErr > 0) {\
			errno = _threadErr; \
			check_error(0, userMsg);\
		} \
	} while (0)
			
/* tip koji opisuje argument niti */
typedef struct {
	
	int row;
	int col;
	
} data_t;

/* matrice i dimenzije */
int n, m1, m2, k;
int** mat1, **mat2, **mat3;

/* max -> deljena promenljiva */
int max = 0;
/* flag koji govori da li je max inicijalizovan ili ne */
int initialized = 0;
/* muteks za sinhronizaciju */
pthread_mutex_t globalLock;

/* alokacija i ucitavanje matrica */
void create_matrix(void){
	
	scanf("%d%d", &n, &m1);
	
	mat1 = malloc(sizeof(int*)*n);
	check_error(mat1 != NULL, "..");
	for (int i = 0; i < n; i++) {
		mat1[i] = malloc(sizeof(int)*m1);
		check_error(mat1[i] != NULL, "...");
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m1; j++) {
			scanf("%d", &mat1[i][j]);
		}
	}
	
	scanf("%d%d", &m2, &k);
	
	check_error(m1 == m2, "...");
	
	mat2 = malloc(sizeof(int*)*m2);
	check_error(mat2 != NULL, "..");
	for (int i = 0; i < m2; i++) {
		mat2[i] = malloc(sizeof(int)*k);
		check_error(mat2[i] != NULL, "...");
	}
	
	for (int i = 0; i < m2; i++) {
		for (int j = 0; j < k; j++) {
			scanf("%d", &mat2[i][j]);
		}
	}
	
	mat3 = malloc(sizeof(int*)*n);
	check_error(mat3 != NULL, "..");
	for (int i = 0; i < n; i++) {
		mat3[i] = malloc(sizeof(int)*k);
		check_error(mat3[i] != NULL, "...");
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			mat3[i][j] = 0;
		}
	}
}

/* oslobadjanje matrica */
void free_matrix(void){
	
	for (int i = 0; i < n; i++) {
		free(mat1[i]);
		free(mat3[i]);
	}
	
	free(mat1);
	free(mat3);
	
	for (int i = 0; i < m1; i++) {
		free(mat2[i]);
	}
	free(mat2);
}

/* prikaz rezultata */
void print_matrix(void){
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			printf("%d ", mat3[i][j]);
		}
		printf("\n");
	}
	
	printf("%d\n", max);
}

/* funkcija koja implementira nit */
void* threadFunc(void* a){
	
	/* citamo argument */
	data_t* arg = (data_t*) a;
	
	/* racunamo elelemnt matrice */
	for (int i = 0; i < m1; i++) {
		mat3[arg->row][arg->col] += mat1[arg->row][i]*mat2[i][arg->col];
	}
	
	/* modifikujemo deljenu promenljivu */
	check_errorP(pthread_mutex_lock(&globalLock),"...");
	if (initialized) {
		if (mat3[arg->row][arg->col] > max) {
			max = mat3[arg->row][arg->col];
		}
	}
	else {
		max = mat3[arg->row][arg->col];
		initialized = 1;
	}
	check_errorP(pthread_mutex_unlock(&globalLock), "...");
}

int main(int argc, char** argv) {
	
	/* ucitavamo matrice */
	create_matrix();
	
	/* inicijalizujemo muteks */
	check_errorP(pthread_mutex_init(&globalLock, NULL), "...");
	
	/* alociramo prostor za tred id */
	pthread_t* tids = malloc(sizeof(pthread_t)*n*k);
	check_error(tids != NULL, "..");
	
	/* alociramo prostor za argumente niti */
	data_t* args = malloc(sizeof(data_t)*n*k);
	check_error(args != NULL, "...");
	
	/* startujemo niti */
	for (int i = 0; i < n; i++){
		for (int j = 0; j < k; j++) {
			args[i*k + j].row = i;
			args[i*k + j].col = j;
			check_errorP(pthread_create(&tids[i*k+j], NULL, threadFunc, &args[i*k+j]), "...");
		}
	}	
	
	/* cekamo da se zavrse */
	for (int i = 0; i < n; i++){
		for (int j = 0; j < k; j++) {
		
			check_errorP(pthread_join(tids[i*k+j], NULL), "...");
		}
	}
	
	/* prikazujemo rezultat */
	print_matrix();
	/* oslobadjamo resurse */
	check_errorP(pthread_mutex_destroy(&globalLock), "...");
	free_matrix();
	free(args);
	free(tids);
	
	exit(EXIT_SUCCESS);
}
