#include <stdio.h>
#include <stdlib.h>  // Pour la fonction abs
#include <ctype.h>   // Pour la fonction toupper
#include <stdbool.h> // Pour utiliser le type bool
#include <conio.h>   // Pour Windows: getch()
#include <string.h>  // Pour les chaines de caractères
#include <time.h>    // Pour le random

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

// fonction de conversion en char pour sauvegarde
char piece_to_char(int piece)
{
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
    case 0:
    default:
        pieceChar = ' '; // Case vide
    }
    return pieceChar;
}

// Fonction d'ouverture du fichier de sauvegarde
int char_to_piece(char pieceChar)
{
    switch (pieceChar)
    {
    case 'r':
        return 1; // Tour blanche
    case 'n':
        return 2; // Cheval blanc
    case 'b':
        return 3; // Fou blanc
    case 'q':
        return 4; // Reine blanche
    case 'k':
        return 5; // Roi blanc
    case 'p':
        return 6; // Pion blanc
    case 'R':
        return -1; // Tour noire
    case 'N':
        return -2; // Cheval noir
    case 'B':
        return -3; // Fou noir
    case 'Q':
        return -4; // Reine noire
    case 'K':
        return -5; // Roi noir
    case 'P':
        return -6; // Pion noir
    case ' ':
    default:
        return 0; // Case vide
    }
}

// Fonction de sauvegarde
void save_game(int chessboard[SIZE][SIZE], char filename[])
{
    filename = strcat(filename, ".hess");
    FILE *save_file = fopen(filename, "w");

    if (save_file == NULL)
    {
        printf("Erreur lors de la creation du fichier de sauvegarde.\n");
        return;
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            fprintf(save_file, "%c", piece_to_char(chessboard[i][j])); // Utilisez une fonction pour convertir les pièces en caractères
        }
        fprintf(save_file, "\n");
    }

    fclose(save_file);
    printf("Jeu sauvegarde avec succes vers %s\n", filename);
}

// Fonction de chargement du fichier de sauvegarde
void load_game(int chessboard[SIZE][SIZE], char filename[])
{
    filename = strcat(filename, ".hess");
    FILE *save_file = fopen(filename, "r");

    if (save_file == NULL)
    {
        printf("Aucun fichier de sauvegarde nomme %s n'a ete trouve.\n", filename);
        return;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int piece = char_to_piece(fgetc(save_file)); // Utilisez une fonction pour convertir les caractères en pièces
            chessboard[i][j] = piece;
        }
        // Lire le caractère de fin de ligne pour passer à la ligne suivante
        fgetc(save_file);
    }

    fclose(save_file);
    printf("Jeu charge avec succes depuis %s\n", filename);
}

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
            printf("%c ", piece_to_char(piece));
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

void indices_to_chess(int indiceLigne, int indiceColonne, char *chessNotation)
{
    char colonneChar = 'A' + indiceColonne;
    int ligne = 8 - indiceLigne;
    sprintf(chessNotation, "%c%d", colonneChar, ligne);
}

// Fonction pour déplacer une pièce
void move_piece(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee)
{
    // Copier la pièce de la case de départ vers la case d'arrivée
    chessboard[ligneArrivee][colonneArrivee] = chessboard[ligneDepart][colonneDepart];

    // Mettre la case de départ à EMPTY
    chessboard[ligneDepart][colonneDepart] = EMPTY;
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
bool is_rook_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, bool playWithRobot)
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
                if (!playWithRobot)
                {
                    printf("Trajectoire de la tour bloquee.\n");
                }
                return false; // Déplacement invalide
            }
        }

        // Vérification terminée, le déplacement est valide
        return true;
    }
    else
    {
        if (!playWithRobot)
        {
            printf("La tour ne peut se deplacer qu'horizontalement ou verticalement.\n");
        }
        return false; // Déplacement invalide
    }
}

// Fonction pour vérifier si le cheval peut se déplacer
bool is_knight_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, bool playWithRobot)
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

    if (!playWithRobot)
    {
        printf("Le cheval ne peut se deplacer qu'en L.\n");
    }
    // Si aucune des conditions ci-dessus n'est satisfaite, le déplacement est invalide
    return false;
}

