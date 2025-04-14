#include <string>
#include <utils/encryption.hpp>
#include <models/certificate.hpp>

Certificate::Certificate(size_t hash, const std::string& data) : hash(hash), data(data) {}

size_t Certificate::getHash() const {
    return hash;
}

std::string Certificate::getEncryptedData() const {
    return data;
}