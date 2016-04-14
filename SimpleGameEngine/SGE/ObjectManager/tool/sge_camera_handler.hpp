//
//  sge_camera_handler.hpp
//  SimpleGameEngine
//
//  Created by Janusz Majchrzak on 11/04/16.
//  Copyright © 2016 Hamashy. All rights reserved.
//

#ifndef sge_camera_handler_h
#define sge_camera_handler_h

namespace SGE {
    
    ObjectManager::CameraHandler::CameraHandler(std::pair<int, int> resolution, ObjectManager* m) noexcept : manager(m) {
        this->camera = new Camera2d(resolution.first, resolution.second);
        this->manager->registerCamera(this->camera);
    }
    
    Camera2d* ObjectManager::CameraHandler::getCamera()
    {
        return this->camera;
    }
    
    void ObjectManager::CameraHandler::setScale(double _scale) noexcept {
        this->camera->setScale(_scale);
    }
    
    void ObjectManager::CameraHandler::setPosition(int _x, int _y) noexcept {
        this->camera->setPosition(glm::vec2(_x, _y));
    }
    
    void ObjectManager::CameraHandler::updateCamera(void) const noexcept {
        this->camera->update();
    }
    
    const glm::mat4& ObjectManager::CameraHandler::getCameraMatrix(void) const noexcept {
        return this->camera->getCameraMatrix();
    }
    
    void ObjectManager::CameraHandler::setPosition(glm::vec2 pos) noexcept {
        this->setPosition(pos.x, pos.y);
    }
    
    glm::vec2 ObjectManager::CameraHandler::getScreenToWorld(glm::vec2 pos) const noexcept {
        return this->camera->screenToWorld(pos);
    }
    
    glm::vec2 ObjectManager::CameraHandler::getScreenToWorld(int _x, int _y) const noexcept {
        return this->getScreenToWorld({_x, _y});
    }

    
}

#endif /* sge_camera_handler_h */
