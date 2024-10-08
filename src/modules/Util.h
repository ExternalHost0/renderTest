//
// Created by Hayden Rivas on 7/12/24.
//
#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#ifndef RENDERTEST_UTIL_H
#define RENDERTEST_UTIL_H


class Util {
private:

public:
    static std::string readWholeFile(const std::string& fileName);
    static unsigned int compileShader(unsigned int type, const std::string& filename);

};


#endif //RENDERTEST_UTIL_H
