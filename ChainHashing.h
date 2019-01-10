#include "List.h"

#ifndef WET2_CHAINHASHING_H
#define WET2_CHAINHASHING_H

static const int minTableSize = 12;

template <class T, class K>
class ChainHashing {
    int size;
    int numOfElements;
    List<T,K>* listArray;
public:
    ChainHashing(int numOfElements);
    ChainHashing(const ChainHashing&) = delete;
    ~ChainHashing();
    void MakeHash(T* dataArr, K* keyArr, int arraySize);
    void Insert(const T& data, const K& key);
    void Delete(const K key);
    bool contains(const K key);
    T& GetData(const K key);
    int GetNumOfElements();
    template <class F>
    void DoSomething(F& f){
        for (int i = 0; i < size; i++){
            listArray[i].DoSomething(f);
        }
    }
};

template <class T, class K>
static List<T,K>* NewTable(List<T,K>* listArray, int size, int newSize){
    int listSize,h;
    T tmpData;
    K tmpKey;
    List<T,K>* newList = new List<T,K>[newSize];
    for (int i = 0; i < size; i++) {
        listSize = listArray[i].GetSize();
        for (int j = 0; j < listSize; j++) {
            tmpData = listArray[i].GetFirstData();
            tmpKey = listArray[i].GetFirstKey();
            listArray[i].ListRemove(tmpKey);
            h = tmpKey % (newSize);
            newList[h].ListInsert(tmpData, tmpKey);
        }
    }
    return newList;
};

template <class T, class K>
ChainHashing<T,K>::ChainHashing(int numOfElements) : size(minTableSize), numOfElements(0) {
    if( (2*numOfElements) > minTableSize ){
        listArray = new List<T,K>[2*numOfElements];
        size = 2 * numOfElements;

    } else {
        listArray = new List<T, K>[minTableSize];
        size = minTableSize;
    }
}

template <class T, class K>
void ChainHashing<T,K>::MakeHash(T *dataArr, K *keyArr, int arraySize) {
    int h;
    for (int i = 0; i < arraySize; i++) {
        h = keyArr[i] % size;
        listArray[h].ListInsert(dataArr[i],keyArr[i]);
        numOfElements++;
    }
}

template <class T, class K>
ChainHashing<T,K>::~ChainHashing() {
    delete[] listArray;
}

template <class T, class K>
void ChainHashing<T,K>::Insert(const T &data, const K &key) {
    int h = key % size;
    if (listArray[h].ListContains(key)){
        return;
    }
    listArray[h].ListInsert(data,key);
    numOfElements++;
    if (numOfElements == size){
        List<T,K>* newTable = NewTable(listArray, size, 2*size);
        delete[] listArray;
        listArray = newTable;
        size = 2 * size;
    }
}

template <class T, class K>
void ChainHashing<T,K>::Delete(const K key) {
    int h = key % size;
    listArray[h].ListRemove(key);
    numOfElements--;
    if ( (numOfElements == (size/4)) && (numOfElements > 12) ){
        List<T,K>* newTable = NewTable(listArray, size, size/2);
        delete[] listArray;
        listArray = newTable;
        size = size / 4;
    }
}

template <class T, class K>
bool ChainHashing<T,K>::contains(const K key) {
    int h = key % size;
    return listArray[h].ListContains(key);
}

template <class T, class K>
T& ChainHashing<T,K>::GetData(const K key) {
    int h = key % size;
    return listArray[h].GetData(key);
}

template <class T, class K>
int ChainHashing<T,K>::GetNumOfElements() {
    return numOfElements;
}

#endif //WET2_CHAINHASHING_H
