#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

struct segment{
    int gcd_;
    int ants_;
};

const int maxn = 1e5 + 5;
int n, ants[maxn], t;
segment segTree[4 * maxn];

int gcd(int n, int m) {
    if (n < m)
        return gcd(m, n);
    if (m == 0)
        return n;
    return gcd(m, n % m);
}

int mid(int l, int r) {
    return l + (r - l) / 2;
}

segment merge(segment left, segment right) {
    segment seg;
    seg.gcd_ = gcd(left.gcd_, right.gcd_);
    seg.ants_ = (seg.gcd_ == left.gcd_) * left.ants_ + (seg.gcd_ == right.gcd_) * right.ants_;
    return seg;
}

void build(int seg = 1, int left = 0, int right = n - 1) {
    if (left == right){
        segment s;
        s.gcd_ = ants[left];
        s.ants_ = 1;
        segTree[seg] = s;
    }
    else {
        int m = mid(left, right);
        build(seg * 2, left, m);
        build(seg * 2 + 1, m + 1, right);
        segTree[seg] = merge(segTree[seg*2], segTree[seg*2 + 1]);
    }
}

segment query(int i, int j, int seg = 1, int left = 0, int right = n - 1) {
    if (j < left || i > right) {
        segment s;
        s.gcd_ = 0;
        s.ants_ = 0;
        return s;
    }
    if (i <= left && j >= right) {
        return segTree[seg];
    }
    else {
        return merge(query(i, j, seg * 2, left, mid(left, right)), 
                     query(i, j, seg * 2 + 1, mid(left, right) + 1, right));
    }
}

void print() {
    for (int i = 0; i < 15; i++) {
        cout << i << ": "<<segTree[i].gcd_ << " " << segTree[i].ants_ << endl;
    }
}


int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ants[i];
    }
    build();
    cin >> t;
    int start, end;
    for (int i = 0; i < t; i++) {
        cin >> start;
        cin >> end;
        start--;
        end--;
        cout << (end - start + 1) - query(start, end).ants_ << endl;
    }
}