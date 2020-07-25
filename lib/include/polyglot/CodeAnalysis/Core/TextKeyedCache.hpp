#ifndef POLYGLOT_CODEANALYSIS_CORE_TEXTKEYEDCACHE_H
#define POLYGLOT_CODEANALYSIS_CORE_TEXTKEYEDCACHE_H

#include <memory>
#include <random>
#include <string_view>
#include "polyglot/polyglot_global.hpp"

namespace polyglot::CodeAnalysis
{

template <typename T>
class POLYGLOT_API TextKeyedCache
{
public:
    TextKeyedCache() noexcept = default;

private:
    static const int LOCAL_SIZE_BITS = 11;
    static const int LOCAL_SIZE = (1 << LOCAL_SIZE_BITS);
    static const int LOCAL_SIZE_MASK = LOCAL_SIZE - 1;

    static const int SHARED_SIZE_BITS = 16;
    static const int SHARED_SIZE = (1 << SHARED_SIZE_BITS);
    static const int SHARED_SIZE_MASK = SHARED_SIZE - 1;

    static const int SHARED_BUCKET_BITS = 4;
    static const int SHARED_BUCKET_SIZE = (1 << SHARED_BUCKET_BITS);
    static const int SHARED_BUCKET_SIZE_MASK = SHARED_BUCKET_SIZE - 1;

private:
    constexpr int localIndexFromHash(int hash) const noexcept { return hash & LOCAL_SIZE_MASK; }
    constexpr int sharedIndexFromHash(int hash) const noexcept { return (hash ^ (hash >> LOCAL_SIZE_BITS)) & SHARED_SIZE_MASK; }

private:
    template <typename T>
    struct LocalCacheEntry
    {
        LocalCacheEntry<T>() noexcept
            : hashCode{-1},
              item{nullptr},
              text{}
        {}

        LocalCacheEntry<T>(const LocalCacheEntry<T>&) noexcept = default;
        LocalCacheEntry<T>(LocalCacheEntry<T>&&) noexcept = default;
        LocalCacheEntry<T>& operator=(const LocalCacheEntry<T>&) noexcept = default;
        LocalCacheEntry<T>& operator=(LocalCacheEntry&&) noexcept = default;

        int hashCode;
        std::shared_ptr<T> item;
        std::string_view text;
    };

    template <typename T>
    struct SharedEntryValue
    {
        SharedEntryValue<T>() noexcept
            : item{nullptr},
              text{}
        {}

        SharedEntryValue<T>(const SharedEntryValue<T>&) noexcept = default;
        SharedEntryValue<T>(SharedEntryValue<T>&&) noexcept = default;
        SharedEntryValue<T>& operator=(const SharedEntryValue<T>&) noexcept = default;
        SharedEntryValue<T>& operator=(SharedEntryValue<T>&&) noexcept = default;

        std::shared_ptr<T> item;
        std::string_view text;
    };

    template <typename T>
    struct SharedCacheEntry
    {
        SharedCacheEntry<T>() noexcept
            : hashCode{-1},
              entry{nullptr}
        {}

        SharedCacheEntry<T>(const SharedCacheEntry<T>&) noexcept = default;
        SharedCacheEntry<T>(SharedCacheEntry<T>&&) noexcept = default;
        SharedCacheEntry<T>& operator=(const SharedCacheEntry<T>&) noexcept = default;
        SharedCacheEntry<T>& operator=(SharedCacheEntry<T>&&) noexcept = default;

        int hashCode;
        std::shared_ptr<SharedEntryValue<T>> entry;
    };

private:
    std::shared_ptr<LocalCacheEntry<T>> _localTable[LOCAL_SIZE];
    std::shared_ptr<SharedCacheEntry<T>> _sharedTable[SHARED_SIZE];

private:
    std::shared_ptr<SharedEntryValue<T>> lookupSharedEntry(std::string_view chars, int hashCode) noexcept
    {
        int sharedIndex = sharedIndexFromHash(hashCode);
        std::shared_ptr<SharedEntryValue<T>> sharedEntryValue;

        for (int i = 0; i < SHARED_BUCKET_SIZE + 1; i++)
        {
            auto sharedEntry = _sharedTable[sharedIndex];

            if (sharedEntry != nullptr && sharedEntry->entry != nullptr)
            {
                if (sharedEntry->hashCode == hashCode && sharedEntry->entry->text == chars)
                {
                    sharedEntryValue = sharedEntry->entry;
                    break;
                }

                sharedEntryValue = nullptr;
            }
            else
                break;

            sharedIndex = (sharedIndex + i) & SHARED_SIZE_MASK;
        }

        return sharedEntryValue;
    }

    int nextRandom() noexcept
    {
        std::random_device rd{};
        std::mt19937 generator{rd()};
        return generator();
    }

    void addSharedItem(int hashCode, std::shared_ptr<SharedEntryValue<T>> cacheEntry)
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

        int randomIndex = nextRandom() & SHARED_BUCKET_SIZE_MASK;
        sharedIndex = (sharedIndex + ((randomIndex * randomIndex + randomIndex) / 2)) & SHARED_SIZE_MASK;

foundIndex:
        _sharedTable[sharedIndex] = std::make_shared<SharedCacheEntry<T>>();
        _sharedTable[sharedIndex]->hashCode = hashCode;
        _sharedTable[sharedIndex]->entry = cacheEntry;
    }

public:
    std::shared_ptr<T> lookupItem(std::string_view chars, int hashCode) noexcept
    {
        std::shared_ptr<LocalCacheEntry<T>> localSlot = _localTable[localIndexFromHash(hashCode)];

        if (localSlot != nullptr && localSlot->hashCode == hashCode && localSlot->text == chars)
            return localSlot->item;

        std::shared_ptr<SharedEntryValue<T>> sharedEntryValue = lookupSharedEntry(chars, hashCode);

        if (sharedEntryValue != nullptr)
        {
            if (localSlot == nullptr)
                localSlot = std::make_shared<LocalCacheEntry<T>>();

            localSlot->hashCode = hashCode;
            localSlot->text = sharedEntryValue->text;
            std::shared_ptr<T> item = sharedEntryValue->item;
            localSlot->item = item;
            return item;
        }

        return nullptr;
    }

    void addItem(std::string_view chars, int hashCode, std::shared_ptr<T> item)
    {
        auto sharedEntryValue = std::make_shared<SharedEntryValue<T>>();
        sharedEntryValue->text = chars;
        sharedEntryValue->item = item;
        addSharedItem(hashCode, sharedEntryValue);

        std::shared_ptr<LocalCacheEntry<T>> localSlot = _localTable[localIndexFromHash(hashCode)];
        localSlot = std::make_shared<LocalCacheEntry<T>>();
        localSlot->hashCode = hashCode;
        localSlot->text = chars;
        localSlot->item = item;
    }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_TEXTKEYEDCACHE_H
