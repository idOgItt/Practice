#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_BINARY_SEARCH_TREE_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_BINARY_SEARCH_TREE_H

#include <list>
#include <stack>
#include <vector>
#include <memory>
#include <logger.h>
#include <logger_guardant.h>
#include <not_implemented.h>
#include <search_tree.h>
#include <stack>
#include <pp_allocator.h>

template<typename tkey, typename tvalue, compator<tkey> compare>
class binary_search_tree final
{
public:

    using value_type = std::pair<const tkey, tvalue>;

protected:
    
    struct node
    {
    
    public:
        
        value_type data;

        node* parent;
        node* left_subtree;
        node* right_subtree;
        
        explicit node(
            tkey const &key,
            tvalue const &value);
        
        explicit node(
            tkey const &key,
            tvalue &&value);


        virtual ~node() =default;
    };

public:


    // region iterators definition

    class prefix_iterator;
    class prefix_const_iterator;
    class prefix_reverse_iterator;
    class prefix_const_reverse_iterator;

    class infix_iterator;
    class infix_const_iterator;
    class infix_reverse_iterator;
    class infix_const_reverse_iterator;

    class postfix_iterator;
    class postfix_const_iterator;
    class postfix_reverse_iterator;
    class postfix_const_reverse_iterator;
    
    class prefix_iterator
    {
    protected:

        node* _data;

        /** If iterator == end or before_begin _data points to nullptr, _backup to last node
         *
         */
        node* _backup;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference = ptrdiff_t;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::bidirectional_iterator_tag;
        
        explicit prefix_iterator(node* data = nullptr);

        virtual ~prefix_iterator() =default;

        bool operator==(
            prefix_iterator const &other) const noexcept;
        
        bool operator!=(
            prefix_iterator const &other) const noexcept;
        
        prefix_iterator &operator++() & noexcept;
        
        prefix_iterator const operator++(
            int not_used);

        prefix_iterator &operator--() & noexcept;

        prefix_iterator const operator--(
                int not_used);

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;
        
    };
    
    class prefix_const_iterator
    {
    protected:

        prefix_iterator _base;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference = ptrdiff_t;
        using reference = const value_type&;
        using pointer = value_type* const;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit prefix_const_iterator(const node* data = nullptr);

        virtual ~prefix_const_iterator() =default;

        bool operator==(
                prefix_iterator const &other) const noexcept;

        bool operator!=(
                prefix_iterator const &other) const noexcept;

        prefix_const_iterator &operator++() & noexcept;

        prefix_const_iterator const operator++(
                int not_used);

        prefix_const_iterator &operator--() & noexcept;

        prefix_const_iterator const operator--(
                int not_used);

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;
        
    };
    
    class prefix_reverse_iterator
    {
    protected:

        prefix_iterator _base;

    public:

        using value_type = binary_search_tree<tkey, tvalue, compare>::value_type;
        using difference = ptrdiff_t;
        using reference = const value_type&;
        using pointer = value_type* const;
        using iterator_category = std::bidirectional_iterator_tag;

        explicit prefix_reverse_iterator(node* data = nullptr);

        virtual ~prefix_reverse_iterator() =default;

        bool operator==(
                prefix_reverse_iterator const &other) const noexcept;

        bool operator!=(
                prefix_reverse_iterator const &other) const noexcept;

        prefix_reverse_iterator &operator++() & noexcept;

        prefix_reverse_iterator const operator++(
                int not_used);

        prefix_reverse_iterator &operator--() & noexcept;

        prefix_reverse_iterator const operator--(
                int not_used);

        /** Throws exception if end
         */
        reference operator*();

        /** UB if iterator points to end
         *
         */

        pointer operator->() noexcept;
        size_t depth() const noexcept;
        
    };
    
    class prefix_const_reverse_iterator
    {
    protected:

        std::unique_ptr<iterator_data> _data;
        std::stack<node**> _path;

    public:
        
        explicit prefix_const_reverse_iterator(const std::stack<node**>& path = std::stack<node**>(), iterator_data* data = nullptr);
    
    public:

        prefix_const_reverse_iterator(const prefix_const_reverse_iterator& other);
        prefix_const_reverse_iterator(prefix_const_reverse_iterator&& other) noexcept =default;

        prefix_const_reverse_iterator& operator=(const prefix_const_reverse_iterator& other);
        prefix_const_reverse_iterator& operator=(prefix_const_reverse_iterator&& other) noexcept =default;

        virtual ~prefix_const_reverse_iterator() =default;

        bool operator==(
            prefix_const_reverse_iterator const &other) const noexcept;
        
        bool operator!=(
            prefix_const_reverse_iterator const &other) const noexcept;
        
        prefix_const_reverse_iterator &operator++();
        
