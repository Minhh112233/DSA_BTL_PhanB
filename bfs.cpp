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
class BFS {
private:
    int n, m, x1, y1, x2, y2;

    // Mảng lưu trữ các nước đi của quân mã
    int dx[8] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[8] = {1, -1, 1, -1, 2, -2, 2, -2};

public:
    BFS(int n, int m, int x1, int y1, int x2, int y2) 
        : n(n), m(m), x1(x1), y1(y1), x2(x2), y2(y2) {}

    // Hàm tìm số bước tối thiểu bằng BFS
    int find_min_steps() {
        // Cấp phát mảng 2 chiều thủ công cho visited
        bool **visited = new bool*[n];
        for (int i = 0; i < n; ++i) {
            visited[i] = new bool[m];
            for (int j = 0; j < m; ++j) {
                visited[i][j] = false;
            }
        }

        // Khởi tạo hàng đợi
        QUEUE<Position> q;

        // Thêm vị trí ban đầu vào hàng đợi
        q.push({x1, y1, 0});
        visited[x1][y1] = true;

        while (q.size() > 0) {
            Position current = q.front(); // Lấy vị trí hiện tại
            q.pop();

            // Kiểm tra nếu đã đến đích
            if (current.x == x2 && current.y == y2) {
                // Giải phóng bộ nhớ trước khi kết thúc chương trình
                for (int i = 0; i < n; ++i) {
                    delete[] visited[i];
                }
                delete[] visited;
                return current.steps; // Trả về số bước
            }

            // Duyệt qua các nước đi của quân mã
            for (int i = 0; i < 8; ++i) {
                int nx = current.x + dx[i];
                int ny = current.y + dy[i];

                // Kiểm tra tọa độ hợp lệ và chưa được thăm
                if (nx >= 0 && ny >= 0 && nx < n && ny < m && !visited[nx][ny]) {
                    visited[nx][ny] = true; // Đánh dấu đã thăm
                    q.push({nx, ny, current.steps + 1}); // Thêm vào hàng đợi
                }
            }
        }

        // Giải phóng bộ nhớ trước khi kết thúc chương trình
        for (int i = 0; i < n; ++i) {
            delete[] visited[i];
        }
        delete[] visited;

        return -1; // Không tìm thấy đường đến đích
    }
};

int main() {
    int n, m, x1, y1, x2, y2;
    cin >> n >> m >> x1 >> y1 >> x2 >> y2;

    // Tạo đối tượng BFS và tìm số bước
    BFS bfs(n, m, x1, y1, x2, y2);
    int result = bfs.find_min_steps();

    cout << result; // In ra số bước ít nhất
    return 0;
}
