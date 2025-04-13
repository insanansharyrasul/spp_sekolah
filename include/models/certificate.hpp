#pragma once
#include <string>
class Certificate {
   private:
    size_t hash;
    std::string data;

   public:
    Certificate(size_t hash = 0, const std::string& data = "");
    size_t getHash() const;
    std::string getEncryptedData() const;
};