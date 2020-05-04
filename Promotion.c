#include "PromotionList.h"


Promotion *createPromotion(char *name)
{

    Promotion *myEleve;

    myEleve=(Promotion *)malloc(sizeof(Promotion));
    if(myEleve==NULL)
    {
        printf("Probleme de memoire\n");
        exit(1);
    }

    myEleve->name=(char *)malloc(sizeof (char)*strlen(name));
    if(myEleve->name==NULL)
    {
        printf("Probleme de memoire\n");
        exit(1);
    }

    myEleve->eleves=NULL;
    myEleve->size=0;
    myEleve->curentid=0;
    myEleve->moyennepromo=0;

    strcpy(myEleve->name, name);

    return myEleve;
}

void deletePromotion(Promotion **p)
{

    for(int i=0;i<(*p)->size;i++)
        deleteEleve(&(*p)->eleves[i]);

    free((*p)->name);

    free(*p);
    *p=NULL;
}

void addEleve(Promotion *p1, Eleve *pe)
{
    Eleve *my;
    my=createEleve(pe->name, pe->pname, p1->name,pe->id);
    for(int i=0; i<pe->sizenote; i++)
        addnote(my,pe->notes[i]);

    p1->size++;

    p1->eleves=(Eleve**)realloc(p1->eleves, p1->size*sizeof(Eleve*));
    if(p1->eleves==NULL)
    {
        printf("Probleme de memoire\n");
        exit(1);
    }

    p1->eleves[p1->size-1]=my;
}

void displayPromotion(Promotion* p1)
{
    if(p1->size==0)
    {
        printf("AUCUN ELEVES\n");
    }
    else {
        for(int i=0; i<p1->size; i++)
        {
            printf("%d : %s %s : %.2lf\n",p1->eleves[i]->id, p1->eleves[i]->name, p1->eleves[i]->pname, p1->eleves[i]->moyenne);
            printf("\n");
        }
    }


}

void deleteEleveFromPromotion(Promotion *list, int id)
{
    Eleve* tmp;

    for(int i=0; i<list->size-1;i++)
    {
        for(int j=0; j<list->size-1; j++)
            if(list->eleves[j]->id==id)
            {
                tmp=list->eleves[j];
                list->eleves[j]=list->eleves[j+1];
                list->eleves[j+1]=tmp;
            }
    }

    list->eleves[list->size-1]=NULL;
    list->size--;

    list->eleves=(Eleve*)realloc(list->eleves, list->size*sizeof(Eleve*));


}


int findElevefromId(Promotion *p1, int id)
{
    for(int i=0; i<p1->size; i++)
    {
        if(p1->eleves[i]->id==id)
        {
            return 0;
        }

    }

    return 1;
}

Eleve *getElevefromId(Promotion *p1, int id)
{
    for(int i=0; i<p1->size; i++)
    {
        if(p1->eleves[i]->id==id)
        {
            return p1->eleves[i];
        }

    }
}

void calculMoyennePromo(Promotion* mypromo)
{
    double tmp=0;

    if(mypromo->size==0)
        mypromo->moyennepromo=0;
    else {



        for(int i=0; i<mypromo->size; i++)
            tmp+=mypromo->eleves[i]->moyenne;

        mypromo->moyennepromo=tmp/mypromo->size;
    }
}



void sortEleves(Promotion *mypromo,int (cmp )(void *a, void *b) )
{
    qsort(mypromo->eleves, mypromo->size, sizeof (struct Eleve*), cmp);
}
