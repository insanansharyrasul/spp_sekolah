#include <string>
class Certificate {
   private:
    int hash;
    std::string encrypted_data;

   public:
    Certificate(int hash, const std::string& data) : hash(hash), encrypted_data(data) {}
    int getHash() const { return hash; }
    std::string getEncryptedData() const { return encrypted_data; }
};