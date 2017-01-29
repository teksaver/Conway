/***********************************************************************
* (c)2017 - Sylvain Tenier
* Implémentation à but pédagogique de la suite de Conway
* Licence GPL v3 ou toute version ultérieure
* https://www.gnu.org/licenses/gpl-3.0.fr.html
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**
 * renvoie le nombre saisi entre min et max
 * @param int min valeur minimale de la saisie
 * @param int max valeur maximale de la saisie
 * @return la valeur saisie
 */
char saisir(int min, int max)
{
    int n; //valeur à renvoyer entre min et max
    char check; // un char est un entier sur un octet
    do
    {
        check=0;
        printf("Saisissez une valeur entre %d et %d\n",min,max);
        while(check!=1)
        {
            check=fscanf(stdin, "%d", &n);
            getchar();
        }
    }
    while(n<min || n>max);
    return n;
}

/**
 * affiche la suite de Conway
 * @param char * adresse du tableau contenant la suite
 * @param int taille nombre de cases du tableau
 */
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


/**
 * calcule la suite de conway pour la valeur demandée
 * @param char ** adr_suite adresse du pointeur vers la suite
 * @param int n nombre d'itérations souhaitées
 * @return la taille du tableau contenant la suite
 * @return adr_suite adresse du tableau modifiée par la réallocation
 */
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


/**
 * demande le nombre d'itérations si non fourni en argument, calcule et affiche la suite
 * @param int argc nombre d'arguments
 * @param char * argv[] les arguments fournis en entrée
 */
int main(int argc, char * argv[])
{
    char * suite=malloc(sizeof(char)); //suite à afficher
    unsigned long taille;
    char n; //nombre d'itérations
    // si l'utilisateur a fourni un nombre en argument, ce nombre est utilisé
    // sinon on lui demande avec la fonction saisie
    switch(argc)
    {
    //si le programme a été lancé sans argument. argc vaut 1 et argv[0] contient le nom du programme
    case 1:
        n=saisir(1,20);
        break;
    //si le programme a été lancé avec1 argument. argc vaut 1
    //argv[0] contient le nom du programme
    //argv[1] doit contenir un nombre pour indiquer le nombre d'itérations
    case 2:
        n=atoi(argv[1]);
        if(n<=0)
        {
            printf("usage : conway <n>\nVous avez saisi %d. n doit être un entier positif",n);
            exit(-1);
        }
        break;
    default:
        printf("usage : conway <n>\n. Vous devez fourni un seul argument, pas %d. n doit être un entier positif",argc);
        exit(-1);
    }

    printf("Affichage de la suite de Conway pour %d itérations\n",n);
    suite[0]=1;
    taille=calculer_conway(&suite,n); // envoi d'un double pointeur pour gérer la réallocation
    printf("fin du calcul, la suite compte %li chiffres\n",taille);
    afficher_conway(suite,taille);
    return 0;
}
