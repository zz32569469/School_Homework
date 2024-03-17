#include<bits/stdc++.h>

using namespace std;

class A_star_For_8puzzle{
    public:

        int total_vst;
        
        A_star_For_8puzzle(vector<int> x){
            this->initBoard=x;
            total_vst=0;
        };

        void solver(){
            long long initState=transLate(initBoard);
            g[initState]=0;
            fa[initState]=-1;

            pq.push({g[initState]+h(initState), initState});
            

            while(!pq.empty()){
                auto [f, nowState]=pq.top();
                pq.pop();

                total_vst+=1;

                //cout<<nowState<<' '<<f<<'\n';

                if(checkGoal(nowState)){
                    vector<vector<string>> fo=findAnswer(nowState);

                    for(auto step:fo){
                        for(auto pattern:step){
                            cout<<pattern<<'\n';
                        }
                        cout<<'\n';
                    }
                    return ;
                }

                if(vsted[nowState]) continue;
                vsted[nowState]=1;


                auto [nowPos, row, col]=findZero(nowState);
                long long t=1;
                for(int i=0;i<nowPos;i++) t*=10;

                long long nxtState;
                bool right=(col!=2), left=(col!=0), up=(row!=0), down=(row!=2);


                if(right){
                    long long nxtPos=t*10;
                    nxtState=nowState;
                    nxtState+=nowState/nxtPos%10*t;
                    nxtState-=nowState/nxtPos%10*nxtPos;

                    //cout<<"right:"<<' '<<nxtState<<'\n';

                    if(!vsted[nxtState]){
                        fa[nxtState]=nowState;
                        g[nxtState]=g[nowState]+1;
                        pq.push({g[nxtState]+h(nxtState), nxtState});
                    } 
                }

                if(left){
                    long long nxtPos=t/10;
                    nxtState=nowState;
                    nxtState+=nowState/nxtPos%10*t;
                    nxtState-=nowState/nxtPos%10*nxtPos;

                    //cout<<"left:"<<' '<<nxtState<<'\n';

                    if(!vsted[nxtState]){
                        fa[nxtState]=nowState;
                        g[nxtState]=g[nowState]+1;
                        pq.push({g[nxtState]+h(nxtState), nxtState});
                    } 
                }

                if(up){
                    long long nxtPos=t/1000;
                    nxtState=nowState;
                    nxtState-=nowState/nxtPos%10*nxtPos;
                    nxtState+=nowState/nxtPos%10*t;

                    //cout<<"up:"<<' '<<nxtState<<'\n';

                    if(!vsted[nxtState]){
                        fa[nxtState]=nowState;
                        g[nxtState]=g[nowState]+1;
                        pq.push({g[nxtState]+h(nxtState), nxtState});
                    } 
                }

                if(down){
                    long long nxtPos=t*1000;
                    nxtState=nowState;
                    nxtState+=nowState/nxtPos%10*t;
                    nxtState-=nowState/nxtPos%10*nxtPos;

                    //cout<<"down:"<<' '<<nxtState<<'\n';

                    if(!vsted[nxtState]){
                        fa[nxtState]=nowState;
                        g[nxtState]=g[nowState]+1;
                        pq.push({g[nxtState]+h(nxtState), nxtState});
                    } 
                }

                
            }
        }

        
    private:
        
        vector<int>initBoard;
        priority_queue<pair<int, long long>, vector<pair<int, long long>>, greater<pair<int, long long>>>pq;
        unordered_map<long long, int>g;
        unordered_map<long long, bool>vsted;
        unordered_map<long long, long long>fa;

        
        long long transLate(vector<int> x){
            long long ret=0, p=1;
            for(int i=0;i<9;i++) ret+=p*x[i], p*=10;
            return ret;
        }
        
        vector<string> turnTranlate(long long x){
            vector<string>ret;
            long long p=1;
            for(int i=0;i<3;i++){
                ret.push_back(string());
                for(int j=0;j<3;j++, p*=10){
                    ret.back()+=('0'+x/p%10);
                }
            }
            return ret;
        }

        int h(long long x){
            long long ret=0, p=1;
            for(int i=0;i<9;i++, p*=10){
                long long now=x/p%10;

                long long row=now/3, col=now%3, g_row=i/3, g_col=i%3;
                ret+=abs(g_row-row)+abs(g_col-col);
            }
            return ret;
        }

        tuple<int, int, int> findZero(long long x){
            long long p=1;
            for(int i=0;i<9;i++, p*=10){
                if(x/p%10==0){
                    return {i, i/3, i%3};
                }
            }
        }

        bool checkGoal(long long x){
            return x==876543210;
        }

        vector<vector<string>> findAnswer(long long x){
            vector<vector<string>>ret;
            while(x!=-1){
                cout<<x<<'\n';
                ret.push_back(turnTranlate(x));
                x=fa[x];
            }
            reverse(ret.begin(), ret.end());
            return ret;
        }
};

int main(){
    vector<int>init={   4, 3, 2, 
                        6, 1, 8, 
                        5, 0 ,7};// give a 8-puzzle

    A_star_For_8puzzle pb(init);
    pb.solver();
    cout<<pb.total_vst<<'\n';
    cout<<"Fin.\n";
}
