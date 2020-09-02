#include "polyglot/CodeAnalysis/Core/TextKeyedCache.hpp"

namespace polyglot::CodeAnalysis
{

TokenInfo TextKeyedCache::lookupItem(std::string_view chars,
                                     int hashCode) noexcept
{
    const int localIndex = localIndexFromHash(hashCode);
    auto& ptrLocalEntry = _localTable[localIndex];

    if (ptrLocalEntry != nullptr && ptrLocalEntry->hashCode == hashCode && ptrLocalEntry->text == chars)
        return ptrLocalEntry->item;

    auto ptrSharedEntry = lookupSharedEntry(chars, hashCode);

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
                             int hashCode,
                             TokenInfo item) noexcept
{
    auto ptrCacheEntry = std::make_shared<CacheEntry>(hashCode, std::move(item), chars);
    addSharedItem(hashCode, ptrCacheEntry);

    const int localIndex = localIndexFromHash(hashCode);
    _localTable[localIndex] = ptrCacheEntry;
}

std::shared_ptr<CacheEntry> TextKeyedCache::lookupSharedEntry(std::string_view chars,
                                                              int hashCode) noexcept
{
    int sharedIndex = sharedIndexFromHash(hashCode);
    std::shared_ptr<CacheEntry> ptrSharedEntry = nullptr;

    for (int i = 0; i < SHARED_BUCKET_SIZE + 1; i++)
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

void TextKeyedCache::addSharedItem(int hashCode,
                                   const std::shared_ptr<CacheEntry>& cacheEntry) noexcept
{
    int sharedIndex = sharedIndexFromHash(hashCode);
    int currentIndex = sharedIndex;

    for (int i = 1; i < SHARED_BUCKET_SIZE + 1; i++)
    {
        if (_sharedTable[sharedIndex] == nullptr)
        {
            sharedIndex = currentIndex;
            goto foundIndex;
        }

        currentIndex = (currentIndex + i) & SHARED_SIZE_MASK;
    }

    {
        int randomIndex = nextRandom() & SHARED_BUCKET_SIZE_MASK;
        sharedIndex = (sharedIndex + ((randomIndex * randomIndex + randomIndex) / 2)) & SHARED_SIZE_MASK;
    }

foundIndex:
    _sharedTable[sharedIndex] = cacheEntry;
}

} // end namespace polyglot::CodeAnalysis
