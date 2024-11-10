#include <iostream>
using namespace std;

// Cấu trúc lưu trữ thông tin vị trí quân mã
struct Position {
    int x, y, steps; // x, y là tọa độ và steps là số bước
};

// Các nước đi của quân mã
int dx[8] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[8] = {1, -1, 1, -1, 2, -2, 2, -2};

// Lớp node cho hàng đợi (queue)
template <class T>
class node {
    T elem;
    node<T> *next;

public:
    node(T x, node<T> *N = nullptr) {
        elem = x;
        next = N;
    }
    T &getelem() {
        return elem;
    }
    void setnext(node *N) {
        next = N;
    }
    node<T> *getnext() {
        return next;
    }
};

// Lớp hàng đợi (queue)
template<class T>
class QUEUE {
    unsigned num;
    node<T> *F, *L;

public:
    QUEUE() {
        num = 0;
        F = L = nullptr;
    }

    unsigned size() { return num; }

    T &front() { return F->getelem(); }

    void push(T x) {
        if (num == 0) F = L = new node<T>(x);
        else {
            L->setnext(new node<T>(x));
            L = L->getnext();
        }
        num++;
    }

    void pop() {
        if (num == 0) return;
        F = F->getnext();
        num--;
    }
};

// Lớp BFS
// Lớp BFS
class BFS {
private:
    int n, m, x1, y1, x2, y2;
    int dx[8] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[8] = {1, -1, 1, -1, 2, -2, 2, -2};

public:
    // Khởi tạo đối tượng BFS với các tham số
    BFS(int n, int m, int x1, int y1, int x2, int y2);

    // Khởi tạo mảng visited
    bool** taoMangDaTham();

    // Giải phóng mảng visited
    void giaiPhongMang(bool** daTham);

    // Xử lý các nước đi của quân mã
    void xuLyNuocDi(QUEUE<Position>& q, bool** daTham, Position& hienTai);

    // Tìm số bước tối thiểu để quân mã di chuyển từ điểm bắt đầu đến điểm đích
    int timBuocDiItNhat();
};

// Định nghĩa các phương thức bên ngoài lớp

BFS::BFS(int n, int m, int x1, int y1, int x2, int y2) 
    : n(n), m(m), x1(x1), y1(y1), x2(x2), y2(y2) {}

bool** BFS::taoMangDaTham() {
    bool **daTham = new bool*[n];
    for (int i = 0; i < n; ++i) {
        daTham[i] = new bool[m]{false};
    }
    return daTham;
}

void BFS::giaiPhongMang(bool** daTham) {
    for (int i = 0; i < n; ++i) {
        delete[] daTham[i];
    }
    delete[] daTham;
}

void BFS::xuLyNuocDi(QUEUE<Position>& q, bool** daTham, Position& hienTai) {
    for (int i = 0; i < 8; ++i) {
        int nx = hienTai.x + dx[i];
        int ny = hienTai.y + dy[i];
        if (nx >= 0 && ny >= 0 && nx < n && ny < m && !daTham[nx][ny]) {
            daTham[nx][ny] = true;
            q.push({nx, ny, hienTai.steps + 1});
        }
    }
}

int BFS::timBuocDiItNhat() {
    bool **daTham = taoMangDaTham();
    QUEUE<Position> q;
    q.push({x1, y1, 0});
    daTham[x1][y1] = true;

    while (q.size() > 0) {
        Position hienTai = q.front();
        q.pop();
        if (hienTai.x == x2 && hienTai.y == y2) {
            giaiPhongMang(daTham);
            return hienTai.steps;
        }
        xuLyNuocDi(q, daTham, hienTai);
    }

    giaiPhongMang(daTham);
    return -1;
}

int main() {
    int n, m, x1, y1, x2, y2;
    cin >> n >> m >> x1 >> y1 >> x2 >> y2;

    // Tạo đối tượng BFS và tìm số bước
    BFS bfs(n, m, x1, y1, x2, y2);
    int result = bfs.timBuocDiItNhat();

    cout << result; // In ra số bước ít nhất
    return 0;
}
