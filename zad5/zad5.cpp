#include <iostream>
using namespace std;

typedef unsigned short ushort;

ushort find_village_index(string name, string* villages, ushort villages_count) {
    for(int i=0;i<villages_count;i++) {
        if(name == villages[i]) {
            return i;
        }
    }
    //jakby cos sie zepsulo
    return -1;
}

ushort longest_trip(bool** neighbour_matrix, string* villages_names, ushort village_count, string* stops, ushort stop_count, ushort start_index) {
    ushort considered_stop;
    ushort current_index;
    ushort max_route = 0;
    ushort current_route;
    for(int i=0;i<stop_count;i++) {
        considered_stop = find_village_index(stops[i],villages_names,village_count);
        current_route = 0;
        for(int j=1;j<village_count;j++) {
            if(neighbour_matrix[j][considered_stop]) {

            }
        }

    }
    return max_route;
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(nullptr); 
    // cin.tie(nullptr);

    ushort n;    //liczba wszystkich wiosek
    ushort m;    //liczba wiosek odwiedzonych przez Kazimierza

    cin>>n>>m;

    //wpisanie wszystkich nazw wiosek - aby potem rozpoznac po indeksie w macierzy sasiedztwa
    string* villages_names = new string[n];
    string name;
    for(int i=0;i<n;i++) {
        cin>>name;
        villages_names[i] = name;
    }

    //utworzenie macierzy sasiedztwa
    bool** neighbour_matrix = new bool*[n];
    for(int i=0;i<n;i++) {
        neighbour_matrix[i] = new bool[n];                  //MOZNA ZROBIC O PONAD POLOWE MNIEJSZA BO GRAF NIESKIEROWANY
        for(int k=0;k<n;k++) {
            neighbour_matrix[i][k] = false;
        }
    }
    
    //wpisanie informacji o sasiadach danej wioski do macierzy sasiedztwa
    for(int i=0;i<n;i++) {
        cin>>name;
        while(name != "X") {
            neighbour_matrix[i][find_village_index(name,villages_names,n)] = true;
            cin>>name;
        }
    }

    //testowe wyswietlenie macierzy
    cout<<endl;
    cout<<"  ";
    for(int i=0;i<n;i++) {
        cout<<villages_names[i][0]<<' ';
    }
    cout<<endl;
    for(int i=0;i<n;i++) {
        cout<<villages_names[i][0]<<" ";
        for(int j=0;j<n;j++) {
            cout<<neighbour_matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    //startowa wioska
    string start;
    cin>>start;
    ushort start_index = find_village_index(start,villages_names,n);

    //przystanki do wykonania
    string* stops = new string[m];
    for(int i=0;i<m;i++) {
        cin>>stops[i];
    }

    /*
        jeden start i wiele zakonczen
    */

    cout<<longest_trip(neighbour_matrix, villages_names, n, stops, m, start_index)<<"\n";

    return 0;
}