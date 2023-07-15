#include "tree.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void checkSize()
{
    cout << "size: ";
    Tree<int> tree({1, 2, 3, 3, 1, 1, 2, 2, 2, 7, 5});
    Tree<int> emptyTree;
    Tree<int> singleValTree({0});
    if (tree.size() == 5 && emptyTree.size() == 0 && singleValTree.size() == 1)
        cout << "OK";
    else
        cout << "error";
    cout << endl;
}

void checkContains()
{
    cout << "contains: ";
    Tree<int> tree({5, 1, 9, 7, 2, 2, 0, 9, 9}), emptyTree, singleValTree({10});
    if (
        tree.contains(5) && tree.contains(9) && tree.contains(2) && !tree.contains(8) &&
        !emptyTree.contains(1) && singleValTree.contains(10) && !singleValTree.contains(9)
    )
        cout << "OK";
    else
        cout << "error";
    cout << endl;
}

void addToTree(Tree<int>& tree, const vector<int>& v)
{
    for (int elem: v)
        tree.add(elem);
}

bool equal(const vector<int>& a, const vector<int>& b)
{
    unsigned n = a.size();
    if (n != b.size())
        return false;
    for (unsigned i = 0; i < n; i++)
        if (a[i] != b[i])
            return false;
    return true;
}

void checkAdd()
{
    cout << "add: ";
    Tree<int> tree;
    vector<int> values = {4, 5, 2, 1, 3, 0, 10, 7, 6, 9, 12};
    addToTree(tree, values);
    sort(values.begin(), values.end());
    if (equal((vector<int>)tree, values))
        cout << "OK";
    else
        cout << "error";
    cout << endl;
}

void checkValuePop()
{
    cout << "value pop: ";
    Tree<int> treeA({1, 5, 2, 2, 3, 1});
    treeA.pop(1);
    treeA.pop(2);
    treeA.pop(3);
    treeA.pop(5);
    Tree<int> treeB({2});
    treeB.add(20);
    treeB.pop(2);
    treeB.pop(100);
    Tree<int> treeC({1, 2, 3, -1, -2, -3, 0});
    treeC.pop(1);
    treeC.pop(0);
    treeC.pop(-2);
    Tree<int> treeD({3, 6, 1, 4, 5, 7});
    treeD.pop(3);
    treeD.pop(6);
    if (
        equal((vector<int>)treeA, {}) &&
        equal((vector<int>)treeB, {20}) &&
        equal((vector<int>)treeC, {-3, -1, 2, 3}) &&
        equal((vector<int>)treeD, {1, 4, 5, 7})
    )
        cout << "OK";
    else
        cout << "error";
    cout << endl;
}

void checkIndexPop()
{
    cout << "index pop: ";
    Tree<int> tree({1, 5, 2, 4, 3, 10, -40, -30, -50, -25, 100, 102, 97, 90, 95, 91});
    vector<int> v = (vector<int>)tree;
    tree.popIndex(0);
    tree.popIndex(4);
    tree.popIndex(7);
    tree.popIndex(2);
    tree.popIndex(0);
    tree.popIndex(3);
    v.erase(v.begin() + 0);
    v.erase(v.begin() + 4);
    v.erase(v.begin() + 7);
    v.erase(v.begin() + 2);
    v.erase(v.begin() + 0);
    v.erase(v.begin() + 3);
    if (equal((vector<int>)tree, v))
        cout << "OK";
    else
        cout << "error";
    cout << endl;
}

void checkIntersection()
{
    cout << "intersection: ";
    Tree<int> a1({1, 5, 2, 4, 3}), b1({1, 2, 4, 9}), c1({1, 2, 4});
    Tree<int> r1 = a1 & b1;
    Tree<int> a2, b2({5, 1, 4, 2, 7}), c2;
    Tree<int> r2 = a2 & b2;
    Tree<int> a3({1, 4}), b3({5, 1, 4, 2, 7}), c3({1, 4});
    Tree<int> r3 = a3 & b3;
    Tree<int> a4({5}), b4({5}), c4({5});
    Tree<int> r4 = a4 & b4;
    if (
        equal((vector<int>)c1, (vector<int>)r1) &&
        equal((vector<int>)c2, (vector<int>)r2) &&
        equal((vector<int>)c3, (vector<int>)r3) &&
        equal((vector<int>)c4, (vector<int>)r4)
    )
        cout << "OK";
    else
        cout << "error";
    cout << endl;
}

void checkMerge()
{
    cout << "merge: ";
    Tree<int> a1({1, 3, 2, 10}), b1({1, 10, 2, 3}), c1({3, 10, 1, 2});
    Tree<int> r1 = a1 + b1;
    Tree<int> a2({1, 5, -6, -4, -10}), b2({1, -10, 8, 4, 6, 11, 5}), \
            c2({1, 5, -6, -4, -10, 1, 8, 4, 6, 11});
    Tree<int> r2 = a2 + b2;
    Tree<int> a3({1, 7, 2, 23, 17}), b3({6, 2, 8, 4, 10}), \
            c3({1, 7, 2, 23, 17, 6, 2, 8, 4, 10});
    Tree<int> r3 = a3 + b3;
    if (
        equal((vector<int>)c1, (vector<int>)r1) &&
        equal((vector<int>)c2, (vector<int>)r2) &&
        equal((vector<int>)c3, (vector<int>)r3)
    )
        cout << "OK";
    else
        cout << "error";
    cout << endl;
}

void checkSymmetricDifference()
{
    cout << "symmetric difference: ";
    Tree<int> a1({8, 10, 1, 3, 2, 0}), b1({6, 4, 5, 8, 10}), \
            c1({5, 6, 2, 1, 0, 3, 4});
    Tree<int> r1 = a1 ^ b1;
    Tree<int> a2({1, 3, 2}), b2({6, 5, 4}), c2({4, 2, 1, 3, 6, 5});
    Tree<int> r2 = a2 ^ b2;
    if (
        equal((vector<int>)c1, (vector<int>)r1) &&
        equal((vector<int>)c2, (vector<int>)r2)
    )
        cout << "OK";
    else
        cout << "error";
    cout << endl;
}

void checkDifference()
{
    cout << "difference: ";
    Tree<int> a1({4, 2, 3, 1, 6, 5, 7}), b1({2, 6, 1}), \
            c1({4, 3, 5, 7});
    Tree<int> r1 = a1 - b1;
    Tree<int> a2({4, 2, 3, 1, 6, 5, 7}), b2({20, 60, 10}), \
            c2({4, 2, 3, 1, 6, 5, 7});
    Tree<int> r2 = a2 - b2;
    Tree<int> a3({3, 4, 2}), b3({4, 2, 3, 1, 6, 5, 7}), c3;
    Tree<int> r3 = a3 - b3;
    Tree<int> a4({3, 4, 2}), b4, c4({3, 4, 2});
    Tree<int> r4 = a4 - b4;
    if (
        equal((vector<int>)c1, (vector<int>)r1) &&
        equal((vector<int>)c1, (vector<int>)r2) &&
        equal((vector<int>)c1, (vector<int>)r3) &&
        equal((vector<int>)c1, (vector<int>)r4)
    )
        cout << "OK";
    else
        cout << "error";
    cout << endl;
}

void runTests()
{
    checkSize();
    checkContains();
    checkAdd();
    checkValuePop();
    checkIndexPop();
    checkIntersection();
    checkMerge();
    checkDifference();
    checkSymmetricDifference();
}
