#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_AVL_TREE_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_AVL_TREE_H

#include <binary_search_tree.h>

template<typename tkey, typename tvalue>
class AVL_tree final:
    public binary_search_tree<tkey, tvalue>
{

private:
    
    struct node final:
        binary_search_tree<tkey, tvalue>::node
    {
        size_t height;

        ~node() noexcept override =default;
    };

public:
    
    struct iterator_data final:
        public binary_search_tree<tkey, tvalue>::iterator_data
    {
    
    public:
        
        size_t subtree_height;
    
    public:
        
        explicit iterator_data(
            unsigned int depth = 0,
            tkey const &key = tkey(),
            tvalue const &value = tvalue(),
            size_t subtree_height = 0);
        
    };

public:

    // region iterator definition

    class prefix_iterator : public binary_search_tree<tkey, tvalue>::prefix_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::prefix_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::prefix_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::prefix_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::prefix_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::prefix_iterator::_data->depth = binary_search_tree<tkey, tvalue>::prefix_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::prefix_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::prefix_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::prefix_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::prefix_iterator::_data.get())); }

    public:

        explicit prefix_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::prefix_iterator(path, data) {}

    };

    class prefix_const_iterator : public binary_search_tree<tkey, tvalue>::prefix_const_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::prefix_const_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::prefix_const_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::prefix_const_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::prefix_const_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::prefix_const_iterator::_data->depth = binary_search_tree<tkey, tvalue>::prefix_const_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::prefix_const_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::prefix_const_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::prefix_const_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::prefix_const_iterator::_data.get())); }

    public:

        explicit prefix_const_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::prefix_const_iterator(path, data) {}

    };

    class prefix_reverse_iterator : public binary_search_tree<tkey, tvalue>::prefix_reverse_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::_data->depth = binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::prefix_reverse_iterator::_data.get())); }

    public:

        explicit prefix_reverse_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::prefix_reverse_iterator(path, data) {}

    };

    class prefix_const_reverse_iterator : public binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::_data->depth = binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator::_data.get())); }

    public:

        explicit prefix_const_reverse_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::prefix_const_reverse_iterator(path, data) {}

    };

    class infix_iterator : public binary_search_tree<tkey, tvalue>::infix_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::infix_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::infix_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::infix_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::infix_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::infix_iterator::_data->depth = binary_search_tree<tkey, tvalue>::infix_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::infix_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::infix_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::infix_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::infix_iterator::_data.get())); }

    public:

        explicit infix_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::infix_iterator(path, data) {}

    };

    class infix_const_iterator : public binary_search_tree<tkey, tvalue>::infix_const_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::infix_const_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::infix_const_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::infix_const_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::infix_const_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::infix_const_iterator::_data->depth = binary_search_tree<tkey, tvalue>::infix_const_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::infix_const_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::infix_const_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::infix_const_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::infix_const_iterator::_data.get())); }

    public:

        explicit infix_const_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::infix_const_iterator(path, data) {}

    };

    class infix_reverse_iterator : public binary_search_tree<tkey, tvalue>::infix_reverse_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::infix_reverse_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::infix_reverse_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::infix_reverse_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::infix_reverse_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::infix_reverse_iterator::_data->depth = binary_search_tree<tkey, tvalue>::infix_reverse_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::infix_reverse_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::infix_reverse_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::infix_reverse_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::infix_reverse_iterator::_data.get())); }

    public:

        explicit infix_reverse_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::infix_reverse_iterator(path, data) {}

    };

    class infix_const_reverse_iterator : public binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::_data->depth = binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator::_data.get())); }

    public:

        explicit infix_const_reverse_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::infix_const_reverse_iterator(path, data) {}

    };

    class postfix_iterator : public binary_search_tree<tkey, tvalue>::postfix_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::postfix_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::postfix_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::postfix_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::postfix_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::postfix_iterator::_data->depth = binary_search_tree<tkey, tvalue>::postfix_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::postfix_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::postfix_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::postfix_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::postfix_iterator::_data.get())); }

    public:

        explicit postfix_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::postfix_iterator(path, data) {}

    };

    class postfix_const_iterator : public binary_search_tree<tkey, tvalue>::postfix_const_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::postfix_const_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::postfix_const_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::postfix_const_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::postfix_const_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::postfix_const_iterator::_data->depth = binary_search_tree<tkey, tvalue>::postfix_const_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::postfix_const_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::postfix_const_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::postfix_const_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::postfix_const_iterator::_data.get())); }

    public:

        explicit postfix_const_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::postfix_const_iterator(path, data) {}

    };

    class postfix_reverse_iterator : public binary_search_tree<tkey, tvalue>::postfix_reverse_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::_data->depth = binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::postfix_reverse_iterator::_data.get())); }

    public:

        explicit postfix_reverse_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::postfix_reverse_iterator(path, data) {}

    };

    class postfix_const_reverse_iterator : public binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator
    {
        void update_value(binary_search_tree<tkey, tvalue>::iterator_data* data) override
        {
            binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::_data->key = (*binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::_path.top())->key;
            binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::_data->value = (*binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::_path.top())->value;
            binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::_data->depth = binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::_path.size() - 1;
            static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::_data.get())->subtree_height = static_cast<node*>(*binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::_path.top())->height;
        }

        binary_search_tree<tkey, tvalue>::iterator_data* clone_data() override { return binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::_data.get() == nullptr ? nullptr : new iterator_data(*static_cast<iterator_data*>(binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator::_data.get())); }

    public:

        explicit postfix_const_reverse_iterator(const std::stack<typename binary_search_tree<tkey, tvalue>::node**>& path = std::stack<typename binary_search_tree<tkey, tvalue>::node**>(), iterator_data* data = nullptr) : binary_search_tree<tkey, tvalue>::postfix_const_reverse_iterator(path, data) {}

    };

    // endregion iterator definition
    
    // region iterator requests declaration

    prefix_iterator begin_prefix() const noexcept;

    prefix_iterator end_prefix() const noexcept;

    prefix_const_iterator cbegin_prefix() const noexcept;

    prefix_const_iterator cend_prefix() const noexcept;

    prefix_reverse_iterator rbegin_prefix() const noexcept;

    prefix_reverse_iterator rend_prefix() const noexcept;

    prefix_const_reverse_iterator crbegin_prefix() const noexcept;

    prefix_const_reverse_iterator crend_prefix() const noexcept;

    infix_iterator begin_infix() const noexcept;

    infix_iterator end_infix() const noexcept;

    infix_const_iterator cbegin_infix() const noexcept;

    infix_const_iterator cend_infix() const noexcept;

    infix_reverse_iterator rbegin_infix() const noexcept;

    infix_reverse_iterator rend_infix() const noexcept;

    infix_const_reverse_iterator crbegin_infix() const noexcept;

    infix_const_reverse_iterator crend_infix() const noexcept;

    postfix_iterator begin_postfix() const noexcept;

    postfix_iterator end_postfix() const noexcept;

    postfix_const_iterator cbegin_postfix() const noexcept;

    postfix_const_iterator cend_postfix() const noexcept;

    postfix_reverse_iterator rbegin_postfix() const noexcept;

    postfix_reverse_iterator rend_postfix() const noexcept;

    postfix_const_reverse_iterator crbegin_postfix() const noexcept;

    postfix_const_reverse_iterator crend_postfix() const noexcept;
    
    // endregion iterator requests declaration
    
    explicit AVL_tree(
        std::function<int(tkey const &, tkey const &)> comparer,
        allocator *allocator = nullptr,
        logger *logger = nullptr,
        typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy = binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy::throw_an_exception,
        typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy = binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy::throw_an_exception);

