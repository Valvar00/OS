#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
    int N_P[10][1],max_p=0,min_thr=0,max_thr=0,p_w=0,dif=0;
    cout << "Insert number of processors(up to 10)";
    cin >> max_p;
    for(int i=0; i<max_p; i++)
    {
        N_P[i][0]=0;
    }
    cout << "Insert minimum threshold" ;
    cin >> min_thr ;
    cout << "Insert maximum threshold" ;
    cin >> max_thr ;
    cout << "Insert difference to shuffle" ;
    cin >> dif ;
    while(true)
    {
        //Here i implement the distribution of systems
        cout << "\nInsert weight of the process";
        cin >> p_w ;
        int check=1;
        if(p_w==0)
            break;
        //k is needed to choose random processor to ask for process
        int k=rand()%max_p;
        //check if process weight more than threshold
        if(p_w>max_thr)
        {
            N_P[k][0]+=p_w;
            check=0;
        }
        //if less than max threshold checks if less than min threshold
        else
        {
            if(N_P[k][0]<min_thr)
            {
                N_P[k][0]+=p_w;
                check=0;
            }
            else
                //if processor has more weight that threshold it goes into the next one
                for(int i=0; i<max_p; i++)
                    if(k+i<=max_p)
                    {
                        if((N_P[k+i][0]+p_w)<max_thr)
                        {
                            N_P[i][0]+=p_w;
                            check=0;
                        }
                    }
                    else
                    {
                        //this process just done if all processors are busy too after the random one
                        for(int p=0; p<k; p++)
                            if((N_P[p][0]+p_w)<max_thr)
                            {
                                N_P[p][0]+=p_w;
                                check=0;
                            }
                    }
        }
        //if process weight is between the min threshold and max threshold it just adds to random one
        if(check==1)
        {
            N_P[k][0]+=p_w;
        }
        for(int i=0; i<max_p; i++)
            cout << N_P[i][0] << " ";
        //this process is used to reshuffle the processes weight on our processors
        for(int i=0; i<max_p; i++)
            for(int j=0; j<max_p; j++)
                //in this peace of code i checks if difference is more than constant number
                if((N_P[i][0]-N_P[j][0])>dif)
                    //in this part i choose from which process i will subtract or add
                    if(N_P[i][0]>N_P[j][0])
                    {
                        N_P[i][0]-=dif/2;
                        N_P[j][0]+=dif/2;
                    }
                    else
                    {
                        N_P[i][0]+=dif/2;
                        N_P[j][0]-=dif/2;
                    }
        //prints out the processors after reshuffling
        cout << "\nAfter reshuffling\n" ;
        for(int i=0; i<max_p; i++)
            cout << N_P[i][0] << " ";
    }
    return 0;
}
