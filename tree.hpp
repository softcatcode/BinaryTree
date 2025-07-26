#include "illegalfuncuseexception.h"
#include "nulliteratorexception.h"
#include "nullpointerexception.h"
#include "tree.h"
#include <algorithm>
#include <concepts>
#include <iostream>
#include <fstream>

template <Comparable T>
Tree<T>::Tree() noexcept
{
    root.reset();
}

template <Comparable T>
template <Container Cont>
requires Convertible<typename Cont::value_type, T> && Assignable<typename Cont::value_type, T>
Tree<T>::Tree(const Cont& container)
{
    vector<T> v;
    for (auto elem: container)
        v.push_back(elem);
    root.reset();
    random_shuffle(v.begin(), v.end());
    for (auto elem: v)
        add(elem);
}

template <Comparable T>
template <input_iterator Iter>
requires Convertible<typename Iter::value_type, T>
Tree<T>::Tree(const Iter& l, const Iter& r)
{
    vector<T> v;
    for (auto iter = l; iter != r; ++iter)
        v.push_back(*iter);
    root.reset();
    random_shuffle(v.begin(), v.end());
    for (auto elem: v)
        add(elem);
}

template <Comparable T>
Tree<T>::Tree(const std::initializer_list<T>& initList)
{
    vector<T> v;
    for (auto elem: initList)
        v.push_back(elem);
    root.reset();
    random_shuffle(v.begin(), v.end());
    for (auto elem: v)
        add(elem);
}

template <Comparable T>
void Tree<T>::merge(const Tree<T>& tree)
{
    vector<T> v;
    for (auto elem: tree)
        v.push_back(elem);
    random_shuffle(v.begin(), v.end());
    for (auto elem: v)
        add(elem);
}

template <Comparable T>
void Tree<T>::erase(const Tree<T>& tree)
{
    for (T elem: tree)
        if (contains(elem))
            pop(elem);
}

template <Comparable T>
Tree<T>::Tree(const Tree<T>& tree)
{
    root.reset();
    vector<T> v = (vector<T>)tree;
    root.reset();
    random_shuffle(v.begin(), v.end());
    for (auto elem: v)
        add(elem);
}

template <Comparable T>
Tree<T>::Tree(Tree<T>&& tree) noexcept
{
    root = tree.root;
    tree.root.reset();
}

template <Comparable T>
Tree<T>::~Tree()
{
    clear();
}

template <Comparable T>
unsigned Tree<T>::movePtrTo(shared_ptr< Node<T> >& ptr, const T& value) const
{
    if (!ptr)
        throw NullPointerException(
            "Null pointer exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot move null pointer"
        );
    bool goLeftCond, goRightCond;
    unsigned index = sizeOf(ptr->getLeft());
    do {
        goLeftCond = value < ptr->getValue() && ptr->getLeft();
        goRightCond = value > ptr->getValue() && ptr->getRight();
        if (goRightCond) {
            ptr = ptr->getRight();
            index += sizeOf(ptr->getLeft()) + 1;
        }
        else if (goLeftCond) {
            ptr = ptr->getLeft();
            index -= sizeOf(ptr->getRight()) + 1;
        }
    } while (goLeftCond || goRightCond);
    return index;
}

template <Comparable T>
void Tree<T>::updateSize(TreeIterator<T> iter)
{
    if (iter.emptyStack())
        throw NullIteratorException(
            "Null iterator exception",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "cannot update size by iterator that does not target to a node"
        );
    do {
        updateNodeSize<T>(*iter.toShared());
        iter.goBack();
    } while (!iter.emptyStack());
}

template <Comparable T>
unsigned Tree<T>::indexOf(const T& value) const
{
    if (!root)
        return 0;
    shared_ptr< Node<T> > ptr = root;
    unsigned index = movePtrTo(ptr, value);
    return ptr->getValue() == value ? index : sizeOf(root);
}

