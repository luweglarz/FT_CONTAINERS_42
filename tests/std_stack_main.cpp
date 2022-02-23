#include "tests.hpp"

int main(void){
    //insert perf
    std::stack<std::string> std_stack;
    int i = 0;
    while (i < 10000){
        std_stack.push("AAAAA");
        i++;
    }
    return (0);
}