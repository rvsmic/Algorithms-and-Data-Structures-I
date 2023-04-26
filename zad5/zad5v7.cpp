#include <iostream>
using namespace std;

//szybsza (?) wersja

typedef unsigned short ushort;

struct Village {
    string name;
    Village **neighbours;
    ushort neighbours_count;

    // do pozniejszego szukania trasy
    bool checked;

    Village(){}
    Village(string name) {
        this->name = name;
        checked = false;
    }

    void add_neighbours(string *neighbours_names, ushort count, Village **villages, ushort villages_count) {
        neighbours_count = count;
        neighbours = new Village*[count];
        for(int i=0;i<count;i++) {
            for(int j=0;j<villages_count;j++) {
                if(villages[j]->name == neighbours_names[i]) {
                    neighbours[i] = villages[j];
                    break;
                }
            }
        }
    }

    static Village *find_village(Village **villages, ushort count, string name) {
        for(int i=0;i<count;i++) {
            if(name == villages[i]->name) {
                return villages[i];
            }
        }
        // wyrzuci przy blednych danych jedynie
        return nullptr;
    }

    ushort find_longest_route(string *visits, ushort visit_count, Village **villages, ushort village_count);
};

struct Queue {
    Village* village;
    Queue* next;

    Queue(){}
    Queue(Village* village) {
        this->village = village;
    }

    void append(Village* new_next) {
        Queue *new_queue = new Queue(new_next);
        this->next = new_queue;
    }

    Queue* pop_first() {
        return this->next;
    }
};
ushort Village::find_longest_route(string *visits, ushort visit_count, Village **villages, ushort village_count) {
        ushort max_route = 0;
        ushort current_route = 0;

        Queue* queue = new Queue(this); //zawsze pierwszy element kolejki
        ushort queue_size = 1;

        ushort found_counter = 0;

        Queue* first_on_level = queue;
        Queue* temp;
        ushort temp_size;

        while(found_counter < visit_count) {
            temp_size = 0;
            for(int i=0;i<queue_size;i++) {
                for(int j=0;j<queue->village->neighbours_count;j++) {
                    for(int k=0;k<visit_count;k++) {
                        if(queue->village->name == visits[k]) {
                            if(max_route < current_route) {
                                max_route = current_route;
                            }
                            found_counter++;
                            visits[k] = "";
                            if(visit_count == found_counter) {
                                return max_route;
                            }
                        }
                    }
                    if(!queue->village->neighbours[j]->checked) {
                        queue->append(queue->village->neighbours[j]);
                        temp_size++;
                        queue->village->neighbours[j]->checked = true;
                    }
                }
                temp = queue;
                queue = queue->pop_first();
                delete temp;
                temp_size--;
            }
            queue_size = temp_size;
            current_route++;
        }

        return max_route;
    }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.tie(nullptr);

    ushort n; // liczba wszystkich wiosek
    ushort m; // liczba wiosek odwiedzonych przez Kazimierza

    cin>>n>>m;

    // wpisanie wszystkich nazw wiosek
    Village** villages = new Village*[n];
    string name;
    for(int i=0;i<n;i++) {
        cin>>name;
        villages[i] = new Village(name);
    }

    string *neighbours = new string[n];
    ushort count;

    for(int i=0;i<n;i++) {
        cin>>name;
        count = 0;
        while(name != "X") {
            neighbours[count] = name;
            cin>>name;
            count++;
        }
        villages[i]->add_neighbours(neighbours,count,villages,n);
    }

    // wpisanie startowej wioski i ustalenie wskaznika
    Village* start;
    cin>>name;
    start = Village::find_village(villages,n,name);

    // wpisanie nazw wiosek do odwiedzenia
    string *visits = new string[m];
    for(int i=0;i<m;i++) {
        cin>>name;
        visits[i] = name;
    }

    // poszukiwanie trasy i wyswietlenie wyniku algorytmu
    cout<<start->find_longest_route(visits,m,villages,n)<<"\n";
}