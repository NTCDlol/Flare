#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

// Structure to track allocated memory blocks
struct MemoryBlock {
    int id;
    std::string description;
    size_t size;
    bool isVirtual;
    void* pointer;  // In a real implementation, this would point to the actual memory

    MemoryBlock(int id, const std::string& desc, size_t sz, bool isVirt, void* ptr)
        : id(id), description(desc), size(sz), isVirtual(isVirt), pointer(ptr) {}
};

class MemoryManager {
public:
    MemoryManager();
    ~MemoryManager();

    // Allocate a block of memory with the given ID
    bool allocateMemory(const std::string& description, size_t size, int id);

    // Allocate a block of virtual memory with the given ID
    bool allocateVirtualMemory(const std::string& description, size_t size, int id);

    // Free a block of memory with the given ID
    bool freeMemory(int id, int mode);

    // Get the size of a memory block
    size_t getMemorySize(int id) const;

    // Check if a memory block exists
    bool hasMemory(int id) const;

    // Get total available memory (simplified implementation)
    size_t getTotalMemory() const;

private:
    std::unordered_map<int, std::shared_ptr<MemoryBlock>> m_memoryBlocks;
    size_t m_totalMemory;  // Simplified representation of total system memory
    
    // Internal method to allocate memory of specified type
    bool allocateMemoryInternal(const std::string& description, size_t size, int id, bool isVirtual);
};

#endif // MEMORY_MANAGER_H
