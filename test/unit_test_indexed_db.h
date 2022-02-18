#include "gtest/gtest.h"
#include "db.h"
#include "db_index/hash_map_index.h"

void verify_record_without_id(const Record &expect_record, const Record &actual_record) {
    ASSERT_EQ(expect_record.get_name(), actual_record.get_name());
    ASSERT_EQ(expect_record.get_age(), actual_record.get_age());
    ASSERT_EQ(expect_record.get_hobbies(), actual_record.get_hobbies());
}

void prepare_db(GasWorksDB &db, std::vector<Record> &new_records, bool enable_index) {
    std::vector<Record> records = {
            Record("coco", 20, {"playing", "eating"}),
            Record("sam", 15, {"jogging"}),
            Record("coco", 8, {"racing"}),
            Record("james", 15, {"movie", "swimming"}),
            Record("tom", 10, {"eating", "playing"}),
            Record("coco", 35, {"car", "cat", "code"}),
            Record("coco", 35, {"car", "cat", "code"}),// considered a different recorded as above
    };

    // set db index mode
    db.set_enable_index(enable_index);

    // insert records
    for (auto &record: records) {
        // add as "expect"
        new_records.push_back(record);

        // insert into db
        // this step also insert record into index regardless of enable_index being true or false
        db.insert_record(record);
    }

    ASSERT_FALSE(db.is_empty());
    ASSERT_EQ(records.size(), db.count());
    ASSERT_EQ(records.size(), new_records.size());
    ASSERT_EQ(enable_index, db.get_enable_index());
}

template<typename IndexType>
void test_db_initialization(bool enable_index) {
    GasWorksDB db(new IndexType());
    db.set_enable_index(enable_index);

    ASSERT_TRUE(db.is_empty());
    ASSERT_EQ(0, db.count());
}

template<typename IndexType>
void test_db_insert_first_record(bool enable_index) {
    GasWorksDB db(new IndexType());
    db.set_enable_index(enable_index);

    // insert one record
    Record new_record("coco", 2, {"playing", "eating"});
    db.insert_record(new_record);

    ASSERT_FALSE(db.is_empty());
    ASSERT_EQ(1, db.count());

    // validate the content of the record
    std::vector<Record> found_records;

    // search by age
    ASSERT_FALSE(db.find_by_age(3, found_records));
    ASSERT_TRUE(found_records.empty());

    ASSERT_TRUE(db.find_by_age(2, found_records));
    ASSERT_EQ(1, found_records.size());

    ASSERT_EQ(0, found_records[0].get_id());  // only one record, starts from 0
    verify_record_without_id(new_record, found_records[0]);
    found_records.clear();

    // search by name
    ASSERT_FALSE(db.find_by_name("abc", found_records));
    ASSERT_TRUE(found_records.empty());

    ASSERT_TRUE(db.find_by_name("coco", found_records));
    ASSERT_EQ(1, found_records.size());

    ASSERT_EQ(0, found_records[0].get_id());  // only one record, starts from 0
    verify_record_without_id(new_record, found_records[0]);
    found_records.clear();

    // search by id
    Record a_found_record;
    ASSERT_FALSE(db.find_by_id(3, a_found_record));

    ASSERT_TRUE(db.find_by_id(0, a_found_record));

    ASSERT_EQ(0, a_found_record.get_id());  // only one record, starts from 0
    verify_record_without_id(new_record, a_found_record);
}

template<typename IndexType>
void test_db_multiple_records_search_by_id(bool enable_index) {
    // prepare db
    GasWorksDB db(new IndexType());
    std::vector<Record> new_records;
    prepare_db(db, new_records, enable_index);

    // search by id
    for (int i = 0; i < new_records.size(); i++) {
        Record a_found_record;
        ASSERT_FALSE(db.find_by_id(new_records.size() + i, a_found_record));
        ASSERT_TRUE(db.find_by_id(i, a_found_record));

        ASSERT_EQ(i, a_found_record.get_id());  // only one record, starts from 0
        verify_record_without_id(new_records[i], a_found_record);
    }
}