        prefix_const_reverse_iterator const operator++(
            int not_used);
        
        iterator_data const *operator*() const;
        
    };
    
    class infix_iterator
    {
    protected:

        std::unique_ptr<iterator_data> _data;
        std::stack<node**> _path;

    public:

        friend class binary_search_tree;

        explicit infix_iterator(const std::stack<node**>& path = std::stack<node**>(), iterator_data* data = nullptr);
    
    public:

        infix_iterator(const infix_iterator& other);
        infix_iterator(infix_iterator&& other) noexcept =default;

        infix_iterator& operator=(const infix_iterator& other);
        infix_iterator& operator=(infix_iterator&& other) noexcept =default;

        virtual ~infix_iterator() =default;

        bool operator==(
            infix_iterator const &other) const noexcept;
        
        bool operator!=(
            infix_iterator const &other) const noexcept;
        
        infix_iterator &operator++();
        
        infix_iterator const operator++(
            int not_used);
        
        iterator_data *operator*();
        
    };
    
    class infix_const_iterator
    {
    protected:

        std::unique_ptr<iterator_data> _data;
        std::stack<node**> _path;

    public:
        
        explicit infix_const_iterator(const std::stack<node**>& path = std::stack<node**>(), iterator_data* data = nullptr);
    
    public:

        infix_const_iterator(const infix_const_iterator& other);
        infix_const_iterator(infix_const_iterator&& other) noexcept =default;

        infix_const_iterator& operator=(const infix_const_iterator& other);
        infix_const_iterator& operator=(infix_const_iterator&& other) noexcept =default;

        virtual ~infix_const_iterator() =default;

        bool operator==(
            infix_const_iterator const &other) const noexcept;
        
        bool operator!=(
            infix_const_iterator const &other) const noexcept;
        
        infix_const_iterator &operator++();
        
        infix_const_iterator operator++(
            int not_used);
        
        iterator_data const *operator*() const;
        
    };
    
    class infix_reverse_iterator
    {
    protected:

        std::unique_ptr<iterator_data> _data;
        std::stack<node**> _path;

    public:
        
        explicit infix_reverse_iterator(const std::stack<node**>& path = std::stack<node**>(), iterator_data* data = nullptr);
    
    public:

        infix_reverse_iterator(const infix_reverse_iterator& other);
        infix_reverse_iterator(infix_reverse_iterator&& other) noexcept =default;

        infix_reverse_iterator& operator=(const infix_reverse_iterator& other);
        infix_reverse_iterator& operator=(infix_reverse_iterator&& other) noexcept =default;

        virtual ~infix_reverse_iterator() =default;

        bool operator==(
            infix_reverse_iterator const &other) const noexcept;
        
        bool operator!=(
            infix_reverse_iterator const &other) const noexcept;
        
        infix_reverse_iterator &operator++();
        
        infix_reverse_iterator const operator++(
            int not_used);
        
        iterator_data *operator*() const;
        
    };
    
    class infix_const_reverse_iterator
    {
    protected:

        std::unique_ptr<iterator_data> _data;
        std::stack<node**> _path;

    public:
        
        explicit infix_const_reverse_iterator(const std::stack<node**>& path = std::stack<node**>(), iterator_data* data = nullptr);
    
    public:

        infix_const_reverse_iterator(const infix_const_reverse_iterator& other);
        infix_const_reverse_iterator(infix_const_reverse_iterator&& other) noexcept =default;

        infix_const_reverse_iterator& operator=(const infix_const_reverse_iterator& other);
        infix_const_reverse_iterator& operator=(infix_const_reverse_iterator&& other) noexcept =default;

        virtual ~infix_const_reverse_iterator() =default;

        bool operator==(
            infix_const_reverse_iterator const &other) const noexcept;
        
        bool operator!=(
            infix_const_reverse_iterator const &other) const noexcept;
        
        infix_const_reverse_iterator &operator++();
        
        infix_const_reverse_iterator const operator++(
            int not_used);
        
        iterator_data const *operator*() const;
        
    };
    
    class postfix_iterator
    {
    protected:

        std::unique_ptr<iterator_data> _data;
        std::stack<node**> _path;

    public:
        
        explicit postfix_iterator(const std::stack<node**>& path = std::stack<node**>(), iterator_data* data = nullptr);
    
    public:

        postfix_iterator(const postfix_iterator& other);
        postfix_iterator(postfix_iterator&& other) noexcept =default;

        postfix_iterator& operator=(const postfix_iterator& other);
        postfix_iterator& operator=(postfix_iterator&& other) noexcept =default;

        virtual ~postfix_iterator() =default;

        bool operator==(
            postfix_iterator const &other) const noexcept;
        
        bool operator!=(
            postfix_iterator const &other) const noexcept;
        
        postfix_iterator &operator++();
        
