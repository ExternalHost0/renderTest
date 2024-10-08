//
// Created by Hayden Rivas on 7/20/24.
//
#include <GL/glew.h>
#include <glm.hpp>
#include "detail/type_quat.hpp"
using glm::vec2, glm::vec3, glm::quat;

using EntityId = std::uint32_t;
using ComponentTypeId = std::uint8_t;

#ifndef RENDERTEST_STRUCTS_H
#define RENDERTEST_STRUCTS_H

const EntityId MAX_ENTITIES = 5000; // max entities available to entitymanager
const ComponentTypeId MAX_COMPONENTS = 16; // max components available to componentmanager

struct Vec4clampf {
    GLclampf r, g, b, a;
};
struct Vec2GLsizei {
    GLsizei x, y;
};

enum Category {
    NONE,
    SHAPE,
    CAMERA
};



#endif //RENDERTEST_STRUCTS_H
