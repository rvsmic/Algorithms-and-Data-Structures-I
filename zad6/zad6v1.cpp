#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned short ushort;

/*
  ZAMIENIC BABELKOWE NA SZYBSZE
  ZAMIENIC SPOSOB SZUKANIA POTEM LUDZI POZOSTALYCH
  SZUKAC ZBEDNYCH PETLI BO ICH SPORO CHB
  ????
*/

struct Warrior {
  ushort id;
  ushort x,y;
  ushort power;

  Warrior(){}
  Warrior(ushort id, ushort x, ushort y, ushort power) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->power = power;
  }
};

vector <Warrior*> sort_by_x(vector <Warrior*> warriors) {
    for(int i=0;i<warriors.size();i++) {
        for(int j=1;j<warriors.size();j++) {
            if(warriors[j-1]->x > warriors[j]->x) {
                swap(warriors[j-1],warriors[j]);
            }
        }
    }
    return warriors;
}

// void merge_by_x(vector <Warrior*> warriors, ushort start, ushort middle, ushort end) {
//   vector <Warrior*> left(warriors.at,warriors.begin() + middle);
//   vector <Warrior*> right(warriors.begin() + middle, warriors.end());
//   ushort i=0,j=0,k=start;
//   while(i < left.size() && j < right.size()) {
//     if(left[i]->x <= right[j]->x) {
//       warriors[k] = left[i];
//       i++;
//     } else {
//       warriors[k] = right[j];
//       j++;
//     }
//     k++;
//   }

//   while(i < left.size()) {
//     warriors[k] = left[i];
//     i++; k++;
//   }
//   while(j < right.size()) {
//     warriors[k] = right[j];
//     j++; k++;
//   }
// }

// void mergesort_by_x(vector <Warrior*> warriors, ushort start, ushort end) {
//   if(start > end) {
//     return;
//   }
//   ushort middle = warriors.size() / 2;
//   mergesort_by_x(warriors,start,middle);
//   mergesort_by_x(warriors,middle+1,end);
//   merge_by_x(warriors,start,middle,end);
// }

float calculate_distance(Warrior* first, Warrior* second) {
  float a = abs(first->x - second->x);
  float b = abs(first->y - second->y);
  return sqrt(pow(a,2) + pow(b,2));
}

//testowe
void print_warriors(vector <Warrior*> warriors) {
    cout<<"^^^\n";
    for(int i=0;i<warriors.size();i++) {
        cout<<"id: "<<warriors[i]->id<<" x:"<<warriors[i]->x<<" y:"<<warriors[i]->y<<" power:"<<warriors[i]->power<<"\n";
    }
    cout<<"___\n";
}

void check_distance_conditions(float distance, float *min_distance, Warrior* first_person, Warrior* second_person, pair <Warrior*,Warrior*> *fighters) {
  if(distance < *min_distance) {
      //cout<<"NEW ROUTE: "<<distance<<"\n";
      *min_distance = distance;
      //zawsze w first jest ten o mniejszym numerku
      if(first_person->id < second_person->id) {
        fighters->first = first_person;
        fighters->second = second_person;
      } else {
        fighters->first = second_person;
        fighters->second = first_person;
      }

      //jezeli sa w takiej samej odleglosci jak inna para
    } else if(distance == *min_distance) {
      //cout<<"SAME ROUTE: "<<distance<<"\n";
      //ustawiamy aktualna pare rosnaco id
      Warrior *smaller_id, *larger_id;
      if(first_person->id < second_person->id) {
        smaller_id = first_person;
        larger_id = second_person;
      } else {
        smaller_id = second_person;
        larger_id = first_person;
      }

      //jezeli mniejszy indeks z aktualnej pary jest mniejszy od firsta to zmieniamy cala pare walczaca
      if(smaller_id->id < fighters->first->id) {
        fighters->first = smaller_id;
        fighters->second = larger_id;
        //jezeli mniejszy indeks jest rowny firstowi to sprawdzamy seconda
      } else if(smaller_id->id == fighters->first->id && larger_id->id < fighters->second->id) {
        fighters->first = smaller_id;
        fighters->second = larger_id;
      }
    }
}

