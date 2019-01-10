
#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include <functional>
#include <iostream>
#include <math.h>
#include "exceptions.h"

using namespace Wet1::AVL;

template <class T, class K>
class Node{
public:
    T data;
    K key;
    T max;
    Node* rightSon;
    Node* leftSon;
    Node* parent;
    int balance;
    int height;
    Node(const T data, const K key);
    Node(const Node&) = default;
    ~Node() = default;
};

template <class T, class K,class Function>
class PutInTree {
    Function function;
    int index;
    T* arr;
public:
    PutInTree( Function filter,T* arr) : function(filter) ,index(0), arr(arr) {};
    ~PutInTree() = default;
    void operator() (T& data, K& key){
        data = arr[index];
        key = function(arr[index]);
        index++;
    }
};

template < class T, class K>
class PutInArray {
    int index;
    T* arr;
public:
    PutInArray(int size) : index(0) {
        arr = new T[size];
    }
    ~PutInArray() {
        delete[] arr;
    }
    void operator() (T& data, K& key){
            arr[index] = data;
            index++;

    }
    T* GetArray(){
        return arr;
    }
};

template < class T, class K>
class Counter{
    int count;
public:
    Counter() : count(0){};
    ~Counter() = default;
    void operator() (T& data, K& key){
         count++;
    }
    int GetCounter(){
        return count;
    }
};
template <class T, class K>
static void FixMax (Node<T,K>* root) {
    if(root){
            T leftMax=root->max;
            T rightMax=root->max;
            if (root->leftSon != NULL) {
                leftMax = root->leftSon->max;
            }
            if (root->rightSon != NULL) {
                rightMax = root->rightSon->max;
            }
            if (leftMax > rightMax) {
                if(leftMax > root->max)
                    root->max = leftMax ;
                return;
            }
            if(rightMax > root->max)
                root->max = rightMax;
            else if(root->data > root->max) root->max = root->data;
            if(!root->leftSon && !root->rightSon) root->max = root->data;
    }
};
template <class T, class K>
static void Fixheight (Node<T,K>* root) {
    if (root) {
        int leftHeight = 0;
        int rightHeight = 0;
        if (root->leftSon != NULL) {
            leftHeight = root->leftSon->height;
        }
        if (root->rightSon != NULL) {
            rightHeight = root->rightSon->height;
        }
        if (leftHeight > rightHeight) {
            root->height = leftHeight + 1;
            root->balance = leftHeight - rightHeight;
            FixMax(root);
            return;
        }
        root->height = rightHeight + 1;
        root->balance = leftHeight - rightHeight;
        FixMax(root);
    }

}
template <class T, class K>
static void FixNewMax (Node<T,K>* root) {
    if(root){
        T leftMax=root->data;
        T rightMax=root->data;
        if (root->leftSon != NULL) {
            leftMax = root->leftSon->max;
        }
        if (root->rightSon != NULL) {
            rightMax = root->rightSon->max;
        }
        if (leftMax > rightMax) {
            if(root->data < leftMax)
                root->max = leftMax ;
            else root->max=root->data;
            return;
        }
        if(root->data < rightMax)
            root->max = rightMax ;
        else root->max=root->data;
        return;
    }
};
template <class T, class K>
static void FixTreeMaxAux(Node<T,K>* root){
    if (root){
        FixTreeMaxAux(root->leftSon);
        FixTreeMaxAux(root->rightSon);
        FixNewMax(root);
    }
}

template <class DoSomething, class T, class K>
static void InOrderAux(Node<T,K>* root, DoSomething &doSomething){
    if (root){
        InOrderAux(root->leftSon,doSomething);
        doSomething(root->data, root->key);
        InOrderAux(root->rightSon,doSomething);
    }
}

template <class DoSomething, class T, class K>
static void ReverseInOrderAux(Node<T,K>* root, DoSomething &doSomething){
    Node<T, K>* tmp;
    if (root){
        tmp = root->parent;
        ReverseInOrderAux(root->rightSon, doSomething);
        if(doSomething(root)){
            Fixheight(tmp);
            return;
        }
        ReverseInOrderAux(root->leftSon, doSomething);
        Fixheight(tmp);
    }
}

 template <class T,class Compare>
