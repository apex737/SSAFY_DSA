#include <bits/stdc++.h>

using namespace std;
int T, N;
int board[15][15];
bool blocked[15][4];
struct Node
{
  int r, c;
};

void dfs(int cur, int sum, int cnt);

int dr[] = {1, 0, -1, 0};
int dc[] = {0, -1, 0, 1};

vector<Node> vp;

int mn;
int mxCnt;
/* 문풀 전략
1. 가장자리 제외하고 벡터에 넣기
2. 해당 노드에서 가능한 모든 경로를 확인
-> 막힌 경로가 있다면 경로 폐기 (가지치기)
*/
int main()
{
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    mn = 999;
    mxCnt = 0;
    cin >> N;
    vp.clear();
    memset(blocked, 0, sizeof(blocked));
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
      {
        cin >> board[i][j];
        // 가장자리 제외하고 벡터에 넣기
        if (board[i][j] == 1 && i != 0 && i != N - 1 && j != 0 && j != N - 1)
          vp.push_back({i, j});
      }

    // 가능한 모든 경로를 시도
    dfs(0, 0, 0);
    cout << "#" << t << " " << mn << "\n";
  }
  return 0;
}

/* DFS
Depth: Core 수
Width: 가능한 경로의 수

* 왜캐 빡센가?? *
1. 다중목적 최적화 (lexicographic Optimization)
=> mxCnt 중 mn을 선택해야하며 mxCnt가 mn보다 우선되는걸 고려해야한다. 

2. 그리디 vs DFS (완탐/백트래킹)
=> 선택 간 간섭 때문에 LO가 GO가 아닌 경우가 존재한다.

3. 마커 철회가 낯설다.. 근데 DFS 기본 예제라 익숙해져야함
*/
/**
 * @param cur : 현재 DFS 깊이 (몇번째 코어인가?) 
 * @param sum : 경로 누산값
 * @param cnt : 경로가 존재하는 코어 개수
 */
void dfs(int cur, int sum, int cnt)
{
  // 현재 cnt에 남은 코어 다 더해도 mxCnt 미만이면 가망 없음
  if((cnt + (vp.size() - cur)) < mxCnt) return;

  // 모든 노드 탐색했으면 최소거리 갱신 후 리턴
  if (cur == vp.size())
  {
    // mxCnt가 갱신되면 무조건 그걸 우선함
    if(cnt > mxCnt) 
    {
      mxCnt = cnt;
      mn = sum;
    } 
    else if (cnt == mxCnt) {
      mn = min(mn, sum);
    }
    return;
  }

  // 개별 노드에서 사방탐색을 수행하면서
  // 가능한 경로를 체크하고 막힌 경로가 있으면 가지치기
  for (int dir = 0; dir < 4; dir++)
  {
    if (!blocked[cur][dir])
    {
      int r, c;
      // 현재 코어 위치 잡기
      r = vp[cur].r;
      c = vp[cur].c;
      for (int d = 1;; d++)
      {
        // 코어를 기준으로 d 만큼 이동하며 탐색
        int nr = r + dr[dir] * d;
        int nc = c + dc[dir] * d;

        // 경계에 닿으면 경로 하나가 확정됨; 다음으로 이동
        if (nr < 0 || nc < 0 || nr >= N || nc >= N)
        {
          dfs(cur + 1, sum + (d - 1), cnt + 1);
          /* ---------- step return 즉시 경로 폐기! ---------- */
          for (int dd = 1; dd < d; dd++)
            board[r + dr[dir] * dd][c + dc[dir] * dd] = 0;
          break;
        }
        // 다른 코어에 닿으면 경로를 폐기하고 마커에 닿아도 탐색종료
        // 기존 마커도 전부 철회
        int b;
        if ((b = board[nr][nc]) > 0)
        {
          if (b == 1)
            blocked[cur][dir] = 1;

          // 마커에 닿을 때 (b==2) 포함; 마커 철회
          for (int dd = 1; dd < d; dd++)
            board[r + dr[dir] * dd][c + dc[dir] * dd] = 0;
          break;
        }
        // 경계에 닿기 전까진 보드마킹
        board[nr][nc] = 2;
      }
    }
  }

  // 사방탐색 성공 여부와 무관하게 경로 자체를 pass
  // 이 선택이 더 많은 경로를 살릴 수도 있기 때문임..!
  dfs(cur+1, sum, cnt);
}
