#include "__매뉴얼__.h"

int main()
{
  theApple();
}

/* -------------------------- 1. 이분탐색/투포인터 -------------------------- */
int search_b(int n, int size)
{
  int st = 0;
  int en = size;
  int mid;
  while (st < en)
  {
    mid = (st + en) / 2;
    if (sorted[mid] >= n)
      en = mid;
    else
      st = mid + 1;
  }

  return st; // n 이상인 최초 인덱스
}

void theApple()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++)
  {
    int N;
    cin >> N;
    vector<int> A(N);
    vector<int> B(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];
    int mx = 0;
    unordered_map<int,int> m;
    int sum = 0;
    for (int st = 0, en = 0; en < N; en++)
    {
      // 1. 상태변경
      m[B[en]]++;
      // 2. 제약해소
      while (m.at(B[en]) > 1)
      {
        m[B[st]]--;
        sum -= A[st];
        st++;
      }
      // 3. 출력갱신
      sum += A[en];
      mx = max(mx, sum);
    }
    //  정의된 최대 이익을 출력한다.
    cout << "#" << t << " " << mx << "\n";
  }
}

int conditionalMaxPartialSum(const vector<int> &v, int K)
/* 구간 내 음수 개수가 K개 이하인 경우에 대한 구간합의 최댓값을 반환 */
{
  int cnt, mx, sum;
  sum = cnt = 0;
  mx = -9999;
  for (int st = 0, en = 0; en < v.size(); en++)
  {
    // 1. 상태 변경
    int cur = v[en];
    if (cur < 0)
      cnt++;
    sum += cur;

    // 2. 제약 해소
    while (cnt > K)
    {
      int val = v[st];
      if (val < 0)
        cnt--;
      sum -= val;
      st++;
    }

    // 3. 출력 갱신
    mx = max(mx, sum);
  }
  return mx;
}

int getMaxEvenLen(const vector<int> &v, int K)
/* 최대 K번까지 임의의 홀수를 삭제할 수 있을 때
연속된 짝수들로만 이루어진 수열의 최대길이 */
{
  int st, en, mx, cnt;
  mx = cnt = 0;
  for (st = en = 0; en < v.size(); en++)
  {
    // 1. 상태갱신
    int cur = v[en];
    if (cur % 2 == 1)
      cnt++;
    // 2. 제약해소
    while (cnt > K)
    {
      if (v[st] % 2 == 1)
        cnt--;
      st++;
    }
    // 3. 출력갱신
    mx = max(mx, en - st + 1 - cnt);
  }
  return mx;
}

/* -------------------------- 2.   -------------------------- */

/* -------------------------- 3. 중복 제거/확인 -------------------------- */
// 1. 컨테이너 중복 제거: STL - SUE Idium
int *myUnique(int arr[], int size)
{
  int *wr = arr;                 // 확정된 값 (정렬 되었기 때문)
  int *rd = arr + 1;             // 비교할 값
  for (int i = 1; i < size; i++) // rd를 고려하여 1부터 시작
  {
    if (*wr != *rd)
      *(++wr) = *rd;
    rd++;
  }
  return ++wr; // 쓰레기가 시작하는 위치
}

void compressArray(int arr[], int &size)
{
  // 1. Sort
  sort(arr, arr + size);
  // 2. Unique: 원본 배열을 변경
  int *pTrashHead = myUnique(arr, size);
  // 중요: 포인터 뺄셈은 인덱스 차이 (sizeof(type)으로 자동 나눔)
  size = (pTrashHead - arr);
  // 3. Erase
  // 함수 밖에서 갱신된 arr, size를 써서 해결해야함
}

void compressVector(vector<int> &v)
{
  // 1. Sort
  sort(v.begin(), v.end());
  // 2. Unique
  auto pTrashHead = unique(v.begin(), v.end());
  // 3. Erase
  v.erase(pTrashHead, v.end());
}

// 2. 컨테이너 내부 중복 확인
bool hasDup(int arr[], int size)
{
  unordered_set<int> s;
  for (int i = 0; i < size; i++)
  {
    if (s.count(arr[i]))
      return true;
    s.insert(arr[i]);
  }
  return false;
}

void test3()
{
  vector<int> testVec{1, 3, 4, 1, 1, 3, 5, 5, 5, 3, 4};
  int testArr[] = {1, 3, 4, 1, 1, 3, 5, 5, 5, 3, 4};
  int size = sizeof(testArr) / sizeof(int);
  int prevSize = size;

  cout << "hasDup: ";
  cout << hasDup(testArr, size) << "\n\n";
  compressArray(testArr, size);
  cout << "compressArray: ";
  for (int i = 0; i < size; i++)
    cout << testArr[i] << " ";
  cout << "\n\n";

  cout << "compressArray + Trash: ";
  for (int i = 0; i < prevSize; i++)
    cout << testArr[i] << " ";
  cout << "\n\n";

  cout << "compressVector: ";
  compressVector(testVec);
  for (const auto &i : testVec)
    cout << i << " ";
  cout << "\n";
}