static int merge1(T* a, int na, T* b, int nb, T* c,Compare& compare){
    int ia, ib, ic;
    for(ia=ib=ic=0; (ia < na) && (ib < nb); ic++){
        if (compare(a[ia],b[ib])<0) {
            c[ic] = a[ia];
            ia++;
        }
        else if (a[ia] == b[ib]){
            c[ic] = a[ia] + b[ib];
            ib++;
            ia++;
        }
        else{
            c[ic] = b[ib];
            ib++;
        }
    }
    for(; ia < na; ia++, ic++) c[ic] = a[ia];
    for(; ib < nb; ib++, ic++) c[ic] = b[ib];
    return ic;
};

template <class T, class K>
class AVL{
    Node<T,K>* head;
    int size;
public:
    AVL();
    AVL(const AVL&) = delete;
    ~AVL();
    int GetSize();
    void Insert (const T& data, const K& key);
    bool contains(const K key);
    void remove(const K key);
    K& getMaxKey();
    T& Get(const K key);
    Node<T,K>* GetNode(const K key);
    T& GetHeadMax();
    template <class DoSomething>
    void InOrder(DoSomething& doSomething) {
        InOrderAux(head,doSomething);
    }
    void FixTreeMax(){
        FixTreeMaxAux(head);
    }
    template <class DoSomething>
    void ReverseInOrder(DoSomething& doSomething ) {
        ReverseInOrderAux(head, doSomething);
    }
    void EmptyTree (int size, Node<T,K>* dummy);
    void BuildAlmostComplete(int size, Node<T,K>* dummy);
    template <class Function,class Compare>
    void uniteTrees(AVL* tree1, AVL* tree2, Function& f,Compare& compare){
        Counter<T, K> counter1;
        tree1->InOrder(counter1);
        Counter<T, K> counter2;
        tree2->InOrder(counter2);
        PutInArray<T, K> putA1(counter1.GetCounter());
        PutInArray<T, K> putA2(counter2.GetCounter());
        tree1->InOrder(putA1);
        tree2->InOrder(putA2);
        int newSize = counter1.GetCounter() + counter2.GetCounter();
        T* merged = new T[newSize];
        newSize = merge1(putA1.GetArray(), counter1.GetCounter(), putA2.GetArray(), counter2.GetCounter(), merged,compare);
        Node<T, K>* dummy = (tree1->head) ? tree1->head : (tree2->head) ? tree2->head : tree1->head;
        BuildAlmostComplete(newSize, dummy);
        PutInTree<T, K,Function> putIn(f,merged);
        this->InOrder(putIn);
        this->size = newSize;
        delete[] merged;
    }
};

// if node is parent's: right son it returns 1, left son 0, otherwise -1
template <class T, class K>
static int CheckWhichSonForParent(Node<T,K>* node){
    if (!(node->parent)) return -1;
    if (node->parent->rightSon == node) return 1;
    return 0;
}

template <class T, class K>
static void DeleteTree(Node<T,K>* head) {
    if (head == NULL ){
        return;
    }
    DeleteTree(head->leftSon);
    DeleteTree(head->rightSon);
    delete head;
}

template <class T, class K>
Node<T,K>::Node(const T data, const K key) : data(data), key(key),max(data), rightSon(NULL), leftSon(NULL),
                                        parent(NULL),  balance(0), height(1) {}

template <class T, class K>
AVL<T,K>::AVL() : head(NULL), size(0) {};

template <class T, class K>
AVL<T,K>::~AVL() {
    DeleteTree(head);
}



template <class T, class K>
static Node<T,K>* RotateLL(Node<T,K>* root) {
    Node<T,K>* parent = root->parent;
    int right = CheckWhichSonForParent(root);
    Node<T,K>* temp = root->leftSon;
    root->leftSon = temp->rightSon;
    if (root->leftSon) root->leftSon->parent = root;
    temp->rightSon = root;
    root->parent = temp;
    temp->parent = parent;
    if (right != -1){
        if (right == 1){
            parent->rightSon = temp;
        } else{
            parent->leftSon = temp;
        }
    }
    Fixheight(root);
    Fixheight(temp);
    return temp;
}

template <class T, class K>
static Node<T,K>* RotateRR(Node<T,K>* root) {
    Node<T,K>* parent = root->parent;
    int right = CheckWhichSonForParent(root);
    Node<T,K>* temp = root->rightSon;
    root->rightSon = temp->leftSon;
    if (root->rightSon) root->rightSon->parent = root;
    temp->leftSon = root;
    root->parent = temp;
    temp->parent = parent;
    if (right != -1){
        if (right == 1){
            parent->rightSon = temp;
        } else{
            parent->leftSon = temp;
        }
    }
    Fixheight(root);
    Fixheight(temp);
    return temp;
}

