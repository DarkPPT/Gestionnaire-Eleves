#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include "PromotionList.h"
#include "File.h"



PromotionList *curentList;
long idpromo;
long ideleve;

int idEleveGlobal=1;





void MenuModifiePromotion();
void MenuPrincipale();
void MenuListerEleves();
void MenuModifierEleves();

int getIdPromotion();
int getIdEleve();


int checkarray(char *str);
int checkinteger(char *str);

void capitalize(char* str);
void capitalizename(char* str);
int lire(char *chaine, int longueur);
long lireLong();
void clearscr();
void viderBuffer();
void exitProgramme();

int main()
{

    curentList=createPromotionList();
    MenuPrincipale();

    /*system("COLOR 1");
    printf("Hello World");*/



    return 0;
}


void MenuPrincipale()
{
    long choix = 0;
    char choixpromo[20];
    char filename[20];


    while (1) {
        printf("        _____                        __________        .__              .__             .__\n");
        printf("       /     \\   ____   ____  __ __  \\______   \\_______|__| ____   ____ |__|__________  |  |\n");
        printf("      /  \\ /  \\_/ __ \\ /    \\|  |  \\  |     ___/\\_  __ \\  |/    \\_/ ___\\|  \\____ \\__  \\ |  |\n");
        printf("     /    Y    \\  ___/|   |  \\  |  /  |    |     |  | \\/  |   |  \\  \\___|  |  |_> > __ \\|  |__\n");
        printf("     \\____|__  /\\___  >___|  /____/   |____|     |__|  |__|___|  /\\___  >__|   __(____  /____/\n");
        printf("      \\/     \\/     \\/                                  \\/     \\/   |__|       \\/\n");
        printf("        `.______________________________________________________________________________.'    \n");
        printf("         || ||                                                                      || ||    \n");
        printf("         || ||  1- Ajouter une promotion.                                           || ||    \n");
        printf("         || ||  2- Supprimer une promotion.                                         || ||    \n");
        printf("         || ||  3- Modifier une promotion.                                          || ||    \n");
        printf("         || ||  4- Voir tout les eleves.                                            || ||    \n");
        printf("         || ||  5- Enregistrer un rapport.                                          || ||    \n");
        printf("         || ||  6- Quitter.                                                         || ||    \n");
        printf("        _||_||______________________________________________________________________||_||_   \n");
        printf("       .'________________________________________________________________________________`.  \n");
        displayList(curentList);



        printf("Choix: ");
        choix = lireLong();

        if((choix==0 || !(choix<=7 && choix >=1)))
        {
            clearscr();
            printf("Choix Errone\n");
            MenuPrincipale();


        }

        switch (choix) {
        case 1 :


            printf("Nom de la promotion:");
            lire(choixpromo, 20);

            if(strlen(choixpromo)!=0)
            {
                addPromotion(curentList, createPromotion(choixpromo));
                clearscr();
                printf("La promotion %s a ete cree\n", choixpromo);

            }
            else {
                clearscr();
                printf("La promotion ne peut pas avoir de nom vide\n");
            }

            break;
        case 2:

            if(getIdPromotion()==1)
            {
                clearscr();
                printf("La promotion est introuvable\n");

            }
            else
            {
                removePromotion(curentList, getPromotionfromId(curentList, idpromo));
                clearscr();
                printf("La promotion a ete supprimer\n");

            }
            break;
        case 3:

            if(getIdPromotion()==0)
            {
                clearscr();
                MenuModifiePromotion();
            }
            else {
                clearscr();
                printf("La promotion est introuvable\n");
            }
            break;
        case 4:
            if(curentList->size==0)
            {
                clearscr();
                printf("Auncune promotions disponible\n");
            }
            else {
                clearscr();
                for(int i=0; i<curentList->size; i++)
                {


                    printf("\nPromotion : %s\n\n", curentList->promotion[i]->name);
                    calculMoyennePromo(curentList->promotion[i]);
                    printf("Moyenne de la promotion : %.2lf\n\n", curentList->promotion[i]->moyennepromo);

                    if(curentList->promotion[i]->size==0)
                    {
                        printf("|===========================================|\n");
                        printf("|    Auncun Eleves dans cette promotion     |\n");
                        printf("|===========================================|\n");

                    }
                    else {
                        printf("|===========================================|\n");
                        for(int j=0; j<curentList->promotion[i]->size; j++)
                        {
                            printf("%d : %s %s %.2f\n", curentList->promotion[i]->eleves[j]->id, curentList->promotion[i]->eleves[j]->name, curentList->promotion[i]->eleves[j]->pname, curentList->promotion[i]->eleves[j]->moyenne );

                        }
                        printf("|===========================================|\n");


                    }

                }
                printf("Cliquer sur une touche pour continuer\n");
                getch();
                clearscr();


            }
            break;

        case 5:
            printf("\nNom du rapport: ");
            lire(filename,20);

            if(strlen(filename)==0)
            {
                clearscr();
                printf("Le nom ne peut pas etre vide\n");
            }
            else {
                char tmp[23];
                memset(tmp,0,23);

                strcat(tmp, filename);
                strcat(tmp, ".txt");

                SavetoFile(curentList,tmp);
                memset(filename, 0, 20);
                memset(tmp,0,23);
                clearscr();
                printf("Fichier Cree\n");
            }

            break;
        case 6:
            exitProgramme();
            break;
        }

    }
}







