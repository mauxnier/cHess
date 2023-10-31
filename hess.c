#include <stdio.h>
#include <stdlib.h>  // Pour la fonction abs
#include <ctype.h>   // Pour la fonction toupper
#include <stdbool.h> // Pour utiliser le type bool
#include <conio.h>   // Pour Windows: getch()

// Taille de l'échiquier (8x8)
#define SIZE 8

enum Pieces
{
    EMPTY = 0,
    // Pièces de bases
    ROOK = 1,
    KNIGHT = 2,
    BISHOP = 3,
    QUEEN = 4,
    KING = 5,
    PAWN = 6,
    // Pièces blanches
    WHITE_ROOK = 1,
    WHITE_KNIGHT = 2,
    WHITE_BISHOP = 3,
    WHITE_QUEEN = 4,
    WHITE_KING = 5,
    WHITE_PAWN = 6,
    // Pièces noires
    BLACK_ROOK = -1,
    BLACK_KNIGHT = -2,
    BLACK_BISHOP = -3,
    BLACK_QUEEN = -4,
    BLACK_KING = -5,
    BLACK_PAWN = -6
};

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

// Fonction pour afficher l'échiquier de manière plus visuelle
void display_chessboard(int chessboard[8][8])
{
    printf("\n---------------------------\n|   / A B C D E F G H \\   |\n"); // Indices de colonnes
    printf("|   |-----------------|   |\n");

    for (int i = 0; i < 8; i++)
    {
        printf("| %d | ", 8 - i); // Indices de lignes

        for (int j = 0; j < 8; j++)
        {
            int piece = chessboard[i][j];

            // Utiliser des caractères pour représenter les pièces
            char pieceChar;

            switch (piece)
            {
            case 1:
                pieceChar = 'r'; // Tour blanche
                break;
            case 2:
                pieceChar = 'n'; // Cheval blanc
                break;
            case 3:
                pieceChar = 'b'; // Fou blanc
                break;
            case 4:
                pieceChar = 'q'; // Reine blanche
                break;
            case 5:
                pieceChar = 'k'; // Roi blanc
                break;
            case 6:
                pieceChar = 'p'; // Pion blanc
                break;
            case -1:
                pieceChar = 'R'; // Tour noire
                break;
            case -2:
                pieceChar = 'N'; // Cheval noir
                break;
            case -3:
                pieceChar = 'B'; // Fou noir
                break;
            case -4:
                pieceChar = 'Q'; // Reine noire
                break;
            case -5:
                pieceChar = 'K'; // Roi noir
                break;
            case -6:
                pieceChar = 'P'; // Pion noir
                break;
            default:
                pieceChar = ' '; // Case vide
            }

            printf("%c ", pieceChar);
        }
        printf("| %d |\n", 8 - i); // Indices de lignes
    }
    printf("|   |-----------------|   |\n");
    printf("|   \\ A B C D E F G H /   |\n---------------------------\n\n"); // Indices de colonnes
}

// Fonction pour convertir la notation d'échecs en indices de ligne et de colonne
void chess_to_indices(char colonne, int ligne, int *indiceLigne, int *indiceColonne)
{
    // Assurez-vous que la lettre de la colonne est en majuscule
    colonne = toupper(colonne);

    // Vérifiez que les coordonnées sont valides
    if (colonne < 'A' || colonne > 'H' || ligne < 1 || ligne > 8)
    {
        // printf("%c / %d", colonne, ligne);
        printf("Coordonnees du plateau invalides.\n");
        *indiceLigne = -1;
        *indiceColonne = -1;
        return;
    }

    // Convertissez la lettre de la colonne en un indice de 0 à 7
    *indiceColonne = colonne - 'A';

    // Convertissez le numéro de ligne en un indice de 0 à 7
    *indiceLigne = 8 - ligne;
}

