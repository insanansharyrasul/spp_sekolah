#include <models/certificate.hpp>
#include <models/payment.hpp>
#include <repositories/certificate_repository.hpp>
#include <repositories/payment_repository.hpp>
#include <repositories/student_repository.hpp>
#include <services/certificate_service.hpp>
#include <utils/encryption.hpp>

CertificateService::CertificateService(PaymentRepository& paymentRepo,
                                       CertificateRepository& certificateRepo,
                                       StudentRepository& studentRepo) : paymentRepo(paymentRepo),
                                                                         certificateRepo(certificateRepo),
                                                                         studentRepo(studentRepo) {}

std::string CertificateService::encryptData(const std::string& data) {
    return Encryption::encrypt(data);
}

size_t CertificateService::generateSignature(const std::string& data) {
    return Encryption::hash(data);
}

bool CertificateService::validateCertificate(size_t signature) {
    Certificate* certificate = certificateRepo.getCertificate(Certificate(signature, ""));
    if (certificate == nullptr) {
        return false;
    }

    std::string decryptedData = encryptData(certificate->getEncryptedData());
    size_t generatedSignature = generateSignature(decryptedData);
    return generatedSignature == signature;
}

std::string CertificateService::decodeCertificate(size_t certificateHash) {
    Certificate* certificate = certificateRepo.getCertificate(Certificate(certificateHash, ""));
    if (certificate == nullptr) {
        return "";
    }
    
    // Decrypt the data using the same encryption function (XOR is its own inverse)
    std::string decryptedData = Encryption::decrypt(certificate->getEncryptedData());
    
    // Verify the certificate signature
    size_t calculatedHash = generateSignature(decryptedData);
    if (calculatedHash != certificate->getHash()) {
        return ""; // Invalid certificate
    }
    
    return decryptedData; // Format: paymentId,studentId,amount,deadline
}

std::string CertificateService::generateCertificate(const std::string& paymentId) {
    Payment* payment = paymentRepo.findById(paymentId);
    if (payment->getId() == "") {
        return "";
    }
    Student* student = studentRepo.findById(payment->getStudentId());
    if (student->getId() == 0) {
        return "";
    }

    std::string data = paymentId + "," +
                       std::to_string(student->getId()) + "," +
                       std::to_string(payment->getAmount()) + "," +
                       std::to_string(payment->getDeadline());
    std::string encryptedData = encryptData(data);
    size_t signature = generateSignature(data);

    Certificate certificate(signature, encryptedData);
    return certificateRepo.addCertificate(certificate);
}

bool CertificateService::deleteCertificate(const std::string& certId) {
    certificateRepo.removeCertificate(Certificate(std::stoull(certId), ""));
    return true;
}