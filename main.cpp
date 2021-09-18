
#include "vector.hpp"
#include "Iterator.hpp"
#include <iostream>
#include <vector>
#include "stack.hpp"
#include <stack>
#include "pair.hpp"
#include "map.hpp"
#include <map>

int main() {


    ft::map<int, char> mappa;
    for (size_t i = 1; i < 19; i++)
    {
        mappa.insert(ft::make_pair(i, i+33));
    }
    ft::map<int, char>::iterator it = mappa.begin();

    std::cout << it->first << '\n';
    
   

    

// tree.insert(7);
// tree.insert(3);
// tree.insert(18);
// tree.insert(10);
// tree.insert(22);
// tree.insert(8);
// tree.insert(11);
// tree.insert(26);
// tree.insert(2);
// tree.insert(6);
// tree.insert(13);

// tree.printInOrder();
// tree.printLevelOrder();

// std::cout<<std::endl<<"Deleting 18, 11, 3, 10, 22"<<std::endl;

// tree.deleteByVal(18);
// tree.deleteByVal(11);
// tree.deleteByVal(3);
// tree.deleteByVal(10);
// tree.deleteByVal(22);

// tree.printInOrder(); 
// tree.printLevelOrder();
return 0;
}