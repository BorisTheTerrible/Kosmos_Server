#ifndef Environment_hpp
#define Environment_hpp

#include <stdio.h>

/*
    Checks compiler type at compile time.
 */
#if defined(__clang__)
    #define COMPILER "CLANG"
#elif defined(__GNUG__)
    #define COMPILER "GNU"
#elif defined(_MSC_VER)
    #define COMPILER "MSVC"
#else
    #warning "Compiling using unknown compiler! Will default to GNU compiler standards."
    #define COMPILER "GNU"
#endif

/*
    Checks operating system at compile time.
 */
#if defined(unix) || defined(__unix) || (__unix__)
    #define PLATFORM "UNIX_LIKE"
#elif defined(__APPLE__) || defined(__MACH__)
    #define PLATFORM "UNIX_LIKE"
#elif defined(__linux__)
    #define PLATFORM "UNIX_LIKE"
#elif defined(__FreeBSD__)
    #define PLATFORM "UNIX_LIKE"
#elif defined(_WIN32) && !defined(_WIN64)
    #define PLATFORM "WIN_32"
#elif defined(_WIN64)
    #define PLATFORM "WIN_64"
#else
    #warning "Compiling on unknown platform! Will default to compiling for UNIX-LIKE standards."
    #define PLATFORM "UNIX_LIKE"
#endif

/*
    Checks c++ support at compile time.
 */
#if __cplusplus < 201103L
    #warning "Your compiler is likely not c++11 compliant! Compilation will most likely fail!"
#endif

/*
    Checks library kind
 */
#ifdef _LIBCPP_VERSION
    #define LIB_KIND "LIBC++"
#else
    #define LIB_KIND "LIBSTDC++"
#endif

/*
    Checks GNU extensions support
 */
#if __cplusplus == 1
    #define EXTENSION_SUPPORT "GNU++"
#else
    #define EXTENSION_SUPPORT "NONE"
#endif

/*
    Checks to make sure variables types are of correct size at compile time.
 */
static_assert(sizeof(bool) == 1, "Type bool is not one byte!");
static_assert(sizeof(char) == 1, "Type char is not one byte!");
static_assert(sizeof(short) == 2,  "Type short is not two bytes!");
static_assert(sizeof(int) == 4, "Type int is not four bytes!");
static_assert(sizeof(long) == 8, "Type long is not eight bytes!");
static_assert(sizeof(float) == 4, "Type float is not four bytes!");
static_assert(sizeof(double) == 8, "Type double is not eight bytes!");

/*
    This class is never mean't to be instantianed.
    It is meant for runtime checks.

    It is marked as final so you cannot try to be silly and extend the class.
 */
class EnvironmentChecks final
{
public:
    bool getIsBigEndian();
//public

private:
     /*
        This is here to keep someone from being frisky and trying to instantiate this class.
     */
    virtual void f() = 0;

    /*
        This only used to call runtimeMethod() where runtime checks are run.
     */
    static int dummyVariable;

    static bool isBigEndian;

    /*
        Runtime checks should be placed in here.
        Runtime environment variables should be set in here.
     */
    static int runtimeMethod();
//private
};

#endif /* Environment_hpp */
