#include<iostream>
#include<fstream>
#include<vector>
using namespace std;





double calcule_similetude(vector<int>a,vector<int>b){
    int i=0,j=0;
    double somme=0.0;
    double norme_a=0.0;
    double norme_b=0.0;
    while (i < a.size() && j < b.size()) {
        somme += a[i] * b[j];
        norme_a += a[i] * a[i];
        norme_b += b[j] * b[j];
    }
    norme_a = sqrt(norme_a);
    norme_b = sqrt(norme_b);

    if (norme_a==0||norme_b==0)
    {
        return 0;
    }
    
    return (somme / (norme_a * norme_b));
}

int main(){
    ifstream FichierA("fichier1.txt");
    ifstream FichierB("fichier2.txt");

    if (!fichierA.is_open() || !fichierB.is_open()) {
        cerr << "Erreur lors de l'ouverture des fichiers." << std::endl;
        return 1;
    }

    
}