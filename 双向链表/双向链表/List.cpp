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

	void _Clear()     //清除
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
	
	void PushBack(const DataType&x)   //尾插
	{
		if(_head == NULL)      //空
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
		if(_head == _tail)    //为空或只有一个节点
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
		if(_head == _tail)    //为空或只有一个节点
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

	void Insert(ListNode* pos,const DataType& x)    //插入
	{
		assert(pos);
		ListNode* next = pos->_next;
		ListNode* tmp = new ListNode(x);
		if(pos == _tail)       //尾插
		{
			_tail->_next  =tmp;
			tmp->_prev = _tail;
			_tail = tmp;
		}
		else     //中间插入
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
		//一个节点
		if(_head == _tail)
		{
			assert(_head == pos);
			delete pos;
			_head = _tail = NULL;
			return;
		}
		//多个节点
		if(pos == _head)    //头删
		{
			_head = _head->_next;
			_head->_prev = NULL;
		}
		else if(pos == _tail)    //尾删
		{
			_tail = _tail->_prev;
			_tail->_next = NULL;
		}
		else      //删中间的
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
		while(!(left == right || right->_next == left))    //奇数个：左右不相等；偶数个：右的下一个与左不重合
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