#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define MAX 1000
using namespace std;

// C?u tr�c bi?u di?n m?t c?nh v?i 3 thu?c t�nh: �?nh b?t �?u, �?nh k?t th�c, v� tr?ng s?
struct Edge {
    int u;
    int v;
    int w;
    bool operator<(const Edge& other) const {
        return w < other.w; // So s�nh tr?ng s? c?a c�c c?nh �? s?p x?p
    }
};

// Khai b�o c�c bi?n to�n c?c
int n, m; // S? �?nh v� s? c?nh
vector<Edge> edges; // Danh s�ch c�c c?nh
int parent[MAX]; // M?ng l�u cha c?a m?i �?nh trong c�y
int sz[MAX]; // M?ng l�u k�ch th�?c c?a m?i t?p h?p

// H�m kh?i t?o c�c t?p h?p r?i r?c ban �?u
void makeset() {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
}

// H�m t?m t?p h?p �?i di?n c?a �?nh v
int findset(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = findset(parent[v]); // T?i �u b?ng c�ch n�n ��?ng �i
}

// H�m h?p nh?t hai t?p h?p ch?a a v� b
bool unionset(int a, int b) {
    a = findset(a);
    b = findset(b);
    if (a == b) return false; // N?u c�ng m?t t?p h?p th? kh�ng h?p nh?t
    if (sz[a] < sz[b])
        swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
}

// H�m th?c hi?n thu?t to�n Kruskal �? t?m c�y khung c?c ti?u
void kruskal() {
    vector<Edge> mst; // Danh s�ch c�c c?nh c?a c�y khung c?c ti?u
    int d = 0; // T?ng tr?ng s? c?a c�y khung c?c ti?u
    sort(edges.begin(), edges.end()); // S?p x?p c�c c?nh theo tr?ng s?
    for (int i = 0; i < m; i++) {
        if (mst.size() == n - 1)
            break;
        Edge e = edges[i];
        if (unionset(e.u, e.v)) {
            mst.push_back(e);
            d += e.w;
        }
    }
    if (mst.size() != n - 1) {
        cout << "Do thi khong lien thong !\n"; // �? th? kh�ng li�n th�ng
    }
    else {
        cout << "MST: " << d << endl;
        for (auto it : mst) {
            cout << it.u << " " << it.v << " " << it.w << endl;
        }
    }
}

// H�m th?c hi?n thu?t to�n Kruskal nh�ng lu�n ch?a c?nh (x, y)
void kruskal_with_edge(int x, int y) {
    vector<Edge> mst; // Danh s�ch c�c c?nh c?a c�y khung c?c ti?u
    int d = 0; // T?ng tr?ng s? c?a c�y khung c?c ti?u
    sort(edges.begin(), edges.end()); // S?p x?p c�c c?nh theo tr?ng s?

    // T?m v� l�u tr?ng s? c?a c?nh (x, y)
    int weight_xy = -1;
    for (const auto& edge : edges) {
        if ((edge.u == x && edge.v == y) || (edge.u == y && edge.v == x)) {
            weight_xy = edge.w;
            break;
        }
    }

    // Th�m c?nh (x, y) v�o c�y khung
    if (unionset(x, y)) {
        mst.push_back({ x, y, weight_xy });
        d += weight_xy;
    }

    // Ti?p t?c thu?t to�n Kruskal
    for (int i = 0; i < m; i++) {
        if (mst.size() == n - 1)
            break;
        Edge e = edges[i];
        if (unionset(e.u, e.v)) {
            mst.push_back(e);
            d += e.w;
        }
    }
    if (mst.size() != n - 1) {
        cout << "Do thi khong lien thong !\n"; // �? th? kh�ng li�n th�ng
    }
    else {
        cout << "MST voi canh (" << x << ", " << y << "): " << d << endl;
        for (auto it : mst) {
            cout << it.u << " " << it.v << " " << it.w << endl;
        }
    }
}

// H�m �?c d? li?u �? th? t? file
void input() {
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Khong mo duoc file!" << endl;
        exit(1);
    }
    infile >> n >> m; // �?c s? �?nh v� s? c?nh
    edges.resize(m); // �i?u ch?nh k�ch th�?c danh s�ch c?nh
    for (int i = 0; i < m; ++i) {
        infile >> edges[i].u >> edges[i].v >> edges[i].w; // �?c t?ng c?nh
    }
    infile.close();
}

int main() {
    input(); // �?c d? li?u �?u v�o
    makeset(); // Kh?i t?o c�c t?p h?p
    kruskal(); // T?m c�y khung c?c ti?u th�ng th�?ng

    int x, y;
    cout << "Nhap canh (x, y) phai co trong cay khung cuc tieu: ";
    cin >> x >> y; // �?c c?nh (x, y) t? b�n ph�m

    makeset(); // Kh?i t?o l?i c�c t?p h?p
    kruskal_with_edge(x, y); // T?m c�y khung c?c ti?u ch?a c?nh (x, y)

    return 0;
}
