#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned short ushort;

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

struct Indexed_Warrior {
    ushort index;
    Warrior* warrior;
    Indexed_Warrior(){}
    Indexed_Warrior(ushort index, Warrior* warrior) {
        this->index = index;
        this->warrior = warrior;
    }
};

//comparatory dla funkcji sortowania
bool sort_by_x(Warrior* a, Warrior* b) {
    return a->x < b->x;
}

bool sort_by_y(Indexed_Warrior* a, Indexed_Warrior* b) {
  return a->warrior->y < b->warrior->y;
}

//obliczanie dystansu miedzy dwoma danymi osobami
float calculate_distance(Warrior* first, Warrior* second) {
  float a = abs(first->x - second->x);
  float b = abs(first->y - second->y);
  return sqrt(a*a + b*b);
}

//sprawdzenie czy podany dystans jest mniejszy lub rowny aktualnie najkrotszemu i ewentualna zmiana wojownikow
void check_distance_conditions(vector <Warrior*> warriors, float distance, float *min_distance, ushort first_person_index, ushort second_person_index, pair <ushort,ushort> *fighters) {
  if(distance < *min_distance) {
      *min_distance = distance;
      //zawsze w first jest ten o mniejszym numerku
      if(warriors[first_person_index]->id < warriors[second_person_index]->id) {
        fighters->first = first_person_index;
        fighters->second = second_person_index;
      } else {
        fighters->first = second_person_index;
        fighters->second = first_person_index;
      }

      //jezeli sa w takiej samej odleglosci jak inna para
    } else if(distance == *min_distance) {
      //ustawiamy aktualna pare rosnaco id
      ushort smaller_id_index, larger_id_index;
      if(warriors[first_person_index]->id < warriors[second_person_index]->id) {
        smaller_id_index = first_person_index;
        larger_id_index = second_person_index;
      } else {
        smaller_id_index = second_person_index;
        larger_id_index = first_person_index;
      }

      //jezeli mniejszy indeks z aktualnej pary jest mniejszy od firsta to zmieniamy cala pare walczaca
      if(warriors[smaller_id_index]->id < warriors[fighters->first]->id) {
        fighters->first = smaller_id_index;
        fighters->second = larger_id_index;
        //jezeli mniejszy indeks jest rowny firstowi to sprawdzamy seconda
      } else if(warriors[smaller_id_index]->id == warriors[fighters->first]->id && warriors[larger_id_index]->id < warriors[fighters->second]->id) {
        fighters->first =  smaller_id_index;
        fighters->second = larger_id_index;
      }
    }
}

void check_line_distance_conditions(vector <Warrior*> warriors, vector <Indexed_Warrior*> indexed_warriors, float distance, float *min_distance, ushort first_person_index, ushort second_person_index, pair <ushort,ushort> *fighters) {
  
}

//podzial na pary, a nastepnie szukanie najkrotszego dystansu i wojownikow do walki
void divide(vector <Warrior*> warriors, ushort start, ushort end, float *min_distance, pair <ushort,ushort> *fighters) {
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
  
  float distance;
  //jezeli jest jeden
  if(end - start == 1) {
    return;

    //jezeli sa dwa
  } else if(end - start == 2) {
    distance = calculate_distance(warriors[start],warriors[end-1]);
    check_distance_conditions(warriors,distance,min_distance,start,end-1,fighters);

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
    vector <Indexed_Warrior*> in_range_warriors;

    //szukanie takich osob - tylko sposrod tych na obecnym poziomie (bo i tak wyzej reszta zostanie sprawdzona)
    for(int i=start;i<end;++i) {
      if(abs((float(warriors[i]->x) - middle_x)) <= *min_distance) {
        in_range_warriors.push_back(new Indexed_Warrior(i,warriors[i]));
      }
    }

    //sortowanie po y ??????
    sort(in_range_warriors.begin(),in_range_warriors.end(),sort_by_y);

    //iteracja przez znalezione osoby i sprawdzenie czy sa blizej siebie niz najlepsza znaleziona para
    for(int i=0;i<in_range_warriors.size();++i) {
      for(int j=i+1;j<in_range_warriors.size();++j) {
        if(in_range_warriors[j]->warrior->y - in_range_warriors[i]->warrior->y <= *min_distance) {
            float dist = calculate_distance(in_range_warriors[i]->warrior,in_range_warriors[j]->warrior);
            check_line_distance_conditions(warriors,in_range_warriors,dist,min_distance,i,j,fighters);
        }
      }
    }

    //zwolnienie pamieci
    in_range_warriors.clear();
  }
}

//szukanie przegranego w parze najblizszej sobie
vector <Warrior*> fight(vector <Warrior*> warriors) {
  //minimalny dystans nieskonczony zeby znalezc jakas pare
  float min_distance = INFINITY;
  //para wojownikow najblizszych sobie
  pair <ushort,ushort> fighters_indexes;
  //szukanie "najlepszych" osob do walki
  divide(warriors,0,warriors.size(),&min_distance,&fighters_indexes);

  //indeksy pierwszej i drugiej osoby z walczacej pary
  ushort first = fighters_indexes.first, second = fighters_indexes.second;

  //sprawdzenie kto wygral, wyswietlenie i usuniecie z walczacych
  if(warriors[first]->power > warriors[second]->power) {
    cout<<warriors[second]->x<<" "<<warriors[second]->y<<"\n";
    warriors.erase(warriors.begin() + second);
  } else if(warriors[first]->power < warriors[second]->power) {
    cout<<warriors[first]->x<<" "<<warriors[first]->y<<"\n";
    warriors.erase(warriors.begin() + first);
  } else {
    if(warriors[first]->id < warriors[second]->id) {
      cout<<warriors[second]->x<<" "<<warriors[second]->y<<"\n";
      warriors.erase(warriors.begin() + second);
    } else {
      cout<<warriors[first]->x<<" "<<warriors[first]->y<<"\n";
      warriors.erase(warriors.begin() + first);
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