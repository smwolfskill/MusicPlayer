#ifndef CVECTOR_H
#define CVECTOR_H

#include "vector.h"
#include "compare.h"

/**
 * @brief CVector --- 'ComparisonVector': extension of Vector that allows more intricate element comparisons
 *                    via Compare class to compare elements of a class against some property
 *                    e.g. an artist and string pair are 'equivalent' when artist.name = the string value.
 * @author      Scott Wolfskill
 * @created     12/05/2017
 * @last_edit   12/05/2017
 */
template<class T, class compareType>
class CVector : public Vector<T>
{
public:
    //Methods:
    CVector(std::size_t blankElements = 0) : Vector<T>(blankElements) {}

    /**
     * @brief find
     * @param lookFor Variable to look for in class T via Compare<T, compareType>.
     * @return index in vector of location, or -1 if not found.
     */
    int find(const Compare<T,compareType> &compare, const compareType &lookFor) const;

};

template<class T, class compareType>
int CVector<T,compareType>::find(const Compare<T,compareType> &compare, const compareType &lookFor) const
{
    for(unsigned i = 0; i < this->size(); i++) {
        if(compare.equiv(this->at(i), lookFor)) { //found 'equivalent' of lookFor
            return (int) i;
        }
    }
    return -1; //not found
}


#endif // CVECTOR_H
