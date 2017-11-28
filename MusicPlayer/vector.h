#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

/**
 * @brief Vector --- extension of std::vector for intuitive element traversal, insertion and removal.
 * @author      Scott Wolfskill
 * @created     11/28/2017
 * @last_edit   11/28/2017
 */
template<class T>
class Vector : std::vector<T>
{
public:
    //Methods:
    Vector(std::size_t capacity) : std::vector<T>(capacity) {}
    bool contains(const T &element) const;
    bool insertAfter(int index, const T &toAdd);
    bool removeAt(int index);

private:
    //Methods:
    /**
     * @brief getIteratorAt index in vector.
     * @param index 0-based index.
     * @param iteratorIndex Init. before calling. Will point to index of result. Usage optional.
     * @return Iterator.
     */
    typename std::vector<T>::const_iterator getIteratorAt(int index, int * const iteratorIndex = nullptr) const;

    /**
     * @brief Return an iterator to where in vector (element) is located, if exists.
     * @param song Ptr. of Song to find.
     * @param location Ptr to index that will be assigned when found. Usage optional.
     * @return Iterator of location that must be free'd by caller.
     */
     typename std::vector<T>::const_iterator * find(const T &element, int * const location = nullptr) const;
};

#endif // VECTOR_H
