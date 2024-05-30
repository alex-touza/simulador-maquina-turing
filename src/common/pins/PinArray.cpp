//
// Created by backo on 30/5/2024.
//

#include "PinArray.h"

using namespace TMPins;

inline void* operator new(size_t, void* ptr) noexcept {
    return ptr;
}

template<class T>
T* PinArray<T>::getObjects(int pinStart, int pinEnd) {
    int length = pinEnd - pinStart + 1;

    T* array = static_cast<T*>(::operator new[](length * sizeof(T)));

    T* ptr = array;

    for (int i = 0; i < length; ++i, ++ptr) {
        new(ptr) T(pinStart + i); // Using placement new to construct each T with different value
    }


    return array;
}

template<class T>
PinArray<T>::~PinArray() {
    for (int i = 0; i < this->n; ++i) {
        this->array[i].~T();
    }

    ::operator delete[](array);
}


template<class T>
PinArray<T>::PinArray(T* _array, int _n) : array(_array), n(_n) {}

template<class T>
PinArray<T>::PinArray(int pinStart, int pinEnd) : n(pinEnd - pinStart + 1) {
    this->array = PinArray<T>::getObjects(pinStart, pinEnd);
}

template<class T>
void PinArray<T>::begin() {
    for (int i = 0; i < this->n; ++i) {
        this->array[i].begin();
    }

}

template<class T>
void PinArray<T>::rangeFunc(void (func)(T*), int start, int end) {
    if (end == -1) {
        if (start == 0) end = this->n;
        else end = start;
    }

    T* ptr = this->array + start;
    for (int i = start; i < end; ++i, ++ptr)
        func(ptr);


}

template<class T>
unsigned int* PinArray<T>::rangeFunc(unsigned int (func)(T*), int start, int end) {
    if (end == -1) {
        if (start == 0) end = this->n;
        else end = start;
    }

    auto* result = new unsigned int[end - start];

    T* ptr = this->array + start;
    unsigned int* resPtr = result;

    for (int i = start; i < end; ++i, ++ptr, ++resPtr)
        *resPtr = func(ptr);

    return result;
}

template<class U, bool state>
void setLambda(U* out) {
    dynamic_cast<OutputPin*>(out)->set(state);
}
/*
template<class U>
void onLambda(U* out) {
    dynamic_cast<OutputPin*>(out)->on();
}
template<class U>
void offLambda(U* out) {
    dynamic_cast<OutputPin*>(out)->off();
}
 */

template<class T>
void OutputPinArray<T>::set(bool state, int start, int end) {
    if (state)
        this->rangeFunc(setLambda<T, true>, start, end);
    else
        this->rangeFunc(setLambda<T, false>, start, end);
}

template<class T>
void OutputPinArray<T>::on(int start, int end) {
    this->set(true, start, end);
}

template<class T>
void OutputPinArray<T>::off(int start, int end) {
    this->set(false, start, end);
}

