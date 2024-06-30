#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_SCAPEGOAT_TREE_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_SCAPEGOAT_TREE_H

#include <binary_search_tree.h>
#include <iterator>

namespace __detail
{
    class SPG_TAG;

    template<typename tkey, typename tvalue, typename compare>
    class bst_impl<tkey, tvalue, compare, SPG_TAG>
    {
        template<class ...Args>
        static binary_search_tree<tkey, tvalue, compare, SPG_TAG>::node* create_node(binary_search_tree<tkey, tvalue, compare, SPG_TAG>& cont, Args&& ...args);

        //Does not invalidate node*, needed for splay tree
        static void post_search(binary_search_tree<tkey, tvalue, compare, SPG_TAG>::node**){}

        //Does not invalidate node*
        static void post_insert(binary_search_tree<tkey, tvalue, compare, SPG_TAG>& cont, binary_search_tree<tkey, tvalue, compare, SPG_TAG>::node**);

        static void erase(binary_search_tree<tkey, tvalue, compare, SPG_TAG>& cont, binary_search_tree<tkey, tvalue, compare, SPG_TAG>::node**);
    };
}

template<typename tkey, typename tvalue, compator<tkey> compare = std::less<tkey>>
class scapegoat_tree final:
    public binary_search_tree<tkey, tvalue, compare, __detail::SPG_TAG>
{

private:

    using parent = binary_search_tree<tkey, tvalue, compare, __detail::SPG_TAG>;
    
    struct node final:
        parent::node
    {
        size_t size;

        node(tkey const &key_, tvalue &&value_);
        node(tkey const &key_, const tvalue& value_);

        template<class ...Args>
        node(parent::node* par, Args&&... args);

        void recalculate_size() noexcept;
        bool is_disbalanced(double alpha) noexcept;
        
    };

public:

    using value_type = parent::value_type;

    explicit scapegoat_tree(
            const compare& comp = compare(),
            pp_allocator<value_type> alloc = pp_allocator<value_type>(),
            logger *logger = nullptr, double alpha = 0.7);

    template<input_iterator_for_pair<tkey, tvalue> iterator>
    explicit scapegoat_tree(iterator begin, iterator end, const compare& cmp = compare(),
            pp_allocator<value_type> alloc = pp_allocator<value_type>(),
            logger* logger = nullptr, double alpha = 0.7);

    template<std::ranges::input_range Range>
    explicit scapegoat_tree(Range&& range, const compare& cmp = compare(),
            pp_allocator<value_type> alloc = pp_allocator<value_type>(),
            logger* logger = nullptr, double alpha = 0.7);


    scapegoat_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp = compare(),
            pp_allocator<value_type> alloc = pp_allocator<value_type>(),
            logger* logger = nullptr, double alpha = 0.7);

public:
    
    ~scapegoat_tree() noexcept final;
    
    scapegoat_tree(scapegoat_tree const &other);
    
    scapegoat_tree &operator=(scapegoat_tree const &other);
    
    scapegoat_tree(scapegoat_tree &&other) noexcept;
    
    scapegoat_tree &operator=(scapegoat_tree &&other) noexcept;

public:
    
    void setup_alpha(double alpha);

private:

    double _alpha;
};

template<typename compare, typename U, typename iterator>
explicit scapegoat_tree(iterator begin, iterator end, const compare& cmp = compare(),
        pp_allocator<U> alloc = pp_allocator<U>(),
        logger* logger = nullptr, double alpha = 0.7) -> scapegoat_tree<const typename std::iterator_traits<iterator>::value_type::first_type, typename std::iterator_traits<iterator>::value_type::second_type, compare>;

template<typename compare, typename U, std::ranges::forward_range Range>
explicit scapegoat_tree(Range&& range, const compare& cmp = compare(),
        pp_allocator<U> alloc = pp_allocator<U>(),
        logger* logger = nullptr, double alpha = 0.7) -> scapegoat_tree<const typename std::iterator_traits<typename std::ranges::iterator_t<Range>>::value_type::first_type, typename std::iterator_traits<typename std::ranges::iterator_t<Range>>::value_type::second_type, compare> ;

template<typename tkey, typename tvalue, typename compare, typename U>
scapegoat_tree(std::initializer_list<std::pair<tkey, tvalue>> data, const compare& cmp = compare(),
        pp_allocator<U> alloc = pp_allocator<U>(),
        logger* logger = nullptr, double alpha = 0.7) -> scapegoat_tree<tkey, tvalue, compare>;

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_SCAPEGOAT_TREE_H