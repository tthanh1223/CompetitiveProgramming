#include <iostream>
#include <vector>
#include <string>
#include <limits>

// This is a iostream library
int main()
{
    int* p_number {nullptr}; //Will init with nullptr
    double* p_fractional_number {};
    int data {56};
    p_number = &data;
    std::cout << *p_number << std::endl;
    return 0;
}
/*
    std::cout : print data to terminal
    std::cin : reading data from the terminal
    std::cerr : printing errors to the console
    std::clog : printing log messages to the console
    std::boolalpha : make bool show up as a true/false instread of 1/0
    std::numeric_limits<T>::min()
    std::numeric_limits<T>::max()
    std::numeric_limits<T>::lowest()
*/
