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

        void recalculate_height() noexcept;

        /*
         * Returns positive if right subtree is bigger
         */
        short get_balance() const noexcept;

		node(tkey const &key_, tvalue &&value_);
		node(tkey const &key_, const tvalue& value_);

        ~node() noexcept override =default;
    };

public:
    
    struct iterator_data final:
        public binary_search_tree<tkey, tvalue>::iterator_data
    {
    
    public:
        
        size_t subtree_height;

		void update(const typename binary_search_tree<tkey, tvalue>::node* n, unsigned int _depth) override;

		binary_search_tree<tkey, tvalue>::iterator_data* clone() override;

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
binary_search_tree<tkey, tvalue>::iterator_data *AVL_tree<tkey, tvalue>::iterator_data::clone()
{
	return new iterator_data(*this);
}

template<typename tkey, typename tvalue>
void AVL_tree<tkey, tvalue>::iterator_data::update(const binary_search_tree<tkey, tvalue>::node *n, unsigned int _depth)
{
	binary_search_tree<tkey, tvalue>::iterator_data::key = n->key;
	binary_search_tree<tkey, tvalue>::iterator_data::value = n->value;
	binary_search_tree<tkey, tvalue>::iterator_data::depth = _depth;
	subtree_height = static_cast<node*>(n)->height;
}

template<typename tkey, typename tvalue>
AVL_tree<tkey, tvalue>::node::node(const tkey &key_, tvalue &&value_) : binary_search_tree<tkey, tvalue>::node(key_, std::move(value_)), height(1) {}

template<typename tkey, typename tvalue>
AVL_tree<tkey, tvalue>::node::node(const tkey &key_, const tvalue& value_) : binary_search_tree<tkey, tvalue>::node(key_, value_), height(1) {}

template<typename tkey, typename tvalue>
void AVL_tree<tkey, tvalue>::node::recalculate_height() noexcept
{
    size_t lheight = binary_search_tree<tkey, tvalue>::node::left_subtree == nullptr ? 0 : static_cast<node*>(binary_search_tree<tkey, tvalue>::node::left_subtree)->height;
    size_t rheight = binary_search_tree<tkey, tvalue>::node::right_subtree == nullptr ? 0 : static_cast<node*>(binary_search_tree<tkey, tvalue>::node::right_subtree)->height;
    height = std::max(lheight, rheight) + 1;
}

template<typename tkey, typename tvalue>
short AVL_tree<tkey, tvalue>::node::get_balance() const noexcept
{
    long long lheight = binary_search_tree<tkey, tvalue>::node::left_subtree == nullptr ? 0 : static_cast<node*>(binary_search_tree<tkey, tvalue>::node::left_subtree)->height;
    long long rheight = binary_search_tree<tkey, tvalue>::node::right_subtree == nullptr ? 0 : static_cast<node*>(binary_search_tree<tkey, tvalue>::node::right_subtree)->height;

    return rheight - lheight;
}

template<typename tkey, typename tvalue>
tvalue AVL_tree<tkey, tvalue>::dispose_inner(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &node_path)
{
    tvalue res = (*node_path.top())->value;

    typename binary_search_tree<tkey, tvalue>::node* current_node = *node_path.top();

    if (current_node->right_subtree == nullptr && current_node->left_subtree == nullptr)
    {
        *node_path.top() = nullptr;
        node_path.pop();
    } else if (current_node->right_subtree == nullptr || current_node->left_subtree == nullptr)
    {
        typename binary_search_tree<tkey, tvalue>::node* node_of_interest = current_node->right_subtree != nullptr ? current_node->right_subtree : current_node->left_subtree;

        *node_path.top() = node_of_interest;

        node_path.pop();
    } else
    {
        std::deque<typename binary_search_tree<tkey, tvalue>::node**> additional_path;
        typename binary_search_tree<tkey, tvalue>::node** node_of_interest = &current_node->left_subtree;

        while ((*node_of_interest)->right_subtree != nullptr)
        {
            node_of_interest = &((*node_of_interest)->right_subtree);
            additional_path.push_back(node_of_interest);
        }

		typename binary_search_tree<tkey, tvalue>::node* tmp = *node_of_interest;
        *node_of_interest = (*node_of_interest)->left_subtree;
        *node_path.top() = tmp;

        tmp->left_subtree = current_node->left_subtree == tmp ? tmp->left_subtree : current_node->left_subtree;
        tmp->right_subtree = current_node->right_subtree;

        if (current_node->left_subtree != tmp)
            node_path.push(&current_node->left_subtree);

        if (!additional_path.empty())
            additional_path.pop_back();

        while (!additional_path.empty())
        {
            node_path.push(additional_path.front());
            additional_path.pop_front();
        }
    }

    allocator::destruct(current_node);
    allocator_guardant::deallocate_with_guard(current_node);

    while (!node_path.empty())
    {
        static_cast<node*>(*node_path.top())->recalculate_height();
        short balance = static_cast<node*>(*node_path.top())->get_balance();

        if (balance < -1)
        {
            short inner_balance = static_cast<node*>((*node_path.top())->left_subtree)->get_balance();
            if (inner_balance <= 0)
            {
                binary_search_tree<tkey, tvalue>::small_right_rotation(*node_path.top());
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::right_subtree)->recalculate_height();
                static_cast<node*>(*node_path.top())->recalculate_height();
            } else
            {
                binary_search_tree<tkey, tvalue>::big_right_rotation(*node_path.top());
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::right_subtree)->recalculate_height();
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::left_subtree)->recalculate_height();
                static_cast<node*>(*node_path.top())->recalculate_height();
            }
        } else if (balance > 1)
        {
            short inner_balance = static_cast<node*>((*node_path.top())->right_subtree)->get_balance();
            if (inner_balance >= 0)
            {
                binary_search_tree<tkey, tvalue>::small_left_rotation(*node_path.top());
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::left_subtree)->recalculate_height();
                static_cast<node*>(*node_path.top())->recalculate_height();
            } else
            {
                binary_search_tree<tkey, tvalue>::big_left_rotation(*node_path.top());
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::right_subtree)->recalculate_height();
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::left_subtree)->recalculate_height();
                static_cast<node*>(*node_path.top())->recalculate_height();
            }
        }
    }

    return res;
}

