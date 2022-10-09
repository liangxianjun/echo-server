#include <iostream>
#include <string>
#include <mutex>

class logger {
    public:
        logger();  
        ~logger();
        void log(size_t level, const std::string& what, const std::string& happen);
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

void logger::log(size_t level, const std::string& what, const std::string& happen) {
    std::string log_level;
    switch (level)
    {
    case 0:
        log_level = "[DEBUG]";
        break;
    
    default:
        log_level = "";
        break;
    }
    m.lock();
    now = std::time(nullptr);
    // std::clog<<log_level<<"\t"<<std::put_time(std::localtime(&now), "%F %T%z")<<"\t"<<what<<"\t"<<happen<<std::endl;
    std::clog<<log_level<<"\t"<<std::put_time(std::localtime(&now), "%F %T")<<"\t"<<what<<"\t"<<happen<<std::endl;
    m.unlock();
}