#include <iostream>
#include<stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <set>
#include <functional>
using namespace std;
const int inf = 98765432;
#define max(a,b) (a>b ? a:b)
#define min(a,b) (a<b ? a:b)

/* Coder`s high Tons of damage 10222 */

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
char dir[4] = {'R', 'L', 'D', 'U'};
char A[11][11];

struct XY {
  int x;
  int y;
  string path;
  XY(int x, int y, string path) :x(x), y(y), path(path){}
  bool operator < (const XY &XY2) const {
    if (x == XY2.x) {
      return y < XY2.y;
    }
    else {
      return x < XY2.x;
    }
  }
};

string bfs(set<XY> &v) {
  string ans;
  queue<set<XY>> q;
  q.push(v);
  while (!q.empty()) {
    set<XY> q_v;
    q_v = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) { // 0 = R  1 = L  2 = D  3 = U
      set<XY>::iterator iter;
      set<XY> move_set;
      bool break_check = false;
      for (iter = q_v.begin(); iter != q_v.end(); iter++) {
        XY tmp = *iter;
        int cur_x = tmp.x;
        int cur_y = tmp.y;
        string cur_st = tmp.path;
        int st_size = cur_st.size();
        char last_c = '\0';

        if (st_size != 0) {
          last_c = cur_st[st_size - 1];
          //cout << "last_c : " << last_c << endl;
        }
        if (st_size >= 10) {
          break_check = true;
          break;
        }
        if (last_c == dir[i]) {
          break_check = true;
          break;
        }
        if (last_c == 'R' && i == 1) {
          break_check = true;
          break;
        }
        if (last_c == 'L' && i == 0) {
          break_check = true;
          break;
        }
        if (last_c == 'U' && i == 2) {
          break_check = true;
          break;
        }
        if (last_c == 'D' && i == 3) {
          break_check = true;
          break;
        }
        
        bool goal = false;
        while (1) {
          if (A[cur_x + dx[i]][cur_y + dy[i]] == '#') {
            break;
          }
          else if (A[cur_x + dx[i]][cur_y + dy[i]] == 'O') {
            goal = true;
            break;
          }
          else if (A[cur_x + dx[i]][cur_y + dy[i]] == '.') {
            cur_x += dx[i];
            cur_y += dy[i];
          }
        } // while(1)
        

        if (goal == false) { // 도착한 점이 아니라면 set에 insert
          move_set.insert(XY(cur_x, cur_y, cur_st + dir[i]));

        }
        

      } //for iter
      /*set<XY>::iterator iter2;
      for (iter2 = move_set.begin(); iter2 != move_set.end(); iter2++) {
        XY t = *iter2;
        cout << t.x << " " << t.y << " " << t.path << endl;
      }*/
      if (move_set.size() == 0 && break_check == false) {
        // 경로 넣기 (더이상 넣을 것이 없기때문 다 넣음)
        auto a = q_v.begin();
        XY b = *a;
        ans = b.path + dir[i];
        return ans;
      }
      if (move_set.size() != 0) {
        q.push(move_set); // 한 방향에 대해 모든 요소를 처리하면 푸시
      }
    } // for i 0~4

  } // q empty()
  return "XHAE";
}
int main() {
  int T;
  cin >> T;
  while (T--) {
    int N, M;
    set<XY> v;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        cin >> A[i][j];
        if (A[i][j] == '.') {
          v.insert(XY(i, j, ""));
        }
      }
    }    

    cout << bfs(v) << endl;

  } // while T

}