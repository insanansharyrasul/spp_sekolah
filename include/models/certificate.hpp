#pragma once
#include <string>
class Certificate {
   private:
    int hash;
    std::string encrypted_data;

   public:
    Certificate(int hash, const std::string& data);
    int getHash() const;
    std::string getEncryptedData() const;
};