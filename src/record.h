#pragma once

#include <string>
#include <unordered_set>

class GasWorksDB;

class Record {
    friend class GasWorksDB;

private:
    unsigned id;
    std::string name;
    unsigned age;
    std::unordered_set<std::string> hobbies;

public:

    Record() {}

    Record(const std::string &name, unsigned int age, const std::unordered_set<std::string> &hobbies) : name(name),
                                                                                                        age(age),
                                                                                                        hobbies(hobbies) {}

    bool operator==(const Record &rhs) const {
        return id == rhs.id &&
               name == rhs.name &&
               age == rhs.age &&
               hobbies == rhs.hobbies;
    }

    bool operator!=(const Record &rhs) const {
        return !(rhs == *this);
    }

    unsigned int get_id() const {
        return id;
    }

    const std::string &get_name() const {
        return name;
    }

    unsigned int get_age() const {
        return age;
    }

    const std::unordered_set<std::string> &get_hobbies() const {
        return hobbies;
    }
};