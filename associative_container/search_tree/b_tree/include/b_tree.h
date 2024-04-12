//
// Created by Des Caldnd on 4/12/2024.
//

#include <iterator>
#include <utility>
#include <array>
#include <concepts>
#include <stack>
#include <allocator_guardant.h>
#include <logger_guardant.h>

#ifndef MP_OS_B_TREE_H
#define MP_OS_B_TREE_H

template<typename compare, typename tkey>
concept compator = requires(compare c, const tkey& lhs, const tkey& rhs)
{
    {c(lhs, rhs)} -> std::same_as<bool>;
} && std::copyable<compare> && std::default_initializable<compare>;



template <typename tkey, typename tvalue, std::size_t t = 5, compator<tkey> compare = std::less<tkey>>
class B_tree final : public allocator_guardant, public logger_guardant, private compare
{
public:

    using tree_data_type = std::pair<const tkey, tvalue>;

private:

    static constexpr const size_t minimum_keys_in_node = t - 1;
    static constexpr const size_t maximum_keys_in_node = 2 * t - 1;

    // region comparators declaration

    inline bool compare_keys(const tkey& lhs, const tkey& rhs) const;

    inline bool compare_pairs(const tree_data_type& lhs, const tree_data_type& rhs) const;

    // endregion comparators declaration

    struct btree_node
    {
        // TODO: need additional data?
        std::array<tree_data_type, maximum_keys_in_node + 1> keys;
        std::array<btree_node*, maximum_keys_in_node + 1> pointers;
    };

    allocator* _allocator;
    logger* _logger;

    btree_node* _root;

    size_t _size;

    logger* get_logger() const noexcept override;
    allocator* get_allocator() const noexcept override;

public:

    // region constructors declaration
    B_tree(compare cmp = compare(), allocator* allocator = nullptr, logger* logger = nullptr);

    template<typename iterator>
    requires std::forward_iterator<iterator> && requires (iterator a)
                                                {{ *a } -> std::convertible_to<tree_data_type>;}
    B_tree(iterator begin, iterator end, compare cmp = compare(), allocator* allocator = nullptr, logger* logger = nullptr);

    // endregion constructors declaration

    // region five declaration

    B_tree(const B_tree& other);
    B_tree(B_tree&& other) noexcept;

    B_tree& operator=(const B_tree& other);
    B_tree& operator=(B_tree&& other) noexcept;

    ~B_tree() noexcept;

    // endregion five declaration

    // region iterators declaration

    class btree_iterator
    {

    public:
        using value_type = tree_data_type;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;

        using self = btree_iterator;

        friend class B_tree;

        btree_iterator();
        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        self& operator--();
        self operator--(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t depth() const noexcept;

        size_t current_node_keys_count() const noexcept;

        bool is_terminate_node() const noexcept;
        // TODO: other methods for testing

    private:
        btree_iterator(const std::stack<std::pair<btree_node**, size_t>>& path);
    };

    class btree_const_iterator
    {
    public:
        using value_type = tree_data_type;
        using reference = const value_type&;
        using pointer = const value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;

        using self = btree_const_iterator;

        friend class B_tree;

        btree_const_iterator();
        btree_const_iterator(const btree_iterator& it);

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        self& operator--();
        self operator--(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t depth() const noexcept;

        size_t current_node_keys_count() const noexcept;

        bool is_terminate_node() const noexcept;
        // TODO: other methods for testing

    private:
        btree_const_iterator(const std::stack<std::pair<btree_node**, size_t>>& path);
    };

    class btree_reverse_iterator
    {
    public:
        using value_type = tree_data_type;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;

        using self = btree_reverse_iterator;

        friend class B_tree;

        btree_reverse_iterator();
        btree_reverse_iterator(const btree_iterator& it);

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        self& operator--();
        self operator--(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t depth() const noexcept;

        size_t current_node_keys_count() const noexcept;

        bool is_terminate_node() const noexcept;
        // TODO: other methods for testing

    private:
        // need validate index
        btree_reverse_iterator(const std::stack<std::pair<btree_node**, size_t>>& path);
    };

    class btree_const_reverse_iterator
    {
    public:
        using value_type = tree_data_type;
        using reference = const value_type&;
        using pointer = const value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;

        using self = btree_const_reverse_iterator;

        friend class B_tree;

        btree_const_reverse_iterator();
        btree_const_reverse_iterator(const btree_reverse_iterator& it);

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        self& operator--();
        self operator--(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t depth() const noexcept;

        size_t current_node_keys_count() const noexcept;

        bool is_terminate_node() const noexcept;
        // TODO: other methods for testing

    private:
        // need validate index
        btree_const_reverse_iterator(const std::stack<std::pair<btree_node**, size_t>>& path);
    };

    friend class btree_iterator;
    friend class btree_const_iterator;
    friend class btree_reverse_iterator;
    friend class btree_const_reverse_iterator;

    // endregion iterators declaration

    // region element access declaration

    /*
     * Returns a reference to the mapped value of the element with specified key. If no such element exists, an exception of type std::out_of_range is thrown.
     */
    tvalue& at(const tkey&);
    const tvalue& at(const tkey&) const;


    /*
     * If key not exists, makes default initialization of value
     */
    tvalue& operator[](const tkey& key);
    tvalue& operator[](tkey&& key);

    // endregion element access declaration

    // region iterator begins declaration

    btree_iterator begin() const;
    btree_iterator end() const;

    btree_const_iterator cbegin() const;
    btree_const_iterator cend() const;

    btree_reverse_iterator rbegin() const;
    btree_reverse_iterator rend() const;

    btree_const_reverse_iterator crbegin() const;
    btree_const_reverse_iterator crend() const;

    // endregion iterator begins declaration

    // region lookup declaration

    size_t size() const noexcept;

    /*
     * Returns end() if not exist
     */
    btree_iterator find(const tkey& key);
    btree_const_iterator find(const tkey& key) const;

    std::pair<btree_iterator, btree_iterator> find_range(const tkey& lower, const tkey& upper, bool include_lower = true, bool include_upper = false) const;

    bool contains(const tkey& key) const;

    // endregion lookup declaration

    // region modifiers declaration

    void clear() noexcept;

    /*
     * Does nothing if key exists, delegates to emplace.
     * Second return value is true, when inserted
     */
    std::pair<btree_iterator, bool> insert(const tree_data_type& data);
    std::pair<btree_iterator, bool> insert(tree_data_type&& data);

    template <typename ...Args>
    std::pair<btree_iterator, bool> emplace(Args&&... args);

    /*
     * Updates value if key exists, delegates to emplace.
     */
    btree_iterator insert_or_assign(const tree_data_type& data);
    btree_iterator insert_or_assign(tree_data_type&& data);

    template <typename ...Args>
    btree_iterator emplace_or_assign(Args&&... args);

    /*
     * Return iterator to node next ro removed or end() if key not exists
     */
    btree_iterator erase(btree_const_iterator pos);
    btree_iterator erase(const tkey& key);

    // endregion modifiers declaration
};

template<typename tkey, typename tvalue, std::size_t t, compator<tkey> compare>
bool B_tree<tkey, tvalue, t, compare>::compare_pairs(const B_tree::tree_data_type &lhs,
                                                     const B_tree::tree_data_type &rhs) const
{
    return compare_keys(lhs.first, rhs.first);
}

template<typename tkey, typename tvalue, std::size_t t, compator<tkey> compare>
bool B_tree<tkey, tvalue, t, compare>::compare_keys(const tkey &lhs, const tkey &rhs) const
{
    return compare::operator()(lhs, rhs);
}


#endif //MP_OS_B_TREE_H
