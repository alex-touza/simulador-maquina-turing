//
// Created by backo on 30/5/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_PINARRAY_H
#define SIMULADOR_MAQUINA_TURING_PINARRAY_H

#include "DigitalIn.h"
#include "DigitalOut.h"
#include "AnalogOut.h"
#include "AnalogIn.h"

namespace TMPins {

    template<class T>
    class PinArray {
    private:
        T* array;
        const int n;

    public:
        static T* getObjects(int, int);

        PinArray(T*, int);

        PinArray(int, int);

        void begin();

        /*
         * Quan hi ha paràmetres de l'estil (int start, int end),
         * si s'assigna `start` però no `end`, aquest últim valor
         * serà igual a `start`. D'aquesta forma, no es repeteix el
         * valor si només es vol actuar per a un sol element.
         */

        void rangeFunc(void (func)(T*), int = 0, int = -1);

        unsigned int* rangeFunc(unsigned int (func)(T*), int = 0, int = -1);

        ~PinArray();

    };

    template<class T>
    class OutputPinArray : protected PinArray<T> {
    public:
        using PinArray<T>::PinArray;
        using PinArray<T>::begin;

        void set(bool, int = 0, int = -1);

        void on(int = 0, int = -1);

        void off(int = 0, int = -1);
    };


    template class OutputPinArray<DigitalOut>;
    template class PinArray<DigitalOut>;

    // template class PinArray<DigitalIn>;
    // template class PinArray<DigitalOut>;
    // template class PinArray<AnalogIn>;
    // template class PinArray<AnalogOut>;

} // TMPins

#endif //SIMULADOR_MAQUINA_TURING_PINARRAY_H
