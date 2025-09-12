#include "VectorStore.h"

int main() {
    // Student can use this main function to do some basic testing
    // ArrayList test
    // ArrayList<int> array(15);
    // array.add(1);
    // array.add(2);
    // array.add(3);
    // array.add(4);
    // array.add(5);
    // array.add(6);
    // // cout << array.toString() << endl;
    // // cout << array.size() << endl;
    // // cout << boolalpha << array.empty() << endl;
    // // array.removeAt(0);
    // // array.add(3, 10);
    // // cout << array.toString() << endl;

    // ArrayList<int> copy = array;
    // cout << boolalpha << (array.begin() != copy.begin()) << endl;
    // auto it1 = array.begin();
    // *it1 = 10;
    // cout << array.toString() << endl << copy.toString() << endl;

    // SinglyLinkedList test
    SinglyLinkedList<int> list;
    cout << list.toString() << endl;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    list.add(6);
    cout << list.toString() << endl;

    list.truncate(3);
    cout << list.size() << endl << list.toString() << endl;
    // for (auto it = list.begin(); it != list.end(); it++)
    // {
    //     cout << *it << endl;
    // }
    // try
    // {
    //     cout << list.get(6) << endl;
    // }
    // catch (out_of_range e)
    // {
    //     cerr << e.what() << endl;
    // }
    return 0;
}