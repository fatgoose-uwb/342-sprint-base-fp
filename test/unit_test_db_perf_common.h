#include "gtest/gtest.h"
#include "btree/map.h"
#include "db_index/hash_map_index.h"
#include "db_index/btree_map_index.h"
#include "db_index/index_group.h"
#include "db.h"
#include <chrono>
#include <random>
#include <iostream>
#include <unordered_map>

using namespace std::chrono;

void prepare_db_for_perf_test(GasWorksDB &hash_indexed_db, GasWorksDB &btree_indexed_db, unsigned table_size,
                              unsigned HOBBY_TYPE_COUNT, unsigned MIN_HOBBY_COUNT, unsigned AGE_MAX,
                              std::vector<Record *> &records);