#include <iostream>

int main() {
    unsigned long n = 0;
    unsigned long m = 0;
    int c2 = 0;
    int c5 = 0;
    std::cin >> n >> m >> c2 >> c5;

    if(n >= m || n == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }

    unsigned long  res = 0;
    unsigned long need = m - n;
    unsigned long how_many_for_5 = need / 4;
    if((how_many_for_5 * c5) < (how_many_for_5 * 4 * c2)) {
        res += how_many_for_5 * c5;
        need -= how_many_for_5 * 4;
        if(need) {
            res += (c5 < (need * c2))? c5 : need * c2;
        }
    }
    else{
        res += (c5 < (need * c2))? c5 : need * c2;
    }

    std::cout << res << std::endl;

    return 0;
}
