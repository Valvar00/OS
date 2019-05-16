#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

double working_set[10];
double str[]={6,6,6,101,5,5,5,101,100,100,103,7,7,7,7};

int work_set_init(int len){
    int j=1,check=1;
    working_set[0]=str[0];
    for(int i=1;i<len;i++){
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
    return j;
}

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
    int n = sizeof(str)/sizeof(*str);
    long av_page_fault_service_time = 8000000,m_acs_t = 200 ;
    int frames=62;
    int page_faults_max=62;
    double *p1,*p2;
    int j=work_set_init(n);
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

    double page_requests[6],eq_request[6],rand_request[6];
    for(int i=0;i<j;i++){
        page_requests[i]=working_set[i]/p1[i];
    }
    for(int i=0;i<j;i++){
        eq_request[i]=working_set[i]/equal_all;
    }
    for(int i=0;i<j;i++){
        rand_request[i]=working_set[i]/p2[i];
    }
    cout << "\nProportional requests: " ;
    for(int i=0;i<j;i++)
        if(round(page_requests[i])!=0)
            cout << round(page_requests[i]) << " ";
        else
            cout << "1 " ;
    cout << "\nEqual requests: "  ;
    for(int i=0;i<j;i++)
        if(round(eq_request[i])!=0)
            cout << round(eq_request[i]) << " ";
        else
            cout << "1 " ;
    cout << "\nRandom requests: " ;
    for(int i=0;i<j;i++)
        if(round(rand_request[i])!=0)
            cout << round(rand_request[i]) << " ";
        else
            cout << "1 " ;
    cout << "\n" ;

    double prop_faults=0,eq_faults=0,rand_faults=0;
    for(int i=0;i<j;i++){
        prop_faults+=fmod(working_set[i],p1[i]);
    }
    for(int i=0;i<j;i++){
        if(i!=1 || i!=4)
            eq_faults+=fmod(working_set[i],equal_all);
        else
            eq_faults+=fmod(working_set[i],equal_all+1);
    }
    for(int i=0;i<j;i++){
        rand_faults+=fmod(working_set[i],p2[i]);
    }
    double prop_fr=prop_faults/page_faults_max;
    double rand_fr=rand_faults/page_faults_max;
    double eq_fr=eq_faults/page_faults_max;
    cout << "\nProportional faults: " << prop_fr ;
    cout << "\nEqual faults: " <<  rand_fr;
    cout << "\nRandom faults: " <<  eq_fr;

    cout << "\n\nEffective Access Time(EAT) for Proportional " ;
    cout << ((1-prop_fr)*m_acs_t+prop_fr*av_page_fault_service_time);
    cout << "\nEffective Access Time(EAT) for Equal " ;
    cout << ((1-rand_fr)*m_acs_t+rand_fr*av_page_fault_service_time);
    cout << "\nEffective Access Time(EAT) for Random " ;
    cout << ((1-eq_fr)*m_acs_t+eq_fr*av_page_fault_service_time);
    return 0;
}
