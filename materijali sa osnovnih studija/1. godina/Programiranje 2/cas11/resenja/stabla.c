#include "stabla.h"

void greska()
{
    fprintf(stderr, "-1\n");
    exit(EXIT_FAILURE);
}

Cvor* napravi_cvor(int broj)
{
    Cvor* novi = malloc(sizeof(Cvor));
    if(novi == NULL)
            greska();
            
    novi->vrednost = broj;
    novi->levo = NULL;
    novi->desno = NULL;
    
    return novi;
}

void dodaj_u_stablo(Cvor** koren, int broj)
{
    if(*koren == NULL)
    {
            *koren = napravi_cvor(broj);
            return;
    }
    
    if(broj < (*koren)->vrednost)
            dodaj_u_stablo(&(*koren)->levo, broj);
    else
            dodaj_u_stablo(&(*koren)->desno, broj);
}

void ucitaj_stablo(Cvor** koren, FILE* ulaz)
{
    int broj;	
    while(fscanf(ulaz, "%d", &broj) != EOF)
            dodaj_u_stablo(koren, broj);
            
}

void ispisi_stablo_infiksno(Cvor* koren)
{
    if(koren != NULL)
    {
        ispisi_stablo_infiksno(koren->levo);
        printf("%d ", koren->vrednost);
        ispisi_stablo_infiksno(koren->desno);
    }
}

void ispisi_stablo_prefiksno(Cvor* koren)
{
    if(koren != NULL)
    {
        printf("%d ", koren->vrednost);
        ispisi_stablo_prefiksno(koren->levo);
        ispisi_stablo_prefiksno(koren->desno);
    }
}

void ispisi_stablo_postfiksno(Cvor* koren)
{
    if(koren != NULL)
    {
        ispisi_stablo_postfiksno(koren->levo);
        ispisi_stablo_postfiksno(koren->desno);
        printf("%d ", koren->vrednost);
    }
}

void ispisi_stablo(Cvor* koren, FILE* f)
{
    if(koren != NULL)
    {
            ispisi_stablo(koren->levo, f);
            printf("%d ", koren->vrednost);
            ispisi_stablo(koren->desno, f);
    }
}

void oslobodi_stablo(Cvor* koren){
    if(koren)
    {
            oslobodi_stablo(koren->levo);
            oslobodi_stablo(koren->desno);
            free(koren);
    }
}
