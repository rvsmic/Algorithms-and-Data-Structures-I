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

    ushort find_longest_route(string *visits, ushort visit_count, Village **villages, ushort village_count) {
        /*
            petla schodzaca po poziomach grafu
            przy kazdym zejsciu zmienia elementy z poziomu na checked = true zeby sie nie zapetlic
            i zwieksza current_route
            na kazdym zejsciu porownuje sasiadow danego elementu z poziomu z wizytami
            jak znajdzie to dana wizyta jest zamieniana na "" i counter jest zwiekszony
            jak counter == visit_count konczymy szukanie
        */
        ushort max_route = 0;
        ushort current_route = 1;

        Village** current_level = new Village*[village_count];
        ushort level_size = 1;
        current_level[0] = this;

        Village **temp_level;
        ushort temp_size;

        ushort visit_counter = 0;
        bool found_all = false;

        // szukamy az znajdziemy wszystkie wizyty
        while(visit_counter < visit_count) {
            // sprawdzenie danego poziomu
            for(int i=0;i<level_size;i++) {
                // przeszukanie sasiadow danego elementu z poziomu bez wracania do gory
                for(int j=0;j<current_level[i]->neighbours_count;j++) {
                    // sprawdzenie dany sasiad jest wizyta
                    for(int k=0;k<visit_count;k++) {
                        if(visits[k] == current_level[i]->neighbours[j]->name && !current_level[i]->neighbours[j]->checked) {
                            if(current_route > max_route) {
                                max_route = current_route;
                            }
                            visits[k] = "";
                            visit_counter++;
                            if(visit_counter == visit_count) {
                                return max_route;
                            }
                        }
                    }
                }
                current_level[i]->checked = true;
            }
            current_route++;

            // zejscie nizej
            temp_size = level_size;
            temp_level = new Village*[village_count];
            level_size = 0;
            for (int j=0;j<temp_size;++j) {
                for (int k=0;k<current_level[j]->neighbours_count;++k) {
                    if (!current_level[j]->neighbours[k]->checked) {
                        current_level[j]->neighbours[k]->checked = true;
                        temp_level[level_size] = current_level[j]->neighbours[k];
                        level_size++;
                    }
                }
            }
            delete[] current_level;
            current_level = temp_level;
        }
        return max_route;
    }

    void test_print() {
        cout<<name<<": ";
        for(int i = 0; i < neighbours_count; i++) {
            cout<<neighbours[i]->name<<" ";
        }
        cout<<"\n";
    }
};

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
    // wpisanie informacji o sasiadach danej wioski do macierzy sasiedztwa
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

    // wpisanie wiosek do odwiedzenia
    string *visits = new string[m];
    for(int i=0;i<m;i++) {
        cin>>name;
        visits[i] = name;
    }

    // testowe
    //  cout<<"---"<<endl;
    //  for(int i=0;i<n;i++) {
    //      villages[i]->test_print();
    //  }
    //  cout<<"---"<<endl;
    //  cout<<"==="<<endl;
    //  for(int i=0;i<m;i++) {
    //      visits[i]->test_print();
    //  }
    //  cout<<"==="<<endl;

    // poszukiwanie trasy i wyswietlenie wyniku algorytmu
    cout<<start->find_longest_route(visits,m,villages,n)<<"\n";
}