// Fonction pour vérifier si une pièce peut être déplacée vers une case d'arrivée
bool is_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee)
{
    // Vérifier si les coordonnées de départ et d'arrivée sont valides
    if (ligneDepart < 0 || ligneDepart >= SIZE || colonneDepart < 0 || colonneDepart >= SIZE ||
        ligneArrivee < 0 || ligneArrivee >= SIZE || colonneArrivee < 0 || colonneArrivee >= SIZE)
    {
        return false; // Déplacement invalide
    }

    int pieceDepart = chessboard[ligneDepart][colonneDepart];
    int pieceArrivee = chessboard[ligneArrivee][colonneArrivee];

    // Vérifier si les pièces sont de la même couleur (positives ou négatives)
    if ((pieceDepart > 0 && pieceArrivee > 0) || (pieceDepart < 0 && pieceArrivee < 0))
    {
        return false; // Déplacement invalide (même famille)
    }

    return true; // Déplacement valide par défaut
}

// Fonction pour vérifier si la tour peut se déplacer
bool is_rook_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee)
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
                printf("Trajectoire de la tour bloquee.\n");
                return false; // Déplacement invalide
            }
        }

        // Vérification terminée, le déplacement est valide
        return true;
    }
    else
    {
        printf("La tour ne peut se deplacer qu'horizontalement ou verticalement.\n");
        return false; // Déplacement invalide
    }
}

// Fonction pour vérifier si le cheval peut se déplacer
bool is_knight_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee)
{
    // Vérifier si le déplacement du cheval est valide
    int deltaLigne = abs(ligneArrivee - ligneDepart);
    int deltaColonne = abs(colonneArrivee - colonneDepart);

    // Le cheval se déplace en "L" : 2 cases dans une direction et 1 case dans une direction perpendiculaire
    if ((deltaLigne == 2 && deltaColonne == 1) || (deltaLigne == 1 && deltaColonne == 2))
    {
        // Vérifier que la case d'arrivée est libre ou contient une pièce ennemie
        if (chessboard[ligneArrivee][colonneArrivee] <= 0)
        {
            // Le déplacement est valide
            return true;
        }
    }

    printf("Le cheval ne peut se deplacer qu'en L.\n");
    // Si aucune des conditions ci-dessus n'est satisfaite, le déplacement est invalide
    return false;
}

// Fonction pour vérifier si le fou peut se déplacer
bool is_bishop_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee)
{
    // Vérifier si le déplacement du fou est diagonal
    int deltaLigne = abs(ligneArrivee - ligneDepart);
    int deltaColonne = abs(colonneArrivee - colonneDepart);

    if (deltaLigne == deltaColonne)
    {
        int pasLigne = (ligneArrivee > ligneDepart) ? 1 : -1;
        int pasColonne = (colonneArrivee > colonneDepart) ? 1 : -1;

        // Vérifier que la trajectoire est libre
        for (int i = 1; i < deltaLigne; i++)
        {
            int ligneIntermediaire = ligneDepart + i * pasLigne;
            int colonneIntermediaire = colonneDepart + i * pasColonne;
            if (chessboard[ligneIntermediaire][colonneIntermediaire] != 0)
            {
                printf("Trajectoire du fou bloquee.\n");
                return false; // Déplacement invalide
            }
        }

        // Vérification terminée, le déplacement est valide
        return true;
    }
    else
    {
        printf("Le fou ne peut se deplacer qu'en diagonale.\n");
        return false; // Déplacement invalide
    }
}

