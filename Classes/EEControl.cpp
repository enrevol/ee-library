#include "EEControl.hpp"
#include "cocos2d.h"

namespace_ee_begin
Button::~Button() {
    if (_normalSpriteFrame != nullptr) {
        _normalSpriteFrame->release();
    }
    if (_pressedSpriteFrame != nullptr) {
        _pressedSpriteFrame->release();
    }
    if (_disabledSpriteFrame != nullptr) {
        _disabledSpriteFrame->release();
    }
}

cocos2d::SpriteFrame* Button::getSpriteFrameForState(ButtonState state) const {
    cocos2d::SpriteFrame* ret = nullptr;
    switch (state) {
        case ButtonState::Normal: ret = _normalSpriteFrame; break;
        case ButtonState::Pressed: ret = _pressedSpriteFrame; break;
        case ButtonState::Disabled: ret = _disabledSpriteFrame; break;
    }
    return ret;
}

void Button::setSpriteFrameForState(ButtonState state, const std::string& spriteFrameName) {
    auto frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName);
    setSpriteFrameForState(state, frame);
}

void Button::setSpriteFrameForState(ButtonState state, cocos2d::SpriteFrame* spriteFrame) {
    decltype(&_normalSpriteFrame) frame = nullptr;
    switch (state) {
        case ButtonState::Normal: frame = &_normalSpriteFrame; break;
        case ButtonState::Pressed: frame = &_pressedSpriteFrame; break;
        case ButtonState::Disabled: frame = &_disabledSpriteFrame; break;
    }
    if (*frame != nullptr) {
        (*frame)->release();
    }
    (*frame) = spriteFrame;
    (*frame)->retain();
    updateState();
}

void Button::setSpriteFrame(cocos2d::SpriteFrame* spriteFrame) {
    Sprite::setSpriteFrame(spriteFrame);
    spriteFrame->retain();
    _normalSpriteFrame = spriteFrame;
}

void Button::updateState(ButtonState state) {
    TouchListener::updateState(state);
    auto sprite = getSpriteFrameForState(state);
    if (sprite == nullptr) {
        sprite = getSpriteFrameForState(ButtonState::Normal);
    }
    setSpriteFrame(sprite);
}
namespace_ee_end