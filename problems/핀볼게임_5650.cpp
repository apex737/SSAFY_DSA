#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

/* 꿀잼 BFS 
1. 벽종류에 따라 진행방향 매핑
-> 회전과 반드시 관련 있는게 분명해보임..
=> 1: 하(ccw), 좌(cw)
=> 2: 좌(ccw), 상(cw)
=> 3: 상(ccw), 우(cw)
=> 4: 우(ccw), 하(cw)

2. 웜홀통과 로직
3. 블랙홀/벽.. 종료
1) 블랙홀이면 바로 스코어 리턴
2) flat한 벽에서 튕기면 
- s>=1; 2s+1 리턴
- s=0; 1 리턴
*/
struct Ball {
  int r,c,dir,s;
};

struct Node {
  int r,c;
};
// 하-좌-상-우
// 1-4 피규어를 회전
int dr[] = {1,0,-1,0};
int dc[] = {0,-1,0,1};
int board[101][101];
int main()
{
  int T;
  cin >> T;
  for(int t=1; t<=T; t++)
  {
    int score = 0;
    int N;
    cin >> N;
    // 웜홀 번호를 좌표 2개에 매핑
    map<int, vector<Node>> w;
    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
      {
        cin >> board[i][j];
        // 웜홀 보관
        if(board[i][j] >= 6 && board[i][j] <= 10)
          w[board[i][j]].push_back({i,j});
      }

    cout << "#" << t << " " << score << "\n";
  }
  return 0;
}