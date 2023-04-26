#include <iostream>
using namespace std;

/*
  kodowanie wartosci krabow i pulapek do jednej wspolnej wartosci do porownywania
  wzor: k - ilosc krabow, p - ilosc pulapek
  (k + 1) * 9 - (p - 1) = 9k + 9 - p + 1 = 9k - p + 10
  fragment tablicy kodowania:
    0  1   2   ...  97   98   99  -kraby
  1 9  18  27  ...  882  891  900
  2 8  17  26  ...  881  890  899
  3 7  16  25  ...  880  889  898
  4 6  15  24  ...  879  888  897
  5 5  14  23  ...  878  887  896
  6 4  13  22  ...  877  886  895
  7 3  12  21  ...  876  885  894
  8 2  11  20  ...  875  884  893
  9 1  10  19  ...  874  883  892
  ^pulapki

  dzieki takiemu kodowaniu mozna bez jakichkolwiek problemow uzyc algorytmu, poniewaz:
  jezeli A ma wiecej krabow od B to normalne porownanie
  tak samo w wypadku jak sa rowne bo wartosc maleje wraz z wzrostem ilosci pulapek
*/

struct Huntsman {
  char* name;
  short value; //obliczane wg wzoru wyzej

  Huntsman(){}
  Huntsman(char* name, short crabs, short traps) {
    this->name = name;
    value = ((9 * crabs) - traps) + 10;
  }
};

/*
  sortowanie liniowe wzgledem ilosci krabow - malejaco
  jak ilosc krabow taka sama to wzgledem ilosci pulapek - najpierw ten co ma mniej
  jak tyle samo to nie zmieniamy kolejnosci
*/
inline Huntsman *counting_sort(Huntsman *in, int size) {
  //posortowana tablica do zwrocenia
  Huntsman *out = new Huntsman[size];
  //tablica liczaca ilosc wystapien indeksu
  int *counter = new int[900];
  //wyzerowanie na start
  for(int i=0;i<900;++i) {
    counter[i] = 0;
  }

  //zliczanie wystapien wartosci indeksu
  for(int i=0;i<size;++i) {
    ++counter[in[i].value - 1];
  }

  //pierwszy sprawdzany element zmniejszamy o jeden
  --counter[899];

  //idziemy w dol bo chcemy kolejnosc malejaca - przy rosnacej trzeba "odwrocic" oba ponizsze fory
  //zmieniamy counter na przedzialy wystepowania wartosci w posortowanej tablicy - do powtorzen - counter[i] zawiera ilosc elementow <= i
  for(int i=898;i>=0;--i) {
    counter[i] = counter[i] + counter[i+1];
  }

  //przejscie od konca bo sortujemy malejaco a chcemy ewentualnie zachowac orginalna kolejnosc
  for(int i=size-1;i>=0;--i) {
    //do out na pozycji <ilosc elementow mniejszych od tego indeksu> zapisujemy wartosc z in z tego indeksu
    out[counter[in[i].value - 1]] = in[i];
    //zmniejszenie wartosci countera dla danej wartosci in jakby mialy byc powtorzenia - zmieni sie indeks dla out potem
    --counter[in[i].value - 1];
  }
  
  //zwrocenie posortowanej tablicy
  return out;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  int n;              //liczba mysliwych
  short k_i, p_i;     //liczba krabow, liczba pulapek
  char *name;         //imie mysliwego
  Huntsman *huntsmen; //tablica mysliwych
  cin>>n;
  huntsmen = new Huntsman[n];
  for(int i=0;i<n;++i) {
    name = new char[21];
    cin>>name>>k_i>>p_i;
    huntsmen[i] = Huntsman(name,k_i,p_i);
  }

  //posortowanie ze zlozonoscia O(n) !!!
  huntsmen = counting_sort(huntsmen,n);

  //wyswietlenie odpowiedzi
  for(int i=0;i<n;++i) {
    cout<<huntsmen[i].name<<" ";
  }
  return 0;
}