#include<iostream>
#include<string>
#include<fstream>
using namespace std;
ifstream fin("in.txt");
/*
    4
    S->BA
    A->a|BA|CA
    B->b|AA|AB
    C->c|BC|BB
    baabca
*/

string productie, productii[100][100], matrice[100][100], input, caracter;
string  neterminal_start, combinatie, rezultat_concatenare;
int numar_neterminale, index1, index2;


string concatenare(string a, string b) { //concatenarea neterminalilor
    string rezultat=a;
    for(int i = 0; i < b.length(); i++) {
        if (rezultat.find(b[i]) > rezultat.length())
            rezultat += b[i];
    }
    return rezultat;
}

string combinatii(string a, string b){ //toate combinatiile dintre a si b
    string productie_noua = "", rezultat = "";
    for(int i = 0; i < a.length(); i++)
        for(int j = 0; j < b.length(); j++) {
            productie_noua = productie_noua + a[i] + b[j];
            for(int l = 0; l < numar_neterminale; l++) { //caut in matricea cu productiile daca este generata de vreun neterminal productia noua
                int k = 1;
                while(productii[l][k] != "") {
                    if(productii[l][k] == productie_noua) {
                        rezultat = concatenare(rezultat, productii[l][0]); //retin neterminalele care genereaza productia respectiva
                    }
                    k++;
                }
            }
            productie_noua = "";
        }
    return rezultat;
}

int main() {
    fin >> numar_neterminale;
    for(int i=0; i<numar_neterminale; i++) {
        fin>>productie;
        index1 = productie.find("->"); //indexul la care gasesc simbolul ->
        productii[i][0] = productie.substr(0, index1);
        if(i==0) {
            neterminal_start=productie.substr(0, index1); //memorez primul neterminal introdus
        }
        productie = productie.substr(index1 + 2, productie.length());
        int j=1; //incep de la 1 pentru ca pe pozitia 0 am neterminalul
        while(productie.length() != 0) {
            index2 = productie.find("|");
            if (index2 > productie.length()) {
                productii[i][j] = productie;
                productie = "";
            }
            else {
                productii[i][j] = productie.substr(0, index2);
                productie = productie.substr(index2 + 1, productie.length());
            }
            j++;
        }
    }
    fin >> input;
    for(int i = 0; i < input.length(); i++) { //completez diagonala principala a matricei
        rezultat_concatenare = "";
        caracter = input[i];
        for(int j = 0; j < numar_neterminale; j++) {
            for(int k = 1; productii[j][k] != ""; k++) {
                if(productii[j][k] == caracter){
                    rezultat_concatenare = concatenare(rezultat_concatenare, productii[j][0]); //iau toate neterminalele care duc in terminalul curent
                }
            }
        }
        matrice[i][i] = rezultat_concatenare;
    }
    for(int i = 1; i < input.length(); i++) { //completez partea de deasupra diagonalei principale a matricei
        for(int j = i; j < input.length(); j++) {
            rezultat_concatenare = "";
            for(int k = j - i; k < j; k++) {
                combinatie = combinatii(matrice[j - i][k], matrice[k + 1][j]);
                rezultat_concatenare = concatenare(rezultat_concatenare, combinatie);
            }
            matrice[j - i][j] = rezultat_concatenare;
        }
    }
    if(matrice[0][input.length() - 1].find(neterminal_start) != string::npos) //verific daca in coltul din dreapta sus se gaseste neterminalul de start
        cout << "Face parte din limbaj!";
    else
        cout << "Nu face parte din limbaj. :(";
    fin.close();
    return 0;
}