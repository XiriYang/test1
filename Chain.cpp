template<class T>
struct chainNode {
	//���ݳ�Ա
	T element;
	chainNode<T>* next;
	//����
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
//���캯�������ƹ��캯������������
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
//����Ĺ��캯���͸��ƹ��캯��
template<class T>
chain<T>::chain(int initialCapacity)
{
	//���캯��
	firstNode = NULL;
	listSize = 0;
}
template<class T>
chain<T>::chain(const chain<T>& theList)
{
	//���ƹ��캯��
	listSize = theList.listSize;
	if (listSize == 0)
	{
		//����Ϊ��
		firstNode = NULL;
		return;
	}
	//����theSize�ǿ�
	chainNode<T>* sourceNode = theList.firstNode;
	firstNode = new chainNode<T>(sourceNode->element);//������Ԫ��
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;
	//��ǰ�ڵ�����һ���ڵ�
	while (sourceNode != NULL)
	{
		//����ʣ�µ�Ԫ��
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;//�������
}
//�������������
template<class T>
chain<T>::~chain()
{
	//ɾ����������нڵ�
	while (firstNode != NULL)
	{
		//ɾ���׽ڵ�
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		fistNode = nextNode;
	}
}