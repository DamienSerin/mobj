#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include "Timer.h"
#include "GPL_2_text.h"

using namespace std;

namespace vector_bench{

    void backInsert(){
        Timer* t = new Timer();
        t->start();

        vector<string> vgpl;
        int i = 0;

        //Parcours du tableau de char et ajout à la fin du vecteur
        while(GPL_2_text[i] != NULL){
            //conversion de la chaine de char en string
            string s(GPL_2_text[i]);
            vgpl.push_back(s);
            i++;
        }
        cout << "Nombre d'éléments dans le vecteur: " << vgpl.size() << '\n' << endl;

        //Tri du vecteur
        sort(vgpl.begin(), vgpl.end());

        //Parcours du vecteur avec un iterateur
        for(vector<string>::iterator it=vgpl.begin(); it!=vgpl.end(); ++it)
            cout << *it << ' ';
        cout << '\n';

        t->stop();
        cout << "\n Vector - backInsert: " << *t << endl;
    }

    void frontInsert(){
        Timer* t = new Timer();
        t->start();

        vector<string> vgpl;
        int i = 0;

        //Parcours du tableau de char et ajout au début du vecteur
        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);
            //on insere la string au début du vecteur
            vgpl.insert(vgpl.begin(),s);
            i++;
        }
        cout << "Nombre d'éléments dans le vecteur: " << vgpl.size() << '\n' << endl;

        sort(vgpl.begin(), vgpl.end());

        for(vector<string>::iterator it=vgpl.begin(); it!=vgpl.end(); ++it)
            cout << *it << ' ';
        cout << '\n';

        t->stop();
        cout << "\n Vector - frontInsert: " << *t << endl;
    }

    void sortEachInsert(){
        Timer* t = new Timer();
        t->start();

        vector<string> vgpl;
        int i = 0;

        //insertion en fin de vecteur et tri pour chacun des mots
        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);
            vgpl.push_back(s);
            sort(vgpl.begin(), vgpl.end());
            i++;
        }
        cout << "Nombre d'éléments dans le vecteur: " << vgpl.size() << '\n' << endl;

        for(vector<string>::iterator it=vgpl.begin(); it!=vgpl.end(); ++it)
            cout << *it << ' ';
        cout << '\n';

        t->stop();
        cout << "\n Vector - sortEachInsert: " << *t << endl;
    }
}

namespace list_bench{

    void backInsert(){
        Timer* t = new Timer();
        t->start();

        list<string> lgpl;
        int i = 0;

        //insertion en fin de liste
        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);
            lgpl.push_back(s);
            i++;
        }
        cout << "Nombre  d'éléments dans la liste: " << lgpl.size() << '\n' << endl;

        //tri de la liste en utilisant la fonction sort() de la classe list
        lgpl.sort();

        //parcours de la liste avec un iterateur
        for(list<string>::iterator it=lgpl.begin(); it!=lgpl.end(); ++it)
            cout << *it << ' ';
        cout << '\n';

        t->stop();
        cout << "\n List - backInsert: " << *t << endl;
    }

    void frontInsert(){
        Timer* t = new Timer();
        t->start();

        list<string> lgpl;
        int i = 0;

        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);
            //insertion en début de liste
            lgpl.push_front(s);
            i++;
        }
        cout << "Nombre d'éléments dans la liste: " << lgpl.size() << '\n' << endl;

        lgpl.sort();

        for(list<string>::iterator it=lgpl.begin(); it!=lgpl.end(); ++it)
            cout << *it << ' ';
        cout << '\n';

        t->stop();
        cout << "\n List - frontInsert: " << *t << endl;
    }

    void sortEachInsert(){
        Timer* t = new Timer();
        t->start();

        list<string> lgpl;
        int i = 0;

        //insertion en tête puis tri de la liste pour chacun des mots
        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);
            lgpl.push_back(s);
            lgpl.sort();
            i++;
        }
        cout << "Nombre d'éléments dans la liste: " << lgpl.size() << '\n' << endl;

        for(list<string>::iterator it=lgpl.begin(); it!=lgpl.end(); ++it)
            cout << *it << ' ';
        cout << endl;

        t->stop();
        cout << "\n List - sortEachInsert: " << *t << endl;
    }
}

namespace map_bench {

    //Objet fonctionnel
    class CompareString {
    public:
        //fonction de tri
        bool operator()(const string& a, const string& b) const {
            //ordre lexicographique inverse
            return a > b;
        }
    };

    void mapGpl(){
        map<string, int, CompareString> mapOfGplWords;
        int i = 0;
        int numberOfWords = 0;

        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);

            //on test l'existence du mot dans la map
            //s'il existe on incrémente son compteur de 1
            //s'il n'existe pas il est inséré dans la map
            if(mapOfGplWords.insert(make_pair(s,1)).second == false)
                mapOfGplWords[s]+=1;

            i++;
        }
        cout << "Nombre d'éléments dans la map: " << mapOfGplWords.size() << '\n' << endl;

        map<string, int>::iterator it = mapOfGplWords.begin();
        while(it != mapOfGplWords.end()){
            cout<< it->first << ':' << it->second << ' ';
            numberOfWords+=it->second;
            it++;
        }
        cout << endl;
        cout << "\nNombre de mot dans le texte: "<< numberOfWords << endl;
    }
}

int main(){
    vector_bench::backInsert();
    cout << "\n\n" << endl;
    vector_bench::frontInsert();
    cout << "\n\n" << endl;
    vector_bench::sortEachInsert();
    cout << "\n\n" << endl;

    list_bench::backInsert();
    cout << "\n\n" << endl;
    list_bench::frontInsert();
    cout << "\n\n" << endl;
    list_bench::sortEachInsert();
    cout << "\n\n" << endl;

    map_bench::mapGpl();

    return 0;
}
