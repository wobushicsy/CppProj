#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr {
public:
    explicit UniquePtr(T* _p);
    UniquePtr();
    ~UniquePtr();
    UniquePtr(UniquePtr<T>& another) = delete;
    UniquePtr<T>& operator=(UniquePtr<T>& src) = delete;
    explicit operator bool() const;
    T* get();
    T& operator*() ;
    T* operator->() ;
    void reset();
    void reset(T* p);
    T* release();

private:
    T* _p;
};

template <typename T>
UniquePtr<T> make_unique(T arg);

#include "unique_ptr.hpp"

#endif //UNIQUE_PTR