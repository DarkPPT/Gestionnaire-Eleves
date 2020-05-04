#include "Promotion.h"

#ifndef _PROMOTION_LIST_H_
#define _PROMOTION_LIST_H_

typedef struct PromotionList PromotionList;

struct PromotionList
{
    Promotion **promotion;
    int size;
    int curentIdPromo;
    int currentIdEleve;


};



PromotionList *createPromotionList();

void deletePromotionList(PromotionList **p);
void deletePromotionFromList(PromotionList *promolist, Promotion *promo );

void addPromotion(PromotionList *p1, Promotion *pe);
void removePromotion(PromotionList *list, Promotion *pe);

void displayList(PromotionList* p1);

int findPromotionfromId(PromotionList *p1, int id);
Promotion *getPromotionfromId(PromotionList *p1, int id);

#endif
