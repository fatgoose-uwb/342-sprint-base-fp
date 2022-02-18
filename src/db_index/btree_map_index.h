#pragma once

#include "Index.h"
#include <unordered_map>
#include <vector>
#include "../btree/map.h"

template<typename KeyType>
class BtreeMapIndex : public Index<KeyType> {
private:
    btree::map<KeyType, std::vector<unsigned>> index;

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
                                   std::vector<unsigned> &found_record_ids) override {

        if (lower_bound > upper_bound) {
            return;
        }

        auto it_lower_bound = index.lower_bound(lower_bound);
        auto it_upper_bound = index.upper_bound(upper_bound);

        for (auto it = it_lower_bound; it != it_upper_bound; ++it) {
            for (auto &id: it->second) {
                found_record_ids.push_back(id);
            }
        }
    }
};
