#include <iostream>
using namespace std;

//jak problem hetmana!!!

/*
  szukamy sposrod wszystkich mozliwych rozwiazan najtanszy uklad
  przerywamy jak w ktoryms wierszu nie da sie dostawic namiotu lub jak koszt bedzie za duzy
  rekurencyjnie robimy - obecny koszt i poziom zaglebienia przekazany jako argument
  konczymy szukanie jak dotrzemy do ostatniego wiersza i postawimy
  wtedy sprawdzamy koszt i ewentualnie aktualizujemy zapis

  ustawiamy namiot w pierwszym niezajetym miejscu
  albo stawiamy i oznaczamy zablokowane miejsca w np dodatkowej tablicy
  potem stawiamy dopiero na wolnym miejscu itd
  na koncu sprawdzamy kwote i dalej
  cofamy sie o jeden i oblokowujemy miejsce w drugiej tablicy
  i tak az mozemy postawic inaczzej namiot
  przerywamy jak nie da sie postawic lub jest juz drozej w danej chwili
*/

inline void remove_one(int **taken, int size, int row, int column) {
  //zwolnienie miejsca
  taken[row][column]--;

  //w pionie
  for(int i=0;i<size;++i) {
    if(i != row) {
      taken[i][column]--;
    }
  }

  //w poziomie
  for(int i=0;i<size;++i) {
    if(i != column) {
      taken[row][i]--;
    }
  }

  //na ukos - z lewej gora
  //w dol od punktu
  for(int i=0;i<size;++i) {
    if(row + 1 + i == size) {
      break;
    } else if(column + 1 + i == size) {
      break;
    } else {
      taken[row + 1 + i][column + 1 + i]--;
    }
  }
  //w gore od punktu
  for(int i=0;i<size;++i) {
    if(row - 1 - i == -1) {
      break;
    } else if(column - 1 - i == -1) {
      break;
    } else {
      taken[row - 1 - i][column - 1 - i]--;
    }
  }

  //na ukos - z prawej gora
  //w dol od punktu
  for(int i=0;i<size;++i) {
    if(row + 1 + i == size) {
      break;
    } else if(column - 1 - i == -1) {
      break;
    } else {
      taken[row + 1 + i][column - 1 - i]--;
    }
  }
  //w gore od punktu
  for(int i=0;i<size;++i) {
    if(row - 1 - i == -1) {
      break;
    } else if(column + 1 + i == size) {
      break;
    } else {
      taken[row - 1 - i][column + 1 + i]--;
    }
  }
}

inline void take_place(int **taken, int size, int row, int column) {
  //zajecie miejsca i poblokowanie "szachowanych" linii
  taken[row][column]++;
  //w pionie
  for(int i=0;i<size;++i) {
    if(i != row) {
      taken[i][column]++;
    }
  }

  //w poziomie
  for(int i=0;i<size;++i) {
    if(i != column) {
      taken[row][i]++;
    }
  }

  //na ukos - z lewej gora
  //w dol od punktu
  for(int i=0;i<size;++i) {
    if(row + 1 + i == size) {
      break;
    } else if(column + 1 + i == size) {
      break;
    } else {
      taken[row + 1 + i][column + 1 + i]++;
    }
  }
  //w gore od punktu
  for(int i=0;i<size;++i) {
    if(row - 1 - i == -1) {
      break;
    } else if(column - 1 - i == -1) {
      break;
    } else {
      taken[row - 1 - i][column - 1 - i]++;
    }
  }

  //na ukos - z prawej gora
  //w dol od punktu
  for(int i=0;i<size;++i) {
    if(row + 1 + i == size) {
      break;
    } else if(column - 1 - i == -1) {
      break;
    } else {
      taken[row + 1 + i][column - 1 - i]++;
    }
  }
  //w gore od punktu
  for(int i=0;i<size;++i) {
    if(row - 1 - i == -1) {
      break;
    } else if(column + 1 + i == size) {
      break;
    } else {
      taken[row - 1 - i][column + 1 + i]++;
    }
  }
}

