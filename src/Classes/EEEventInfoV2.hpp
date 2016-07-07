//
//  EEEventV2.hpp
//  ee-library
//
//  Created by Zinge on 7/7/16.
//
//

#ifndef EE_LIBRARY_EVENT_INFO_HPP_
#define EE_LIBRARY_EVENT_INFO_HPP_

#include <functional>
#include <tuple>

namespace ee {
template <int EventId, class... Args> class EventInfo final {
public:
    using ArgTypes = std::tuple<Args...>;
    using CallbackType = std::function<void(Args...)>;

    enum { Id = EventId };

    static const std::string& getKey() {
        static const std::string key = "__EE_EVENT__" + std::to_string(Id);
        return key;
    }
};
} // namespace ee

#endif /* EE_LIBRARY_EVENT_INFO_HPP_ */