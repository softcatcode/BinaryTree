#ifndef ABSTRACTTREE_H
#define ABSTRACTTREE_H

#include "basetreeiterator.h"

class BaseTree
{
public:
    using size_type = unsigned;

    BaseTree() noexcept {};
    virtual ~BaseTree() = default;

    virtual size_type size() const noexcept = 0;

    virtual bool empty() const noexcept = 0;
};

#endif // ABSTRACTTREE_H
