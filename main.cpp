#include "VectorStore.h"

int main() {
    // Student can use this main function to do some basic testing
    ArrayList<int> array(15);
    array.add(1);
    array.add(2);
    array.add(3);
    array.add(4);
    array.add(5);
    array.add(6);
    cout << array.toString() << endl;
    cout << array.size() << endl;
    cout << boolalpha << array.empty() << endl;
    array.removeAt(0);
    array.add(3, 10);
    cout << array.toString() << endl;
    return 0;
}