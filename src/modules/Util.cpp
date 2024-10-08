//
// Created by Hayden Rivas on 7/12/24.
//

#include "Util.h"

std::string Util::readWholeFile(const std::string& fileName) {
    std::string result;
    std::string line;
    std::ifstream file("../src/assets/shaders/" + fileName);
    if (file.is_open()) {
        while (std::getline(file, line)) {
            result += line + '\n';
        }
        file.close();
    }
    return result;
}

unsigned int Util::compileShader(unsigned int type, const std::string& filename) {
    const std::string shaderFile = Util::readWholeFile(filename);

    unsigned int shader = glCreateShader(type);

    const char * shaderSource = shaderFile.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // making sure it compiled correctly
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* infoLog = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, infoLog);
        std::cout << "ERROR::SHADER::" << (type==GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}