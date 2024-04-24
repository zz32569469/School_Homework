#include<bits/stdc++.h>

using namespace std;

class MinMaxSearch{

    public:
        MinMaxSearch(){};

        MinMaxSearch(string x, int color, int depth){
            this->initboard=to2Dboard(x);
            this->initColor=colorTochar(color);
            this->opColor=(initColor=='O'? 'X':'O');
            this->depth=depth;
            this->sc.resize(6);
            for(int i=0;i<6;i++) this->sc[i].resize(6, INT_MIN);
        };

        void solver(){
            string ans="Aa";

            vector<string>nxtb;

            for(int i=0;i<6;i++){
                for(int j=0;j<6;j++){
                    int ret=INT_MIN;
                    if(initboard[i][j]=='+' && isValidMove(initboard, initColor, j, i)){
                        nxtb=nxtBoard(initboard, initColor, j, i);

                        ret=max(ret, dfs(nxtb, opColor, 1));
                    }
                    sc[i][j]=ret;
                }
            }

            int x=INT_MIN;
            for(int i=0;i<6;i++){
                for(int j=0;j<6;j++){
                    if(x<sc[i][j]){
                        ans[0]=(i+'A'), ans[1]=(j+'a');
                        x=sc[i][j];
                    }
                    //cout<<sc[i][j]<<' ';
                }
                //cout<<'\n';
            }

            cout<<ans<<'\n';

            return ;
        }
    

    private:
        vector<vector<int>>sc;
        vector<string> initboard;
        int depth;
        char initColor, opColor;
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

        int colorCounter(vector<string> a, char target){
            int ret=0;
            for(auto i:a){
                for(auto c:i) ret+=(c==target);
            }

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

        bool isValidMove(vector<string> nowBoard, char nowp, int nxt_x, int nxt_y){
            if(nowBoard[nxt_y][nxt_x]!='+') return false;

            for(int i=0;i<8;i++){
                if(flipCounter(nowBoard, nowp, nxt_x, nxt_y, i)) return true; 
            }

            return false;
        }

        bool passTurn(vector<string> nowBoard, char nowp){
            for(int i=0;i<6;i++){
                for(int j=0;j<6;j++){
                    if(nowBoard[i][j]=='+' && isValidMove(nowBoard, nowp, j, i)) return false;
                }
            }

            return true;
        }

        bool endGame(vector<string> nowBoard){
            return passTurn(nowBoard, 'X') && passTurn(nowBoard, 'O');
        }

        vector<string> nxtBoard(vector<string> nowBoard, char nowp, int nxt_x, int nxt_y){
            vector<string> ret=nowBoard;

            for(int i=0;i<8;i++){
                if(flipCounter(nowBoard, nowp, nxt_x, nxt_y, i)){
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

        int dfs(vector<string> nowBoard, char nowp, int step){
            //Max layer if depth%2==0

            if(step>=depth) return colorCounter(nowBoard, initColor)-colorCounter(nowBoard, opColor);

            char nxtp=(nowp=='O'? 'X':'O');
            vector<string>nxtb;
            int ret = (step%2==1)? INT_MAX:INT_MIN;

            if(passTurn(nowBoard, nowp)) return dfs(nowBoard, nxtp, step+1);

            for(int i=0;i<6;i++){
                for(int j=0;j<6;j++){
                    if(nowBoard[i][j]=='+' && isValidMove(nowBoard, nowp, j, i)){
                        nxtb=nxtBoard(nowBoard, nowp, j, i);

                        if(step%2) ret=min(ret, dfs(nxtb, nxtp, step+1));
                        else ret=max(ret, dfs(nxtb, nxtp, step+1));
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
        string s;
        int color, depth;
        cin>>s>>color>>depth;

        MinMaxSearch pb(s, color, depth);

        pb.solver();

    }
}