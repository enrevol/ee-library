//
//  EEBlurBackground.cpp
//  ee-library
//
//  Created by Zinge on 6/24/16.
//
//

/*

#include "EEBlurBackground.hpp"
#include "EEShader.hpp"

#include <cocos2d.h>

NS_EE_BEGIN
NS_ANONYMOUS_BEGIN

NS_ANONYMOUS_END
bool BlurBackground::init() {
    if (Node::init() == false) {
        return false;
    }

    renderScale_ = 1.0f;
    sigma_ = 2.0f;
    blurRadius_ = 4;
    useLinearSampling_ = false;
    rendererDirty_ = true;
    rendererInitialized_ = false;

    scheduleUpdate();
    return true;
}

void BlurBackground::updateRenderers() {
    if (rendererDirty_) {
        rendererDirty_ = false;
        resetRenderers();
        createRenderers();
    }
}

void BlurBackground::createRenderers() {
    CC_ASSERT(rendererInitialized_ == false);
    CC_ASSERT(horizontalRenderer_ == nullptr);
    CC_ASSERT(verticalRenderer_ == nullptr);

    auto&& winSize = _director->getWinSize();
    setContentSize(winSize);

    auto renderSize = winSize * renderScale_ / CC_CONTENT_SCALE_FACTOR();

    int width = static_cast<int>(std::ceil(renderSize.width));
    int height = static_cast<int>(std::ceil(renderSize.height));

    horizontalRenderer_ = cocos2d::RenderTexture::create(
        width, height, cocos2d::Texture2D::PixelFormat::RGBA8888,
        GL_DEPTH24_STENCIL8);

    verticalRenderer_ = cocos2d::RenderTexture::create(
        width, height, cocos2d::Texture2D::PixelFormat::RGBA8888,
        GL_DEPTH24_STENCIL8);

    configHorizontalRenderer();
    configVerticalRenderer();

    addChild(horizontalRenderer_, -1);
    addChild(verticalRenderer_, -1);

    rendererInitialized_ = true;
}

void BlurBackground::resetRenderers() {
    if (rendererInitialized_ == false) {
        return;
    }

    CC_ASSERT(horizontalRenderer_ != nullptr);
    CC_ASSERT(verticalRenderer_ != nullptr);

    horizontalRenderer_->removeFromParent();
    verticalRenderer_->removeFromParent();

    horizontalRenderer_ = nullptr;
    verticalRenderer_ = nullptr;

    rendererInitialized_ = false;
}

void BlurBackground::configHorizontalRenderer() {
    horizontalRenderer_->setKeepMatrix(true);
    horizontalRenderer_->setVisible(false);

    auto sprite = horizontalRenderer_->getSprite();
    auto texture = sprite->getTexture();

    float textureWidth = texture->getContentSizeInPixels().width;

    sprite->setGLProgram(Shader::createHorizontalBlurProgram(
        textureWidth, blurRadius_, useLinearSampling_, sigma_));
    sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
}

void BlurBackground::configVerticalRenderer() {
    verticalRenderer_->setScale(CC_CONTENT_SCALE_FACTOR() / renderScale_);

    auto sprite = verticalRenderer_->getSprite();
    auto texture = sprite->getTexture();

    if (renderScale_ / CC_CONTENT_SCALE_FACTOR() < 1.0f) {
        // Enable anti-alias because downsampling is used.
        // If anti-alias is not enabled, the resulting sprite will be blocky.
        texture->setAntiAliasTexParameters();
    } else {
        // Disable anti-alias.
        texture->setAliasTexParameters();
    }

    float textureHeight = texture->getContentSizeInPixels().height;

    sprite->setGLProgram(Shader::createVerticalBlurProgram(
        textureHeight, blurRadius_, useLinearSampling_, sigma_));
    sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
}

void BlurBackground::setRenderScale(float scale) {
    if (renderScale_ == scale) {
        return;
    }
    renderScale_ = scale;
    rendererDirty_ = true;
}

void BlurBackground::setBlurRadius(int radius) {
    if (blurRadius_ == radius) {
        return;
    }
    blurRadius_ = radius;
    rendererDirty_ = true;
}

void BlurBackground::setSigma(float sigma) {
    if (sigma_ == sigma) {
        return;
    }
    sigma_ = sigma;
    rendererDirty_ = true;
}

void BlurBackground::setUseLinearSampling(bool use) {
    if (useLinearSampling_ == use) {
        return;
    }
    useLinearSampling_ = use;
    rendererDirty_ = true;
}

void BlurBackground::update(float delta) {
    if (isVisible()) {
        updateRenderers();

        setVisible(false);
        horizontalRenderer_->beginWithClear(0, 0, 0, 0);

        auto scene = _director->getRunningScene();
        scene->visit();

        horizontalRenderer_->end();
        setVisible(true);

        verticalRenderer_->beginWithClear(0, 0, 0, 0);
        horizontalRenderer_->getSprite()->visit();
        verticalRenderer_->end();

        // Force render immediately to prevent crashs when switching scenes.
        _director->getRenderer()->render();
    }
}

void BlurBackground::visit(cocos2d::Renderer* renderer,
                           const cocos2d::Mat4& parentTransforms,
                           std::uint32_t parentFlags) {
    Node::visit(renderer, parentTransforms, parentFlags);
}
NS_EE_END

*/
