#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned short ushort;
typedef unsigned int uint;

/*
 _ 3 1 5 4 10  s=0
  _3 1 5 10 4  s=3
  3 _5 1 10 4  s=8
  3 5 _10 1 4  s=18
  3 5 1 _10 4  s=28
  3 5 1 4 _10  s=38

  patrzymy na 1 team i wplyw maja 2 pierwsze druzyny
  a potem patrzymy na wplyw przyszlych druzyn na wynik

  patzymy na pierwsze i druzyn i ich wplyw na wynik

  tablica dwuwymiarowa
  kolumny - druzyny (1 - 5)
  wiersze - zamiany (0 - 5)

  wpisujemy max wartosc dla danej ilosci zmian

  i = 1
  aktualizujemy tylko 2 pierwsze wiersze
    0 1 2 3 4
    1 2 3 4 5
  0 3
  1 3 1
  2
  3
  4
  5
  
  i = 2
  aktualizujemy 3 pierwsze wiersze - przesuwamy w dol i dodajemy aktualna druzyne do poprzednich wynikow - z lewej strony druzyny
    0 1 2 3 4
    1 2 3 4 5
  0
  1 6
  2 6 2
  3
  4
  5

  teraz prawa strona
  patrzymy na poprzednia tablice
    0 1 2 3 4
    1 2 3 4 5
  0   4
  1 6 4 8       - 8 bo patrzymy na wiersz o 1 zmiane wczesniej czyli wiersz 0 z poprzedniej - tam max wartosc to 3 + aktualna wartosc 5 = 8
  2 6 2 8 7     - 7 bo patrzymy na wiersz o 2 zmiany wczesniej czyli wiersz 0 z poprzedniej - max 3 + 4 = 7
  3
  4
  5

  i = 3
  aktualizujemy pierwsze 4 wiersze - to samo co wyzej
    1 2 3  4  5
  0 
  1   5
  2 9 5 13
  3 9 3 13 11
  4
  5

  teraz prawa
    1 2 3  4  5
  0     9
  1   5 11 8
  2 9 5 13 12 14
  3 9 3 13 12 18
  4
  5

  i = 4
  aktualizujemy pierwszych 5 wierszy - to samo co wyzej
    1  2 3  4  5
  0 
  1      14
  2    6 16 12
  3 12 6 18 16 24
  4 12 4 18 16 28
  5


    1  2 3  4  5
  0         13
  1      14 15 19
  2    6 16 17 21
  3 12 6 18 17 24
  4 12 4 18 16 28
  5

  i = 5
  aktualizujemy pierwszych 6 wierszy - to samo co wyzej
    1  2 3  4  5
  0 
  1         17
  2      19 19 29
  3    7 21 21 31
  4 15 7 23 21 34
  5 15 5 23 20 38

  i wychodzi ze nie modyfikujemy potem


  wynik bedzie zawsze w ostaniej kolumnie w ostatnim wierszu!!!!!

  *** maksima prefiksowe (dla chetnych) - do szukania maxa w wierszu

*/

void print_arr(vector <vector <uint> > arr, string text) {
  cout<<text<<":\n";
  for(int i=0;i<arr.size();++i) {
    for(int j=0;j<arr[i].size();++j) {
      cout<<arr[i][j]<<" ";
    }
    cout<<endl;
  }
}

uint max_in_row(vector <uint> row) {
  uint mx = 0;
  for(int i=0;i<row.size();++i) {
    if(row[i] > mx) {
      mx = row[i];
    }
  }
  return mx;
}

void update_result(vector <uint> &original_order, vector <vector <uint> > &result_arr, vector <vector <uint> > &old_arr, ushort team_count, int current_person_index) {
  //wyzerowanie pierwszego wiersza result
  for(int i=0;i<result_arr.size();++i) {
    result_arr[0][i] = 0;
  }
  
  //LEWA STRONA OD AKTUALNEJ DRUZYNY
  for(int i=1;i<result_arr.size();++i) {
    //kopiujemy wiersze ze starej do nowej z przesunieciem ~ np. old[0] = result[1]
    result_arr[i] = old_arr[i-1];

    //zwiekszenie wartosci o odpowiadajace wartosci druzyny z kolumny
    for(int j=0;j<result_arr[i].size();++j) {
      if(result_arr[i][j] > 0) {
        result_arr[i][j] += original_order[j];
      }
    }
  }
  
  //PRAWA STRONA OD AKTUALNEJ DRUZYNY
  //"schodki" dla aktualizacji "prawej strony"
  ushort max_i,max_j,max_from_row;
  //zeby nie wyjsc poza tablice w pionie
  if(current_person_index + 2 > team_count + 1) {
    max_i = team_count + 1;
  } else {
    max_i = current_person_index + 2;
  }

  for(int i=0;i<max_i;++i) {
    //zeby nie wyjsc poza tablice w poziomie
    if(i + current_person_index + 1 > team_count) {
      max_j = team_count;
    } else {
      max_j = i + current_person_index + 1;
    }

    for(int j=current_person_index;j<max_j;++j) {
      max_from_row = max_in_row(old_arr[j-current_person_index]) + original_order[j];
      if(result_arr[i][j] < max_from_row) {
        result_arr[i][j] = max_from_row;
      }
    }
  }
  
  //zapisanie do starej - tak wektory robia kopie
  old_arr = result_arr;
}

uint max_result(vector <uint> &original_order, ushort team_count) {
  vector <vector <uint> > result_arr;
  vector <vector <uint> > old_arr;

  //n+1 wierszy bo patrzymy tez na 0 przejsc
  result_arr.reserve(team_count+1);
  old_arr.reserve(team_count+1);

  //n kolumn w kazdym wierszu
  for(int i=0;i<team_count+1;++i) {
    result_arr[i].reserve(team_count);
    old_arr[i].reserve(team_count);
  }

  for(int i=0;i<team_count;++i) {
    update_result(original_order,result_arr,old_arr,team_count,i);
    print_arr(result_arr,"result");
    print_arr(old_arr,"old");
  }

  return result_arr[team_count-1][team_count];
}

int main() {
  ushort n;         //liczba zespolow
  vector <uint> a;  //wyniki zespolow
  uint number;
  cin>>n;
  for(int i=0;i<n;++i) {
    cin>>number;
    a.push_back(number);
  }

  cout<<max_result(a,n)<<"\n";

  return 0;
}