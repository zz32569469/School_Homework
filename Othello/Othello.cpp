#include<bits/stdc++.h>

using namespace std;

class MinMaxSearch{

    public:
        MinMaxSearch(){};

        MinMaxSearch(string x, int color, string nxt){
            this->initboard=to2Dboard(x);
            this->initColor=color;
            this->nxt=nxt;
        };

        int solver(){
            vector<string> a=nxtBoard(initboard, initColor, nxt);
            for(auto i:a) cout<<i;
            cout<<'\n';
            return 0;
        }
    

    private:
        vector<string> initboard;
        int initColor;
        string nxt;
        int dirx[8]={0, 1, 1, 1, 0, -1, -1, -1};
        int diry[8]={-1, -1, 0, 1, 1, 1, 0, -1};
        //enum dirction {up, up_right, right, down_right, down, down_left, left, left_up};

        vector<string> to2Dboard(string s){
            vector<string>ret(6);
            for(int i=0;i<6;i++){
                ret[i].resize(6);
                for(int j=0;j<6;j++) ret[i][j]=s[6*i+j];
            }

            return ret;
        }

        char colorTochar(int x){
            return x==1? 'X':'O';
        }

        int colorCounter(vector<string> a, int color){
            char target=colorTochar(color);

            int ret=0;
            for(auto i:a){
                for(auto c:i) ret+=(c==target);
            }

            return ret;
        }

        pair<int, int> nxtTrans(string x){
            pair<int, int>ret;
            ret.first=x[1]-'a', ret.second=x[0]-'A';
            return ret;
        }

        int flipCounter(vector<string> board, char nowp, int nxt_x, int nxt_y, int from){
            char nxtp=(nowp=='O'? 'X':'O');

            int now_x=nxt_x, now_y=nxt_y;
            string strt;

            while(now_x>=0 && now_y>=0 && now_x<6 && now_y<6){
                strt+=board[now_y][now_x];
                now_x+=dirx[from], now_y+=diry[from];
            }

            strt[0]=nowp;
            int ret=0;
            for(int i=1;i<strt.size();i++){
                if(strt[i]==nowp) return ret;
                else if(strt[i]==nxtp) ret++;
                else return 0;
            }

            return 0;
        }

        vector<string> nxtBoard(vector<string> nowBoard, int color, string nxt){
            char nowp=colorTochar(color);
            auto [nxt_x, nxt_y]=nxtTrans(nxt);

            vector<string> ret=nowBoard;

            for(int i=0;i<8;i++){
                if(flipCounter(nowBoard, nowp, nxt_x, nxt_y, i)>0){
                    int now_x=nxt_x, now_y=nxt_y;
                    
                    while(now_x>=0 && now_y>=0 && now_x<6 && now_y<6){
                        if(ret[now_y][now_x]==nowp && (now_y!=nxt_y || now_x!=nxt_x)) break;
                        ret[now_y][now_x]=nowp;
                        now_x+=dirx[i], now_y+=diry[i];
                    }
                }
            }

            return ret;
        }
};

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int t=1;
    cin>>t;

    while(t--){
        string s, nxt;
        int color;
        cin>>s>>color>>nxt;

        MinMaxSearch pb(s, color, nxt);

        pb.solver();

    }
}