public:
    
    ~AVL_tree() noexcept final =default;
    
    AVL_tree(
        AVL_tree<tkey, tvalue> const &other);
    
    AVL_tree<tkey, tvalue> &operator=(
        AVL_tree<tkey, tvalue> const &other);
    
    AVL_tree(
        AVL_tree<tkey, tvalue> &&other) noexcept =default;
    
    AVL_tree<tkey, tvalue> &operator=(
        AVL_tree<tkey, tvalue> &&other) noexcept =default;

private:

    void insert_inner(std::stack<typename binary_search_tree<tkey, tvalue>::node**>& node_path, const tkey& key, tvalue&& val) override;

    void insert_inner(std::stack<typename binary_search_tree<tkey, tvalue>::node**>& node_path, const tkey& key, const tvalue& val) override;

    template<typename tval_arg>
    void insert_inner_t(std::stack<typename binary_search_tree<tkey, tvalue>::node**>& node_path, const tkey& key, tval_arg&& val);

    tvalue dispose_inner(std::stack<typename binary_search_tree<tkey, tvalue>::node**>& node_path) override;

    void copy_subtree(typename binary_search_tree<tkey, tvalue>::node** target, typename binary_search_tree<tkey, tvalue>::node* src) override;
    
};

template<typename tkey, typename tvalue>
void AVL_tree<tkey, tvalue>::insert_inner(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &node_path, const tkey &key, tvalue&& val)
{
    insert_inner_t(node_path, key, std::move(val));
}

