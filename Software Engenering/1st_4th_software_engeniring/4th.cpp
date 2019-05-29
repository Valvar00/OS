#include <iostream>

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyz";

int main()
{
    char str[20],coded_str[20];
    int i=0,k=26,arr[20],num;
    for(i=0;i<20;i++){
        cin >> str[i] ;
        arr[i]=str[i]-96;
        if(str[i]=='`'){
            arr[i]=arr[0];
            break;
        }
    }
    for(int j=0;j<i;j++)
    {
        num=(arr[j]+arr[j+1])%k;
        coded_str[j]=alphabet[num-1];
    }
    cout << coded_str ;
}
