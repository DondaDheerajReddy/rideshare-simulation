// Person.h
#pragma once
#include <string>
#include "Location.h"

class Person {
protected:
    int         id;
    std::string name;
    Location    location;

public:
    Person(int id, const std::string& name, const Location& location);
    virtual ~Person() = default;   // virtual destructor — critical for base classes

    int         getId()       const;
    std::string getName()     const;
    Location    getLocation() const;

    void setLocation(const Location& newLocation);

    virtual std::string getRole() const = 0;   // pure virtual — Person alone is abstract
    virtual void        display() const;
};