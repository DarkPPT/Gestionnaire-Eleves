#include "Eleve.h"

#ifndef _Eleve_LIST_H_
#define _Eleve_LIST_H_

typedef struct Promotion Promotion;

struct Promotion
{
    int id;
    Eleve **eleves;
    char *name;
    int size;
    int curentid;

    double moyennepromo;
};


Promotion *createPromotion(char *name);
void deletePromotion(Promotion **p);

void deleteEleveFromPromotion(Promotion *list, int id);

void addEleve(Promotion *p1, Eleve *pe);

void displayPromotion(Promotion* p1);

int findElevefromId(Promotion *p1, int id);
Eleve *getElevefromId(Promotion *p1, int id);
void calculMoyennePromo(Promotion* mypromo);


void sortEleves(Promotion *mypromo,int (cmp )(void *a, void *b) );


#endif

