#ifndef COMPARE_H
#define COMPARE_H

template <class T, class Member>
class Compare {
public:
    explicit Compare() {}
    virtual bool equiv(const T &classInstance, const Member &memberVar) const = 0;
/*private:
    Compare() {} //uninstantiable*/
};

#endif // COMPARE_H
