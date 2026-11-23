#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

struct Point {
    int x, y;
};

int dist_sq(Point p) {
    return p.x * p.x + p.y * p.y;
}

void print_points(const vector<Point>& pts) {
    for (Point p : pts) {
        cout << "(" << p.x << "; " << p.y << ") ";
    }
    cout << "\n";
}

// а) Удалить все точки из IV четверти (x > 0 и y < 0)
void remove_fourth_quadrant(vector<Point>& pts) {
    auto new_end = remove_if(pts.begin(), pts.end(), [](Point p) {
        return p.x > 0 && p.y < 0;
    });
    pts.erase(new_end, pts.end());
}

// б) Подсчитать количество точек на прямой y = x
int count_on_diagonal(const vector<Point>& pts) {
    return count_if(pts.begin(), pts.end(), [](Point p) {
        return p.x == p.y;
    });
}

// в) Найти все наименее удалённые от (0, 0) точки
vector<Point> find_closest_points(const vector<Point>& pts) {
    vector<Point> res;
    if (pts.empty()) return res;

    auto min_it = min_element(pts.begin(), pts.end(), [](Point a, Point b) {
        return dist_sq(a) < dist_sq(b);
    });
    int min_d = dist_sq(*min_it);

    for (Point p : pts) {
        if (dist_sq(p) == min_d) {
            res.push_back(p);
        }
    }
    return res;
}

// г) Расположить в порядке убывания x, не меняя порядок точек с одинаковым x
void sort_by_x_desc(vector<Point>& pts) {
    stable_sort(pts.begin(), pts.end(), [](Point a, Point b) {
        return a.x > b.x;
    });
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    vector<Point> points = {
        {2, 2}, {3, -4}, {-1, 1}, {0, 0}, {5, -1}, {-2, -2}, {2, 5}, {1, -1}
    };

    cout << "Исходные точки:\n";
    print_points(points);

    // а)
    remove_fourth_quadrant(points);
    cout << "\nа) После удаления точек из IV четверти:\n";
    print_points(points);

    // б)
    int cnt = count_on_diagonal(points);
    cout << "\nб) Количество точек на прямой y = x: " << cnt << "\n";

    // в)
    vector<Point> closest = find_closest_points(points);
    cout << "\nв) Наименее удалённые от (0, 0) точки:\n";
    print_points(closest);

    // г)
    sort_by_x_desc(points);
    cout << "\nг) После сортировки по убыванию x:\n";
    print_points(points);

    return 0;
}