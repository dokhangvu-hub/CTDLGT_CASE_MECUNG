#include <iostream>
#include <vector>
#include <chrono>   // Thư viện đo thời gian
#include <iomanip>  // Thư viện căn chỉnh in ấn

using namespace std;
using namespace std::chrono;

// --- CẤU TRÚC DỮ LIỆU CƠ BẢN ---
struct Point {
    int x, y;
};

// --- CLASS CHÍNH (Bạn thiết kế cái này) ---
class MazeSolver {
public:
    int n, m; // Số hàng, số cột
    vector<vector<int>> map; // Ma trận mê cung: 0 là đường, 1 là tường
    vector<Point> path; // Lưu đường đi tìm được (để in ra kết quả)
    Point startPos, endPos;

    // Constructor: Khởi tạo
    MazeSolver(int rows, int cols) {
        n = rows;
        m = cols;
        // Mặc định khởi tạo toàn bộ là tường (1)
        map.resize(n, vector<int>(m, 1));
        startPos = {0, 0};
        endPos = {n - 1, m - 1};
    }

    void printMap() {
        // Chỉ in nếu map nhỏ, map to quá in ra sẽ bị vỡ giao diện console
        if (n > 50 || m > 50) {
            cout << "[Canh bao] Me cung qua lon (" << n << "x" << m << ") - Khong hien thi Console!" << endl;
            return;
        }

        cout << "--- MAP PREVIEW ---" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == startPos.x && j == startPos.y) cout << "S "; // Start
                else if (i == endPos.x && j == endPos.y) cout << "E "; // End
                else if (map[i][j] == 1) cout << "# "; // Tường
                else cout << ". "; // Đường
            }
            cout << endl;
        }
    }
};

// --- HÀM MAIN (Trình điều khiển - Controller) ---
int main() {
    int choice;
    MazeSolver* game = nullptr; // Dùng con trỏ để dễ quản lý vòng đời game

    while (true) {
        cout << "\n==============================\n";
        cout << "   DO AN: MAZE SOLVER SYSTEM  \n";
        cout << "==============================\n";
        cout << "1. Khoi tao va Sinh me cung\n";
        cout << "2. Giai me cung (DFS)\n";
        cout << "3. Giai me cung (BFS)\n";
        cout << "4. Hien thi me cung\n";
        cout << "0. Thoat\n";
        cout << "Lua chon: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1: {
            int h, w;
            cout << "Nhap so hang (Height): "; cin >> h;
            cout << "Nhap so cot (Width): "; cin >> w;
            
            // Xóa game cũ nếu có để tránh Memory Leak
            if (game != nullptr) delete game; 
            
            game = new MazeSolver(h, w);
            
            // Đo thời gian sinh mê cung (Optional)
            game->generateMaze(); // Gọi code của TV2
            cout << "Sinh me cung thanh cong!\n";
            break;
        }
        case 2:
        case 3: {
            if (game == nullptr) {
                cout << ">> Vui long tao me cung truoc (Chon 1)!\n";
                break;
            }
            
            // --- ĐO THỜI GIAN CHẠY (QUAN TRỌNG ĐỂ LÀM BÁO CÁO) ---
            auto start = high_resolution_clock::now();
            
            bool found = false;
            if (choice == 2) found = game->solveDFS(); // Gọi code TV3
            else found = game->solveBFS();             // Gọi code TV3

            auto stop = high_resolution_clock::now();
            // Tính ra vi giây (microseconds) để chính xác hơn
            auto duration = duration_cast<microseconds>(stop - start);

            if (found) cout << ">> Ket qua: TIM THAY DUONG DI!\n";
            else cout << ">> Ket qua: KHONG THAY DUONG DI!\n";
            
            cout << ">> Thoi gian thuc thi: " << duration.count() << " microseconds.\n";
            break;
        }
        case 4:
            if (game) game->printMap();
            else cout << "Chua co du lieu!\n";
            break;
        default:
            cout << "Lua chon khong hop le.\n";
        }
    }
    
    if (game) delete game; // Dọn dẹp bộ nhớ trước khi thoát
    return 0;
}