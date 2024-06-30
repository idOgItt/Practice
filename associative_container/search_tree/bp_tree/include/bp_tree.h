//
// Created by Des Caldnd on 5/9/2024.
//

#ifndef MP_OS_BP_TREE_H
#define MP_OS_BP_TREE_H

#include <search_tree.h>

template <typename tkey, typename tvalue, compator<tkey> compare = std::less<tkey>, std::size_t t = 5>
class Bp_tree final : public allocator_guardant, public logger_guardant, private compare
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

    // region nodes declaration

    struct bptree_node
    {
        size_t size;
        const bool is_terminate;

        bptree_node(bool term) noexcept;
    };

    struct bptree_node_middle : public bptree_node
    {
        std::array<tkey, maximum_keys_in_node + 1> keys;
        std::array<bptree_node*, maximum_keys_in_node + 2> pointers;

        bptree_node_middle() noexcept;
    };

    struct bptree_node_terminate : public bptree_node
    {
        std::array<tree_data_type, maximum_keys_in_node + 1> keys;
        bptree_node_terminate* forward;

        bptree_node_terminate() noexcept;
    };

    // endregion nodes declaration

    struct path_t
    {
        std::stack<std::pair<bptree_node**, size_t>> _path;
        size_t _index;
        std::pair<bptree_node_middle*, size_t> _parent;
    };

    allocator_dbg_helper* _allocator;
    logger* _logger;

    mutable bptree_node* _root;

    size_t _size;

    logger* get_logger() const noexcept override;
    allocator_dbg_helper* get_allocator() const noexcept override;

public:

    // region constructors declaration

    explicit Bp_tree(const compare& cmp = compare(), allocator_dbg_helper* allocator = nullptr, logger* logger = nullptr);

    template<input_iterator_for_pair<tkey, tvalue> iterator>
    explicit Bp_tree(iterator begin, iterator end, const compare& cmp = compare(), allocator_dbg_helper* allocator = nullptr, logger* logger = nullptr);


    Bp_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp = compare(), allocator_dbg_helper* allocator = nullptr, logger* logger = nullptr);

    // endregion constructors declaration

    // region five declaration

    Bp_tree(const Bp_tree& other);
    Bp_tree(Bp_tree&& other) noexcept;

    Bp_tree& operator=(const Bp_tree& other);
    Bp_tree& operator=(Bp_tree&& other) noexcept;

    ~Bp_tree() noexcept override;

    // endregion five declaration

    // region iterators declaration

    class bptree_iterator;
    class bptree_const_iterator;

    class bptree_iterator
    {
        bptree_node_terminate* _node;
        size_t _index;

    public:
        using value_type = tree_data_type_const;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = ptrdiff_t;

        using self = bptree_iterator;

        friend class Bp_tree;
        friend class bptree_const_iterator;

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t current_node_keys_count() const noexcept;

        explicit bptree_iterator(bptree_node_terminate* node = nullptr, size_t index = 0);
    };

    class bptree_const_iterator
    {
        bptree_node_terminate* _node;
        size_t _index;
    public:
        using value_type = tree_data_type_const;
        using reference = const value_type&;
        using pointer = const value_type*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = ptrdiff_t;

        using self = bptree_const_iterator;

        friend class Bp_tree;
        friend class bptree_iterator;

        bptree_const_iterator(const bptree_iterator& it) noexcept;

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        size_t current_node_keys_count() const noexcept;

        explicit bptree_const_iterator(bptree_node_terminate* node = nullptr, size_t index = 0);
    };

    friend class bptree_iterator;
    friend class bptree_const_iterator;

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

    bptree_iterator begin();
    bptree_iterator end();

    bptree_const_iterator begin() const;
    bptree_const_iterator end() const;

    bptree_const_iterator cbegin() const;
    bptree_const_iterator cend() const;

    // endregion iterator begins declaration

    // region lookup declaration

    size_t size() const noexcept;

    bool empty() const noexcept;

    /*
     * Returns end() if not exist
     */
    bptree_iterator find(const tkey& key);
    bptree_const_iterator find(const tkey& key) const;

    std::pair<bptree_iterator, bptree_iterator> find_range(const tkey& lower, const tkey& upper, bool include_lower = true, bool include_upper = false);

    std::pair<bptree_const_iterator, bptree_const_iterator> find_range(const tkey& lower, const tkey& upper, bool include_lower = true, bool include_upper = false) const;

    bool contains(const tkey& key) const;

    // endregion lookup declaration

    // region modifiers declaration

    void clear() noexcept;

    /*
     * Does nothing if key exists, delegates to emplace.
     * Second return value is true, when inserted
     */
    std::pair<bptree_iterator, bool> insert(const tree_data_type& data);
    std::pair<bptree_iterator, bool> insert(tree_data_type&& data);

    template <typename ...Args>
    std::pair<bptree_iterator, bool> emplace(Args&&... args);

    /*
     * Updates value if key exists, delegates to emplace.
     */
    bptree_iterator insert_or_assign(const tree_data_type& data);
    bptree_iterator insert_or_assign(tree_data_type&& data);

    template <typename ...Args>
    bptree_iterator emplace_or_assign(Args&&... args);

    /*
     * Return iterator to node next ro removed or end() if key not exists
     */
    bptree_iterator erase(bptree_iterator pos);
    bptree_iterator erase(const tkey& key);

    // endregion modifiers declaration

