#ifndef MANUAL
#define MANUAL
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/* -------------------------- 1. 이분탐색 -------------------------- */
vector<int> sorted;
int search_b(int n, int size);
void theApple();
int conditionalMaxPartialSum(const vector<int>& v, int K);
int getMaxEvenLen(const vector<int>& v, int K);
/* -------------------------- 2. -------------------------- */




/* -------------------------- 3. 중복 제거/확인 -------------------------- */
void compressArray(int arr[], int& size);
void compressVector(vector<int>& v);
bool hasDup(int arr[], int size);
pair<vector<int>, vector<int>> getMinMaxPositions(const vector<int>& v);
void test3();

/* -------------------------- 4. 순열과 조합 -------------------------- */
int n, r;
vector<int> sel;
vector<int> v;
vector<bool> seen;
int cnt; 
void comb(int cur, int st);   // 조합 nCr: 오름차순 선택
void comb_d(int cur, int st);   // 중복조합 nHr: 오름차순 중복 허용 선택
void perm(int cur);   // nPr 순열
void perm_d(int cur);   // n^r 중복순열
void comb_z(int cur, int st, int d);
void dfs(int d);
void test4();

/* -------------------------- 5. 그리드 탐색 -------------------------- */
// ------------- 5-1 십자형 완전 탐색 (비정방)   ------------- //
int dc[] = {1, 0, -1, 0};
int dr[] = {0, 1, 0, -1};
int board_n[10][15];
int cross_search_n();

#endif