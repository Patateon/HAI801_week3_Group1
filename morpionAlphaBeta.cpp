#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

const int SIZE = 4;
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
            if (c != ' '){
                grille.push_back(c);
            }else{
                grille.push_back(EMPTY);
            }
        }
        if (grille.size() == SIZE * SIZE)
            grilles.push_back(grille);
        else{
            cout<<grille.size()<<", "<<SIZE*SIZE<<endl;
        }
    }

    fichier.close();

    cout<<"Start parsing..."<<endl;
    for (int k = 0; k < grilles.size(); k++){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                plateau[i][j] = grilles[k][i * SIZE + j];
            }
        }

    // cout<<"Start solving..."<<endl;

    int score = minimax(COMPUTER, INT_MIN, INT_MAX);

    // afficherPlateau();

    if (score > 0){
        // cout << "L'ordinateur a gagné !" << endl;
        nbVictoire++;
    }
    else if (score < 0){
        // cout << "Le joueur humain a gagné !" << endl;
        nbDefaite++;
    }
    else{
        // cout << "Match nul !" << endl;
        nbNul++;
    }

    // cout << endl;
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
        bool ligne = true;
        for (int j = 0; j < SIZE; j++){
            ligne = ligne && plateau[i][j] == joueur;
        }
        if (ligne)
            return true;

        bool colonne = true;
        for (int j = 0; j < SIZE; j++){
            colonne = colonne && plateau[j][i] == joueur;
        }
        if (colonne)
            return true;
    }

    bool diagonal = true;
    for (int j = 0; j < SIZE; j++){
        diagonal = diagonal && plateau[j][j] == joueur;
    }
    if (diagonal)
        return true;

    diagonal = true;
    for (int j = 0; j < SIZE; j++){
        diagonal = diagonal && plateau[j][SIZE-1-j] == joueur;
    }
    if (diagonal)
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
