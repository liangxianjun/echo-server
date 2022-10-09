#include <iostream>
#include <string>
#include <mutex>

class logger {
    public:
        logger();  
        ~logger();
        void log(int level, const std::string& what, const std::string& happen);
    private:
        std::mutex m;
        time_t now;
};

logger::logger() {
    now = std::time(nullptr);
}

logger::~logger() {
    std::clog<<"awsl\n";
}

void logger::log(int level, const std::string& what, const std::string& happen) {
    std::string log_level;
    switch (level)
    {
    case 0:
        log_level = "\e[0;32m[DEBUG]";
        break;
    case 1:
        log_level = "\e[0;31m[ERROR]";
        break;
    default:
        log_level = "";
        break;
    }
    m.lock();
    now = std::time(nullptr);
    std::clog<<log_level<<"\t"<<std::put_time(std::localtime(&now), "%F %T")<<"\t"<<what<<"\t"<<happen<<"\e[0m"<<std::endl;
    m.unlock();
}