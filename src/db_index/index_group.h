#pragma once

#include "Index.h"
#include "hash_map_index.h"
#include "btree_map_index.h"
#include <vector>

/*
 * this interface to allow GasWorksDB to take multiple implementations (e.g. hash, map) of index group
 */
class IndexGroupInterface {
public:
    virtual Index<std::string> &get_name_index() = 0;

    virtual Index<unsigned> &get_age_index() = 0;

    virtual Index<std::string> &get_hobby_index() = 0;

    virtual ~IndexGroupInterface() = default;
};

class HashIndexGroup : public IndexGroupInterface {
    HashMapIndex<std::string> name_index;
    HashMapIndex<unsigned> age_index;
    HashMapIndex<std::string> hobby_index;

public:
    Index<std::string> &get_name_index() override {
        return name_index;
    }

    Index<unsigned int> &get_age_index() override {
        return age_index;
    }

    Index<std::string> &get_hobby_index() override {
        return hobby_index;
    }
};

class BtreeIndexGroup : public IndexGroupInterface {
    BtreeMapIndex<std::string> name_index;
    BtreeMapIndex<unsigned> age_index;
    BtreeMapIndex<std::string> hobby_index;

public:
    Index<std::string> &get_name_index() override {
        return name_index;
    }

    Index<unsigned> &get_age_index() override {
        return age_index;
    }

    Index<std::string> &get_hobby_index() override {
        return hobby_index;
    }
};