//podzial na pary
void divide(vector <Warrior*> warriors, ushort start, ushort end, float *min_distance, pair <Warrior*,Warrior*> *fighters) {
  //rozwazany przedzial ->  <start,end)
  
  //jak juz zostanie para lub pojedynczy
  if(end - start < 2) {
    return;
  }
  //bedzie po lewej ewentualny pojedynczy
  //lewa strona
  divide(warriors,start,(start+end)/2,min_distance,fighters);
  //prawa strona
  divide(warriors,(start+end)/2,end,min_distance,fighters);
  
  float distance;
  //jezeli jest jeden
  if(end - start == 1) {
    distance = INFINITY;

    //jezeli sa dwa
  } else if(end - start == 2) {
    distance = calculate_distance(warriors[start],warriors[end-1]);
    check_distance_conditions(distance,min_distance,warriors[start],warriors[end-1],fighters);

    //jezeli sa najblizej siebie do tej pory
    // if(distance < *min_distance) {
    //   cout<<"NEW ROUTE: "<<distance<<"\n";
    //   *min_distance = distance;
    //   //zawsze w first jest ten o mniejszym numerku
    //   if(warriors[start]->id < warriors[end-1]->id) {
    //     fighters->first = warriors[start];
    //     fighters->second = warriors[end-1];
    //   } else {
    //     fighters->first = warriors[end-1];
    //     fighters->second = warriors[start];
    //   }

    //   //jezeli sa w takiej samej odleglosci jak inna para
    // } else if(distance == *min_distance) {
    //   cout<<"SAME ROUTE: "<<distance<<"\n";
    //   //ustawiamy aktualna pare rosnaco id
    //   Warrior *smaller_id, *larger_id;
    //   if(warriors[start]->id < warriors[end-1]->id) {
    //     smaller_id = warriors[start];
    //     larger_id = warriors[end-1];
    //   } else {
    //     smaller_id = warriors[end-1];
    //     larger_id = warriors[start];
    //   }

    //   //jezeli mniejszy indeks z aktualnej pary jest mniejszy od firsta to zmieniamy cala pare walczaca
    //   if(smaller_id->id < fighters->first->id) {
    //     fighters->first = smaller_id;
    //     fighters->second = larger_id;
    //     //jezeli mniejszy indeks jest rowny firstowi to sprawdzamy seconda
    //   } else if(smaller_id->id == fighters->first->id && larger_id->id < fighters->second->id) {
    //     fighters->first = smaller_id;
    //     fighters->second = larger_id;
    //   }
    // }

    //jezeli jest wiecej ~ juz na nizszych poziomach
  } else {
    //znalezienie "linii srodkowej" w okolicy ktorej moze byc niesprawdzona para
    float middle_x;
    //jezeli nieparzysta liczba osob
    //cout<<"END-START= "<<end<<" "<<start<<"\n";
    if((end - start) & 1) {
      middle_x = warriors[(start+end-1)/2]->x;
      //jezeli parzysta liczba osob
    } else {
      middle_x = float(float(float(warriors[(start + end-1) / 2]->x) + float(warriors[((start + end-1) / 2) + 1]->x)) / 2);
      //cout<<"MID_X: "<<middle_x<<"\n";
      //cout<<"1: "<<warriors[(start + end-1) / 2]->x<<" 2: "<<warriors[((start + end-1) / 2) + 1]->x<<"\n";
    }
    vector <Warrior*> in_range_warriors;
    for(int i=0;i<warriors.size();++i) {
      if(abs((float(warriors[i]->x) - middle_x)) <= *min_distance) {
        //cout<<"A?-"<<abs(float(warriors[i]->x) - middle_x)<<"\n";
        in_range_warriors.push_back(warriors[i]);
      }
    }

    for(int i=0;i<in_range_warriors.size();++i) {
      for(int j=i+1;j<in_range_warriors.size();++j) {
        float dist = calculate_distance(in_range_warriors[i],in_range_warriors[j]);
        check_distance_conditions(dist,min_distance,in_range_warriors[i],in_range_warriors[j],fighters);
      }
    }

    //cout<<"IN RANGE\n";
    //print_warriors(in_range_warriors);

    //ZAPETLA SIE W NIESKONCZONOSC
    //divide(in_range_warriors,0,in_range_warriors.size(),min_distance,fighters);

    in_range_warriors.clear();
  }
}

vector <Warrior*> fight(vector <Warrior*> warriors) {
  float min_distance = INFINITY;
  pair <Warrior*,Warrior*> fighters;
  //szukanie najmniejszej odleglosci
  divide(warriors,0,warriors.size(),&min_distance,&fighters);

  Warrior *first = fighters.first, *second = fighters.second;
  //cout<<"F: "<<first->id<<" S: "<<second->id<<'\n';

  //sprawdzenie kto wygral, wyswietlenie i usuniecie z walczacych
  if(first->power > second->power) {
    cout<<second->x<<" "<<second->y<<"\n";
    warriors.erase(find(warriors.begin(),warriors.end(),second));
  } else if(first->power < second->power) {
    cout<<first->x<<" "<<first->y<<"\n";
    warriors.erase(find(warriors.begin(),warriors.end(),first));
  } else {
    if(first->id < second->id) {
      cout<<second->x<<" "<<second->y<<"\n";
      warriors.erase(find(warriors.begin(),warriors.end(),second));
    } else {
      cout<<first->x<<" "<<first->y<<"\n";
      warriors.erase(find(warriors.begin(),warriors.end(),first));
    }
  }
  //zwrocenie zmniejszonej tablicy wojownikow
  return warriors;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  ushort n,t; //liczba wojownikow, liczba walk
  ushort x,y,w; //koordynaty osoby, moc osoby
  
  cin>>n>>t;

  vector <Warrior*> warriors;

  for(int i=0;i<n;++i) {
    cin>>x>>y>>w;
    warriors.push_back(new Warrior(i,x,y,w));
  }
  
  //print_warriors(warriors);
  warriors = sort_by_x(warriors);
  //print_warriors(warriors);

  for(int i=0;i<t;++i) {
    warriors = fight(warriors);
    //print_warriors(warriors);
  }

  return 0;
}