// Fonction pour vérifier si le fou peut se déplacer
bool is_bishop_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, bool playWithRobot)
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
                if (!playWithRobot)
                {
                    printf("Trajectoire du fou bloquee.\n");
                }
                return false; // Déplacement invalide
            }
        }

        // Vérification terminée, le déplacement est valide
        return true;
    }
    else
    {
        if (!playWithRobot)
        {
            printf("Le fou ne peut se deplacer qu'en diagonale.\n");
        }
        return false; // Déplacement invalide
    }
}

// Fonction pour vérifier si la reine peut se déplacer
bool is_queen_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, bool playWithRobot)
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
                if (!playWithRobot)
                {
                    printf("Trajectoire de la reine bloquee.\n");
                }
                return false; // Déplacement invalide
            }
        }

        // Vérification terminée, le déplacement est valide
        return true;
    }
    else
    {
        if (!playWithRobot)
        {
            printf("La reine ne peut se deplacer qu'horizontalement, verticalement ou en diagonale.\n");
        }
        return false; // Déplacement invalide
    }
}

// Fonction pour vérifier si le roi peut se déplacer
bool is_king_move_valid(int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, bool playWithRobot)
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
        if (!playWithRobot)
        {
            printf("Le roi ne peut se deplacer que d'une case horizontalement, verticalement ou en diagonale.\n");
        }
        return false; // Déplacement invalide
    }
}

// Fonction pour vérifier si le déplacement d'un pion est valide
bool is_pawn_move_valid(int chessboard[SIZE][SIZE], int ligneDepart, int colonneDepart, int ligneArrivee, int colonneArrivee, bool playWithRobot)
{
    // Récupérer la valeur de la pièce dans la case de départ
    int valeurPiece = chessboard[ligneDepart][colonneDepart];

    // Calculer la différence de lignes et de colonnes entre la case de départ et la case d'arrivée
    int deltaLigne = ligneArrivee - ligneDepart;
    int deltaColonne = colonneArrivee - colonneDepart;

    // Les pions blancs se déplacent vers le haut (+valeurPiece) et les noirs vers le bas (-valeurPiece)
    if (valeurPiece > 0)
    {
        if (chessboard[ligneArrivee][colonneArrivee] == EMPTY)
        {
            if (deltaLigne == -1 && deltaColonne == 0)
            {
                return true; // Déplacement d'une case vers le haut
            }
            else if (deltaLigne == -2 && deltaColonne == 0 && ligneDepart == 6)
            {
                // Déplacement initial de deux cases pour les pions blancs
                if (chessboard[ligneDepart - 1][colonneDepart] == EMPTY)
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
        if (chessboard[ligneArrivee][colonneArrivee] == EMPTY)
        {
            if (deltaLigne == 1 && deltaColonne == 0)
            {
                return true; // Déplacement d'une case vers le bas
            }
            else if (deltaLigne == 2 && deltaColonne == 0 && ligneDepart == 1)
            {
                // Déplacement initial de deux cases pour les pions noirs
                if (chessboard[ligneDepart + 1][colonneDepart] == EMPTY)
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

    if (!playWithRobot)
    {
        printf("Le pion ne peut se deplacer que d'une case vers l'avant ou en diagonale avant pour manger.\n");
    }

    return false; // Déplacement invalide par défaut
}

// Fonction pour vérifier si la partie d'échecs est terminée
bool is_game_over(int chessboard[SIZE][SIZE])
{
    bool whiteFound = false, blackFound = false;
    // Parcourez le tableau pour rechercher des pions blancs et noirs
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int piece = chessboard[i][j];
            if (piece > 0)
            {
                whiteFound = true; // Pion blanc trouvé
            }
            else if (piece < 0)
            {
                blackFound = true; // Pion noir trouvé
            }
        }
    }

    if (blackFound && !whiteFound)
    {
        display_chessboard(chessboard);
        printf("La partie est terminee. Les noirs ont gagne !\n");
        return true;
    }
    else if (whiteFound && !blackFound)
    {
        display_chessboard(chessboard);
        printf("La partie est terminee. Les blancs ont gagne !\n");
        return true;
    }

    // Si aucune des conditions de fin de partie n'est vérifiée, la partie n'est pas terminée
    return false;
}

// Vérifie si le déplacement est bon en fonction du type de piece
bool is_move_valid_by_piece(int chessboard[SIZE][SIZE], int indiceLigneDepart, int indiceColonneDepart, int indiceLigneArrivee, int indiceColonneArrivee, bool playWithRobot)
{
    // Vérifier si la pièce peut se déplacer vers la case d'arrivée
    bool deplacementValide = false;
    char *nomPiece = "";

    int pieceDepart = chessboard[indiceLigneDepart][indiceColonneDepart];

    // Vérifier le type de la pièce
    switch (abs(pieceDepart))
    {
    case ROOK:
        deplacementValide = is_rook_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee, playWithRobot);
        nomPiece = "Tour";
        break;
    case KNIGHT:
        deplacementValide = is_knight_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee, playWithRobot);
        nomPiece = "Cheval";
        break;
    case BISHOP:
        deplacementValide = is_bishop_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee, playWithRobot);
        nomPiece = "Fou";
        break;
    case QUEEN:
        deplacementValide = is_queen_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee, playWithRobot);
        nomPiece = "Reine";
        break;
    case KING:
        deplacementValide = is_king_move_valid(indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee, playWithRobot);
        nomPiece = "Roi";
        break;
    case PAWN:
        deplacementValide = is_pawn_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee, playWithRobot);
        nomPiece = "Pion";
        break;
    default:
        if (!playWithRobot)
        {
            printf("Piece invalide.\n");
        }
    }

    if (!deplacementValide)
    {
        if (!playWithRobot)
        {
            printf("Le deplacement ne respecte pas les mouvements autorises de la piece %s\n", nomPiece);
        }
        return false;
    }
    else
    {
        deplacementValide = is_move_valid(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee);

        if (!deplacementValide)
        {
            if (!playWithRobot)
            {
                printf("Vous ne pouvez pas deplacer cette piece vers cette case.\n");
            }

            return false;
        }
        else
        {
            if (playWithRobot)
            {
                // Convertir les indices en notation d'échecs
                char chessNotationDepart[3];
                indices_to_chess(indiceLigneDepart, indiceColonneDepart, chessNotationDepart);
                char chessNotationArrivee[3];
                indices_to_chess(indiceLigneArrivee, indiceColonneArrivee, chessNotationArrivee);

                printf("Le robot a deplace sa piece %s de %s vers %s.\n", nomPiece, chessNotationDepart, chessNotationArrivee);
            }
            return true;
        }
    }
}

