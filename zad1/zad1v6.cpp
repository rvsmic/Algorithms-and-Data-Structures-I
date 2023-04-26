#include <iostream>
#include <cstring>
using namespace std;

struct Person {
    string name;
    unsigned int count,speed;
    float height;

    Person(string name, unsigned int count, float height, unsigned int speed) {
        this->name = name;
        this->count = count;
        this->height = height;
        this->speed = speed;
    }
    Person(){}
};

Person* get_count_people(Person* people,unsigned int& amount) {
    Person* new_people = people;
    unsigned int max_count = 0;
    for(int i=0;i<amount;i++) {
        if(people[i].count > max_count) {
            max_count = people[i].count;
        }
    }
    unsigned int check_count = 0;
    for(int i=0;i<amount;i++) {
        if(people[i].count == max_count) {
            check_count++;
        }
    }
    if(check_count>1) {
        //delete[] new_people;
        new_people = new Person[check_count];
        unsigned int k = 0;
        for(int i=0;i<amount;i++) {
            if(people[i].count == max_count) {
                memcpy(&new_people[k],&people[i],sizeof(Person));
            }
        }
        //delete[] people;
    }
    amount = check_count;
    return new_people;
}

Person* get_height_people(Person* people,unsigned int& amount) {
    Person* new_people = people;
    unsigned int max_height = 0;
    for(int i=0;i<amount;i++) {
        if(people[i].height > max_height) {
            max_height = people[i].height;
        }
    }
    unsigned int check_count = 0;
    for(int i=0;i<amount;i++) {
        if(people[i].height == max_height) {
            check_count++;
        }
    }
    if(check_count>1) {
        //delete[] new_people;
        new_people = new Person[check_count];
        unsigned int k = 0;
        for(int i=0;i<amount;i++) {
            if(people[i].height == max_height) {
                memcpy(&new_people[k],&people[i],sizeof(Person));
            }
        }
        //delete[] people;
    }
    amount = check_count;
    return new_people;
}

Person* get_speed_people(Person* people,unsigned int& amount) {
    Person* new_people = people;
    unsigned int max_speed = 0;
    for(int i=0;i<amount;i++) {
        if(people[i].speed > max_speed) {
            max_speed = people[i].speed;
        }
    }
    unsigned int check_count = 0;
    for(int i=0;i<amount;i++) {
        if(people[i].speed == max_speed) {
            check_count++;
        }
    }
    if(check_count>1) {
        //delete[] new_people;
        new_people = new Person[check_count];
        unsigned int k = 0;
        for(int i=0;i<amount;i++) {
            if(people[i].speed == max_speed) {
                memcpy(&new_people[k],&people[i],sizeof(Person));
            }
        }
        //delete[] people;
    }
    amount = check_count;
    return new_people;
}

string get_person(Person* people, unsigned int amount, unsigned int order[]) {
    string max_name;
    for(int i=0;i<3;i++) {
        if(order[i]==1) { 
            Person *tmp_people = new Person[amount];
            memcpy(tmp_people,people,amount*sizeof(Person));
            //delete[] people;
            people = get_count_people(tmp_people,amount);
            if(amount == 1) {
                max_name = people[0].name;
                break;
            }
            else continue;
        }
        if(order[i]==2) {
            Person *tmp_people = new Person[amount];
            memcpy(tmp_people,people,amount*sizeof(Person));
            //delete[] people;
            people = get_height_people(tmp_people,amount);
            if(amount == 1) {
                max_name = people[0].name;
                break;
            }
            else continue;
        }
        if(order[i]==3) {
            Person *tmp_people = new Person[amount];
            memcpy(tmp_people,people,amount*sizeof(Person));
            //delete[] people;
            people = get_speed_people(tmp_people,amount);
            if(amount == 1) {
                max_name = people[0].name;
                break;
            }
            else continue;
        }
    }
    return max_name;
}

int main(){
    unsigned int n,m;
    cin>>n;
    string *max_names = new string[n];
    for(int i=0;i<n;i++) {
        unsigned int order[3];
        string s;
        unsigned int u, c;
        float w;
        cin>>m;
        Person *people = new Person[m];
        cin>>order[0]>>order[1]>>order[2];
        for(int j=0;j<m;j++) {
            cin>>s>>u>>w>>c;
            people[j] = Person(s,u,w,c);
        }
        max_names[i] = get_person(people, m, order);
    }
    for(int i=0;i<n;i++) {
        cout<<max_names[i]<<'\n';
    }
    delete[] max_names;
    return 0;
}