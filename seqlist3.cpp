//
// Created by aqizhou on 2023/4/9.
//

#include<iostream>
#include<cassert>
using namespace std;

#define MAX_SIZE 10
#define EXTEND_SIZE 5
typedef int ElemType;

struct SequenceList {
    ElemType* data;
    int length;
    int max_size;
};

class ListManage {
public:
    ListManage() { InitList(); }
    ~ListManage(){DestroyList();}
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
    void DestroyList();
    void ExtendList();
};

void ListManage::InitList() {
    list_.data = new ElemType[MAX_SIZE];
    list_.max_size=MAX_SIZE;
    ClearList();
}

void ListManage::ClearList() {
    memset(list_.data,0,sizeof(ElemType)*MAX_SIZE);
    list_.length=0;
}

void ListManage::Insert(int pos, ElemType value){
    if(list_.length>=list_.max_size){
        ExtendList();
    }
    for(int i=list_.length;i>pos;--i){
        list_.data[i]=list_.data[i-1];
    }
    list_.data[pos]=value;
    ++list_.length;
}

void ListManage::PushBack(ElemType value) {
    Insert(list_.length,value);
}

void ListManage::PopBack() {
    Delete(list_.length-1);
}

void ListManage::PushFront(ElemType value) {
    Insert(0,value);
}

void ListManage::PopFront() {
    Delete(0);
}

void ListManage::Delete(int pos) {
    assert(pos<list_.length&&pos>=0);
    for(int i=pos;i<list_.length-1;++i){
        list_.data[i]=list_.data[i+1];
    }
    --list_.length;
}

void ListManage::MergeList(const SequenceList &list2) {
    ElemType* new_array = new ElemType[list_.max_size+list2.length];
    int new_size = list_.max_size+list2.length;
    memset(new_array,0,sizeof(ElemType)*new_size);
    int i=0,j=0,k=0;
    while(j<list_.length&&k<list2.length){
        new_array[i++]=list_.data[j]<list2.data[k]?list_.data[j++]:list2.data[k++];
    }
    while(j<list_.length){
        new_array[i++]=list_.data[j++];
    }
    while(k<list2.length){
        new_array[i++]=list2.data[k++];
    }
    delete []list_.data;
    list_.data=new_array;
    list_.length+=list2.length;
    list_.max_size=new_size;
}

void ListManage::PrintList() {
    for(int i=0;i<list_.length;++i){
        cout<<list_.data[i]<<" ";
    }
    cout<<endl;
}

void ListManage::DestroyList() {
    if(list_.data){
        delete []list_.data;
    }
    list_.length=0;
}

void ListManage::ExtendList() {
    ElemType* new_data = new ElemType[list_.length+EXTEND_SIZE];
    int new_size = list_.length+EXTEND_SIZE;
    memset(new_data,0,sizeof(ElemType)*new_size);
    memcpy(new_data,list_.data,sizeof(ElemType)*list_.length);
    delete [] list_.data;
    list_.data=new_data;
    list_.max_size=new_size;
}

int main(){
    ListManage list_manage;
    for (int i = 0; i < 5; ++i)
        list_manage.PushBack(i);
    list_manage.PrintList();
    list_manage.PopFront();
    list_manage.PrintList();
    list_manage.PushFront(-1);
    list_manage.PrintList();
    list_manage.PopBack();
    list_manage.Insert(2,1);
    list_manage.PrintList();

    SequenceList sequence_list2;
    sequence_list2.data = new ElemType[2];
    sequence_list2.data[0] = 0;
    sequence_list2.data[1] = 4;
    sequence_list2.length = 2;
    list_manage.MergeList(sequence_list2);
    list_manage.PrintList();
}
