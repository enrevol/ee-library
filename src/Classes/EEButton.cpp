//
//  EEButton.cpp
//  ee-library
//
//  Created by Zinge on 4/23/16.
//
//

#include "EEButton.hpp"
#include "EEUtils.hpp"

#include <cocos2d.h>
#include <ui/CocosGUI.h>

NS_EE_BEGIN
NS_DETAIL_BEGIN
auto ButtonEx::getDefaultHitTester() -> const HitTester& {
    static const HitTester checker = [](cocos2d::Touch* touch,
                                            Button* button) {
        // Retrieve world position.
        auto&& position = touch->getLocation();
        
        // Convert to local position.
        auto&& localPosition = button->convertToNodeSpace(position);
        
        // Retrieve local bounding box.
        auto&& contentSize = button->getContentSize();
        
        return (0 <= localPosition.x && localPosition.x <= contentSize.width &&
                0 <= localPosition.y && localPosition.y <= contentSize.height);
    };
    return checker;
}

ButtonEx::ButtonEx()
: zoomingDuration_(0.05f)
, currentTouch_(nullptr)
, currentEvent_(nullptr)
, container_(nullptr) {}

ButtonEx::~ButtonEx() = default;

ButtonEx* ButtonEx::create() {
    auto result = new (std::nothrow) ButtonEx();
    if (result != nullptr && result->init()) {
        result->autorelease();
    } else {
        CC_SAFE_DELETE(result);
    }
    return result;
}

ButtonEx* ButtonEx::create(const std::string& normalImage,
                           const std::string& selectedImage,
                           const std::string& disableImage,
                           TextureResType texType) {
    auto result = new (std::nothrow) ButtonEx();
    if (result != nullptr && result->init(normalImage,
                                          selectedImage,
                                          disableImage,
                                          texType)) {
        result->autorelease();
        result->setScale9Enabled(true);
    } else {
        CC_SAFE_DELETE(result);
    }
    return result;
}

void ButtonEx::addChild(Node* child, int localZOrder, int tag) {
    // Forward to the container.
    container_->addChild(child, localZOrder, tag);
}

void ButtonEx::addChild(Node* child, int localZOrder, const std::string& name) {
    // Forward to the container.
    container_->addChild(child, localZOrder, name);
}

auto ButtonEx::getChildByTag(int tag) const -> Node* {
    // Forward to the container.
    return container_->getChildByTag(tag);
}

auto ButtonEx::getChildByName(const std::string& name) const -> Node* {
    // Forward to the container.
    return container_->getChildByName(name);
}

auto ButtonEx::getChildren() -> cocos2d::Vector<Node*>& {
    // Forward to the container.
    return container_->getChildren();
}

auto ButtonEx::getChildren() const -> const cocos2d::Vector<Node*>& {
    // Forward to the container.
    return container_->getChildren();
}

ssize_t ButtonEx::getChildrenCount() const {
    // Forward to the container.
    return container_->getChildrenCount();
}

void ButtonEx::removeChild(Node* child, bool cleanup) {
    // Forward to the container.
    container_->removeChild(child, cleanup);
}

void ButtonEx::removeAllChildrenWithCleanup(bool cleanup) {
    // Forward to the container.
    container_->removeAllChildrenWithCleanup(cleanup);
}

void ButtonEx::reorderChild(Node* child, int localZOrder) {
    if (child == container_) {
        Button::reorderChild(child, localZOrder);
    } else {
        // Forward to the container.
        container_->reorderChild(child, localZOrder);
    }
}

void ButtonEx::sortAllChildren() {
    // Forward to the container.
    container_->sortAllChildren();
}

void ButtonEx::setContentSize(const cocos2d::Size& contentSize) {
    Button::setContentSize(contentSize);
}

bool ButtonEx::hitTest(const cocos2d::Point& point,
                       const cocos2d::Camera* camera,
                       cocos2d::Vec3* p) const {
    // Forward to the container.
    return container_->hitTest(point, camera, p);
}

