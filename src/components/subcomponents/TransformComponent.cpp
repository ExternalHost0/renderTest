//
// Created by Hayden Rivas on 8/21/24.
//

#include "TransformComponent.h"

void TransformComponent::ImGuiComponent() {
    ImGui::Begin("Transform Component");
    {
        ImGui::Text("Position");
    }
    ImGui::End();
}

void TransformComponent::Move(vec3 newPosition) {
    position = newPosition;
}

void TransformComponent::Rotate(quat newRotation) {
    rotation = newRotation;
}

void TransformComponent::Scale(vec3 newScale) {
    scale = newScale;
}