template<typename IndexType>
void test_db_multiple_records_search_by_age(bool enable_index) {
    // prepare db
    GasWorksDB db(new IndexType());
    std::vector<Record> new_records;
    prepare_db(db, new_records, enable_index);

    // validate the content of the record
    std::vector<Record> found_records;

    // single answer
    ASSERT_FALSE(db.find_by_age(3, found_records));
    ASSERT_TRUE(found_records.empty());

    ASSERT_TRUE(db.find_by_age(8, found_records));
    ASSERT_EQ(1, found_records.size());

    int expect_id = 2;
    ASSERT_EQ(expect_id, found_records[0].get_id());
    verify_record_without_id(new_records[expect_id], found_records[0]);

    // multiple answers
    found_records.clear();
    ASSERT_TRUE(db.find_by_age(15, found_records));
    ASSERT_EQ(2, found_records.size());

    std::set<int> expect_ids = {1, 3};
    std::set<int> actual_ids;
    std::vector<int> ids;

    for (auto &record: found_records) {
        actual_ids.insert(record.get_id());
        ids.push_back(record.get_id());
    }
    ASSERT_EQ(expect_ids, actual_ids);

    std::sort(ids.begin(), ids.end());
    for (int i = 0; i < ids.size(); ++i) {
        verify_record_without_id(new_records[ids[i]], found_records[i]);
    }
}

template<typename IndexType>
void test_db_multiple_records_search_by_name(bool enable_index) {
    // prepare db
    GasWorksDB db(new IndexType());
    std::vector<Record> new_records;
    prepare_db(db, new_records, enable_index);

    // validate the content of the record
    std::vector<Record> found_records;

    // single answer
    ASSERT_FALSE(db.find_by_name("seattle", found_records));
    ASSERT_TRUE(found_records.empty());

    ASSERT_TRUE(db.find_by_name("james", found_records));
    ASSERT_EQ(1, found_records.size());

    int expect_id = 3;
    ASSERT_EQ(expect_id, found_records[0].get_id());
    verify_record_without_id(new_records[expect_id], found_records[0]);

    // multiple answers
    found_records.clear();
    ASSERT_TRUE(db.find_by_name("coco", found_records));
    ASSERT_EQ(4, found_records.size());

    std::set<int> expect_ids = {0, 2, 5, 6};
    std::set<int> actual_ids;
    std::vector<int> ids;

    for (auto &record: found_records) {
        actual_ids.insert(record.get_id());
        ids.push_back(record.get_id());
    }
    ASSERT_EQ(expect_ids, actual_ids);

    std::sort(ids.begin(), ids.end());
    for (int i = 0; i < ids.size(); ++i) {
        verify_record_without_id(new_records[ids[i]], found_records[i]);
    }
}

template<typename IndexType>
void db_multiple_records_search_by_hobbies_single_answer(bool enable_index) {
    // prepare db
    GasWorksDB db(new IndexType());
    std::vector<Record> new_records;
    prepare_db(db, new_records, enable_index);

    // validate the content of the record
    std::vector<Record> found_records;

    // single answer, single hobby
    ASSERT_FALSE(db.find_by_hobbies({"chess"}, found_records));
    ASSERT_TRUE(found_records.empty());

    ASSERT_TRUE(db.find_by_hobbies({"racing"}, found_records));
    ASSERT_EQ(1, found_records.size());

    int expect_id = 2;
    ASSERT_EQ(expect_id, found_records[0].get_id());
    verify_record_without_id(new_records[expect_id], found_records[0]);

    // single answer, multiple hobbies
    found_records.clear();
    ASSERT_FALSE(db.find_by_hobbies({"movie", "smoking"}, found_records));
    ASSERT_TRUE(found_records.empty());

    ASSERT_TRUE(db.find_by_hobbies({"movie", "swimming"}, found_records));
    ASSERT_EQ(1, found_records.size());

    expect_id = 3;
    ASSERT_EQ(expect_id, found_records[0].get_id());
    verify_record_without_id(new_records[expect_id], found_records[0]);

    // single answer, multiple hobbies, different order
    found_records.clear();
    ASSERT_FALSE(db.find_by_hobbies({"smoking", "movie"}, found_records));
    ASSERT_TRUE(found_records.empty());

    ASSERT_TRUE(db.find_by_hobbies({"swimming", "movie"}, found_records));
    ASSERT_EQ(1, found_records.size());

    ASSERT_EQ(expect_id, found_records[0].get_id());
    verify_record_without_id(new_records[expect_id], found_records[0]);
}

