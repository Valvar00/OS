#include <iostream>
#include <cassert>


using namespace std;

int arr[10],weight[10]={6,5,7,2,3,4,5,6,7,1},ch=1;

int get_num(){
    char str[13];
    int k=0;
    cout << "NIP " ;
    for(int i=0;i<13;i++){
        cin >> str[i];
        if(i!=3 && i!=7 && i!=10){
            arr[k]=str[i]-48;
            if(arr[k]>10 or arr[k] <0)
                return 0;
            k++;
        }
    }
    if(str[3]=='-' && str[7]=='-' && str[10]=='-')
        return 1;
}

int NIP(int ch)
{
    int i,sum=0;
    if(ch!=0){
        //cout << "Weighted NIP:" ;
        for(i=0;i<10;i++){
            sum+=arr[i]*weight[i];
            //cout << arr[i]*weight[i] << " ";
        }
        sum-=arr[9]*weight[9];
        //cout << "\n" << "Sum=" << sum;
        //cout << "\n" << "Mod=" << sum%11 ;
        return sum;
    }
    else
        return -1;
}

void test_correct(){
    int res=NIP(1);
    assert(res==230);
}

void test_incorrect_0(){
    int res=NIP(0);
    assert(res==230);
}

void test_incorrect_1(){
    int res=NIP(0);
    assert(res==-1);
}

void testsuit(){
test_correct();
test_incorrect_0();
test_incorrect_1();
}

int main()
{
    int check=get_num();
    testsuit();
}
