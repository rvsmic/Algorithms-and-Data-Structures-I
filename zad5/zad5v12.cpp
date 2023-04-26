#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;
typedef unsigned short ushort;

/*
    max sciezka z najkrotszych sciezek do punktow
    odczytywanie bfs - dodawanie do kolejki sasiadow
    liczenie odleglosci 
    tablica z komorka z min odlegloscia do wierzcholka i komorka z odwiedzeniem wierzcholka

    najpierw do kolejki dodajemy wierzcholek A z odlegloscia 0
    poki kolejka nie jest pusta sciagamy element z kolejki > oznaczamy sasiadow jako odwiedzonych > dodajemy sasiadow do kolejki
    z odlegloscia zwiekszona

    kolejka w zlozonosci liniowej musi byc

    przy wpisywaniu nazw - nie szukac nazw w wierzcholkach!!!
    uzyc komponentow stl - "map" - szukac po kluczu - zlozonosc logarytmiczna
*/

struct Village {
    string name;
    //tablica sasiadow
    vector <Village*> neighbours;

    //czy odwiedzona
    bool checked;
    //czy jest celem podrozy
    bool is_target;

    Village(){}
    Village(string name) {
        this->name = name;
        checked = false;
        is_target = false;
    }

    ushort find_longest_route(vector <Village*> villages, ushort villages_count) {
        //this to startowa wioska
        queue <Village*> village_queue;
        //wstawienie startowej wioski do kolejki
        village_queue.push(this);

        //droga dla danego poziomu
        ushort current_route = 1;
        //maksymalna droga
        ushort max_route = 0;
        //wskaznik na aktualna wioske
        Village* current;

        //licznik elementow na poziomie
        ushort level_counter = 0;
        //rozmiar poziomu
        ushort level_cap = 1;
        //przyszly rozmiar poziomu
        ushort future_level_cap = 0;

        //"odwiedzenie" poczatkowej wioski 
        this->checked = true;
        
        while(!village_queue.empty()) {
            //odwiedzenie wioski
            level_counter++;
            //sciagniecie wioski z kolejki
            current = village_queue.front();
            village_queue.pop();
            //przejscie po sasiadach sciagnietej wioski
            for(int j=0;j<current->neighbours.size();j++) {
                //jezeli sasiad jeszcze nie byl odwiedzony
                if(!current->neighbours[j]->checked) {
                    //jezeli jest celem i ma dalsza trase
                    if(current->neighbours[j]->is_target && current_route > max_route) {
                        max_route = current_route;
                    }
                    //odwiedzenie
                    current->neighbours[j]->checked = true;
                    //dodanie do kolejki
                    village_queue.push(current->neighbours[j]);
                    //zwiekszenie przyszlego rozmiaru poziomu
                    future_level_cap++;
                }
            }
            //restart zliczania poziomu w wypadku skonczenia aktualnego
            if(level_counter == level_cap) {
                current_route++;
                level_counter = 0;
                level_cap = future_level_cap;
                future_level_cap = 0;
            }
        }
        //zwrocenie najkrotszej drogi do najdalszej wioski
        return max_route;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.tie(nullptr);

    //liczba wszystkich wiosek, liczba docelowych wiosek
    ushort n,m;
    cin>>n>>m;

    //tymczasowe przechowywanie danej nazwy
    string name;

    //wszystkie wioski
    vector <Village*> villages;
    //mapa wiosek i ich indeksow
    map <string,ushort> villages_map;

    for(int i=0;i<n;i++) {
        cin>>name;
        //dodanie do tablicy wiosek
        villages.push_back(new Village(name));
        //uzupelnienie mapy
        villages_map[name] = i;
    }

    for(int i=0;i<n;i++) {
        cin>>name;
        while(name != "X") {
            //dodanie do sasiadow danej wioski
            villages[i]->neighbours.push_back(villages[villages_map[name]]);
            cin>>name;
        }
    }

    //wskaznik na wioske startowa
    Village* start;
    cin>>name;

    start = villages[villages_map[name]];

    //wioski docelowe
    for(int i=0;i<m;i++) {
        cin>>name;
        //ustawienie ze dana wioska jest celem
        villages[villages_map[name]]->is_target = true;
    }

    //wyrzucenie z pamieci mapy, poniewaz juz jest zbedna, a jeszcze bedzie potrzebne miejsce dla kolejki
    villages_map.clear();

    cout<<start->find_longest_route(villages,n);

    return 0;
}