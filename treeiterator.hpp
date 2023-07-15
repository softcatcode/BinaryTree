#include "treeiterator.h"
#include "tree.h"
#include "nulliteratorexception.h"
#include "indexoutofrangeexception.h"

template <Comparable T>
TreeIterator<T>::TreeIterator() noexcept
    : BidirectionalTreeIterator<T> () {}

template <Comparable T>
TreeIterator<T>::TreeIterator(const Tree<T>& tree)
    : BidirectionalTreeIterator<T> (tree) {}

template<Comparable T>
void TreeIterator<T>::operator = (const TreeIterator<T>& iter)
{
    this->rootPtr.reset();
    this->rootPtr = iter.rootPtr;
    this->path = iter.path;
}

template <Comparable T>
TreeIterator<T>::TreeIterator(const shared_ptr< Node<T> >& rootPtr) noexcept
{
    this->rootPtr = rootPtr;
}

template <Comparable T>
inline void TreeIterator<T>::moveToEnd()
{
    clearStack();
}

template <Comparable T>
void TreeIterator<T>::clearStack()
{
    while (!this->path.empty())
        this->path.pop();
}

template <Comparable T>
void TreeIterator<T>::moveToRoot()
{
    if (!*this)
        throw NullIteratorException(
            "null iterator exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "no tree associated with the iterator"
        );
    clearStack();
    this->path.push(this->rootPtr);
}

template <Comparable T>
void TreeIterator<T>::moveToBegin()
{
    if (!*this) {
        moveToEnd();
        return;
    }
    clearStack();
    this->path.push(this->rootPtr);
    auto ptr = this->toShared();
    while (ptr->getLeft()) {
        this->goLeft();
        ptr = ptr->getLeft();
    }
}

template <Comparable T>
void TreeIterator<T>::moveToIndex(unsigned index)
{
    unsigned count = sizeOf(this->rootPtr.lock());
    if (index < count)
    {
        moveToRoot();
        unsigned curInd = sizeOf(this->toShared()->getLeft());
        while (curInd != index)
        {
            if (curInd > index) {
                this->goLeft();
                curInd -= sizeOf(this->toShared()->getRight()) + 1;
            } else {
                this->goRight();
                curInd += sizeOf(this->toShared()->getLeft()) + 1;
            }
        }
    }
    else if (index == count)
        moveToEnd();
    else
        throw IndexOutOfRangeException(
            "index out of range exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "index is too big"
        );
}

template <Comparable T>
long long TreeIterator<T>::operator - (const TreeIterator<T>& iter) const
{
    long long l = this->index();
    long long r = iter.index();
    return r - l;
}

template <Comparable T>
TreeIterator<T> TreeIterator<T>::operator + (unsigned delta) const
{
    unsigned curInd = this->index();
    TreeIterator<T> iter(*this);
    iter.moveToIndex(curInd + delta);
    return iter;
}

template <Comparable T>
void TreeIterator<T>::operator -= (long long delta)
{
    unsigned curInd = this->index();
    int newIndex = (long long)curInd - delta;
    if (newIndex < 0 || (unsigned)newIndex > sizeOf(this->rootPtr.lock()))
        throw IndexOutOfRangeException(
            "index out of range exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "index is too big or result index is less zero"
        );
    this->moveToIndex((unsigned)newIndex);
}

template <Comparable T>
void TreeIterator<T>::operator += (long long delta)
{
    unsigned curInd = this->index();
    int newIndex = (long long)curInd + delta;
    if (newIndex < 0 || (unsigned)newIndex > sizeOf(this->rootPtr.lock()))
        throw IndexOutOfRangeException(
            "index out of range exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "index is too big or result index is less zero"
        );
    this->moveToIndex((unsigned)newIndex);
}

template<Comparable T>
T& TreeIterator<T>::operator [] (int index)
{
    unsigned curInd = this->index();
    this->moveToIndex(curInd + index);
    return this->toShared()->getValue();
}
