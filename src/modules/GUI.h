//
// Created by Hayden Rivas on 7/18/24.
//

#include "IconsFontAwesome6.h"
#include "IconsFontAwesome6Brands.h"

#include "imgui.h"
#include "detail/type_vec3.hpp"

#ifndef RENDERTEST_GUI_H
#define RENDERTEST_GUI_H


class GUI {
private:
public:
    static void Init();
    static void InitStyle();

    static void ActualWindowUpdate();
    static void EndUpdate();

    static void Update();

    static void StyleColorsRichDark(ImGuiStyle* dst = nullptr);
    static void StyleColorsDeepLight(ImGuiStyle* dst = nullptr);

};


#endif //RENDERTEST_GUI_H
