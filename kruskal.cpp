#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define MAX 1000
using namespace std;


struct Edge {
    int u;//dinh bat dau
    int v;//dinh ket thuc
    int w;//trong so
    bool operator<(const Edge& other) const {
        return w < other.w; 
    }
};  

//khai bao bien toan cuc
vector<Edge> edges; 
int n, m;
int parent[MAX]; 
int sz[MAX]; 

// ham gan nhan
void makeset() {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
}

//ham tim tap hop dai dien cua dinh v
int findset(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = findset(parent[v]); //de quy toi uu duong di
}

//ham ket hop cac tap hop chua a va b
bool unionset(int a, int b) {
    a = findset(a);
    b = findset(b);
    if (a == b) return false; //cung 1 tap hop thi khong ket hop
    if (sz[a] < sz[b])
        swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
}

// ham krusual
void kruskal() {
    vector<Edge> mst; //danh sach chua cac canh cua cay khung cuc tieu
    int d = 0; // tong trong so cua cay khung cuc tieu
    sort(edges.begin(), edges.end()); //sap xep trong so tang dan
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
        cout << "Do thi khong lien thong !\n"; 
    }
    else {
        cout << "MST: " << d << endl;
        for (auto it : mst) {
            cout << it.u << " " << it.v << " " << it.w << endl;
        }
    }
}

// ham krusal nhung chua  (x, y)
void kruskal_with_edge(int x, int y) {
    vector<Edge> mst; 
    int d = 0; 
    sort(edges.begin(), edges.end());

    // tim luu trong so (x,y);
    int weight_xy = -1;
    bool flag = false;
    for (const auto& edge : edges) {
        if ((edge.u == x && edge.v == y) || (edge.u == y && edge.v == x)) {
            weight_xy = edge.w;
            flag = true;
                break;// dung vong lap khi ko tim thay canh
        }
    }
    if (!flag) {
        cout << "Khong tim thay trong so canh giua " << x << " va " << y << endl;
        return ; // Thoát kh?i hàm n?u không t?m th?y c?nh
    }
    
    // Them (x,y) vao cay khung
    if (unionset(x, y)) {
        mst.push_back({ x, y, weight_xy });
        d += weight_xy;
    }

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
        cout << "Do thi khong lien thong !\n"; 
    }
    else {
        cout << "MST voi canh (" << x << ", " << y << "): " << d << endl;
        for (auto it : mst) {
            cout << it.u << " " << it.v << " " << it.w << endl;
        }
    }
}

//ham doc du lieu tu file
void input() {
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Khong mo duoc file!" << endl;
        exit(1);
    }
    infile >> n >> m; 
    edges.resize(m); 
    for (int i = 0; i < m; ++i) {
        infile >> edges[i].u >> edges[i].v >> edges[i].w; 
    }
    infile.close();
}

int main() {
    input(); 
    makeset(); 
    kruskal(); 

    int x, y;
    cout << "Nhap canh (x, y) phai co trong cay khung cuc tieu: ";
    cin >> x >> y; 

    makeset(); 
    kruskal_with_edge(x, y); 

    return 0;
}
