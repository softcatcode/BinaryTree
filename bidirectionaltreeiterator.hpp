#include "bidirectionaltreeiterator.h"
#include "nulliteratorexception.h"
#include "tree.h"

template <Comparable T>
BidirectionalTreeIterator<T>::BidirectionalTreeIterator() noexcept
    : ForwardTreeIterator<T>() {}

template <Comparable T>
BidirectionalTreeIterator<T>::BidirectionalTreeIterator(const Tree<T>& tree)
    : ForwardTreeIterator<T>(tree) {}

template <Comparable T>
BidirectionalTreeIterator<T>::BidirectionalTreeIterator(const BidirectionalTreeIterator<T>& iter)
    : ForwardTreeIterator<T>(iter) {}

template <Comparable T>
shared_ptr<T> BidirectionalTreeIterator<T>::operator -> () const
{
    auto ptr = this->toShared();
    if (!ptr)
        throw NullPointerException(
            "null pointer exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "pointer is derived from end or null iterator"
        );
    return make_shared<T>(ptr->getValue());
}

template <Comparable T>
BidirectionalTreeIterator<T>& BidirectionalTreeIterator<T>::operator -- ()
{
    auto ptr = this->toShared();
    if (!ptr)
        throw NullPointerException(
            "null pointer exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "pointer is derived from end or null iterator"
        );
    if (ptr->getLeft())
        this->goLeft();
    else
    {
        T prevValue;
        do {
            prevValue = *this;
            this->goBack();
            ptr = this->toShared();
        }
        while (ptr && ptr->getValue() > prevValue);
    }
    return *this;
}

template <Comparable T>
bool BidirectionalTreeIterator<T>::operator == (const BidirectionalTreeIterator<T>& iter) const
{
    if (!*this)
        return !iter;
    if (this->rootPtr.lock() != iter.rootPtr.lock())
        throw IllegalFuncUseException(
            "prohibited to use comparison",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "iterators are associated with different trees"
        );
    if (this->emptyStack())
        return iter.emptyStack();
    return this->toShared() == iter.toShared();
}

template <Comparable T>
unsigned BidirectionalTreeIterator<T>::index() const
{
    if (!*this)
        throw NullIteratorException(
            "null iterator exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot determine index by null iterator"
        );
    if (this->emptyStack())
        return sizeOf(this->rootPtr.lock());
    auto pathCopy = this->path;
    shared_ptr< Node<T> > ptr = pathCopy.top().lock();
    unsigned result = sizeOf(ptr->getLeft());
    T prevValue = ptr->getValue();
    pathCopy.pop();
    while (!pathCopy.empty())
    {
        ptr = pathCopy.top().lock();
        if (ptr->getValue() < prevValue)
            result += sizeOf(ptr->getLeft()) + 1;
        prevValue = ptr->getValue();
        pathCopy.pop();
    }
    return result;
}

template <Comparable T>
bool BidirectionalTreeIterator<T>::operator < (const BidirectionalTreeIterator<T>& iter) const
{
    if (!*this)
        throw NullIteratorException(
            "null iterator exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot compare if left operand is null"
        );
    if (!iter)
        throw NullIteratorException(
            "null iterator exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot compare if right operand is null"
        );
    if (this->rootPtr != iter.rootPtr)
        throw IllegalFuncUseException(
            "prohibited to use comparison",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "iterators are associated with different trees"
        );
    return this->index() < ((BidirectionalTreeIterator)iter).index();
}

template <Comparable T>
bool BidirectionalTreeIterator<T>::operator <= (const BidirectionalTreeIterator<T>& iter) const
{
    return *this == iter || *this < iter;
}

template <Comparable T>
bool BidirectionalTreeIterator<T>::operator > (const BidirectionalTreeIterator<T>& iter) const
{
    return !(*this <= iter);
}

template <Comparable T>
bool BidirectionalTreeIterator<T>::operator >= (const BidirectionalTreeIterator<T>& iter) const
{
    return *this == iter || *this > iter;
}
