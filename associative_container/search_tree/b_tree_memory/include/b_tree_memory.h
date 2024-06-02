//
// Created by Des Caldnd on 5/29/2024.
//

#ifndef MP_OS_B_TREE_DISK_H
#define MP_OS_B_TREE_MEMORY_H

#include <iterator>
#include <utility>
#include <array>
#include <concepts>
#include <stack>
#include <fstream>
#include <initializer_list>
#include <logger_guardant.h>
#include <search_tree.h>
#include <optional>
#include <tree_interface.h>


template <serializable tkey, serializable tvalue, compator<tkey> compare = std::less<tkey>, std::size_t t = 5>
class B_tree_disk final : public logger_guardant, private compare, public tree_interface<tkey, tvalue, compare, t>
{
public:

    using tree_data_type = std::pair<tkey, tvalue>;
    using tree_data_type_const = std::pair<const tkey, tvalue>;

private:

    static constexpr const size_t minimum_keys_in_node = t - 1;
    static constexpr const size_t maximum_keys_in_node = 2 * t - 1;

    // region comparators declaration

    inline bool compare_keys(const tkey& lhs, const tkey& rhs) const;

    inline bool compare_pairs(const tree_data_type& lhs, const tree_data_type& rhs) const;

    // endregion comparators declaration

    struct btree_disk_node
    {
        size_t size;
        std::array<tree_data_type, maximum_keys_in_node + 1> keys;
        std::array<btree_mem_node*, maximum_keys_in_node + 2> pointers;

        btree_disk_node() noexcept;
    };

    logger* _logger;

    mutable std::fstream file;

    logger* get_logger() const noexcept override;

public:

    // region constructors declaration

    explicit B_tree_disk(const std::string& file_path, const compare& cmp = compare(), logger* logger = nullptr);


    // endregion constructors declaration

    // region five declaration

    B_tree_disk(B_tree_memory&& other) noexcept =default;
    B_tree_memory& operator=(B_tree_memory&& other) noexcept =default;

    B_tree_disk(const B_tree_memory& other) =delete;
    B_tree_memory& operator=(const B_tree_memory& other) =delete;

    ~B_tree_disk() noexcept override =default;

    // endregion five declaration

    // region iterators declaration

    class btree_const_iterator
    {
        std::stack<std::pair<size_t , size_t>> _path;
        size_t _index;
    public:
        using value_type = tree_data_type_const;
        using reference = const value_type&;
        using pointer = const value_type*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = ptrdiff_t;

        using self = btree_mem_const_iterator;

        friend class B_tree_memory;

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        explicit btree_const_iterator(const std::stack<std::pair<size_t, size_t>>& path = std::stack<std::pair<size_t, size_t>>(), size_t index = 0);
    };

    friend class btree_mem_const_iterator;

    // endregion iterators declaration

    // region element access declaration

    /*
     * Returns a reference to the mapped value of the element with specified key. If no such element exists, an exception of type std::out_of_range is thrown.
     */
    std::optional<tvalue> at(const tkey&) const override;

    // endregion element access declaration

    // region iterator begins declaration

    btree_mem_const_iterator begin() const;
    btree_mem_const_iterator end() const;

    // endregion iterator begins declaration

    // region lookup declaration

    bool empty() const noexcept;

    std::vector<tree_data_type_const> find_range(const tkey& lower, const tkey& upper, bool include_lower = true, bool include_upper = false) const override;

    // endregion lookup declaration

    // region modifiers declaration

    void clear() noexcept;

    /*
     * Does nothing if key exists, delegates to emplace.
     * Second return value is true, when inserted
     */
    bool insert(const tree_data_type& data) override;
    bool insert(tree_data_type&& data) override;

    template <typename ...Args>
    std::pair<btree_mem_const_iterator, bool> emplace(Args&&... args);

    /*
     * Updates value if key exists, delegates to emplace.
     */
    bool insert_or_assign(const tree_data_type& data) override;
    bool insert_or_assign(tree_data_type&& data) override;

    template <typename ...Args>
    bool emplace_or_assign(Args&&... args);

    /*
     * Return iterator to node next ro removed or end() if key not exists
     */
    bool erase(const tkey& key) override;

    // endregion modifiers declaration

private:

    btree_mem_const_iterator erase_inner(std::stack<std::pair<btree_mem_node**, size_t>>& path, size_t index) noexcept;

    std::pair<std::stack<std::pair<btree_mem_node**, size_t>>, size_t> find_path(const tkey& key) const noexcept;

    std::pair<size_t, bool> find_index(const tkey& key, btree_mem_node* node) const noexcept;

    static bool exists(btree_mem_node* node, size_t ind) noexcept;

    static bool is_terminate_node(btree_mem_node* node) noexcept;

    btree_mem_const_iterator emplace_inner(tree_data_type&& data, std::stack<std::pair<btree_mem_node**, size_t>>& path);

    static void insert_array(btree_mem_node* node, btree_mem_node* right_node, tree_data_type&& data, size_t index) noexcept;

    static btree_mem_node* remove_array(btree_mem_node* node, size_t index, bool remove_left_ptr = true) noexcept;

    void split_node(std::stack<std::pair<btree_mem_node**, size_t>>& path, btree_mem_node*& node, size_t& index);

    void rebalance_node(std::stack<std::pair<btree_mem_node**, size_t>>& path, btree_mem_node*& node, size_t& index);
};

template<serializable tkey, serializable tvalue, compator<tkey> compare, std::size_t t>
bool B_tree_memory<tkey, tvalue, compare, t>::compare_pairs(const B_tree_memory::tree_data_type &lhs,
                                                            const B_tree_memory::tree_data_type &rhs) const
{
    return compare_keys(lhs.first, rhs.first);
}

template<serializable tkey, serializable tvalue, compator<tkey> compare, std::size_t t>
bool B_tree_memory<tkey, tvalue, compare, t>::compare_keys(const tkey &lhs, const tkey &rhs) const
{
    return compare::operator()(lhs, rhs);
}

#endif //MP_OS_B_TREE_DISK_H
