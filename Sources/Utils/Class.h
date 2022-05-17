#pragma once


#define ConstructSetter(Class, FuncName, Var) \
    inline Class& FuncName(const decltype(Class::Var)& value) { Var = value; return *this; }