bool ButtonEx::onTouchBegan(cocos2d::Touch* touch,
                            cocos2d::Event* event) {
    CC_ASSERT(currentTouch_ == nullptr);
    CC_ASSERT(currentEvent_ == nullptr);
    currentTouch_ = touch;
    currentEvent_ = event;
    bool result = Button::onTouchBegan(touch, event);
    currentTouch_ = nullptr;
    currentEvent_ = nullptr;
    return result;
}

void ButtonEx::onTouchMoved(cocos2d::Touch* touch,
                            cocos2d::Event* event) {
    if (touch->getDelta() == cocos2d::Vec2::ZERO) {
        return;
    }
    CC_ASSERT(currentTouch_ == nullptr);
    CC_ASSERT(currentEvent_ == nullptr);
    currentTouch_ = touch;
    currentEvent_ = event;
    Button::onTouchMoved(touch, event);
    currentTouch_ = nullptr;
    currentEvent_ = nullptr;
}

void ButtonEx::onTouchEnded(cocos2d::Touch* touch,
                            cocos2d::Event* event) {
    CC_ASSERT(currentTouch_ == nullptr);
    CC_ASSERT(currentEvent_ == nullptr);
    currentTouch_ = touch;
    currentEvent_ = event;
    Button::onTouchEnded(touch, event);
    currentTouch_ = nullptr;
    currentEvent_ = nullptr;
}

void ButtonEx::setScale9Enabled(bool enable) {
    Button::setScale9Enabled(enable);
}

std::string ButtonEx::getDescription() const {
    return "ee::ButtonEx";
}

void ButtonEx::setZoomingDuration(float duration) noexcept {
    zoomingDuration_ = duration;
}

float ButtonEx::getZoomingDuration() const noexcept {
    return zoomingDuration_;
}

void ButtonEx::setTouchBeganCallback(const TouchCallback& callback) {
    addTouchEventListener([callback, this](cocos2d::Ref*, TouchEventType type) {
        if (type == TouchEventType::BEGAN) {
            callback(currentTouch_, currentEvent_);
        }
    });
}

void ButtonEx::setTouchMovedCallback(const TouchCallback& callback) {
    addTouchEventListener([callback, this](cocos2d::Ref*, TouchEventType type) {
        if (type == TouchEventType::MOVED) {
            callback(currentTouch_, currentEvent_);
        }
    });
}

void ButtonEx::setTouchEndedCallback(const TouchCallback& callback) {
    addTouchEventListener([callback, this](cocos2d::Ref*, TouchEventType type) {
        if (type == TouchEventType::ENDED) {
            callback(currentTouch_, currentEvent_);
        }
    });
}

auto ButtonEx::getContainer() const noexcept -> const Widget* {
    return container_;
}

auto ButtonEx::getContainer() noexcept -> Widget* {
    return container_;
}

bool ButtonEx::init() {
    if (Button::init() == false) {
        return false;
    }
    return true;
}

bool ButtonEx::init(const std::string& normalImage,
                    const std::string& selectedImage,
                    const std::string& disableImage,
                    TextureResType texType) {
    if (Button::init(normalImage, selectedImage,
                     disableImage, texType) == false) {
        return false;
    }
    return true;
}

void ButtonEx::initRenderer() {
    Button::initRenderer();
    createTitleRenderer();
    
    std::vector<RefGuard> guards = {
        _buttonNormalRenderer,
        _buttonClickedRenderer,
        _buttonDisabledRenderer,
        _titleRenderer
    };
    
    // Remove all sprites and title and add to the internal container.
    removeProtectedChild(_buttonNormalRenderer);
    removeProtectedChild(_buttonClickedRenderer);
    removeProtectedChild(_buttonDisabledRenderer);
    removeProtectedChild(_titleRenderer);
    
    container_ = Widget::create();
    container_->ignoreContentAdaptWithSize(false);
    container_->setSwallowTouches(false);
    container_->setPropagateTouchEvents(true);
    container_->setFocusEnabled(false);
    container_->setPositionType(PositionType::PERCENT);
    container_->setPositionPercent(cocos2d::Vec2(0.5f, 0.5f));
    container_->setSizeType(SizeType::PERCENT);
    container_->setSizePercent(cocos2d::Vec2(1.0f, 1.0f));
    
    addProtectedChild(container_, std::numeric_limits<int>::min());
    
    container_->addProtectedChild(_buttonNormalRenderer);
    container_->addProtectedChild(_buttonClickedRenderer);
    container_->addProtectedChild(_buttonDisabledRenderer);
    container_->addProtectedChild(_titleRenderer);
}

