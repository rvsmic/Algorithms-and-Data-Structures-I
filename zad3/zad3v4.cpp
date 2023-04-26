#include <iostream>
using namespace std;

struct Pair {
    unsigned short number;
    char side;  //L lub R

    Pair(){}
    Pair(unsigned short number, char side){
        this->number = number;
        this->side = side;
    }
};

struct List {
    Pair data;
    List *previous;
    List *next;

    List(Pair data) {
        this->data = data;
        previous = this;
        next = this;
    }
    List(Pair data, List* previous) {
        this->data = data;
        this->previous = previous;
        previous->next = this;
    }

    void connect_final(List* first) {
        first->previous = this;
        this->next = first;
    }

    List* save_new_current(short direction) {
        if(direction == 0) {
            return previous;
        } else {
            return next;
        }
    }

    void basic_pop_element() {
        next->previous = previous;
        previous->next = next;
    }

    void pop_first() {
        next->previous = next;
    }

    void pop_last() {
        previous->next = previous;
    }

    void pop_element(List* element, char condition) {
        next->previous = previous;
        previous->next = next;
        if(condition == 0) {
            element = next;
        } else if(condition == 1) {
            element = previous;
        } else {
            element = this;
        }
    }

    List* scramble(short n) {
        List* current_left = this;
        List* next_left = this->next->next;

        //na pozniejsze poprawki polaczenia
        List* final_right = this->next;
        List* first_left = this;
        List* left_fix = this->next->next->next;

        for(int i=0;i<n;i++) {
            //ustawiamy prawe otaczajace nowa pozycje
            current_left->next->next = current_left;
            next_left->next->previous = current_left;
            
            //ustawiamy przestawiona lewa osobe
            current_left->previous = current_left->next;
            current_left->next = next_left->next;

            //podmiana na kolejna lewa osobe
            //warunek w celu pozostania na ostatniej osobie pod koniec
            if(i<n-1) {
                current_left = next_left;
                next_left = next_left->next->next;
            }
        }
        //ustawienie powiazania (n-2)L z 0P
        current_left->next = final_right;
        //ustawienie powiazania 1P z (n-1)L
        left_fix->previous = first_left;
        //ustawienie powiazania 0P z (n-1)L
        final_right->next = first_left;
        //ustawienie powiazania 0P z (n-2)L
        final_right->previous = current_left;

        return current_left;
    }

    List* jump(short jump, short direction) {
        List* current = this;
        if(direction == 0) {
            for(int i=0;i<jump-1;i++) {     //-1 bo najpierw rece podnosi ta sama osoba
                current = current->next;
            }
        } else {
            for(int i=0;i<jump-1;i++) {
                current = current->previous;
            }
        }
        return current;
    }

    List* find_start(short number) {
        List* current = this;
        while(current->data.number != number || current->data.side != 'P') {    //i guess mozna optymalniej zeby strone skoku wybrac
            current = current->jump(2,0);
        }
        return current;
    }

    static void print_state(List* person, short count, short direction) {
        for(int i=0;i<count;i++) {
            //cout<<person->data.number<<" ";
            cout<<person->data.number<<person->data.side<<" ";
            person = person->jump(2,direction);
        }
        cout<<"\n";
    }

    //funkcje do wyrzuconych:

    void add_out(List* new_out) {
        new_out->next = new_out;
        this->next = new_out;
        new_out->previous = this;
    }

