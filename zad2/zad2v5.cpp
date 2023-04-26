#include <iostream>
using namespace std;

struct Mountain {
    string name;
    unsigned int height;

    Mountain(){}
    Mountain(string name, unsigned int height) {
        this->name = name;
        this->height = height;
    }
};

bool is_power_of_2(unsigned int number) {
    short one_count = 0;
    while(number > 0 && one_count < 2) {
        if((number&1)==1) {
            one_count++;
        }
        number = number >> 1;
    }
    if(one_count == 1) {
        return true;
    }
    return false;
}

Mountain* sort_mountains(Mountain* mountains, int amount) {
    int j;
    Mountain main;
    for(int i=1;i<amount;++i) {
        j=i;
        main = mountains[i];
        while(j > 0 && main.height < mountains[j-1].height) {
            mountains[j] = mountains[j-1];
            --j;
        }
        mountains[j] = main;
    }
    return mountains;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    cin.tie(nullptr);

    short t;
    cin>>t;
    Mountain **normal_mountains = new Mountain*[t], **power_mountains = new Mountain*[t];
    int *normal_mountains_count = new int[t], *power_mountains_count = new int[t];

    for(int i=0;i<t;++i) {
        unsigned short n;
        int power_count = 0, normal_count = 0;
        string s;
        unsigned int w;

        cin>>n;

        normal_mountains[i] = new Mountain[n];
        power_mountains[i] = new Mountain[n];

        for(int j=0;j<n;++j) {
            cin>>s>>w;
            if(is_power_of_2(w)) {
                power_mountains[i][power_count] = Mountain(s,w);
                power_count++;
            }
            else {
                normal_mountains[i][normal_count] = Mountain(s,w);
                normal_count++;
            }
        }

        normal_mountains_count[i] = normal_count;
        power_mountains_count[i] = power_count;

        power_mountains[i] = sort_mountains(power_mountains[i],power_count);
        normal_mountains[i] = sort_mountains(normal_mountains[i],normal_count);
    }

    for(int i=0;i<t;++i) {
        for(int j=0;j<power_mountains_count[i];++j) {
            cout<<power_mountains[i][j].name<<"-"<<power_mountains[i][j].height<<" ";
        }
        for(int j=0;j<normal_mountains_count[i];++j) {
            cout<<normal_mountains[i][j].name<<"-"<<normal_mountains[i][j].height<<" ";
        }
        cout<<"\n";
    }
    delete[] normal_mountains;
    delete[] power_mountains;
    delete[] normal_mountains_count;
    delete[] power_mountains_count;

    return 0;
}