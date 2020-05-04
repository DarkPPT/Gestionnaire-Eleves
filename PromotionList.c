#include "PromotionList.h"

PromotionList *createPromotionList()
{
    PromotionList *mycurentList;

    mycurentList = malloc(sizeof(PromotionList));

    mycurentList->promotion=NULL;
    mycurentList->size=0;
    mycurentList->curentIdPromo=1;
    mycurentList->currentIdEleve=1;

    return mycurentList;
}

void deletePromotionList(PromotionList **p)
{
    for(int i=0; i<(*p)->size; i++)
        deletePromotion(&(*p)->promotion[i]);
    free(*p);

    *p=NULL;
}

void deletePromotionFromList(PromotionList *promolist, Promotion *promo )
{
    Promotion* tmp;

    for(int i=0; i<promolist->size-1;i++)
    {
        for(int j=0; j<promolist->size-1; j++)
            if(promolist->promotion[j]==promo)
            {
                tmp=promolist->promotion[j];
                promolist->promotion[j]=promo;
                promolist->promotion[j+1]=tmp;
            }
    }

    deletePromotion(&promolist->promotion[promolist->size-1]);
    promolist->size--;
    void *ptrnull=(Promotion**)realloc(promolist->promotion, promolist->size*sizeof(Promotion*));

    if(ptrnull==NULL)
    {
        printf("Probleme de memoire\n");
        exit(1);
    }
    else {
        promolist->promotion=ptrnull;
    }
}

void addPromotion(PromotionList *p1, Promotion *pe)
{


    pe->id=p1->curentIdPromo;
    p1->curentIdPromo++;

    p1->size++;
    p1->promotion=(Promotion**)realloc(p1->promotion, p1->size*sizeof(Promotion*));

    if(p1->promotion==NULL)
    {
        printf("Probleme de memoire\n");
        exit(1);
    }

    p1->promotion[p1->size-1]=pe;
}

void removePromotion(PromotionList *list, Promotion *pe)
{
    Promotion* tmp;

    if(list->size==0)
    {
        printf("\nAUCUNE PROMOTION A SUPPRIMER");
    }
    else {
        for(int i=0; i<list->size-1;i++)
        {
            for(int j=0; j<list->size-1; j++)
                if(list->promotion[j]==pe)
                {
                    tmp=list->promotion[j];
                    list->promotion[j]=list->promotion[j+1];
                    list->promotion[j+1]=tmp;

                }


        }

        deletePromotion(&list->promotion[list->size-1]);

        list->size--;
        list->promotion=realloc(list->promotion, list->size*sizeof(Promotion*));

    }


}

void displayList(PromotionList* p1)
{
    if(p1->size==0)
    {
        printf("                                  |Aucune promotions disponible|\n");
    }
    else {


        for(int i=0; i<p1->size; i++)
        {
            printf("                             - %d : %s\n",p1->promotion[i]->id
                   , p1->promotion[i]->name);
        }
    }
}

int findPromotionfromId(PromotionList *p1, int id)
{
    for(int i=0; i<p1->size; i++)
    {
        if(p1->promotion[i]->id==id)
        {
            return 0;
        }

    }

    return 1;
}


Promotion *getPromotionfromId(PromotionList *p1, int id)
{
    for(int i=0; i<p1->size; i++)
    {
        if(p1->promotion[i]->id==id)
        {
            return p1->promotion[i];
        }

    }

}




