#include "Eleve.h"


Eleve* createEleve(char* nom, char*  pnom, char *promo, int id)
{
    Eleve* eleve;
    eleve=NULL;




    eleve = (Eleve*)malloc(sizeof (Eleve));
    if(eleve==NULL)
    {
        printf("Probleme de memoire\n");
        exit(1);
    }


    eleve->name = malloc(sizeof (char)*strlen(nom));
    if(eleve->name==NULL)
    {
        printf("Probleme de memoire\n");
        exit(1);
    }


    eleve->pname = malloc(sizeof (char)*strlen(pnom));
    if(eleve->pname==NULL)
    {
        printf("Probleme de memoire\n");
        exit(1);
    }

    eleve->promo = malloc(sizeof (char)*strlen(promo));
    if(eleve->promo==NULL)
    {
        printf("Probleme de memoire\n");
        exit(1);
    }

    strcpy(eleve->name, nom);
    strcpy(eleve->pname, pnom);
    strcpy(eleve->promo, promo);

    eleve->id=id;
    eleve->notes=NULL;
    eleve->sizenote=0;
    eleve->moyenne=0;

    return eleve;
}

void deleteEleve(Eleve **p)
{
    free((*p)->name);
    free((*p)->pname);
    free((*p)->promo);
    free((*p)->notes);

    free(*p);

    *p=NULL;
}

void addnote(Eleve *eleve, double note)
{
    eleve->sizenote++;
    eleve->notes=(double*)realloc(eleve->notes, eleve->sizenote*sizeof (double));

    if(eleve->notes==NULL)
    {
        printf("Probleme de memoire\n");
        exit(1);
    }

    eleve->notes[eleve->sizenote-1]=note;

    calculMoyenneEleve(eleve);

}
void calculMoyenneEleve(Eleve *eleve)
{
    double tmp=0;
    for(int i=0; i<eleve->sizenote; i++)
        tmp+=eleve->notes[i];

    eleve->moyenne=tmp/eleve->sizenote;

}


int compareElevesByLastName(void *a, void *b)
{
    const Eleve *v1 = *(Eleve* const *) a;
    const Eleve *v2 = *(Eleve* const *) b;

    return strcmp(v1->pname, v2->pname);

}

int compareElevesByFirstName(void *a, void *b)
{
    const Eleve *v1 = *(Eleve* const *) a;
    const Eleve *v2 = *(Eleve* const *) b;

    return strcmp(v1->name, v2->name);
}

int compareElevesByPromo(void *a, void *b)
{
    const Eleve *v1 = *(Eleve* const *) a;
    const Eleve *v2 = *(Eleve* const *) b;

    return strcmp(v1->promo, v2->promo);

}

int compareElevesByMoyenne(void *a, void *b)
{
    const Eleve *v1 = *(Eleve* const *) a;
    const Eleve *v2 = *(Eleve* const *) b;

    if(v1->moyenne>=v2->moyenne)
        return 0;
    else
        return 1;
}

void displayEleve(Eleve *eleve)
{
    printf("             Id:  %d\n", eleve->id);
    printf("            Nom:  %s\n", eleve->name);
    printf("         Prenom:  %s\n", eleve->pname);
    printf("      Promotion:  %s\n", eleve->promo);

    if(eleve->sizenote==0)
        printf("            AUCUNES NOTES\n");
    else {
        printf("            Moyenne:  %.2lf\n", eleve->moyenne);
        printf("            Notes:  %d\n", eleve->sizenote);
        for(int i=0 ; i<eleve->sizenote; i++ )
            printf("                    %d :  %.2lf\n", i+1, eleve->notes[i]);
    }

}


