#ifndef BIDIRECTIONALTREEITERATOR_H
#define BIDIRECTIONALTREEITERATOR_H

#include "forwardtreeiterator.hpp"

template <Comparable T>
class Tree;

template <Comparable T>
class BidirectionalTreeIterator: public ForwardTreeIterator<T>
{
public:
    using iter_concept = bidirectional_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = unsigned;

    BidirectionalTreeIterator() noexcept;
    BidirectionalTreeIterator(const Tree<T>& tree);
    explicit BidirectionalTreeIterator(const BidirectionalTreeIterator<T>& iter);

    unsigned index() const;

    BidirectionalTreeIterator<T>& operator -- ();

    shared_ptr<T> operator -> () const;

    bool operator <= (const BidirectionalTreeIterator<T>& iter) const;
    bool operator < (const BidirectionalTreeIterator<T>& iter) const;
    bool operator >= (const BidirectionalTreeIterator<T>& iter) const;
    bool operator > (const BidirectionalTreeIterator<T>& iter) const;
    bool operator == (const BidirectionalTreeIterator<T>& iter) const;
};

#endif // BIDIRECTIONALTREEITERATOR_H