template<typename tkey, typename tvalue>
void AVL_tree<tkey, tvalue>::insert_inner(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &node_path, const tkey &key, const tvalue& val)
{
    insert_inner_t(node_path, key, val);
}

template<typename tkey, typename tvalue>
void AVL_tree<tkey, tvalue>::copy_subtree(typename binary_search_tree<tkey, tvalue>::node** target, typename binary_search_tree<tkey, tvalue>::node* src)
{
    if(src == nullptr)
    {
        *target = nullptr;
        return;
    }

    *target = reinterpret_cast<node*>(allocator_guardant::allocate_with_guard(sizeof(node)));
    try
    {
        allocator::construct(*static_cast<node**>(target), *static_cast<node*>(src));
    } catch(...)
    {
        allocator_guardant::deallocate_with_guard(*target);
        *target = nullptr;
        throw;
    }

    (*target)->right_subtree = nullptr;
    (*target)->left_subtree = nullptr;

    copy_subtree(&((*target)->left_subtree), src->left_subtree);
    copy_subtree(&((*target)->right_subtree), src->right_subtree);
}

template<typename tkey, typename tvalue>
AVL_tree<tkey, tvalue>::iterator_data::iterator_data(
    unsigned int depth,
    tkey const &key,
    tvalue const &value,
    size_t subtree_height_):
    binary_search_tree<tkey, tvalue>::iterator_data(depth, key, value), subtree_height(subtree_height_) {}

template<typename tkey, typename tvalue>
AVL_tree<tkey, tvalue>::AVL_tree(std::function<int(tkey const &, tkey const &)> comparer,
    allocator *allocator,
    logger *logger,
    typename binary_search_tree<tkey, tvalue>::insertion_of_existent_key_attempt_strategy insertion_strategy,
    typename binary_search_tree<tkey, tvalue>::disposal_of_nonexistent_key_attempt_strategy disposal_strategy) : binary_search_tree<tkey, tvalue>(comparer, allocator, logger, insertion_strategy, disposal_strategy) {}

template<typename tkey, typename tvalue>
AVL_tree<tkey, tvalue>::AVL_tree(AVL_tree<tkey, tvalue> const &other) : binary_search_tree<tkey, tvalue>(other) {}

template<typename tkey, typename tvalue>
AVL_tree<tkey, tvalue> &AVL_tree<tkey, tvalue>::operator=(AVL_tree<tkey, tvalue> const &other)
{
    if (this != &other)
    {
        binary_search_tree<tkey, tvalue>::operator=(other);
    }
    return *this;
}

// region iterator requests definition

template<typename tkey, typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_iterator AVL_tree<tkey, tvalue>::begin_prefix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    if (binary_search_tree<tkey, tvalue>::_root != nullptr)
        stack.push(&(binary_search_tree<tkey, tvalue>::_root));

    return prefix_iterator(stack, new iterator_data);
}

