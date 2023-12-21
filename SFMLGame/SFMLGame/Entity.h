#pragma once
#include "Components.h"
#include <memory>
#include <string>

class Entity {
    friend class EntityManager;

    bool m_active = true;
    bool m_colliding = false;
    size_t m_id = 0;
    std::string m_tag = "Default";

    //private constructor so we cannot create entities on our own
    Entity(const size_t id, const std::string& tag);

public:
    //component pointers
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CLifespan> cLifespan;
    std::shared_ptr<CRect> cRect;

    bool isActive() const;
    bool isColliding() const;
    void setColliding(bool val);
    const std::string& tag() const;
    const size_t id() const;
    void destroy();
};