void MenuModifiePromotion()
{
    char nom[20];
    char pnom[20];
    Promotion *mypromo;


    mypromo=getPromotionfromId(curentList, idpromo);

    long choix = 0;

    printf("   |===========================================|\n");
    printf("          Promotion : %s                        \n", mypromo->name);
    printf("   |===========================================|\n");
    printf("   |  1- Lister les eleves.                    |\n");
    printf("   |  2- Ajouter un eleve.                     |\n");
    printf("   |  3- Supprimer un eleve.                   |\n");
    printf("   |  4- Modifier un eleve.                    |\n");
    printf("   |  5- Ajouter une note.                     |\n");
    printf("   |  6- Detail d'un eleve.                    |\n");
    printf("   |  7- Retour.                               |\n");
    printf("   |===========================================|\n");
    printf("Choix: ");
    choix = lireLong();

    if((choix==0 || !(choix<=7 && choix >=1)))
    {
        clearscr();
        MenuModifiePromotion();
    }
    else
    {

        switch (choix) {
        case 1 :
            clearscr();
            MenuListerEleves();
            break;
        case 2:
            clearscr();
            printf("Nom:");
            lire(nom, 20);

            if(strlen(nom)==0 || checkarray(nom))
            {
                printf("Le nom n'est pas dans le bon format\n");
                MenuModifiePromotion();
            }
            else {
                capitalizename(nom);
                printf("Prenom:");
                lire(pnom, 20);

                if(strlen(pnom)==0 || checkarray(pnom))
                {
                    printf("Le prenom n'est pas dans le bon format\n");
                    MenuModifiePromotion();
                }
                else {
                    capitalize(pnom);
                    mypromo=getPromotionfromId(curentList,idpromo);
                    addEleve(getPromotionfromId(curentList, idpromo),createEleve(nom, pnom,mypromo->name,curentList->currentIdEleve));
                    curentList->currentIdEleve++;
                    clearscr();
                    printf("Eleve ajoute\n");
                    MenuModifiePromotion();

                }
            }

            break;
        case 3:
            if(getIdEleve()==1)
            {
                MenuModifiePromotion();
            }
            else
            {

                deleteEleveFromPromotion(getPromotionfromId(curentList, idpromo), ideleve);
                clearscr();
                printf("Eleve Supprimer\n");
                MenuModifiePromotion();
            }
            break;
        case 4:
            if(getIdEleve()==1)
            {
                clearscr();
                printf("ELEVE INTROUVABLE\n");
                MenuModifiePromotion();
            }
            else {
                clearscr();
                MenuModifierEleves();
            }

            clearscr();
            break;
        case 5:

            mypromo=getPromotionfromId(curentList,idpromo);

            if(mypromo->size==0)
            {
                printf("AUCUN ELEVES\n");
                MenuModifiePromotion();

            }
            else {
                for(int i=0; i<mypromo->size; i++)
                {
                    printf("%d : %s %s\n", mypromo->eleves[i]->id, mypromo->eleves[i]->name, mypromo->eleves[i]->pname);
                    double temp;
                    printf(">");


                    while (scanf("%lf", &temp)==0|| !(temp>=0 && temp<=20))
                    {
                        printf ("Mauvais format !\n");
                        fflush(stdin);
                    }

                    addnote(mypromo->eleves[i], temp);
                }
                clearscr();
                MenuModifiePromotion();
            }

            break;
        case 6:

            if(getIdEleve()==1)
            {
                clearscr();
                MenuModifiePromotion();
            }
            else
            {
                clearscr();
                Promotion *mypromo = getPromotionfromId(curentList,idpromo);
                displayEleve(getElevefromId(mypromo, ideleve));
                MenuModifiePromotion();
            }

            break;
        case 7:
            clearscr();
            MenuPrincipale();

            break;
        }

    }

}




