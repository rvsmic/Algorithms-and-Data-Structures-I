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
            petla while krecaca sie az do couter == visit_count
            w srodku sprawdza w petli po kolei current wioski czy sa wizytami
            jezeli sa to zwieksza couter i zmienia wizyte na  ""
            przy po sprawdzeniu danej wioski na aktualnym poziomie zmienia ja na checked = true
            po sprawdzeniu poziomu odpala sie petla zmieniajaca current wioski na sasiadow current wiosek
            rownoczesnie pomija powtorzenia
        */
        ushort max_route = 0;
        ushort current_route = 0;

        Village** current_level = new Village*[village_count];
        ushort level_size = 1;
        current_level[0] = this;

        Village **temp_level;
        ushort temp_size;

        ushort visit_counter = 0;

        //sprawdzanie az do znalezienia wszystkich wizyt
        while(visit_counter < visit_count) {
            temp_size = 0;
            temp_level = new Village*[village_count];
            //sprawdzenie wszystkich wiosek z poziomu
            for(int i=0;i<level_size;i++) {
                //porownanie ze wszystkimi wizytami
                for(int j=0;j<visit_count;j++) {
                    if(visits[j] == current_level[i]->name) {
                        visit_counter++;
                        visits[j] = "";
                        if(current_route > max_route) {
                            max_route = current_route;
                        }
                        //jak wszystkie odwiedzi
                        if(visit_counter == visit_count) {
                            return max_route;
                        }
                    }
                }
                current_level[i]->checked = true;

                //przygotowanie na nowy poziom
                for(int j=0;j<current_level[i]->neighbours_count;j++) {
                    //jezeli nie bylo wyzej
                    if(!current_level[i]->neighbours[j]->checked) {
                        current_level[i]->neighbours[j]->checked = true;
                        temp_level[temp_size] = current_level[i]->neighbours[j];
                        temp_size++;
                    }
                }
            }
            //zejscie nizej
            current_route++;

            //usuniecie zbednych danych z pamieci i przypisanie nowego temp do current
            delete[] current_level;
            current_level = temp_level;
            level_size = temp_size;
        }
        return max_route;
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

    // wpisanie nazw wiosek do odwiedzenia
    string *visits = new string[m];
    for(int i=0;i<m;i++) {
        cin>>name;
        visits[i] = name;
    }

    // poszukiwanie trasy i wyswietlenie wyniku algorytmu
    cout<<start->find_longest_route(visits,m,villages,n)<<"\n";
}