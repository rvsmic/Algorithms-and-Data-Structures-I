#include <iostream>
using namespace std;

//w tej wersji sprawdzamy tylko istotne elementy

typedef unsigned short ushort;

struct Village {
    string name;
    Village** neighbours;
    ushort neighbours_count;
    
    //do pozniejszego szukania trasy
    bool checked;

    Village(){}
    Village(string name) {
        this->name = name;
        checked = false;
    }

    void add_neighbours(string* neighbours_names, ushort count, Village** villages, ushort villages_count) {
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

    static Village* find_village(Village** villages, ushort count, string name) {
        for(int i=0;i<count;i++) {
            if(name == villages[i]->name) {
                return villages[i];
            }
        }
        //wyrzuci przy blednych danych jedynie
        return nullptr;
    }

    ushort find_longest_route(Village** visits, ushort visit_count, Village** villages, ushort village_count) {
        /*
            petla obracajaca po wizytach szukajaca i wizyty we wszystkich wioskach
            startuje od start czyli this wpisanego do tablicy current i ustawia jej wielkosc na 1
            petla sprawdza tablice sasiadow obecnego elementu i jak nie znajdzie to schodzi nizej
            ale jedynie do checked == false
            schodzac nizej zwieksza dlugosc trasy
            przy okazji sprawdzania wpisuje wskazniki do sasiadow do tablicy current_level i ustala jej nowa wielkosc
            w chwili schodzenia nizej zmienia aktualny wskaznik na checked = true dzieki czemu potem sie nie zapetli

            EWENTUALNIE SPROBOWAC Z WHILEM I COUNTEREM NA ZNALEZIONE WIZYTY - SPRAWDZANIE INDYWIDUALNIE NA KAZDEJ WIOSCE CZY JEST WIZYTA
        */
        ushort max_route = 0;
        ushort current_route;

        Village** current_level = new Village*[village_count];
        ushort level_size = 1;
        current_level[0] = this;

        bool found = false;

        Village** temp_level;
        ushort temp_size;

        //sprawdzenie wszystkich wizyt
        for(int i=0;i<visit_count;i++) {
            current_route = 1;
            //cout<<" VISIT:"<<visits[i]->name;
            //ewentualne schodzenie coraz nizej
            for(int l=0;l<village_count;l++) {
                //cout<<" ROUTE:"<<current_route;
                //sprawdzenie danego poziomu
                for(int j=0;j<level_size;j++) {
                    //cout<<" CURRENT:"<<current_level[j]->name;
                    //sprawdzenie sasiadow danego elementu z poziomu ale bez elementu "nad nim"
                    for(int k=0;k<current_level[j]->neighbours_count;k++) {
                        if(current_level[j]->neighbours[k] == visits[i] && !current_level[j]->neighbours[k]->checked) {
                            if(current_route > max_route) {
                                max_route = current_route;
                            }
                            found = true;
                            break;
                        }

                    }
                    if(found) {
                        break;
                    }
                    current_level[j]->checked = true;
                }
                if(found) {
                    found = false;
                    break;
                }
                //zejscie nizej
                current_route++;

                temp_size = level_size;
                temp_level = new Village*[village_count];
                level_size = 0;
                for(int j=0;j<temp_size;j++) {
                    for(int k=0;k<current_level[j]->neighbours_count;k++) {
                        if(!current_level[j]->neighbours[k]->checked) {
                            current_level[j]->neighbours[k]->checked = true;
                            temp_level[level_size] = current_level[j]->neighbours[k];
                            level_size++;
                        }
                    }
                }
                delete[] current_level;
                current_level = temp_level;
            }
            //wyzerowanie checkow na kolejna wizyte
            for(int j=0;j<village_count;j++) {
                villages[j]->checked = false;
            }
        }
        return max_route;
    }

    void test_print() {
        cout<<name<<": ";
        for(int i=0;i<neighbours_count;i++) {
            cout<<neighbours[i]->name<<" ";
        }
        cout<<"\n";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    cin.tie(nullptr);
    
    ushort n;    //liczba wszystkich wiosek
    ushort m;    //liczba wiosek odwiedzonych przez Kazimierza

    cin>>n>>m;

    //wpisanie wszystkich nazw wiosek
    Village** villages = new Village*[n];
    string name;
    for(int i=0;i<n;i++) {
        cin>>name;
        villages[i] = new Village(name);
    }

    string* neighbours = new string[n];
    ushort count;
    //wpisanie informacji o sasiadach danej wioski do macierzy sasiedztwa
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

    //wpisanie startowej wioski i ustalenie wskaznika
    Village* start;
    cin>>name;
    start = Village::find_village(villages,n,name);
    
    //wpisanie wiosek do odwiedzenia
    Village** visits = new Village*[m];
    for(int i=0;i<m;i++) {
        cin>>name;
        visits[i] = Village::find_village(villages,n,name);
    }

    //testowe
    // cout<<"---"<<endl;
    // for(int i=0;i<n;i++) {
    //     villages[i]->test_print();
    // }
    // cout<<"---"<<endl;
    // cout<<"==="<<endl;
    // for(int i=0;i<m;i++) {
    //     visits[i]->test_print();
    // }
    // cout<<"==="<<endl;

    //poszukiwanie trasy i wyswietlenie wyniku algorytmu
    cout<<start->find_longest_route(visits,m,villages,n)<<"\n";
}