void MenuListerEleves()
{
    long choix;
    Promotion *mypromo;

    printf("   |===========================================|\n");
    printf("   |  1- Voir par nom.                         |\n");
    printf("   |  2- Voir par prenom.                      |\n");
    printf("   |  3- Voir par moyenne.                     |\n");
    printf("   |  4- Retour.                               |\n");
    printf("   |===========================================|\n");
    printf("Choix: ");
    choix = lireLong();

    if((choix==0 || !(choix<=4 && choix >=1)))
    {
        clearscr();
        MenuListerEleves();
    }

    switch (choix) {
    case 1 :
        clearscr();


        mypromo = getPromotionfromId(curentList, idpromo);
        sortEleves(mypromo, compareElevesByFirstName);
        displayPromotion(mypromo);
        MenuListerEleves();

        break;
    case 2:
        clearscr();
        mypromo = getPromotionfromId(curentList, idpromo);
        sortEleves(mypromo, compareElevesByLastName);
        displayPromotion(mypromo);
        MenuListerEleves();

        break;
    case 3:
        clearscr();
        mypromo = getPromotionfromId(curentList, idpromo);
        sortEleves(mypromo, compareElevesByMoyenne);
        displayPromotion(mypromo);
        MenuListerEleves();

        break;
    case 4:
        clearscr();
        MenuModifiePromotion();
        break;
    }



}



