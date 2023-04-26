#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned short ushort;
typedef unsigned int uint;


void print_arr(uint **arr, ushort team_count, string text) {
  cout<<text<<":\n";
  for(int i=0;i<team_count+1;++i) {
    for(int j=0;j<team_count;++j) {
      cout<<arr[i][j]<<"\t";
    }
    cout<<endl;
  }
}

uint max_in_row(uint* row, ushort row_size) {
  uint mx = 0;
  for(int i=0;i<row_size;++i) {
    if(row[i] > mx) {
      mx = row[i];
    }
  }
  return mx;
}

void update_result(uint *original_order, uint **result_arr, uint **old_arr, ushort team_count, int current_person_index) {
  //wyzerowanie pierwszego wiersza result
  for(int i=0;i<team_count;++i) {
    result_arr[0][i] = 0;
  }
  
  //LEWA STRONA OD AKTUALNEJ DRUZYNY
  for(int i=1;i<team_count+1;++i) {
    //kopiujemy wiersze ze starej do nowej z przesunieciem ~ np. old[0] = result[1]
    //result_arr[i] = old_arr[i-1];
    copy(*(old_arr + i - 1),*(old_arr + i - 1) + team_count + 1,*(result_arr + i));

    //zwiekszenie wartosci o odpowiadajace wartosci druzyny z kolumny
    for(int j=0;j<team_count;++j) {
      if(result_arr[i][j] > 0) {
        result_arr[i][j] += original_order[j];
      }
    }
  }

  //print_arr(result_arr,team_count,"result_new");
  
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
      if(i == j + 1) {
        if(result_arr[i][j] < original_order[j]) {
          result_arr[i][j] = original_order[j];
        } else {
          continue;
        }
      } else {
        max_from_row = max_in_row(old_arr[i-(j-current_person_index)],team_count) + original_order[j];
        //cout<<"OLD_ROW: ";
        //for(int k=0;k<team_count;k++) {
          //cout<<old_arr[j-current_person_index][k]<<" ";
        //}cout<<endl;
        //cout<<"MAX:"<<max_from_row<<"\n";
        if(result_arr[i][j] < max_from_row) {
          result_arr[i][j] = max_from_row;
        }
      }
      
    }
  }
  
  //zapisanie do starej
  for(int i=0;i<team_count+1;++i) {
    copy(*(result_arr + i),*(result_arr + i) + team_count + 1,*(old_arr+i));
  }
}

uint max_result(uint *original_order, ushort team_count) {
  uint **result_arr;
  uint **old_arr;

  //n+1 wierszy bo patrzymy tez na 0 przejsc
  result_arr = new uint*[team_count+1];
  old_arr = new uint*[team_count+1];

  //n kolumn w kazdym wierszu
  for(int i=0;i<team_count+1;++i) {
    result_arr[i] = new uint[team_count];
    old_arr[i] = new uint[team_count];
  }

  //przejscie soltysa i ewentualne zamiany
  for(int i=0;i<team_count;++i) {
    update_result(original_order,result_arr,old_arr,team_count,i);
    //print_arr(result_arr,team_count,"result");
    //print_arr(old_arr,team_count,"old");
  }

  //prawy dolny rog tablicy
  return result_arr[team_count][team_count-1];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  ushort n;         //liczba zespolow
  uint *a;          //wyniki zespolow
  cin>>n;
  a = new uint[n];
  for(int i=0;i<n;++i) {
    cin>>a[i];
  }

  cout<<max_result(a,n)<<"\n";

  return 0;
}