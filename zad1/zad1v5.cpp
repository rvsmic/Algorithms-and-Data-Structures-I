#include <iostream>
#include <cstring>

using namespace std;

char* compare_people(char **names,unsigned int *count,float *height,unsigned int *speed,unsigned int size,unsigned int order[]) {
    char *max_name = new char[100];
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
                char **new_names = new char*[check_count];
                float *new_height = new float[check_count];
                unsigned int *new_count = new unsigned int[check_count], *new_speed = new unsigned int[check_count];
                unsigned int k=0;
                for(int j=0;j<size;j++) {
                    if(count[j]==max_count) {
                        new_names[k] = new char[100];
                        memcpy(&new_names[k], &names[j], strlen(names[j])+1);
                        memcpy(&new_count[k], &count[j], sizeof(unsigned int));
                        memcpy(&new_height[k], &height[j], sizeof(float));
                        memcpy(&new_speed[k], &speed[j], sizeof(unsigned int));
                        k++;
                    }
                }
                size = check_count;

                // for(int j=0;j<check_count;j++){
                //     delete[] names[j];
                // }
                delete[] names;
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
                char **new_names = new char*[check_count];
                float *new_height = new float[check_count];
                unsigned int *new_count = new unsigned int[check_count], *new_speed = new unsigned int[check_count];
                unsigned int k=0;
                for(int j=0;j<size;j++) {
                    if(height[j]==max_height) {
                        new_names[k] = new char[100];
                        memcpy(&new_names[k], &names[j], strlen(names[j])+1);
                        memcpy(&new_count[k], &count[j], sizeof(unsigned int));
                        memcpy(&new_height[k], &height[j], sizeof(float));
                        memcpy(&new_speed[k], &speed[j], sizeof(unsigned int));
                        k++;
                    }
                }
                size = check_count;

                // for(int j=0;j<check_count;j++){
                //     delete[] names[j];
                // }
                delete[] names;
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
                char **new_names = new char*[check_count];
                float *new_height = new float[check_count];
                unsigned int *new_count = new unsigned int[check_count], *new_speed = new unsigned int[check_count];
                unsigned int k=0;
                for(int j=0;j<size;j++) {
                    if(speed[j]==max_speed) {
                        new_names[k] = new char[100];
                        memcpy(&new_names[k], &names[j], strlen(names[j])+1);
                        memcpy(&new_count[k], &count[j], sizeof(unsigned int));
                        memcpy(&new_height[k], &height[j], sizeof(float));
                        memcpy(&new_speed[k], &speed[j], sizeof(unsigned int));
                        k++;
                    }
                }
                size = check_count;

                // for(int j=0;j<check_count;j++){
                //     delete[] names[j];
                // }
                delete[] names;
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
    char** max_name = new char*[n];
    for(int i=0;i<n;i++) {

        unsigned int order[3];
        char s[100], **names;
        unsigned int u,c, *count, *speed;
        float w, *height;

        cin>>m;
        names = new char*[m];
        count = new unsigned int[m];
        height = new float[m];
        speed = new unsigned int[m];

        cin>>order[0]>>order[1]>>order[2];

        for(int j=0;j<m;j++) {
            cin>>s>>u>>w>>c;
            names[j]=new char[100];
            names[j]=s;
            count[j]=u;
            height[j]=w;
            speed[j]=c;
        }
        max_name[i] = new char[100];
        max_name[i] = compare_people(names,count,height,speed, m, order);
        //delete[] names;
    }
    for(int i=0;i<n;i++) {
        cout<<max_name[i]<<"\n";
    }
    //delete[] max_name;

    return 0;
}