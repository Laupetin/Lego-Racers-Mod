#pragma once

template<typename T> class Singleton
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

    Singleton() = default;
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;
};
