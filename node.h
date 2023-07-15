#ifndef NODE_H
#define NODE_H

#include <memory>
#include "comparable.h"
using namespace std;

template<Comparable Type>
class Node
{
    using next_ptr = shared_ptr< Node<Type> >;
    using size_type = unsigned;

    size_type size;
    Type value;
    next_ptr left, right;

    Node(const Type& value): size(1), value(value)
    {
        left.reset();
        right.reset();
    }

public:
    ~Node() = default;

    /// getters
    Type& getValue() { return value; }
    next_ptr getLeft() { return left; }
    next_ptr getRight() { return right; }
    size_type getSize() { return size; }

    /// setters
    void setValue(const Type& val) { value = val; }
    void setLeft(const next_ptr& ptr)
    {
        left.reset();
        left = ptr;
    }
    void setRight(const next_ptr& ptr)
    {
        right.reset();
        right = ptr;
    }
    void setSize(size_type newSize) { size = newSize; }

    template <typename... Args>
    static shared_ptr<Node> create(Args&&... args);
};

template <typename T>
template<typename... Args>
shared_ptr<Node<T>> Node<T>::create(Args&&... args)
{
    struct EnableConstructor: public Node<T> {
        EnableConstructor(Args&&... args):
            Node<T>(forward<Args>(args)...) {}
    };
    return make_shared<EnableConstructor>(
        EnableConstructor(forward<Args>(args)...)
    );
}

template <typename T>
unsigned sizeOf(const shared_ptr< Node<T> >& node) noexcept
{
    return node ? node->getSize() : 0;
}

template <typename Type>
void updateNodeSize(Node<Type>& node)
{
    node.setSize(sizeOf(node.getLeft()) + 1 + sizeOf(node.getRight()));
}

#endif // NODE_H