// Demande à l'utilisateur case départ et case arrivée
bool ask_move(int chessboard[SIZE][SIZE], bool tourBlancs, int *indiceLigneDepart, int *indiceColonneDepart, int *indiceLigneArrivee, int *indiceColonneArrivee)
{
    // Demander au joueur de saisir les coordonnées de la case de départ
    char colonneDepart;
    int ligneDepart;
    printf("Entrez les coordonnees de la case de depart sans virgule (colonne, ligne) : ");
    scanf(" %c%d", &colonneDepart, &ligneDepart);

    // Convertir les coordonnées d'échecs en indices de ligne et de colonne
    int indiceLigneDepartVal = *indiceLigneDepart, indiceColonneDepartVal = *indiceColonneDepart;
    chess_to_indices(colonneDepart, ligneDepart, &indiceLigneDepartVal, &indiceColonneDepartVal);

    // Vérifier si les coordonnées de départ sont valides
    if (indiceLigneDepartVal == -1 || indiceColonneDepartVal == -1)
    {
        printf("Coordonnees de depart invalides.\n");
        return false;
    }

    // Vérifier si la case de départ contient une pièce de la bonne couleur
    int pieceDepart = chessboard[indiceLigneDepartVal][indiceColonneDepartVal];
    if ((tourBlancs && pieceDepart < 0) || (!tourBlancs && pieceDepart > 0))
    {
        printf("La case de depart ne contient pas une piece de votre couleur.\n");
        return false;
    }
    else if (pieceDepart == 0)
    {
        printf("Veuillez choisir une piece a deplacer.\n");
        return false;
    }

    // Demander au joueur de saisir les coordonnées de la case d'arrivée
    char colonneArrivee;
    int ligneArrivee;
    printf("Entrez les coordonnees de la case d'arrivee sans virgule (colonne, ligne) : ");
    scanf(" %c%d", &colonneArrivee, &ligneArrivee);

    // Convertir les coordonnées d'échecs en indices de ligne et de colonne
    int indiceLigneArriveeVal = *indiceLigneArrivee, indiceColonneArriveeVal = *indiceColonneArrivee;
    chess_to_indices(colonneArrivee, ligneArrivee, &indiceLigneArriveeVal, &indiceColonneArriveeVal);

    // Vérifier si les coordonnées d'arrivée sont valides
    if (indiceLigneArriveeVal == -1 || indiceColonneArriveeVal == -1)
    {
        printf("Coordonnees d'arrivee invalides.\n");
        return false;
    }

    // Vérifier si la case d'arrivée contient une pièce de la même couleur
    int pieceArrivee = chessboard[indiceLigneArriveeVal][indiceColonneArriveeVal];
    if ((tourBlancs && pieceArrivee > 0) || (!tourBlancs && pieceArrivee < 0))
    {
        printf("La case d'arrivee contient une piece de votre couleur.\n");
        return false;
    }

    // Dans ask_move, à la fin de la fonction
    *indiceLigneDepart = indiceLigneDepartVal;
    *indiceColonneDepart = indiceColonneDepartVal;
    *indiceLigneArrivee = indiceLigneArriveeVal;
    *indiceColonneArrivee = indiceColonneArriveeVal;

    return true;
}

