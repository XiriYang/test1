#include <iostream>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <stdexcept> // 用于标准异常类
using namespace std;

// 定义异常类
class illegalParameterVal : public logic_error {
public:
    explicit illegalParameterVal(const string& message) : logic_error(message) {}
};

class illegalIndex : public logic_error {
public:
    explicit illegalIndex(const string& message) : logic_error(message) {}
};

// 一个线性表的抽象类
template <class T>
class linearList {
public:
    virtual ~linearList() {};
    virtual bool empty() const = 0; // 返回 true, 当且仅当线性表为空
    virtual int size() const = 0; // 返回线性表的元素个数
    virtual T& get(int theIndex) const = 0; // 返回索引为 theIndex 的元素
    virtual int indexOf(const T& theElement) const = 0; // 返回 theElement 第一次出现时的索引
    virtual void erase(int theIndex) = 0; // 删除索引为 theIndex 的元素
    virtual void insert(int theIndex, const T& theElement) = 0; // 把 theElement 插入索引为 theIndex 的位置
    virtual void output(ostream& out) const = 0; // 把线性表插入输出流 out
};

// 改变一个一维数组的长度
template <class T>
void changeLength1D(T*& a, int oldLength, int newLength) {
    if (newLength < 0)
        throw illegalParameterVal("New length must be >= 0.");
    T* temp = new T[newLength]; // 新数组
    int number = min(newLength, oldLength); // 需要复制的元素个数
    copy(a, a + number, temp); // 复制
    delete[] a; // 删除旧数组
    a = temp;
}

// arrayList 的类定义
template <class T>
class arrayList : public linearList<T> {
public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>&);
    ~arrayList() {
        delete[] element;
        element = nullptr; // 避免悬空指针
    }
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    int capacity() const { return arrayLength; }

protected:
    void checkIndex(int theIndex) const; // 索引若无效则抛出异常
    T* element; // 一维数组
    int arrayLength; // 一维数组的容量
    int listSize; // 元素的个数
};

// arrayList 的构造函数
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

// 检查索引是否有效
template <class T>
void arrayList<T>::checkIndex(int theIndex) const {
    if (theIndex < 0 || theIndex >= listSize) {
        ostringstream s;
        s << "Invalid index: " << theIndex << ". Valid range: [0, " << listSize - 1 << "].";
        throw illegalIndex(s.str());
    }
}

// 返回索引为 theIndex 的元素
template <class T>
T& arrayList<T>::get(int theIndex) const {
    checkIndex(theIndex);
    return element[theIndex];
}

// 返回 theElement 第一次出现时的索引，不存在则返回 -1
template <class T>
int arrayList<T>::indexOf(const T& theElement) const {
    int theIndex = (int)(find(element, element + listSize, theElement) - element);
    if (theIndex == listSize)
        return -1;
    else
        return theIndex;
}

// 删除索引为 theIndex 的元素
template <class T>
void arrayList<T>::erase(int theIndex) {
    checkIndex(theIndex);
    copy(element + theIndex + 1, element + listSize, element + theIndex);
    element[--listSize].~T();
}

// 在索引 theIndex 的位置上插入一个元素
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
