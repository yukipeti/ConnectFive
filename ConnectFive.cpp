#include <vector>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void Standby(void);                                           //開始前準備
void BoardOutput(void);                                        //盤面の出力
void Game(void);                                                //入力処理
void BoardScan(int x, int y);                                   //盤面の調査
int BoardScanSub(int x, int y, int MoveX, int MoveY);          //置いた場所を中心に並ぶ個数の調査
void Finish(void);                                              //ゲーム終了処理

string YesOrNo;
int PlayerNumber=1;
int BoardSize=0;
string PlayerNameOne,PlayerNameTwo;
vector<vector<int>> PlayBoard;

//main
int main()
{
    Standby();

    int i;
    string BoardSizeSub;

    while(1)
    {
        cout << "盤面のサイズを入力してください。(6<n<21) n*n" << endl << "n=";
        cin >> BoardSizeSub;
        try
        {
            BoardSize=stoi(BoardSizeSub);
        }
        catch(const invalid_argument& e)
        {
            cout << "数値を入力してください" << endl;
        }
        if (BoardSize < 7 && BoardSize!=0) cout << "値が小さすぎます" << endl;
        else if (BoardSize > 20) cout << "値が大きすぎます" << endl;
        else if(BoardSize!=0) break;
    }
    cout << endl;

    PlayBoard=vector<vector<int>>(BoardSize, vector<int>(BoardSize, 0));

    BoardOutput();

    cout<<"ゲームスタート！"<<endl;

    for(i=0;i<(BoardSize * BoardSize); i++)
    {
        Game();
        BoardOutput();
        if(PlayerNumber < 2) PlayerNumber++;
        else PlayerNumber=1;
    }

    return 0;
}
//開始前準備-------------------------------------------------
void Standby(void)
{
    cout << "五目並べを開始しますか？ [y/n]" << endl;
    while(1)
    {
        cin >> YesOrNo;

        if (YesOrNo == "n")
        {
            cout << "そう....またね.... ;^;" << endl;
            exit(0);
        } else if (YesOrNo != "y")
        {
            cout << "[y]か[n]を入力してください" << endl;
        }else break;
    }

    cout << "~~五目並べRule~~" << endl << "縦横斜め五個自分の駒を揃えたら勝ち!!!!!!" << endl;

    cout << "プレイヤー名を入力してください" << endl;
    cout << "しかし駒は[P1=●],[P2=◯]固定です" << endl;

    cout << "P1=";
    cin >> PlayerNameOne;
    while(1)
    {
        cout << "P2=";
        cin >> PlayerNameTwo;
        if(PlayerNameTwo==PlayerNameOne)
        {
            cout << "同じ名前は使用できません" << endl;
        }
        else break;
    }
}
//盤面の出力--------------------------------------------------------
void BoardOutput(void)
{
    int i,j;

    cout << "  ";
    for(i=0; i < BoardSize; i++)
    {
        cout << setw(2) << i+1;
    }
    cout << endl;
    for(i=0; i < BoardSize; i++)
    {
        cout << setw(2) << i+1 << " ";
        for(j=0; j < BoardSize; j++)
        {
            switch(PlayBoard[j][i])
            {
                case 0: cout << "- "; break;
                case 1: cout << "● "; break;
                case 2: cout << "◯ "; break;
            }
        }
        cout << endl;
    }
    cout << endl;
}
//入力処理--------------------------------------------------------
void Game(void)
{
    string x,y;
    int X,Y;

    switch(PlayerNumber)
    {
        case 0: cout << "-"; break;
        case 1: cout << PlayerNameOne << "(●)"; break;
        case 2: cout << PlayerNameTwo << "(◯)"; break;
    }
    cout<< "のターンです。" <<endl;
    while(1)
    {
        while(1)
        {
            cout << "置く場所を決めてください(x y) ";
            cin >> x >> y; //xの後に　入れないと処理止まるからどうにかしろ
            try
            {
                X = stoi(x);
                Y = stoi(y);
            }
            catch(const invalid_argument& e){}

            if (X == 0 || Y == 0 || X > BoardSize || Y > BoardSize) cout << "不正な入力です" << endl;
            else if (X >= 0 && X <= BoardSize && Y >= 0 && Y <= BoardSize) break;
            else cout << "その場所にはおけません" << endl;
        }
        X--; Y--;

        if(PlayBoard[X][Y] == 0)
        {
            PlayBoard[X][Y]=PlayerNumber;
            break;
        } else cout << "その場所にはおけません" << endl;
    }
    BoardScan(X, Y);
}
//盤面の調査(五つならんだかどうか)--------------------------------------------------------
void BoardScan(int x, int y)
{
    int n[4];                  //縦横斜めに並んだ数(八方向)
    int MoveX, MoveY;
    int i;

    MoveX = 1; MoveY = 1;     //[＼]方向
    n[0] = BoardScanSub(x, y, MoveX, MoveY);

    MoveX = 0; MoveY = 1;     //[│]方向
    n[1] = BoardScanSub(x, y, MoveX, MoveY);

    MoveX = 1; MoveY = 0;     //[─]方向
    n[2] = BoardScanSub(x, y, MoveX, MoveY);

    MoveX = -1; MoveY = 1;    //[／]方向
    n[3] = BoardScanSub(x, y, MoveX, MoveY);

    for( i = 0; i < 4; i++ ){
        if(n[i] == 5) Finish();
    }

}

int BoardScanSub(int x, int y, int MoveX, int MoveY)
{
    int n=1;                 //置いた場所の一個分を初期化
    int i,j,k;

    for(i=1;i<5;i++)
    {
        j=x+(MoveX * i);
        k=y+(MoveY * i);
        if(j==10 || j==-1 || k==10 || k==-1) break;
        else if(PlayBoard[j][k] == PlayerNumber) n+=1;
    }
    for(i=1;i<5;i++)
    {
        j=x+(-1 * MoveX * i);
        k=y+(-1 * MoveY * i);
        if(j==10 || j==-1 || k==10 || k==-1) break;
        else if(PlayBoard[j][k] == PlayerNumber) n+=1;
    }

    return n;
}
//決着～ゲーム終了-----------------------------------------------------
void Finish()
{
    BoardOutput();
    if(PlayerNumber==1) cout << PlayerNameOne << "(";
    else if(PlayerNumber==2) cout << PlayerNameTwo << "(";

    switch (PlayerNumber)
    {
        case 0: cout << "-"; break;
        case 1: cout << "●"; break;
        case 2: cout << "◯"; break;
    }
    cout << ")の勝利です！" << endl;

    exit(0);
}