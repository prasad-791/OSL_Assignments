#include <bits/stdc++.h>
using namespace std;

class Process{
    
    public:
    int no,arrival,burst;
    Process(){}
    Process(int no,int arrival,int burst){
        this->no = no;
        this->arrival = arrival;
        this->burst = burst;
    }
};

int context_switches=0;

int solve(Process p[],int ct[],int rt[],int n){
    int completed=0;
    int curr_time=0;
    int minrem=INT_MAX;
    bool present=false;
    int ind=-1,prevind=-1;
    while(completed!=n){
        for(int i=0;i<n;i++){
            if(p[i].arrival<=curr_time && p[i].burst < minrem && p[i].burst!=0){
                ind = i;
                minrem = p[i].burst;
                present = true;
            }   
        }
        if(!present){
            curr_time++;
            continue;
        }
        if(rt[ind]==-1){
            rt[ind] = curr_time - p[ind].arrival;
        }
        if(prevind != ind){
            prevind = ind;
            context_switches++;
        }
        curr_time++;
        p[ind].burst--;
        minrem = p[ind].burst;

        if(p[ind].burst==0){
            completed++;
            ct[ind] = curr_time;
            minrem = INT_MAX;
            present = false;
        }
    }
    return curr_time;
}

void print(int arr[],int burs[],int ct[],int tat[],int wt[],int rt[],int n,int sl){
    cout<<"|"<<setw(8)<<"Process"<<"|"<<setw(15)<<"Arrival Time"<<"|"<<setw(15)<<"Burst Time"<<"|"<<setw(20)<<"Completion Time"<<"|"<<setw(20)<<"Turn Around Time";
    cout<<"|"<<setw(15)<<"Waiting Time"<<"|"<<setw(15)<<"Response Time"<<"|"<<endl;
    for(int i=0;i<n;i++){
        cout<<"|"<<setw(8)<<i+1<<"|"<<setw(15)<<arr[i]<<"|"<<setw(15)<<burs[i]<<"|"<<setw(20)<<ct[i]<<"|"<<setw(20)<<tat[i]<<"|"<<setw(15)<<wt[i]<<"|";
        cout<<setw(15)<<rt[i]<<"|"<<endl;
    }
    cout<<"\nAverage Turn Around time = "<<(accumulate(tat,tat+n,0)/(float)n)<<endl;
    cout<<"\nAverage Waiting time = "<<(accumulate(wt,wt+n,0)/(float)n)<<endl;
    cout<<"\nScheduling Length = "<<sl<<endl;
    cout<<"\nThroughPut = "<<n<<"/"<<sl<<" = "<<(float)n/sl<<endl;
    cout<<"\nNo of Context Switches = "<<context_switches<<"\n\n";
}

int main(){
    int n;
    cout<<"Enter the no of Processes\n";
    cin>>n;
    Process proc[n];
    int arr[n],burs[n],ct[n],wt[n],tat[n];
    int rt[n];
    memset(rt,-1,sizeof(rt));
    cout<<"Enter arrival and burst time for each process\n";
    int a,b;
    for(int i=0;i<n;i++){
        cin>>a>>b;
        arr[i] = a;
        burs[i] = b;
        Process obj(i,a,b);
        proc[i] = obj;
    }
    int scheduling_len = solve(proc,ct,rt,n);
    for(int i=0;i<n;i++){
        tat[i] = ct[i]-arr[i];
        wt[i] = tat[i]-burs[i];
        wt[i] = wt[i]<=0 ? 0 : wt[i];
    }
    print(arr,burs,ct,tat,wt,rt,n,scheduling_len);
}