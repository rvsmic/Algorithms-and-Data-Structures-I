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

    void pop_first() {
        //wyrzucenie z poczatku
        next->prev = next;

        //ustawienie wyrzuconego
        next = this;
    }

    void pop_last() {
        //wyrzucenie z konca
        prev->next = prev;

        //ustawienie wyrzuconego
        prev = this;
    }

    List* add_out(List* new_out) {
        new_out->prev = this;
        this->next = new_out;

        return new_out;
    }

    short find_deleted_pair(short delete_count) {   //TO MOZE BYC WOLNE
        //this to pierwsza kolejkowa osoba
        short number, max_number = -1, max_distance;
        List* current = this;
        List* compared;
        for(int i=0;i<delete_count;i++) {
            number = current->data.number;
            current = current->next;
            compared = current;
            for(int j=i+1;j<delete_count;j++) {
                if(compared->data.number == number) {
                    if(max_number == -1) {
                        max_number = number;
                        max_distance = delete_count-j;
                    } else if((delete_count-j) > max_distance){
                        max_number = number;
                        max_distance = delete_count-j;
                    }

                    if(max_distance == delete_count-1) {
                        return max_number;
                    }
                }
                compared = compared->next;
            }
        }
        return max_number;
    }

    List* get_from_number(short number, short delete_count) {
        //this to dana usunieta osoba startowa
        List* current = this;
        for(int i=0;i<delete_count;i++) {
            if(current->data.number == number) {
                if(current == current->prev) {
                    current->pop_first();
                } else if (current == current->next) {
                    current->pop_last();
                } else {
                    current->pop_element();
                }
                return current;
            }
            current = current->next;
        }
        return current;
    }

    void join_game(List* new_player, short direction, char person_number) {
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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    cin.tie(nullptr);

    short n, p, k; //ilosc par, para zaczynajaca, kierunek

    cin>>n>>p>>k;

    short count = n*2;  //faktyczna ilosc osob

    short m; //ilosc operacji

    cin>>m;

    short op, flag, x; //operacja, flaga, ruch

    //pary juz ustawione pomieszane
    Pair data = Pair(0,'P');
    List* first_pair = new List(data);
    data = Pair(n-1,'L');
    List* current = new List(first_pair,data);

    //do przypisania startowego wskaznika
    List* start = first_pair;

    for(int i=1;i<n;i++) {
        data = Pair(i,'P');
        current = new List(current,data);
        data = Pair((i-1)%n,'L');
        current = new List(current,data);
        if(i == p) {
            start = current->prev;
        }
    }

    current->link_end(first_pair);

    current = start;

    //do wyrzuconych
    List* out;
    List* first_out;
    List* new_current;
    List* first_out_next;
    List* out_prev;
    short delete_count = 0;
    short pair_number;

    for(int i=0;i<m;i++) {
        cin>>op>>x;

        if(op == 0) {
            current = current->jump(x,k);
            current->print(count,k);
        }

        else if(op == 1) {
            cin>>flag;

            current = current->jump(x,k);

            //zapisanie nowego currenta
            new_current = current->new_current(k);

            //usuniecie elementu
            current->pop_element();

            //dodanie wyrzuconego do kolejki
            if(delete_count == 0) {
                first_out = current;
                out = current;
            } else {
                out = out->add_out(current);
            }
            delete_count++;
            count--;

            //ustawienie currenta
            current = new_current;

            //first_out zawsze poczatkiem kolejki, a out zawsze koncem
            //dodanie pary osob
            if(flag == 1 || count <= 3) {
                //znalezienie numera pary do dodania
                pair_number = first_out->find_deleted_pair(delete_count);

                //w wypadku braku par w kolejce omija ten segment
                if(pair_number != -1) {
                    //w wypadku jakby first_out byl nowa osoba
                    first_out_next = first_out->next;

                    //w wypadku jakby out byl ostatnia osoba - do dodawania potem kolejnych przegranych
                    out_prev = out->prev;

                    //znalezienie pierwszej osoby
                    new_current = first_out->get_from_number(pair_number,delete_count);

                    //nowy first_out
                    if(first_out==new_current) {
                        first_out = first_out_next;
                    }
                    if(out == new_current) {
                        out = out_prev;
                    }

                    delete_count--;
                    count++;

                    //dolaczenie pierwszej osoby
                    current->join_game(new_current,k,0);

                    //w wypadku jakby first_out byl nowa osoba
                    first_out_next = first_out->next;

                    //w wypadku jakby out byl ostatnia osoba - do dodawania potem kolejnych przegranych
                    out_prev = out->prev;

                    //znalezienie drugiej osoby
                    new_current = first_out->get_from_number(pair_number,delete_count);

                    //nowy first_out
                    if(first_out==new_current) {
                        first_out = first_out_next;
                    }
                    if(out == new_current) {
                        out = out_prev;
                    }

                    delete_count--;
                    count++;

                    //dolaczenie drugiej osoby
                    current->join_game(new_current,k,1);
                }
            }

            if(k==0) {
                k=1;
            } else {
                k=0;
            }
        }

        else if(op == 2) {
            current = current->jump(x,k);
            if(k==0) {
                k=1;
            } else {
                k=0;
            }
        }

    }

    return 0;
}