// Fonction pour générer un coup aléatoire pour le robot
bool generate_random_move(int chessboard[SIZE][SIZE], int *indiceLigneDepart, int *indiceColonneDepart, int *indiceLigneArrivee, int *indiceColonneArrivee)
{
    int ligne, colonne;
    int piece;
    bool piecetrouve = false;
    bool aMoveFound = false;
    int max_i = 1000;

    // Initialise le générateur de nombres aléatoires avec une graine basée sur l'horloge
    srand(time(NULL));

    // Trouver une pièce noire aléatoire
    for (int i1 = 0; i1 < max_i && !piecetrouve; i1++)
    {
        ligne = rand() % SIZE;
        colonne = rand() % SIZE;
        piece = chessboard[ligne][colonne];
        if (piece < 0)
        {
            piecetrouve = true;
            // Mise à jour des indices de départ
            *indiceLigneDepart = ligne;
            *indiceColonneDepart = colonne;

            // Générer aléatoirement des indices pour la case d'arrivée
            for (int i2 = 0; i2 < max_i && !aMoveFound; i2++)
            {
                ligne = rand() % SIZE;
                colonne = rand() % SIZE;
                // Mise à jour des indices d'arrivée
                *indiceLigneArrivee = ligne;
                *indiceColonneArrivee = colonne;
                if (is_move_valid_by_piece(chessboard, *indiceLigneDepart, *indiceColonneDepart, *indiceLigneArrivee, *indiceColonneArrivee, true))
                {
                    aMoveFound = true;
                    return true;
                }
            }
            piecetrouve = false;
        }
    }

    printf("Le robot n'a pas trouve de coup valide a jouer.\n");

    return false;
}

// Fonction pour proposer à l'utilisateur d'enregistrer la partie en appuyant sur Échap ou de continuer en appuyant sur n'importe quelle autre touche
bool save_game_prompt(int chessboard[SIZE][SIZE])
{
    printf("Appuyez sur Echap pour enregistrer la partie (ou n'importe quelle autre touche pour continuer)...\n");

    char key = getch();
    if (key == 27)
    {
        // Sauvegarde du jeu (à améliorer)
        printf("Voulez vous sauvegarder et quitter la partie ? (o/n): ");
        char c3;
        scanf(" %c", &c3);
        if (c3 == 'o' || c3 == 'O')
        {
            printf("Donnez un nom au fichier de sauvegarde: ");
            char filename[100]; // Allouez suffisamment d'espace pour le nom du fichier

            if (scanf("%99s", filename) == 1)
            { // Utilisez %99s pour éviter un dépassement de mémoire
                printf("Nom du fichier: %s.hess\n", filename);
                save_game(chessboard, filename);
                return true; // La partie est enregistrée
            }
            else
            {
                printf("Erreur lors de la saisie du nom de fichier.\n");
            }
        }
        else
        {
            printf("Partie non enregistree. Le jeu continue !\n");
            return false;
        }
    }

    // Si l'utilisateur appuie sur n'importe quelle autre touche, la partie continue
    return false;
}

