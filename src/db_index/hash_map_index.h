#pragma once

#include "Index.h"
#include <unordered_map>

template<typename KeyType>
class HashMapIndex : public Index<KeyType> {
private:
    std::unordered_map<KeyType, std::vector<unsigned>> index;

public:
    void insert_record(KeyType key, unsigned record_id) override {
        index[key].push_back(record_id);
    }

    void find_records(KeyType key, std::vector<unsigned> &found_record_ids) override {
        if (index.find(key) == index.end()) {
            return;
        }
        found_record_ids = index[key];
    }

    void find_records_by_age_range(KeyType lower_bound,
                                   KeyType upper_bound,
                                   std::vector<unsigned int> &found_record_ids) override {
        throw std::runtime_error("range query in hash index is unsupported");
    }
};