bool set_camp(int **costs, int size, int **taken, int *anwser, int *min_cost, int *current_cost, int row, int *final_anwser) {
  //przejscie calego wiersza
  for(int column=0;column<size;++column) {
    //jak znajdzie wolne miejsce
    if(taken[row][column] == 0) {
      //zapis wartosci pola
      *current_cost += costs[row][column];

      //jezeli juz przekracza minimalny koszt
      if(*current_cost > *min_cost) {
        *current_cost -= costs[row][column];
        //przejscie do dalszego szukania w wierszu
        continue;
      }

      //zajmuje miejsce na planszy
      take_place(taken,size,row,column);

      //zapis do tablicy odpowiedzi
      anwser[row] = column;

      //jak ostatni wiersz to zwroci do sprawdzenia czy jest lepsze
      if(row == size - 1) {
        //jezeli jest lepsze niz poprzednia najlepsza odpowiedz
        if(*current_cost < *min_cost) {
          *min_cost = *current_cost;
          for(int i=0;i<size;++i) {
            final_anwser[i] = anwser[i];
          }
        }
        //usuniecie ostatniego elementu do pelnego sprawdzenia nastepnego obrotu petli dla wyzszego wiersza
        remove_one(taken,size,row,column);
        *current_cost -= costs[row][column];
        return true;
      }
      //inaczej idzie dalej
      if(set_camp(costs,size,taken,anwser,min_cost,current_cost,row+1,final_anwser)) {
        bool found_more = false;
        //usuniecie aktualnego elementu - jak znalazlo juz element nizej to ten if sie wykonuje,
        //wiec zeby ewentualnie sprawdzic dalsza czesc wiersza czy nie ma lepszej konfiguracji to czyscimy ten wiersz
        remove_one(taken,size,row,column);
        *current_cost -= costs[row][column];
        //sprawdzamy od nastepnego elementu w wierszu czy istnieje inna konfiguracja
        for(int i=column+1;i<size;++i) {
          //istnieje
          if(taken[row][i] == 0) {
            found_more = true;
            break;
          }
        }
        //jak istnieje to nastepny obrot petli dla tego wiersza - szukanie dalszego "startu"
        if(found_more) {
          continue;
        }
        //info ze to ostatnia mozliwa konfiguracja w wierszu i udalo sie wstawic
        return true;
        //jak nizej sie nie da wstawic
      } else {
        //usuniecie tego elementu - bo szuka dalej w tym samym wierszu
        remove_one(taken,size,row,column);
        *current_cost -= costs[row][column];
      }
    }
  }
  return false;
}

inline void find_best_campsites(int **costs, int size) {
  //tablica tymczasowych odpowiedzi
  int *anwser = new int[size];
  //tablica ostatecznych odpowiedzi
  int *final_anwser = new int[size];
  //tablica zajetych miejsc - liczba naraz szachujacych pol
  int **taken = new int*[size];
  //minimalny koszt do tej pory
  int min_cost = 2147483647;  //max inta
  //aktualny sprawdzany koszt
  int current_cost = 0;
  //aktualny wiersz
  int row = 0;
  
  //przygotowanie tablicy zajetych miejsc
  for(int i=0;i<size;++i) {
    taken[i] = new int[size];
    for(int j=0;j<size;++j) {
      taken[i][j] = 0;
    }
  }
  
  //rozpoczecie rekurencyjnego szukania
  set_camp(costs,size,taken,anwser,&min_cost,&current_cost,row,final_anwser);
  
  //wyjscie
  for(int i=0;i<size;++i) {
    cout<<final_anwser[i]<<" ";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  int n;    //liczba obozow
  int **a;  //plansza obozow z kosztami budowy
  cin>>n;

  //stworzenie tablicy kosztow
  a = new int*[n];
  for(int i=0;i<n;++i) {
    a[i] = new int[n];
  }

  //wpisanie danych
  for(int i=0;i<n;++i) {
    for(int j=0;j<n;++j) {
      cin>>a[i][j];
    }
  }

  //szukanie najlepszej konfigruacji obozow
  find_best_campsites(a,n);

  return 0;
}