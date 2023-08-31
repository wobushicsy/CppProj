#include "unique_ptr.h"

template <typename T>
UniquePtr<T>::UniquePtr(T* _p) : _p(_p) {}

template <typename T>
UniquePtr<T>::UniquePtr() : _p(nullptr) {}

template <typename T>
UniquePtr<T>::~UniquePtr() {
    delete _p;
    _p = nullptr;
}

template <typename T>
T* UniquePtr<T>::get() {
    return _p;
}

template <typename T>
T& UniquePtr<T>::operator*() {
    return *_p;
}

template <typename T>
T* UniquePtr<T>::operator->() {
    return _p;
}

template <typename T>
UniquePtr<T>::operator bool() const {
    return _p != nullptr;
}

template <typename T>
void UniquePtr<T>::reset() {
    delete _p;
    _p = nullptr;
}

template <typename T>
void UniquePtr<T>::reset(T* p) {
    delete _p;
    _p = p;
}

template <typename T>
T* UniquePtr<T>::release() {
    T* tmp = _p;
    _p = nullptr;
    return tmp;
}

template <typename T>
UniquePtr<T> make_unique(T arg) {
    return UniquePtr<T>(new T(arg));
}
