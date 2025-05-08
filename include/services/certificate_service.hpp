#pragma once
#include <repositories/certificate_repository.hpp>
#include <repositories/payment_repository.hpp>
#include <repositories/student_repository.hpp>

class CertificateService {
   private:
    PaymentRepository& paymentRepo;
    CertificateRepository& certificateRepo;
    StudentRepository& studentRepo;

    // Encryption and signature methods
    std::string encryptData(const std::string& data);
    size_t generateSignature(const std::string& data);

   public:
    CertificateService(PaymentRepository& paymentRepo,
                       CertificateRepository& certificateRepo,
                       StudentRepository& studentRepo);

    // Certificate operations
    std::string generateCertificate(const std::string& paymentId);
    bool validateCertificate(size_t signature);
    bool deleteCertificate(const std::string& certId);
    std::string decodeCertificate(size_t certificateHash);
};