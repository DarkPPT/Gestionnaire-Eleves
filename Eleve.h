#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _Eleve_H_
#define _Eleve_H_


typedef struct Eleve Eleve;

struct Eleve
{
    int id;
    char *name;
    char *pname;
    char *promo;
    double *notes;
    int sizenote;

    double moyenne;
};


Eleve* createEleve(char* nom, char*  pnom, char *promo, int id);
void deleteEleve(Eleve** p);

void addnote(Eleve *eleve, double note);

int compareElevesByLastName(void *a, void *b);
int compareElevesByFirstName(void *a, void *b);
int compareElevesByPromo(void *a, void *b);
int compareElevesByMoyenne(void *a, void *b);


void displayEleve(Eleve *eleve);

void calculMoyenneEleve(Eleve *eleve);

#endif
