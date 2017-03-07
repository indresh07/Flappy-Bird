#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#include<iostream>
#include<string>
#include<SDL.h>
namespace gameEngine{
    extern void fatalError(std::string errorString);
}

#endif // ERRORS_H_INCLUDED
