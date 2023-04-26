#include <iostream>

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
};

string compare_people(Person** people, unsigned int size, unsigned int order[3]) {
    string max_name;

    for(int i=0;i<3;i++) {
        if(order[i]==1) {
            unsigned int max_count = 0, check_count = 0;
            for(int j=0;j<size;j++) {
                if(people[j]->count>max_count) {
                    max_count = people[j]->count;
                    max_name = people[j]->name;
                }
            }
            for(int j=0;j<size;j++) {
                if(people[j]->count==max_count) {
                    check_count++;
                }
            }
            if(check_count>1) {
                Person **new_people = new Person*[check_count];
                unsigned int k=0;
                for(int j=0;j<size;j++) {
                    if(people[j]->count==max_count) {
                        new_people[k] = people[j];
                        k++;
                    }
                }
                people = new_people;
                size = check_count;
            }
            else break;
        }
        if(order[i]==2) {
            float max_height = 0;
            unsigned int check_count = 0;
            for(int j=0;j<size;j++) {
                if(people[j]->height>max_height) {
                    max_height = people[j]->height;
                    max_name = people[j]->name;
                }
            }
            for(int j=0;j<size;j++) {
                if(people[j]->height==max_height) {
                    check_count++;
                }
            }
            if(check_count>1) {
                Person **new_people = new Person*[check_count];
                unsigned int k=0;
                for(int j=0;j<size;j++) {
                    if(people[j]->height==max_height) {
                        new_people[k] = people[j];
                        k++;
                    }
                }
                people = new_people;
                size = check_count;
            }
            else break;
        }
        if(order[i]==3) {
            unsigned int max_speed = 0, check_count = 0;
            for(int j=0;j<size;j++) {
                if(people[j]->speed>max_speed) {
                    max_speed = people[j]->speed;
                    max_name = people[j]->name;
                }
            }
            for(int j=0;j<size;j++) {
                if(people[j]->speed==max_speed) {
                    check_count++;
                }
            }
            if(check_count>1) {
                Person **new_people = new Person*[check_count];
                unsigned int k=0;
                for(int j=0;j<size;j++) {
                    if(people[j]->speed==max_speed) {
                        new_people[k] = people[j];
                        k++;
                    }
                }
                people = new_people;
                size = check_count;
            }
            else break;
        }
    }

    return max_name;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.tie(nullptr);

    unsigned int n,m;
    cin>>n;
    string* max_name = new string[n];
    for(int i=0;i<n;i++) {

        unsigned int order[3];
        string s;
        unsigned int u,c;
        float w;

        cin>>m;

        Person **people = new Person*[m];

        cin>>order[0]>>order[1]>>order[2];

        for(int j=0;j<m;j++) {
            cin>>s>>u>>w>>c;
            people[j] = new Person(s,u,w,c);
        }

        max_name[i] = compare_people(people, m, order);

        for(int j=0;j<m;j++) {
            delete people[j];
        }
        delete[] people;
    }
    for(int i=0;i<n;i++) {
        cout<<max_name[i]<<"\n";
    }
    delete[] max_name;
}