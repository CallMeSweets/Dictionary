#include <iostream>
#include "Dictionary.h"
using namespace std;

int main()
{
    Dictionary<int, int> *d1 = new Dictionary<int, int>();
    d1->insert(50,50);
    d1->insert(75,75);
    d1->insert(25,25);
    d1->insert(40,40);
    d1->insert(10,10);
    d1->insert(85,85);
    d1->insert(65,65);
    d1->insert(90,90);
    d1->insert(95,95);
    d1->print_t();


    d1->insert(100,100);
    d1->print_t();

    d1->insert(55,55);
    d1->print_t();

    return 0;
}
