#include <iostream>
#include <vector>
#include <algorithm>



int main() {

    int n, k, remaining;
    int smallest_difference = INT32_MAX;
    std::cin >> n >> k;
    remaining = n - k - 1;


    std::vector<int> planks(n);
    for (int  i = 0; i < n; ++i) {
        std::cin >> planks[i];
    }

    std::sort(planks.begin(), planks.end());


    for(int i = 0; i + remaining < n; ++i){
        if(planks[i+remaining] - planks[i] < smallest_difference)
            smallest_difference = planks[i+remaining] - planks[i];
    }
    std::cout << smallest_difference << std::endl;



    return 0;
}
