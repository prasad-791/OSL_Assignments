// Prasad Sanjay Khalkar
// Roll No: 33138
// TE-09 L-09

#include <bits/stdc++.h>
using namespace std;


// Process Structure
class Process{
    
    public:
    int no,arrival,burst;
    Process(){}
    Process(int no,int arrival,int burst){
        this->no = no;
        this->arrival = arrival;
        this->burst = burst;
    }
    void printproc(){
        cout<<no<<" "<<arrival<<" "<<burst<<endl;
    }
};


// comparator for sorting the processes based on arrival time
bool cmp(Process a,Process b){
    return a.arrival < b.arrival;
}

int context_switches = -1;

// printing 
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

// Round Robin Scheduling Algo
int rr(Process proc[],int n,int q,int ct[],int rt[]){
    int curr_time=0,completed = 0;
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


// SJF Scheduling Algo
int sjf(Process p[],int ct[],int rt[],int n){
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

int main(){
    int n,q;
    cout<<"Enter the no of Processes\n";
    cin>>n;     // no of processes
    Process proc[n];
    int arr[n],burs[n],ct[n],wt[n],tat[n];
    int rt[n];
    memset(rt,-1,sizeof(rt));   // initialising the response time to -1
    cout<<"Enter arrival and burst time for each process\n";
    int a,b;
    for(int i=0;i<n;i++){
        cin>>a>>b;      // arrival time and burst time of each process
        arr[i] = a;
        burs[i] = b;
        Process obj(i,a,b);
        proc[i] = obj;
    }
    int scheduling_len;
    int choice;     // choice for sjf or rr
    cout<<"\nEnter 1 for SJF\n";
    cout<<"Enter 2 for Round Robin\n";

    cout<<"\nEnter your choice\n";
    cin>>choice;

    switch(choice){
        case 1:
            scheduling_len = sjf(proc,ct,rt,n);
            break;
        case 2:
            cout<<"\nEnter the value of time quantum\n";
            cin>>q;     // time quantum for rr
            sort(proc,proc+n,cmp);
            scheduling_len = rr(proc,n,q,ct,rt);
            break;
        default:
                cout<<"\nEnter valid choice\n";
    }
    // calculating waiting time and turn around time 
    for(int i=0;i<n;i++){
        tat[i] = ct[i]-arr[i];
        wt[i] = tat[i]-burs[i];
        wt[i] = wt[i]<=0 ? 0 : wt[i];
    }
    // printing
    print(arr,burs,ct,tat,wt,rt,n,scheduling_len);

}