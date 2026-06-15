// Passenger.cpp
#include "Passenger.h"
#include <iostream>

Passenger::Passenger(int id, const std::string& name, const Location& location,
                     PaymentMethod payment, double balance)
    : Person(id, name, location),
      paymentMethod(payment),
      balance(balance) {}

PaymentMethod           Passenger::getPaymentMethod() const { return paymentMethod; }
double                  Passenger::getBalance()       const { return balance; }
const std::vector<int>& Passenger::getRideHistory()   const { return rideHistory; }

void Passenger::addRideToHistory(int tripId) {
    rideHistory.push_back(tripId);
}

bool Passenger::deductBalance(double amount) {
    if (paymentMethod == PaymentMethod::WALLET && balance < amount)
        return false;
    balance -= amount;
    return true;
}

std::string Passenger::paymentToString() const {
    switch (paymentMethod) {
        case PaymentMethod::CASH:   return "Cash";
        case PaymentMethod::CARD:   return "Card";
        case PaymentMethod::WALLET: return "Wallet";
        default:                    return "Unknown";
    }
}

std::string Passenger::getRole() const { return "Passenger"; }

void Passenger::display() const {
    Person::display();
    std::cout << "  Payment : " << paymentToString()
              << " | Balance: $" << balance
              << " | Rides taken: " << rideHistory.size() << "\n";
}