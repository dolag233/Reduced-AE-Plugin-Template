//
//  ADOBE CONFIDENTIAL
//  __________________
//
//  Copyright 2016 Adobe
//  All Rights Reserved.
//
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe and its suppliers, if any. The intellectual
//  and technical concepts contained herein are proprietary to Adobe
//  and its suppliers and are protected by all applicable intellectual
//  property laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe.
//

#ifndef ARTEMIS_PLATFORM_HPP
#define ARTEMIS_PLATFORM_HPP

/*
    The ARTEMIS_PLATFORM() macro is used to conditionalize code based on platform or platform
    attibutes.

    It is used as:

    #if ARTEMIS_PLATFORM(MACOS)
    #endif

    The attributes currently create a hierarchy from general to specific, items lower in the
    hierarchy imply their parent are defined as '1', all others are '0'.

    This graph may eventually become a DAG. Higher level nodes represent a set of services that the
    lower level nodes have in common. As such, it should rarely be necessary to write an expression
    using more than one of these terms. If you find yourself doing so, please name the common
    service and add the flag.

    An unqualified else clause should only be written entirely in terms of standard constructs that
    has no platform dependencies and should not assume that 'not X' implies some other 'Y'.

    POSIX - any Posix compliant platform
        APPLE - any Apple platform
            MACOS - compiled for macOS
            IOS - compiled for iOS
        LINUX - compiled for Linux
        ANDROID - compiled for Android
    MICROSOFT - any Microsoft platform
        UWP - Compiled for UWP
        WIN32 - Compiled for Win32
*/
#define ARTEMIS_PLATFORM(X) (ARTEMIS_PRIVATE_PLATFORM_##X())

/**************************************************************************************************/

// The *_PRIVATE_* macros are just that. Don't use them directly.

#define ARTEMIS_PRIVATE_PLATFORM_ANDROID() 0
#define ARTEMIS_PRIVATE_PLATFORM_WEB() 0
#define ARTEMIS_PRIVATE_PLATFORM_APPLE() 0
#define ARTEMIS_PRIVATE_PLATFORM_IOS() 0
#define ARTEMIS_PRIVATE_PLATFORM_LINUX() 0
#define ARTEMIS_PRIVATE_PLATFORM_MACOS() 0
#define ARTEMIS_PRIVATE_PLATFORM_MICROSOFT() 0
#define ARTEMIS_PRIVATE_PLATFORM_POSIX() 0
#define ARTEMIS_PRIVATE_PLATFORM_UWP() 0
#define ARTEMIS_PRIVATE_PLATFORM_WIN32() 0

#if defined(__ANDROID__)
    #undef ARTEMIS_PRIVATE_PLATFORM_POSIX
    #define ARTEMIS_PRIVATE_PLATFORM_POSIX() 1
    #undef ARTEMIS_PRIVATE_PLATFORM_ANDROID
    #define ARTEMIS_PRIVATE_PLATFORM_ANDROID() 1
#elif defined(_WIN32)
    #include <sdkddkver.h> // for #define WINVER
    #include <winapifamily.h>

    #undef ARTEMIS_PRIVATE_PLATFORM_MICROSOFT
    #define ARTEMIS_PRIVATE_PLATFORM_MICROSOFT() 1

    #if defined(WINAPI_FAMILY) && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
        #undef ARTEMIS_PRIVATE_PLATFORM_UWP
        #define ARTEMIS_PRIVATE_PLATFORM_UWP() 1
    #else
        #undef ARTEMIS_PRIVATE_PLATFORM_WIN32
        #define ARTEMIS_PRIVATE_PLATFORM_WIN32() 1
    #endif
#elif defined(__APPLE__) && !defined (__SIMULATED_WASM__)
    #include "TargetConditionals.h"

    #undef ARTEMIS_PRIVATE_PLATFORM_POSIX
    #define ARTEMIS_PRIVATE_PLATFORM_POSIX() 1
    #undef ARTEMIS_PRIVATE_PLATFORM_APPLE
    #define ARTEMIS_PRIVATE_PLATFORM_APPLE() 1

    #if TARGET_OS_SIMULATOR || TARGET_OS_IPHONE
        #undef ARTEMIS_PRIVATE_PLATFORM_IOS
        #define ARTEMIS_PRIVATE_PLATFORM_IOS() 1
    #elif TARGET_OS_MAC
        #undef ARTEMIS_PRIVATE_PLATFORM_MACOS
        #define ARTEMIS_PRIVATE_PLATFORM_MACOS() 1
    #endif
#elif defined(__LINUX__)
    #undef ARTEMIS_PRIVATE_PLATFORM_POSIX
    #define ARTEMIS_PRIVATE_PLATFORM_POSIX() 1
    #undef ARTEMIS_PRIVATE_PLATFORM_LINUX
    #define ARTEMIS_PRIVATE_PLATFORM_LINUX() 1
#elif defined(__EMSCRIPTEN__) || defined (__SIMULATED_WASM__)
    #undef ARTEMIS_PRIVATE_PLATFORM_POSIX
    #define ARTEMIS_PRIVATE_PLATFORM_POSIX() 1
    #undef ARTEMIS_PRIVATE_PLATFORM_WEB
    #define ARTEMIS_PRIVATE_PLATFORM_WEB() 1
#endif

#endif // ARTEMIS_PLATFORM_HPP
