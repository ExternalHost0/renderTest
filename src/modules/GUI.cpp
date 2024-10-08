//
// Created by Hayden Rivas on 7/18/24.
//

#include "GUI.h"
#include "../Application.h"
#include "imgui_internal.h"
#include "imgui_stdlib.h"


void GUI::Init() {

    Application& app = Application::get();
    // Setup Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(app.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
    // calls for styling imgui
    InitStyle();
}
void GUI::InitStyle() {
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    {
        style.DockingSeparatorSize = 4.0f;
        style.FramePadding = {7, 5};
        style.SeparatorTextAlign = {50, 50};
        style.FrameRounding = 1.0f;
    }

    // main font config
    ImFontConfig fontCfg;
    {
        fontCfg.FontDataOwnedByAtlas = false;
        fontCfg.OversampleH = 2;
        fontCfg.OversampleV = 2;
        fontCfg.RasterizerMultiply = 1.0f;
        fontCfg.RasterizerDensity = 2.0f;
    }

    // icon font config
    ImFontConfig iconFontCfg;
    {
        iconFontCfg.RasterizerDensity = 2.0f;
        iconFontCfg.MergeMode = true;
        iconFontCfg.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
    }
    static const ImWchar IFA_Range[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
    static const ImWchar IFABrands_Range[] = {ICON_MIN_FAB, ICON_MAX_FAB, 0};

    // main font
    io.Fonts->AddFontFromFileTTF("../src/assets/fonts/NotoSans-Regular.ttf", 17.0f, &fontCfg);
    // icon fonts
    float iconsize = 16.0f;
    io.Fonts->AddFontFromFileTTF("../src/assets/fonts/" FONT_ICON_FILE_NAME_FAR, iconsize, &iconFontCfg, IFA_Range);
    io.Fonts->AddFontFromFileTTF("../src/assets/fonts/" FONT_ICON_FILE_NAME_FAS, iconsize, &iconFontCfg, IFA_Range);
    io.Fonts->AddFontFromFileTTF("../src/assets/fonts/" FONT_ICON_FILE_NAME_FAB, iconsize, &iconFontCfg, IFABrands_Range);

    // our default style for the user interface
    GUI::StyleColorsRichDark();
}


bool openDockspace = true;

void GUI::Update() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Dockspace Setup
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_NoWindowMenuButton; // Config flags for the Dockspace
    const ImGuiViewport *viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGuiWindowFlags dockspaceWindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    dockspaceWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    dockspaceWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    dockspaceWindowFlags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

    // Set the parent m_Window's styles to match that of the main viewport:
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f); // No corner rounding on the m_Window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f); // No border around the m_Window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("DockSpace Main", &openDockspace, dockspaceWindowFlags);
    {
        ImGui::PopStyleVar(3);
        ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspace_flags);

        GUI::ActualWindowUpdate();
    }
    ImGui::End();
    GUI::EndUpdate();
}


ImGuiWindowFlags defaultWindowFlags = ImGuiWindowFlags_NoCollapse;
void GUI::ActualWindowUpdate() {

    // --- MY GUI RENDERING --- //

    // Top Menu Bar
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("Save");
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "esc")) Application::get().PreQuit();
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    Application &app = Application::get();
    static int selected = -1; // for right click context, made static to avoid leaving scope
