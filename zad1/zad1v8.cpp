#include <iostream>
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

Person* compare_people(Person* best_person, Person* new_person, unsigned int order[]) {
    for(int i=0;i<3;i++) {
        if(order[i]==1) {
            if(new_person->count>best_person->count) {
                delete best_person;
                return new_person;
            }
            else if(new_person->count<best_person->count) {
                delete new_person;
                break;
            }
        }
        if(order[i]==2) {
            if(new_person->height>best_person->height) {
                delete best_person;
                return new_person;
            }
            else if(new_person->height<best_person->height) {
                delete new_person;
                break;
            }
        }
        if(order[i]==3) {
            if(new_person->speed>best_person->speed) {
                delete best_person;
                return new_person;
            }
            else if(new_person->speed<best_person->speed) {
                delete new_person;
                break;
            }
        }
    }
    return best_person;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.tie(nullptr);

    unsigned int n,m;
    cin>>n;
    unsigned int order[3];
    string* max_names = new string[n];
    
    for(int i=0;i<n;++i) {
        cin>>m;
        unsigned int max_count=0,max_speed=0;
        float max_height=0;
        Person *best_person, *new_person;
        cin>>order[0]>>order[1]>>order[2];
        for(int j=0;j<m;++j) {
            string s;
            unsigned int u,c;
            float w;
            cin>>s>>u>>w>>c;
            if(j==0) {
                best_person = new Person(s,u,w,c);
            }
            else {
                new_person = new Person(s,u,w,c);
                best_person = compare_people(best_person,new_person,order);
            }
        }
        max_names[i] = best_person->name;
    }
    for(int i=0;i<n;++i) {
        cout<<max_names[i]<<"\n";
    }
    delete[] max_names;
    return 0;
}