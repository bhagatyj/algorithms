#include "base.h"
#include <assert.h>
#include "bubbleSort.h"
#include "mergeSort.h"
#include "quickSort.h"
#include "selectionSort.h"
#include "heapSort.h"
#include <ctime>
using namespace std;

int main(int argc, char **argv) {
    time_t t1, t2;
    int value;
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
*/
    QuickSorter qs = QuickSorter(5);
	qs.fillRandom();
    qs.print();
    qs.sortIt();
    cout << (qs.is_sorted() ? "Sorted" : "Not Sorted")  << endl;
    qs.print();

/*
    SelectionSorter ss = SelectionSorter(50);
	ss.fillRandom();
    ss.print();
    ss.sortIt();
    cout << (ss.is_sorted() ? "Sorted" : "Not Sorted")  << endl;
    ss.print();
    Heap hp = Heap(100);
    hp.add(2);
    hp.add(3);
    hp.add(1);
    hp.add(4);
    hp.add(9);
    hp.add(8);
    hp.add(6);
    hp.add(5);
    hp.add(7);
    hp.print();
    value = hp.delHead();
    while ( value != -1 ) {
        cout << "Value .. " << value << endl;
        value = hp.delHead();

    }
    HeapSort hs = HeapSort(5000);
    hs.fillRandom();
    //hs.print();
    hs.sortIt();
    cout << (hs.is_sorted() ? "Sorted" : "Not Sorted")  << endl;
    hs.print();
*/
}
