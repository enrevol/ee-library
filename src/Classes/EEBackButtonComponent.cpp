//
//  EEBackButtonComponent.cpp
//  ee-library
//
//  Created by Zinge on 12/27/16.
//
//

#include "EEBackButtonComponent.hpp"

#include <cocos2d.h>

NS_EE_BEGIN
BackButtonComponent*
BackButtonComponent::create(const BackButtonCallback& callback) {
    auto result = new (std::nothrow) BackButtonComponent();
    if (result != nullptr && result->initWithCallback(callback)) {
        result->autorelease();
    } else {
        CC_SAFE_DELETE(result);
    }
    return result;
}

void BackButtonComponent::onAdd() {
    Super::onAdd();

    CC_ASSERT(listener_ == nullptr);

    listener_ = cocos2d::EventListenerKeyboard::create();
    listener_->onKeyReleased =
        std::bind(&BackButtonComponent::onKeyReleased, this,
                  std::placeholders::_1, std::placeholders::_2);

    cocos2d::Director::getInstance()
        ->getEventDispatcher()
        ->addEventListenerWithSceneGraphPriority(listener_, getOwner());
}

void BackButtonComponent::onRemove() {
    Super::onRemove();
    CC_ASSERT(listener_ != nullptr);

    cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener(
        listener_);

    listener_ = nullptr;
}

void BackButtonComponent::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode,
                                        cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_BACK) {
        if (getOwner()->isRunning()) {
            callback_();

            // Allow only one event listener receives event.
            event->stopPropagation();
        }
    }
}
NS_EE_END