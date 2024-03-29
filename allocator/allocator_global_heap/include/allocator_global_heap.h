#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H

#include <allocator.h>
#include <logger.h>
#include <logger_guardant.h>
#include <typename_holder.h>

class allocator_global_heap final:
    public allocator,
    private logger_guardant,
    private typename_holder
{

private:
    
    logger *_logger;

    static constexpr const size_t size_t_size = sizeof(size_t);

public:
    
    explicit allocator_global_heap(
        logger *logger = nullptr);
    
    ~allocator_global_heap() override =default;
    
    allocator_global_heap(
        allocator_global_heap const &other) = delete;
    
    allocator_global_heap &operator=(
        allocator_global_heap const &other) = delete;
    
    allocator_global_heap(
        allocator_global_heap &&other) noexcept =default;
    
    allocator_global_heap &operator=(
        allocator_global_heap &&other) noexcept =default;

public:
    
    [[nodiscard]] void *allocate(
        size_t value_size,
        size_t values_count) override;
    
    void deallocate(
        void *at) override;

private:
    
    inline logger *get_logger() const override;

    std::string get_dump(char* data, size_t size);

    static std::string dump_byte(char byte);

    static char int_to_char(int val);

private:
    
    inline std::string get_typename() const noexcept override;

public:

};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_ALLOCATOR_ALLOCATOR_GLOBAL_HEAP_H