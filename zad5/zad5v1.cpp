#include <iostream>
using namespace std;

typedef unsigned short ushort;

class Village {
    string name;
    Village* neighbours;
    ushort neighbour_count;
    
    public:
    Village(){}
    Village(string name) {
        this->name = name;
        neighbour_count = 0;
    }

    string get_name() {
        return name;
    }

    void add_neighbours(Village* all_villages, ushort village_count, string* villages_to_add, ushort add_count) {
        neighbour_count = add_count;
        neighbours = new Village[neighbour_count];
        ushort counter = 0;
        for(int i=0;i<add_count;i++) {
            for(int j=0;j<village_count;j++) {
                if(all_villages[j].name == villages_to_add[i]) {
                    neighbours[counter] = all_villages[j];
                    counter++;
                    break;
                }
            }
        }
    }

    ushort find_longest_path(string* destinations, ushort destination_count, ushort* found_counter, ushort current_distance, ushort* max_distance) {
        if(*found_counter == destination_count) {
            return *max_distance;
        }

        
        for(int i=0;i<this->neighbour_count;i++) {
            for(int j=0;j<destination_count;j++) {
                if(destinations[j] == this->neighbours[i].name) {
                    destinations[j] = "";
                    found_counter++;
                    if(current_distance > *max_distance) {
                        *max_distance = current_distance;
                    }
                }

                if(found_counter == destination_count) {
                    return *max_distance;
                }
            }
        }

        //jak zle cos
        return -1;
    }

    // ushort find_longest_path(Village* villages, ushort villages_count, string* destinations, ushort destinations_count) {
    //     //this to startowa wioska
    //     ushort distance = 0;
    //     ushort max_distance = 0;
    //     Village* current = this;
    //     ushort found_counter = 0;

    //     if(current->name == destinations[0]) {
    //         found_counter++;
    //     }

    //     while(found_counter < destinations_count) {
    //         distance++;
    //         for(int i=0;i<current->neighbour_count;i++) {
    //             for(int j=0;j<destinations_count;j++) {
    //                 if(current->neighbours[i].name == destinations[j]) {
    //                     if(max_distance < distance) {
    //                         max_distance = distance;
    //                     }
    //                 //zeby bralo pod uwage tylko najkrotsze trasy
    //                     destinations[i] = "";
    //                     found_counter++;
    //                 }
    //             }
    //         }
    //         current = 
    //     }

    //     // for(int i=0;i<destinations_count;i++) {
    //     //     distance++;
    //     //     for(int j=0;j<current->neighbour_count;j++) {
    //     //         if(current->neighbours[j].name == destinations[i]) {
    //     //             if(max_distance < distance) {
    //     //                 max_distance = distance;
    //     //             }
    //     //             //zeby bralo pod uwage tylko najkrotsze trasy
    //     //             destinations[i] = "";
    //     //             found_counter++;
    //     //         }
    //     //         if(found_counter == destinations_count) {
    //     //             return max_distance;
    //     //         }
    //     //     }
    //     // }

    //     return max_distance;
    // }

    //testowe
    void print_village() {
        cout<<name<<": ";
        for(int i=0;i<neighbour_count;i++) {
            cout<<neighbours[i].name<<" ";
        }
        cout<<endl;
    }
};

/*
    wioski ustawione w grafie
    polaczone powiazaniami
    algorytm odczytuje graf metoda bfs i szuka koncowych wiosek, zliczajac przy tym trase
    przerywa odczytywanie jak juz znajdzie wszystkie wioski
*/

int main() {

    ushort n;    //liczba wszystkich wiosek
    ushort m;    //liczba wiosek odwiedzonych przez Kazimierza

    cin>>n>>m;

    //utworzenie wierzcholkow grafu
    Village* villages = new Village[n];
    string name;
    for(int i=0;i<n;i++) {
        cin>>name;
        villages[i] = Village(name);
    }

    string* villages_to_add = new string[n];
    ushort add_count = 0;
    
    //powiazanie wierzcholkow grafu
    for(int i=0;i<n;i++) {
        cin>>name;
        while(name != "X") {
            villages_to_add[add_count] = name;
            add_count++;
            cin>>name;
        }
        villages[i].add_neighbours(villages,n,villages_to_add,add_count);
        add_count = 0;
    }
    delete[] villages_to_add;

    //startowa wioska
    string start_name;
    ushort start_index;
    cin>>start_name;

    //znalezienie startowej wioski w grafie
    for(int i=0;i<n;i++) {
        if(villages[i].get_name() == start_name) {
            start_index = i;
            break;
        }
    }

    //przystanki do wykonania
    string* destinations = new string[m];
    for(int i=0;i<m;i++) {
        cin>>destinations[i];
    }
    delete[] destinations;

    //testowe
    cout<<"---"<<endl;
    for(int i=0;i<n;i++) {
        villages[i].print_village();
    }
    cout<<"---"<<endl;

    //odpowiedz
    cout<<villages[start_index].find_longest_path(villages,n,destinations,m)<<"\n";

    return 0;
}