//
// Created by Hayden Rivas on 8/21/24.
//

#ifndef RENDERTEST_TRANSFORMCOMPONENT_H
#define RENDERTEST_TRANSFORMCOMPONENT_H

#include "../../Structs.h"
#include "../BaseComponent.h"

class TransformComponent : public BaseComponent {
private:
    vec3 position;
    quat rotation;
    vec3 scale;
public:
    void ImGuiComponent() override;

    void Move(vec3 newPosition);
    void Rotate(quat newRotation);
    void Scale(vec3 newScale);

};


#endif //RENDERTEST_TRANSFORMCOMPONENT_H
