#include "illegalfuncuseexception.h"
#include "nulliteratorexception.h"
#include "forwardtreeiterator.h"
#include "tree.h"

template <Comparable T>
ForwardTreeIterator<T>::ForwardTreeIterator() noexcept
{
    this->rootPtr.reset();
}

template <Comparable T>
ForwardTreeIterator<T>::~ForwardTreeIterator() noexcept
{
    reset();
}

template <Comparable T>
ForwardTreeIterator<T>::ForwardTreeIterator(const Tree<T>& tree)
{
    this->rootPtr = tree.root;
    if (!tree.empty())
        this->path.push(tree.root);
}

template <Comparable T>
ForwardTreeIterator<T>::ForwardTreeIterator(const ForwardTreeIterator<T>& iter)
{
    this->rootPtr.reset();
    this->rootPtr = iter.rootPtr;
    this->path = iter.path;
}

template <Comparable T>
ForwardTreeIterator<T>::operator bool() const
{
    return this->rootPtr.lock();
}

template <Comparable T>
bool ForwardTreeIterator<T>::operator ! () const
{
    return !this->rootPtr.lock();
}

template <Comparable T>
ForwardTreeIterator<T>& ForwardTreeIterator<T>::operator ++ ()
{
    auto ptr = this->toShared();
    if (!ptr)
        throw NullIteratorException(
            "null iterator exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot increment null iterator"
        );
    if (ptr->getRight())
    {
        goRight();
        ptr = this->toShared();
        while (ptr->getLeft()) {
            ptr = ptr->getLeft();
            goLeft();
        }
    }
    else
    {
        T prevValue;
        do {
            prevValue = this->toShared()->getValue();
            goBack();
            ptr = this->toShared();
        }
        while (ptr && ptr->getValue() < prevValue);
    }
    return *this;
}

template <Comparable T>
const T& ForwardTreeIterator<T>::operator * () const
{
    if (!*this || emptyStack())
        throw NullIteratorException(
            "null iterator exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot dereference null or end iterator"
        );
    return this->path.top().lock()->getValue();
}

template <Comparable T>
bool ForwardTreeIterator<T>::operator != (const ForwardTreeIterator<T>& iter) const
{
    if (!*this)
        return iter;
    if (this->rootPtr != iter.rootPtr)
        throw IllegalFuncUseException(
            "prohibited to use comparison",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "iterators are associated with different trees"
        );
    if (emptyStack())
        return !iter.emptyStack();
    return this->toShared() != iter.toShared();
}

template <Comparable T>
void ForwardTreeIterator<T>::goBack()
{
    if (!*this)
        throw IllegalFuncUseException(
            "prohibited to use the function",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot invoke go back function from null iterator"
        );
    if (emptyStack()) {
        this->path.push(this->rootPtr);
        while (this->toShared()->getRight())
            goRight();
    } else
        this->path.pop();
}

template <Comparable T>
void ForwardTreeIterator<T>::goRight()
{
    if (!this->rootPtr.lock())
        throw NullIteratorException(
            "null iterator exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot move null iterator"
        );
    auto ptr = this->toShared();
    if (!ptr->getRight())
        throw IllegalFuncUseException(
            "prohibited to use the function",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot go to unexisting node"
        );
    this->path.push(ptr->getRight());
}

template <Comparable T>
void ForwardTreeIterator<T>::goLeft()
{
    if (!this->rootPtr.lock())
        throw NullIteratorException(
            "null iterator exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot move null iterator"
        );
    auto ptr = this->toShared();
    if (!ptr->getLeft())
        throw IllegalFuncUseException(
            "prohibited to use the function",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot go to unexisting node"
        );
    this->path.push(ptr->getLeft());
}

template <Comparable T>
void ForwardTreeIterator<T>::clear()
{
    while (!this->path.empty())
        this->path.pop();
}

template <Comparable T>
void ForwardTreeIterator<T>::reset()
{
    clear();
    rootPtr.reset();
}
