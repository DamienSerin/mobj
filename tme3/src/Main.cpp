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

        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);
            vgpl.push_back(s);
            i++;
        }

        cout << "Nb éléments dans le vecteur: " << vgpl.size() << '\n' << endl;

        sort(vgpl.begin(), vgpl.end());

        for(vector<string>::iterator it=vgpl.begin(); it!=vgpl.end(); ++it)
            cout << *it << ' ';
        cout << '\n';

        t->stop();
        cout << '\n' << *t << endl;
    }

    void frontInsert(){
        Timer* t = new Timer();

        t->start();
        vector<string> vgpl;
        int i = 0;

        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);
            vgpl.insert(vgpl.begin(),s);
            i++;
        }

        cout << "Nb éléments dans le vecteur: " << vgpl.size() << '\n' << endl;

        sort(vgpl.begin(), vgpl.end());

        for(vector<string>::iterator it=vgpl.begin(); it!=vgpl.end(); ++it)
            cout << *it << ' ';
        cout << '\n';

        t->stop();
        cout << '\n' << *t << endl;
    }

    void sortEachInsert(){
        Timer* t = new Timer();

        t->start();
        vector<string> vgpl;
        int i = 0;

        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);
            vgpl.push_back(s);
            sort(vgpl.begin(), vgpl.end());
            i++;
        }

        cout << "Nb éléments dans le vecteur: " << vgpl.size() << '\n' << endl;

        for(vector<string>::iterator it=vgpl.begin(); it!=vgpl.end(); ++it)
            cout << *it << ' ';
        cout << '\n';

        t->stop();
        cout << '\n' << *t << endl;
    }
}

namespace list_bench{
    void backInsert(){
        Timer* t = new Timer();

        t->start();
        list<string> lgpl;
        int i = 0;

        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);
            lgpl.push_back(s);
            i++;
        }

        cout << "Nb éléments dans la liste: " << lgpl.size() << '\n' << endl;

        lgpl.sort();

        for(list<string>::iterator it=lgpl.begin(); it!=lgpl.end(); ++it)
            cout << *it << ' ';
        cout << '\n';

        t->stop();
        cout << '\n' << *t << endl;
    }

    void frontInsert(){
        Timer* t = new Timer();

        t->start();
        list<string> lgpl;
        int i = 0;

        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);
            lgpl.push_front(s);
            i++;
        }

        cout << "Nb éléments dans la liste: " << lgpl.size() << '\n' << endl;

        lgpl.sort();

        for(list<string>::iterator it=lgpl.begin(); it!=lgpl.end(); ++it)
            cout << *it << ' ';
        cout << '\n';

        t->stop();
        cout << '\n' << *t << endl;
    }

    void sortEachInsert(){
        Timer* t = new Timer();

        t->start();
        list<string> lgpl;
        int i = 0;

        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);
            lgpl.push_back(s);
            lgpl.sort();
            i++;
        }

        cout << "Nb éléments dans la liste: " << lgpl.size() << '\n' << endl;

        for(list<string>::iterator it=lgpl.begin(); it!=lgpl.end(); ++it)
            cout << *it << ' ';
        cout << endl;

        t->stop();
        cout << '\n' << *t << endl;
    }
}

namespace map_bench {

    class CompareString {
    public:
        bool operator()(const string& a, const string& b) const {
            return a > b;
        }
    };

    void mapGpl(){
        map<string, int, CompareString> mapOfGplWords;
        int i = 0;
        int numberOfWords = 0;

        while(GPL_2_text[i] != NULL){
            string s(GPL_2_text[i]);

            if(mapOfGplWords.insert(make_pair(s,1)).second == false)
                mapOfGplWords[s]+=1;

            i++;
        }

        cout << "Nb éléments dans la map: " << mapOfGplWords.size() << '\n' << endl;

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
    //vector_bench::backInsert();
    //vector_bench::frontInsert();
    //vector_bench::sortEachInsert();

    //list_bench::backInsert();
    //list_bench::frontInsert();
    //list_bench::sortEachInsert();

    map_bench::mapGpl();
}
