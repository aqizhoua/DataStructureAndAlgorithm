#include<iostream>
#include<cassert>
using namespace std;

#define MAX_SIZE 10
typedef int ElemType;

struct SequenceList {
    ElemType data[MAX_SIZE];
    int length;
};

class ListManage {
public:
    ListManage() { _InitList(); }
protected:
    SequenceList list_;
protected:
    void _InitList();
    void _ClearList();
public:
    void Insert(int pos, ElemType value);
    void Delete(int pos);
    void PushBack(ElemType value);
    void PopBack();
    void PushFront(ElemType value);
    void PopFront();
    void MergeList(const SequenceList& list2);
    void PrintList();
};

void ListManage::_InitList() {
    _ClearList();
}

void ListManage::_ClearList() {
    list_.length = 0;
    memset(&list_, 0, sizeof(ElemType) * MAX_SIZE);
}

void ListManage::Insert(int pos, ElemType value) {
    assert(pos >= 0 && pos < MAX_SIZE);
    ++list_.length;
    for (ElemType i = list_.length-1; i >pos; --i) {
        list_.data[i] = list_.data[i-1];
    }
    list_.data[pos] = value;
}

void ListManage::Delete(int pos) {
    assert(pos >= 0 && pos < MAX_SIZE);
    for (ElemType i = pos; i < list_.length-1; ++i) {
        list_.data[i] = list_.data[i + 1];
    }
    --list_.length;
}

void ListManage::PushBack(ElemType value) {
    assert(list_.length < MAX_SIZE);
    Insert(list_.length, value);
}

void ListManage::PopBack() {
    assert(list_.length > 0);
    Delete(list_.length - 1);
}

void ListManage::PushFront(ElemType value) {
    assert(list_.length < MAX_SIZE);
    Insert(0, value);
}

void ListManage::PopFront() {
    assert(list_.length >0);
    Delete(0);
}

void ListManage::MergeList(const SequenceList& list2) {
    assert(list_.length + list2.length <= MAX_SIZE);
    ElemType temp_array[MAX_SIZE] = { 0 };
    int i = 0, j = 0,k=0;
    while (!(i== list_.length||j==list2.length)) {
        temp_array[k++] = list_.data[i] < list2.data[j] ? list_.data[i++] : list2.data[j++];
    }
    if (i == list_.length) {
        while (j < list2.length) {
            temp_array[k++] = list2.data[j++];
        }
    }
    else if (i == list2.length) {
        while (j < list_.length) {
            temp_array[k++] = list_.data[j++];
        }
    }
    memcpy(list_.data, temp_array, sizeof(ElemType) * (list_.length + list2.length));
    list_.length += list2.length;
}

void ListManage::PrintList() {
    for (int i = 0; i < list_.length; ++i) {
        cout << list_.data[i] << " ";
    }
    cout << endl;
}


int main() {
    ListManage list_manage;
    for (int i = 0; i < 5; ++i)
        list_manage.PushBack(i);
    list_manage.PrintList();
    list_manage.PopFront();
    list_manage.PrintList();
    list_manage.PushFront(-1);
    list_manage.PrintList();
    list_manage.PopBack();
    list_manage.PrintList();

    SequenceList sequence_list2;
    sequence_list2.data[0] = 0;
    sequence_list2.data[1] = 4;
    sequence_list2.length = 2;
    list_manage.MergeList(sequence_list2);
    list_manage.PrintList();


}