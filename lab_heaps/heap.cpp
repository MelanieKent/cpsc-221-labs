/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

#include <cmath>

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return 2*(currentIdx)+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return 2*(currentIdx)+2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    if (currentIdx%2 == 1) {
        return currentIdx/2;
    }
    return currentIdx/2-1;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    if (rightChild(currentIdx) >= _elems.size()) {
        return leftChild(currentIdx);
    }
    if (higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)])) {
        return leftChild(currentIdx);
    }
    return rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if (!hasAChild(currentIdx)) {
        return;
    }
    size_t priorityChildIndex = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[priorityChildIndex], _elems[currentIdx])) {
        std::swap(_elems[currentIdx], _elems[priorityChildIndex]);
        heapifyDown(priorityChildIndex);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
   // nothing
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{   _elems = elems;
    for (size_t i = parent(elems.size()-1); i>=1; i--) {
        heapifyDown(i);
    }
    heapifyDown(0);
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    T temp = _elems[0];
    _elems[0] = _elems[_elems.size()-1];
    _elems.pop_back();
    heapifyDown(0);

    return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    return _elems[0];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    return _elems.empty();
}
