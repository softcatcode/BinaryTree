#ifndef TREE_H
#define TREE_H

#include "node.h"
#include "comparable.h"
#include "container.h"
#include "basetree.h"
#include "treeiterator.hpp"
#include <vector>
#include <algorithm>

template <Comparable T>
class Tree: public BaseTree
{
public:

    using value_type = T;
    using iterator = TreeIterator<T>;
    using const_iterator = TreeIterator<T>;
    using size_type = unsigned;

    Tree() noexcept;

    template <Container Cont>
    requires Convertible<typename Cont::value_type, T> && Assignable<typename Cont::value_type, T>
    Tree(const Cont& container);

    template <input_iterator Iter>
    requires Convertible<typename Iter::value_type, T>
    Tree(const Iter& l, const Iter& r);

    Tree(const std::initializer_list<T>& initList);

    explicit Tree(const Tree<T>& tree);

    Tree(Tree<T>&& tree) noexcept;

    ~Tree();


    iterator find(const T& value) const;
    bool contains(const T& value) const;
    size_type indexOf(const T& value) const;

    void add(const T& value);
    Tree<T>& operator += (const T& value);
    Tree<T> operator + (const T& value) const;

    void pop(iterator& iter);
    void popIndex(size_type index);
    void pop(const T& value);
    Tree<T> operator - (const T& value) const;
    Tree<T>& operator -= (const T& value);

    Tree<T> operator & (const T& value) const;
    Tree<T>& operator &= (const T& value);

    Tree<T> operator ^ (const T& value) const;
    Tree<T>& operator ^= (const T& value);

    void merge(const Tree<T>& tree);
    Tree<T> operator + (const Tree<T>& tree) const;
    Tree<T>& operator += (const Tree<T>& tree);

    void erase(const Tree<T>& tree);
    Tree<T> operator - (const Tree<T>& tree) const;
    Tree<T>& operator -= (const Tree<T>& tree);

    void intersectWith(const Tree<T>& tree) const { *this &= tree; };
    Tree<T> operator & (const Tree<T>& tree) const;
    Tree<T>& operator &= (const Tree<T>& tree);

    void symDifferenceWith(const Tree<T>& tree) { *this ^= tree; };
    Tree<T> operator ^ (const Tree<T>& tree) const;
    Tree<T>& operator ^= (const Tree<T>& tree);

    bool equal(const Tree<T>& tree) const { return *this == tree; };
    bool operator == (const Tree<T>& tree) const;
    Tree<T>& operator = (const Tree<T>& tree);

    void clear();
    Tree<T> clone() const;
    bool empty() const noexcept override { return sizeOf(root) == 0; };
    size_type size() const noexcept override { return sizeOf(root); };
    operator vector<T>() const;

    iterator begin() const noexcept;
    iterator end() const noexcept;
    iterator cbegin() const noexcept { return begin(); };
    iterator cend() const noexcept { return end(); };
    iterator rbegin() const noexcept { return end(); };
    iterator rend() const noexcept { return begin(); };
    iterator crbegin() const noexcept { return cend(); };
    iterator crend() const noexcept { return begin(); };

private:
    shared_ptr< Node<T> > root;

    friend class ForwardTreeIterator<T>;
    friend class BidirectionalTreeIterator<T>;
    friend class TreeIterator<T>;

    void popBothLinkNode(iterator& iter);
    void popNotBothLinkNode(iterator& iter);

    void updateSize(iterator iter);
    unsigned movePtrTo(shared_ptr< Node<T> >& ptr, const T& value) const;
};

template <Comparable T>
ostream& operator << (ostream& out, const Tree<T>& tree);

#endif // TREE_H
