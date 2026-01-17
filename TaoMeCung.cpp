#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int H = 15;
const int W = 31;

char maze[H][W];

// 4 hướng: phải, trái, xuống, lên
int dx[4] = {0, 0, 2, -2};
int dy[4] = {2, -2, 0, 0};

// Kiểm tra ô hợp lệ
bool valid(int x, int y) {
    return x > 0 && x < H - 1 &&
           y > 0 && y < W - 1 &&
           maze[x][y] == '#';
}

// Sinh mê cung DFS Backtracking
void generateMaze(int x, int y) {
    maze[x][y] = ' ';

    int dir[4] = {0, 1, 2, 3};
    random_shuffle(dir, dir + 4);

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[dir[i]];
        int ny = y + dy[dir[i]];

        if (valid(nx, ny)) {
            // Phá tường ở giữa
            maze[x + dx[dir[i]] / 2][y + dy[dir[i]] / 2] = ' ';
            generateMaze(nx, ny);
        }
    }
}

int main() {
    srand(time(NULL));

    // Khởi tạo mê cung toàn tường
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            maze[i][j] = '#';

    // Sinh mê cung từ (1,1)
    generateMaze(1, 1);

    // Thêm lối vào & lối thoát 
    maze[1][0] = ' ';           // Lối vào (bên trái)
    maze[1][1] = ' ';

    maze[H - 2][W - 1] = ' ';   // Lối thoát (bên phải)
    maze[H - 2][W - 2] = ' ';
    // ==================================

    // In mê cung
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++)
            cout << maze[i][j];
        cout << endl;
    }

    return 0;
}

