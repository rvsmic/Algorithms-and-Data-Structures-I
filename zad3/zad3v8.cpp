#include <iostream>
using namespace std;

struct Pair {
    short number;
    char side;

    Pair(){}
    Pair(short number, char side) {
        this->number = number;
        this->side = side;
    }
};

struct List {
    Pair data;
    List* next;
    List* prev;

    List(Pair data) {
        this->data = data;
        next = this;
        prev = this;
    }
    List(List* old_pair, Pair data) {
        this->data = data;
        prev = old_pair;
        old_pair->next = this;
    }

    void link_end(List* first) {
        first->prev = this;
        next = first;
    }

    void print(short count, short direction) {
        List* current = this;
        if(direction == 0) {
            for(int i=0;i<count;i++) {
                cout<<current->data.number<<" ";
                current = current->next;
            }
        } else {
            for(int i=0;i<count;i++) {
                cout<<current->data.number<<" ";
                current = current->prev;
            }
        }
        cout<<"\n";
    }

    List* jump(short jump, short direction) {
        List* current = this;
        if(direction == 0) {
            for(int i=0;i<jump-1;i++) {
                current = current->next;
            }
        } else {
            for(int i=0;i<jump-1;i++) {
                current = current->prev;
            }
        }
        return current;
    }

    //DO USUWANIA:

    List* new_current(short direction) {
        if(direction == 0) {
            return prev;
        } else {
            return next;
        }
    }

    void pop_element() {
        //wyrzucenie z lancucha
        next->prev = prev;
        prev->next = next;

        //ustawienie wyrzuconego
        next = this;
        prev = this;
    }

    List* pop_first() {
        //element nastepny w kolejce
        List* temp = this->next;
        temp->prev = temp;
        delete this;
        return temp;
    }

    void add_out(List** new_out, List** first_out, List** last_out, bool *delete_arr, short* delete_count) {
        if(delete_arr[(*new_out)->data.number] == true) {
            //jezeli nikogo nie ma w kolejce
            if(*delete_count == 0) {
                (*last_out) = (*new_out);
            }
            
            //"dopisanie" do kolejki 2 osoby
            (*new_out)->prev = (*last_out);
            (*last_out)->next = (*new_out);

            //ustalenie nowej osoby jako ostatniej w kolejce
            if(*delete_count != 0) {
                (*last_out) = (*new_out);
            }
            
            //ustalenie first osoby przy dolaczaniu do pustej kolejki
            if(*delete_count == 0) {
                (*first_out) = (*last_out);
            }

            (*delete_count)++;
        } else {
            //"dopisanie" do tablicy 1 osoby
            delete_arr[(*new_out)->data.number] = true;
            delete *new_out;
        }
    }

    void join_chain(List* new_player, short direction, char person_number) {
        //this jest aktualnym wskaznikiem grajacej osoby
        if(direction == 0) {
            //trzeba dodac osobe przed this i za nastepna osoba od this
            if(person_number == 0) {
                new_player->next = this;
                new_player->prev = prev;

                prev->next = new_player;
                prev = new_player;
            } else {
                new_player->next = next->next;
                new_player->prev = next;

                next->next->prev = new_player;
                next->next = new_player;
            }
        } else {
            if(person_number == 0) {
                new_player->next = next;
                new_player->prev = this;

                next->prev = new_player;
                next = new_player;                
            } else {
                new_player->next = prev;
                new_player->prev = prev->prev;

                prev->prev->next = new_player;
                prev->prev = new_player;
            }
        }
    }

    void join_game(List** first_out, bool* delete_arr, short* delete_count, short direction, short* count) {
        //jak nie ma par
        if(*delete_count == 0) {
            return;
        }

        //zapisanie numeru nowej pary
        short number = (*first_out)->data.number;

        //wyrzucenie pary z kolejki
        *first_out = (*first_out)->pop_first();
        delete_arr[number] = false;

        //dodanie nowej pary do gry
        this->join_chain(new List(Pair(number,'N')),direction,0);
        this->join_chain(new List(Pair(number,'N')),direction,1);
        
        //zmniejszenie liczby par
        (*delete_count)--;

        //zwiekszenie ilosci graczy
        *count+=2;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    cin.tie(nullptr);

    //ilosc par, para zaczynajaca, kierunek
    short n, p, k;      

    cin>>n>>p>>k;

    //faktyczna ilosc osob
    short count = n*2;  

    //ilosc operacji
    short m; 

    cin>>m;

    //operacja, flaga, ruch
    short op, flag, x;

    //pary juz ustawione pomieszane
    Pair data = Pair(0,'P');
    List* first_pair = new List(data);
    data = Pair(n-1,'L');
    List* current = new List(first_pair,data);

    //do przypisania startowego wskaznika
    List* start = first_pair;

    //do sprawdzania pozniejszego dodawania do gry
    bool *delete_arr = new bool[n];
    delete_arr[0] = false;

    for(int i=1;i<n;i++) {
        data = Pair(i,'P');
        current = new List(current,data);
        data = Pair((i-1)%n,'L');
        current = new List(current,data);
        if(i == p) {
            start = current->prev;
        }
        delete_arr[i] = false;
    }

    //zamkniecie kola z par
    current->link_end(first_pair);

    //ustawienie startowej pary
    current = start;

    //do kolejki usunietych
    List* first_out, *last_out, *new_current;
    short delete_count = 0;

    for(int i=0;i<m;i++) {
        cin>>op>>x;

        if(op == 0) {
            //przeskok o x w kierunku k
            current = current->jump(x,k);

            //wydrukowanie odpowiedzi
            current->print(count,k);
        }

        else if(op == 1) {
            cin>>flag;

            //przeskok o x w kierunku k
            current = current->jump(x,k);

            //zapisanie nowego currenta
            new_current = current->new_current(k);

            //wyrzucenie elementu i zapisanie pod current
            current->pop_element();
            count--;

            //dodanie do kolejki lub usuniecie wskaznika
            last_out->add_out(&current, &first_out, &last_out, delete_arr, &delete_count);

            //ustawienie nowej pozycji currenta
            current = new_current;

            //cout<<"deleted:";
            //first_out->test_print(delete_count);

            if(flag == 1 || count <= 3) {
                //dolaczenie do gry
                current->join_game(&first_out, delete_arr, &delete_count, k, &count);
            }

            //zmiana kierunku
            if(k==0) {
                k=1;
            } else {
                k=0;
            }
        }

        else if(op == 2) {
            //przeskok o x w kierunku k
            current = current->jump(x,k);

            //zmiana kierunku
            if(k==0) {
                k=1;
            } else {
                k=0;
            }
        }

    }

    return 0;
}