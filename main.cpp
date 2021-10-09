
#include "vector.hpp"
#include "Iterator.hpp"
#include "pair.hpp"
#include "map.hpp"
#include "stack.hpp"

#include <iostream>
#include <vector>
#include <stack>

#include <map>

// namespace ft = std;

int main() {
 


    std::map<int, long>    smap;
    ft::map<int, long>     fmap;

    for (std::map<int, long>::iterator i = smap.begin(); i != smap.end(); ++i)
        i->second = 0;


    for (ft::map<int, long>::iterator i = fmap.begin(); i != fmap.end(); ++i)
        i->second = 0;

    std::map<int, long>::iterator  s_it = smap.begin();
    // s_it++; ++s_it; s_it--; --s_it;  // infinite
    std::cout << "std: ";
    if (s_it != smap.begin())
        std::cout <<  "KO" << ' ' << std::endl;
    else
        std::cout <<  "OK" << ' ' << std::endl;

    ft::map<int, long>::iterator  f_it = fmap.begin();
    --f_it;
    std::cout << "ft:  ";
    std::cout << std::addressof(f_it) << '\n';
    if (f_it != fmap.begin())
        std::cout << "KO" << ' ' << std::endl;
    else
        std::cout << "OK" << ' ' << std::endl;


return 0;
}