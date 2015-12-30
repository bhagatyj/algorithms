#include "base.h"
#include <assert.h>
#include "bubbleSort.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "selectionSort.h"
#include <ctime>
using namespace std;

int main(int argc, char **argv) {
    time_t t1, t2;
/*
    Sort s = Sort(5);
    s.sortIt();
    cout << (s.is_sorted() ? "Sorted" : "Not Sorted")  << endl;

    BubbleSort bs = BubbleSort(800);
    t1 = time(NULL);
    bs.sortIt();
    t2 = time(NULL);
    //bs.print();
    cout << t2-t1 << endl;
    cout << (bs.is_sorted() ? "Sorted" : "Not Sorted")  << endl;
    MergeSorter ms = MergeSorter(9);
    t1 = time(NULL);
    ms.sortIt();
    t2 = time(NULL);
    //ms.print();
    cout << t2-t1 << endl;
    cout << (ms.is_sorted() ? "Sorted" : "Not Sorted")  << endl;

    QuickSorter qs = QuickSorter(5);
    qs.print();
    qs.sortIt();
    cout << (qs.is_sorted() ? "Sorted" : "Not Sorted")  << endl;
    qs.print();
*/
    SelectionSorter ss = SelectionSorter(50);
    ss.print();
    ss.sortIt();
    cout << (ss.is_sorted() ? "Sorted" : "Not Sorted")  << endl;
    ss.print();
}
