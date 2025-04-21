#include <iostream>
#include <string>

namespace Encryption {

std::string encrypt(const std::string &data, const std::string &key) {
    std::string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}

std::string decrypt(const std::string &data, const std::string &key) {
    return encrypt(data, key);
}

size_t hash(const std::string &data) {
    return std::hash<std::string>{}(data);
}  

}