#include <payment.hpp>
#include <string>
#include <unordered_map>
#include <vector>
class PaymentRepository {
   private:
    std::unordered_map<std::string, Payment> payments;
    std::unordered_multimap<int, std::string> studentPaymentIndex;  // For faster lookup by student ID
    std::string dataFilePath;

   public:
    PaymentRepository(const std::string& filePath);

    // CRUD operations
    bool add(const Payment& payment);
    Payment* findById(const std::string& id);
    std::vector<Payment> findByStudentId(int studentId);
    std::vector<Payment> findAll();

    // Specialized queries
    std::vector<Payment> findOverduePayments();
    std::vector<Payment> findPaymentsByMonth(int year, int month);

    // Persistence
    bool loadFromFile();
    bool saveToFile();
};