#include "unit_test_db_perf_common.h"

using namespace std::chrono;

unsigned random_unsigned(const unsigned min, const unsigned max) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<unsigned> distr(min, max);

    return distr(eng);
}

std::string random_int_in_string(const unsigned min, const unsigned max) {
    return std::to_string(random_unsigned(min, max));
}

void prepare_db_for_perf_test(GasWorksDB &hash_indexed_db, GasWorksDB &btree_indexed_db, unsigned table_size,
                              unsigned HOBBY_TYPE_COUNT, unsigned MIN_HOBBY_COUNT, unsigned AGE_MAX,
                              std::vector<Record *> &records) {
    for (int i = 0; i < table_size; ++i) {
        /*
         * create a set of hobbies
         */
        auto HOBBY_COUNT_PER_PERSON = random_unsigned(MIN_HOBBY_COUNT, HOBBY_TYPE_COUNT);
        std::unordered_set<std::string> hobbies;
        for (int j = 0; j < HOBBY_COUNT_PER_PERSON; ++j) {
            hobbies.insert(random_int_in_string(1, HOBBY_TYPE_COUNT));
        }

        /*
         * create a new record
         */
        records.push_back(
                new Record(
                        "name-" + random_int_in_string(1, table_size),  // up to record_count unique names
                        random_unsigned(1, AGE_MAX),    // age from 1 - AGE_MAX
                        hobbies
                )
        );
    }

    for (auto record: records) {
        hash_indexed_db.insert_record(*record);
        btree_indexed_db.insert_record(*record);
    }
}

TEST(final_project, btree_range_search) {

    std::unordered_map<int, std::string> expect = {
            {50, "123"},
            {52, "456"},
            {55, "789"},
    };

    btree::map<int, std::string> index;
    index[0] = "abc";
    index[100] = "xyz";
    for (auto &kv: expect) {
        index[kv.first] = kv.second;
    }

    auto it_lower_bound = index.lower_bound(50);
    auto it_upper_bound = index.upper_bound(60);

    for (auto it = it_lower_bound; it != it_upper_bound; ++it) {
        ASSERT_EQ(expect[it->first], it->second);
    }
}
