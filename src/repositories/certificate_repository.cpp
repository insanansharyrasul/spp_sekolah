#include <fstream>
#include <repositories/certificate_repository.hpp>
#include <sstream>

CertificateRepository::CertificateRepository(const std::string& filePath) : dataFilePath(filePath) {
    loadFromFile();
}

// CRUD

std::string CertificateRepository::addCertificate(const Certificate& certificate) {
    if (certificates.find(certificate.getHash()) != certificates.end()) {
        return "";
    }
    certificates[certificate.getHash()] = certificate;
    saveToFile();
    return std::to_string(certificate.getHash());
}

Certificate* CertificateRepository::getCertificate(Certificate certificate) {
    auto it = certificates.find(certificate.getHash());
    if (it != certificates.end()) {
        return &it->second;
    }
    return nullptr;
}

bool CertificateRepository::removeCertificate(Certificate certificate) {
    auto it = certificates.find(certificate.getHash());
    if (it != certificates.end()) {
        certificates.erase(it);
        return saveToFile();
    }
    return false;
}

// Persistence
bool CertificateRepository::loadFromFile() {
    std::ifstream inFile(dataFilePath);
    if (!inFile.is_open()) {
        return false;  // Failed to open file
    }

    certificates.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        size_t hash;
        std::string data;

        ss >> hash;
        ss.ignore();
        std::getline(ss, data);

        Certificate certificate(hash, data);
        certificates[hash] = certificate;
    }
    inFile.close();
    return true;
}

bool CertificateRepository::saveToFile() {
    std::ofstream outFile(dataFilePath);
    if (!outFile.is_open()) {
        return false;  // Failed to open file
    }

    for (const auto& pair : certificates) {
        const Certificate& certificate = pair.second;
        outFile << certificate.getHash() << "," << certificate.getEncryptedData() << "\n";
    }
    outFile.close();
    return true;
}