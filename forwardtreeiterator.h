#ifndef ForwardITERATOR_H
#define ForwardITERATOR_H

#include "basetreeiterator.h"

template <Comparable T>
class Tree;

template <Comparable T>
class ForwardTreeIterator: public BaseTreeIterator<T>
{
public:
    using iter_concept = forward_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = unsigned;

    ForwardTreeIterator() noexcept;
    ForwardTreeIterator(const Tree<T>& tree);
    explicit ForwardTreeIterator(const ForwardTreeIterator<T>& iter);
    ~ForwardTreeIterator() noexcept;

    ForwardTreeIterator<T>& operator ++ ();

    bool operator != (const ForwardTreeIterator<T>& iterator) const;

    const T& operator * () const;

    operator bool() const;

    bool operator ! () const;

    void goLeft();
    void goRight();
    void goBack();

    void clear();
    void reset();

    virtual shared_ptr< Node<T> > toShared() const override
    {
        shared_ptr< Node<T> > ptr;
        ptr.reset();
        if (!this->path.empty())
            ptr = this->path.top().lock();
        return ptr;
    }

    bool emptyStack() const { return this->path.empty(); }

protected:
    weak_ptr< Node<T> > rootPtr;
};

#endif // FORWARDTREEITERATOR_H
