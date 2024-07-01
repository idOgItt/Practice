#ifndef MP_OS_WORKBENCH_HASH_TABLE_H
#define MP_OS_WORKBENCH_HASH_TABLE_H

#include <associative_container.h>
#include <not_implemented.h>
#include <vector>
#include <logger.h>
#include <map>
#include <pp_allocator.h>

// TODO: concept search_ds
template<typename T, typename tkey, typename tvalue>
concept search_ds_for = std::same_as<typename T::value_type, std::pair<const tkey, tvalue>> && std::copy_constructible<std::pair<const tkey, tvalue>> && std::copy_constructible<T> && std::ranges::forward_range<T> &&
            requires (T t, tkey key, tvalue val)
            {
                {t.insert(std::make_pair(key, val)).first} -> std::forward_iterator;
                {t.insert(std::make_pair(key, val)).second} -> std::same_as<bool>;
                {t.find(key)} -> std::forward_iterator;
                {t.erase(key)} -> std::forward_iterator;
            };

template<typename tkey, typename tvalue, search_ds_for<tkey, tvalue> sds = std::map<tkey, tvalue, std::less<tkey>, pp_allocator<std::pair<const tkey, tvalue>>>, typename hash = std::hash<tkey>>
class hash_table final
{

public:

    using value_type = std::pair<const tkey, tvalue>;
    using sds_it = std::ranges::iterator_t<sds>;
    using sds_cit = std::ranges::const_iterator_t<sds>;

private:

    using vector = std::vector<sds, pp_allocator<sds>>;

    vector _buckets;
    pp_allocator<value_type> _alloc;
    size_t _size;
    size_t _used_buckets;
    double _max_load_factor;
    logger* _logger;

public:

    // region constructors declaration

    explicit hash_table(pp_allocator<value_type> = pp_allocator<value_type>(), logger* logger = nullptr);

    template<input_iterator_for_pair<tkey, tvalue> iterator>
    explicit hash_table(iterator begin, iterator end, pp_allocator<value_type> = pp_allocator<value_type>(), logger* logger = nullptr);

    hash_table(std::initializer_list<std::pair<tkey, tvalue>> data, pp_allocator<value_type> = pp_allocator<value_type>(), logger* logger = nullptr);

    // endregion constructors declaration

    // region five declaration

    hash_table(const hash_table& other);

    hash_table(hash_table&& other) noexcept;

    hash_table& operator=(const hash_table& other);

    hash_table& operator=(hash_table&& other) noexcept;

    ~hash_table() noexcept;

    // endregion five declaration

    // region iterator

    class iterator final
    {
        vector::iterator _bucket_it;
        vector::iterator _bucket_sentinel;

        sds_it _data_it;
        sds_it _data_sentinel;

    public:

        using value_type = std::pair<const tkey, tvalue>;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using pointer = value_type *;
        using iterator_category = std::forward_iterator_tag;
        using self = iterator;

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;

        explicit iterator(vector::iterator begin = vector::iterator(), vector::iterator end = vector::iterator());

        /** data_beg MUST be part of begin iterator, UB otherwise
         */
        explicit iterator(vector::iterator begin = vector::iterator(), vector::iterator end = vector::iterator(), sds_it data_beg = sds_it());

    };

    class const_iterator final
    {
        vector::const_iterator _bucket_it;
        vector::const_iterator _bucket_sentinel;

        sds_cit _data_it;
        sds_cit _data_sentinel;

    public:

        using value_type = std::pair<const tkey, tvalue>;
        using difference_type = ptrdiff_t;
        using reference = value_type&;
        using pointer = value_type *;
        using iterator_category = std::forward_iterator_tag;
        using self = const_iterator;

        reference operator*() const noexcept;
        pointer operator->() const noexcept;

        self& operator++();
        self operator++(int);

        bool operator==(const self& other) const noexcept;
        bool operator!=(const self& other) const noexcept;


        const_iterator(const iterator&);
        explicit const_iterator(vector::const_iterator begin = vector::const_iterator(), vector::const_iterator end = vector::const_iterator());

        /** data_beg MUST be part of begin iterator, UB otherwise
         */
        explicit const_iterator(vector::const_iterator begin = vector::const_iterator(), vector::const_iterator end = vector::const_iterator(), sds_cit data_beg = sds_cit());
    };

    friend class iterator;
    friend class const_iterator;

    // endregion iterator

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

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    const_iterator cbegin();
    const_iterator cend();

    // endregion iterator begins declaration

    // region lookup declaration

    size_t size() const noexcept;
    bool empty() const noexcept;

    /*
     * Returns end() if not exist
     */

    iterator find(const tkey& key);
    const_iterator find(const tkey& key) const;

    iterator lower_bound(const tkey& key);
    const_iterator lower_bound(const tkey& key) const;

    iterator upper_bound(const tkey& key);
    const_iterator upper_bound(const tkey& key) const;

    bool contains(const tkey& key) const;

    // endregion lookup declaration

    // region modifiers declaration

    void clear() noexcept;

    /*
     * Does nothing if key exists, delegates to emplace.
     * Second return value is true, when inserted
     */
    std::pair<iterator, bool> insert(const value_type & data);
    std::pair<iterator, bool> insert(value_type && data);

    template <typename ...Args>
    std::pair<iterator, bool> emplace(Args&&... args);

    /*
     * Updates value if key exists, delegates to emplace.
     */
    iterator insert_or_assign(const value_type & data);
    iterator insert_or_assign(value_type && data);

    template <typename ...Args>
    iterator emplace_or_assign(Args&&... args);

    /*
     * Return iterator to node next ro removed or end() if key not exists
     */
    iterator erase(iterator pos);
    iterator erase(const_iterator pos);

    iterator erase(iterator beg, iterator en);
    iterator erase(const_iterator beg, const_iterator en);


    iterator erase(const tkey& key);

    // endregion modifiers declaration

    // region hash policy

    double max_load_factor() const;
    void max_load_factor(double ml);

    double load_factor() const;

    void rehash(size_t count);
    void reserve(size_t count);

    // endregion hash policy
};


#endif //MP_OS_WORKBENCH_HASH_TABLE_H