template <Comparable T>
TreeIterator<T> Tree<T>::find(const T& value) const
{
    unsigned index = indexOf(value);
    TreeIterator<T> iter(root);
    iter.moveToIndex(index);
    return iter;
}

template <Comparable T>
void swapValues(const TreeIterator<T>& a, const TreeIterator<T>& b)
{
    auto ptrA = a.toShared();
    auto ptrB = b.toShared();
    auto valueA = ptrA->getValue();
    auto valueB = ptrB->getValue();
    ptrA->setValue(valueB);
    ptrB->setValue(valueA);
}

template <Comparable T>
void Tree<T>::popBothLinkNode(TreeIterator<T>& iter)
{
    auto ptr = iter.toShared();
    if (!ptr || !ptr->getLeft() || !ptr->getRight())
        throw IllegalFuncUseException(
            "this function call is prohibited in this case",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "the node does not have 2 children"
        );
    TreeIterator<T> popIter(iter);
    popIter.moveToIndex(iter.index() + 1);
    swapValues(iter, popIter);
    auto prevPtr = popIter.toShared();
    popIter.goBack();
    ptr = popIter.toShared();
    if (prevPtr == ptr->getLeft())
        ptr->setLeft(ptr->getLeft()->getRight());
    else
        ptr->setRight(ptr->getRight()->getRight());
    updateSize(popIter);
    iter.goBack();
}

template <Comparable T>
void Tree<T>::popNotBothLinkNode(TreeIterator<T>& iter)
{
    auto ptr = iter.toShared();
    if (!ptr || (ptr->getLeft() && ptr->getRight()))
        throw IllegalFuncUseException(
            "this function call is prohibited in this case",
            __FUNCTION__,
            __DATE__,
            __TIME__,
            __LINE__,
            "the node has 2 children"
        );
    if (root == ptr)
    {
        if (root->getLeft())
            root = root->getLeft();
        else
            root = root->getRight();
    }
    else
    {
        auto next = ptr->getLeft() ? ptr->getLeft() : ptr->getRight();
        auto prevPtr = ptr;
        iter.goBack();
        ptr = iter.toShared();
        if (ptr->getLeft() == prevPtr)
            ptr->setLeft(next);
        else if (ptr->getRight() == prevPtr)
            ptr->setRight(next);
        updateSize(iter);
    }
}

template <Comparable T>
void Tree<T>::pop(TreeIterator<T>& iter)
{
    if (iter.emptyStack())
        return;
    auto ptr = iter.toShared();
    if (ptr->getLeft() && ptr->getRight())
        popBothLinkNode(iter);
    else
        popNotBothLinkNode(iter);
}

template <Comparable T>
void Tree<T>::popIndex(size_type index)
{
    TreeIterator<T> iter(root);
    iter.moveToIndex(index);
    pop(iter);
}

template <Comparable T>
void Tree<T>::pop(const T& value)
{
    size_type index = indexOf(value);
    popIndex(index);
}

template <Comparable T>
bool Tree<T>::contains(const T& value) const
{
    return find(value) != end();
}

template <Comparable T>
void Tree<T>::add(const T& value)
{
    shared_ptr< Node<T> > ptr = root;
    if (!ptr)
        root = Node<T>::create(value);
    else
    {
        shared_ptr< Node<T> > ptr = root;
        unsigned index = movePtrTo(ptr, value);
        TreeIterator<T> iter(root);
        iter.moveToIndex(index);
        if (value < ptr->getValue())
            ptr->setLeft(Node<T>::create(value));
        else if (value > ptr->getValue())
            ptr->setRight(Node<T>::create(value));
        if (value != ptr->getValue())
            updateSize(iter);
    }
}

template <Comparable T>
Tree<T> Tree<T>::clone() const
{
    Tree<T> newTree = *this;
    return newTree;
}

template <Comparable T>
TreeIterator<T> Tree<T>::begin() const noexcept
{
    TreeIterator<T> iter(this->root);
    iter.moveToBegin();
    return iter;
}