    void return_to_game(List* first_out, List* last_out, short direction) {
        //funkcja dla current - osoby przed usunieta osoba
        List* first = first_out;
        List* second = first_out->next;
        bool found = false;
        while(first->data.number != second->data.number) {
            while(second != last_out) {
                second = second->next;
                if(first->data.number == second->data.number) {
                    found = true;
                    break;
                }
            }
            if(found) {
                break;
            } else {
                first = first->next;
                second = first->next;
            }
        }
        if(first->next == second) {
            if(first == first->previous) {
                first_out = second->next;
                first->pop_first();
                second->pop_first();
            } else if(second == second->next){
                last_out = second->previous;
                second->pop_last();
                first->pop_last();
            } else {
                first->basic_pop_element();
                second->basic_pop_element();
            }
        } else {
            if(first == first->previous) {
                first_out = first->next;
                first->pop_first();
            } else {
                first->basic_pop_element();
            }

            if(second == second->next) {
                last_out = second->previous;
                second->pop_last();
            } else {
                second->basic_pop_element();
            }
        }

        //zalezy gdzie sie cofnelismy (zegar / przeciw)
        if(direction == 0) {    //TUTAJ COS MOZLIWE ZE JEST ZLE
            //ustawienie first osoby
            first->next = this;
            first->previous = this->previous;
            
            //osoby wokol first osoby
            this->previous->next = first;
            this->previous = first;
            
            //ustawienie second osoby
            second->next = this->next->next;
            second->previous = this->next;

            //osoby wokol second osoby
            this->next->next->previous = second;
            this->next->next = second;
        } else {
            //ustawienie first osoby
            first->previous = this;
            first->next = this->next;
            
            //osoby wokol first osoby
            this->next->previous = first;
            this->next = first;

            //ustawienie second osoby
            second->previous = this->previous->previous;
            second->next = this->previous;
            
            //osoby wokol second osoby
            this->previous->previous->next = second;
            this->previous->previous = second;
        }
    }
};

int main() {
    //liczba par, numer startowej pary, zwrot gry (0-zgodnie z zegarem, 1-odwrotnie)
    short n,p,k;

    cin>>n>>p>>k;

    //liczba wszystkich graczy
    short count = 2*n;

    //liczba operacji
    short m;   
    cin>>m;

    //operacja, parametr, (ewentualnie) flaga      
    short op, x, flag;

    //stworzenie startowej pary
    Pair data = Pair(0,'P');
    List* first = new List(data);
    data = Pair(0,'L');
    List* current = new List(data,first);

    //do kolejki wyrzuconych
    List* out;
    List* first_out;

    //stworzenie i powiazanie reszty par
    for(int i=1;i<n;i++) {
        data = Pair(i,'P');
        current = new List(data,current);
        data = Pair(i,'L');
        current = new List(data,current);
    }

    //polaczenie konca z poczatkiem listy
    current->connect_final(first);

    //pomieszanie listy
    current = current->scramble(n);
    
    //ustalenie startowej osoby
    current = current->find_start(p);

    //pomocniczy wskaznik do usuwania osob
    List* temp;

    //przetwarzanie operacji
    for(int i=0;i<m;i++) {
        cin>>op;
        if(op == 1) {
            cin>>x>>flag;
        } else {
            cin>>x;
        }

        if(op == 0) {
            //wykonanie ruchu i wyswietlenie stanu
            current = current->jump(x,k);
            List::print_state(current,count,k);

        } else if (op == 1) {
            //pomylka osoby + ewentualny powrot do gry
            current = current->jump(x,k);

            if(n*2==count) {
                temp = current->save_new_current(k);
                current->basic_pop_element();
                first_out = current;
                first_out->next = first_out;
                first_out->previous = first_out;
                out = first_out;
                current = temp;
                count--;
            } else {
                temp = current->save_new_current(k);
                current->basic_pop_element();
                out->add_out(current);
                out = current;
                current = temp;
                count--;
            }

            if(flag == 1 || count <= 3) {
                current->return_to_game(first_out,out,k);
                count+=2;
            }

            //zmiana kierunku
            if(k==1) {
                k=0;
            } else {
                k=1;
            }

        } else if (op == 2) {
            //zmiana kierunku ruchu
            current = current->jump(x,k);

            if(k==1) {
                k=0;
            } else {
                k=1;
            }

        }
    }
    return 0;
}