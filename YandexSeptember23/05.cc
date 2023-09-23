#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <unordered_map>

struct Student {
    int rating;
    std::unordered_map<int, int> wishlist{{-1, INT_FAST32_MAX}};
    int program = -1;
};
struct Program{
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> abiturients;
    int capacity;
    int not_done = 1;
    int operator+(Program& rhs){
        return not_done + rhs.not_done;
    }
    friend int operator+(int lhs, Program&rhs){
        return lhs + rhs.not_done;
    }
};

int main() {

    int programs_count = 0;
    int students_count = 0;

    std::cin >> students_count >> programs_count;

    std::vector<Student> students(students_count);
    std::vector<Program> programs(programs_count);

    for(int i = 0; i < programs_count; ++i) {
        std::cin >> programs[i].capacity;
    }
    int wishcount, wish;
    for(int i = 0; i < students_count; ++i) {

        std::cin >> students[i].rating >> wishcount;

        for(int j = 0; j < wishcount; ++j) {
            std::cin >> wish;
            students[i].wishlist[wish - 1] = j + 1;
            programs[wish - 1].abiturients.push(std::make_pair(students[i].rating, i));
        }
    }
    int not_over = programs.size();
    while(not_over) {

        for(int i = 0; i < programs.size(); ++i) {
            while(programs[i].capacity && !programs[i].abiturients.empty()) {
                Student & current = students[programs[i].abiturients.top().second];
                if(current.wishlist[i] && current.wishlist[i] < current.wishlist[current.program]) {
                    if(current.program != -1) {
                        ++programs[current.program].capacity;
                        programs[current.program].not_done = 1;
                    }
                    current.program = i;
                    --programs[i].capacity;
                }
                programs[i].abiturients.pop();
            }
            programs[i].not_done = 0;
        }

        not_over = std::accumulate(programs.begin(), programs.end(), 0);

    }


    for(const auto &val : students) {
        std::cout << (val.program != -1 ? val.program + 1  : -1) << " ";
    }
    std::cout << std::endl;
    return 0;
}
