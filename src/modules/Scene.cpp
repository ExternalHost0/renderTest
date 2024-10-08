//
// Created by Hayden Rivas on 7/19/24.
//

#include "Scene.h"

#include "../Application.h"

Scene::Scene() = default;
void Scene::Update() {
    m_PrimaryCamera.Update();
//    m_SystemManager.Update();

}

//void Scene::AddObject(Object* object) {
//    // adding to the list
//    int tempTick = 0;
//
//    for (const Object* obj : m_Objects) {
//        if (obj->m_Name == object->m_Name || obj->m_Name == object->m_Name + " " + std::to_string(tempTick)) {
//            tempTick += 1;
//        }
//    }
//    if (tempTick) object->m_Name = object->m_Name + " " + std::to_string(tempTick);
//
//    m_Objects.push_back(object);
//}

// getter and setter for primary camera of scene
void Scene::MakePrimaryCamera(Camera* camera) { m_PrimaryCamera = *camera; }

// weird workaround...
Camera& Scene::GetPrimaryCamera() { return m_PrimaryCamera; }