        postfix_iterator const operator++(
            int not_used);
        
        iterator_data *operator*() const;
        
    };
    
    class postfix_const_iterator
    {
    protected:

        std::unique_ptr<iterator_data> _data;
        std::stack<node**> _path;

    public:
        
        explicit postfix_const_iterator(const std::stack<node**>& path = std::stack<node**>(), iterator_data* data = nullptr);
    
    public:

        postfix_const_iterator(const postfix_const_iterator& other);
        postfix_const_iterator(postfix_const_iterator&& other) noexcept =default;

        postfix_const_iterator& operator=(const postfix_const_iterator& other);
        postfix_const_iterator& operator=(postfix_const_iterator&& other) noexcept =default;

        virtual ~postfix_const_iterator() =default;

        bool operator==(
            postfix_const_iterator const &other) const noexcept;
        
        bool operator!=(
            postfix_const_iterator const &other) const noexcept;
        
        postfix_const_iterator &operator++();
        
        postfix_const_iterator const operator++(
            int not_used);
        
        iterator_data const *operator*() const;
        
    };
    
    class postfix_reverse_iterator
    {
    protected:

        std::unique_ptr<iterator_data> _data;
        std::stack<node**> _path;

    public:
        
        explicit postfix_reverse_iterator(const std::stack<node**>& path = std::stack<node**>(), iterator_data* data = nullptr);
    
    public:

        postfix_reverse_iterator(const postfix_reverse_iterator& other);
        postfix_reverse_iterator(postfix_reverse_iterator&& other) noexcept =default;

        postfix_reverse_iterator& operator=(const postfix_reverse_iterator& other);
        postfix_reverse_iterator& operator=(postfix_reverse_iterator&& other) noexcept =default;

        virtual ~postfix_reverse_iterator() =default;

        bool operator==(
            postfix_reverse_iterator const &other) const noexcept;
        
        bool operator!=(
            postfix_reverse_iterator const &other) const noexcept;
        
        postfix_reverse_iterator &operator++();
        
        postfix_reverse_iterator const operator++(
            int not_used);
        
        iterator_data *operator*() const;
        
    };
    
    class postfix_const_reverse_iterator
    {
    protected:

        std::unique_ptr<iterator_data> _data;
        std::stack<node**> _path;

    public:
        
        explicit postfix_const_reverse_iterator(const std::stack<node**>& path = std::stack<node**>(), iterator_data* data = nullptr);
    
    public:

        postfix_const_reverse_iterator(const postfix_const_reverse_iterator& other);
        postfix_const_reverse_iterator(postfix_const_reverse_iterator&& other) noexcept =default;

        postfix_const_reverse_iterator& operator=(const postfix_const_reverse_iterator& other);
        postfix_const_reverse_iterator& operator=(postfix_const_reverse_iterator&& other) noexcept =default;

        virtual ~postfix_const_reverse_iterator() =default;

        bool operator==(
            postfix_const_reverse_iterator const &other) const noexcept;
        
        bool operator!=(
            postfix_const_reverse_iterator const &other) const noexcept;
        
        postfix_const_reverse_iterator &operator++();
        
        postfix_const_reverse_iterator const operator++(
            int not_used);
        
        iterator_data const *operator*() const;
        
    };

    friend class prefix_iterator;
    friend class prefix_const_iterator;
    friend class prefix_reverse_iterator;
    friend class prefix_const_reverse_iterator;

    friend class postfix_iterator;
    friend class postfix_const_iterator;
    friend class postfix_reverse_iterator;
    friend class postfix_const_reverse_iterator;

    friend class infix_iterator;
    friend class infix_const_iterator;
    friend class infix_reverse_iterator;
    friend class infix_const_reverse_iterator;

    // endregion iterators definition

public:
    
    // region target operations strategies definition
    
    enum class insertion_of_existent_key_attempt_strategy
    {
        update_value,
        throw_an_exception
    };
    
    enum class disposal_of_nonexistent_key_attempt_strategy
    {
        do_nothing,
        throw_an_exception
    };
    
    // endregion target operations strategies definition
    
    // region target operations associated exception types
    
    class insertion_of_existent_key_attempt_exception final:
        public std::logic_error
    {
    
    private:
        
        tkey _key;
    
    public:
        
        explicit insertion_of_existent_key_attempt_exception(
            tkey const &key);
        
    public:
        
        tkey const &get_key() const noexcept;
    
    };
    
    class obtaining_of_nonexistent_key_attempt_exception final:
        public std::logic_error
    {
    
    private:
        
        tkey _key;
        
    public:
        
        explicit obtaining_of_nonexistent_key_attempt_exception(
            tkey const &key);
        
    public:
        
        tkey const &get_key() const noexcept;
        
    };
    
