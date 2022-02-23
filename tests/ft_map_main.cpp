#include "tests.hpp"

int main(void){
    //insert perf
    ft::map<int, std::string> ft_map;
    int i = 0;
    while (i < 10000){
        ft::pair<int, std::string> thepair = ft::make_pair(i, "AAAAA");
        ft_map.insert(thepair);
        i++;
    }
    return (0);
}