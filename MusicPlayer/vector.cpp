#include "vector.h"

#define constIterator typename std::vector<T>::const_iterator

template<class T>
bool Vector<T>::contains(const T &element) const
{
    constIterator * location = find(element);
    if(location != nullptr) {
        free(location);
        return true;
    }
    return false;
}

template<class T>
bool Vector<T>::insertAfter(int index, const T &toAdd)
{
    std::size_t index_ = (std::size_t) index;
    if(index_ < -1 || index_ >= this->size()) {
        return false;
    }
    if(index_ == this->size() - 1) { //insert at end
        push_back(toAdd);
    } else {
        constIterator iterAt = getIteratorAt(index);
        insert(iterAt, toAdd);
    }
    return true;
}

template<class T>
bool Vector<T>::removeAt(int index)
{
    std::size_t index_ = (std::size_t) index;
    if(index_ < 0 || index_ >= this->size()) {
        return false;
    }
    if(index_ == this->size() - 1) { //remove end
        this->pop_back();
    } else {
        constIterator iterAt = getIteratorAt(index);
        erase(iterAt);
    }
    return true;
}

template<class T>
constIterator Vector<T>::getIteratorAt(int index, int * const iteratorIndex) const
{
    constIterator iterator = this->begin();
    int count = 0;
    while(count < index) {
        iterator++;
    }
    if(iteratorIndex != nullptr) {
        *iteratorIndex = count;
    }
    return iterator;
}

template<class T>
constIterator * Vector<T>::find(const T &element, int * const location) const
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
