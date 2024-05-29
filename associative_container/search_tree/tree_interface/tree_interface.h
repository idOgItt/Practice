//
// Created by Des Caldnd on 5/29/2024.
//

#ifndef MP_OS_TREE_INTERFACE_H
#define MP_OS_TREE_INTERFACE_H

#include <search_tree.h>

template <serializable tkey, serializable tvalue, compator<tkey> compare, size_t t>
class tree_interface
{
public:
    using tree_data_type = std::pair<tkey, tvalue>;
    using tree_data_type_const = std::pair<const tkey, tvalue>;

    virtual std::optional<tvalue> at(const tkey&) const =0;

    virtual std::vector<tree_data_type_const> find_range(const tkey& lower, const tkey& upper, bool include_lower = true, bool include_upper = false) const =0;

    virtual bool insert(const tree_data_type& data) =0;
    virtual bool insert(tree_data_type&& data) =0;

    virtual bool insert_or_assign(const tree_data_type& data) =0;
    virtual bool insert_or_assign(tree_data_type&& data) =0;

    virtual bool erase(const tkey& key) =0;

    virtual ~tree_interface() =default;
};

#endif //MP_OS_TREE_INTERFACE_H
