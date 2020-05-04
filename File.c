#include "File.h"

void SavetoFile(PromotionList *p1, char *filename)
{

    FILE *f = fopen(filename, "w+");

    if(f==NULL)
    {
        printf("ERREUR\n");
    }

    else {

        fprintf(f, "*************************\n");
        fprintf(f, "*Nombre de Promotion: %d*\n",p1->size);
        fprintf(f, "*************************\n");
        if(p1->size==0)
        {
            fprintf(f, "Aucune Promotions\n");
        }
        else
        {

            fprintf(f, "++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

            for(int i=0; i<p1->size; i++)
            {
                calculMoyennePromo(p1->promotion[i]);

                fprintf(f, "              Promotion : %s\n", p1->promotion[i]->name);
                fprintf(f, "        Nombre d'Eleves : %d\n", p1->promotion[i]->size);
                fprintf(f, "Moyenne de la Promotion : %.2lf\n", p1->promotion[i]->moyennepromo);

                if(p1->promotion[i]->size==0)
                {
                    fprintf(f, "----------------------------------------------------\n");
                    fprintf(f, "                AUCUN ELEVES                        \n");
                    fprintf(f, "----------------------------------------------------\n");

                }
                else
                {
                    fprintf(f, "----------------------------------------------------\n");

                    for(int j=0; j<p1->promotion[i]->size; j++)
                    {

                        fprintf(f,"             Id:  %d\n", p1->promotion[i]->eleves[j]->id);
                        fprintf(f,"            Nom:  %s\n", p1->promotion[i]->eleves[j]->name);
                        fprintf(f,"         Prenom:  %s\n", p1->promotion[i]->eleves[j]->pname);

                        if(p1->promotion[i]->eleves[j]->sizenote==0)
                            fprintf(f,"            AUCUNES NOTES\n");
                        else {
                            fprintf(f,"        Moyenne:  %.2lf\n", p1->promotion[i]->eleves[j]->moyenne);
                            fprintf(f,"        Notes:  %d\n", p1->promotion[i]->eleves[j]->sizenote);
                            fprintf(f, "****************************************************\n");
                            for(int k=0 ; k<p1->promotion[i]->eleves[j]->sizenote; k++ )
                            {
                                fprintf(f,"                    %d :  %.2lf\n", k, p1->promotion[i]->eleves[j]->notes[k]);
                                fprintf(f, "****************************************************\n");
                            }


                        }
                        fprintf(f, "----------------------------------------------------\n");


                    }
                }
                fprintf(f, "++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

            }

        }

    }
    fclose(f);
}

