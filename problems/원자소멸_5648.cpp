#include <iostream>
#include <vector>
using namespace std;

/* 전형적인 이동 + 상태관리 시뮬레이션
핵심1. cur -> [pipes] -> nxt -> cur (상태 피드백 구조)
핵심2. 동적할당을 막기 위해 전역 선언 후 재사용

1. 벡터에 노드를 잘 넣어주기
2. while 루프를 돌면서 0.5 틱 이동
-> 그러나, float 단순 비교는 오차가 누적된다..
* ---- 좌표 스케일링으로 해상도를 높인다 ----  *
1) 오프셋 1000을 먹여서 양수 범위로 만들고
2) 2배 스케일링해서 경계를 0 <= x,y <= 4000으로 만든다.

3. 경계 이탈 시 드랍한다
*/

// 원자들의 이동 방향은 상(0), 하(1), 좌(2), 우(3)로 주어진다.
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
struct Atom
{
  int x, y, dir, K;
};

// 각 시뮬레이션 별 임시 마커
int board[4005][4005];

// 동적 할당을 막기 위해, 전역할당 후 재사용
const int OFFSET = 1000;
const int MAXN = OFFSET;
vector<Atom> cur(MAXN), pipe(MAXN), nxt(MAXN);

int main()
{
  cin.tie(0)->sync_with_stdio(0);
  int T;
  cin >> T;

  for (int t = 1; t <= T; t++)
  {
    int N;
    cin >> N;
    cur.resize(N);
    int sum = 0;
    for (int n = 0; n < N; n++)
    {
      cin >> cur[n].x >> cur[n].y >> cur[n].dir >> cur[n].K;
      cur[n].x = (cur[n].x + OFFSET) * 2;
      cur[n].y = (cur[n].y + OFFSET) * 2;
    }

    while (!cur.empty())
    {
      // 1. 좌표 업데이트
      for (auto &a : cur)
      {
        a.x += dx[a.dir];
        a.y += dy[a.dir];
      }

      // 2. 이탈 처리
      pipe.clear();
      for (auto &a : cur)
      {
        if (a.x < 0 || a.x > 4000 || a.y < 0 || a.y > 4000)
          continue;

        pipe.push_back(a);
        board[a.x][a.y]++;
      }

      // 3. 충돌 처리
      nxt.clear();
      for (auto &a : pipe)
      {
        if (board[a.x][a.y] > 1) sum += a.K;
        else nxt.push_back(a);
      }

      // 4. 재사용을 위해 초기화
      for (auto &a : pipe) 
        board[a.x][a.y] = 0;

      cur.swap(nxt);
    }

    cout << "#" << t << " " << sum << "\n";
  }
  return 0;
}