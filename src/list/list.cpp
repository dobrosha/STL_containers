#include <iostream>
#include <list>
//#include "s21_list.h"
using namespace std;

int main() {

    list<int> std_list_first = {};
    list<int> std_list_second = {1, 3, 4, 5};
    std_list_first.merge(std_list_second);
    for (auto it = std_list_first.begin(); it != std_list_first.end(); ++it) {
        cout << *it << endl;









    return 0;
}