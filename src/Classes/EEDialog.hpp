//
//  EEDialog.h
//  roll-eat
//
//  Created by Hoang Le Hai on 9/1/15.
//
//

#ifndef EE_LIBRARY_DIALOG_H
#define EE_LIBRARY_DIALOG_H

#include <functional>
#include <memory>
#include <vector>

#include "EEMacro.hpp"
#include "EECocos2dxFwd.hpp"

#include <ui/UIWidget.h>

NS_EE_BEGIN
namespace dialog {
class Dialog;
} // namespace dialog

using dialog::Dialog;

namespace dialog {
class Dialog : public cocos2d::ui::Widget {
public:
    using CallbackType = std::function<void(Dialog*)>;
    
    using TransitionType = cocos2d::FiniteTimeAction;
    using TransitionRef = cocos2d::RefPtr<TransitionType>;
    
    template<class... Args>
    using enable_if_args_are_transition_types =
        std::enable_if_t<
            (std::is_base_of<
                TransitionType,
                std::remove_pointer_t<std::decay_t<Args>>
             >::value && ...)
        >;
    
    static const int ContainerLocalZOrder;
    static const std::size_t TopLevel;
    
    virtual void show(std::size_t level = TopLevel);
    
    virtual void hide();
    
    std::size_t getDialogLevel() const noexcept;
    
    virtual const cocos2d::Node* getContainer() const;
    virtual cocos2d::Node* getContainer();
    
    virtual void setActive(bool active);
    
    bool isActive() const noexcept;

    virtual Dialog* addDialogWillShowCallback(const CallbackType& callback,
                                              int priority = 0);
    
    virtual Dialog* addDialogDidShowCallback(const CallbackType& callback,
                                             int priority = 0);
    
    virtual Dialog* addDialogWillHideCallback(const CallbackType& callback,
                                              int priority = 0);
    
    virtual Dialog* addDialogDidHideCallback(const CallbackType& callback,
                                             int priority = 0);
    
    void setShowingTransitions(const std::vector<TransitionRef>& transitions);
    void setHidingTransitions(const std::vector<TransitionRef>& transitions);
    
    void addShowingTransitions(const std::vector<TransitionRef>& transitions);
    void addHidingTransitions(const std::vector<TransitionRef>& transitions);
    
    const std::vector<TransitionRef>& getShowingTransitions() const;
    const std::vector<TransitionRef>& getHidingTransitions() const;
    
    template<class... Transitions>
    enable_if_args_are_transition_types<Transitions...>
    setShowingTransitions(Transitions&&... transitions) {
        setShowingTransitions({ std::forward<Transitions>(transitions)... });
    }
    
    template<class... Transitions>
    enable_if_args_are_transition_types<Transitions...>
    setHidingTransitions(Transitions&&... transitions) {
        setHidingTransitions({ std::forward<Transitions>(transitions)... });
    }
    
    template<class... Transitions>
    enable_if_args_are_transition_types<Transitions...>
    addShowingTransitions(Transitions&&... transitions) {
        addShowingTransitions({ std::forward<Transitions>(transitions)... });
    }
    
    template<class... Transitions>
    enable_if_args_are_transition_types<Transitions...>
    addHidingTransitions(Transitions&&... transitions) {
        addHidingTransitions({ std::forward<Transitions>(transitions)... });
    }
    
protected:
    friend class DialogManager;
    
    virtual bool init() override;

    virtual void onEnter() override;
    virtual void onExit() override;    
    
    /// Invoked when the user clicked the outside boundary of this dialog.
    virtual void onClickedOutside();
    
    virtual void onDialogWillShow();
    virtual void onDialogDidShow();
    virtual void onDialogWillHide();
    virtual void onDialogDidHide();
    
private:
    using CallbackInfo = std::pair<CallbackType, int>;
    
    virtual bool hitTest(const cocos2d::Point& pt,
                         const cocos2d::Camera* camera,
                         cocos2d::Vec3* p) const override;
    
    void invokeCallbacks(std::vector<CallbackInfo>& callbacks);
    
    std::size_t dialogLevel_;
    bool isActive_;
    
    std::vector<TransitionRef> showingTransitions_;
    std::vector<TransitionRef> hidingTransitions_;
    
    std::vector<CallbackInfo> onDialogWillShowCallbacks_;
    std::vector<CallbackInfo> onDialogDidShowCallbacks_;
    std::vector<CallbackInfo> onDialogWillHideCallbacks_;
    std::vector<CallbackInfo> onDialogDidHideCallbacks_;
};
} // namespace dialog.
NS_EE_END

#endif /* EE_LIBRARY_DIALOG_H */
