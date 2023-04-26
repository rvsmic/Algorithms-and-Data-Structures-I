#include <iostream>
using namespace std;

struct Op {
  int tower_number;
  int fix_priority;

  int max_index;
  int min_index;

  Op(){}
  Op(int tower_number, int fix_priority) {
    this->tower_number = tower_number;
    this->fix_priority = fix_priority;
  }
};

//przesianie do gory
inline void sift_up(Op** operations, int operation_count, bool max_mode) {
  //tu liczymy indeksy od 1 wiec wszedzie -1 trzeba - zeby mozna bylo latwo znalezc rodzica
  int index = operation_count;
  int parent_index;
  if(index == 1){
    operations[0]->max_index = 0;
    operations[0]->min_index = 0;
  }

  while(index > 1) {
    parent_index = index/2;
    if(max_mode && operations[parent_index - 1]->fix_priority < operations[index - 1]->fix_priority) {
      Op* temp = operations[parent_index - 1];
      operations[parent_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      operations[parent_index - 1]->max_index = parent_index - 1;
      operations[index - 1]->max_index = index - 1;
    } else if(!max_mode && operations[parent_index - 1]->fix_priority > operations[index - 1]->fix_priority) {
      Op* temp = operations[parent_index - 1];
      operations[parent_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      operations[parent_index - 1]->min_index = parent_index - 1;
      operations[index - 1]->min_index = index - 1;
    } else {
      if(max_mode) {
        operations[index - 1]->max_index = index - 1;
      } else {
        operations[index - 1]->min_index = index - 1;
      }
      break;
    }
    index = parent_index;
  }
}

inline void sift_down(Op** operations, int operation_count, bool max_mode) {
  //numerujemy indeksy od 1 wiec wszedzie -1 trzeba
  int index = 1;
  int child_index;
  while(index < operation_count) {
    child_index = index * 2;
    if(child_index > operation_count) {
      return;
    }
    //wybranie wiekszego dziecka
    if(max_mode && operations[child_index - 1]->fix_priority < operations[child_index]->fix_priority) {
      child_index++;
    } else if (!max_mode && operations[child_index - 1]->fix_priority > operations[child_index]->fix_priority) {
      child_index++;
    }

    if(max_mode && operations[index - 1]->fix_priority < operations[child_index - 1]->fix_priority) {
      Op* temp = operations[child_index - 1];
      operations[child_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      operations[child_index - 1]->max_index = child_index - 1;
      operations[index - 1]->max_index = index - 1;
    } else if (!max_mode && operations[index - 1]->fix_priority > operations[child_index - 1]->fix_priority) {
      Op* temp = operations[child_index - 1];
      operations[child_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      operations[child_index - 1]->min_index = child_index - 1;
      operations[index - 1]->min_index = index - 1;
    } else {
      if(max_mode) {
        operations[index - 1]->max_index = index - 1;
      } else {
        operations[index - 1]->min_index = index - 1;
      }
      break;
    }
    index = child_index;
  }
}

inline void fix_node(Op** operations, int node_index, int operation_count, bool max_mode) {
  //tu liczymy indeksy od 1 wiec wszedzie -1 trzeba - zeby mozna bylo latwo znalezc rodzica
  int index = node_index + 1;
  int parent_index;
  if(index == 1){
    operations[0]->max_index = 0;
    operations[0]->min_index = 0;
  }

  while(index > 1) {
    parent_index = index/2;
    if(max_mode && operations[parent_index - 1]->fix_priority < operations[index - 1]->fix_priority) {
      Op* temp = operations[parent_index - 1];
      operations[parent_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      operations[parent_index - 1]->max_index = parent_index - 1;
      operations[index - 1]->max_index = index - 1;
    } else if(!max_mode && operations[parent_index - 1]->fix_priority > operations[index - 1]->fix_priority) {
      Op* temp = operations[parent_index - 1];
      operations[parent_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      operations[parent_index - 1]->min_index = parent_index - 1;
      operations[index - 1]->min_index = index - 1;
    } else {
      if(max_mode) {
        operations[index - 1]->max_index = index - 1;
      } else {
        operations[index - 1]->min_index = index - 1;
      }
      break;
    }
    index = parent_index;
  }

  index = node_index + 1;
  int child_index;
  while(index < operation_count) {
    child_index = index * 2;
    if(child_index > operation_count) {
      return;
    }
    //wybranie wiekszego dziecka
    if(max_mode && operations[child_index - 1]->fix_priority < operations[child_index]->fix_priority) {
      child_index++;
    } else if (!max_mode && operations[child_index - 1]->fix_priority > operations[child_index]->fix_priority) {
      child_index++;
    }

    if(max_mode && operations[index - 1]->fix_priority < operations[child_index - 1]->fix_priority) {
      Op* temp = operations[child_index - 1];
      operations[child_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      operations[child_index - 1]->max_index = child_index - 1;
      operations[index - 1]->max_index = index - 1;
    } else if (!max_mode && operations[index - 1]->fix_priority > operations[child_index - 1]->fix_priority) {
      Op* temp = operations[child_index - 1];
      operations[child_index - 1] = operations[index - 1];
      operations[index - 1] = temp;

      operations[child_index - 1]->min_index = child_index - 1;
      operations[index - 1]->min_index = index - 1;
    } else {
      if(max_mode) {
        operations[index - 1]->max_index = index - 1;
      } else {
        operations[index - 1]->min_index = index - 1;
      }
      break;
    }
    index = child_index;
  }
}

inline void pop(Op** operations, Op** opposite_operations, int *operation_count, bool max_mode) {
  if(*operation_count == 0) {
    return;
  }
  cout<<operations[0]->tower_number<<"\n";
   
  Op* old_root = operations[0];
  Op* swapped_node = operations[*operation_count - 1];
  int swapped_node_index;
  operations[0] = swapped_node;
  if(max_mode) {
    opposite_operations[old_root->min_index] = operations[0];
  } else {
    opposite_operations[old_root->max_index] = operations[0];
  }
  opposite_operations[*operation_count - 1] = old_root;
  
  *operation_count -= 1;

  sift_down(operations,*operation_count,max_mode);

  if(max_mode) {
    swapped_node_index = swapped_node->min_index;
  } else {
    swapped_node_index = swapped_node->max_index;
  }

  fix_node(opposite_operations,swapped_node_index,*operation_count,!max_mode);

  delete old_root;
}

//zwiekszenie tablicy kopca
inline Op** enlarge_heap(Op** heap, int arr_size) {
  Op** tmp = new Op*[arr_size + 200];
  //memcpy(tmp,heap,sizeof(Op*) * arr_size);
  for(int i=0;i<arr_size;++i) {
    tmp[i] = heap[i];
  }
  delete[] heap;
  return tmp;
}

//TEST
void print_heap(Op** heap, int size, string text) {
  cout<<text<<":"<<endl;
  for(int i=0;i<size;++i) {
    //cout<<heap[i]->tower_number<<"_"<<heap[i]->fix_priority<<" ";
    cout<<heap[i]->max_index<<">"<<heap[i]->min_index<<" ";
  }
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.tie(nullptr);

  int n; //liczba zestawow
  int m, op, a, b; //liczba danych w zestawie, rodzaj operacji, numer wiezy, priorytet naprawy
  int operation_count; //liczba operacji w kopcu - rozmiar kopca
  int real_heap_size; //prawdziwy rozmiar tablicy kopca
  Op** max_heap;
  Op** min_heap;
  Op* operation;
  cin>>n;
  for(int i=0;i<n;++i) {
    cin>>m;
    real_heap_size = 100;
    max_heap = new Op*[real_heap_size];
    min_heap = new Op*[real_heap_size];
    operation_count = 0;
    
    for(int j=0;j<m;++j) {
      cin>>op;
      if(op == 0) {
        cin>>a>>b;

        //jak zapelni kopiec
        if(operation_count == real_heap_size) {
          max_heap = enlarge_heap(max_heap,real_heap_size);
          min_heap = enlarge_heap(min_heap,real_heap_size);
          real_heap_size += 200;
        }
        
        //dopisanie na koniec kopcow
        operation = new Op(a,b);
        max_heap[operation_count] = operation;
        min_heap[operation_count] = operation;
        operation_count++;

        // print_heap(max_heap,operation_count,"MAX - add to end");
        // print_heap(min_heap,operation_count,"MIN - add to end");

        //przesianie i przypisanie indeksow w przeciwnych kopcach
        sift_up(max_heap,operation_count,true);
        sift_up(min_heap,operation_count,false);

        // print_heap(max_heap,operation_count,"MAX - after sifting");
        // print_heap(min_heap,operation_count,"MIN - after sifting");
        
      } else  if (op == 1) {
        pop(max_heap,min_heap,&operation_count,true);
      } else {
        pop(min_heap,max_heap,&operation_count,false);
      }
    }
    for(int i=0;i<operation_count;++i) {
      delete max_heap[i];
    }
    delete[] max_heap;
    delete[] min_heap;
  }
  return 0;
}