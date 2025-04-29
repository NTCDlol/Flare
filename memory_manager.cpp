#include "memory_manager.h"
#include <iostream>

MemoryManager::MemoryManager() : m_totalMemory(0) {
    // In a real system, we would determine the actual available system memory
    // This is a simplified implementation
    m_totalMemory = 8 * 1024 * 1024 * 1024; // 8 GB
}

MemoryManager::~MemoryManager() {
    // Free all allocated memory blocks
    for (auto& pair : m_memoryBlocks) {
        // In a real implementation, we would free the actual memory here
        // For now, we just print out that we're freeing memory
        std::cout << "Freeing memory block " << pair.first 
                  << " (" << pair.second->description << ")" << std::endl;
    }
    m_memoryBlocks.clear();
}

bool MemoryManager::allocateMemory(const std::string& description, size_t size, int id) {
    return allocateMemoryInternal(description, size, id, false);
}

bool MemoryManager::allocateVirtualMemory(const std::string& description, size_t size, int id) {
    return allocateMemoryInternal(description, size, id, true);
}

bool MemoryManager::allocateMemoryInternal(const std::string& description, size_t size, int id, bool isVirtual) {
    // Check if ID is already in use
    if (m_memoryBlocks.find(id) != m_memoryBlocks.end()) {
        std::cerr << "Memory ID " << id << " is already in use" << std::endl;
        return false;
    }

    // If size is "auto" (0), allocate a small default size
    if (size == 0) {
        size = 1024; // 1 KB default
    }

    // In a real implementation, we would allocate actual memory here
    // For now, we just track the allocation
    void* pointer = nullptr;
    // In a real implementation: pointer = malloc(size);

    // Create and store the memory block
    auto block = std::make_shared<MemoryBlock>(id, description, size, isVirtual, pointer);
    m_memoryBlocks[id] = block;

    std::cout << (isVirtual ? "Virtual" : "Regular") << " memory allocated: " 
              << "ID=" << id << ", Description=" << description 
              << ", Size=" << size << " bytes" << std::endl;
    
    return true;
}

bool MemoryManager::freeMemory(int id, int mode) {
    auto it = m_memoryBlocks.find(id);
    if (it == m_memoryBlocks.end()) {
        std::cerr << "Memory ID " << id << " not found" << std::endl;
        return false;
    }

    // In a real implementation, we would free the actual memory here
    // For now, we just remove the block from our tracking
    std::cout << "Freeing " << (it->second->isVirtual ? "virtual" : "regular") 
              << " memory: ID=" << id << ", Description=" << it->second->description 
              << ", Mode=" << mode << std::endl;

    m_memoryBlocks.erase(it);
    return true;
}

size_t MemoryManager::getMemorySize(int id) const {
    auto it = m_memoryBlocks.find(id);
    if (it == m_memoryBlocks.end()) {
        return 0;
    }
    return it->second->size;
}

bool MemoryManager::hasMemory(int id) const {
    return m_memoryBlocks.find(id) != m_memoryBlocks.end();
}

size_t MemoryManager::getTotalMemory() const {
    return m_totalMemory;
}
