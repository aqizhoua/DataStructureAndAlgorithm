#include<iostream>
using namespace std;

typedef int ElemType;

struct Node {
	Node* next;
	ElemType value;
};

class LinkList {
protected:
	Node* head_=nullptr;
	int length_=0;
protected:
	void _InitList();
	void _DestroyList();
public:
	LinkList() { _InitList();}
	~LinkList() { _DestroyList(); }
	void InsertNode(int pos, ElemType v);
	void DeleteNode(int pos);
	void PushFront(ElemType v);
	void PopFront();
	void PushBack(ElemType v);
	void PopBack();
	void ReverseList(int pos=0);
	void MergeList(const LinkList& link_list);
	void PrintList();
};

void LinkList::_InitList() {
	head_ = new Node;
	head_->next = nullptr;
}

void LinkList::_DestroyList() {
	Node* temp = head_;
	if (head_) {
		head_ = head_->next;
		delete temp;
		temp = head_;
	}
	length_ = 0;
}

void LinkList::InsertNode(int pos, ElemType v) {
	Node* new_node = new Node;
	new_node->value = v;
	new_node->next = nullptr;
	Node* temp = head_;
	while (pos--) {
		temp = temp->next;
	}
	Node* t_temp = temp->next;
	temp->next = new_node;
	new_node->next = t_temp;
	++length_;
}

void LinkList::DeleteNode(int pos) {
	Node* temp = head_;
	while (pos--) {
		temp = temp->next;
	}
	Node* t_temp = temp->next;
	temp->next = t_temp->next;
	delete t_temp;
	--length_;
}

void LinkList::PushFront(ElemType v) {
	InsertNode(0, v);
}

void LinkList::PopFront() {
	DeleteNode(0);
}

void LinkList::PushBack(ElemType v) {
	InsertNode(length_, v);
}

void LinkList::PopBack() {
	DeleteNode(length_ - 1);
}

void LinkList::ReverseList(int pos) {
	//Node* temp = head_->next;
	//while (pos--) {
	//	temp = temp->next;
	//}
	//Node* t_temp = temp->next;
	//while (t_temp) {
	//	t_temp = temp->next
	//}
}

void LinkList::MergeList(const LinkList& link_list) {
	Node* new_head = new Node;
	Node* new_temp = new_head;
	Node* this_temp = head_->next;
	Node* temp = link_list.head_->next;
	while (this_temp && temp) {
		Node* new_node = new Node;
		new_node->next = nullptr;
		new_temp->next = new_node;
		new_temp = new_node;
		if (this_temp->value < temp->value) {
			new_node->value = this_temp->value;
			this_temp = this_temp->next;			
		}
		else {
			new_node->value = temp->value;
			temp = temp->next;
		}		
	}
	while (this_temp) {
		Node* new_node = new Node;
		new_node->next = nullptr;
		new_temp->next = new_node;
		new_temp = new_node;
		new_node->value = this_temp->value;
		this_temp = this_temp->next;
	}
	while (temp) {
		Node* new_node = new Node;
		new_node->next = nullptr;
		new_temp->next = new_node;
		new_temp = new_node;
		new_node->value = temp->value;
		temp = temp->next;
	}
	_DestroyList();
	head_ = new_head;
}

void LinkList::PrintList() {
	Node* temp = head_->next;
	while (temp) {
		cout << temp->value << " ";
		temp = temp->next;
	}
	cout << endl;
}



int main() {
	LinkList link_list;
	ElemType e;
	e = 1;link_list.PushBack(e);
	e = 2;link_list.PushBack(e);
	e = 3;link_list.PushFront(e);
	e = 4;link_list.PushFront(e);
	link_list.PrintList();
	link_list.PopBack();
	link_list.PrintList();
	link_list.InsertNode(1, 100);
	link_list.DeleteNode(2);
	link_list.PrintList();


	LinkList link_list1;
	link_list1.PushBack(1);
	link_list1.PushBack(3);
	link_list1.PushBack(5);
	link_list1.PushBack(7);

	LinkList link_list2;
	link_list2.PushBack(2);
	link_list2.PushBack(4);
	link_list2.PushBack(6);
	link_list2.PushBack(8);

	link_list1.MergeList(link_list2);
	link_list1.PrintList();


	return 0;
}