#include "tests.hpp"

int main(void){
    //insert perf
    ft::stack<std::string> ft_stack;
    int i = 0;
    while (i < 10000){
        ft_stack.push("AAAAA");
        i++;
    }
    return (0);
}