    class disposal_of_nonexistent_key_attempt_exception final:
        public std::logic_error
    {
    
    private:
        
        tkey _key;
    
    public:
        
        explicit disposal_of_nonexistent_key_attempt_exception(
            tkey const &key);
        
    public:
        
        tkey const &get_key() const noexcept;
    
    };
    
    // endregion target operations associated exception types


protected:
    
    mutable node *_root;
    
    insertion_of_existent_key_attempt_strategy _insertion_stratagy;
    
    disposal_of_nonexistent_key_attempt_strategy _disposal_strategy;

public:
    explicit binary_search_tree(
            std::function<int(tkey const &, tkey const &)> comparer,
            smart_mem_resource *allocator = nullptr,
            logger *logger = nullptr,
            typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy = binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy::throw_an_exception,
            typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy = binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy::throw_an_exception);

public:
    
    binary_search_tree(
        binary_search_tree<tkey, tvalue> const &other);
    
    binary_search_tree(
        binary_search_tree<tkey, tvalue> &&other) noexcept;
    
    binary_search_tree<tkey, tvalue> &operator=(
        binary_search_tree<tkey, tvalue> const &other);
    
    binary_search_tree<tkey, tvalue> &operator=(
        binary_search_tree<tkey, tvalue> &&other) noexcept;
    
    ~binary_search_tree() override;

public:
    
    void insert(
        tkey const &key,
        tvalue const &value) final;
    
    void insert(
        tkey const &key,
        tvalue &&value) final;
    
    tvalue const &obtain(
        tkey const &key) final;
    
    std::vector<typename associative_container<tkey, tvalue>::key_value_pair> obtain_between(
        tkey const &lower_bound,
        tkey const &upper_bound,
        bool lower_bound_inclusive,
        bool upper_bound_inclusive) final;
    
    tvalue dispose(tkey const &key) final;
    
public:
    
    void set_insertion_strategy(typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy) noexcept;
    
    void set_removal_strategy(typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy) noexcept;

public:
    
    // region iterators requests definition
    
    prefix_iterator begin_prefix() noexcept;
    
    prefix_iterator end_prefix() noexcept;
    
    prefix_const_iterator cbegin_prefix() const noexcept;
    
    prefix_const_iterator cend_prefix() const noexcept;
    
    prefix_reverse_iterator rbegin_prefix() noexcept;
    
    prefix_reverse_iterator rend_prefix() noexcept;
    
    prefix_const_reverse_iterator crbegin_prefix() const noexcept;
    
    prefix_const_reverse_iterator crend_prefix() const noexcept;
    
    infix_iterator begin_infix() noexcept;
    
    infix_iterator end_infix() noexcept;
    
    infix_const_iterator cbegin_infix() const noexcept;
    
    infix_const_iterator cend_infix() const noexcept;
    
    infix_reverse_iterator rbegin_infix() noexcept;
    
    infix_reverse_iterator rend_infix() noexcept;
    
    infix_const_reverse_iterator crbegin_infix() const noexcept;
    
    infix_const_reverse_iterator crend_infix() const noexcept;
    
    postfix_iterator begin_postfix() noexcept;
    
    postfix_iterator end_postfix() noexcept;
    
    postfix_const_iterator cbegin_postfix() const noexcept;
    
    postfix_const_iterator cend_postfix() const noexcept;
    
    postfix_reverse_iterator rbegin_postfix() noexcept;
    
    postfix_reverse_iterator rend_postfix() noexcept;
    
    postfix_const_reverse_iterator crbegin_postfix() const noexcept;
    
    postfix_const_reverse_iterator crend_postfix() const noexcept;
    
    // endregion iterators requests definition

protected:

    std::stack<node**> find_path(const tkey&);

    virtual void insert_inner(std::stack<node**>& node_path, const tkey& key, tvalue&& val);

    virtual void insert_inner(std::stack<node**>& node_path, const tkey& key, const tvalue& val);

    virtual tvalue& obtain_inner(std::stack<node**>& node_path);

    virtual tvalue dispose_inner(std::stack<node**>& node_path);

    void destroy_subtree(node* n) noexcept;

    virtual void copy_subtree(node** target, node* src);

    static bool is_left_subtree(node* child, node* parent) noexcept;

    virtual void actions_after_update_insert(std::stack<node**>& path);

    static node** get_last_node(infix_iterator& it);

    // region subtree rotations definition
    
    void small_left_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root) const;
    
    void small_right_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root) const;
    
    void big_left_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root) const;
    
    void big_right_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root) const;
    
    void double_left_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root) const;
    
    void double_right_rotation(
        typename binary_search_tree<tkey, tvalue>::node *&subtree_root) const;
    
    // endregion subtree rotations definition
    
};


#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_BINARY_SEARCH_TREE_H