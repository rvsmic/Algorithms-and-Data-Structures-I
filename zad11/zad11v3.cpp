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

bool people_comparator(Person* a, Person* b) {
  if(a->id == b->id) {
    if(a->last_name.compare(b->last_name) == 0) {
      return a->first_name.compare(b->first_name) < 0;
    }
    return a->last_name.compare(b->last_name) < 0;
  }
  return a->id < b->id;
}

bool group_comparator(Person* a, Person* b) {
  return a->group < b->group;
}

//test
void print_people(Person** people, uint start, uint end, string text) {
  cout<<text<<":\n";
  for(int i=start;i<end;++i) {
    cout<<people[i]->id<<" "<<people[i]->last_name<<" "<<people[i]->first_name<<endl;
  }
}

uint find_median(Person** people, uint start, uint end) {
  sort(people + start,people + end,people_comparator);
  return (start + end) / 2;
}

void find_element(Person** people, uint start, uint end, uint* k) {
  
  // cout<<endl<<"For people: "<<start<<" - "<<end;
  // print_people(people,start,end,"");
  // cout<<endl;

  uint size = end - start;
  if(size <= 10) {
    // cout<<"list <= 10"<<endl;
    sort(people + start,people + end,people_comparator);
    // print_people(people,start,end - start,"Sorted");
    *k += start;
    cout<<people[*k]->first_name<<"\n"<<people[*k]->last_name<<"\n"<<people[*k]->id<<"\n";
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
    median_person = people[index];
    people[index] = people[median_index];
    people[median_index] = median_person;
    ++median_index;
  }
  index = find_median(people,start + ((arr_count - 1) * 5), start + (((arr_count - 1) * 5) + last_size));
  median_person = people[index];
  people[index] = people[median_index];
  people[median_index] = median_person;
  ++median_index;
  // cout<<"arr count= "<<arr_count<<" k= "<<*k<<endl;
  // print_people(people_medians,0,arr_count,"Median people");
  median_person = people[find_median(people,start,median_index)];

  // cout<<"MEDIAN: "<<median_person->id<<" "<<median_person->first_name<<" "<<median_person->last_name<<endl;

  //podzial na tablice B, C i D ~ ustawienie w dobrej kolejnosci w orginalnym segmencie
  uint B_end = 0, C_end = 0, D_end = 0;

  for(int i=start;i<end;++i) {
    if(people[i]->id == median_person->id && people[i]->last_name == median_person->last_name && people[i]->first_name == median_person->first_name) {
      people[i]->group = 'C';
      ++C_end;
    } else if(people_comparator(people[i],median_person)) {
      people[i]->group = 'B';
      ++B_end; 
    } else {
      people[i]->group = 'D';
      ++D_end;
    }
  }

  // cout<<"B:"<<B_end<<" C:"<<C_end<<" D:"<<D_end<<endl;
  sort(people + start, people + end,group_comparator);

  // print_people(people,start,B_end,"People for B");
  // print_people(people,B_end,B_end + C_end,"People for C");
  // print_people(people,B_end + C_end,B_end + C_end + D_end,"People for D");

  if(*k <= B_end) {
    // cout<<"find in B"<<endl;
    find_element(people,start,start + B_end,k);
  } else if(*k > B_end && *k <= (B_end + C_end)) {
    // cout<<"found median"<<endl;
    cout<<median_person->first_name<<"\n"<<median_person->last_name<<"\n"<<median_person->id<<"\n";
    return;
  } else {
    // cout<<"find in D"<<endl;
    *k -= (B_end + C_end);
    // cout<<"new k="<<*k<<endl;
    // cout<<"D end:"<<D_end<<" C end: "<<C_end<<endl;
    find_element(people,start+ B_end + C_end,start + B_end + C_end + D_end,k);
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

  find_element(people,0,n,&k);
  
  return 0;
}