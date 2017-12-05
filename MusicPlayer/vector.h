#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <algorithm> //for sort

/**
 * @brief Vector --- extension of std::vector for intuitive element traversal, insertion and removal.
 * @author      Scott Wolfskill
 * @created     11/28/2017
 * @last_edit   12/04/2017
 */
template<class T>
class Vector : public std::vector<T>
{
public:
    //Methods:
    Vector(std::size_t blankElements = 0) : std::vector<T>(blankElements) {}
    //size_type size() const : size() {}
    //void push_back(const T &element) : push_back(element) {}

    bool contains(const T &element) const;

    /**
     * @brief Return index of first occurrence of (toFind).
     * @param element Element to find.
     * @return 0-based index of Element in vector, or -1 if not found.
     */
    int find(const T &toFind) const;

    /**
     * @brief Insert element before a specified index. Use push_back to insert at end.
     * @param index 0-based index of position to insert before.
     * @param toAdd Element to add.
     * @return false if invalid index.
     */
    bool insertBefore(int index, const T &toAdd);

    /**
     * @brief Insert an element into its properly sorted place in the vector.
     * @param toAdd Element to insert.
     */
    //void insertSorted(const T &toAdd);

    /**
     * @brief Remove element at (index) from the vector.
     * @param index 0-based index of element to remove.
     * @return false if invalid index.
     */
    bool removeAt(int index);

    //T operator [](size_type index) { return (*this)[index]; }

    /**
     * @brief Sort the vector using std::sort and operator<, which must be defined for class T.
     */
    void sort();

private:
    //Vars:
    //bool sorted; //true if this vector is in a sorted state.

    //Methods:
    /**
     * @brief getIteratorAt index in vector.
     * @param index 0-based index.
     * @return Iterator.
     */
    typename std::vector<T>::const_iterator getIteratorAt(int index) const;

    /**
     * @brief Return an iterator to where in vector (element) is located, if exists.
     * @param song Ptr. of Song to find.
     * @param location Ptr to index that will be assigned when found. Usage optional.
     * @param compare Comparison class used to determine if we've found (toFind).
     *                Default compares elements directly with ==.
     * @return Iterator of location that must be free'd by caller.
     */
     typename std::vector<T>::const_iterator * find_(const T &element,
                                                     int * const location = nullptr/*,
                                                     const Compare * const compare = nullptr*/) const;
};

#define constIterator typename std::vector<T>::const_iterator

template<class T>
bool Vector<T>::contains(const T &element) const
{
    constIterator * location = find_(element);
    if(location != nullptr) {
        free(location);
        return true;
    }
    return false;
}

template<class T>
int Vector<T>::find(const T &toFind/*, const Compare * const compare*/) const {
    int location = -1;
    delete find_(toFind, &location/*, compare*/); //free iterator; don't need
    return location;
}

template<class T>
bool Vector<T>::insertBefore(int index, const T &toAdd)
{
    std::size_t index_ = (std::size_t) index;
    if(index < 0 || index_ >= this->size()) {
        return false;
    }
    constIterator iterAt = getIteratorAt(index);
    this->insert(iterAt, toAdd); //inserts before iterAt
    return true;
}

template<class T>
bool Vector<T>::removeAt(int index)
{
    std::size_t index_ = (std::size_t) index;
    if(index < 0 || index_ >= this->size()) {
        return false;
    }
    if(index_ == this->size() - 1) { //remove end
        this->pop_back();
    } else {
        constIterator iterAt = getIteratorAt(index);
        this->erase(iterAt);
    }
    return true;
}

template<class T>
void Vector<T>::sort() {
    std::sort(this->begin(), this->end);
}

template<class T>
constIterator Vector<T>::getIteratorAt(int index) const
{
    constIterator iterator = this->begin();
    int count = 0;
    while(count < index) {
        iterator++;
    }
    return iterator;
}

template<class T>
constIterator * Vector<T>::find_(const T &element, int * const location/*, const Compare * const compare*/) const
{
    //Search through all elements in until found.
    constIterator iterator = this->begin();
    int index = 0;
    while(iterator != this->end()) {
        if(*iterator == element) { //found element
            if(location != nullptr) {
                *location = index;
            }
            //constIterator * ret = (constIterator *) malloc(sizeof(constIterator));
            constIterator * ret = new constIterator();
            *ret = iterator;
            return ret;
        }
        index++;
        iterator++;
    }
    return nullptr;
}

#endif // VECTOR_H
