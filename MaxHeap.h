#ifndef MEVNE_WET2_HEAP_H
#define MEVNE_WET2_HEAP_H

#include <functional>
#include <iostream>
#include <math.h>

template <class K>
class MaxHeap{
private:
    K* heapArr;
    int size;
    int capacity;
    void SiftDown(int i);
    int SiftUp(int i);
public:
    MaxHeap(int cap);
    MaxHeap(const MaxHeap&) = delete;
    ~MaxHeap();
    int Parent(int i);
    int RightSon(int i);
    int LeftSon(int i);
    void MakeHeap(K arr[], int n);
    int Insert (const K& key);
    K& FindMax();
    void DelMax();
    int GetSize();
    void IncreaseKey(K value, int index);
};


template <class K>
static void Swap(K* a, K* b){
    K tmp = *a;
    *a = *b;
    *b = tmp;
}

template <class K>
int MaxHeap<K>::Parent(int i) {
    return (i - 1) / 2;
}

template <class K>
int MaxHeap<K>::RightSon(int i) {
    return (2 * i) + 2;
}

template <class K>
int MaxHeap<K>::LeftSon(int i) {
    return (2 * i) + 1;
}

template <class K>
int MaxHeap<K>::SiftUp(int i) {
    while (i != 0 && heapArr[i] > heapArr[Parent(i)]){
        Swap(heapArr + i, heapArr + Parent(i));
        i = Parent(i);
    }
    return i;
}

template <class K>
void MaxHeap<K>::SiftDown(int i) {
    int j = i;
    while (j <= (size-2) / 2) {
        if (LeftSon(j) == (size - 1)){
            if (heapArr[j] < heapArr[LeftSon(j)]) {
                Swap(heapArr + j, heapArr + LeftSon(j));
            }
            j = LeftSon(j);
        }
        else{
            if (heapArr[j] < heapArr[LeftSon(j)] && heapArr[LeftSon(j)] > heapArr[RightSon(j)]){
                Swap(heapArr + LeftSon(j), heapArr + j);
                j = LeftSon(j);
            }
            else if (heapArr[j] < heapArr[RightSon(j)] && heapArr[RightSon(j)] > heapArr[LeftSon(j)]){
                Swap(heapArr + RightSon(j), heapArr + j);
                j = RightSon(j);
            }
            else break;
        }
    }
}

template <class K>
MaxHeap<K>::MaxHeap(int cap){
    size = 0;
    capacity = cap;
    heapArr = new K[cap];
}

template <class K>
void MaxHeap<K>::MakeHeap(K* arr, int n) {
    for (int i = 0; i < n; i++) {
        heapArr[i] = arr[i];
    }
    size = n;
    for (int j = (n-1)/2; j >= 0 ; j--) {
        SiftDown(j);
    }
}

template <class K>
int MaxHeap<K>::Insert(const K &key) {
    int i = size;
    if (size == capacity){
        K* tmp = new K[2*capacity];
        for (int j = 0; j < size; j++) {
            tmp[j] = heapArr[j];
        }
        delete[] heapArr;
        capacity = 2 * capacity;
        heapArr = tmp;
    }
    size++;
    heapArr[i] = key;
    return SiftUp(i);
}

template <class K>
K& MaxHeap<K>::FindMax() {
        return heapArr[0];
}

template <class K>
void MaxHeap<K>::DelMax() {
    if (size > 0) {
        Swap(heapArr, heapArr + (size - 1));
        size--;
        SiftDown(0);
        double check = ((double) size / (double) capacity);
        if (check <= (1 / 4)) {
            int *tmp = new K[capacity / 2];
            for (int i = 0; i < size; i++) {
                tmp[i] = heapArr[i];
            }
            delete[] heapArr;
            capacity = capacity / 2;
            heapArr = tmp;
        }
    }
}

template <class K>
int MaxHeap<K>::GetSize() {
    return size;
}
template<class K>
void MaxHeap<K>::IncreaseKey(K value, int index){
    if (heapArr[index] < value)
        heapArr[index] = value;
    SiftUp(index);
}

template <class K>
MaxHeap<K>::~MaxHeap() {
    delete[] heapArr;
}

#endif //MEVNE_WET2_HEAP_H
