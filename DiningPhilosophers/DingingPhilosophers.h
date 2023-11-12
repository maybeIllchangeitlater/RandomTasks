#ifndef UNTITLED_PHILOSOPHER_H
#define UNTITLED_PHILOSOPHER_H
#include <thread>
#include <chrono>
namespace s21{
    struct Fork{
        Fork(size_t id) : id_(id) {}
        size_t id_;
        std::mutex mtx_;
    };

    struct Philosopher {
    public:
        Philosopher(size_t eat_time, size_t sleepy, size_t must_eat_each, size_t run_for, Fork &left_fork, Fork &right_fork)
                : eat_time_(eat_time), sleepy_(sleepy), must_eat_each_(must_eat_each), ate_(0), run_for_(std::chrono::milliseconds(run_for * 1000)), l_(left_fork), r_(right_fork){

        }

        void EatAndSleep(){
            Feed();
            Sleep();
        }
        void Feed(){
            std::lock(l_.mtx_, r_.mtx_);//avoids deadlocks
            std::lock_guard<std::mutex> l_lock(l_.mtx_, std::adopt_lock);
            std::lock_guard<std::mutex> r_lock(r_.mtx_, std::adopt_lock);
            ++ate_;
            last_feed_ = std::chrono::high_resolution_clock::now();
            std::this_thread::sleep_for(std::chrono::milliseconds(eat_time_ * 1000));
        }

        void Sleep(){
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepy_ * 1000));
        }

        void Run(){
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            start_ = std::chrono::high_resolution_clock::now();
            last_feed_ = std::chrono::high_resolution_clock::now();

            while (!dead_ && (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_) < run_for_)){
                if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - last_feed_) > std::chrono::milliseconds(must_eat_each_ * 1000)){

                    dead_ = true;
                    break;

                }else{
                    EatAndSleep();
                }
            }
            run_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_);
        }

        void Start(){
            thread_ = std::thread(&Philosopher::Run, this);
        }

        void Join(){
            thread_.join();
        }

//    private:
        bool dead_ = false;
        size_t eat_time_;
        std::chrono::time_point<std::chrono::high_resolution_clock> start_;
        size_t sleepy_;
        size_t must_eat_each_;
        size_t ate_;
        std::chrono::time_point<std::chrono::high_resolution_clock> last_feed_;
        std::chrono::milliseconds run_time_;
        std::chrono::milliseconds run_for_;
        Fork& l_;
        Fork& r_;
        std::thread thread_;

    };
    } //s21
#endif //UNTITLED_PHILOSOPHER_H
