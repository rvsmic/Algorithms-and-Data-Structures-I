#include <iostream>
#include <cstdlib>
using namespace std;

struct Person {
    string name;
    unsigned int count;
    float height;
    unsigned int speed;
    Person(string name, unsigned int count, float height, unsigned int speed) {
        this->name = name;
        this->count = count;
        this->height = height;
        this->speed = speed;
    }
    // ~Person() {
    //     delete this;
    // }
};

bool check_max_count(Person **people, unsigned int &m, string &max_person,unsigned int &max_count) {
    for(int i=0;i<m;i++) {
        if(people[i]->count > max_count) {
            max_count = people[i]->count;
            max_person = people[i]->name;
        }
    }
    unsigned int check_count = 0;
    for(int i=0;i<m;i++) {
        if(people[i]->count == max_count) {
            check_count++;
        }
    }
    Person **new_people = new Person*[check_count];
    unsigned int k = 0;
    for(int i=0;i<m;i++) {
        if(people[i]->count == max_count) {
            new_people[k] = people[i];
            k++;
        }
        //delete people[i];
    }
    people = new_people; //usunac?
    m = check_count;
    if(check_count > 1) {
        return false;
    }
    else {
        return true;
    }
}

bool check_max_height(Person **people, unsigned int &m, string &max_person, float &max_height) {
    for(int i=0;i<m;i++) {
        if(people[i]->height > max_height) {
            max_height = people[i]->height;
            max_person = people[i]->name;
        }
    }
    unsigned int check_count = 0;
    for(int i=0;i<m;i++) {
        if(people[i]->height == max_height) {
            check_count++;
        }
    }
    Person **new_people = new Person*[check_count];
    unsigned int k = 0;
    for(int i=0;i<m;i++) {
        if(people[i]->height == max_height) {
            new_people[k] = people[i];
            k++;
        }
        delete people[i];
    }
    delete people;
    people = new_people;
    m = check_count;
    if(check_count > 1){
        return false;
    }
    else {
        return true;
    }
}

bool check_max_speed(Person **people, unsigned int &m, string &max_person,unsigned int &max_speed) {
    for(int i=0;i<m;i++) {
        if(people[i]->speed > max_speed) {
            max_speed = people[i]->speed;
            max_person = people[i]->name;
        }
    }
    unsigned int check_count = 0;
    for(int i=0;i<m;i++) {
        if(people[i]->speed == max_speed) {
            check_count++;
        }
    }
    Person **new_people = new Person*[check_count];
    unsigned int k = 0;
    for(int i=0;i<m;i++) {
        if(people[i]->speed == max_speed) {
            new_people[k] = people[i];
            k++;
        }
        //delete people[i];
    }
    people = new_people;
    m = check_count;
    if(check_count > 1){
        return false;
    }
    else {
        return true;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.tie(nullptr);

    unsigned int n,m;
    cin>>n;
    for(int i=0;i<n;i++) {
        cin>>m;
        unsigned int order[3];
        string max_person = "";
        unsigned int max_count = 0, max_speed = 0;
        float max_height = 0;
        Person **people = new Person*[m];
        cin>>order[0]>>order[1]>>order[2];
        for(int j=0;j<m;j++) {
            string s;
            unsigned int u,c;
            float w;
            cin>>s>>u>>w>>c;
            people[j] = new Person(s,u,w,c);
        }
        bool check = false;
        for(int j=0;j<3;j++) {
            if(order[j]==1) {
                check = check_max_count(people,m,max_person,max_count);
                cout<<max_count<<"-count\n";
            }
            if(order[j]==2) {
                check = check_max_height(people,m,max_person,max_height);
                cout<<max_height<<"-height\n";
            }
            if(order[j]==3) {
                check = check_max_speed(people,m,max_person,max_speed);
                cout<<max_speed<<"-speed\n";
            }

            if(check) {
                break;
            }
        }
        cout<<max_person;
    }

    // unsigned int n, m;
    // cin>>n;
    // for(int i=0;i<n;i++) {
    //     cin>>m;
    //     int order[3]; 
    //     bool check[3];
    //     string max_person;
    //     unsigned int max_count=0;
    //     float max_height=0, max_speed=0;
    //     //scanf("%d %d %d", &order[0],&order[1],&order[2]);
    //     cin>>order[0]>>order[1]>>order[2];
    //     for(int j=0;j<m;j++) {
    //         string s;
    //         int u;
    //         float w;
    //         unsigned int c;
    //         //scanf("%s %d %f %d", &s,&u,&w,&c);
    //         cin>>s>>u>>w>>c;
    //         for(int k=0;k<3;k++) {
    //             if(order[k]==1) {
    //                 check_max_count(s,u,max_person,max_count);
    //             }
    //             if(order[k]==2) {
    //                 check_max_height(s,w,max_person,max_height);
    //             }
    //             if(order[k]==3) {
    //                 check_max_speed(s,u,max_person,max_speed);
    //             }
    //         }
    //         max_count=0;
    //         max_height=0;
    //         max_speed=0;
    //     }
    //     cout<<max_person<<"\n";
    // }
}