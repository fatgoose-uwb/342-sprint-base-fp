#pragma once

#include "btree/map.h"
#include "record.h"
#include "db_index/Index.h"
#include "db_index/index_group.h"
#include <vector>

class GasWorksDB {
private:
    std::vector<Record> table;

    bool enable_index = false;

    // indexes for better read performance
    // another example of DI (dependency inversion) here.
    IndexGroupInterface *index_group;

    void update_index(const Record &new_record, unsigned record_id);

    static std::string hobbies_key_hasher(std::unordered_set<std::string> hobbies);

public:
    GasWorksDB(IndexGroupInterface *indexGroup) : index_group(indexGroup) {}

    void insert_record(Record new_record_to_insert);

    bool find_by_name(const std::string &name, std::vector<Record> &found_records);

    bool find_by_id(unsigned int id, Record &found_record);

    bool find_by_age(unsigned age, std::vector<Record> &found_records);

    bool find_by_age_range(unsigned age_lower_bound, unsigned age_upper_bound, std::vector<Record> &found_records);

    bool find_by_hobbies(const std::unordered_set<std::string> &hobbies, std::vector<Record> &found_records);

    bool operator==(const GasWorksDB &rhs) const {
        return table == rhs.table;
    }

    bool operator!=(const GasWorksDB &rhs) const {
        return !(rhs == *this);
    }

    unsigned count() {
        return table.size();
    }

    bool is_empty() {
        return count() == 0;
    }

    bool get_enable_index() const;

    void set_enable_index(bool enableIndex);

    virtual ~GasWorksDB() {
        delete index_group;
    };
};