#include <iostream>
#include <vector>

using namespace std;

const long long INF = 2000000000000000000LL;

struct Edge {
    int u, v;
    long long w; // cạnh từ u đến v, trọng số w
};

void bellmanFord(int n, int S, vector<Edge>& e, vector<long long>& D, vector<int>& trace) {
    // e: danh sách cạnh
    // n: số đỉnh
    // S: đỉnh bắt đầu
    // D: độ dài đường đi ngắn nhất
    // trace: mảng truy vết đường đi
    // INF nếu không có đường đi
    // -INF nếu có đường đi âm vô tận
    D.resize(n, INF);
    trace.resize(n, -1);

    D[S] = 0;
    for (int T = 1; T < n; T++) {
        for (auto E : e) {
            int u = E.u;
            int v = E.v;
            long long w = E.w;
            if (D[u] != INF && D[v] > D[u] + w) {
                D[v] = D[u] + w;
                trace[v] = u;
            }
        }
    }
    //kiem tra do thi co trong so am khong
    for (int T = 0; T < n; T++) {
        for (auto E : e) {
            int u = E.u;
            int v = E.v;
            long long w = E.w;
            if (D[u] != INF && D[v] > D[u] + w) {
                // vẫn còn tối ưu được --> âm vô cực
                D[v] = -INF;
                trace[v] = u;
            }
        }
    }
}

//TÌM LẠI ĐƯỜNG ĐI NGẮN NHẤT
vector<int> trace_path(vector<int>& trace, int S, int u) {
    if (u != S && trace[u] == -1) return vector<int>(0); // không có đường đi

    vector<int> path;
    while (u != -1) { // truy vết ngược từ u về S
        path.push_back(u);
        u = trace[u];
    }
    reverse(path.begin(), path.end()); // cần reverse vì đường đi lúc này là từ u về S

    return path;
}

//CÁC TRƯỜNG HỢP CÓ CHU TRÌNH ÂM

//// sau khi chạy xong N-1 vòng lặp Bellman-Ford 


//TÌM CHU TRÌNH ÂM

bool findNegativeCycle(int n, vector<long long> &D, vector<int> &trace, vector<int> &negCycle) {
    // mảng D và trace đã được chạy qua thuật toán Bellman-Ford
    int negStart = -1; // đỉnh bắt đầu
    for (auto E : e) {
        int u = E.u;
        int v = E.v;
        long long w = E.w;
        if (D[u] != INF && D[v] > D[u] + w) {
            D[v] = -INF;
            trace[v] = u;
            negStart = v; // đã tìm thấy -INF
        }
    }

    if (negStart == -1) return false; // không có chu trình âm

    int u = negStart;
    for (int i = 0; i < n; i++) {
        u = trace[u]; // đưa u về chu trình âm
    }

    negCycle = vector<int>(1, u);
    for (int v = trace[u]; v != u; v = trace[u]) {
        negCycle.push_back(v); // truy vết một vòng
    }
    reverse(negCycle.begin(), negCycle.end());

    return true;
}

int main() {

    

    return 0;
}

