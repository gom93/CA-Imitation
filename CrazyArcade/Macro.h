#pragma once

#define DECLARE_SINGLETON(Type)                                \
public:                                                        \
    static Type& Get()                                         \
    {                                                          \
        static Type instance;                                  \
        return instance;                                       \
    }                                                          \
private:                                                       \
    Type() = default;                                          \
    ~Type() = default;                                         \
    Type(const Type&) = delete;                                \
    Type& operator=(const Type&) = delete;