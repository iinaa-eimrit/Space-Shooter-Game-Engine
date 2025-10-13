#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

class Config
{
private:
    std::unordered_map<std::string, std::string> settings;
    
public:
    bool loadFromFile(const std::string& filename);
    
    template<typename T>
    T get(const std::string& key, T defaultValue = T()) const;
    
    template<typename T>
    void set(const std::string& key, T value);
};

// Template implementations
template<typename T>
T Config::get(const std::string& key, T defaultValue) const
{
    auto it = settings.find(key);
    if (it != settings.end())
    {
        std::istringstream iss(it->second);
        T value;
        if (iss >> value)
        {
            return value;
        }
    }
    return defaultValue;
}

// Specialization for std::string
template<>
inline std::string Config::get<std::string>(const std::string& key, std::string defaultValue) const
{
    auto it = settings.find(key);
    if (it != settings.end())
    {
        return it->second;
    }
    return defaultValue;
}

// Specialization for bool
template<>
inline bool Config::get<bool>(const std::string& key, bool defaultValue) const
{
    auto it = settings.find(key);
    if (it != settings.end())
    {
        std::string value = it->second;
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        return (value == "true" || value == "1" || value == "yes");
    }
    return defaultValue;
}

template<typename T>
void Config::set(const std::string& key, T value)
{
    std::ostringstream oss;
    oss << value;
    settings[key] = oss.str();
}