//
// Created by Hayden Rivas on 7/18/24.
//

#ifndef RENDERTEST_PRIMITIVES_H
#define RENDERTEST_PRIMITIVES_H


class Primitives {
private:
public:
    // geometry
    const float triVerts[9] = {
            -0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };
    constexpr static const float quadVerts[12] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };
    constexpr static const float cubeVerts[24] = {
            1.0f,  1.0f, 1.0f,  // front top right       0
            1.0f, -1.0f, 1.0f,  // front bottom right    1
            -1.0f, -1.0f, 1.0f,  // front bottom left    2
            -1.0f,  1.0f, 1.0f,   // front top left     3

            1.0f,  1.0f, -1.0f,  // back top right     4
            1.0f, -1.0f, -1.0f,  // back bottom right  5
            -1.0f, -1.0f, -1.0f,  // back bottom left  6
            -1.0f,  1.0f, -1.0f,   // back top left    7
    };

    constexpr static unsigned int quadIndicies[6] = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };
    constexpr static unsigned int cubeIndicies[36] = {
            0, 1, 3, 3, 1, 2,
            1, 5, 2, 2, 5, 6,
            5, 4, 6, 6, 4, 7,
            4, 0, 7, 7, 0, 3,
            3, 2, 7, 7, 2, 6,
            4, 5, 0, 0, 5, 1
    };

};


#endif //RENDERTEST_PRIMITIVES_H
