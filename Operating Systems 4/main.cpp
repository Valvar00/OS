#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

double working_set[10];


double equal_allocation(int fr,int len){
return fr/len;
}

double* random_allocation(int fr,int len){
    static double fr_str[6];
    int f=fr;
    for(int i=0;i<len;i++){
        fr_str[i]=rand() % (f+1);
        if(fr_str[i]==0){
            fr_str[i]+=1;
            fr_str[0]-=1;
        }
        f-=fr_str[i];
    }
    return fr_str;
}

double* propotionall_allocation(int fr,int len){
    int sum=0;
    static double fr_str[6];
    for(int i=0;i<len;i++){
        sum+=working_set[i];
    }
    for(int i=0;i<len;i++){
        fr_str[i]=(working_set[i]/sum)*fr;
    }
    return fr_str;
}

int main()
{
    double str[]={6,6,6,101,5,5,5,101,100,100,103,7,7,7,7};
    int n = sizeof(str)/sizeof(*str),j=1,check=1;
    int frames=62;
    double *p1,*p2;
    working_set[0]=str[0];
    for(int i=1;i<n;i++){
        for(int k=0;k<j;k++){
            if(str[i]==working_set[k]){
                check=0;
            }
        }
        if(check==1){
            working_set[j]=str[i];
            j++;
        }
        check=1;
    }
    cout << "Working Set: " ;
    for(int i=0;i<j;i++)
        cout <<  working_set[i] << " " ;
    cout << "\n" ;


    p1 = propotionall_allocation(frames,j);
    p2 = random_allocation(frames,j);
    double equal_all=equal_allocation(frames,j);
    cout << "Proportional allocation: " ;
    for(int i=0;i<j;i++)
        cout << round(p1[i]) << " " ;
    cout << "\nEqual allocation: " << equal_all << "\nRandom allocation: " ;
    for(int i=0;i<j;i++)
        cout << round(p2[i]) << " " ;
    cout << "\n" ;

    double prop_faults=0,eq_faults=0,rand_faults=0;
    for(int i=0;i<j;i++){
        prop_faults+=fmod(working_set[i],p1[i]);
    }
    for(int i=0;i<j;i++){
        eq_faults+=fmod(working_set[i],equal_all);
    }
    for(int i=0;i<j;i++){
        rand_faults+=fmod(working_set[i],p2[i]);
    }
    cout << "\nProportional faults: " << prop_faults ;
    cout << "\nEqual faults: " << eq_faults ;
    cout << "\nRandom faults: " << rand_faults ;
    return 0;
}
