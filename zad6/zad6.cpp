#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

/*
    najblizsze od siebie punkty walcza
    osoba z nizsza sila odpada z gry
    albo szukac za kazdym razem najblizszych sobie osobnikow - dziel i zwyciezaj
    wykonujemy algorytm dla najmniejszych danych - para osob
    jak jeden punkt to odleglosc nieskonczona (zwrocona z funkcji)
    jak wiecej punktow to dzielimy na lewa i prawa strone i wykonujemy osobno algorytm
    jak posortujemy dane po np x to podzial bedzie latwiejszy - sortowanie wzgledem x
    zwracamy min odleglosc z przypadku atomowego - najmniejszego
    jeszcze trzeba dodac operacje szukania odleglosci pomiedzy sasiadami rozdzielonymi podzialem

    przyklad
    posortowane wzgledem x
    0 i 2 ida do swojej tablicy a 1 i 3 do swojej
    wykonujemy algorytm i zwracamy odleglosc
    dla lewej strony pierwiastek z 5 a dla prawej wychodzi pierw z 40
    wybieramy mniejsza
    sprawdzamy punkt przeciecia - bierzemy srodkowe wartosci i wyliczamy linie srodkowa - u nas 2.5
    sprawdzamy czy od tej linii znajduje sie punkt w mniejszej odleglosci niz ta znaleziona wyzej
    np: 0 ma 1.5, 2 ma 0.5, 1 ma 0.5 wiec sie lapia do porownania
    wtedy sprawdzamy wszystkie znalezione pary czy maja mniejsza odleglosc niz ta znaleziona wczesniej - brute force - malo ich wiec nie wplynie specjalnie na szybkosc
    znajduje sie 0,2 najlepszy - sprawdzamy sile - 2 przegrywa wiec wypisujemy jego lokalizacje po czym usuwamy z planszy
    
    algortym sie ponawia na 3 punktach

    warto posortowac po wspolrzednej y jak juz patrzymy na odleglosc od narysowanej linii

    przy remisie mniejszy numer wygrywa

    t moze byc 0?
*/

typedef unsigned short ushort;

struct Warrior {
    ushort id;
    ushort x,y;
    ushort power;

    Warrior(){}
    Warrior(ushort id, ushort x, ushort y, ushort power) {
        this->id = id;
        this->x = x;
        this->y = y;
        this->power = power;
    }
};

//zamienic na quicksort!!!!!!!!!!!!!!!!!

vector <Warrior*> sort_by_x(vector <Warrior*> warriors) {
    for(int i=0;i<warriors.size();i++) {
        for(int j=1;j<warriors.size();j++) {
            if(warriors[j-1]->x > warriors[j]->x) {
                swap(warriors[j-1],warriors[j]);
            }
        }
    }
    return warriors;
}

vector <Warrior*> sort_by_y(vector <Warrior*> warriors) {
    for(int i=0;i<warriors.size();i++) {
        for(int j=1;j<warriors.size();j++) {
            if(warriors[j-1]->y > warriors[j]->y) {
                swap(warriors[j-1],warriors[j]);
            }
        }
    }
    return warriors;
}

//testowe
void print_warriors(vector <Warrior*> warriors) {
    cout<<"---\n";
    for(int i=0;i<warriors.size();i++) {
        cout<<"id: "<<warriors[i]->id<<" x:"<<warriors[i]->x<<" y:"<<warriors[i]->y<<" power:"<<warriors[i]->power<<"\n";
    }
    cout<<"---\n";
}

float closest_fight(vector <Warrior*> warriors, pair <Warrior*,Warrior*> *chosen_warriors, float* min_distance) {
    if(warriors.size() < 3) {
        //jestesmy na atomowym poziomie wiec sprawdzamy walke
        if(warriors.size() < 2) {
            return INFINITY;
        }
        float A = abs(warriors[0]->x - warriors[1]->x);
        float B = abs(warriors[0]->y - warriors[1]->y);
        float result = sqrt(pow(A,2) + pow(B,2));
        if(result < *min_distance) {
            *min_distance = result;
            chosen_warriors->first = warriors[0];
            chosen_warriors->second = warriors[1];
        }
        return result;
    } else {
        //dalszy podzial na pary
        //wywolanie fight na obu polowkach
        float left_distance, right_distance;
        ushort new_size = warriors.size()/2;
        ushort c = 0;
        vector <Warrior*> tmp_warriors;
        for(int i=0;i<new_size;i++) {
            tmp_warriors.push_back(warriors[c]);
            c++;
        }
        left_distance = closest_fight(tmp_warriors,chosen_warriors,min_distance);
        tmp_warriors.clear();
        for(int j=0;j<warriors.size()-new_size;j++) {
            tmp_warriors.push_back(warriors[c]);
            c++;
        }
        right_distance = closest_fight(tmp_warriors,chosen_warriors,min_distance);
        tmp_warriors.clear();

        if(left_distance < right_distance) {
            return left_distance;
        } else {
            return right_distance;
        }
    }
}

float calculate_distance(vector <Warrior*> warriors) {
    float A = abs(warriors[0]->x - warriors[1]->x);
    float B = abs(warriors[0]->y - warriors[1]->y);
    return sqrt(pow(A,2) + pow(B,2));
}

vector <Warrior*> fight(vector <Warrior*> warriors) {
    //posortowanie wedlug x na start
    warriors = sort_by_x(warriors);
    //para wyznaczonych walczacych
    pair <Warrior*,Warrior*> chosen_warriors;
    //minimalny dystans miedzy osobami
    float min_distance = INFINITY;
    //szukanie "dziel i zwyciezaj" najblizszych osob 
    cout<<closest_fight(warriors,&chosen_warriors,&min_distance)<<" - "<<chosen_warriors.first->id<<" - "<<chosen_warriors.second->id<<" ~ "<<min_distance<<"\n";
    //znaleziona z algorytmu odpowiednia para do gry
    //teraz trzeba sprawdzic srodek - miedzy srodkowymi osobami
    float middle_x;
    if(warriors.size() & 1) {
        middle_x = float((warriors[warriors.size()/2]->x + warriors[(warriors.size()/2)+1]->x)/2);
    } else {
        middle_x = float((warriors[warriors.size()/2]->x + warriors[(warriors.size()/2)-1]->x)/2);
    }
    //kopia i posortowanie po y osoby
    vector <Warrior*> sorted_warriors = sort_by_y(warriors);
    //teraz sprawdzamy odleglosc czy jest mniejsza niz middle_x
    for(int i=0;i<warriors.size();i++) {
        
    }
    



}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.tie(nullptr);

    ushort n, t, x, y, w; //liczba wojownikow, liczba oczekiwanych walk, wspolrzedne walki, moc zawodnika
    cin>>n>>t;

    vector <Warrior*> warriors;

    for(int i=0;i<n;++i) {
        cin>>x>>y>>w;
        warriors.push_back(new Warrior(i,x,y,w));
    }

    warriors = fight(warriors);


    // Warrior::print_warriors(warriors);

    // warriors = Warrior::sort_by_x(warriors);

    // Warrior::print_warriors(warriors);

    return 0;
}