/* -------------------------- 4. 순열과 조합 -------------------------- */
void comb(int cur, int st)
{
  if (cur == r)
  {
    for (int i : sel)
    {

      cout << v[i] << " ";
    }
    cout << "\n";
    cnt++;
    return;
  }

  for (int i = st; i < n; i++)
  {
    sel[cur] = i;
    comb(cur + 1, i + 1);
  }
}

// 중복조합 nHr: 오름차순 중복 허용 선택
void comb_d(int cur, int st)
{
  if (cur == r)
  {
    for (int i : sel)
      cout << v[i] << " ";
    cout << "\n";
    cnt++;
    return;
  }

  for (int i = st; i < n; i++)
  {
    sel[cur] = i;
    comb_d(cur + 1, i);
  }
}

/* nPr 순열
- 조합을 선택하는 순서(order)가 결과에 영향을 줌
- 포지션(i) 앞의 인덱스를 선택가능 (i=0 부터 시작)
- 단, 중복 허용 안함 (seen[i]) */
void perm(int cur)
{
  if (cur == r)
  {
    for (int i : sel)
      cout << v[i] << " ";
    cout << "\n";
    cnt++;
    return;
  }

  for (int i = 0; i < n; i++)
  {
    if (seen[i])
      continue;
    seen[i] = 1;
    sel[cur] = i;
    perm(cur + 1);
    seen[i] = 0;
  }
}

// n^r 중복순열: 순서(order)가 있는 중복(dup) 조합
void perm_d(int cur)
{
  if (cur == r)
  {
    for (int i : sel)
      cout << v[i] << " ";
    cout << "\n";
    cnt++;
    return;
  }

  for (int i = 0; i < n; i++)
  {
    sel[cur] = i;
    perm_d(cur + 1);
  }
}

// depth가 z인 조합
void comb_z(int cur, int st, int z)
{
  if (cur == r)
  {
    // 1. 상태 변환

    // 2. 다이브 전 가지치기 + dfs
    /* if( !seen[d+1] ) {
      seen[d+1] = 1;
      dfs(d+1);
    }
    */
    dfs(z + 1);

    // 3. 원상복구

    return;
  }

  for (int i = st; i < v.size(); i++)
  {
    sel[cur] = i;
    comb_z(cur + 1, i + 1, z);
  }
}

// z층까지 쌓아올림
void dfs(int z)
{
  if (z == 10)
  {
    cout << "DFS\n";
    return;
  }

  // comb_z 에서만 layer를 올릴 수 있음
  // 층의 새로운 조합을 재탐색
  comb_z(0, 0, z);
}

void test4()
{
  cin >> n >> r;
  sel.resize(r);
  v.resize(n);
  seen.resize(n);
  for (int i = 0; i < n; i++)
  {
    v[i] = i + 1;
  }

  cout << "--- nPr begin ---" << "\n";
  perm(0);
  cout << n << "P" << r << " = " << cnt << "\n";
  cnt = 0;

  cout << "--- nPr end ---" << "\n\n";

  cout << "--- n^r begin ---" << "\n";
  perm_d(0);
  cout << n << "^" << r << " = " << cnt << "\n";
  cnt = 0;
  cout << "--- n^r end ---" << "\n\n";

  cout << "--- nCr begin ---" << "\n";
  comb(0, 0);
  cout << n << "C" << r << " = " << cnt << "\n";
  cnt = 0;
  cout << "--- nCr end ---" << "\n\n";

  cout << "--- nHr begin ---" << "\n";
  comb_d(0, 0);
  cout << n << "H" << r << " = " << cnt << "\n";
}

/* -------------------------- 5. 그리드 탐색 -------------------------- */
int cross_search_n()
/* 예시: 10x15 행렬의 십자 누산 값 중 최댓값 출력 */
{
  int mx = 0;
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 15; j++)
    {
      int sum = board_n[i][j];
      for (int dir = 0; dir < 4; dir++)
      {
        for (int d = 1;; d++)
        {
          int nr = i + dr[dir] * d;
          int nc = j + dc[dir] * d;
          if (nr < 0 || nr >= 10 || nc < 0 || nc >= 15)
            break;
          sum += board_n[nr][nc];
        }
      }
      mx = max(mx, sum);
    }

  return mx;
}

void test5(ifstream &infile)
{
  cout << "[RUN] test5_1: 10x15 Matrix Scan" << "\n";

  // 파일 커서가 유지된 스트림에서 10x15 채우기
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 15; j++)
    {
      if (!(infile >> board_n[i][j]))
      {
        cerr << "[ERROR] 10x15 데이터 읽기 실패!" << "\n";
        return;
      }
    }
  cout << "[SUCCESS] 10x15 데이터 로드 완료." << "\n";

  int result_n = cross_search_n();
  cout << "10x15 십자 누산 최댓값: " << result_n << "\n";
  cout << "\n";
}
