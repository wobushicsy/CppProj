#include "shared_ptr.h"

template <typename T>
size_t SharedPtr<T>::count = 0;

template <typename T>
SharedPtr<T>::SharedPtr(T* p) {
    _p = p;
    count = 1;
}

template <typename T>
SharedPtr<T>::SharedPtr() {
    _p = nullptr;
    count = 0;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    count -= 1;
    if (count == 0) {
        delete _p;
        _p = nullptr;
    }
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& another) {
    count += 1;
    _p = another._p;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& src) {
    if (src._p == _p) {
        return *this;
    }
    _p = src._p;
    count += 1;
    return *this;
}

template<class T>
SharedPtr<T>::operator bool() const {
    return _p != nullptr;
}

template <typename T>
size_t SharedPtr<T>::use_count() {
    return count;
}

template <typename T>
T* SharedPtr<T>::get() {
    return _p;
}

template <typename T>
T& SharedPtr<T>::operator*() {
    return *_p;
}

template <typename T>
T* SharedPtr<T>::operator->() {
    return _p;
}

template <typename T>
void SharedPtr<T>::reset() {
    _p = nullptr;
    count -= 1;
}

template <typename T>
void SharedPtr<T>::reset(T* another) {
    count -= 1;
    *this = SharedPtr<T>(another);
}

template <typename T>
SharedPtr<T> make_shared(T arg) {
    return SharedPtr<T>(new T(arg));
}
