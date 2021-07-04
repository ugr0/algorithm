#include <bits/stdc++.h>
using namespace std;

struct Point {
  double px, py;
};

Point operator-(const Point& a1, const Point& a2) {
  return Point{a1.px - a2.px, a1.py - a2.py};
}

double getAngle(Point G) {
  double I = G.px / sqrt(G.px * G.px + G.py * G.py);
  double angle = acos(I) * 180.0 / M_PI;
  if (G.py >= 0.0) {
    return angle;
  } else {
    return 360.0 - angle;
  }
}

double getAngle2(double I1, double I2) {
  double res = abs(I1 - I2);
  if (res >= 180.0) return 360.0 - res;
  return res;
}

int N;
Point G[2009];

double solve(int pos) {
  // 偏角の昇順にソート
  vector<double> vec;
  for (int i = 0; i < N; i++) {
    if (i == pos) continue;
    Point SA = G[i] - G[pos];
    double angle = getAngle(SA);
    vec.push_back(angle);
  }
  sort(vec.begin(), vec.end());

  double ret = 0.0;
  for (int i = 0; i < vec.size(); i++) {
    double target = vec[i] + 180.0;
    if (target >= 360.0) target -= 360.0;
    int pos1 = lower_bound(vec.begin(), vec.end(), target) - vec.begin();

    int CandIdx1 = pos1 % vec.size();
    int CandIdx2 = (pos1 + vec.size() - 1) % vec.size();
    double Candidate1 = getAngle2(vec[i], vec[CandIdx1]);
    double Candidate2 = getAngle2(vec[i], vec[CandIdx2]);
    ret = max({ret, Candidate1, Candidate2});
  }

  return ret;
}