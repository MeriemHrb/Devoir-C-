#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

// Fonction pour convertir une liste de mots en vecteur de hachage
vector<int> motsVersHachage(const vector<string>& mots, const unordered_map<string, int>& dictionnaire) {
    vector<int> hachage(dictionnaire.size(), 0);

    for (size_t i = 0; i < mots.size(); ++i) {
        const string& mot = mots[i];
        if (dictionnaire.find(mot) != dictionnaire.end()) {
            hachage[dictionnaire.at(mot)]++;
        }
    }

    return hachage;
}


// Fonction pour construire un dictionnaire de mots avec des identifiants numériques
unordered_map<string, int> construireDictionnaire(const vector<vector<string> >& fichiers) {
    unordered_map<string, int> dictionnaire;
    int identifiant = 0;

    for (size_t i = 0; i < fichiers.size(); ++i) {
        const vector<string>& fichier = fichiers[i];
        for (size_t j = 0; j < fichier.size(); ++j) {
            const string& mot = fichier[j];
            if (dictionnaire.find(mot) == dictionnaire.end()) {
                dictionnaire[mot] = identifiant++;
            }
        }
    }

    return dictionnaire;
}
// Fonction pour calculer la similarité cosinus
double calcule_similetude(const vector<int>& a, const vector<int>& b) {
    double produit_scalaire = 0.0;
    double norme_a = 0.0;
    double norme_b = 0.0;

    for (size_t i = 0; i < a.size(); ++i) {
        produit_scalaire += a[i] * b[i];
        norme_a += a[i] * a[i];
        norme_b += b[i] * b[i];
    }

    norme_a = sqrt(norme_a);
    norme_b = sqrt(norme_b);

    if (norme_a == 0 || norme_b == 0) {
        // Éviter une division par zéro
        return 0.0;
    }

    return produit_scalaire / (norme_a * norme_b);
}



int main() {
    // Lire le contenu des fichiers A et B
    ifstream fichierA("fichier1.txt");
    ifstream fichierB("fichier2.txt");

    if (!fichierA.is_open() || !fichierB.is_open()) {
        cerr << "Erreur lors de l'ouverture des fichiers." << endl;
        return 1;
    }

    // Lire le contenu des fichiers en tant que listes de mots
    vector<string> mots_A, mots_B;
    string mot;

    // Lire le fichier A
    while (fichierA >> mot) {
        mots_A.push_back(mot);
    }

    // Lire le fichier B
    while (fichierB >> mot) {
        mots_B.push_back(mot);
    }

    // Construire un dictionnaire de mots avec des identifiants numériques
    vector<vector<string> > fichiers;
    fichiers.push_back(mots_A);
    fichiers.push_back(mots_B);
    unordered_map<string, int> dictionnaire = construireDictionnaire(fichiers);

    // Convertir les listes de mots en vecteurs de hachage
    vector<int> hachage_A = motsVersHachage(mots_A, dictionnaire);
    vector<int> hachage_B = motsVersHachage(mots_B, dictionnaire);

    // Calcul de la similarité cosinus
    double similarite = calcule_similetude(hachage_A, hachage_B);

    cout << "Similarite Cosinus entre A et B : " << similarite << endl;

    return 0;
}
