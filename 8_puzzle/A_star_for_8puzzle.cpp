#include<bits/stdc++.h>

using namespace std;

class A_star_For_8puzzle{
    public:

        int total_vst=0;

        A_star_For_8puzzle(){
            this->initBoard={0, 1, 2, 3, 4, 5, 6, 7, 8};
            this->initState=-1;
        };
        A_star_For_8puzzle(long long x){
            this->initState=x;
            this->initBoard={0, 1, 2, 3, 4, 5, 6, 7, 8};
        };
        A_star_For_8puzzle(vector<int> x){
            this->initBoard=x;
            this->initState=-1;
        };

        void solver(){
            
            if(initState==-1) initState=transLate(initBoard);
            
            if(noSolution(initState)){
                cout<<"No solution!!\n";
                return ;
            }

            int pri=0;
            g[initState]=0;
            fa[initState]={-1, ""};

            pq.push({g[initState]+h(initState), pri++, initState});
            

            while(!pq.empty()){
                auto [f, cnt, nowState]=pq.top();
                pq.pop();

                total_vst+=1;

                //cout<<nowState<<' '<<f<<'\n';

                if(checkGoal(nowState)){
                    findAnswer(nowState);
                    
                    //cout<<"Step: "<<pattern.size()-1<<'\n';
                    for(int i=0;i<pattern.size();i++){
                        //for(auto s:pattern[i]){
                        //    cout<<s<<'\n';
                        //}
                        if(i!=pattern.size()-1) cout<<operation[i]<<'\n';
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

                if(up){
                    long long nxtPos=t*1000;
                    nxtState=nowState;
                    nxtState+=nowState/nxtPos%10*t;
                    nxtState-=nowState/nxtPos%10*nxtPos;

                    //cout<<"up:"<<' '<<nxtState<<'\n';

                    if(!vsted[nxtState]){
                        fa[nxtState]={nowState, "up"};
                        g[nxtState]=g[nowState]+1;
                        pq.push({g[nxtState]+h(nxtState), pri++, nxtState});
                    } 
                }

                if(down){
                    long long nxtPos=t/1000;
                    nxtState=nowState;
                    nxtState-=nowState/nxtPos%10*nxtPos;
                    nxtState+=nowState/nxtPos%10*t;

                    //cout<<"down:"<<' '<<nxtState<<'\n';

                    if(!vsted[nxtState]){
                        fa[nxtState]={nowState, "down"};
                        g[nxtState]=g[nowState]+1;
                        pq.push({g[nxtState]+h(nxtState), pri++, nxtState});
                    } 
                }

                if(left){
                    long long nxtPos=t*10;
                    nxtState=nowState;
                    nxtState+=nowState/nxtPos%10*t;
                    nxtState-=nowState/nxtPos%10*nxtPos;

                    //cout<<"left:"<<' '<<nxtState<<'\n';

                    if(!vsted[nxtState]){
                        fa[nxtState]={nowState, "left"};
                        g[nxtState]=g[nowState]+1;
                        pq.push({g[nxtState]+h(nxtState), pri++, nxtState});
                    } 
                }

                if(right){
                    long long nxtPos=t/10;
                    nxtState=nowState;
                    nxtState+=nowState/nxtPos%10*t;
                    nxtState-=nowState/nxtPos%10*nxtPos;

                    //cout<<"right:"<<' '<<nxtState<<'\n';

                    if(!vsted[nxtState]){
                        fa[nxtState]={nowState, "right"};
                        g[nxtState]=g[nowState]+1;
                        pq.push({g[nxtState]+h(nxtState), pri++, nxtState});
                    } 
                }
            }
        }

        
    private:
        
        vector<int>initBoard;
        long long initState;
        priority_queue<tuple<int, int, long long>, vector<tuple<int, int, long long>>, greater<tuple<int, int, long long>>>pq;
        unordered_map<long long, int>g;
        unordered_map<long long, bool>vsted;
        unordered_map<long long, pair<long long, string>>fa;
        vector<vector<string>>pattern;
        vector<string>operation;

        
        long long transLate(vector<int> x){
            long long ret=0, p=1;
            for(int i=8;i>=0;i--) ret+=p*x[i], p*=10;
            return ret;
        }
        
        vector<string> turnTranslate(long long x){
            vector<string>ret;
            long long p=100000000;
            for(int i=0;i<3;i++){
                ret.push_back(string());
                for(int j=0;j<3;j++, p/=10){
                    ret.back()+=('0'+x/p%10);
                }
            }
            return ret;
        }

        int h(long long x){
            long long ret=0, p=1;
            for(int i=0;i<9;i++, p*=10){
                long long now=x/p%10;
                if(now==0) continue;
                long long row=now/3, col=now%3, g_row=(8-i)/3, g_col=(8-i)%3;
                ret+=abs(g_row-row)+abs(g_col-col);
            }
            return ret;
        }

        tuple<int, int, int> findZero(long long x){
            long long p=1;
            for(int i=8;i>=0;i--, p*=10){
                if(x/p%10==0){
                    return {8-i, i/3, i%3};
                }
            }
        }

        bool checkGoal(long long x){
            return x==12345678;
        }

        void findAnswer(long long x){
            while(x!=-1){
                //cout<<x<<'\n';
                pattern.push_back(turnTranslate(x));
                operation.push_back("move 0 to "+fa[x].second);
                x=fa[x].first;
            }
            reverse(pattern.begin(), pattern.end());
            operation.pop_back();
            reverse(operation.begin(), operation.end());
            
        }

        bool noSolution(long long x){
            string s=to_string(x);

            int  cnt=0;
            for(int i=0;i<9;i++){
                for(int j=i;j<9;j++){
                    if(s[i]=='0' || s[j]=='0') continue;
                    if(s[i]>s[j]) cnt++;
                }
            }

            return cnt%2;
        }
};

int main(){
    //ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    vector<int>init={   1, 2, 3, 
                        4, 5, 6, 
                        7, 8, 0};// give a 8-puzzle
    
    long long x=-1;
    cin>>x;

    if(x==12345678){
        cout<<"It is the goal state.\n";
        return 0;
    }

    A_star_For_8puzzle pb(x);
    pb.solver();
    //cout<<pb.total_vst<<'\n';

    //cout<<"Fin.\n";
}
