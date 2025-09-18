#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <cstdlib>
#include <thread>

void init(){
      setvbuf(stdin, (char *)NULL, _IONBF, 0);
      setvbuf(stdout, (char *)NULL, _IONBF, 0);
      setvbuf(stderr, (char *)NULL, _IONBF, 0);
}

void get_flag() {
    std::string flag;
    const char* env_flag = std::getenv("FLAG");
    if (env_flag != nullptr) {
        flag = env_flag;
        if (flag.length() > 29) {
            flag = flag.substr(0, 29);
        }
    }
    
    std::cout << "flag = " << flag << std::endl;
}

void timer_thread() {
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "\nTime Out!\n";
    std::exit(1);
}

int main() {
    init();
    
    std::thread timer(timer_thread);
    timer.detach();
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(0, 9999);
    
    std::cout << "100calculate 10seconds\n";
    std::cout << "? is POSITIVE INTEGER\n";
    std::cout << "Data Type is unsigned int\n";
    
    for (int i = 0; i < 100; i++) {
        unsigned int ran1 = dis(gen);
        unsigned int ran2 = dis(gen);
        
        if (ran1 < ran2) {
            std::swap(ran1, ran2);
        }
        
        std::cout << ran1 << " + ? = " << ran2 << '\n';
        std::cout << "? = ";
        
        long int input;
        std::cin >> input;
        
        if (input < 0) {
            std::cout << "ONLY POSITIVE\n";
            return 1;
        }
        
        ran1 += input;
        if (ran1 != ran2) {
            std::cout << "fail\n";
            std::cout << ran1 << ", " << ran2 << '\n';
            return 1;
        }
        
        std::cout << "success (" << i + 1 << "/100)\n";
    }
    
    get_flag();
    return 0;
}


