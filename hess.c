#include <stdio.h>
#include <stdlib.h> // Pour la fonction abs
#include <ctype.h>  // Pour la fonction toupper
#include <stdbool.h> // Pour utiliser le type bool

// Taille de l'échiquier (8x8)
#define SIZE 8

// Fonction pour initialiser un échiquier vide
void init_chessboard(int chessboard[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            chessboard[i][j] = 0; // Échiquier vide
        }
    }
}

// Fonction pour afficher l'échiquier
void display_chessboard(int chessboard[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%2d ", chessboard[i][j]);
        }
        printf("\n");
    }
}

// Fonction pour convertir la notation d'échecs en indices de liste
int chess_to_indices(char colonne, int ligne)
{
    // Assurez-vous que la lettre de la colonne est en majuscule
    colonne = toupper(colonne);

    // Vérifiez que les coordonnées sont valides
    if (colonne < 'A' || colonne > 'H' || ligne < 1 || ligne > 8)
    {
        printf("Coordonnées d'échecs invalides.\n");
        return -1; // Indique une erreur
    }

    // Convertissez la lettre de la colonne en un indice de 0 à 7
    int indiceColonne = colonne - 'A';

    // Convertissez le numéro de ligne en un indice de 0 à 7
    int indiceLigne = 8 - ligne;

    // Calculez l'indice de la liste 2D en utilisant les indices de colonne et de ligne
    int indiceListe = indiceLigne * 8 + indiceColonne;

    return indiceListe;
}

// Fonction pour vérifier si une pièce peut être déplacée vers une case d'arrivée
bool is_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee) {
    // Vérifier si les coordonnées de départ et d'arrivée sont valides
    if (ligneDepart < 0 || ligneDepart >= SIZE || colonneDepart < 0 || colonneDepart >= SIZE ||
        ligneArrivee < 0 || ligneArrivee >= SIZE || colonneArrivee < 0 || colonneArrivee >= SIZE) {
        return false; // Déplacement invalide
    }

    int pieceDepart = chessboard[ligneDepart][colonneDepart];
    int pieceArrivee = chessboard[ligneArrivee][colonneArrivee];

    // Vérifier si les pièces sont de la même couleur (positives ou négatives)
    if ((pieceDepart > 0 && pieceArrivee > 0) || (pieceDepart < 0 && pieceArrivee < 0)) {
        return false; // Déplacement invalide (même famille)
    }

    return true; // Déplacement valide par défaut
}


// Fonction pour vérifier si la tour peut se déplacer
int is_rook_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee)
{
    // Vérifier si la tour se déplace horizontalement ou verticalement
    if (ligneDepart == ligneArrivee || colonneDepart == colonneArrivee)
    {
        // Vérifier que la trajectoire est libre
        int deltaLigne = abs(ligneArrivee - ligneDepart);
        int deltaColonne = abs(colonneArrivee - colonneDepart);
        int pasLigne = (ligneDepart == ligneArrivee) ? 0 : (ligneArrivee > ligneDepart) ? 1
                                                                                        : -1;
        int pasColonne = (colonneDepart == colonneArrivee) ? 0 : (colonneArrivee > colonneDepart) ? 1
                                                                                                  : -1;

        for (int i = 1; i < deltaLigne + deltaColonne; i++)
        {
            int ligneIntermediaire = ligneDepart + i * pasLigne;
            int colonneIntermediaire = colonneDepart + i * pasColonne;
            if (chessboard[ligneIntermediaire][colonneIntermediaire] != 0)
            {
                printf("Trajectoire bloquée.\n");
                return 0; // Déplacement invalide
            }
        }

        // Vérification terminée, le déplacement est valide
        return 1;
    }
    else
    {
        printf("La tour ne peut se déplacer qu'horizontalement ou verticalement.\n");
        return 0; // Déplacement invalide
    }
}

int main()
{
    int chessboard[SIZE][SIZE];

    // Initialisez l'échiquier vide
    initialiserchessboard(chessboard);

    // Placez les pièces sur le jeu
    chessboard[0][0] = -1; // Tour noire
    chessboard[0][7] = -1; // Tour noire
    chessboard[0][1] = -2; // Cheval noir
    chessboard[0][6] = -2; // Cheval noir
    chessboard[0][2] = -3; // Fou noir
    chessboard[0][5] = -3; // Fou noir
    chessboard[0][3] = -4; // Reine noire
    // chessboard[0][4] = -5; // Roi noir

    chessboard[7][0] = -1; // Tour blanche
    chessboard[7][7] = -1; // Tour blanche
    chessboard[7][1] = -2; // Cheval blanc
    chessboard[7][6] = -2; // Cheval blanc
    chessboard[7][2] = -3; // Fou blanc
    chessboard[7][5] = -3; // Fou blanc
    chessboard[7][3] = -4; // Reine blanche
    // chessboard[7][4] = -5; // Roi blanc

    // Affichez l'échiquier
    afficherchessboard(chessboard);

    return 0;
}
