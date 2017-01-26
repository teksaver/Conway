#include <stdio.h>
#include <stdlib.h>

char saisir()
{
    int n; //valeur à renvoyer entre 1 et 20
    int check;
    do
    {
        check=0;
        printf("Saisissez une valeur entre 1 et 20\n");
        while(check!=1)
        {
            check=fscanf(stdin, "%d", &n);
            getchar();
        }
    }
    while(n<1 || n>100);
    return n;
}

void afficher_conway(char * suite,int taille)
{
    int i;
    printf("La suite est :");
    for(i=0; i<taille; i++)
    {
        printf("%d",suite[i]);
    }
    printf("\n");
}

unsigned long calculer_conway(char ** adr_suite, int n)
{
    char * suite=*adr_suite; // récupération du tableau initial à une case
    char * buffer;
    unsigned long pos_suite; //position pour le parcours de la suite
    unsigned long pos_buffer; // position pour le remplissage du buffer
    int occ; //occurences de lu chiffre traité
    char chiffre;
    int i;
    unsigned long taille_suite=1; //nombre de chiffres dans la suite calculée
    //au départ la suite contient 1
    for(i=1; i<n; i++)
    {
        //printf("** etape #%d***\n",i+1);
        pos_suite=0;
        pos_buffer=0;
        chiffre=suite[0];
        occ=0;
        buffer=malloc(2*taille_suite*sizeof(char));
        //suite+=1;
        while(pos_suite<taille_suite)
        {
            // si le chiffre suivant on incrémente l'occurence
            if(suite[pos_suite]==chiffre)
            {
                occ+=1;
            }
            // sinon on décale le buffer et on traite un nouveau chiffre
            // occ est réinitilialisé à 1 car on a déjà vu ce chiffre
            else
            {
                pos_buffer+=2;
                chiffre=suite[pos_suite];
                occ=1;
            }
            // dans tous les cas on met à jour la situation dans le buffer
            buffer[pos_buffer]=occ;
            buffer[pos_buffer+1]=chiffre;
            pos_suite+=1;
        }
        //enregistrement de la taille
        taille_suite=pos_buffer+2;
        //printf("fin de l'étape %d/%d.La nouvelle suite fait %li chiffres\n",i+1,n,taille_suite);
        free(suite); //libération de la mémoire
        suite=buffer;
    }

    *adr_suite=suite; // on remet la suite calculée à la bonne adresse
    return taille_suite;
}



int main()
{
    char * suite=malloc(sizeof(char)); //suite à afficher
    unsigned long taille;
    char n; //nombre d'itérations
    n=saisir();
    printf("Affichage de la suite de Conway pour %d itérations\n",n);
    suite[0]=1;
    taille=calculer_conway(&suite,n);
    printf("fin du calcul, la suite compte %li chiffres\n",taille);
    afficher_conway(suite,taille);
    return 0;
}
