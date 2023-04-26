#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned int uint;

/*
  dokladnie jak algorytm piatek
  dzielimy na el mniejsze rowne i wieksze - rekurencyjnie
  k trzeba adekwatnie zmieniac jak wybralismy tablice dalsza niz B

  szukanie mediany:
  dzilimy tablice na zbiory po 5 elementow - MOZNA POSORTOWAC I ZWROCIC SRODKOWY ELEMENT JAKO MEDIANE!!!
  a potem tak samo z tablica median
  
  wazne:
  nie tworzyc malych tablic ale dzialac na indeksach - nawet do median itp
  przekazywac referencje do funkcji, a nie kopie

*/

struct Person {
  uint id;
  string first_name;
  string last_name;
  char group;

  Person(){}
  Person(uint id, string first_name, string last_name) {
    this->id = id;
    this->first_name = first_name;
    this->last_name = last_name;
  }
};

bool people_comparator(Person* &a, Person* &b) {
  if(a->id == b->id) {
    if(a->last_name.compare(b->last_name) == 0) {
      return a->first_name.compare(b->first_name) < 0;
    }
    return a->last_name.compare(b->last_name) < 0;
  }
  return a->id < b->id;
}

bool group_comparator(Person* &a, Person* &b) {
  return a->group < b->group;
}

inline uint find_median(Person*** people, uint start, uint end) {
  sort((*people) + start,(*people) + end,people_comparator);
  return (start + end) / 2;
}

inline void find_element(Person*** people, uint start, uint end, uint* k) {
  uint size = end - start;
  if(size <= 10) {
    sort((*people) + start,(*people) + end,people_comparator);
    *k += start;
    cout<<(*people)[*k]->first_name<<"\n"<<(*people)[*k]->last_name<<"\n"<<(*people)[*k]->id<<"\n";
    return;
  }

  //liczba podlist
  uint arr_count = size / 5;
  uint last_size = size % 5;
  if(last_size != 0) {
    arr_count++;
  }

  //znalezienie mediany median
  uint median_index = start;
  Person* median_person;
  uint index;
  for(uint i=0;i<arr_count - 1;++i) {
    index = find_median(people,start + (i*5),start + ((i+1)*5));
    median_person = (*people)[index];
    (*people)[index] = (*people)[median_index];
    (*people)[median_index] = median_person;
    ++median_index;
  }
  index = find_median(people,start + ((arr_count - 1) * 5), start + (((arr_count - 1) * 5) + last_size));
  median_person = (*people)[index];
  (*people)[index] = (*people)[median_index];
  (*people)[median_index] = median_person;
  ++median_index;
  median_person = (*people)[find_median(people,start,median_index)];

  //podzial na tablice B, C i D ~ ustawienie w dobrej kolejnosci w orginalnym segmencie
  uint B_end = 0, C_end = 0;

  for(int i=start;i<end;++i) {
    if((*people)[i]->id == median_person->id && (*people)[i]->last_name == median_person->last_name && (*people)[i]->first_name == median_person->first_name) {
      (*people)[i]->group = 'C';
      ++C_end;
    } else if(people_comparator((*people)[i],median_person)) {
      (*people)[i]->group = 'B';
      ++B_end; 
    } else {
      (*people)[i]->group = 'D';
    }
  }

  sort((*people) + start, (*people) + end,group_comparator);

  if(*k <= B_end) {
    find_element(people,start,start + B_end,k);
  } else if(*k > B_end && *k <= (B_end + C_end)) {
    cout<<median_person->first_name<<"\n"<<median_person->last_name<<"\n"<<median_person->id<<"\n";
    return;
  } else {
    *k -= (B_end + C_end);
    find_element(people,start+ B_end + C_end,end,k);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  uint n; //liczba wnioskow
  uint k; //wylosowana liczba - numer szukanego wniosku
  string first_name, last_name;
  uint id;
  Person** people;

  cin>>n>>k;
  people = new Person*[n];

  for(int i=0;i<n;++i) {
    cin>>first_name>>last_name>>id;
    people[i] = new Person(id,first_name,last_name); 
  }

  find_element(&people,0,n,&k);
  
  return 0;
}