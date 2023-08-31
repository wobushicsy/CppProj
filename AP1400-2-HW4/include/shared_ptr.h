#ifndef SHARED_PTR
#define SHARED_PTR

#include <cstddef>
using std::size_t;

template <class T>
class SharedPtr {
public:
    explicit SharedPtr(T* p);
    SharedPtr();
    ~SharedPtr();
    SharedPtr(const SharedPtr<T>& another);
    SharedPtr<T>& operator=(const SharedPtr<T>& src);
    explicit operator bool() const;
    size_t use_count();
    T* get();
    T& operator*();
    T* operator->();
    void reset();
    void reset(T* another);

private:
    T* _p;
    static size_t count;
};

template <class T>
SharedPtr<T> make_shared(T arg);

#include "shared_ptr.hpp"

#endif //SHARED_PTR