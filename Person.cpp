// Person.cpp
#include "Person.h"
#include <iostream>
#include "RideshareExceptions.h"

Person::Person(int id, const std::string& name, const Location& location)
    : id(id), name(name), location(location)
{
    if (name.empty())
        throw InvalidArgumentException("Person", "name cannot be empty");
    if (id < 0)
        throw InvalidArgumentException("Person", "ID cannot be negative");
}

int         Person::getId()       const { return id; }
std::string Person::getName()     const { return name; }
Location    Person::getLocation() const { return location; }

void Person::setLocation(const Location& newLocation) {
    location = newLocation;
}

void Person::display() const {
    std::cout << "[" << getRole() << "] "
              << name << " (ID: " << id << ")"
              << " at " << location.toString() << "\n";
}