template <Comparable T>
TreeIterator<T> Tree<T>::end() const noexcept
{
    TreeIterator<T> iter(root);
    return iter;
}

template <Comparable T>
Tree<T>::operator vector<T>() const
{
    vector<T> v;
    for (T elem: *this)
        v.push_back(elem);
    return v;
}

template <Comparable T>
Tree<T> Tree<T>::operator + (const Tree<T>& tree) const
{
    Tree<T> resultTree(*this);
    resultTree.merge(tree);
    return resultTree;
}

template <Comparable T>
Tree<T> Tree<T>::operator + (const T& value) const
{
    Tree<T> resultTree(*this);
    resultTree.add(value);
    return resultTree;
}

template <Comparable T>
Tree<T> Tree<T>::operator & (const Tree<T>& tree) const
{
    vector<T> v;
    for (T elem: tree)
        if (contains(elem))
            v.push_back(elem);
    random_shuffle(v.begin(), v.end());
    Tree<T> resultTree(v);
    return resultTree;
}

template <Comparable T>
Tree<T> Tree<T>::operator & (const T& value) const
{
    Tree<T> resultTree;
    if (contains(value))
        resultTree.add(value);
    return resultTree;
}

template <Comparable T>
Tree<T>& Tree<T>::operator &= (const T& value)
{
    bool hadValue = contains(value);
    clear();
    if (hadValue)
        add(value);
    return *this;
}

template <Comparable T>
Tree<T> Tree<T>::operator - (const Tree<T>& tree) const
{
    Tree<T> resultTree(*this);
    resultTree.erase(tree);
    return resultTree;
}

template <Comparable T>
Tree<T> Tree<T>::operator - (const T& value) const
{
    Tree<T> resultTree(*this);
    resultTree.pop(value);
    return resultTree;
}

template <Comparable T>
Tree<T> Tree<T>::operator ^ (const Tree<T>& tree) const
{
    Tree<T> resultTree = *this + tree;
    resultTree -= *this & tree;
    return resultTree;
}

template <Comparable T>
Tree<T> Tree<T>::operator ^ (const T& value) const
{
    Tree<T> resultTree(*this);
    if (resultTree.contains(value))
        resultTree.pop(value);
    else
        resultTree.add(value);
    return resultTree;
}

template <Comparable T>
Tree<T>& Tree<T>::operator ^= (const T& value)
{
    if (contains(value))
        pop(value);
    else
        add(value);
    return *this;
}

template <Comparable T>
Tree<T>& Tree<T>::operator += (const Tree<T>& tree)
{
    *this = *this + tree;
    return *this;
}

template <Comparable T>
Tree<T>& Tree<T>::operator &= (const Tree<T>& tree)
{
    *this = *this & tree;
    return *this;
}

template <Comparable T>
Tree<T>& Tree<T>::operator ^= (const Tree<T>& tree)
{
    *this = *this ^ tree;
    return *this;
}

template <Comparable T>
Tree<T>& Tree<T>::operator -= (const Tree<T>& tree)
{
    *this = *this - tree;
    return *this;
}

template <Comparable T>
bool Tree<T>::operator == (const Tree<T>& tree) const
{
    Tree<T> tmpTree = *this ^ tree;
    return tmpTree.empty();
}

template <Comparable T>
void Tree<T>::clear()
{
    while (root)
        pop(root->getValue());
}

template <Comparable T>
Tree<T>& Tree<T>::operator = (const Tree<T>& tree)
{
    vector<T> v = (vector<int>)tree;
    random_shuffle(v.begin(), v.end());
    clear();
    for (T elem: v)
        add(elem);
    return *this;
}

template <Comparable T>
ostream& operator << (ostream& out, const Tree<T>& tree)
{
    for (T elem: tree)
        out << elem << ' ';
    out << endl;
    return out;
}
