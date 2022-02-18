#pragma once

template<typename KeyType>
class Index {

public:
    virtual void insert_record(KeyType key, unsigned record_id) = 0;

    virtual void find_records(KeyType key, std::vector<unsigned> &found_record_ids) = 0;

    virtual void find_records_by_age_range(KeyType lower_bound,
                                           KeyType upper_bound,
                                           std::vector<unsigned> &found_record_ids) = 0;
};