template <class T, class K>
static Node<T,K>* Balance (Node<T,K>* root){
    Fixheight(root);
    if (root->balance == 2){
        if (root->leftSon->balance < 0){
            root->leftSon = RotateRR(root->leftSon);
        }
        return RotateLL(root);
    }
    if (root->balance == -2){
        if (root->rightSon->balance > 0){
            root->rightSon = RotateLL(root->rightSon);
        }
        return RotateRR(root);
    }
    return root;
}

// if node has: 2 sons it returns 2, right son 1, left son 0, otherwise -1
template <class T, class K>
static int CheckSons(Node<T,K>* node){
    if (!(node->rightSon) && !(node->leftSon)) return -1;
    if ((node->rightSon) && !(node->leftSon)) return 1;
    if (!(node->rightSon) && (node->leftSon)) return 0;
    return 2;
}

template <class T, class K>
static void SwitchNodes(Node<T,K>* node1, Node<T,K>* node2){
    int parentsSon1 = CheckWhichSonForParent(node1);
    int parentsSon2 = CheckWhichSonForParent(node2);
    int height = node1->height;
    int balance = node1->balance;
    Node<T,K>* parent1 = node1->parent;
    Node<T,K>* parent2 = node2->parent;
    node1->height = node2->height;
    node1->balance = node2->balance;
    node2->height = height;
    node2->balance = balance;
    node1->parent = (node1 == parent2) ? node2 : parent2;
    node2->parent = parent1;
    if (parentsSon1 != -1){
        (parentsSon1 == 1) ? parent1->rightSon = node2 : parent1->leftSon = node2;
    }
    if (parentsSon2 != -1){
        (parentsSon2 == 1) ? parent2->rightSon = node1 : parent2->leftSon = node1;
    }
    Node<T,K>* tmp = node1->rightSon;
    node1->rightSon = node2->rightSon;
    node2->rightSon = tmp;
    tmp = node1->leftSon;
    node1->leftSon = node2->leftSon;
    node2->leftSon = tmp;
    if (node1->rightSon) node1->rightSon->parent = node1;
    if (node1->leftSon) node1->leftSon->parent = node1;
    if (node2->rightSon) node2->rightSon->parent = node2;
    if (node2->leftSon) node2->leftSon->parent = node2;
}

template <class T, class K>
static Node<T,K>* FindWhereToAdd(Node<T,K>* root, K key){
    if (root->key < key && (root->rightSon)) return FindWhereToAdd(root->rightSon, key);
    if (root->key > key && (root->leftSon)) return FindWhereToAdd(root->leftSon, key);
    return root;
}


template <class T, class K>
static Node<T,K>* FindKey (Node<T,K>* root, K key) {
    while (root != NULL){
        if (root->key > key){
            root = root->leftSon;
        } else if (root->key < key){
            root = root->rightSon;
        } else{
            return root;
        }
    }
    return NULL;
}

template <class T, class K>
static Node<T,K>* FindMaxKey(Node<T,K>* root){
    Node<T,K>* tmp = root;
    if (tmp != NULL) {
        while (tmp->rightSon != NULL) {
            tmp = tmp->rightSon;
        }
    }
    return tmp;
};

template <class T,class K>
static Node<T,K>* InsertNode (Node<T,K>* root ,const T& data, const K& key) {
    Node<T,K>* temp;
    if (root == NULL){
        return new Node<T, K>(data, key);
    } else if (root->key > key) {
        temp = InsertNode(root->leftSon, data, key);
        root->height++;
        root->leftSon = temp;
        temp->parent = root;

    } else if (root->key < key){
        temp = InsertNode(root->rightSon, data, key);
        root->height++;
        root->rightSon = temp;
        temp->parent = root;
    }
    return Balance(root);
}

template <class T, class K>
int AVL<T,K>::GetSize() {
    return size;
}

template <class T, class K>
void AVL<T,K>::Insert(const T& data, const K& key) {
    if (contains(key)) {
        throw KeyAlreadyExist();
    }
    this->head = InsertNode(head, data, key);
    this->head->parent = NULL;
    size++;
}


template <class T, class K>
bool AVL<T,K>::contains(const K key) {
    Node<T,K>* node = FindKey(head, key);
    if (!node){
        return false;
    }
    return true;
}

template <class T, class K>
T& AVL<T,K>::Get(const K key) {
    Node<T,K>* node = FindKey(head, key);
    return node->data;
}
template <class T, class K>
T& AVL<T,K>::GetHeadMax() {
    return head->max;
}
template <class T, class K>
K& AVL<T,K>::getMaxKey(){
    Node<T, K> *node = FindMaxKey(head);
    return node->data;
};

