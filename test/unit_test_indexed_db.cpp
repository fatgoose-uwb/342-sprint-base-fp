#include "unit_test_indexed_db.h"

TEST(final_project, test_db_initialization) {
    test_db_initialization<HashIndexGroup>(true);
    test_db_initialization<HashIndexGroup>(false);

    test_db_initialization<BtreeIndexGroup>(true);
    test_db_initialization<BtreeIndexGroup>(false);
}

TEST(final_project, db_insert_first_record) {
    test_db_insert_first_record<HashIndexGroup>(true);
    test_db_insert_first_record<HashIndexGroup>(false);

    test_db_insert_first_record<BtreeIndexGroup>(true);
    test_db_insert_first_record<BtreeIndexGroup>(false);
}

TEST(final_project, test_db_multiple_records_search_by_id) {
    test_db_multiple_records_search_by_id<HashIndexGroup>(true);
    test_db_multiple_records_search_by_id<HashIndexGroup>(false);

    test_db_multiple_records_search_by_id<BtreeIndexGroup>(true);
    test_db_multiple_records_search_by_id<BtreeIndexGroup>(false);
}

TEST(final_project, test_db_multiple_records_search_by_age) {
    test_db_multiple_records_search_by_age<HashIndexGroup>(true);
    test_db_multiple_records_search_by_age<HashIndexGroup>(false);

    test_db_multiple_records_search_by_age<BtreeIndexGroup>(true);
    test_db_multiple_records_search_by_age<BtreeIndexGroup>(false);
}

TEST(final_project, test_db_multiple_records_search_by_name) {
    test_db_multiple_records_search_by_name<HashIndexGroup>(true);
    test_db_multiple_records_search_by_name<HashIndexGroup>(false);

    test_db_multiple_records_search_by_name<BtreeIndexGroup>(true);
    test_db_multiple_records_search_by_name<BtreeIndexGroup>(false);
}

TEST(final_project, db_multiple_records_search_by_hobbies_single_answer) {
    db_multiple_records_search_by_hobbies_single_answer<HashIndexGroup>(true);
    db_multiple_records_search_by_hobbies_single_answer<HashIndexGroup>(false);

    db_multiple_records_search_by_hobbies_single_answer<BtreeIndexGroup>(true);
    db_multiple_records_search_by_hobbies_single_answer<BtreeIndexGroup>(false);
}

TEST(final_project, db_multiple_records_search_by_hobbies_multiple_answer) {
    test_db_multiple_records_search_by_hobbies_multiple_answer<HashIndexGroup>(true);
    test_db_multiple_records_search_by_hobbies_multiple_answer<HashIndexGroup>(false);

    test_db_multiple_records_search_by_hobbies_multiple_answer<BtreeIndexGroup>(true);
    test_db_multiple_records_search_by_hobbies_multiple_answer<BtreeIndexGroup>(false);
}

TEST(final_project, test_db_multiple_records_search_by_hobbies_no_partial_match) {
    test_db_multiple_records_search_by_hobbies_no_partial_match<HashIndexGroup>(true);
    test_db_multiple_records_search_by_hobbies_no_partial_match<HashIndexGroup>(false);

    test_db_multiple_records_search_by_hobbies_no_partial_match<BtreeIndexGroup>(true);
    test_db_multiple_records_search_by_hobbies_no_partial_match<BtreeIndexGroup>(false);
}

TEST(final_project, test_db_multiple_records_search_by_age_range) {
    /*
     * range only supported by tree index
     */
    test_db_multiple_records_search_by_age_range<BtreeIndexGroup>(true);
    test_db_multiple_records_search_by_age_range<BtreeIndexGroup>(false);
}
