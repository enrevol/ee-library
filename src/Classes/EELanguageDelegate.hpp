//
//  EELanguageDelegate.hpp
//  ee-library
//
//  Created by Zinge on 7/21/17.
//
//

#ifndef EE_LIBRARY_LANGUAGE_DELEGATE_HPP
#define EE_LIBRARY_LANGUAGE_DELEGATE_HPP

#include <functional>
#include <string>
#include <vector>

namespace ee {
class Language;

class LanguageDelegate {
private:
    using Self = LanguageDelegate;

public:
    using TextCallback = std::function<void(const std::string& text)>;

    LanguageDelegate();
    virtual ~LanguageDelegate();

    const Language& getLanguage() const;

    /// Sets the multilingual key.
    /// @param[in] key The multilingual key.
    /// @return Instance to this for chaining.
    Self* setKey(const std::string& key);

    /// Sets the format arguments.
    /// @param[in] args The format arguments.
    /// @return Instance to this for chaining.
    Self* setFormat(const std::vector<std::string>& args);

    /// Sets the display language.
    /// @param[in] language The desired language.
    /// @return Instance to this for chaining.
    Self* setLanguage(const Language& language);

    /// Sets the text callback.
    /// @param[in] callback The desired callback.
    /// @return Instance to this for chaining.
    Self* setTextCallback(const TextCallback& callback);

protected:
    std::unique_ptr<Language> language_;
    std::unique_ptr<std::string> key_;
    std::unique_ptr<std::vector<std::string>> args_;

private:
    TextCallback textCallback_;

    void updateText();
};
} // namespace ee

#endif /* EE_LIBRARY_LANGUAGE_DELEGATE_HPP */