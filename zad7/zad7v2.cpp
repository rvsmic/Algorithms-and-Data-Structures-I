#include <iostream>
using namespace std;
typedef unsigned int uint;
typedef unsigned short ushort;

void print_arr(uint **arr, ushort team_count, string text) {
  cout<<text<<":\n";
  for(int i=0;i<team_count+1;++i) {
    for(int j=0;j<team_count;++j) {
      cout<<arr[i][j]<<"\t";
    }
    cout<<endl;
  }
}

void update_prefixes(uint **prefixes, uint **results, ushort team_count) {
  uint row_max;
  for(int i=0;i<team_count+1;++i) {
    row_max = 0;
    for(int j=0;j<team_count;++j) {
      if(results[i][j] > row_max) {
        row_max = results[i][j];
      }
      if(row_max > prefixes[i][j]) {
        prefixes[i][j] = row_max;
      }
    }
  }
}

//inline
void move_teams(uint **results, uint **prefixes, uint *points, ushort team_count, ushort current_team_index) {
  //przesuniecie o jeden wiersz w dol i dodanie punktow druzyny z kolumny
  for(int i=team_count;i>0;--i) {
    for(int j=0;j<team_count;++j) {
      if(results[i-1][j] > 0) {
        results[i][j] = results[i-1][j] + points[j];
      }
    }
  }

  //wyzerowanie pierwszego wiersza
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
      if(i+current_team_index == j || i+current_team_index-1 == j) {
        //results[i][j] = prefixes[i-(j-current_team_index)][j-i+1] + points[j];
        results[i][j] = prefixes[i-(j-current_team_index)][j-1] + points[j];
      } else if(i==j) {
        uint temp = prefixes[i-1][j] + points[j];
        if(temp > results[i][j])
        results[i][j] = temp;
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
    //cout<<"n = "<<i+1<<"\n";
    //print_arr(results, team_count, "results");
    //print_arr(prefixes, team_count, "prefixes");
  }

  return results[team_count][team_count-1];
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