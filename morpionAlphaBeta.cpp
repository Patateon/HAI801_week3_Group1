#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

const int SIZE = 3;
const char EMPTY = '-';
const char COMPUTER = 'X';
const char HUMAN = 'O';
int nbVictoire = 0;
int nbDefaite = 0;
int nbNul = 0;

class Morpion {
public:
    void jouer(const char* nomFichier);
    
private:
    char plateau[SIZE][SIZE];
    int minimax(char joueur, int alpha, int beta);
    bool estPlein();
    bool estGagnant(char joueur);
    void afficherPlateau();
};

void Morpion::jouer(const char* nomFichier) {
    ifstream fichier(nomFichier);
    if (!fichier) {
        cerr << "Erreur: Impossible d'ouvrir le fichier." << endl;
        return;
    }

    vector<vector<char>> grilles;
    string ligne;
    while (getline(fichier, ligne)) {
        vector<char> grille;
        for (char c : ligne) {
            if (c != ' ')
                grille.push_back(c);
        }
        if (grille.size() == SIZE * SIZE)
            grilles.push_back(grille);
    }

    fichier.close();

    for (auto& grille : grilles) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                plateau[i][j] = grille[i * SIZE + j];
            }
        }

        afficherPlateau();

        int score = minimax(COMPUTER, INT_MIN, INT_MAX);

        if (score > 0){
            cout << "L'ordinateur a gagné !" << endl;
            nbDefaite +=1;
        }
        else if (score < 0){
            cout << "Le joueur humain a gagné !" << endl;
            nbVictoire ++;
        }
        else{
            cout << "Match nul !" << endl;
            nbNul++;
        }

        cout << endl;
    }
}

int Morpion::minimax(char joueur, int alpha, int beta) {
    if (estGagnant(COMPUTER)) return 1;
    if (estGagnant(HUMAN)) return -1;
    if (estPlein()) return 0;

    if (joueur == COMPUTER) {
        int meilleurScore = INT_MAX;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (plateau[i][j] == EMPTY) {
                    plateau[i][j] = COMPUTER;
                    int score = minimax(HUMAN, alpha, beta);
                    plateau[i][j] = EMPTY;
                    meilleurScore = min(meilleurScore, score);
                    alpha = min(alpha, meilleurScore);
                    if (beta <= alpha) break; // Coupure beta
                }
            }
        }
        return meilleurScore;
    } else {
        int pireScore = INT_MIN;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (plateau[i][j] == EMPTY) {
                    plateau[i][j] = HUMAN;
                    int score = minimax(COMPUTER, alpha, beta);
                    plateau[i][j] = EMPTY;
                    pireScore = max(pireScore, score);
                    beta = max(beta, pireScore);
                    if (beta <= alpha) break; // Coupure alpha
                }
            }
        }
        return pireScore;
    }
}


bool Morpion::estPlein() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (plateau[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}

bool Morpion::estGagnant(char joueur) {
    for (int i = 0; i < SIZE; ++i) {
        if (plateau[i][0] == joueur && plateau[i][1] == joueur && plateau[i][2] == joueur)
            return true;
        if (plateau[0][i] == joueur && plateau[1][i] == joueur && plateau[2][i] == joueur)
            return true;
    }
    if (plateau[0][0] == joueur && plateau[1][1] == joueur && plateau[2][2] == joueur)
        return true;
    if (plateau[0][2] == joueur && plateau[1][1] == joueur && plateau[2][0] == joueur)
        return true;
    return false;
}

void Morpion::afficherPlateau() {
    cout << "Plateau actuel :" << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << plateau[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    double time_spent = 0.0;
 
    clock_t begin = clock();
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <nom_fichier>" << endl;
        return 1;
    }
    // for(int i =0; i < 1000; i++){

    Morpion jeu;
    jeu.jouer(argv[1]);
    // }

    clock_t end = clock();
 
    // calcule le temps écoulé en trouvant la différence (end - begin) et
    // divisant la différence par CLOCKS_PER_SEC pour convertir en secondes
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds\n", time_spent);
    printf("Nombre victoires : %d \n", nbVictoire);
    printf("Nombre defaites : %d \n", nbDefaite);
    printf("Nombre nuls : %d \n", nbNul);
    return 0;

    
}
