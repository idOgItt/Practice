//
// Created by Des Caldnd on 4/12/2024.
//

#include <iterator>
#include <utility>
#include <array>
#include <concepts>
#include <stack>
#include <initializer_list>
#include <allocator_guardant.h>
#include <logger_guardant.h>

#ifndef MP_OS_B_TREE_H
#define MP_OS_B_TREE_H

template<typename compare, typename tkey>
concept compator = requires(const compare c, const tkey& lhs, const tkey& rhs)
{
    {c(lhs, rhs)} -> std::same_as<bool>;
} && std::copyable<compare> && std::default_initializable<compare>;

template<typename f_iter, typename tkey, typename tval>
concept input_iterator_for_pair = std::input_iterator<f_iter> && std::same_as<typename std::iterator_traits<f_iter>::value_type, std::pair<tkey, tval>>;

// TODO: memory resource instead of allocator - std::pmr::memory_resource, std::pmr::polymorphic_allocator

template <typename tkey, typename tvalue, compator<tkey> compare = std::less<tkey>, std::size_t t = 5>
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
        btree_node* parent;
        size_t parent_index;
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

    explicit B_tree(const compare& cmp = compare(), allocator* allocator = nullptr, logger* logger = nullptr);

    template<input_iterator_for_pair<tkey, tvalue> iterator>
    explicit B_tree(iterator begin, iterator end, const compare& cmp = compare(), allocator* allocator = nullptr, logger* logger = nullptr);


	B_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp = compare(), allocator* allocator = nullptr, logger* logger = nullptr);

    // endregion constructors declaration

    // region five declaration

    B_tree(const B_tree& other);
    B_tree(B_tree&& other) noexcept;

    B_tree& operator=(const B_tree& other);
    B_tree& operator=(B_tree&& other) noexcept;

    ~B_tree() noexcept override;

    // endregion five declaration

    // region iterators declaration

    class btree_iterator;
    class btree_reverse_iterator;
    class btree_const_iterator;
    class btree_const_reverse_iterator;

    class btree_iterator
    {
        btree_node* _node;
        size_t _index;

    public:
        using value_type = tree_data_type;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;

        using self = btree_iterator;

        friend class B_tree;
        friend class btree_reverse_iterator;
        friend class btree_const_iterator;
        friend class btree_const_reverse_iterator;

        btree_iterator() noexcept;

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

    private:
        explicit btree_iterator(btree_node* node = nullptr, size_t index = 0) noexcept;
    };

    class btree_const_iterator
    {
        btree_node* _node;
        size_t _index;
    public:
        using value_type = tree_data_type;
        using reference = const value_type&;
        using pointer = const value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;

        using self = btree_const_iterator;

        friend class B_tree;
        friend class btree_reverse_iterator;
        friend class btree_iterator;
        friend class btree_const_reverse_iterator;

        btree_const_iterator() noexcept;
        btree_const_iterator(const btree_iterator& it) noexcept;

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

    private:
        explicit btree_const_iterator(btree_node* node = nullptr, size_t index = 0) noexcept;
    };

    class btree_reverse_iterator
    {
        btree_node* _node;
        size_t _index;
    public:
        using value_type = tree_data_type;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;

        using self = btree_reverse_iterator;

        friend class B_tree;
        friend class btree_iterator;
        friend class btree_const_iterator;
        friend class btree_const_reverse_iterator;

        btree_reverse_iterator() noexcept;
        btree_reverse_iterator(const btree_iterator& it) noexcept;
        operator btree_iterator() const noexcept;

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

    private:
        // need validate index
        explicit btree_reverse_iterator(btree_node* node = nullptr, size_t index = 0) noexcept;
    };

    class btree_const_reverse_iterator
    {
        btree_node* _node;
        size_t _index;
    public:
        using value_type = tree_data_type;
        using reference = const value_type&;
        using pointer = const value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = ptrdiff_t;

        using self = btree_const_reverse_iterator;

        friend class B_tree;
        friend class btree_reverse_iterator;
        friend class btree_const_iterator;
        friend class btree_iterator;

        btree_const_reverse_iterator() noexcept;
        btree_const_reverse_iterator(const btree_reverse_iterator& it) noexcept;
        operator btree_const_iterator() const noexcept;

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

    private:
        // need validate index
        explicit btree_const_reverse_iterator(btree_node* node = nullptr, size_t index = 0) noexcept;
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

    btree_iterator begin();
    btree_iterator end();

    btree_const_iterator begin() const;
    btree_const_iterator end() const;

    btree_const_iterator cbegin() const;
    btree_const_iterator cend() const;

    btree_reverse_iterator rbegin();
    btree_reverse_iterator rend();

    btree_const_reverse_iterator rbegin() const;
    btree_const_reverse_iterator rend() const;

    btree_const_reverse_iterator crbegin() const;
    btree_const_reverse_iterator crend() const;

    // endregion iterator begins declaration

    // region lookup declaration

    size_t size() const noexcept;

	bool empty() const noexcept;

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
    btree_iterator erase(btree_iterator pos);
    btree_iterator erase(const tkey& key);

    // endregion modifiers declaration

private:

    btree_node* copy_subtree(btree_node* parent, btree_node* copyable);

    void destroy_subtree(btree_node* node) noexcept;

    btree_iterator erase_inner(btree_node* node, size_t index) noexcept;

    std::pair<btree_node*, size_t> find_path(const tkey& key) const noexcept;

    static bool exists(btree_node* node, size_t ind) noexcept;

    btree_iterator emplace_inner(tree_data_type&& data, btree_node* node);

};

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t B_tree<tkey, tvalue, compare, t>::btree_iterator::current_node_keys_count() const noexcept
{
    return _node->keys.size();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t B_tree<tkey, tvalue, compare, t>::btree_const_iterator::current_node_keys_count() const noexcept
{
    return _node->keys.size();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t B_tree<tkey, tvalue, compare, t>::btree_reverse_iterator::current_node_keys_count() const noexcept
{
    return _node->keys.size();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t B_tree<tkey, tvalue, compare, t>::btree_const_reverse_iterator::current_node_keys_count() const noexcept
{
    return _node->keys.size();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool B_tree<tkey, tvalue, compare, t>::btree_iterator::is_terminate_node() const noexcept
{
    return _node->pointers.size() > 0 && _node->pointers[0] != nullptr;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool B_tree<tkey, tvalue, compare, t>::btree_const_iterator::is_terminate_node() const noexcept
{
    return _node->pointers.size() > 0 && _node->pointers[0] != nullptr;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool B_tree<tkey, tvalue, compare, t>::btree_reverse_iterator::is_terminate_node() const noexcept
{
    return _node->pointers.size() > 0 && _node->pointers[0] != nullptr;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool B_tree<tkey, tvalue, compare, t>::btree_const_reverse_iterator::is_terminate_node() const noexcept
{
    return _node->pointers.size() > 0 && _node->pointers[0] != nullptr;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::btree_iterator::btree_iterator(B_tree::btree_node *node,
                                                                 size_t index) noexcept : _node(node), _index(index) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::btree_const_iterator::btree_const_iterator(B_tree::btree_node *node,
                                                                             size_t index) noexcept : _node(node), _index(index) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::btree_reverse_iterator::btree_reverse_iterator(B_tree::btree_node *node,
                                                                                 size_t index) noexcept : _node(node), _index(index) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::btree_const_reverse_iterator::btree_const_reverse_iterator(B_tree::btree_node *node,
                                                                                             size_t index) noexcept : _node(node), _index(index) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_iterator::pointer
B_tree<tkey, tvalue, compare, t>::btree_iterator::operator->() const noexcept
{
    return &_node->keys[_index];
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_iterator::reference
B_tree<tkey, tvalue, compare, t>::btree_iterator::operator*() const noexcept
{
    return _node->keys[_index];
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_const_iterator::pointer
B_tree<tkey, tvalue, compare, t>::btree_const_iterator::operator->() const noexcept
{
    return &_node->keys[_index];
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_const_iterator::reference
B_tree<tkey, tvalue, compare, t>::btree_const_iterator::operator*() const noexcept
{
    return _node->keys[_index];
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_reverse_iterator::pointer
B_tree<tkey, tvalue, compare, t>::btree_reverse_iterator::operator->() const noexcept
{
    return &_node->keys[_index];
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_reverse_iterator::reference
B_tree<tkey, tvalue, compare, t>::btree_reverse_iterator::operator*() const noexcept
{
    return _node->keys[_index];
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_const_reverse_iterator::pointer
B_tree<tkey, tvalue, compare, t>::btree_const_reverse_iterator::operator->() const noexcept
{
    return &_node->keys[_index];
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_const_reverse_iterator::reference
B_tree<tkey, tvalue, compare, t>::btree_const_reverse_iterator::operator*() const noexcept
{
    return _node->keys[_index];
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::btree_iterator::btree_iterator() noexcept : _node(nullptr), _index(0) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::btree_const_iterator::btree_const_iterator() noexcept : _node(nullptr), _index(0) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::btree_reverse_iterator::btree_reverse_iterator() noexcept : _node(nullptr), _index(0) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::btree_const_reverse_iterator::btree_const_reverse_iterator() noexcept : _node(nullptr), _index(0) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_const_reverse_iterator B_tree<tkey, tvalue, compare, t>::crend() const
{
    return btree_const_reverse_iterator();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_const_reverse_iterator B_tree<tkey, tvalue, compare, t>::crbegin() const
{
    if (_root == nullptr)
        return btree_const_reverse_iterator();

    auto node = _root;

    while (node->pointers.size() > 0 && node->pointers[0] != nullptr)
    {
        node = node->pointers[node->pointers.size() - 1];
    }
    return btree_const_reverse_iterator(node, node->keys.size() - 1);
}


template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_const_reverse_iterator B_tree<tkey, tvalue, compare, t>::rend() const
{
    return btree_const_reverse_iterator();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_const_reverse_iterator B_tree<tkey, tvalue, compare, t>::rbegin() const
{
    if (_root == nullptr)
        return btree_const_reverse_iterator();

    auto node = _root;

    while (node->pointers.size() > 0 && node->pointers[0] != nullptr)
    {
        node = node->pointers[node->pointers.size() - 1];
    }
    return btree_const_reverse_iterator(node, node->keys.size() - 1);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_reverse_iterator B_tree<tkey, tvalue, compare, t>::rend()
{
    return btree_reverse_iterator();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_reverse_iterator B_tree<tkey, tvalue, compare, t>::rbegin()
{
    if (_root == nullptr)
        return btree_const_iterator();

    auto node = _root;

    while (node->pointers.size() > 0 && node->pointers[0] != nullptr)
    {
        node = node->pointers[node->pointers.size() - 1];
    }
    return btree_const_iterator(node, node->keys.size() - 1);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_const_iterator B_tree<tkey, tvalue, compare, t>::cend() const
{
    return btree_const_iterator();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_const_iterator B_tree<tkey, tvalue, compare, t>::cbegin() const
{
    if (_root == nullptr)
        return btree_const_iterator();

    auto node = _root;

    while (node->pointers.size() > 0 && node->pointers[0] != nullptr)
    {
        node = node->pointers[0];
    }
    return btree_const_iterator(node, 0);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_const_iterator B_tree<tkey, tvalue, compare, t>::end() const
{
    return btree_const_iterator();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_const_iterator B_tree<tkey, tvalue, compare, t>::begin() const
{
    if (_root == nullptr)
        return btree_const_iterator();

    auto node = _root;

    while (node->pointers.size() > 0 && node->pointers[0] != nullptr)
    {
        node = node->pointers[0];
    }
    return btree_const_iterator(node, 0);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_iterator B_tree<tkey, tvalue, compare, t>::end()
{
    return btree_iterator();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_iterator B_tree<tkey, tvalue, compare, t>::begin()
{
    if (_root == nullptr)
        return btree_iterator();

    auto node = _root;

    while (node->pointers.size() > 0 && node->pointers[0] != nullptr)
    {
        node = node->pointers[0];
    }
    return btree_iterator(node, 0);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
template<typename... Args>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_iterator B_tree<tkey, tvalue, compare, t>::emplace_or_assign(Args &&... args)
{
    tree_data_type data(std::forward<Args>(args)...);

    auto [ptr, ind] = find_path(data.first);

    if (exists(ptr, ind))
    {
        ptr->keys[ind] = std::move(data);
        return btree_iterator(ptr, ind);
    }
    return emplace_inner(std::move(data), ptr);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
template<typename... Args>
std::pair<typename B_tree<tkey, tvalue, compare, t>::btree_iterator, bool> B_tree<tkey, tvalue, compare, t>::emplace(Args &&... args)
{
    tree_data_type data(std::forward<Args>(args)...);

    auto [ptr, ind] = find_path(data.first);

    if (exists(ptr, ind))
        return std::make_pair(btree_iterator(ptr, ind), false);
    return std::make_pair(emplace_inner(std::move(data), ptr), true);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
tvalue &B_tree<tkey, tvalue, compare, t>::operator[](const tkey &key)
{
    auto [ptr, ind] = find_path(key);

    if (!exists(ptr, ind))
        return emplace_inner(std::make_pair(key, tvalue()), ptr)->second;

    return ptr->keys[ind].second;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
tvalue &B_tree<tkey, tvalue, compare, t>::operator[](tkey&& key)
{
    auto [ptr, ind] = find_path(key);

    if (!exists(ptr, ind))
        return emplace_inner(std::make_pair(std::move(key), tvalue()), ptr)->second;

    return ptr->keys[ind].second;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
const tvalue &B_tree<tkey, tvalue, compare, t>::at(const tkey &key) const
{
    auto [ptr, ind] = find_path(key);

    if (!exists(ptr, ind))
        throw std::out_of_range("No such key");

    return ptr->keys[ind].second;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
tvalue &B_tree<tkey, tvalue, compare, t>::at(const tkey &key)
{
    auto [ptr, ind] = find_path(key);

    if (!exists(ptr, ind))
        throw std::out_of_range("No such key");

    return ptr->keys[ind].second;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_const_iterator B_tree<tkey, tvalue, compare, t>::find(const tkey &key) const
{
    auto [ptr, ind] = find_path(key);

    return exists(ptr, ind) ? btree_const_iterator(ptr, ind) : cend();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_iterator B_tree<tkey, tvalue, compare, t>::find(const tkey &key)
{
    auto [ptr, ind] = find_path(key);

    return exists(ptr, ind) ? btree_iterator(ptr, ind) : end();
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool B_tree<tkey, tvalue, compare, t>::contains(const tkey &key) const
{
    auto [ptr, ind] = find_path(key);

    return exists(ptr, ind);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool B_tree<tkey, tvalue, compare, t>::empty() const noexcept
{
    return _size == 0;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t B_tree<tkey, tvalue, compare, t>::size() const noexcept
{
    return _size;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::B_tree::btree_iterator B_tree<tkey, tvalue, compare, t>::erase(const tkey &key)
{
    auto [ptr, ind] = find_path(key);
    return erase_inner(ptr, ind);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_iterator B_tree<tkey, tvalue, compare, t>::erase(B_tree::btree_iterator pos)
{
    return erase_inner(pos._node, pos._index);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
std::pair<typename B_tree<tkey, tvalue, compare, t>::btree_iterator, bool> B_tree<tkey, tvalue, compare, t>::insert(const B_tree::tree_data_type &data)
{
    return emplace(data);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
std::pair<typename B_tree<tkey, tvalue, compare, t>::btree_iterator, bool> B_tree<tkey, tvalue, compare, t>::insert(B_tree::tree_data_type&& data)
{
    return emplace(std::move(data));
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_iterator B_tree<tkey, tvalue, compare, t>::insert_or_assign(const B_tree::tree_data_type &data)
{
    return emplace_or_assign(data);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename B_tree<tkey, tvalue, compare, t>::btree_iterator B_tree<tkey, tvalue, compare, t>::insert_or_assign(B_tree::tree_data_type &&data)
{
    return emplace_or_assign(std::move(data));
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
void B_tree<tkey, tvalue, compare, t>::clear() noexcept
{
    destroy_subtree(_root);
    _root = nullptr;
    _size = 0;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t> &B_tree<tkey, tvalue, compare, t>::operator=(const B_tree &other)
{
    if (this != &other)
    {
        compare::operator=(other);
        destroy_subtree(_root);
        _root = copy_subtree(nullptr, other._root);
        _size = other.size();
        _allocator = other._allocator;
        _logger = other._logger;
    }
    return *this;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::B_tree(const B_tree &other) : compare(other), _allocator(other._allocator), _logger(other._logger), _size(other._size)
{
    _root = copy_subtree(nullptr, other._root);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::~B_tree() noexcept
{
    destroy_subtree(_root);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t> &B_tree<tkey, tvalue, compare, t>::operator=(B_tree &&other) noexcept
{
    if (this != &other)
    {
        std::swap(_allocator, other._allocator);
        std::swap(_logger, other._logger);
        std::swap(_size, other._size);
        std::swap(_root, other._root);
        compare::operator=(other);
    }
    return *this;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::B_tree(B_tree &&other) noexcept : compare(other), _allocator(other._allocator), _logger(other._logger), _root(other._root), _size(other._size)
{
    other._root = nullptr;
    other._size = 0;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
template<input_iterator_for_pair<tkey, tvalue> iterator>
B_tree<tkey, tvalue, compare, t>::B_tree(iterator begin, iterator end, const compare &cmp, allocator *allocator,
                                         logger *logger) : compare(cmp), _allocator(allocator), _logger(logger), _root(nullptr), _size(0)
{
    for (; begin != end; ++begin)
    {
        emplace_or_assign(*begin);
    }
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::B_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp, allocator* allocator, logger* logger) : compare(cmp), _allocator(allocator), _logger(logger), _root(nullptr), _size(0)
{
    for (auto& val : data)
    {
        emplace_or_assign(val);
    }
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
B_tree<tkey, tvalue, compare, t>::B_tree(const compare &cmp, allocator *allocator, logger *logger) : compare(cmp), _allocator(allocator), _logger(logger), _root(nullptr), _size(0){}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
logger *B_tree<tkey, tvalue, compare, t>::get_logger() const noexcept
{
    return _logger;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
allocator *B_tree<tkey, tvalue, compare, t>::get_allocator() const noexcept
{
    return _allocator;
}

template<std::input_iterator iterator, compator<typename std::iterator_traits<iterator>::value_type::first_type> compare = std::less<typename std::iterator_traits<iterator>::value_type::first_type>,
    std::size_t t = 5>
B_tree(iterator begin, iterator end, const compare &cmp = compare(), allocator *allocator = nullptr,
                                         logger *logger = nullptr) -> B_tree<typename std::iterator_traits<iterator>::value_type::first_type, typename std::iterator_traits<iterator>::value_type::second_type, compare, t>;

template<typename tkey, typename tvalue, compator<tkey> compare = std::less<tkey>, std::size_t t = 5>
B_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare &cmp = compare(), allocator *allocator = nullptr,
                                         logger *logger = nullptr) -> B_tree<tkey, tvalue, compare, t>;


template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool B_tree<tkey, tvalue, compare, t>::compare_pairs(const B_tree::tree_data_type &lhs,
                                                     const B_tree::tree_data_type &rhs) const
{
    return compare_keys(lhs.first, rhs.first);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool B_tree<tkey, tvalue, compare, t>::compare_keys(const tkey &lhs, const tkey &rhs) const
{
    return compare::operator()(lhs, rhs);
}


#endif //MP_OS_B_TREE_H
