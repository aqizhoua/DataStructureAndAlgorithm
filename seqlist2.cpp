#include<iostream>
#include<cassert>
using namespace std;

#define MAX_SIZE 10

struct Element {
    int number;
    string name;
};
typedef Element ElemType;

struct SequenceList {
    ElemType data[MAX_SIZE];
    int length;
};

class ListManage {
public:
    ListManage() { InitList(); }
protected:
    SequenceList list_;
public:
    void InitList();
    void ClearList();
    void Insert(int pos, ElemType value);
    void Delete(int pos);
    void PushBack(ElemType value);
    void PopBack();
    void PushFront(ElemType value);
    void PopFront();
    void MergeList(const SequenceList& list2);
    void PrintList();
};

void ListManage::InitList() {
    ClearList();
}

void ListManage::ClearList() {
    list_.length = 0;
    memset(&list_, 0, sizeof(ElemType) * MAX_SIZE);
}

void ListManage::Insert(int pos, ElemType value) {
    assert(pos >= 0 && pos < MAX_SIZE);
    ++list_.length;
    for (int i = list_.length - 1; i > pos; --i) {
        list_.data[i] = list_.data[i - 1];
    }
    list_.data[pos] = value;
}

void ListManage::Delete(int pos) {
    assert(pos >= 0 && pos < MAX_SIZE);
    for (int i = pos; i < list_.length - 1; ++i) {
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
    assert(list_.length > 0);
    Delete(0);
}

void ListManage::MergeList(const SequenceList& list2) {
    assert(list_.length + list2.length <= MAX_SIZE);
    ElemType temp_array[MAX_SIZE] = { 0 };
    int i = 0, j = 0, k = 0;
    while (!(i == list_.length || j == list2.length)) {
        temp_array[k++] = list_.data[i].number < list2.data[j].number ? list_.data[i++] : list2.data[j++];
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
        cout << list_.data[i].number << " ";
    }
    cout << endl;
}


int main() {
    ListManage list_manage;
    ElemType e;

    for (int i = 0; i < 5; ++i) {
        e.number = i;
        list_manage.PushBack(e);
    }
    list_manage.PrintList();
    list_manage.PopFront();
    list_manage.PrintList();
    e.number = -1;
    list_manage.PushFront(e);
    list_manage.PrintList();
    list_manage.PopBack();
    list_manage.PrintList();

    SequenceList sequence_list2;
    sequence_list2.data[0].number = 0;
    sequence_list2.data[1].number = 4;
    sequence_list2.length = 2;
    list_manage.MergeList(sequence_list2);
    list_manage.PrintList();
    return 0;

}