template<typename tkey, typename tvalue>
template<typename tval_arg>
void AVL_tree<tkey, tvalue>::insert_inner_t(std::stack<typename binary_search_tree<tkey, tvalue>::node **> &node_path,
                                            const tkey &key, tval_arg &&val)
{
    *node_path.top() = static_cast<typename binary_search_tree<tkey, tvalue>::node*>(reinterpret_cast<node*>(allocator_guardant::allocate_with_guard(sizeof(node))));
    try
    {
        allocator::construct(static_cast<node*>(*node_path.top()), key, std::forward<tval_arg>(val));
    } catch(...)
    {
        allocator_guardant::deallocate_with_guard(static_cast<node*>(*node_path.top()));
        *node_path.top() = nullptr;
        throw;
    }

    static_cast<node*>(*node_path.top())->recalculate_height();

    node* current_node = static_cast<node*>(*node_path.top());

    node_path.pop();

    bool is_last_lift_left, is_prelast_lift_left;

    if (!node_path.empty())
        is_last_lift_left = is_prelast_lift_left = binary_search_tree<tkey, tvalue>::is_left_subtree(current_node, *node_path.top());

    while (!node_path.empty())
    {
        static_cast<node*>(*node_path.top())->recalculate_height();

        short balance = static_cast<node*>(*node_path.top())->get_balance();

        if (balance < -1 || balance > 1)
        {
            if (balance > 1 && is_last_lift_left == is_prelast_lift_left)
            {
                binary_search_tree<tkey, tvalue>::small_left_rotation(*node_path.top());
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::left_subtree)->recalculate_height();
                static_cast<node*>(*node_path.top())->recalculate_height();
            } else if (balance > 1)
            {
                binary_search_tree<tkey, tvalue>::big_left_rotation(*node_path.top());
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::right_subtree)->recalculate_height();
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::left_subtree)->recalculate_height();
                static_cast<node*>(*node_path.top())->recalculate_height();
            } else if (balance < 1 && is_last_lift_left == is_prelast_lift_left)
            {
                binary_search_tree<tkey, tvalue>::small_right_rotation(*node_path.top());
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::right_subtree)->recalculate_height();
                static_cast<node*>(*node_path.top())->recalculate_height();
            } else
            {
                binary_search_tree<tkey, tvalue>::big_right_rotation(*node_path.top());
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::right_subtree)->recalculate_height();
                static_cast<node*>((*node_path.top())->binary_search_tree<tkey, tvalue>::node::left_subtree)->recalculate_height();
                static_cast<node*>(*node_path.top())->recalculate_height();
            }
        }

        current_node = static_cast<node*>(*node_path.top());
        node_path.pop();

        if (!node_path.empty())
            is_prelast_lift_left = std::exchange(is_last_lift_left, binary_search_tree<tkey, tvalue>::is_left_subtree(current_node, *node_path.top()));
    }
}

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

    *target = static_cast<typename binary_search_tree<tkey, tvalue>::node*>(reinterpret_cast<node*>(allocator_guardant::allocate_with_guard(sizeof(node))));
    try
    {
        allocator::construct(static_cast<node*>(*target), *static_cast<node*>(src));
    } catch(...)
    {
        allocator_guardant::deallocate_with_guard(static_cast<node*>(*target));
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
    return prefix_iterator();
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
    return prefix_const_iterator();
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
    return prefix_reverse_iterator();
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
    return prefix_const_reverse_iterator();
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
    return infix_iterator();
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
    return infix_const_iterator();
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
    return infix_reverse_iterator();
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
    return infix_const_reverse_iterator();
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
    return postfix_iterator();
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
    return postfix_const_iterator();
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
    return postfix_reverse_iterator();
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
    return postfix_const_reverse_iterator();
}

// endregion iterator requests definition

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_AVL_TREE_H