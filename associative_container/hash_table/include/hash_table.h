#ifndef MP_OS_WORKBENCH_HASH_TABLE_H
#define MP_OS_WORKBENCH_HASH_TABLE_H

#include <associative_container.h>
#include <not_implemented.h>

// TODO: concept search_ds
template<typename T>
concept search_ds = true;

template<typename tkey, typename tvalue, typename hash = std::hash<tkey>>
class hash_table final
{

public:

    using value_type = std::pair<const tkey, tvalue>;

    void insert(
        tkey const &key,
        tvalue const &value) override;

    void insert(
        tkey const &key,
        tvalue &&value) override;

    tvalue const &obtain(
        tkey const &key) override;

    tvalue dispose(
        tkey const &key) override;

};



#endif //MP_OS_WORKBENCH_HASH_TABLE_H