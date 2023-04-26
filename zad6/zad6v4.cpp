#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned short ushort;

//cos nie dziala :(

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

//comparatory dla funkcji sortowania
bool sort_by_x(Warrior* a, Warrior* b) {
    return a->x < b->x;
}

bool sort_by_y(Warrior* a, Warrior* b) {
  return a->y < b->y;
}

//obliczanie dystansu miedzy dwoma danymi osobami
float calculate_distance(Warrior* first, Warrior* second) {
  float a = first->x - second->x;
  float b = first->y - second->y;
  return sqrt(a*a + b*b);
}

//sprawdzenie czy podany dystans jest mniejszy lub rowny aktualnie najkrotszemu i ewentualna zmiana wojownikow
void check_distance_conditions(float distance, float *min_distance, Warrior* first_person, Warrior* second_person, pair <Warrior*,Warrior*> *fighters) {
  if(distance < *min_distance) {
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

void find_closest(vector <Warrior*> warriors, ushort start, ushort end, float *min_distance, pair <Warrior*,Warrior*> *fighters) {
  float distance;
  //jezeli jest jeden
  if(end - start == 1) {
    return;

    //jezeli sa dwa
  } else if(end - start == 2) {
    distance = calculate_distance(warriors[start],warriors[end-1]);
    check_distance_conditions(distance,min_distance,warriors[start],warriors[end-1],fighters);

    //jezeli jest wiecej ~ juz na nizszych poziomach
  } else {
    //znalezienie "linii srodkowej" w okolicy ktorej moze byc niesprawdzona para
    float middle_x;

    //jezeli nieparzysta liczba osob
    if((end - start) & 1) {
      //x osoby na srodku
      middle_x = warriors[(start+end-1)/2]->x;

      //jezeli parzysta liczba osob
    } else {
      //x miedzy osobami ze srodka
      middle_x = float(float(float(warriors[(start + end-1) / 2]->x) + float(warriors[((start + end-1) / 2) + 1]->x)) / 2);
    }
    
    //osoby ktore sa w odlegosci mniejszej lub rownej min_distance od linii srodkowej ~ dla upewnienia czy znalezlismy na pewno najblizsza pare
    vector <Warrior*> in_range_warriors;

    //szukanie takich osob - tylko sposrod tych na obecnym poziomie (bo i tak wyzej reszta zostanie sprawdzona)
    for(int i=start;i<end;++i) {
      if(abs((float(warriors[i]->x) - middle_x)) <= *min_distance) {
        in_range_warriors.push_back(warriors[i]);
      }
    }

    if(in_range_warriors.size() > 1) {
      //sortowanie po y ??????
      sort(in_range_warriors.begin(),in_range_warriors.end(),sort_by_y);

      //iteracja przez znalezione osoby i sprawdzenie czy sa blizej siebie niz najlepsza znaleziona para
      short same_y_start_index = -1;
      for(int i=0;i<in_range_warriors.size()-1;++i) {
        if(in_range_warriors[i]->y == in_range_warriors[i+1]->y) {
          if(same_y_start_index == -1) {
            same_y_start_index = i;
          }
        } else {
          if(same_y_start_index > -1) {
            for(int j=same_y_start_index;j<i+1;++j) {
              float dist = calculate_distance(in_range_warriors[j],in_range_warriors[i+1]);
              check_distance_conditions(dist,min_distance,in_range_warriors[j],in_range_warriors[i+1],fighters);
            }
            same_y_start_index = -1;
          }
        }
        float dist = calculate_distance(in_range_warriors[i],in_range_warriors[i+1]);
        check_distance_conditions(dist,min_distance,in_range_warriors[i],in_range_warriors[i+1],fighters);
      }
    }

    //zwolnienie pamieci
    in_range_warriors.clear();
  }
}

//podzial na pary, a nastepnie szukanie najkrotszego dystansu i wojownikow do walki
void divide(vector <Warrior*> warriors, ushort start, ushort end, float *min_distance, pair <Warrior*,Warrior*> *fighters) {
  //rozwazany przedzial ->  <start,end)
  
  //jak juz zostanie para lub pojedynczy
  if(end - start < 2) {
    return;
  }

  //podzial robiony w taki sposob ze po lewej zawsze wystapi ewentualny pojedynczy wojownik
  
  //lewa strona
  divide(warriors,start,(start+end)/2,min_distance,fighters);
  //prawa strona
  divide(warriors,(start+end)/2,end,min_distance,fighters);
  //sprawdzanie na podzielonych juz tablicach
  find_closest(warriors,start,end,min_distance,fighters);

}

//szukanie przegranego w parze najblizszej sobie
vector <Warrior*> fight(vector <Warrior*> warriors) {
  //minimalny dystans nieskonczony zeby znalezc jakas pare
  float min_distance = INFINITY;
  //para wojownikow najblizszych sobie
  pair <Warrior*,Warrior*> fighters;
  //szukanie "najlepszych" osob do walki
  divide(warriors,0,warriors.size(),&min_distance,&fighters);

  //pierwsza i druga osoba z walczacej pary
  Warrior *first = fighters.first, *second = fighters.second;

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

  //tablica wojownikow
  vector <Warrior*> warriors;

  //wpisanie i "utworzenie" wojownikow
  for(int i=0;i<n;++i) {
    cin>>x>>y>>w;
    warriors.push_back(new Warrior(i,x,y,w));
  }
  
  //posortowanie wojownikow po x - zlozonosc nlogn
  sort(warriors.begin(),warriors.end(),sort_by_x);

  //odbycie t walk i wyswietlenie poleglych
  for(int i=0;i<t;++i) {
    warriors = fight(warriors);
  }

  return 0;
}