#include "tests.hpp"

int main(void){
    //insert perf
    ft::vector<std::string> ft_vector;
    int i = 0;
    while (i < 10000){
        ft_vector.insert(ft_vector.begin() + 1, "AAAAA");
        i++;
    }
    return (0);
}