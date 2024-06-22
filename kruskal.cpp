#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define MAX 1000
using namespace std;

// C?u trúc bi?u di?n m?t c?nh v?i 3 thu?c tính: ð?nh b?t ð?u, ð?nh k?t thúc, và tr?ng s?
struct Edge {
    int u;
    int v;
    int w;
    bool operator<(const Edge& other) const {
        return w < other.w; // So sánh tr?ng s? c?a các c?nh ð? s?p x?p
    }
};

// Khai báo các bi?n toàn c?c
int n, m; // S? ð?nh và s? c?nh
vector<Edge> edges; // Danh sách các c?nh
int parent[MAX]; // M?ng lýu cha c?a m?i ð?nh trong cây
int sz[MAX]; // M?ng lýu kích thý?c c?a m?i t?p h?p

// Hàm kh?i t?o các t?p h?p r?i r?c ban ð?u
void makeset() {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
}

// Hàm t?m t?p h?p ð?i di?n c?a ð?nh v
int findset(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = findset(parent[v]); // T?i ýu b?ng cách nén ðý?ng ði
}

// Hàm h?p nh?t hai t?p h?p ch?a a và b
bool unionset(int a, int b) {
    a = findset(a);
    b = findset(b);
    if (a == b) return false; // N?u cùng m?t t?p h?p th? không h?p nh?t
    if (sz[a] < sz[b])
        swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
}

// Hàm th?c hi?n thu?t toán Kruskal ð? t?m cây khung c?c ti?u
void kruskal() {
    vector<Edge> mst; // Danh sách các c?nh c?a cây khung c?c ti?u
    int d = 0; // T?ng tr?ng s? c?a cây khung c?c ti?u
    sort(edges.begin(), edges.end()); // S?p x?p các c?nh theo tr?ng s?
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
        cout << "Do thi khong lien thong !\n"; // Ð? th? không liên thông
    }
    else {
        cout << "MST: " << d << endl;
        for (auto it : mst) {
            cout << it.u << " " << it.v << " " << it.w << endl;
        }
    }
}

// Hàm th?c hi?n thu?t toán Kruskal nhýng luôn ch?a c?nh (x, y)
void kruskal_with_edge(int x, int y) {
    vector<Edge> mst; // Danh sách các c?nh c?a cây khung c?c ti?u
    int d = 0; // T?ng tr?ng s? c?a cây khung c?c ti?u
    sort(edges.begin(), edges.end()); // S?p x?p các c?nh theo tr?ng s?

    // T?m và lýu tr?ng s? c?a c?nh (x, y)
    int weight_xy = -1;
    for (const auto& edge : edges) {
        if ((edge.u == x && edge.v == y) || (edge.u == y && edge.v == x)) {
            weight_xy = edge.w;
            break;
        }
    }

    // Thêm c?nh (x, y) vào cây khung
    if (unionset(x, y)) {
        mst.push_back({ x, y, weight_xy });
        d += weight_xy;
    }

    // Ti?p t?c thu?t toán Kruskal
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
        cout << "Do thi khong lien thong !\n"; // Ð? th? không liên thông
    }
    else {
        cout << "MST voi canh (" << x << ", " << y << "): " << d << endl;
        for (auto it : mst) {
            cout << it.u << " " << it.v << " " << it.w << endl;
        }
    }
}

// Hàm ð?c d? li?u ð? th? t? file
void input() {
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Khong mo duoc file!" << endl;
        exit(1);
    }
    infile >> n >> m; // Ð?c s? ð?nh và s? c?nh
    edges.resize(m); // Ði?u ch?nh kích thý?c danh sách c?nh
    for (int i = 0; i < m; ++i) {
        infile >> edges[i].u >> edges[i].v >> edges[i].w; // Ð?c t?ng c?nh
    }
    infile.close();
}

int main() {
    input(); // Ð?c d? li?u ð?u vào
    makeset(); // Kh?i t?o các t?p h?p
    kruskal(); // T?m cây khung c?c ti?u thông thý?ng

    int x, y;
    cout << "Nhap canh (x, y) phai co trong cay khung cuc tieu: ";
    cin >> x >> y; // Ð?c c?nh (x, y) t? bàn phím

    makeset(); // Kh?i t?o l?i các t?p h?p
    kruskal_with_edge(x, y); // T?m cây khung c?c ti?u ch?a c?nh (x, y)

    return 0;
}
