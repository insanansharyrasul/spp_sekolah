#include <repositories/payment_repository.hpp>

class CertificateService {
   private:
    PaymentRepository& paymentRepo;

    // Encryption and signature methods
    std::string encryptData(const std::string& data);
    size_t generateSignature(const std::string& data);

   public:
    CertificateService(PaymentRepository& paymentRepo);

    // Certificate operations
    bool generateCertificate(const std::string& paymentId);
    bool validateCertificate(size_t signature);
};