// Fonction pour vérifier si la reine peut se déplacer
bool is_queen_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee)
{
    // Vérifier si la reine se déplace horizontalement, verticalement ou en diagonale
    int deltaLigne = abs(ligneArrivee - ligneDepart);
    int deltaColonne = abs(colonneArrivee - colonneDepart);

    if (ligneDepart == ligneArrivee || colonneDepart == colonneArrivee || deltaLigne == deltaColonne)
    {
        int pasLigne = (ligneDepart == ligneArrivee) ? 0 : (ligneArrivee > ligneDepart) ? 1
                                                                                        : -1;
        int pasColonne = (colonneDepart == colonneArrivee) ? 0 : (colonneArrivee > colonneDepart) ? 1
                                                                                                  : -1;

        // Vérifier que la trajectoire est libre
        for (int i = 1; i < deltaLigne + deltaColonne; i++)
        {
            int ligneIntermediaire = ligneDepart + i * pasLigne;
            int colonneIntermediaire = colonneDepart + i * pasColonne;
            if (chessboard[ligneIntermediaire][colonneIntermediaire] != 0)
            {
                printf("Trajectoire de la reine bloquee.\n");
                return false; // Déplacement invalide
            }
        }

        // Vérification terminée, le déplacement est valide
        return true;
    }
    else
    {
        printf("La reine ne peut se deplacer qu'horizontalement, verticalement ou en diagonale.\n");
        return false; // Déplacement invalide
    }
}

// Fonction pour vérifier si le roi peut se déplacer
bool is_king_move_valid(int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee)
{
    // Vérifier si le roi se déplace horizontalement, verticalement ou en diagonale
    int deltaLigne = abs(ligneArrivee - ligneDepart);
    int deltaColonne = abs(colonneArrivee - colonneDepart);

    if ((deltaLigne <= 1 && deltaColonne <= 1))
    {
        // Vérification terminée, le déplacement est valide
        return true;
    }
    else
    {
        printf("Le roi ne peut se deplacer que d'une case horizontalement, verticalement ou en diagonale.\n");
        return false; // Déplacement invalide
    }
}

// Fonction pour vérifier si le déplacement d'un pion est valide
bool is_pawn_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee)
{
    // Récupérer la valeur de la pièce dans la case de départ
    int valeurPiece = chessboard[ligneDepart][colonneDepart];

    // Calculer la différence de lignes et de colonnes entre la case de départ et la case d'arrivée
    int deltaLigne = ligneArrivee - ligneDepart;
    int deltaColonne = colonneArrivee - colonneDepart;

    printf("deltaLigne = %d, deltaColonne = %d\n", deltaLigne, deltaColonne);
    printf("ligneDepart = %d, colonneDepart = %d\n", ligneDepart, colonneDepart);
    printf("ligneArrivee = %d, colonneArrivee = %d\n", ligneArrivee, colonneArrivee);

    // Les pions blancs se déplacent vers le haut (+valeurPiece) et les noirs vers le bas (-valeurPiece)
    if (valeurPiece > 0)
    {
        if (chessboard[ligneArrivee][colonneArrivee] == 0)
        {
            if (deltaLigne == -1 && deltaColonne == 0)
            {
                return true; // Déplacement d'une case vers le haut
            }
            else if (deltaLigne == -2 && deltaColonne == 0 && ligneDepart == 6)
            {
                // Déplacement initial de deux cases pour les pions blancs
                if (chessboard[ligneDepart - 1][colonneDepart] == 0)
                {
                    return true; // Déplacement valide
                }
            }
        }
        else if (chessboard[ligneArrivee][colonneArrivee] < 0 && deltaLigne == -1 && abs(deltaColonne) == 1)
        {
            return true; // Prise en diagonale d'une pièce noire
        }
    }
    else if (valeurPiece < 0)
    {
        if (chessboard[ligneArrivee][colonneArrivee] == 0)
        {
            if (deltaLigne == 1 && deltaColonne == 0)
            {
                return true; // Déplacement d'une case vers le bas
            }
            else if (deltaLigne == 2 && deltaColonne == 0 && ligneDepart == 1)
            {
                // Déplacement initial de deux cases pour les pions noirs
                if (chessboard[ligneDepart + 1][colonneDepart] == 0)
                {
                    return true; // Déplacement valide
                }
            }
        }
        else if (chessboard[ligneArrivee][colonneArrivee] > 0 && deltaLigne == 1 && abs(deltaColonne) == 1)
        {
            return true; // Prise en diagonale d'une pièce blanche
        }
    }

    return false; // Déplacement invalide par défaut
}

