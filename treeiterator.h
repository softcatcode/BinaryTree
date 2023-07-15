#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include <memory>
#include <stack>
#include "bidirectionaltreeiterator.hpp"
#include "node.h"
using namespace std;

template<Comparable Type>
class Tree;

template <Comparable T>
class TreeIterator: public BidirectionalTreeIterator<T>
{

    using iter_concept = random_access_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = long long;

    void clearStack();

public:
    TreeIterator() noexcept;

    TreeIterator(const Tree<T>& tree);

    void operator = (const TreeIterator<T>& iter);
    //explicit TreeIterator(const TreeIterator<T>& iter);

    TreeIterator(const shared_ptr< Node<T> >& rootPtr) noexcept;

    difference_type operator - (const TreeIterator<T>& iter) const;

    TreeIterator<T> operator + (unsigned delta) const;

    void operator -= (difference_type delta);
    void operator += (difference_type delta);

    T& operator [] (int index);

    void moveToIndex(unsigned index);
    void moveToRoot();
    void moveToBegin();
    inline void moveToEnd();
};

#endif // TREEITERATOR_H