int main()
{
    int chessboard[SIZE][SIZE];

    // Initialisez l'échiquier vide
    init_chessboard(chessboard);

    // Placez les pièces noires sur le jeu
    chessboard[0][2] = BLACK_ROOK;
    chessboard[0][3] = BLACK_QUEEN;
    chessboard[0][4] = BLACK_BISHOP;
    chessboard[0][5] = BLACK_KNIGHT;

    // Placez les pièces blanches sur le jeu
    chessboard[7][2] = WHITE_ROOK;
    chessboard[7][3] = WHITE_BISHOP;
    chessboard[7][4] = WHITE_QUEEN;
    chessboard[7][5] = WHITE_KNIGHT;

    bool tourBlancs = true; // Pour déterminer de quel côté commence la partie

    printf("\n\x1B[1mBienvenue dans le jeu d'echecs !\x1B[0m\n");
    printf("Vous pouvez quitter le jeu a tout moment en appuyant sur la touche \x1B[1mCTRL+C\x1B[0m.\n\n");

    // Chargement d'une partie (à améliorer)
    printf("Voulez-vous charger une partie ? (o/n): ");
    char c1;
    scanf("%c", &c1);
    if (c1 == 'o' || c1 == 'O')
    {
        printf("Donnez le nom du fichier de sauvegarde: ");
        char filename[100]; // Allouez suffisamment d'espace pour le nom du fichier

        if (scanf("%99s", filename) == 1)
        { // Utilisez %99s pour éviter un dépassement de mémoire
            printf("Nom du fichier: %s.hess\n", filename);
            load_game(chessboard, filename); // TODO enregistrer si c'est les blancs ou noir qui joue
        }
        else
        {
            printf("Erreur lors de la saisie du nom de fichier.\n");
        }
    }

    // Choix de jouer contre un robot (à améliorer)
    bool playWithRobot = false;
    printf("Voulez vous jouer contre un robot ? (o/n): ");
    char c2;
    scanf(" %c", &c2);
    if (c2 == 'o' || c2 == 'O')
    {
        playWithRobot = true;
    }

    bool continueGame = true;
    // Boucle principale du jeu
    while (!is_game_over(chessboard) && continueGame)
    {
        // Afficher l'état actuel de l'échiquier
        display_chessboard(chessboard);

        // Les coordonnées de départ et d'arrivée
        int indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee;
        if (tourBlancs)
        {
            printf("C'est au tour des blancs. (minuscule)\n");
        }
        else
        {
            printf("C'est au tour des noirs. (MAJUSCULE)\n");
        }

        if (!tourBlancs && playWithRobot)
        {
            printf("Le robot joue...\n");
            if (!generate_random_move(chessboard, &indiceLigneDepart, &indiceColonneDepart, &indiceLigneArrivee, &indiceColonneArrivee))
            {
                continue;
            }
        }
        else
        {
            // Proposez à l'utilisateur d'enregistrer la partie ou de continuer
            continueGame = !save_game_prompt(chessboard);
            if (!continueGame)
            {
                break;
            }

            // Demander au joueur de saisir les coordonnées
            if (!ask_move(chessboard, tourBlancs, &indiceLigneDepart, &indiceColonneDepart, &indiceLigneArrivee, &indiceColonneArrivee))
            {
                continue;
            }
            // Vérifier si le déplacement est possible (en fonction du type de pièce jouée)
            if (!is_move_valid_by_piece(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee, false))
            {
                continue;
            }
        }

        // Déplacer la pièce
        move_piece(chessboard, indiceLigneDepart, indiceColonneDepart, indiceLigneArrivee, indiceColonneArrivee);

        // Passer au tour suivant
        tourBlancs = !tourBlancs;
    }

    return 0;
}
