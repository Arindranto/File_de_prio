/* File de priorite suivant la regle de parite + Rmin donc:
** a prioritaire par rapport a b si a pair et a < b */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int tab[100];
int n= 0, tmp;   // La dimension du tableau

/* Procedure d'ajout d'un element suivant les regles de priorite defini aux lignes 1 et 2*/
void ajouter(int nbr){
    unsigned i= n;  // l'indice actuel du nouvel element
    // On insere le nouvel element a la fin du tableau, la dimension augmente
    tab[n++]= nbr;

    // Placement de nbr a sa place suivant l'ordre de priorite
    while (i > 0 && (!((tab[(i-1)/2] - nbr) % 2) && nbr < tab[(i-1)/2] || tab[(i-1)/2] % 2 && !(nbr % 2)))
    {
        // Swap
        tmp= tab[(i-1)/2];
        tab[(i-1)/2]= nbr;
        tab[i]= tmp;
        // Modification de la valeur de i
        i= (i-1)/2;
    }
    return;
}

/* Fonction d'extraction */
int extraire(){
    int prio= tab[0];   // On memorise l'element prioritaire
    tab[0]= tab[--n];   // Copie de la derniere valeur dans l'indice 0
    int p= 0, f= 1;     // Initialisation de l'indice du pere et celui du fils prioritaire

    // Dans le cas où le fils prioritaire est le fils droite
    if (f+1 > 0 && (!((tab[f] - tab[f+1]) % 2) && tab[f+1] < tab[f] || tab[f] % 2 && !(tab[f+1] % 2)))
        f++;

    // Replacement dans le tableau
    while (f<n && (!((tab[p] - tab[f]) % 2) && tab[f] < tab[p] || tab[p] % 2 && !(tab[f] % 2))){
        // Swap
        tmp= tab[p];
        tab[p]= tab[f];
        tab[f]= tmp;

        // Modification des valeurs de p et f
        p= f;   // p reprend l'indice de l'ancien fils prioritaire
        f= 2*p+1;   // F recoit l'indice du nouveau fils gauche
        // Determination du fils prioritaire
        if (f+1 > 0 && (!((tab[f] - tab[f+1]) % 2) && tab[f+1] < tab[f] || tab[f] % 2 && !(tab[f+1] % 2)))
            f++;
    }
    return prio; // On retourne l'element prioritaire
}

// Tri prioritaire in situ inverse
void tri_inverse(){
    int i, m= n;
    n= 0;   // Avant entassment, mettre n a 0 pour etre incrementer lors de l'appel de la fonction ajouter()
    // Entassement
    for(i= 0; i< m; i++)
        ajouter(tab[i]);
    // Detassement
    for(i= m-1; i>=0; i--){
        tab[i]= extraire();
    }
    n= m;   // Rendre la valeur de la dimension
    return;
}

/* Procedure d'affichage du tableau tab */
void afficher(){
    int i;
    for (i= 0; i<n; i++)
        printf("%4d", tab[i]);
    puts("");
    return;
}

int main()
{
    srand(time(0)); // Pour lancer srand avec différents germes à chaque fois
    int i;
    n= 15;
    for (i= 0; i<n; i++)
        tab[i] = rand()%30;
    afficher();
    tri_inverse();
    afficher();
    return 0;
}
