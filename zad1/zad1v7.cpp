#include <iostream>
using namespace std;

struct Person {
    string name;
    unsigned int count,speed;
    float height;
    bool checked;

    Person(string name, unsigned int count, float height, unsigned int speed) {
        this->name = name;
        this->count = count;
        this->height = height;
        this->speed = speed;
        checked = false;
    }
    Person(){}
};

string get_max_person(Person* people, unsigned int size, unsigned int order[]) {
    string max_person;

    unsigned int check_count = 0;
    
    for(int i=0;i<3;++i) {
        if(order[i]==1) {
            if(check_count==1) {
                for(int j=0;j<size;++j) {
                    if(people[j].checked) {
                        max_person = people[j].name;
                        break;
                    }
                }
                break;
            }
            else if(check_count == 0) {
                unsigned int max_count = 0;
                for(int j=0;j<size;++j) {
                    if(people[j].count > max_count) {
                        max_count = people[j].count;
                        max_person = people[j].name;
                    }
                }

                for(int j=0;j<size;++j) {
                    if(people[j].count == max_count) {
                        people[j].checked = true;
                        ++check_count;
                    }
                }
            }
            else {
                unsigned int max_count = 0;
                for(int j=0;j<size;++j) {
                    if( (people[j].count > max_count) && (people[j].checked) ) {
                        max_count = people[j].count;
                        max_person = people[j].name;
                    }
                }
                for(int j=0;j<size;++j) {
                    if( (people[j].count != max_count) && (people[j].checked) ) {
                        people[j].checked = false;
                        --check_count;
                    }
                }
            }
        }
        if(order[i]==2) {
            if(check_count==1) {
                for(int j=0;j<size;++j) {
                    if(people[j].checked) {
                        max_person = people[j].name;
                        break;
                    }
                }
                break;
            }
            else if(check_count == 0) {
                float max_height = 0;
                for(int j=0;j<size;++j) {
                    if(people[j].height > max_height) {
                        max_height = people[j].height;
                        max_person = people[j].name;
                    }
                }

                for(int j=0;j<size;++j) {
                    if(people[j].height == max_height) {
                        people[j].checked = true;
                        ++check_count;
                    }
                }
            }
            else {
                float max_height = 0;
                for(int j=0;j<size;++j) {
                    if( (people[j].height > max_height) && (people[j].checked) ) {
                        max_height = people[j].height;
                        max_person = people[j].name;
                    }
                }
                for(int j=0;j<size;++j) {
                    if( (people[j].height != max_height) && (people[j].checked) ) {
                        people[j].checked = false;
                        --check_count;
                    }
                }
            }
        }
        if(order[i]==3) {
            if(check_count==1) {
                for(int j=0;j<size;++j) {
                    if(people[j].checked) {
                        max_person = people[j].name;
                        break;
                    }
                }
                break;
            }
            else if(check_count == 0) {
                unsigned int max_speed = 0;
                for(int j=0;j<size;++j) {
                    if(people[j].speed > max_speed) {
                        max_speed = people[j].speed;
                        max_person = people[j].name;
                    }
                }

                for(int j=0;j<size;++j) {
                    if(people[j].speed == max_speed) {
                        people[j].checked = true;
                        ++check_count;
                    }
                }
            }
            else {
                unsigned int max_speed = 0;
                for(int j=0;j<size;++j) {
                    if( (people[j].speed > max_speed) && (people[j].checked) ) {
                        max_speed = people[j].speed;
                        max_person = people[j].name;
                    }
                }
                for(int j=0;j<size;++j) {
                    if( (people[j].speed != max_speed) && (people[j].checked) ) {
                        people[j].checked = false;
                        --check_count;
                    }
                }
            }
        }
    }
    delete[] people;
    return max_person;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.tie(nullptr);

    unsigned int n,m;
    cin>>n;
    string *max_names = new string[n];
    unsigned int order[3];
    
    for(int i=0;i<n;++i) {
        cin>>m;
        Person *people = new Person[m];

        cin>>order[0]>>order[1]>>order[2];
        for(int j=0;j<m;++j) {
            string s;
            unsigned int u,c;
            float w;

            cin>>s>>u>>w>>c;
            people[j] = Person(s,u,w,c);
        }
        max_names[i] = get_max_person(people,m,order);

    }
    for(int i=0;i<n;++i) {
        cout<<max_names[i]<<"\n";
    }
    delete[] max_names;
    return 0;
}