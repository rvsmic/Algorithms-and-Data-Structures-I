#include <iostream>
using namespace std;
typedef unsigned int uint;
typedef unsigned short ushort;

//update prefixow
inline void update_prefixes(uint **prefixes, uint **results, ushort team_count) {
  //maksymalna wartosc do tej pory w danym wierszu
  uint row_max;
  for(int i=0;i<team_count+1;++i) {
    row_max = 0;
    for(int j=0;j<team_count;++j) {
      //jezeli jest wieksze od aktualnego maxa to zmieniamy maxa
      if(results[i][j] > row_max) {
        row_max = results[i][j];
      }
      //nadpisanie maxem aktualnej komorki
      prefixes[i][j] = row_max;
    }
  }
}

//zamiany druzyn
inline void move_teams(uint **results, uint **prefixes, uint *points, ushort team_count, ushort current_team_index) {
  //przesuniecie o jeden wiersz w dol i dodanie punktow druzyny z kolumny
  for(int i=team_count;i>0;--i) {
    for(int j=0;j<team_count;++j) {
      if(results[i-1][j] > 0) {
        results[i][j] = results[i-1][j] + points[j];
      }
    }
  }

  //wyzerowanie pierwszego wiersza po przesunieciu
  for(int i=0;i<team_count;++i) {
    results[0][i] = 0;
  }

  //schodki dla prawej strony od aktualnego teamu
  for(int i=0;i<current_team_index+2;++i) {
    //zeby nie wyszlo za tablice w pionie
    if(i == team_count+1) {
      break;
    }

    for(int j=current_team_index;j<current_team_index+i+1;++j) {
      //zeby nie wyszlo za tablice w poziomie
      if(j == team_count) {
        break;
      }
      /*
        patrzymy na najwieksze wartosci z wiersza o odleglosc od sprawdzanej druzyny w prawo 
        (ta sama kolumna da 0, a np nastepna kolumna da 1 ~ patrzymy o te wartosc wierszy nizej)
        i sprawdzamy najwieksza wartosc dla zmienianych miejsc do tej pory (j-1)
        + punkty aktualnie sprawdzanej druzyny
      */
      uint sum = prefixes[i-(j-current_team_index)][j-1] + points[j];
      //jezeli obliczona suma jest wieksza niz aktualna wartosc komorki to nadpisujemy
      if(sum > results[i][j]) {
        results[i][j] = sum;
      }
    }
  }

  //update prefixow na nastepny raz
  update_prefixes(prefixes,results,team_count);
}

uint find_max_points(uint* points, ushort team_count) {
  uint **results = new uint*[team_count + 1];
  uint **prefixes = new uint*[team_count + 1];

  //stworzenie tablic
  for(int i=0;i<team_count+1;++i) {
    results[i] = new uint[team_count];
    prefixes[i] = new uint[team_count];
  }

  //przejscie soltysa
  for(int i=0;i<team_count;++i) {
    move_teams(results,prefixes,points,team_count,i);
  }

  //zwrocenie najwiekszej wartosci z ostatniego wiersza - bo nie zawsze wypada w ostatniej kolumnie w ostatnim wierszu :/
  return prefixes[team_count][team_count-1];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  ushort n; //liczba zespolow
  uint *a;  //punkty druzyn
  cin>>n;
  a = new uint[n];
  for(int i=0;i<n;++i) {
    cin>>a[i];
  }

  cout<<find_max_points(a,n)<<"\n";
}