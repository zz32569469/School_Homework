#include<iostream>
#include<ctime>

using namespace std;

int tot=0;

int main(){
    int n;
    cin>>n;

    clock_t st, ed;
    st=clock();

    for(int i=1;i<=n;i++){
        tot+=i;
    }

    cout<<"tot: "<<tot<<'\n';
    ed=clock();

    cout<<ed-st<<'\n';
    cout<<"main is end.\n";
    return 0;
}