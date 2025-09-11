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
    // cout << array.toString() << endl;
    // cout << array.size() << endl;
    // cout << boolalpha << array.empty() << endl;
    // array.removeAt(0);
    // array.add(3, 10);
    // cout << array.toString() << endl;

    // SinglyLinkedList test
    SinglyLinkedList<int> List;
    List.add(1);
    List.add(2);
    List.add(3);
    List.add(4);
    List.add(5);
    List.add(6);
    cout << List.toString() << endl;
    return 0;
}