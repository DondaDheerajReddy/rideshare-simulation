// Passenger.h
#pragma once
#include "Person.h"
#include <string>
#include <vector>

enum class PaymentMethod {
    CASH,
    CARD,
    WALLET
};

class Passenger : public Person {
private:
    PaymentMethod       paymentMethod;
    std::vector<int>    rideHistory;    // stores trip IDs
    double              balance;        // wallet balance if applicable

public:
    Passenger(int id, const std::string& name, const Location& location,
              PaymentMethod payment, double balance = 0.0);

    PaymentMethod           getPaymentMethod() const;
    double                  getBalance()       const;
    const std::vector<int>& getRideHistory()   const;

    void addRideToHistory(int tripId);
    bool deductBalance(double amount);    // returns false if insufficient funds

    std::string getRole()    const override;
    void        display()    const override;

    std::string paymentToString() const;
};