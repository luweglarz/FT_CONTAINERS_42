#include "tests.hpp"

int main(void){
    //insert perf
    std::map<int, std::string> std_map;
    int i = 0;
    while (i < 10000){
        std::pair<int, std::string> thepair = std::make_pair(i, "AAAAA");
        std_map.insert(thepair);
        i++;
    }
    return (0);
}