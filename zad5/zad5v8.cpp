#include <iostream>
#include <map>
#include <queue>

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
    Village **neighbours;
    ushort neighbours_count;

    ushort distance;
    bool checked;

    bool is_first_on_level;


    Village(){}
    Village(string name) {
        this->name = name;
        distance = 0; //zeby potem znalazlo krotsza sciezke - max value ushorta
        checked = false;
        is_first_on_level = false;
    }

    void add_neighbours(string *neighbours_names, ushort neighbour_count, Village **villages, map <string,ushort> villages_map) {
        this->neighbours_count = neighbour_count;
        neighbours = new Village*[neighbour_count];
        for(int i=0;i<neighbour_count;i++) {
            neighbours[i] = villages[villages_map[neighbours_names[i]]];
        }
    }

    static void test_print(Village** villages, ushort village_count) {
        cout<<endl;
        for(int i=0;i<village_count;i++) {
            cout<<villages[i]->name<<": ";
            for(int j=0;j<villages[i]->neighbours_count;j++) {
                cout<<villages[i]->neighbours[j]->name<<" ";
            }
            cout<<endl;
        }
    }

    ushort find_longest_route(map <string,bool> destinations_map, Village** villages, ushort villages_count) {
        //this to startowa wioska
        queue <Village*> village_queue;
        //wstawienie startowej wioski do kolejki
        village_queue.push(this);

        ushort current_route = 0;
        Village* current;

        //ustawienie drogi 
        this->is_first_on_level = true;
        this->checked = true;
        
        for(int i=0;i<village_queue.size();i++) {
            current = village_queue.front();
            village_queue.pop();
            if(current->is_first_on_level) {
                current_route++;
            }
            for(int j=0;j<current->neighbours_count;j++) {
                if(j == 0) {
                    current->neighbours[j]->is_first_on_level = true;
                }
                if(!current->neighbours[j]->checked) {
                    if(destinations_map[current->neighbours[j]->name]) {
                        current->neighbours[j]->distance = current_route;
                    }
                    current->neighbours[j]->checked = true;
                    village_queue.push(current->neighbours[j]);
                }
            }
        }
        
        //szukanie najmniejszej odleglosci
        //BEDZIE WOLNE ZAPEWNE
        ushort max_distance = 0;
        for(int i=0;i<villages_count;i++) {
            //cout<<villages[i]->name<<" "<<villages[i]->distance<<"\n";
            if(villages[i]->distance > max_distance) {
                max_distance = villages[i]->distance;
            }
        }

        return max_distance;
    }
};

int main() {
    //liczba wszystkich wiosek, liczba docelowych wiosek
    ushort n,m;
    cin>>n>>m;

    string name;

    //wszystkie wioski
    Village **villages = new Village*[n];
    //mapa wiosek i ich indeksow
    map <string,ushort> villages_map;
    map <string,bool> destinations_map;

    for(int i=0;i<n;i++) {
        cin>>name;
        villages[i] = new Village(name);
        villages_map[name] = i;
        destinations_map[name] = false;
    }

    ushort neighbour_count;
    string* neighbours = new string[n];
    for(int i=0;i<n;i++) {
        cin>>name;
        neighbour_count = 0;
        while(name != "X") {
            //dodanie do sasiadow danej wioski
            neighbours[neighbour_count] = name;
            neighbour_count++;
            cin>>name;
        }
        villages[i]->add_neighbours(neighbours,neighbour_count,villages,villages_map);
    }
    delete[] neighbours;

    //wioska startowa
    Village* start;
    cin>>name;

    start = villages[villages_map[name]];

    //wioski docelowe
    for(int i=0;i<m;i++) {
        cin>>name;
        destinations_map[name] = true;
    }

    cout<<start->find_longest_route(destinations_map,villages,n);

    return 0;
}