//    ImGui::Begin("Scene Hierarchy", nullptr, defaultWindowFlags);
//    {
//        auto objects= app.GetCurrentScene().GetVectorPointers();
//
//        int index = 0;
//        for (Object* obj : objects) {
//            ImGui::PushID(index);
//            if (ImGui::Selectable(obj->m_Name.c_str(), selected == index)) selected = index;
//            // right click menu
//            if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
//            {
//                selected = index;
//                ImGui::Text("%s", obj->m_Name.c_str());
//                if (ImGui::Button("Rename")) {
////                    ImGui::InputText("Name", &obj->m_Name);
//                }
//                ImGui::Button("Copy");
//                ImGui::Button("Paste");
//                ImGui::Button("Duplicate");
//                if (ImGui::Button("Delete")) {
//                    app.GetCurrentScene().DeleteObject(index);
//                    ImGui::CloseCurrentPopup();
//                }
//                ImGui::EndPopup();
//            }
//
//            // picker
//            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_AcceptNoDrawDefaultRect)) {
//                ImGui::SetDragDropPayload("Scene Hierarchy", &index, sizeof(int));
////                ImGui::Text("%s", obj->m_Name.c_str());
//                ImGui::EndDragDropSource();
//            }
//
//            // dropper
//            if (ImGui::BeginDragDropTarget()) {
//                // DRAWING THE LINES THAT PREVIEW THE PLACEMENT
//                // rect sizes
//                ImVec2 itemRect = ImGui::GetItemRectSize();
//                ImVec2 itemRectMin = ImGui::GetItemRectMin();
//                ImVec2 itemRectMax = ImGui::GetItemRectMax();
//
//                // determining if we are dropping above or below the hovered item
//                float mouseY = ImGui::GetMousePos().y;
//                bool dropAbove = (mouseY < (itemRectMin.y + itemRect.y * 0.5f));
//                int insertIndex = dropAbove ? index : index+1;
//
//                ImDrawList* draw_list = ImGui::GetWindowDrawList();
//                ImVec2 barStart = dropAbove ? itemRectMin : ImVec2(itemRectMin.x, itemRectMax.y);
//                ImVec2 barEnd = ImVec2(itemRectMax.x, barStart.y);
//                draw_list->AddLine(barStart, barEnd, ImGui::GetColorU32(ImGuiCol_DragDropTarget), 3.0f);
//
//                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Scene Hierarchy")) {
//                    IM_ASSERT(payload->DataSize == sizeof(int));
//                    int payload_index = *(const int*)payload->Data;
//                    if (payload_index == index) return;
//
//                    if (payload_index < insertIndex) { --insertIndex; }
//                    //  moving object algo
//                    auto* element = objects[payload_index];
//                    objects.erase(objects.begin() + payload_index);
//                    objects.insert(objects.begin() + insertIndex, element);
//                }
//                ImGui::EndDragDropTarget();
//            }
//            index++;
//            ImGui::PopID();
//
//        }
//        ImGui::End();
//    }



    float DRAG_SPEED = 0.25f;
    float MIN_DISTANCE = -1000.0f;
    float MAX_DISTANCE = 1000.0f;
//    ImGui::Begin("Properties", nullptr, defaultWindowFlags);
//    {
//        if (selected != -1) {
//            Object* selectobj = app.GetCurrentScene().GetObjectAtIndex(selected);
//
//            ImGui::Text("%s", selectobj->m_Name.c_str());
//
//            ImGui::Text("Position");
//            ImGui::DragFloat("X", &selectobj->m_Position.x, DRAG_SPEED, MIN_DISTANCE, MAX_DISTANCE);
//            ImGui::DragFloat("Y", &selectobj->m_Position.y, DRAG_SPEED, MIN_DISTANCE, MAX_DISTANCE);
//            ImGui::DragFloat("Z", &selectobj->m_Position.z, DRAG_SPEED, MIN_DISTANCE, MAX_DISTANCE);
//        }
//        ImGui::End();
//    }




    ImGui::Begin("Scene View", nullptr, defaultWindowFlags | ImGuiWindowFlags_MenuBar);
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Add"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
                if (ImGui::MenuItem("Close", "Ctrl+W"))  { }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Deconstruct")) {}
                if (ImGui::MenuItem("Constrcut")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        // THIS NEEDS CHECKED, multiplying by 2 solves resolution issue but why, pretty sure this is SSAA
        app.getRenderer().setViewportSize({(int) viewportPanelSize.x * 2, (int) viewportPanelSize.y * 2});
        ImGui::Image(reinterpret_cast<void *>(app.getRenderer().GetFramebufferTexture()),{viewportPanelSize.x, viewportPanelSize.y}, ImVec2{0, 1}, ImVec2{1, 0});

        ImGui::End();
    }
    ImGui::ShowDemoWindow();
}

void GUI::EndUpdate() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
