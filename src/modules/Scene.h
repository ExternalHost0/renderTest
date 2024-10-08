//
// Created by Hayden Rivas on 7/19/24.
//
#include <vector>


#include "../prefabs/other/Camera.h"

#include <set>


#ifndef RENDERTEST_SCENE_H
#define RENDERTEST_SCENE_H

class Scene {
private:
    Camera m_PrimaryCamera;

    std::set<EntityId> m_Entities;

public:

    Scene();


    void Update();

    void MakePrimaryCamera(Camera camera);
    void MakePrimaryCamera(Camera *camera);

    Camera& GetPrimaryCamera();

};


#endif //RENDERTEST_SCENE_H
