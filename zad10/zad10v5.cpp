#include <iostream>
using namespace std;

struct Op {
  int tower_number;
  int fix_priority;
  //indeks tej wiezy w przeciwnym kopcu
  int opposite_index;

  Op(){}
  Op(int tower_number, int fix_priority) {
    this->tower_number = tower_number;
    this->fix_priority = fix_priority;
  }
};

//przesianie do gory - oba kopce na raz
void sift_up(Op* max_heap, Op* min_heap, int operation_count) {
  //tu liczymy indeksy od 1 wiec wszedzie -1 trzeba - zeby mozna bylo latwo znalezc rodzica
  int index = operation_count;
  int parent_index;
  bool max_done = false, min_done = false;

  while(index > 1) {
    parent_index = index/2;
    if(max_heap[parent_index - 1].fix_priority < max_heap[index - 1].fix_priority) {
      Op temp = max_heap[parent_index - 1];
      max_heap[parent_index - 1] = max_heap[index - 1];
      max_heap[index - 1] = temp;

      min_heap[max_heap[parent_index - 1].opposite_index].opposite_index = parent_index - 1;
      min_heap[max_heap[index - 1].opposite_index].opposite_index = index - 1;
    } else {
        max_done = true;
    }
    if(min_heap[parent_index - 1].fix_priority > min_heap[index - 1].fix_priority) {
      Op temp = min_heap[parent_index - 1];
      min_heap[parent_index - 1] = min_heap[index - 1];
      min_heap[index - 1] = temp;

      max_heap[min_heap[parent_index - 1].opposite_index].opposite_index = parent_index - 1;
      max_heap[min_heap[index - 1].opposite_index].opposite_index = index - 1;
    } else {
        min_done = true;
    }
    if(max_done && min_done) {
        break;
    }
    index = parent_index;
  }
}

void sift_down(Op* operations, Op* opposite_operations, int operation_count, bool max_mode) {
  //numerujemy indeksy od 1 wiec wszedzie -1 trzeba
  int index = 1;
  int child_index;
  while(index < operation_count) {
    child_index = index * 2;
    if(child_index > operation_count) {
      break;
    }
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

      opposite_operations[operations[child_index - 1].opposite_index].opposite_index = child_index - 1;
      opposite_operations[operations[index - 1].opposite_index].opposite_index = index - 1;
    } else if (!max_mode && operations[index - 1].fix_priority > operations[child_index - 1].fix_priority) {
      Op temp = operations[child_index - 1];
      operations[child_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      opposite_operations[operations[child_index - 1].opposite_index].opposite_index = child_index - 1;
      opposite_operations[operations[index - 1].opposite_index].opposite_index = index - 1;
    } else {
      break;
    }
    index = child_index;
  }
}

//przesianie w gore i w dol od nowego miejsca dla uzupelniajacego luke node'a - w przeciwnym kopcu do tego z ktorego sciagamy korzen
void fix_node(Op* operations, Op* opposite_operations, int node_index, int operation_count, bool max_mode) {
  //tu liczymy indeksy od 1 wiec wszedzie -1 trzeba - zeby mozna bylo latwo znalezc rodzica
  int index = node_index + 1;
  int parent_index;

  while(index > 1) {
    parent_index = index/2;
    if(max_mode && operations[parent_index - 1].fix_priority < operations[index - 1].fix_priority) {
      Op temp = operations[parent_index - 1];
      operations[parent_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      opposite_operations[operations[parent_index - 1].opposite_index].opposite_index = parent_index - 1;
      opposite_operations[operations[index - 1].opposite_index].opposite_index = index - 1;
    } else if(!max_mode && operations[parent_index - 1].fix_priority > operations[index - 1].fix_priority) {
      Op temp = operations[parent_index - 1];
      operations[parent_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      opposite_operations[operations[parent_index - 1].opposite_index].opposite_index = parent_index - 1;
      opposite_operations[operations[index - 1].opposite_index].opposite_index = index - 1;
    } else {
      break;
    }
    index = parent_index;
  }

  index = node_index + 1;
  int child_index;
  while(index < operation_count) {
    child_index = index * 2;
    if(child_index > operation_count) {
      break;
    }
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

      opposite_operations[operations[child_index - 1].opposite_index].opposite_index = child_index - 1;
      opposite_operations[operations[index - 1].opposite_index].opposite_index = index - 1;
    } else if (!max_mode && operations[index - 1].fix_priority > operations[child_index - 1].fix_priority) {
      Op temp = operations[child_index - 1];
      operations[child_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      opposite_operations[operations[child_index - 1].opposite_index].opposite_index = child_index - 1;
      opposite_operations[operations[index - 1].opposite_index].opposite_index = index - 1;
    } else {
      break;
    }
  }
  index = child_index;
}

//zdjecie korzenia z kopca
void pop(Op* operations, Op* opposite_operations, int *operation_count, bool max_mode) {
  if(*operation_count == 0) {
    return;
  }
  Op old_root = operations[0];
  int node_fix_index;

  //ustawienie nowego korzenia kopca
  operations[0] = operations[*operation_count - 1];
  opposite_operations[operations[0].opposite_index].opposite_index = 0;

  //jezeli nie byl ostatnim w drugim kopcu to przenosimy ostatni z drugiego kopca w miejsce zdjetego elementu
  if(old_root.opposite_index != *operation_count - 1) {
    opposite_operations[old_root.opposite_index] = opposite_operations[*operation_count - 1];
    operations[opposite_operations[old_root.opposite_index].opposite_index].opposite_index = old_root.opposite_index;
  }

  cout<<old_root.tower_number<<"\n";

  *operation_count -= 1;
  if(*operation_count == 0) {
    return;
  }
  //przesianie w dol w glownym kopcu
  sift_down(operations,opposite_operations,*operation_count,max_mode);
  node_fix_index = old_root.opposite_index;
  //naprawa drugiego kopca
  fix_node(opposite_operations,operations,node_fix_index,*operation_count,!max_mode);
}

//zwiekszenie tablicy kopca
Op* enlarge_heap(Op* heap, int arr_size) {
  Op* tmp = new Op[arr_size * 2];
  //memcpy(tmp,heap,sizeof(Op*) * arr_size);
  for(int i=0;i<arr_size;++i) {
    tmp[i] = heap[i];
  }
  delete[] heap;
  return tmp;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  int n; //liczba zestawow
  int m, op, a, b; //liczba danych w zestawie, rodzaj operacji, numer wiezy, priorytet naprawy
  int operation_count; //liczba operacji w kopcu - rozmiar kopca
  int real_heap_size = 100; //prawdziwy rozmiar tablicy kopca
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
          real_heap_size *= 2;
        }
        
        //dopisanie na koniec kopcow
        max_heap[operation_count] = Op(a,b);
        min_heap[operation_count] = Op(a,b);

        //startowe wstawienie na koniec
        max_heap[operation_count].opposite_index = operation_count;
        min_heap[operation_count].opposite_index = operation_count;

        operation_count++;

        //przesianie i przypisanie indeksow w przeciwnych kopcach
        sift_up(max_heap,min_heap,operation_count);

      } else  if (op == 1) {
        pop(max_heap,min_heap,&operation_count,true);
      } else {
        pop(min_heap,max_heap,&operation_count,false);
      }
    }
    delete[] max_heap;
    delete[] min_heap;
  }
  return 0;
}