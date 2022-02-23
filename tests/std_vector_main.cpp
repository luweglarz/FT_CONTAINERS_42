#include "tests.hpp"

int main(void){
    //insert perf
    std::vector<std::string> std_vector;
    int i = 0;
    while (i < 10000){
        std_vector.insert(std_vector.begin() + 1, "AAAAA");
        i++;
    }
    return (0);
}