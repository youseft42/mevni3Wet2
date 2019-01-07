#include <functional>
#include <iostream>

#ifndef WET2_LIST_H
#define WET2_LIST_H

template <class T, class K>
class ListNode{
public:
    T data;
    K key;
    ListNode* nextNode;
    ListNode* prevNode;
    ListNode(const T& data, const K& key);
    ListNode(const ListNode& list) = default;
    ~ListNode() = default;
};

template <class T, class K>
ListNode<T,K>::ListNode(const T& data, const K& key) : data(data), key(key), nextNode(NULL) ,prevNode(NULL){}

template <class T, class K>
class List {
    ListNode<T,K>* head;
    int size;
public:
    List();
    List(const List& list);
    ~List();
    void ListInsert(const T& data, const K& key);
    void ListRemove(const K key);
    bool ListContains(const K key);
    void ListPutInArray(K* arr);
    T& GetFirstData();
    K& GetFirstKey();
    int GetSize();
    void ListRemoveNode(ListNode<T,K>* node);
    bool GetNode(const K key,ListNode<T,K>* node);
    T& GetData(const K key);
    template <class F>
    void DoSomething(F& f){
        ListNode<T,K>* tmp = head;
        while (tmp){
            f(tmp->data);
            tmp = tmp->nextNode;
        }
    }
};

template <class T, class K>
List<T,K>::List() : head(NULL), size(0) {}

template <class T, class K>
List<T,K>::~List() {
    ListNode<T,K>* tmp = head;
    while (tmp != NULL){
        ListNode<T,K>* next = tmp->nextNode;
        delete tmp;
        tmp = next;
    }
}

template <class T, class K>
List<T,K>::List(const List& list){
    size = 0;
    ListNode<T,K>* tmp = list.head;
    while (tmp){
        this->ListInsert(tmp->data, tmp->key);
        tmp = tmp->nextNode;
    }
}

template <class T, class K>
void List<T,K>::ListInsert(const T& data, const K &key) {
    ListNode<T,K>* tmp = new ListNode<T,K>(data, key);
    if(head) head->prevNode=tmp;
    tmp->nextNode = head;
    tmp->prevNode = NULL;
    head = tmp;
    size++;
}
template <class T, class K>
void List<T,K>::ListRemoveNode(ListNode<T,K>* node){
    if(!node)
        return;
    ListNode<T,K>* prev=node->prevNode;
    if(prev)
        prev->nextNode=node->nextNode;
    if(node->nextNode)
        node->nextNode->prevNode=prev;
    size--;
    delete node;
};
template <class T, class K>
void List<T,K>::ListRemove(const K key) {
    if(head){
        ListNode<T,K>* tmp = head;
        if (head->key == key){
            if(size == 1){
                size--;
                delete tmp;
                head=NULL;
                return;
            }
            head = head->nextNode;
            size--;
            delete tmp;
            return;
        }
        ListNode<T,K>* prev = head;
        tmp = head->nextNode;
        while (tmp){
            if (tmp->key == key) {
                prev->nextNode = tmp->nextNode;
                delete tmp;
                size--;
                return;
            }
            tmp = tmp->nextNode;
            prev = prev->nextNode;
        }
    }
}

template <class T, class K>
bool List<T,K>::ListContains(const K key) {
    ListNode<T,K>* tmp = head;
    while (tmp){
        if (tmp->key == key){
            return true;
        }
        tmp = tmp->nextNode;
    }
    return false;
}
template <class T, class K>
bool List<T,K>::GetNode(const K key,ListNode<T,K>* node) {
    ListNode<T,K>* tmp = head;
    while (tmp){
        if (tmp->key == key){
            node=tmp;
            return true;
        }
        tmp = tmp->nextNode;
    }
    return false;
}

template <class T, class K>
T& List<T,K>::GetFirstData() {
    return head->data;
}

template <class T, class K>
K& List<T,K>::GetFirstKey() {
    return head->key;
}

template <class T, class K>
int List<T,K>::GetSize() {
    return size;
}

template <class T, class K>
T& List<T,K>::GetData(const K key) {
    ListNode<T,K>* tmp = head;
    while (tmp){
        if (tmp->key == key){
            break;
        }
        tmp = tmp->nextNode;
    }
    return tmp->data;
}

template <class T, class K>
void List<T,K>::ListPutInArray(K* arr) {
    ListNode<T,K>* tmp = head;
    int i = 0;
    while(tmp){
        arr[i] = tmp->key;
        tmp = tmp->nextNode;
        i++;
    }
}

#endif //WET2_LIST_H
