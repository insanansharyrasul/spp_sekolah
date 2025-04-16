#pragma once
#include <unordered_map>
#include <string>
#include <models/certificate.hpp>
class CertificateRepository {
   private:
    std::unordered_map<size_t, Certificate> certificates;  
    std::string dataFilePath;  
   public:
    CertificateRepository(const std::string& filePath);

    // CRUD
    std::string addCertificate(const Certificate& certificate);
    Certificate* getCertificate(Certificate certificate);
    bool removeCertificate(Certificate certificate);

    // Persistence
    bool loadFromFile();
    bool saveToFile();
};