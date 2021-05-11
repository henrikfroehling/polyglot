#include "Core/Parser/TextKeyedCache.hpp"

namespace polyglot::Core::Parser
{

TokenInfo TextKeyedCache::lookupItem(std::string_view chars,
                                     unsigned long hashCode) noexcept
{
    const unsigned long localIndex = localIndexFromHash(hashCode);
    SharedPtr<CacheEntry>& ptrLocalEntry = _localTable[localIndex];

    if (ptrLocalEntry != nullptr && ptrLocalEntry->hashCode == hashCode && ptrLocalEntry->text == chars)
        return ptrLocalEntry->item;

    SharedPtr<CacheEntry> ptrSharedEntry = lookupSharedEntry(chars, hashCode);

    if (ptrSharedEntry != nullptr)
    {
        if (ptrLocalEntry == nullptr)
        {
            ptrLocalEntry = std::make_shared<CacheEntry>();
            _localTable[localIndex] = ptrLocalEntry;
        }

        ptrLocalEntry->hashCode = hashCode;
        ptrLocalEntry->item = ptrSharedEntry->item;
        ptrLocalEntry->text = ptrSharedEntry->text;
        return ptrSharedEntry->item;
    }

    return TokenInfo{};
}

void TextKeyedCache::addItem(std::string_view chars,
                             unsigned long hashCode,
                             TokenInfo item) noexcept
{
    auto ptrCacheEntry = std::make_shared<CacheEntry>(hashCode, std::move(item), chars);
    addSharedItem(hashCode, ptrCacheEntry);

    const unsigned long localIndex = localIndexFromHash(hashCode);
    _localTable[localIndex] = ptrCacheEntry;
}

SharedPtr<CacheEntry> TextKeyedCache::lookupSharedEntry(std::string_view chars,
                                                        unsigned long hashCode) noexcept
{
    unsigned long sharedIndex = sharedIndexFromHash(hashCode);
    SharedPtr<CacheEntry> ptrSharedEntry = nullptr;

    for (unsigned long i = 0; i < SHARED_BUCKET_SIZE + 1; i++)
    {
        ptrSharedEntry = _sharedTable[sharedIndex];

        if (ptrSharedEntry != nullptr && ptrSharedEntry->hashCode == hashCode && ptrSharedEntry->text == chars)
            return ptrSharedEntry;
        else
            break;

        sharedIndex = (sharedIndex + i) & SHARED_SIZE_MASK;
    }

    return nullptr;
}

void TextKeyedCache::addSharedItem(unsigned long hashCode,
                                   const SharedPtr<CacheEntry>& cacheEntry) noexcept
{
    unsigned long sharedIndex = sharedIndexFromHash(hashCode);
    unsigned long currentIndex = sharedIndex;

    for (unsigned long i = 1; i < SHARED_BUCKET_SIZE + 1; i++)
    {
        if (_sharedTable[sharedIndex] == nullptr)
        {
            sharedIndex = currentIndex;
            goto foundIndex;
        }

        currentIndex = (currentIndex + i) & SHARED_SIZE_MASK;
    }

    {
        unsigned long randomIndex = nextRandom() & SHARED_BUCKET_SIZE_MASK;
        sharedIndex = (sharedIndex + ((randomIndex * randomIndex + randomIndex) / 2)) & SHARED_SIZE_MASK;
    }

foundIndex:
    _sharedTable[sharedIndex] = cacheEntry;
}

} // end namespace polyglot::Core::Parser
