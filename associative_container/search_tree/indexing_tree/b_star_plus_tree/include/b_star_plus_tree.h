#include <iterator>
#include <utility>
#include <vector>
#include <concepts>
#include <stack>
#include <pp_allocator.h>
#include <search_tree.h>
#include <initializer_list>
#include <logger_guardant.h>

#ifndef MP_OS_BS_PLUS_TREE_H
#define MP_OS_BS_PLUS_TREE_H

template <typename tkey, typename tvalue, compator<tkey> compare = std::less<tkey>, std::size_t t = 5>
class BSP_tree final : public logger_guardant, private compare
{
public:

    using tree_data_type = std::pair<tkey, tvalue>;
    using tree_data_type_const = std::pair<const tkey, tvalue>;
    using value_type = tree_data_type_const;

private:

    // TODO: Another restrictions
    static constexpr const size_t minimum_keys_in_node = t - 1;
    static constexpr const size_t maximum_keys_in_node = 2 * t - 1;

    // region comparators declaration

    inline bool compare_keys(const tkey& lhs, const tkey& rhs) const;
    inline bool compare_pairs(const tree_data_type& lhs, const tree_data_type& rhs) const;

    // endregion comparators declaration

    struct bsptree_node_base
    {
        bool _is_terminated;

        bsptree_node_base() noexcept;
        virtual ~bsptree_node_base() =default;
    };

    struct bsptree_node_term : public bsptree_node_base
    {
        bsptree_node_term* _next;
        std::vector<tree_data_type, pp_allocator<tree_data_type>> _data;

        bsptree_node_term(pp_allocator<tree_data_type> al);
    };

    struct bsptree_node_middle : public bsptree_node_base
    {
        std::vector<tkey, pp_allocator<tkey>> _keys;
        std::vector<bsptree_node_base*, pp_allocator<bsptree_node_base*>> _pointers;

        bsptree_node_middle(pp_allocator<tkey> al);
    };

    pp_allocator<value_type> _allocator;
    logger* _logger;
    bsptree_node_base* _root;
    size_t _size;

    logger* get_logger() const noexcept override;
    pp_allocator<value_type> get_allocator() const noexcept;

public:

    // region constructors declaration

    explicit BSP_tree(const compare& cmp = compare(), pp_allocator<value_type> = pp_allocator<value_type>(), logger* logger = nullptr);

    explicit BSP_tree(pp_allocator<value_type> alloc, const compare& comp = compare(), logger *logger = nullptr);

    template<input_iterator_for_pair<tkey, tvalue> iterator>
    explicit BSP_tree(iterator begin, iterator end, const compare& cmp = compare(), pp_allocator<value_type> = pp_allocator<value_type>(), logger* logger = nullptr);

    BSP_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp = compare(), pp_allocator<value_type> = pp_allocator<value_type>(), logger* logger = nullptr);

    // endregion constructors declaration

    // region five declaration

    BSP_tree(const BSP_tree& other);

    BSP_tree(BSP_tree&& other) noexcept;

    BSP_tree& operator=(const BSP_tree& other);

    BSP_tree& operator=(BSP_tree&& other) noexcept;

    ~BSP_tree() noexcept override;

    // endregion five declaration

    // region iterators declaration

    class bsptree_iterator;
    class bsptree_const_iterator;

    class bsptree_iterator final
    {
        bsptree_node_term* _node;
        size_t _index;

    public:
        using value_type = tree_data_type_const;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using self = bsptree_iterator;

        friend class BSP_tree;
        friend class bsptree_const_iterator;

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t current_node_keys_count() const noexcept;
        size_t index() const noexcept;

        explicit bsptree_iterator(bsptree_node_term* node = nullptr, size_t index = 0);

    };

    class bsptree_const_iterator final
    {
        bsptree_node_term* _node;
        size_t _index;

    public:

        using value_type = tree_data_type_const;
        using reference = const value_type&;
        using pointer = const value_type*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using self = bsptree_const_iterator;

        friend class BSP_tree;
        friend class bsptree_iterator;

        bsptree_const_iterator(const bsptree_iterator& it) noexcept;

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t current_node_keys_count() const noexcept;
        size_t index() const noexcept;

        explicit bsptree_const_iterator(bsptree_node_term* node = nullptr, size_t index = 0);
    };

    friend class btree_iterator;
    friend class btree_const_iterator;

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

    bsptree_iterator begin();
    bsptree_iterator end();

    bsptree_const_iterator begin() const;
    bsptree_const_iterator end() const;

    bsptree_const_iterator cbegin() const;
    bsptree_const_iterator cend() const;

    // endregion iterator begins declaration

    // region lookup declaration

    size_t size() const noexcept;
    bool empty() const noexcept;

    /*
     * Returns end() if not exist
     */

    bsptree_iterator find(const tkey& key);
    bsptree_const_iterator find(const tkey& key) const;

    bsptree_iterator lower_bound(const tkey& key);
    bsptree_const_iterator lower_bound(const tkey& key) const;

    bsptree_iterator upper_bound(const tkey& key);
    bsptree_const_iterator upper_bound(const tkey& key) const;

    bool contains(const tkey& key) const;

    // endregion lookup declaration

    // region modifiers declaration

    void clear() noexcept;

    /*
     * Does nothing if key exists, delegates to emplace.
     * Second return value is true, when inserted
     */
    std::pair<bsptree_iterator, bool> insert(const tree_data_type& data);
    std::pair<bsptree_iterator, bool> insert(tree_data_type&& data);

    template <typename ...Args>
    std::pair<bsptree_iterator, bool> emplace(Args&&... args);

    /*
     * Updates value if key exists, delegates to emplace.
     */
    bsptree_iterator insert_or_assign(const tree_data_type& data);
    bsptree_iterator insert_or_assign(tree_data_type&& data);

    template <typename ...Args>
    bsptree_iterator emplace_or_assign(Args&&... args);

    /*
     * Return iterator to node next ro removed or end() if key not exists
     */
    bsptree_iterator erase(bsptree_iterator pos);
    bsptree_iterator erase(bsptree_const_iterator pos);

    bsptree_iterator erase(bsptree_iterator beg, bsptree_iterator en);
    bsptree_iterator erase(bsptree_const_iterator beg, bsptree_const_iterator en);


    bsptree_iterator erase(const tkey& key);

    // endregion modifiers declaration
};

template<std::input_iterator iterator, compator<typename std::iterator_traits<iterator>::value_type::first_type> compare = std::less<typename std::iterator_traits<iterator>::value_type::first_type>,
        std::size_t t = 5, typename U>
BSP_tree(iterator begin, iterator end, const compare &cmp = compare(), pp_allocator<U> = pp_allocator<U>(),
        logger *logger = nullptr) -> BSP_tree<typename std::iterator_traits<iterator>::value_type::first_type, typename std::iterator_traits<iterator>::value_type::second_type, compare, t>;

template<typename tkey, typename tvalue, compator<tkey> compare = std::less<tkey>, std::size_t t = 5, typename U>
BSP_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare &cmp = compare(), pp_allocator<U> = pp_allocator<U>(),
        logger *logger = nullptr) -> BSP_tree<tkey, tvalue, compare, t>;

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BSP_tree<tkey, tvalue, compare, t>::compare_pairs(const BSP_tree::tree_data_type &lhs,
                                                      const BSP_tree::tree_data_type &rhs) const
{
    return compare_keys(lhs.first, rhs.first);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool BSP_tree<tkey, tvalue, compare, t>::compare_keys(const tkey &lhs, const tkey &rhs) const
{
    return compare::operator()(lhs, rhs);
}

#endif