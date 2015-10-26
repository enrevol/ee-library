//
//  EEJni.h
//  roll-eat
//
//  Created by enrevol on 9/28/15.
//
//

#ifndef EE_LIBRARY_JNI_H
#define EE_LIBRARY_JNI_H

#include "EEMacro.hpp"

#include <jni.h>

namespace_ee_begin
class JniString {
public:
    JniString(JNIEnv* env, jstring javaString)
        : _env(env)
        , _javaString(javaString)
        , _nativeString(env->GetStringUTFChars(_javaString, JNI_FALSE)) {}
    
    ~JniString() {
        _env->ReleaseStringUTFChars(_javaString, _nativeString);
    }
    
    operator const char*() const {
        return _nativeString;
    }
    
    JniString(const JniString&) = delete;
    JniString(JniString&&) = delete;
    JniString& operator=(const JniString&) = delete;
    JniString& operator=(JniString&&) = delete;
    
private:
    JNIEnv* _env;
    jstring _javaString;
    const char* _nativeString;
};
namespace_ee_end

#endif // EE_LIBRARY_JNI_H
