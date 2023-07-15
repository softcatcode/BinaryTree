#ifndef BASEITERATOR_H
#define BASEITERATOR_H

#include <memory>
#include <stack>
#include "node.h"
#include "comparable.h"
using namespace std;

template <Comparable T>
class BaseTreeIterator
{
public:
    BaseTreeIterator() noexcept {};
    virtual ~BaseTreeIterator() noexcept {};

    const Node<T>& getNode() const { return *path.top().lock(); };

    virtual shared_ptr< Node<T> > toShared() const = 0;

protected:
    stack< weak_ptr<Node<T>> > path;
};

#endif // BASEITERATOR_H
