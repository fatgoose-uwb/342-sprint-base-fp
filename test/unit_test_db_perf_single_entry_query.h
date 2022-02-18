#include "gtest/gtest.h"
#include "btree/map.h"
#include "db_index/hash_map_index.h"
#include "unit_test_db_perf_common.h"

long long run_single_entry_query_test(GasWorksDB &db,
                                      Record *&record_to_search,
                                      std::vector<Record> &found_record) {
    auto start = high_resolution_clock::now();

    db.find_by_hobbies(record_to_search->get_hobbies(), found_record);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count();
}

/*
 * TODO: fix memory leak
 */
void run_index_perf_single_entry_query(unsigned table_size,
                                       unsigned MIN_HOBBY_COUNT,
                                       unsigned HOBBY_TYPE_COUNT,
                                       unsigned AGE_MAX) {
    if (table_size == 0) {
        return;
    }

    GasWorksDB hash_indexed_db(new HashIndexGroup());
    hash_indexed_db.set_enable_index(true);

    GasWorksDB btree_indexed_db(new BtreeIndexGroup());
    btree_indexed_db.set_enable_index(true);

    std::vector<Record *> records;
    prepare_db_for_perf_test(hash_indexed_db,
                             btree_indexed_db,
                             table_size, HOBBY_TYPE_COUNT, MIN_HOBBY_COUNT, AGE_MAX, records);

    auto &record_to_search = records.back();

    /*
     * test search using hash indexed db
     */
    std::vector<Record> found_records_hash_index;
    auto hash_index_time = run_single_entry_query_test(hash_indexed_db, record_to_search,
                                                       found_records_hash_index);

    /*
     * test search using btree indexed db
     */
    std::vector<Record> found_records_btree_index;
    auto btree_index_time = run_single_entry_query_test(btree_indexed_db, record_to_search,
                                                        found_records_btree_index);

    /*
     * test search without index
     */
    std::vector<Record> found_records_no_index;
    hash_indexed_db.set_enable_index(false);
    auto no_index_time = run_single_entry_query_test(hash_indexed_db, record_to_search, found_records_no_index);

    /*
     * validate consistent search results regardless of db
     */
    ASSERT_TRUE(!found_records_no_index.empty());
    ASSERT_TRUE(!found_records_hash_index.empty());
    ASSERT_TRUE(!found_records_btree_index.empty());
    ASSERT_EQ(found_records_no_index, found_records_hash_index);
    ASSERT_EQ(found_records_no_index, found_records_btree_index);

    /*
     * print out times
     */
    std::cout << table_size << ","
              << hash_index_time
              << ","
              << btree_index_time
              << ","
              << no_index_time
              << std::endl;
}