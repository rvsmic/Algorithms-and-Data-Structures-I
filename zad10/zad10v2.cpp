#include <iostream>
using namespace std;

struct Op {
  int tower_number;
  int fix_priority;

  int opposite_index;

  Op(){}
  Op(int tower_number, int fix_priority) {
    this->tower_number = tower_number;
    this->fix_priority = fix_priority;
  }
};

//TEST
void print_heap(Op* heap, int size, string text) {
  cout<<text<<":"<<endl;
  // cout<<"prio_nr: ";
  for(int i=0;i<size;++i) {
    // cout<<heap[i].fix_priority<<"_"<<heap[i].tower_number<<" ";
    cout<<heap[i].fix_priority<<" ";
  }
  cout<<"\nindexes:\n";
  for(int i=0;i<size;++i) {
    cout<<i<<">"<<heap[i].opposite_index<<" ";
  }
  cout<<endl;
}

//przesianie do gory
void sift_up(Op* operations, Op* opposite_operations, int operation_count, bool max_mode) {
  //tu liczymy indeksy od 1 wiec wszedzie -1 trzeba - zeby mozna bylo latwo znalezc rodzica
  int index = operation_count;
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
}

void sift_down(Op* operations, Op* opposite_operations, int operation_count, bool max_mode) {
  //numerujemy indeksy od 1 wiec wszedzie -1 trzeba
  int index = 1;
  int child_index;
  while(index < operation_count) {
    child_index = index * 2;
    if(child_index > operation_count) {
      return;
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

void pop(Op* operations, Op* opposite_operations, int *operation_count, bool max_mode) {
  if(*operation_count == 0) {
    return;
  }
  Op old_root = operations[0];
  operations[0] = operations[*operation_count - 1];
  //cout<<old_root.tower_number<<"\n";
  cout<<"O: "<<old_root.fix_priority<<"\n";
  *operation_count -= 1;
  if(*operation_count == 0) {
    return;
  }
  cout<<"---\n";
  print_heap(operations,*operation_count,"BEFORE SIFT");
  sift_down(operations,opposite_operations,*operation_count,max_mode);
  //cout<<"OLD "<<old_root.tower_number<<' '<<old_root.fix_priority<<endl;
  cout<<"OLD: "<<old_root.fix_priority<<endl;
  print_heap(operations,*operation_count,"HEAP - OLD");

  for(int i=old_root.opposite_index;i<*operation_count;++i) {
    opposite_operations[i] = opposite_operations[i+1];
    operations[opposite_operations[i].opposite_index].opposite_index = i;
  }
}

//zwiekszenie tablicy kopca
Op* enlarge_heap(Op* heap, int arr_size) {
  Op* tmp = new Op[arr_size + 10];
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
  int real_heap_size = 200; //prawdziwy rozmiar tablicy kopca
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
          real_heap_size += 10;
        }
        
        //dopisanie na koniec kopcow
        max_heap[operation_count] = Op(a,b);
        min_heap[operation_count] = Op(a,b);

        //startowe wstawienie na koniec
        max_heap[operation_count].opposite_index = operation_count;
        min_heap[operation_count].opposite_index = operation_count;

        operation_count++;

        print_heap(max_heap,operation_count,"MAX - add to end");
        print_heap(min_heap,operation_count,"MIN - add to end");
        cout<<endl;

        //przesianie i przypisanie indeksow w przeciwnych kopcach
        sift_up(max_heap,min_heap,operation_count,true);
        sift_up(min_heap,max_heap,operation_count,false);

        print_heap(max_heap,operation_count,"MAX - after sifting");
        print_heap(min_heap,operation_count,"MIN - after sifting");
        cout<<endl;
        
      } else  if (op == 1) {
        pop(max_heap,min_heap,&operation_count,true);
        print_heap(max_heap,operation_count,"MAX pop");
        print_heap(min_heap,operation_count,"MIN pop");
        cout<<"---\n";
      } else {
        pop(min_heap,max_heap,&operation_count,false);
        print_heap(max_heap,operation_count,"MAX pop");
        print_heap(min_heap,operation_count,"MIN pop");
        cout<<"---\n";
      }
    }
    delete[] max_heap;
    delete[] min_heap;
  }
  return 0;
}