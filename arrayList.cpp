#include <iostream>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <stdexcept> // ���ڱ�׼�쳣��
using namespace std;

// �����쳣��
class illegalParameterVal : public logic_error {
public:
    explicit illegalParameterVal(const string& message) : logic_error(message) {}
};

class illegalIndex : public logic_error {
public:
    explicit illegalIndex(const string& message) : logic_error(message) {}
};

// һ�����Ա�ĳ�����
template <class T>
class linearList {
public:
    virtual ~linearList() {};
    virtual bool empty() const = 0; // ���� true, ���ҽ������Ա�Ϊ��
    virtual int size() const = 0; // �������Ա��Ԫ�ظ���
    virtual T& get(int theIndex) const = 0; // ��������Ϊ theIndex ��Ԫ��
    virtual int indexOf(const T& theElement) const = 0; // ���� theElement ��һ�γ���ʱ������
    virtual void erase(int theIndex) = 0; // ɾ������Ϊ theIndex ��Ԫ��
    virtual void insert(int theIndex, const T& theElement) = 0; // �� theElement ��������Ϊ theIndex ��λ��
    virtual void output(ostream& out) const = 0; // �����Ա��������� out
};

// �ı�һ��һά����ĳ���
template <class T>
void changeLength1D(T*& a, int oldLength, int newLength) {
    if (newLength < 0)
        throw illegalParameterVal("New length must be >= 0.");
    T* temp = new T[newLength]; // ������
    int number = min(newLength, oldLength); // ��Ҫ���Ƶ�Ԫ�ظ���
    copy(a, a + number, temp); // ����
    delete[] a; // ɾ��������
    a = temp;
}

// arrayList ���ඨ��
template <class T>
class arrayList : public linearList<T> {
public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>&);
    ~arrayList() {
        delete[] element;
        element = nullptr; // ��������ָ��
    }
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    int capacity() const { return arrayLength; }

protected:
    void checkIndex(int theIndex) const; // ��������Ч���׳��쳣
    T* element; // һά����
    int arrayLength; // һά���������
    int listSize; // Ԫ�صĸ���
};

// arrayList �Ĺ��캯��
template <class T>
arrayList<T>::arrayList(int initialCapacity) {
    if (initialCapacity < 1) {
        throw illegalParameterVal("Initial capacity must be > 0.");
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T>& theList) {
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}

// ��������Ƿ���Ч
template <class T>
void arrayList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        ostringstream s;
        s << "Invalid index: " << theIndex << ". Valid range: [0, " << listSize - 1 << "].";
        throw illegalIndex(s.str());
    }
}

// ��������Ϊ theIndex ��Ԫ��
template <class T>
T& arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return element[theIndex];
}

// ���� theElement ��һ�γ���ʱ���������������򷵻� -1
template <class T>
int arrayList<T>::indexOf(const T& theElement) const {
    int theIndex = (int)(find(element, element + listSize, theElement) - element);
    if (theIndex == listSize)
        return -1;
    else
        return theIndex;
}

// ɾ������Ϊ theIndex ��Ԫ��
template <class T>
void arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    copy(element + theIndex + 1, element + listSize, element + theIndex);
    element[--listSize].~T();
}

// ������ theIndex ��λ���ϲ���һ��Ԫ��
template <class T>
void arrayList<T>::insert(int theIndex, const T& theElement) {
    if (theIndex < 0 || theIndex > listSize) {
        ostringstream s;
        s << "Invalid index: " << theIndex << ". Valid range: [0, " << listSize << "].";
        throw illegalIndex(s.str());
    }
    if (listSize == arrayLength) {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    copy_backward(element + theIndex, element + listSize, element + listSize + 1);
    element[theIndex] = theElement;
    listSize++;
}
