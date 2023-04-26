#include <iostream>

using namespace std;

//zalicza 1-5

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
    while(number>0&&one_count<2) {
        if((number&1)==1) {
            one_count++;
        }
        number = number >> 1;
    }
    if(one_count==1) {
        return true;
    }
    else {
        return false;
    }
}

Mountain* sort_mountains(Mountain* mountains, int amount) {
    int j;
    Mountain tmp;
    for(int i=1;i<amount;++i) {
        j=i;
        while(j > 0 && mountains[j].height < mountains[j-1].height) {
            tmp = mountains[j];
            mountains[j] = mountains[j-1];
            mountains[j-1] = tmp;
            --j;
        }
    }
    return mountains;
}

string* get_mountain_table(Mountain* mountains, int amount) {
    mountains = sort_mountains(mountains,amount);
    string* anwser = new string[amount];
    for(int i=0;i<amount;++i) {
        anwser[i] = mountains[i].name + '-' + to_string(mountains[i].height);
    }
    delete[] mountains;
    return anwser;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.tie(nullptr);

    short t;
    cin>>t;
    string **normal_anwser = new string*[t], **power_anwser = new string*[t];
    Mountain *normal_mountains, *power_mountains;
    int *normal_anwser_count = new int[t], *power_anwser_count = new int[t];

    for(int i=0;i<t;++i) {
        unsigned short n;
        int power_count = 0, normal_count = 0;
        string s;
        unsigned int w;

        cin>>n;

        normal_mountains = new Mountain[n];
        power_mountains = new Mountain[n];

        for(int j=0;j<n;++j) {
            cin>>s>>w;
            if(is_power_of_2(w)) {
                power_mountains[power_count] = Mountain(s,w);
                power_count++;
            }
            else {
                normal_mountains[normal_count] = Mountain(s,w);
                normal_count++;
            }
        }

        normal_anwser_count[i] = normal_count;
        power_anwser_count[i] = power_count;

        power_anwser[i] = get_mountain_table(power_mountains,power_count);
        normal_anwser[i] = get_mountain_table(normal_mountains,normal_count);
    }

    for(int i=0;i<t;++i) {
        for(int j=0;j<power_anwser_count[i];++j) {
            cout<<power_anwser[i][j]<<" ";
        }
        for(int j=0;j<normal_anwser_count[i];++j) {
            cout<<normal_anwser[i][j]<<" ";
        }
        cout<<"\n";
    }

    for(int i=0;i<t;++i) {
        delete[] power_anwser[i];
        delete[] normal_anwser[i];
    }
    delete[] normal_anwser_count;
    delete[] power_anwser_count;
    delete[] power_anwser;

    return 0;
}