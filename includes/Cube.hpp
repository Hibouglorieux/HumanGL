#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>
#include <Shader.hpp>
#include <array>

class Cube {
public:
    Cube(std::array<float, 3> color);
    void draw(float *viewMat) const;
    void setModelMat(float *modelMat);

private:
    GLuint VAO, VBO, EBO;
    Shader shader;
    float *modelMat;
    std::array<float, 3> color;

};

#endif