template <class T, class K>
Node<T,K>* AVL<T,K>::GetNode(const K key) {
    Node<T,K>* node = FindKey(head, key);
    return node;
}

template <class T, class K>
void AVL<T,K>::remove(const K key){
    Node<T,K>* erase = FindKey(head, key);
    if (!(erase)) return;
    Node<T,K>* parent = erase->parent;
    int right = CheckSons(erase);
    int parentsSon = CheckWhichSonForParent(erase);
    if (right == -1){
        if (parentsSon != -1){
            (parentsSon == 1) ? parent->rightSon = NULL : parent->leftSon = NULL;
        }
        if (parentsSon == -1 && size == 1) head = NULL;
    }
    else if (right != 2){
        if (parentsSon == -1){
            head = (erase->rightSon) ? erase->rightSon : erase->leftSon;
            head->parent=NULL;
        }
        else if (parentsSon == 1){
            if (right == 1){
                erase->parent->rightSon = erase->rightSon;
                erase->rightSon->parent = erase->parent;
            }
            else{
                erase->parent->rightSon = erase->leftSon;
                erase->leftSon->parent = erase->parent;
            }
        }
        else{
            if (right == 1){
                erase->parent->leftSon = erase->rightSon;
                erase->rightSon->parent = erase->parent;
            }
            else{
                erase->parent->leftSon = erase->leftSon;
                erase->leftSon->parent = erase->parent;
            }
        }
    }
    else{
        Node<T,K>* alternative = erase->rightSon;
        while (alternative->leftSon) alternative = alternative->leftSon;
        SwitchNodes(erase, alternative);
        parent = erase->parent;
        parentsSon = CheckWhichSonForParent(erase);
        if (parentsSon == 1) {
            erase->parent->rightSon = erase->rightSon;
           if(erase->rightSon) erase->rightSon->parent = erase->parent;
        }
        else{
            erase->parent->leftSon = erase->rightSon;
           if(erase->rightSon) erase->rightSon->parent = erase->parent;
        }
        if (erase == head){
            head = alternative;
            head->parent = NULL;
        }
    }
    Node<T, K>* tmp;
    while (parent != NULL){
        tmp = Balance(parent);
        if (parent == head)
            head = tmp;
        parent = parent->parent;
    }
    delete erase;
    size--;
};

static int power(int h){
    int base = 1;
    while (h){
        base *= 2;
        h--;
    }
    return base;
}

template <class T, class K>
void EmptyTreeAux(Node<T,K>** head,int h, Node<T,K>* dummy ){
    if (!(*head) && h > 0) {
        (*head) = new Node<T, K>(dummy->data, dummy->key);
        (*head)->parent = NULL;
    }
    if (h > 1) {
        (*head)->leftSon = new Node<T, K>(dummy->data, dummy->key);
        (*head)->rightSon = new Node<T, K>(dummy->data, dummy->key);
        (*head)->leftSon->parent = (*head);
        (*head)->rightSon->parent = (*head);
        EmptyTreeAux((&(*head)->rightSon), h - 1, dummy);
        EmptyTreeAux(&((*head)->leftSon), h - 1, dummy);
        Fixheight((*head));
        return;
    }
}

static int GetLog (int size){
    int h = 0;
    if (size == 0) return 0;
    while (size > 1){
        size /= 2;
        h++;
    }
    return h+1;
}

template <class T, class K>
void AVL<T, K>::EmptyTree(int size, Node<T,K>* dummy) {
    int h = GetLog(size);
    EmptyTreeAux(&head, h, dummy);
    this->size = power(h)-1;
}

template<class T, class K>
class DeleteNodes {
    int numOfNodes;
public:

    DeleteNodes(int n) : numOfNodes(n) {}
    ~DeleteNodes() = default;
    bool operator() (Node<T, K>* node){
        if (node->rightSon == NULL && node->leftSon == NULL
            && numOfNodes != 0) {
            int side = CheckWhichSonForParent(node);
            if (side == 1){
                node->parent->rightSon = NULL;
            } else {
                node->parent->leftSon = NULL;
            }
            delete node;
            numOfNodes--;
            return true;
        }
        return false;
    }
};

template <class T,class K>
void AVL<T, K>::BuildAlmostComplete(int s, Node<T,K>* dummy) {
    EmptyTree(s, dummy);
    int numToDelete = this->size - s;
    DeleteNodes<T, K> deleteExtraNode(numToDelete);
    ReverseInOrder(deleteExtraNode);
}

#endif //WET1_AVLTREE_H

