#include<iostream>
#include<thread>
#include<ctime>
#include<mutex>
#include<chrono>

using namespace std;

int tot=0;
mutex tlock;

void sum(int number, int st, int ed){
    int ret=0;

    string s="Thread "+to_string(number)+" start.\n";

    cout<<s;

    
    for(int i=st;i<=ed;i++){
        tlock.lock();
        tot+=i;
        tlock.unlock();
    }

    s="Thread "+to_string(number)+": tot to"+to_string(tot)+"\n";
    cout<<s;

    s="Thread "+to_string(number)+" end.\n";
    cout<<s;

    tot+=ret;
    return;
}

int main(){
    int n, x;
    cin>>x>>n;

    thread th[x+1];
    int last=0, sz=n/x;

    clock_t st, ed;
    st=clock();

    for(int i=0;i<x;i++){
        int next=min(last+sz, n);
        th[i]=thread(&sum, i+1, last+1, next);
        last=next;
    }

    for(int i=0;i<x;i++){
        th[i].join();
    }

    cout<<"tot: "<<tot<<'\n';
    ed=clock();

    cout<<ed-st<<'\n';
    cout<<"main is end.\n";
    return 0;
}