#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned short ushort;

/*
    najblizsze od siebie punkty walcza
    osoba z nizsza sila odpada z gry
    albo szukac za kazdym razem najblizszych sobie osobnikow - dziel i zwyciezaj
    wykonujemy algorytm dla najmniejszych danych - para osob
    jak jeden punkt to odleglosc nieskonczona (zwrocona z funkcji)
    jak wiecej punktow to dzielimy na lewa i prawa strone i wykonujemy osobno algorytm
    jak posortujemy dane po np x to podzial bedzie latwiejszy - sortowanie wzgledem x
    zwracamy min odleglosc z przypadku atomowego - najmniejszego
    jeszcze trzeba dodac operacje szukania odleglosci pomiedzy sasiadami rozdzielonymi podzialem

    przyklad
    posortowane wzgledem x
    0 i 2 ida do swojej tablicy a 1 i 3 do swojej
    wykonujemy algorytm i zwracamy odleglosc
    dla lewej strony pierwiastek z 5 a dla prawej wychodzi pierw z 40
    wybieramy mniejsza
    sprawdzamy punkt przeciecia - bierzemy srodkowe wartosci i wyliczamy linie srodkowa - u nas 2.5
    sprawdzamy czy od tej linii znajduje sie punkt w mniejszej odleglosci niz ta znaleziona wyzej
    np: 0 ma 1.5, 2 ma 0.5, 1 ma 0.5 wiec sie lapia do porownania
    wtedy sprawdzamy wszystkie znalezione pary czy maja mniejsza odleglosc niz ta znaleziona wczesniej - brute force - malo ich wiec nie wplynie specjalnie na szybkosc
    znajduje sie 0,2 najlepszy - sprawdzamy sile - 2 przegrywa wiec wypisujemy jego lokalizacje po czym usuwamy z planszy
    
    algortym sie ponawia na 3 punktach

    warto posortowac po wspolrzednej y jak juz patrzymy na odleglosc od narysowanej linii

    przy remisie mniejszy numer wygrywa

    t moze byc 0?
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

//Warrior, ale trzyma dodatkowo index w "oryginalnej" tablicy wojownikow - struktura uzywana do szukania przy linii z mniejsza iloscia osob
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
inline float calculate_distance(Warrior* first, Warrior* second) {
  float a = first->x - second->x;
  float b = first->y - second->y;
  return sqrt(a*a + b*b);
}

//sprawdzenie czy podany dystans jest mniejszy lub rowny aktualnie najkrotszemu i ewentualna zmiana indeksow wojownikow
inline void check_distance_conditions(vector <Warrior*> &warriors, float distance, float *min_distance, ushort first_person_i, ushort second_person_i, pair <ushort,ushort> *fighters_indexes) {
  if(distance < *min_distance) {
      *min_distance = distance;
      //zawsze w first jest ten o mniejszym numerku
      if(warriors[first_person_i]->id < warriors[second_person_i]->id) {
        fighters_indexes->first = first_person_i;
        fighters_indexes->second = second_person_i;
      } else {
        fighters_indexes->first = second_person_i;
        fighters_indexes->second = first_person_i;
      }

      //jezeli sa w takiej samej odleglosci jak inna para
    } else if(distance == *min_distance) {
      //ustawiamy aktualna pare rosnaco id
      ushort smaller_id_i, larger_id_i;
      if(warriors[first_person_i]->id < warriors[second_person_i]->id) {
        smaller_id_i = first_person_i;
        larger_id_i = second_person_i;
      } else {
        smaller_id_i = second_person_i;
        larger_id_i = first_person_i;
      }

      //jezeli id mniejszego indeksu z aktualnej pary jest mniejsze od id firsta to zmieniamy cala pare walczaca
      if(warriors[smaller_id_i]->id < warriors[fighters_indexes->first]->id) {
        fighters_indexes->first = smaller_id_i;
        fighters_indexes->second = larger_id_i;
        //jezeli id mniejszego indeksu jest rowny id firsta to sprawdzamy seconda
      } else if(warriors[smaller_id_i]->id == warriors[fighters_indexes->first]->id && warriors[larger_id_i]->id < warriors[fighters_indexes->second]->id) {
        fighters_indexes->first = smaller_id_i;
        fighters_indexes->second = larger_id_i;
      }
    }
}

//sprawdzenie czy podany dystans jest mniejszy lub rowny aktualnie najkrotszemu i ewentualna zmiana indeksow wojownikow - wersja dla linii - dla mniejszej grupy osob ktore trzymaja swoje "oryginalne" indeksy w sobie
inline void check_line_distance_conditions(vector <Warrior*> &warriors, vector <Indexed_Warrior*> &indexed_warriors, float distance, float *min_distance, ushort first_person_i, ushort second_person_i, pair <ushort,ushort> *fighters_indexes) {
  if(distance < *min_distance) {
    *min_distance = distance;
    //zawsze w first jest ten o mniejszym numerku
    if(indexed_warriors[first_person_i]->warrior->id < indexed_warriors[second_person_i]->warrior->id) {
      fighters_indexes->first = indexed_warriors[first_person_i]->index;
      fighters_indexes->second = indexed_warriors[second_person_i]->index;
    } else {
      fighters_indexes->first = indexed_warriors[second_person_i]->index;
      fighters_indexes->second = indexed_warriors[first_person_i]->index;
    }

      //jezeli sa w takiej samej odleglosci jak inna para
  } else if(distance == *min_distance) {
    //ustawiamy aktualna pare rosnaco id
    ushort smaller_id_i, larger_id_i;
    if(indexed_warriors[first_person_i]->warrior->id < indexed_warriors[second_person_i]->warrior->id) {
      smaller_id_i = first_person_i;
      larger_id_i = second_person_i;
    } else {
      smaller_id_i = second_person_i;
      larger_id_i = first_person_i;
    }

    //jezeli mniejszy indeks z aktualnej pary jest mniejszy od firsta to zmieniamy cala pare walczaca
    if(indexed_warriors[smaller_id_i]->warrior->id < warriors[fighters_indexes->first]->id) {
      fighters_indexes->first = indexed_warriors[smaller_id_i]->index;
      fighters_indexes->second = indexed_warriors[larger_id_i]->index;
      //jezeli mniejszy indeks jest rowny firstowi to sprawdzamy seconda
    } else if(indexed_warriors[smaller_id_i]->warrior->id == warriors[fighters_indexes->first]->id && indexed_warriors[larger_id_i]->warrior->id < warriors[fighters_indexes->second]->id) {
      fighters_indexes->first = indexed_warriors[smaller_id_i]->index;
      fighters_indexes->second = indexed_warriors[larger_id_i]->index;
    }
  }
}

//podzial na pary, a nastepnie szukanie najkrotszego dystansu i wojownikow do walki
inline void divide(vector <Warrior*> &warriors, ushort start, ushort end, float *min_distance, pair <ushort,ushort> *fighters_indexes) {
  //rozwazany przedzial ->  <start,end)
  //jezeli jest jeden walczacy
  if(end - start == 1) {
    return;

    //jezeli jest dwoch walczacych
  } else if(end - start == 2) {
    float distance = calculate_distance(warriors[start],warriors[end-1]);
    check_distance_conditions(warriors,distance,min_distance,start,end-1,fighters_indexes);

    //jezeli jest wiecej ~ juz na nizszych poziomach
  } else {
    //podzial robiony w taki sposob ze po lewej zawsze wystapi ewentualny pojedynczy wojownik
    //lewa strona
    divide(warriors,start,(start+end)/2,min_distance,fighters_indexes);
    //prawa strona
    divide(warriors,(start+end)/2,end,min_distance,fighters_indexes);

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
      if(fabs((float(warriors[i]->x) - middle_x)) <= *min_distance) {
        in_range_warriors.push_back(new Indexed_Warrior(i,warriors[i]));
      }
    }

    //sortowanie po y
    sort(in_range_warriors.begin(),in_range_warriors.end(),sort_by_y);

    //iteracja przez znalezione osoby i sprawdzenie czy sa blizej siebie niz najlepsza znaleziona para
    for(int i=0;i<in_range_warriors.size();++i) {
      for(int j=i+1;j<in_range_warriors.size();++j) {
        if(in_range_warriors[j]->warrior->y - in_range_warriors[i]->warrior->y <= *min_distance) {
            float dist = calculate_distance(in_range_warriors[i]->warrior,in_range_warriors[j]->warrior);
            check_line_distance_conditions(warriors,in_range_warriors,dist,min_distance,i,j,fighters_indexes);
        } else {
          //jezeli i osoba jest za daleko od j osoby to bedzie jedynie jeszcze dalej od nastepnych
          break;
        }
      }
    }

    //usuniecie z pamieci obiektow w tablicy
    for(int i=0;i<in_range_warriors.size();i++) {
        delete in_range_warriors[i];
    }

    //usuniecie tablicy z pamieci
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

  //pierwsza i druga osoba z walczacej pary
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

  ushort n,t;   //liczba wojownikow, liczba walk
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