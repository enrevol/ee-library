//
//  EEDialog.cpp
//  roll-eat
//
//  Created by Hoang Le Hai on 9/1/15.
//
//

#include "EEDialog.hpp"
#include "EEDialogManager.hpp"
#include "EEUtils.hpp"

#include <cocos2d.h>

NS_EE_BEGIN
namespace dialog {
const int Dialog::ContainerLocalZOrder = 123456;
const std::size_t Dialog::TopLevel = 123456;

bool Dialog::init() {
    if (Widget::init() == false) {
        return false;
    }
    
    setActive(false);
    addClickEventListener(CC_CALLBACK_0(Dialog::onClickedOutside, this));
    
    return true;
}

void Dialog::onEnter() {
    Widget::onEnter();
}

void Dialog::onExit() {
    Widget::onExit();
}
    
const cocos2d::Node* Dialog::getContainer() const {
    return getParent();
}

cocos2d::Node* Dialog::getContainer() {
    return getParent();
}

void Dialog::show(std::size_t level) {
    auto container = cocos2d::Node::create();
    container->setContentSize(_director->getWinSize());
    container->addChild(this);
    
    DialogManager::getInstance()->pushDialog(this, level);
}

void Dialog::hide() {
    DialogManager::getInstance()->popDialog(this);
}
    
Dialog* Dialog::addDialogWillShowCallback(const CallbackType& callback,
                                          int priority) {
    onDialogWillShowCallbacks_.emplace_back(callback, priority);
    return this;
}

Dialog* Dialog::addDialogDidShowCallback(const CallbackType& callback,
                                         int priority) {
    onDialogDidShowCallbacks_.emplace_back(callback, priority);
    return this;
}

Dialog* Dialog::addDialogWillHideCallback(const CallbackType& callback,
                                          int priority) {
    onDialogWillHideCallbacks_.emplace_back(callback, priority);
    return this;
}

Dialog* Dialog::addDialogDidHideCallback(const CallbackType& callback,
                                         int priority) {
    onDialogDidHideCallbacks_.emplace_back(callback, priority);
    return this;
}
    
std::size_t Dialog::getDialogLevel() const noexcept {
    return dialogLevel_;
}
    
void Dialog::setActive(bool active) {
    isActive_ = active;
}
    
bool Dialog::isActive() const noexcept {
    return isActive_;
}

bool Dialog::hitTest(const cocos2d::Point& pt,
                     const cocos2d::Camera* camera,
                     cocos2d::Vec3* p) const {
    // Test outside.
    return (Widget::hitTest(pt, camera, p) == false);
}
    
void Dialog::onDialogWillShow() {
    invokeCallbacks(onDialogWillShowCallbacks_);
}

void Dialog::onDialogDidShow() {
    invokeCallbacks(onDialogDidShowCallbacks_);
}

void Dialog::onDialogWillHide() {
    invokeCallbacks(onDialogWillHideCallbacks_);
}

void Dialog::onDialogDidHide() {
    invokeCallbacks(onDialogDidHideCallbacks_);
}
    
void Dialog::invokeCallbacks(std::vector<CallbackInfo>& callbacks) {
    std::stable_sort(callbacks.begin(), callbacks.end(), Compare2nd<>());
    
    RefGuard guard(this);
    
    for (auto&& info : callbacks) {
        info.first(this);
    }
}

void Dialog::onClickedOutside() {
    if (isActive()) {
        hide();
    }
}
    
void Dialog::setShowingTransitions(const std::vector<TransitionRef>& transitions) {
    showingTransitions_ = transitions;
}

void Dialog::setHidingTransitions(const std::vector<TransitionRef>& transitions) {
    hidingTransitions_ = transitions;
}

void Dialog::addShowingTransitions(const std::vector<TransitionRef>& transitions) {
    showingTransitions_.insert(showingTransitions_.cend(),
                               transitions.cbegin(), transitions.cend());
}

void Dialog::addHidingTransitions(const std::vector<TransitionRef>& transitions) {
    hidingTransitions_.insert(hidingTransitions_.cend(),
                              transitions.cbegin(), transitions.cend());
}

auto Dialog::getShowingTransitions() const -> const std::vector<TransitionRef>& {
    return showingTransitions_;
}

auto Dialog::getHidingTransitions() const -> const std::vector<TransitionRef>&  {
    return hidingTransitions_;
}
} // namespace dialog
NS_EE_END