private:

    void destroy_node(bptree_node* node) noexcept;

    bptree_node* copy_subtree(bptree_node* parent, bptree_node* copyable);

    void destroy_subtree(bptree_node* node) noexcept;

    path_t find_path(const tkey& key) const noexcept;

    std::pair<size_t, bool> find_index(const tkey& key, bptree_node* node) const noexcept;

    static bool exists(bptree_node* node, size_t ind) noexcept;

    static bool is_terminate_node(bptree_node* node) noexcept;

    bptree_iterator erase_inner(path_t path, size_t index) noexcept;

    bptree_iterator emplace_inner(tree_data_type&& data, path_t path);

    static void insert_array(bptree_node* node, bptree_node* right_node, tree_data_type&& data, size_t index) noexcept;

    static bptree_node* remove_array(bptree_node* node, size_t index, bool remove_left_ptr = true) noexcept;
};

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename Bp_tree<tkey, tvalue, compare, t>::bptree_node* Bp_tree<tkey, tvalue, compare, t>::copy_subtree(Bp_tree::bptree_node *parent, Bp_tree::bptree_node *copyable)
{
    if (copyable == nullptr)
        return nullptr;

    if (copyable->is_terminate)
    {
        auto new_node = reinterpret_cast<bptree_node_terminate *>(allocate_with_guard(sizeof(bptree_node_terminate)));

        try
        {
            allocator_dbg_helper::construct(new_node, *static_cast<bptree_node_terminate*>(copyable));
        } catch (...)
        {
            deallocate_with_guard(new_node);
            throw;
        }

        return new_node;
    } else
    {

    }
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool Bp_tree<tkey, tvalue, compare, t>::is_terminate_node(Bp_tree::bptree_node *node) noexcept
{
    return node != nullptr && node->is_terminate;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool Bp_tree<tkey, tvalue, compare, t>::exists(Bp_tree::bptree_node *node, size_t ind) noexcept
{
    return node != nullptr && ind < node->size;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::bptree_const_iterator(
        const Bp_tree::bptree_iterator &it) noexcept : _node(it._node), _index(it._index) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename Bp_tree<tkey, tvalue, compare, t>::bptree_iterator::reference Bp_tree<tkey, tvalue, compare, t>::bptree_iterator::operator*() const noexcept
{
    return *reinterpret_cast<tree_data_type_const*>(&_node->keys[_index]);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename Bp_tree<tkey, tvalue, compare, t>::bptree_iterator::pointer Bp_tree<tkey, tvalue, compare, t>::bptree_iterator::operator->() const noexcept
{
    return reinterpret_cast<tree_data_type_const*>(&_node->keys[_index]);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename Bp_tree<tkey, tvalue, compare, t>::Bp_tree::bptree_iterator::self &Bp_tree<tkey, tvalue, compare, t>::bptree_iterator::operator++()
{
    if (_index < _node->size - 1)
        ++_index;
    else
    {
        _index = 0;
        _node = _node->forward;
    }
    return *this;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename Bp_tree<tkey, tvalue, compare, t>::bptree_iterator::self Bp_tree<tkey, tvalue, compare, t>::bptree_iterator::operator++(int)
{
    auto tmp = *this;
    ++(*this);
    return tmp;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool Bp_tree<tkey, tvalue, compare, t>::bptree_iterator::operator==(
        const Bp_tree::bptree_iterator::self &other) const noexcept
{
    if (_node == nullptr && other._node == nullptr)
        return true;
    return _node == other._node && _index == other._index;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool Bp_tree<tkey, tvalue, compare, t>::bptree_iterator::operator!=(
        const Bp_tree::bptree_iterator::self &other) const noexcept
{
    return !(*this == other);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t Bp_tree<tkey, tvalue, compare, t>::bptree_iterator::current_node_keys_count() const noexcept
{
    return _node == nullptr ? 0 : _node->size;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t>::bptree_iterator::bptree_iterator(Bp_tree::bptree_node_terminate *node, size_t index) : _node(node), _index(index) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::reference Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::operator*() const noexcept
{
    return *reinterpret_cast<tree_data_type_const*>(&_node->keys[_index]);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::pointer Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::operator->() const noexcept
{
    return reinterpret_cast<tree_data_type_const*>(&_node->keys[_index]);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename Bp_tree<tkey, tvalue, compare, t>::Bp_tree::bptree_const_iterator::self &Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::operator++()
{
    if (_index < _node->size - 1)
        ++_index;
    else
    {
        _index = 0;
        _node = _node->forward;
    }
    return *this;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
typename Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::self Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::operator++(int)
{
    auto tmp = *this;
    ++(*this);
    return tmp;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::operator==(
        const Bp_tree::bptree_const_iterator::self &other) const noexcept
{
    if (_node == nullptr && other._node == nullptr)
        return true;
    return _node == other._node && _index == other._index;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::operator!=(
        const Bp_tree::bptree_const_iterator::self &other) const noexcept
{
    return !(*this == other);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
size_t Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::current_node_keys_count() const noexcept
{
    return _node == nullptr ? 0 : _node->size;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t>::bptree_const_iterator::bptree_const_iterator(Bp_tree::bptree_node_terminate *node, size_t index) : _node(node), _index(index) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t> &Bp_tree<tkey, tvalue, compare, t>::operator=(const Bp_tree &other)
{
    if (this != &other)
    {
        bptree_node* tmp = copy_subtree(nullptr, other._root);
        destroy_subtree(_root);
        _root = tmp;
        compare::operator=(other);
        _size = other._size;
        _allocator = other._allocator;
        _logger = other._logger;
    }
    return *this;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t>::Bp_tree(const Bp_tree &other) : compare(other), _allocator(other._allocator), _logger(other._logger), _size(other._size)
{
    _root = copy_subtree(nullptr, other._root);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t>::~Bp_tree() noexcept
{
    destroy_subtree(_root);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t> &Bp_tree<tkey, tvalue, compare, t>::operator=(Bp_tree &&other) noexcept
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
Bp_tree<tkey, tvalue, compare, t>::Bp_tree(Bp_tree &&other) noexcept : compare(other), _allocator(other._allocator), _logger(other._logger), _root(other._root), _size(other._size)
{
    other._root = nullptr;
    other._size = 0;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
template<input_iterator_for_pair<tkey, tvalue> iterator>
Bp_tree<tkey, tvalue, compare, t>::Bp_tree(iterator begin, iterator end, const compare &cmp, allocator_dbg_helper *allocator,
                                           logger *logger) : compare(cmp), _allocator(allocator), _logger(logger), _root(nullptr), _size(0)
{
    for (; begin != end; ++begin)
    {
        emplace_or_assign(*begin);
    }
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t>::Bp_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp, allocator_dbg_helper* allocator, logger* logger) : compare(cmp), _allocator(allocator), _logger(logger), _root(nullptr), _size(0)
{
    for (auto& val : data)
    {
        emplace_or_assign(val);
    }
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t>::Bp_tree(const compare &cmp, allocator_dbg_helper *allocator, logger *logger) : compare(cmp), _allocator(allocator), _logger(logger), _root(nullptr), _size(0){}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t>::bptree_node_terminate::bptree_node_terminate() noexcept : bptree_node(true)
{
    forward = nullptr;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t>::bptree_node_middle::bptree_node_middle() noexcept : bptree_node(false)
{
    pointers[0] = nullptr;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
Bp_tree<tkey, tvalue, compare, t>::bptree_node::bptree_node(bool term) noexcept : size(0), is_terminate(term) {}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
logger *Bp_tree<tkey, tvalue, compare, t>::get_logger() const noexcept
{
    return _logger;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
allocator_dbg_helper *Bp_tree<tkey, tvalue, compare, t>::get_allocator() const noexcept
{
    return _allocator;
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
void Bp_tree<tkey, tvalue, compare, t>::destroy_node(Bp_tree::bptree_node *node) noexcept
{
    if (node->is_terminate)
    {
        auto tmp = static_cast<bptree_node_terminate*>(node);
        allocator_dbg_helper::destruct(tmp);
        deallocate_with_guard(tmp);
    } else
    {
        auto tmp = static_cast<bptree_node_middle*>(node);
        allocator_dbg_helper::destruct(tmp);
        deallocate_with_guard(tmp);
    }
}

template<std::input_iterator iterator, compator<typename std::iterator_traits<iterator>::value_type::first_type> compare = std::less<typename std::iterator_traits<iterator>::value_type::first_type>,
        std::size_t t = 5>
Bp_tree(iterator begin, iterator end, const compare &cmp = compare(), allocator_dbg_helper *allocator = nullptr,
        logger *logger = nullptr) -> Bp_tree<typename std::iterator_traits<iterator>::value_type::first_type, typename std::iterator_traits<iterator>::value_type::second_type, compare, t>;

template<typename tkey, typename tvalue, compator<tkey> compare = std::less<tkey>, std::size_t t = 5>
Bp_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare &cmp = compare(), allocator_dbg_helper *allocator = nullptr,
        logger *logger = nullptr) -> Bp_tree<tkey, tvalue, compare, t>;


template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool Bp_tree<tkey, tvalue, compare, t>::compare_pairs(const Bp_tree::tree_data_type &lhs,
                                                     const Bp_tree::tree_data_type &rhs) const
{
    return compare_keys(lhs.first, rhs.first);
}

template<typename tkey, typename tvalue, compator<tkey> compare, std::size_t t>
bool Bp_tree<tkey, tvalue, compare, t>::compare_keys(const tkey &lhs, const tkey &rhs) const
{
    return compare::operator()(lhs, rhs);
}

#endif //MP_OS_BP_TREE_H
