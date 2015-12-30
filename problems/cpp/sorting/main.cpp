#include "base.h"
#include <assert.h>
#include "bubbleSort.h"
#include "mergeSort.h"
#include <ctime>
using namespace std;

int main(int argc, char **argv) {
    time_t t1, t2;
    Sort s = Sort(5);
    s.sortIt();
    cout << (s.is_sorted() ? "Sorted" : "Not Sorted")  << endl;

    BubbleSort bs = BubbleSort(80000);
    t1 = time(NULL);
    bs.sortIt();
    t2 = time(NULL);
    cout << t2-t1 << endl;
    cout << (bs.is_sorted() ? "Sorted" : "Not Sorted")  << endl;
    MergeSorter ms = MergeSorter(9);
    t1 = time(NULL);
    ms.sortIt();
    t2 = time(NULL);
    ms.print();
    cout << t2-t1 << endl;
    cout << (ms.is_sorted() ? "Sorted" : "Not Sorted")  << endl;
}
