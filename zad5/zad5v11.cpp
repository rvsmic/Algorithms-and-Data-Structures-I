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
    vector <Village*> neighbours;

    bool checked;

    Village(){}
    Village(string name) {
        this->name = name;
        checked = false;
    }

    ushort find_longest_route(map <string,ushort> destinations_map, Village** villages, ushort villages_count) {
        //this to startowa wioska
        queue <Village*> village_queue;
        //wstawienie startowej wioski do kolejki
        village_queue.push(this);

        ushort current_route = 1;
        ushort max_route = 0;
        Village* current;

        ushort level_counter = 0;
        ushort level_cap = 1;
        ushort future_level_cap = 0;

        //ustawienie drogi 
        this->checked = true;
        
        while(!village_queue.empty()) {
            level_counter++;
            current = village_queue.front();
            village_queue.pop();
            for(int j=0;j<current->neighbours.size();j++) {
                if(!current->neighbours[j]->checked) {
                    if(destinations_map[current->neighbours[j]->name] == 54321 && current_route > max_route) {
                        max_route = current_route;
                    }
                    current->neighbours[j]->checked = true;
                    village_queue.push(current->neighbours[j]);
                    future_level_cap++;
                }
            }
            if(level_counter == level_cap) {
                current_route++;
                level_counter = 0;
                level_cap = future_level_cap;
                future_level_cap = 0;
            }
        }
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

    string name;

    //wszystkie wioski
    Village **villages = new Village*[n];
    //mapa wiosek i ich indeksow
    map <string,ushort> villages_map;

    for(int i=0;i<n;i++) {
        cin>>name;
        villages[i] = new Village(name);
        villages_map[name] = i;
    }

    for(int i=0;i<n;i++) {
        cin>>name;
        villages[i]->neighbours.reserve(n);
        while(name != "X") {
            //dodanie do sasiadow danej wioski
            villages[i]->neighbours.push_back(villages[villages_map[name]]);
            cin>>name;
        }
        villages[i]->neighbours.shrink_to_fit();
    }

    //wioska startowa
    Village* start;
    cin>>name;

    start = villages[villages_map[name]];

    //wioski docelowe
    for(int i=0;i<m;i++) {
        cin>>name;
        //bo i tak nie ma tylu wiosek a da sie rozpoznac latwo
        villages_map[name] = 54321;
    }

    cout<<start->find_longest_route(villages_map,villages,n);

    return 0;
}