template<typename tkey, typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_iterator AVL_tree<tkey, tvalue>::end_prefix() const noexcept
{
    return {};
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_iterator AVL_tree<tkey, tvalue>::cbegin_prefix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    if (binary_search_tree<tkey, tvalue>::_root != nullptr)
        stack.push(&(binary_search_tree<tkey, tvalue>::_root));

    return prefix_const_iterator(stack, new iterator_data);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_iterator AVL_tree<tkey, tvalue>::cend_prefix() const noexcept
{
    return {};
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_reverse_iterator AVL_tree<tkey, tvalue>::rbegin_prefix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    if (binary_search_tree<tkey, tvalue>::_root != nullptr)
        stack.push(&(binary_search_tree<tkey, tvalue>::_root));

    return prefix_reverse_iterator(stack, new iterator_data);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_reverse_iterator AVL_tree<tkey, tvalue>::rend_prefix() const noexcept
{
    return {};
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator AVL_tree<tkey, tvalue>::crbegin_prefix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    if (binary_search_tree<tkey, tvalue>::_root != nullptr)
        stack.push(&(binary_search_tree<tkey, tvalue>::_root));

    return prefix_const_reverse_iterator(stack, new iterator_data);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::prefix_const_reverse_iterator AVL_tree<tkey, tvalue>::crend_prefix() const noexcept
{
    return {};
}

template<typename tkey, typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_iterator AVL_tree<tkey, tvalue>::begin_infix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    typename binary_search_tree<tkey, tvalue>::node** current_node = &(binary_search_tree<tkey, tvalue>::_root);
    while(*current_node != nullptr)
    {
        stack.push(current_node);
        current_node = &((*current_node)->left_subtree);
    }
    return infix_iterator(stack, new iterator_data);
}

template<typename tkey, typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_iterator AVL_tree<tkey, tvalue>::end_infix() const noexcept
{
    return {};
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_iterator AVL_tree<tkey, tvalue>::cbegin_infix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    typename binary_search_tree<tkey, tvalue>::node** current_node = &(binary_search_tree<tkey, tvalue>::_root);
    while(*current_node != nullptr)
    {
        stack.push(current_node);
        current_node = &((*current_node)->left_subtree);
    }
    return infix_const_iterator(stack, new iterator_data);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_iterator AVL_tree<tkey, tvalue>::cend_infix() const noexcept
{
    return {};
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_reverse_iterator AVL_tree<tkey, tvalue>::rbegin_infix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    typename binary_search_tree<tkey, tvalue>::node** current_node = &(binary_search_tree<tkey, tvalue>::_root);
    while(*current_node != nullptr)
    {
        stack.push(current_node);
        current_node = &((*current_node)->right_subtree);
    }
    return infix_reverse_iterator(stack, new iterator_data);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_reverse_iterator AVL_tree<tkey, tvalue>::rend_infix() const noexcept
{
    return {};
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_reverse_iterator AVL_tree<tkey, tvalue>::crbegin_infix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    typename binary_search_tree<tkey, tvalue>::node** current_node = &(binary_search_tree<tkey, tvalue>::_root);
    while(*current_node != nullptr)
    {
        stack.push(current_node);
        current_node = &((*current_node)->right_subtree);
    }
    return infix_const_reverse_iterator(stack, new iterator_data);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::infix_const_reverse_iterator AVL_tree<tkey, tvalue>::crend_infix() const noexcept
{
    return {};
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_iterator AVL_tree<tkey, tvalue>::begin_postfix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    typename binary_search_tree<tkey, tvalue>::node** current_node = &(binary_search_tree<tkey, tvalue>::_root);
    while(*current_node != nullptr)
    {
        stack.push(current_node);
        current_node = (*current_node)->left_subtree != nullptr ? &((*current_node)->left_subtree) : &((*current_node)->right_subtree);
    }
    return postfix_iterator(stack, new iterator_data);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_iterator AVL_tree<tkey, tvalue>::end_postfix() const noexcept
{
    return {};
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_iterator AVL_tree<tkey, tvalue>::cbegin_postfix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    typename binary_search_tree<tkey, tvalue>::node** current_node = &(binary_search_tree<tkey, tvalue>::_root);
    while(*current_node != nullptr)
    {
        stack.push(current_node);
        current_node = (*current_node)->left_subtree != nullptr ? &((*current_node)->left_subtree) : &((*current_node)->right_subtree);
    }
    return postfix_const_iterator(stack, new iterator_data);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_iterator AVL_tree<tkey, tvalue>::cend_postfix() const noexcept
{
    return {};
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_reverse_iterator AVL_tree<tkey, tvalue>::rbegin_postfix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    typename binary_search_tree<tkey, tvalue>::node** current_node = &(binary_search_tree<tkey, tvalue>::_root);
    while(*current_node != nullptr)
    {
        stack.push(current_node);
        current_node = (*current_node)->right_subtree != nullptr ? &((*current_node)->right_subtree) : &((*current_node)->left_subtree);
    }
    return postfix_reverse_iterator(stack, new iterator_data);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_reverse_iterator AVL_tree<tkey, tvalue>::rend_postfix() const noexcept
{
    return {};
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator AVL_tree<tkey, tvalue>::crbegin_postfix() const noexcept
{
    std::stack<typename binary_search_tree<tkey, tvalue>::node**> stack;
    typename binary_search_tree<tkey, tvalue>::node** current_node = &(binary_search_tree<tkey, tvalue>::_root);
    while(*current_node != nullptr)
    {
        stack.push(current_node);
        current_node = (*current_node)->right_subtree != nullptr ? &((*current_node)->right_subtree) : &((*current_node)->left_subtree);
    }
    return postfix_const_reverse_iterator(stack, new iterator_data);
}

template<
    typename tkey,
    typename tvalue>
typename AVL_tree<tkey, tvalue>::postfix_const_reverse_iterator AVL_tree<tkey, tvalue>::crend_postfix() const noexcept
{
    return {};
}

// endregion iterator requests definition

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_AVL_TREE_H