//
// Created by Alex on 18/05/2024.
//

#ifndef SIMULADOR_MAQUINA_TURING_LANG_H
#define SIMULADOR_MAQUINA_TURING_LANG_H

#include "Arduino.h"

template<int n>
class Lang {
    class Value {
        String encoded;
        String value;
    };
private:
    Value values[n];
public:
    explicit Lang(String[n]);

    String decode(const String& code);
    String encode(String value);
};




#endif //SIMULADOR_MAQUINA_TURING_LANG_H