void ButtonEx::onPressStateChangedToNormal() {
    // Hide all sprites.
    _buttonNormalRenderer->setVisible(false);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisabledRenderer->setVisible(false);
    
    if (_normalTextureLoaded) {
        _buttonNormalRenderer->setVisible(true);
        _buttonNormalRenderer->setState(cocos2d::ui::Scale9Sprite::State::NORMAL);
    } else {
        // None background.
    }
    
    container_->stopAllActions();
    
    if (_pressedActionEnabled) {
        // Zooming is enabled.
        auto zoomAction = cocos2d::ScaleTo::create(zoomingDuration_, 1.0f);
        container_->runAction(zoomAction);
    } else {
        container_->setScale(1.0f);
    }
}

void ButtonEx::onPressStateChangedToPressed() {
    // Hide all sprites.
    _buttonNormalRenderer->setVisible(false);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisabledRenderer->setVisible(false);
    
    if (_pressedTextureLoaded) {
        // Pressed texture is loaded.
        // Show pressed sprite.
        _buttonClickedRenderer->setVisible(true);
    } else {
        // Pressed texture is not loaded.
        if (_normalTextureLoaded) {
            // Use normal texture instead.
            _buttonNormalRenderer->setVisible(true);
            _buttonNormalRenderer->setState(cocos2d::ui::Scale9Sprite::State::NORMAL);
        } else {
            // None background.
        }
    }
    
    container_->stopAllActions();
    
    if (_pressedActionEnabled) {
        // Zooming is enabled.
        auto zoomAction = cocos2d::ScaleTo::create(zoomingDuration_,
                                                   1.0f + _zoomScale);
        container_->runAction(zoomAction);
    } else {
        // Instantly scaled.
        container_->setScale(1.0f + _zoomScale);
    }
}

void ButtonEx::onPressStateChangedToDisabled() {
    // Hide all sprites.
    _buttonNormalRenderer->setVisible(false);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisabledRenderer->setVisible(false);
    
    if (_disabledTextureLoaded) {
        // Disabled texture is loaded.
        // Show the disabled texture.
        _buttonDisabledRenderer->setVisible(true);
    } else {
        // Disabled texture is not loaded.
        if (_normalTextureLoaded) {
            // Normal texture is loaded.
            // Use the normal texture instead.
            // Gray out the normal sprite.
            _buttonNormalRenderer->setVisible(true);
            _buttonNormalRenderer->setState(cocos2d::ui::Scale9Sprite::State::GRAY);
        } else {
            // None background.
        }
    }
    
    // Stop animation and reset scale.
    container_->stopAllActions();
    container_->setScale(1.0f);
}

void ButtonEx::adaptRenderers() {
    updateTexture();
    Button::adaptRenderers();
}

auto ButtonEx::createCloneInstance() -> Widget* {
    return create();
}

void ButtonEx::copySpecialProperties(Widget* model) {
    auto button = dynamic_cast<ButtonEx*>(model);
    if (button != nullptr) {
        Button::copySpecialProperties(model);
        setZoomingDuration(button->getZoomingDuration());        
    }
}

void ButtonEx::updateTexture() {
    int counter = 0;
    
    if (_normalTextureAdaptDirty &&
        isBright() &&
        _brightStyle == BrightStyle::NORMAL) {
        onPressStateChangedToNormal();
        ++counter;
    }
    if (_pressedTextureAdaptDirty &&
        isBright() &&
        _brightStyle == BrightStyle::HIGHLIGHT) {
        onPressStateChangedToPressed();
        ++counter;
    }
    if (_disabledTextureAdaptDirty &&
        isBright() == false) {
        onPressStateChangedToDisabled();
        ++counter;
    }
    
    CC_ASSERT(counter <= 1);
}
NS_DETAIL_END
NS_EE_END