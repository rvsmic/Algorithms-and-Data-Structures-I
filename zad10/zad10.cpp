#include <iostream>
using namespace std;

/*
  wpisujemy elementy w kopiec
  dodajemy element na koniec - skrajny lisc i sprawdzamy czy to nadal spelnia warunki kopca - ewentualnie podmieniamy
  poki rodzic jest mniejszy to podmieniamy
  przy usunieciu operacji - usuwamy korzen i wrzucamy tam ostatni element z dolu po czym sprawdzamy wlasnosc kopca
  TO DO OPERACJI DLA MAXA - 1

  implementacja tablicowa - dostep do dziecka / rodzica to i * 2 lub i / 2
  usuniecie elementu to tylko zmniejszenie rozmiaru zmiennej - nie przekladanie tablicy

  potrzebne sa dwa kopce - dla max i dla min

  usuwajac z kopca max musze usunac z kopca min

  warto zapamietac pozycje elementow w drugim kopcu

  trzeba napisac funkcje powiekszania pojemnosci kopca
*/

struct Op {
  int tower_number;
  int fix_priority;
  int opposite_heap_index;

  Op(){}
  Op(int tower_number, int fix_priority) {
    this->tower_number = tower_number;
    this->fix_priority = fix_priority;
  }
};

int sift_up(Op* operations, int operation_count, bool max_mode) {
  //numerujemy indeksy od 1 wiec wszedzie -1 trzeba
  int index = operation_count;
  int parent_index;
  while(index > 1) {
    parent_index = index/2;
    if(max_mode && operations[parent_index - 1].fix_priority < operations[index - 1].fix_priority) {
      Op temp = operations[parent_index - 1];
      operations[parent_index - 1] = operations[index - 1];
      operations[index - 1] = temp;
    } else if(!max_mode && operations[parent_index - 1].fix_priority > operations[index - 1].fix_priority) {
      Op temp = operations[parent_index - 1];
      operations[parent_index - 1] = operations[index - 1];
      operations[index - 1] = temp;
    } else {
      return index;
    }
    index = parent_index;
  }
  return index;
}

int sift_down(Op* operations, int operation_count, bool max_mode) {
  //numerujemy indeksy od 1 wiec wszedzie -1 trzeba
  int index = 1;
  int child_index;
  while(index < operation_count) {
    child_index = index*2;
    //wybranie wiekszego dziecka
    if(max_mode && operations[child_index - 1].fix_priority < operations[child_index].fix_priority) {
      child_index++;
    } else if (!max_mode && operations[child_index - 1].fix_priority > operations[child_index].fix_priority) {
      child_index++;
    }

    if(max_mode && operations[index - 1].fix_priority < operations[child_index - 1].fix_priority) {
      Op temp = operations[child_index - 1];
      operations[child_index - 1] = operations[index - 1];
      operations[index - 1] = temp;
    } else if (!max_mode && operations[index - 1].fix_priority > operations[child_index - 1].fix_priority) {
      Op temp = operations[child_index - 1];
      operations[child_index - 1] = operations[index - 1];
      operations[index - 1] = temp;
    } else {
      return index;
    }
    index = child_index;
  }
  return index;
}

//zwiekszenie tablicy kopca
Op* enlarge_heap(Op* heap, int arr_size) {
  Op* tmp = new Op[arr_size * 2];
  memcpy(tmp,heap,sizeof(Op) * arr_size);
  delete[] heap;
  return tmp;
}

void pop(Op* operations, Op* opposite_operations, int *operation_count, bool max_mode) {
  int delete_value;
  if(max_mode) {
    delete_value = 0;
  } else {
    delete_value = 3000001; //max wartosci w zadaniu
  }

  cout<<operations[0].tower_number<<"\n";
  
  operations[0] = operations[*operation_count - 1];
  *operation_count--;
  int opposite_heap_index;
  opposite_heap_index = sift_down(operations,*operation_count,max_mode);
  operations[*operation_count - 1].opposite_heap_index = opposite_heap_index;
  for(int i=opposite_heap_index;i<*operation_count - 1;++i) {
    opposite_operations[i] = opposite_operations[i+1];
  }
}

//TEST
void print_heap(Op* heap, int size, string text) {
  cout<<text<<":"<<endl;
  for(int i=0;i<size;++i) {
    cout<<heap[i].tower_number<<"_"<<heap[i].fix_priority<<" ";
  }
  cout<<endl;
}

int main() {
  int n; //liczba zestawow
  int m, op, a, b; //liczba danych w zestawie, rodzaj operacji, numer wiezy, priorytet naprawy
  int operation_count; //liczba operacji w kopcu - rozmiar kopca
  int real_heap_size = 128; //prawdziwy rozmiar tablicy kopca
  cin>>n;
  for(int i=0;i<n;++i) {
    cin>>m;

    Op* max_heap = new Op[real_heap_size];
    Op* min_heap = new Op[real_heap_size];
    operation_count = 0;
    
    for(int j=0;j<m;++j) {
      cin>>op;
      if(op == 0) {
        cin>>a>>b;

        //jak zapelni kopiec
        if(operation_count == real_heap_size) {
          max_heap = enlarge_heap(max_heap,real_heap_size);
          min_heap = enlarge_heap(min_heap,real_heap_size);
          real_heap_size = real_heap_size<<1;
        }

        //dopisanie na koniec kopca
        max_heap[operation_count] = Op(a,b);
        min_heap[operation_count] = Op(a,b);
        operation_count++;

        print_heap(max_heap,operation_count,"MAX - add to end");
        print_heap(min_heap,operation_count,"MIN - add to end");

        //przesianie i przypisanie indeksow w przeciwnych kopcach
        min_heap[operation_count-1].opposite_heap_index = sift_up(max_heap,operation_count,true);
        max_heap[operation_count-1].opposite_heap_index = sift_up(min_heap,operation_count,false);

        print_heap(max_heap,operation_count,"MAX - after sifting");
        print_heap(min_heap,operation_count,"MIN - after sifting");
      } else  if (op == 1) {
        
      } else {
      
      }
    }
  }
  return 0;
}