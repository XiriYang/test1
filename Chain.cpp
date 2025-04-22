template<class T>
struct chainNode {
	//数据成员
	T element;
	chainNode<T>* next;
	//方法
	chainNode() {
		chainNode(const T & element)
		{
			this->element = element;
		}
	}
	chainNode(coondt T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};
template<class T>
class chain :public:linearList<T>
{
public;
//构造函数，复制构造函数和析构函数
chain(int initialCapacity = 10);
chain(const chain<T>&);
~chain();
bool empty()const { return listSze == 0; }
int size()const { return listSize; }
T& get(int theIndex)const;
int indexOf(const T& theElement)const;
void erase(int thrIndex);
void insert(int theIndex, const T& theElement);
protected:
	void checkIndex(int theIndex)const;
	chainNode<T>* firstNode;
	int listSize;
};
//链表的构造函数和复制构造函数
template<class T>
chain<T>::chain(int initialCapacity)
{
	//构造函数
	firstNode = NULL;
	listSize = 0;
}
template<class T>
chain<T>::chain(const chain<T>& theList)
{
	//复制构造函数
	listSize = theList.listSize;
	if (listSize == 0)
	{
		//链表为空
		firstNode = NULL;
		return;
	}
	//链表theSize非空
	chainNode<T>* sourceNode = theList.firstNode;
	firstNode = new chainNode<T>(sourceNode->element);//复制首元素
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;
	//当前节点的最后一个节点
	while (sourceNode != NULL)
	{
		//复制剩下的元素
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;//链表结束
}
//链表的析构函数
template<class T>
chain<T>::~chain()
{
	//删除链表的所有节点
	while (firstNode != NULL)
	{
		//删除首节点
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		fistNode = nextNode;
	}
}