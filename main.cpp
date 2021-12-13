#include "ClassVector.hpp"
#include <vector>
int main()
{
	std::vector<int>::iterator ibegin;
	std::vector<int>::iterator ilast;
	ft::Vector<int> test(ibegin, ilast);
	ft::Vector<int> test1(5, 10);
	return (0);
}
