#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//prototypes
void affiche_tableau( int** tab, int** sol, int val1, int val2);
int randin(int min, int max);
void generate_solution( int* tab, int val, int range);


// affiche le tableau et le nombre de coups biens et mal placés
void affiche_tableau( int** tab, int** sol, int val1, int val2)
{
    int i,j;
    for (i=0;i<val1;i++)
    {
        printf("\n");
        for (j=0;j<val2;j++)
        {
            printf("%d, ",tab[i][j]);
        }
        printf("\t good : %d   almost : %d",sol[i][0],sol[i][1]);
    }
}

int randin(int min, int max)
{
    return (min+ (rand() % (max-min+1)));
}

void generate_solution( int* tab, int val, int range)
{
    int i;
    for (i=0;i<val;i++)
    {
        tab[i] = randin(1,range);
        printf("%d",tab[i]);
    }

}

int main()
{
    // seed pour le random
    srand((time(NULL)));

    // déclaration des variables du main
    int essais,largeur,repetition,range;
    int i,j,k;
    int input;
    int diff, n;
    int tour;
    int idverif;

    printf("\n\n");
    printf("-----------------------------------\n");
    printf("|                                 |\n");
    printf("|          MASTERMIND             |\n");
    printf("|          (Remi Vion)            |\n");
    printf("-----------------------------------\n\n");

    // on entre des différents paramètres
    printf("\n\nlenth of solution  (3 - 10) = ");
    scanf("%d",&largeur);
    if (largeur<3) {largeur =3;}
    else if (largeur>10) {largeur=10;}

    printf("number of tries    (5 - 50) = ");
    scanf("%d",&essais);
    if (essais<5) {essais=5;}
    else if (essais>50) {essais=50;}

    printf("number of colros    (2 - 9) = ");
    scanf("%d",&range);
    if (range<2) {range=2;}
    else if (range>9) {range=9;}

    printf("recurent colors ( 1 = yes ) = ");
    scanf("%d",&repetition);
    if (repetition != 1) {repetition =0;}

    // on initialise les differentes structures de données
    // dynamique en fonction des paramètres rentrés.
    printf("\ninitialisation ..");
    int*  solution = malloc (sizeof(int)  * largeur);
    int*  verif    = malloc (sizeof(int)  * largeur);
    int** tsol     = malloc (sizeof(int*) * essais);
    int** tjeu     = malloc (sizeof(int*) * essais);

    for (i=0; i<essais; i++)
    {
        tjeu[i] = malloc (sizeof(int) * largeur);
        tsol[i] = malloc (sizeof(int) * 2);
    }

    // on initialise les valeurs des structures de données créées
    for (i=0; i<essais ;i++)
    for (j=0; j<largeur;j++)
        { tjeu[i][j] = 0; }

    for (i=0; i<essais; i++)
    for (j=0; j<2;      j++)
        { tsol[i][j] = 0; }

    for (i=0; i<largeur ;i++)
        { verif[i]    = 0;
          solution[i] = 0; }

    generate_solution(solution,largeur,range);
    printf("\ninitialissation sucess\n\n");

    // on se prépare à lancer la partie
    tour=0;

    // boucle principale du jeu
    for (i=0; i<essais; i++)
    {
        idverif = 0;

        // on demande un entier qui correspond à la solution au joueur
        printf("\n\n\ntry (%d / %d) : ",(tour+1),essais);
        scanf("%d",&input);

        // on décompose le nombre rentré en liste de couleurs
        n=0;

        while ((n<largeur) && (input >= 1))
        {
            diff = input%10;
            input /= 10;
            tjeu[tour][largeur-1-n]=diff;
            n+=1;
        }

        for (j=n; j<largeur;j++)
        {
            tjeu[tour][largeur-1-j]=0;
        }

        // on vérifie la solution proposée
        for (j=0; j<largeur; j++)
        {
            if (tjeu[i][j] == solution[j]) {tsol[i][0]++;}
            else
            {
                verif[idverif]=tjeu[i][j];
                idverif++;
            }
        }
        for (j=0; j<largeur; j++)
        {
            if (tjeu[i][j] != solution[j])
            {
                for(k=0;k<idverif;k++)
                {
                    if (verif[k]==solution[j])
                    {
                        tsol[i][1]++;
                        verif[k]=-1;
                        k=idverif;
                    }
                }
            }
        }
        // quand le joueur propose une solution,
        // on affiche l'etat actuel du jeu
        affiche_tableau(tjeu,tsol,tour+1,largeur);

        //on incrémente le tour
        if (tsol[tour][0] == largeur)
             {  printf("\n\n\n BRAVO, you won! \n");
                getchar();
                i = essais; }
        else { tour++; }
    }

    // fin du programme
    // scanf pour que la console ne se quitte pas
    printf("\n");
    scanf("%d",&i);
    return 0;

}