// Fonction pour vérifier si la partie d'échecs est terminée
bool is_game_over(int chessboard[SIZE][SIZE])
{
    // Recherchez des conditions de fin de partie ici
    // Par exemple, vérifiez si le roi d'une des deux couleurs a été mis en échec et mat,
    // ou si la partie est terminée par un pat (stalemate), un échec perpétuel, etc.
    // Implémentez ces vérifications en fonction des règles de votre jeu d'échecs.

    // Exemple simplifié : La partie est terminée si l'un des rois est absent
    bool roiBlancTrouve = false;
    bool roiNoirTrouve = false;

    for (int ligne = 0; ligne < SIZE; ligne++)
    {
        for (int colonne = 0; colonne < SIZE; colonne++)
        {
            int piece = chessboard[ligne][colonne];
            if (piece == WHITE_KING)
            {
                roiBlancTrouve = true;
            }
            else if (piece == BLACK_KING)
            {
                roiNoirTrouve = true;
            }
        }
    }

    if (!roiBlancTrouve)
    {
        printf("La partie est terminee. Les noirs ont gagne !\n");
        return true;
    }
    else if (!roiNoirTrouve)
    {
        printf("La partie est terminee. Les blancs ont gagne !\n");
        return true;
    }

    // Si aucune des conditions de fin de partie n'est vérifiée, la partie n'est pas terminée
    return false;
}

// Fonction pour déplacer une pièce
void move_piece(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee)
{
    // Copier la pièce de la case de départ vers la case d'arrivée
    chessboard[ligneArrivee][colonneArrivee] = chessboard[ligneDepart][colonneDepart];

    // Mettre la case de départ à EMPTY
    chessboard[ligneDepart][colonneDepart] = EMPTY;
}

