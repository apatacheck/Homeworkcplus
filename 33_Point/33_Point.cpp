#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

struct Point {
    int x;
    int y;
};

long long dist_sq(const Point& p) {
    return 1LL * p.x * p.x + 1LL * p.y * p.y;
}

void print_points(const std::vector<Point>& pts) {
    for (const auto& p : pts) {
        std::cout << "(" << p.x << "; " << p.y << ") ";
    }
    std::cout << "\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::vector<Point> points = {
        {2, 2}, {3, -4}, {-1, 1}, {0, 0}, {5, -1}, {-2, -2}, {2, 5}, {1, -1}
    };

    std::cout << "Исходные точки:\n";
    print_points(points);
    auto new_end = std::remove_if(points.begin(), points.end(), [](const Point& p) {
        return p.x > 0 && p.y < 0;
    });
    points.erase(new_end, points.end());

    std::cout << "\nа) После удаления точек из IV четверти:\n";
    print_points(points);

    auto on_line_count = std::count_if(points.begin(), points.end(), [](const Point& p) {
        return p.x == p.y;
    });

    std::cout << "\nб) Количество точек на прямой y = x: " << on_line_count << "\n";

    std::vector<Point> closest_points;
    if (!points.empty()) {
        auto min_it = std::min_element(points.begin(), points.end(), [](const Point& a, const Point& b) {
            return dist_sq(a) < dist_sq(b);
        });
        long long min_d = dist_sq(*min_it);

        std::copy_if(points.begin(), points.end(), std::back_inserter(closest_points), [min_d](const Point& p) {
            return dist_sq(p) == min_d;
        });
    }

    std::cout << "\nв) Наименее удалённые от (0, 0) точки:\n";
    print_points(closest_points);

    std::stable_sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.x > b.x;
    });

    std::cout << "\nг) После сортировки по убыванию x:\n";
    print_points(points);

    return 0;
}