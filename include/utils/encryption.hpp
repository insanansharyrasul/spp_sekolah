#pragma once
#include <string>

namespace Encryption
{
    const std::string DEFAULT_KEY = "icltspmo";
    std::string encrypt(const std::string &data, const std::string &key = DEFAULT_KEY);
    std::string decrypt(const std::string &data, const std::string &key = DEFAULT_KEY);
    size_t hash(const std::string &data);
}