int main()
{
    int chessboard[SIZE][SIZE];

    // Initialisez l'échiquier vide
    init_chessboard(chessboard);

    // Placez les pièces noires sur le jeu
    chessboard[0][0] = BLACK_ROOK;
    chessboard[0][7] = BLACK_ROOK;
    chessboard[0][1] = BLACK_KNIGHT;
    chessboard[0][6] = BLACK_KNIGHT;
    chessboard[0][2] = BLACK_BISHOP;
    chessboard[0][5] = BLACK_BISHOP;
    chessboard[0][3] = BLACK_QUEEN;
    chessboard[0][4] = BLACK_KING;
    for (int i = 0; i < SIZE; i++)
    {
        chessboard[1][i] = BLACK_PAWN;
    }

    // Placez les pièces blanches sur le jeu
    chessboard[7][0] = WHITE_ROOK;
    chessboard[7][7] = WHITE_ROOK;
    chessboard[7][1] = WHITE_KNIGHT;
    chessboard[7][6] = WHITE_KNIGHT;
    chessboard[7][2] = WHITE_BISHOP;
    chessboard[7][5] = WHITE_BISHOP;
    chessboard[7][3] = WHITE_QUEEN;
    chessboard[7][4] = WHITE_KING;
    for (int i = 0; i < SIZE; i++)
    {
        chessboard[6][i] = WHITE_PAWN;
    }

    bool tourBlancs = true; // Pour déterminer de quel côté commence la partie

    printf("\n\x1B[1mBienvenue dans le jeu d'echecs !\x1B[0m\n");
    printf("Vous pouvez quitter le jeu a tout moment en appuyant sur la touche \x1B[1mCTRL+C\x1B[0m.\n\n");

    // Boucle principale du jeu
    while (!is_game_over(chessboard))
    {
        // Afficher l'état actuel de l'échiquier
        display_chessboard(chessboard);

        if (tourBlancs)
        {
            printf("C'est au tour des blancs. (minuscule)\n");
        }
        else
        {
            printf("C'est au tour des noirs. (MAJUSCULE)\n");
        }

        // Demander au joueur de saisir les coordonnées de la case de départ
        char colonneDepart;
        int ligneDepart;
        printf("Entrez les coordonnees de la case de depart sans virgule (colonne, ligne) : ");
        scanf(" %c%d", &colonneDepart, &ligneDepart);

        // Convertir les coordonnées d'échecs en indices de ligne et de colonne
        int indiceLigneDepart, indiceColonneDepart;
        chess_to_indices(colonneDepart, ligneDepart, &indiceLigneDepart, &indiceColonneDepart);

        // Vérifier si les coordonnées de départ sont valides
        if (indiceLigneDepart == -1 || indiceColonneDepart == -1)
        {
            printf("Coordonnees de depart invalides.\n");
            continue;
        }

        // Vérifier si la case de départ contient une pièce de la bonne couleur
        int pieceDepart = chessboard[indiceLigneDepart][indiceColonneDepart];
        if ((tourBlancs && pieceDepart < 0) || (!tourBlancs && pieceDepart > 0))
        {
            printf("La case de depart ne contient pas une piece de votre couleur.\n");
            continue;
        }
        else if (pieceDepart == 0)
        {
            printf("Veuillez choisir une piece a deplacer.\n");
            continue;
        }

        // Demander au joueur de saisir les coordonnées de la case d'arrivée
        char colonneArrivee;
        int ligneArrivee;
        printf("Entrez les coordonnees de la case d'arrivee sans virgule (colonne, ligne) : ");
        scanf(" %c%d", &colonneArrivee, &ligneArrivee);

        // Convertir les coordonnées d'échecs en indices de ligne et de colonne
        int indiceLigneArrivee, indiceColonneArrivee;
        chess_to_indices(colonneArrivee, ligneArrivee, &indiceLigneArrivee, &indiceColonneArrivee);

        // Vérifier si les coordonnées d'arrivée sont valides
        if (indiceLigneArrivee == -1 || indiceColonneArrivee == -1)
        {
            printf("Coordonnees d'arrivee invalides.\n");
            continue;
        }

        // Vérifier si la case d'arrivée contient une pièce de la même couleur
        int pieceArrivee = chessboard[indiceLigneArrivee][indiceColonneArrivee];
        if ((tourBlancs && pieceArrivee > 0) || (!tourBlancs && pieceArrivee < 0))
        {
            printf("La case d'arrivee contient une piece de votre couleur.\n");
            continue;
        }

        // Vérifier si la pièce peut se déplacer vers la case d'arrivée
        bool deplacementValide = false;
        char *nomPiece = "";

        // Vérifier le type de la pièce
        switch (abs(pieceDepart))
        {
        case ROOK:
            deplacementValide = is_rook_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee);
            nomPiece = "Tour";
            break;
        case KNIGHT:
            deplacementValide = is_knight_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee);
            nomPiece = "Cheval";
            break;
        case BISHOP:
            deplacementValide = is_bishop_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee);
            nomPiece = "Fou";
            break;
        case QUEEN:
            deplacementValide = is_queen_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee);
            nomPiece = "Reine";
            break;
        case KING:
            deplacementValide = is_king_move_valid(indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee);
            nomPiece = "Roi";
            break;
        case PAWN:
            deplacementValide = is_pawn_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee);
            nomPiece = "Pion";
            break;
        default:
            printf("Piece invalide.\n");
            continue;
        }

        if (!deplacementValide)
        {
            printf("Le deplacement ne respecte pas les mouvements autorises de la piece %s\n", nomPiece);
            continue;
        }

        deplacementValide = is_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee);

        if (!deplacementValide)
        {
            printf("Vous ne pouvez pas deplacer cette piece vers cette case.\n");
            continue;
        }

        // Déplacer la pièce
        move_piece(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee);

        // Passer au tour suivant
        tourBlancs = !tourBlancs;

        printf("\n");
    }

    return 0;
}