template<typename IndexType>
void test_db_multiple_records_search_by_hobbies_multiple_answer(bool enable_index) {
    // prepare db
    GasWorksDB db(new IndexType());
    std::vector<Record> new_records;
    prepare_db(db, new_records, enable_index);

    // validate the content of the record
    std::vector<Record> found_records;

    // multiple answers
    ASSERT_TRUE(db.find_by_hobbies({"eating", "playing"}, found_records));
    ASSERT_EQ(2, found_records.size());

    std::set<int> expect_ids = {0, 4};
    std::set<int> actual_ids;
    std::vector<int> ids;

    for (auto &record: found_records) {
        actual_ids.insert(record.get_id());
        ids.push_back(record.get_id());
    }
    ASSERT_EQ(expect_ids, actual_ids);

    std::sort(ids.begin(), ids.end());
    for (int i = 0; i < ids.size(); ++i) {
        verify_record_without_id(new_records[ids[i]], found_records[i]);
    }
}

template<typename IndexType>
void test_db_multiple_records_search_by_hobbies_no_partial_match(bool enable_index) {
    // prepare db
    GasWorksDB db(new IndexType());
    std::vector<Record> new_records;
    prepare_db(db, new_records, enable_index);

    // validate the content of the record
    std::vector<Record> found_records;

    // multiple answers
    ASSERT_TRUE(db.find_by_hobbies({"car", "cat", "code"}, found_records));
    ASSERT_EQ(2, found_records.size());

    std::set<int> expect_ids = {5, 6};
    std::set<int> actual_ids;
    std::vector<int> ids;

    for (auto &record: found_records) {
        actual_ids.insert(record.get_id());
        ids.push_back(record.get_id());
    }
    ASSERT_EQ(expect_ids, actual_ids);

    std::sort(ids.begin(), ids.end());
    for (int i = 0; i < ids.size(); ++i) {
        verify_record_without_id(new_records[ids[i]], found_records[i]);
    }

    // no partial match
    found_records.clear();
    ASSERT_FALSE(db.find_by_hobbies({"car", "cat"}, found_records));
    ASSERT_TRUE(found_records.empty());

    ASSERT_FALSE(db.find_by_hobbies({"code", "cat"}, found_records));
    ASSERT_TRUE(found_records.empty());
}

template<typename IndexType>
void test_db_multiple_records_search_by_age_range(bool enable_index) {
    // prepare db
    GasWorksDB db(new IndexType());
    std::vector<Record> new_records;
    prepare_db(db, new_records, enable_index);

    // validate the content of the record
    std::vector<Record> found_records;

    ASSERT_TRUE(db.find_by_age_range(10, 20, found_records));
    ASSERT_EQ(4, found_records.size());

    std::set<int> expect_ids = {0, 1, 3, 4};
    std::set<int> actual_ids;
    std::vector<int> ids;

    for (auto &record: found_records) {
        actual_ids.insert(record.get_id());
        ids.push_back(record.get_id());
    }
    ASSERT_EQ(expect_ids, actual_ids);

    for (int i = 0; i < ids.size(); ++i) {
        verify_record_without_id(new_records[ids[i]], found_records[i]);
    }
}
