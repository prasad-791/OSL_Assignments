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
    void print(){
        cout<<no<<" "<<arrival<<" "<<burst<<endl;
    }
};

bool cmp(Process a,Process b){
    return a.arrival < b.arrival;
}

int context_switches = -1;


int solve(Process proc[],int n,int q,int ct[],int rt[]){
    int completed = 0,curr_time = 0;
    bool ispresent = false;
    // while(completed!=n){
    //     ispresent = false;
    //     for(int i=0;i<n;i++){
    //         if(proc[i].arrival <= curr_time && proc[i].burst!=0){
    //             ispresent = true;

    //             if(rt[proc[i].no]==-1){
    //                 rt[proc[i].no] = curr_time - proc[i].arrival;
    //             }

    //             if(proc[i].burst > q){
    //                 proc[i].burst -= q;
    //                 curr_time += q;
    //             }else{
    //                 curr_time += proc[i].burst;
    //                 proc[i].burst = 0;
    //                 completed++;
    //                 ct[proc[i].no] = curr_time;
    //             }
    //             context_switches++;
    //         }
    //     }
    //     if(!ispresent){
    //         curr_time++;
    //     }
    // }

    vector<int> rq;
    int inqueue[n];
    for(int i=0;i<n;i++){
        inqueue[i] = 0;
    }
    for(int i=0;i<n;i++){
        if(curr_time >= proc[i].arrival && inqueue[proc[i].no]==0){
            rq.push_back(proc[i].no);
            inqueue[proc[i].no] = 1;
        }
    }
    int ind;
    while(completed!=n){
        if(rq.size()!=0){
            ind = rq[0];
            rq.erase(rq.begin());
            if(rt[ind]==-1){
                rt[ind] = curr_time - proc[ind].arrival;
            }
            if(proc[ind].burst > q){
                curr_time += q;
                proc[ind].burst -= q;
            }else{
                curr_time += proc[ind].burst;
                proc[ind].burst = 0;
                completed++;
                ct[ind] = curr_time;
            }
            for(int i=0;i<n;i++){
                if(curr_time >= proc[i].arrival && inqueue[proc[i].no]==0){
                    rq.push_back(proc[i].no);
                    inqueue[proc[i].no] = 1;
                }
            }
            context_switches++;
            if(proc[ind].burst!=0){
                rq.push_back(ind);
            }
        }else{
            curr_time++;
            for(int i=0;i<n;i++){
                if(curr_time >= proc[i].arrival && inqueue[proc[i].no]==0){
                    rq.push_back(proc[i].no);
                    inqueue[proc[i].no] = 1;
                }
            }
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
    int n,q;
    cout<<"Enter the no of Processes and the value of Quantum\n";
    cin>>n>>q;
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
    sort(proc,proc+n,cmp);

    int scheduling_len = solve(proc,n,q,ct,rt);

    for(int i=0;i<n;i++){
        tat[i] = ct[i]-arr[i];
        wt[i] = tat[i]-burs[i];
        wt[i] = wt[i]<=0 ? 0 : wt[i];
    }
    print(arr,burs,ct,tat,wt,rt,n,scheduling_len);
}