void MenuModifierEleves()
{
    long choix;
    Promotion *mypromo;
    Eleve *myEleve;
    char nom[20];
    char pnom[20];
    double temp;

    mypromo = getPromotionfromId(curentList,idpromo);
    myEleve = getElevefromId(mypromo, ideleve);

    displayEleve(myEleve);
    printf("   |===========================================|\n");
    printf("   |  1- Modifier le nom.                      |\n");
    printf("   |  2- Modifier le prenom.                   |\n");
    printf("   |  3- Modifier les notes.                   |\n");
    printf("   |  4- Changer l'Eleve de Promotion.         |\n");
    printf("   |  5- Retour.                               |\n");
    printf("   |===========================================|\n");
    printf("Choix: ");
    choix = lireLong();

    if((choix==0 || !(choix<=5 && choix >=1)))
    {
        clearscr();
        MenuModifierEleves();
    }

    switch (choix) {
    case 1 :
        printf("Nouveau Nom:");
        lire(nom, 20);

        if(checkarray(nom))
        {
            clearscr();
            printf("Le nom est invalide\n");
            MenuModifierEleves();
        }
        else
        {
            capitalizename(nom);
            addEleve(getPromotionfromId(curentList, idpromo),createEleve(nom, myEleve->pname,mypromo->name,0));
            Eleve *new = getElevefromId(mypromo, 0);

            if(myEleve->sizenote!=0)
            {
                for(int i=0; i<myEleve->sizenote; i++)
                    addnote(new,myEleve->notes[i]);
            }


            deleteEleveFromPromotion(mypromo, myEleve->id);
            new->id=ideleve;

            clearscr();
            printf("Eleve modifier\n");
            MenuModifierEleves();

        }
        break;
    case 2:
        printf("Nouveau Prenom:");
        lire(pnom, 20);

        if(checkarray(pnom))
        {
            clearscr();
            printf("Le nom est invalide\n");
            MenuModifierEleves();
        }
        else
        {
            capitalize(pnom);
            addEleve(getPromotionfromId(curentList, idpromo),createEleve(myEleve->name, pnom,mypromo->name,0));
            Eleve *new = getElevefromId(mypromo, 0);

            for(int i=0; i<myEleve->sizenote; i++)
                addnote(new,myEleve->notes[i]);


            deleteEleveFromPromotion(mypromo, myEleve->id);
            new->id=ideleve;

            clearscr();
            printf("Eleve modifier\n");
            MenuModifierEleves();

        }
        break;
    case 3:

        if(myEleve->sizenote==0)
        {
            clearscr();
            printf("Aucune notes a modifier\n");
            MenuModifierEleves();

        }
        else {


            for(int i=0; i<myEleve->sizenote; i++)
            {
                printf("Ancienne note: %.2lf\n", myEleve->notes[i]);
                printf("Nouvelle note:");

                while (scanf("%lf", &temp)==0|| !(temp>=0 && temp<=20))
                {
                    printf ("Mauvais format !\n");
                    printf("Nouvelle note:");

                }

                myEleve->notes[i]=temp;


            }
            calculMoyenneEleve(myEleve);
            MenuModifierEleves();
        }

        break;
    case 4:

        displayList(curentList);
        printf("ID de la promotion:\n");
        if(getIdPromotion()==1)
        {
            clearscr();
            printf("Promotion Introuvable\n");
            MenuModifierEleves();
        }
        else {
            Promotion *newpromo = getPromotionfromId(curentList,idpromo);
            addEleve(newpromo,myEleve);
            deleteEleveFromPromotion(mypromo,ideleve);
            MenuModifierEleves();
        }

        break;
    case 5:
        clearscr();
        MenuModifiePromotion();
        break;
    }



}




int getIdPromotion()
{

    long choix =0;

    printf("Id promo: ");
    choix = lireLong();

    if(findPromotionfromId(curentList, choix)==1)
    {
        return 1;
    }
    else {
        idpromo=choix;
        clearscr();
        return 0;
    }



}

int getIdEleve()
{
    long choix =0;

    printf("Id eleve: ");
    choix = lireLong();

    if(findElevefromId(getPromotionfromId(curentList, idpromo), choix)==1)
    {
        return 1;
    }
    else {
        ideleve=choix;
        return 0;
    }

    clearscr();
}












int checkarray(char *str)
{
    int i;

    for(i=0;str[i]!='\0';i++)
    {
        if( !( ( str[i]>='a' && str[i]<='z' ) || ( str[i]>='A' && str[i]<='Z')))
        {
            return 1;
        }

    }

    return 0;
}

int checkinteger(char *str)
{
    int i;

    if(str[0]==',')
        return 1;

    for(i=1;str[i]!='\0';i++)
    {
        if( ! (( str[i]>='0' && str[i]<='9') | (str[i]!='.')))
        {
            return 1;
        }

    }

    return 0;
}








void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }

        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}
long lireLong()
{
    char nombreTexte[100] = {0};
    if (lire(nombreTexte, 100))
        return strtol(nombreTexte, NULL, 10);
    else
        return 0;
}


void clearscr()
{
    system("@cls||clear");
}

void exitProgramme()
{
    deletePromotionList(&curentList);
    exit(0);
}
void capitalize(char* str){

    int i;
    if(str[0] >= 'a' && str[0] <= 'z')
        str[0]-=32;

    for(i=1;str[i]!='\0';i++)
    {
        if(str[i-1]==' ')
        {
            if(str[i] >= 'a' && str[i] <= 'z')
                str[i]-=32;

        }
        else
        {
            if(str[i] >= 'A' && str[i] <= 'Z')
                str[i]+=32;
        }
    }

}

void capitalizename(char* str){

    int i;

    for(i=0;str[i]!='\0';i++)
    {
        if(str[i] >= 'a' && str[i] <= 'z')
            str[i]-=32;
    }
}

