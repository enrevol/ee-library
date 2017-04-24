//
//  EEManagedScene.hpp
//  ee-library
//
//  Created by Zinge on 4/24/17.
//
//

#ifndef EE_LIBRARY_MANAGED_SCENE_HPP_
#define EE_LIBRARY_MANAGED_SCENE_HPP_

#include <2d/CCScene.h>

namespace ee {
class SceneSwitcher;

class ManagedScene : public cocos2d::Scene {
private:
    using Super = cocos2d::Scene;

public:
    CREATE_FUNC(ManagedScene);

    virtual ~ManagedScene();

protected:
    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onExit() override;

private:
    friend SceneSwitcher;

    bool unloaded_;

    void unloadItems();
    void unloadImages();
    void unloadAtlases();

    std::vector<std::string> images_;
    std::vector<std::pair<std::string, std::string>> atlases_;
};
} // namespace ee

#endif /* EE_LIBRARY_MANAGED_SCENE_HPP_ */