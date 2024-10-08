//
// Created by Hayden Rivas on 9/26/24.
//

#ifndef RENDERTEST_BASECOMPONENT_H
#define RENDERTEST_BASECOMPONENT_H

#include "imgui.h"

class BaseComponent {
private:

public:
    virtual void ImGuiComponent() = 0;
};


#endif //RENDERTEST_BASECOMPONENT_H
