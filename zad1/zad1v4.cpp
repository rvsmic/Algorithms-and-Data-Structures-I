#include <iostream>
#include <cstring>

using namespace std;

string compare_people(string *names,unsigned int *count,float *height,unsigned int *speed,unsigned int size,unsigned int order[]) {
    string max_name;
    for(int i=0;i<3;i++) {
        if(order[i]==1) {
            unsigned int max_count = 0;
            for(int j=0;j<size;j++) {
                if(count[j]>max_count) {
                    max_count = count[j];
                    max_name = names[j];
                }
            }
            unsigned int check_count = 0;
            for(int j=0;j<size;j++) {
                if(count[j]==max_count) {
                    check_count++;
                }
            }
            if(check_count>1) {
                string *new_names = new string[check_count];
                float *new_height = new float[check_count];
                unsigned int *new_count = new unsigned int[check_count], *new_speed = new unsigned int[check_count];
                unsigned int k=0;
                for(int j=0;j<size;j++) {
                    if(count[j]==max_count) {
                        memcpy(&new_names[k], &names[j], sizeof(string));
                        memcpy(&new_count[k], &count[j], sizeof(unsigned int));
                        memcpy(&new_height[k], &height[j], sizeof(float));
                        memcpy(&new_speed[k], &speed[j], sizeof(unsigned int));
                        k++;
                    }
                }
                size = check_count;

                delete[] count;
                delete[] height;
                delete[] speed;

                names = new_names;
                count = new_count;
                height = new_height;
                speed = new_speed;
            }
            else {
                break;
            }
        }
        if(order[i]==2) {
            float max_height = 0;
            for(int j=0;j<size;j++) {
                if(height[j]>max_height) {
                    max_height = height[j];
                    max_name = names[j];
                }
            }
            unsigned int check_count = 0;
            for(int j=0;j<size;j++) {
                if(height[j]==max_height) {
                    check_count++;
                }
            }
            if(check_count>1) {
                string *new_names = new string[check_count];
                float *new_height = new float[check_count];
                unsigned int *new_count = new unsigned int[check_count], *new_speed = new unsigned int[check_count];
                unsigned int k=0;
                for(int j=0;j<size;j++) {
                    if(height[j]==max_height) {
                        memcpy(&new_names[k], &names[j], sizeof(string));
                        memcpy(&new_count[k], &count[j], sizeof(unsigned int));
                        memcpy(&new_height[k], &height[j], sizeof(float));
                        memcpy(&new_speed[k], &speed[j], sizeof(unsigned int));
                        k++;
                    }
                }
                size = check_count;

                delete[] count;
                delete[] height;
                delete[] speed;

                names = new_names;
                count = new_count;
                height = new_height;
                speed = new_speed;
            }
            else {
                break;
            }
        }
        if(order[i]==3) {
            unsigned int max_speed = 0;
            for(int j=0;j<size;j++) {
                if(speed[j]>max_speed) {
                    max_speed = speed[j];
                    max_name = names[j];
                }
            }
            unsigned int check_count = 0;
            for(int j=0;j<size;j++) {
                if(speed[j]==max_speed) {
                    check_count++;
                }
            }
            if(check_count>1) {
                string *new_names = new string[check_count];
                float *new_height = new float[check_count];
                unsigned int *new_count = new unsigned int[check_count], *new_speed = new unsigned int[check_count];
                unsigned int k=0;
                for(int j=0;j<size;j++) {
                    if(speed[j]==max_speed) {
                        memcpy(&new_names[k], &names[j], sizeof(string));
                        memcpy(&new_count[k], &count[j], sizeof(unsigned int));
                        memcpy(&new_height[k], &height[j], sizeof(float));
                        memcpy(&new_speed[k], &speed[j], sizeof(unsigned int));
                        k++;
                    }
                }
                size = check_count;

                delete[] count;
                delete[] height;
                delete[] speed;

                names = new_names;
                count = new_count;
                height = new_height;
                speed = new_speed;
            }
            else {
                break;
            }
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
        string s, *names;
        unsigned int u,c, *count, *speed;
        float w, *height;

        cin>>m;
        names = new string[m];
        count = new unsigned int[m];
        height = new float[m];
        speed = new unsigned int[m];

        cin>>order[0]>>order[1]>>order[2];

        for(int j=0;j<m;j++) {
            cin>>s>>u>>w>>c;
            names[j]=s;
            count[j]=u;
            height[j]=w;
            speed[j]=c;
        }

        max_name[i] = compare_people(names,count,height,speed, m, order);
        delete[] names;
    }
    for(int i=0;i<n;i++) {
        cout<<max_name[i]<<"\n";
    }
    delete[] max_name;

    return 0;
}