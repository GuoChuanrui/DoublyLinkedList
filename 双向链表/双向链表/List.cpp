#include<iostream>
#include<assert.h>
using namespace std;

typedef int DataType;
struct ListNode
{
	DataType _data;
	ListNode* _next;
	ListNode* _prev;

	ListNode(const DataType& x)
		:_data(x)
		,_next(NULL)
		,_prev(NULL)
	{}
};

class List
{
public:
	List()
		:_head(NULL)
		,_tail(NULL)
	{}

	List(const List& l)
		:_head(NULL)
		,_tail(NULL)
	{
		ListNode* tmp = l._head;
		while(tmp)
		{
			PushBack(tmp->_data);
			tmp = tmp->_next;
		}
	}

	List& operator= (List l)
	{
		_Swap(l);
		return *this;
	}

	~List()
	{
		_Clear();
	}

	void _Clear()     //���
	{
		ListNode* begin = _head;
		while(begin)
		{
			ListNode* del = begin;
			begin  =begin->_next;
			delete del;
		}
		_head = _tail = NULL;
	}

	void _Swap(List& l)
	{
		swap(_head,l._head);
		swap(_tail,l._tail);
	}
	
	void PushBack(const DataType&x)   //β��
	{
		if(_head == NULL)      //��
		{
			_head = new ListNode(x);
			_tail = _head;
		}
		else
		{
			ListNode* tmp = new ListNode(x);
			_tail->_next = tmp;
			tmp->_prev = _tail;
			_tail = tmp;
		}
	}

	void PushFront(const DataType&x)
	{
		ListNode* tmp = new ListNode(x);
		if(_head == NULL)
		{
			_head = _tail = tmp;
			_tail->_next = NULL;
		}
		else
		{
			tmp->_next = _head;
			_head->_prev = tmp;
			_head = tmp;
		}
	}

	void PopBack()
	{
		if(_head == _tail)    //Ϊ�ջ�ֻ��һ���ڵ�
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			ListNode* prev = _tail->_prev;
			prev->_next = NULL;
			delete _tail;
			_tail = prev;
		}
	}

	void PopFront()
	{
		if(_head == _tail)    //Ϊ�ջ�ֻ��һ���ڵ�
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			ListNode* next = _head->_next;
			delete _head;
			_head = next;
			next->_prev = NULL;
		}
	}

	void Insert(ListNode* pos,const DataType& x)    //����
	{
		assert(pos);
		ListNode* next = pos->_next;
		ListNode* tmp = new ListNode(x);
		if(pos == _tail)       //β��
		{
			_tail->_next  =tmp;
			tmp->_prev = _tail;
			_tail = tmp;
		}
		else     //�м����
		{
			pos->_next = tmp;
			tmp->_next = next;
			next->_prev = tmp;
			tmp->_prev = pos;
		}
	}

	ListNode* Find(const DataType& x)
	{
		ListNode* cur = _head;
		while(cur)
		{
			if(cur->_data == x)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return NULL;
	}

	void Erase(ListNode* pos)
	{
		assert(pos);
		//һ���ڵ�
		if(_head == _tail)
		{
			assert(_head == pos);
			delete pos;
			_head = _tail = NULL;
			return;
		}
		//����ڵ�
		if(pos == _head)    //ͷɾ
		{
			_head = _head->_next;
			_head->_prev = NULL;
		}
		else if(pos == _tail)    //βɾ
		{
			_tail = _tail->_prev;
			_tail->_next = NULL;
		}
		else      //ɾ�м��
		{
			ListNode* prev = pos->_prev;
			ListNode* next = pos->_next;
			prev->_next = next;
			next->_prev =prev;
		}
		delete pos;
	}

	void Reverse()
	{
		ListNode* left = _head;
		ListNode* right = _tail;
		while(!(left == right || right->_next == left))    //�����������Ҳ���ȣ�ż�������ҵ���һ�������غ�
		{
			swap(left->_data,right->_data);
			left = left->_next;
			right = right->_prev;
		}
	}

	void Print()
	{
		ListNode* begin = _head;
		while(begin)
		{
			cout<<begin->_data<<"<->";
			begin = begin->_next;
		}
		cout<<"NULL"<<endl;
	}
private:
	ListNode* _head;
	ListNode* _tail;
};
int main()
{
	List l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	l1.Print();

	//ListNode* tmp1 = l1.Find(4);
	//l1.Insert(tmp1,0);
	//l1.PopBack();
	//ListNode* tmp2 = l1.Find(3);
	//l1.Erase(tmp2);

	l1.Reverse();
	l1.Print();
	/*l1.PushFront(0);
	l1.Print();
	l1.PopFront();
	l1.Print();

	List l2;
	l2.PushFront(0);
	l2.Print();
	l2.PopFront();
	l2.Print();
	l2.PopFront();
	l2.Print();*/

	return 0;
}