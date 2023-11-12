#include <iostream>
#include <vector>
#include "DingingPhilosophers.h"

int main() {
    std::vector<s21::Philosopher *> abobas(30);
    std::vector<s21::Fork *> forks(abobas.size());

    for(size_t i = 0; i < forks.size(); ++i){
        forks[i] = new s21::Fork(i);
    }

    for (size_t i = 0; i < abobas.size(); i++) {
        abobas[i] = new s21::Philosopher(5, 5, 11, 26, *forks[i], *forks[i == abobas.size() - 1 ? 0 : i + 1]);
    }

    for(auto & aboba : abobas){
        aboba->Start();
    }
    for(auto & aboba : abobas){
        aboba->Join();
    }

    for(auto & aboba : abobas){
        std::cout << "aboba is ";
        if(aboba->dead_){
            std::cout << "dead ";
        }else{
            std::cout << "alive ";
        }
        std::cout << std::endl << "aboba ate " << aboba->ate_ <<" times and survived for "
        << aboba->run_time_.count() << " milliseconds" << std::endl;
    }
    for(auto & aboba : abobas){
        delete aboba;
    }
    for(auto & fork : forks){
        delete fork;
    }


}
