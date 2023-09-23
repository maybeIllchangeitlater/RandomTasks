#include <iostream>
#include <vector>
#include <set>
#include <queue>

int main() {
    int total = 0;
    int breaks = 0;
    int repairs = 0;

    std::cin >> total >> breaks >> repairs;

    std::vector<std::set<int>> plan(total);

    for (int i = 0; i < breaks; ++i){
        int day = 0;
        int sidewalk = 0;
        std::cin >> day >> sidewalk;
        plan[sidewalk - 1].emplace(day);
    }


    std::priority_queue<int> prefix;

    for(auto &street : plan) {
        if(!street.empty()){
            auto j = ++street.begin();
            for(; j != street.end(); ++(++j)){
                prefix.push((*j - *(--j)));
            }
        --repairs;
        }
    }

    if(repairs < 0) {
        std::cout << -1 << std::endl;
        return 0;
    }

    int sadness = 0;

    while(repairs-- && !prefix.empty()){
        prefix.pop();
    }

    while(!prefix.empty()) {
        sadness += prefix.top();
        prefix.pop();
    }

    std::cout << sadness << std::endl;

    return 0;
}
