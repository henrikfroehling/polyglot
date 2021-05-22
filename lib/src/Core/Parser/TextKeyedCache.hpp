#ifndef POLYGLOT_CORE_PARSER_TEXTKEYEDCACHE_H
#define POLYGLOT_CORE_PARSER_TEXTKEYEDCACHE_H

#include <random>
#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Parser/TokenInfo.hpp"

namespace polyglot::Core::Parser
{

struct CacheEntry final
{
    CacheEntry() noexcept
        : hashCode{0},
          item{},
          text{}
    {}

    explicit CacheEntry(unsigned long hashCode,
                        TokenInfo item,
                        pg_string_view text) noexcept
        : hashCode{hashCode},
          item{std::move(item)},
          text{text}
    {}

    CacheEntry(const CacheEntry&) noexcept = default;
    CacheEntry(CacheEntry&&) noexcept = default;
    CacheEntry& operator=(const CacheEntry&) noexcept = default;
    CacheEntry& operator=(CacheEntry&&) noexcept = default;

    unsigned long hashCode;
    TokenInfo item;
    pg_string_view text;
};

class TextKeyedCache final
{
private:
    static constexpr unsigned long LOCAL_SIZE_BITS = 11;
    static constexpr unsigned long LOCAL_SIZE = (1 << LOCAL_SIZE_BITS);
    static constexpr unsigned long LOCAL_SIZE_MASK = LOCAL_SIZE - 1;

    static constexpr unsigned long SHARED_SIZE_BITS = 16;
    static constexpr unsigned long SHARED_SIZE = (1 << SHARED_SIZE_BITS);
    static constexpr unsigned long SHARED_SIZE_MASK = SHARED_SIZE - 1;

    static constexpr unsigned long SHARED_BUCKET_BITS = 4;
    static constexpr unsigned long SHARED_BUCKET_SIZE = (1 << SHARED_BUCKET_BITS);
    static constexpr unsigned long SHARED_BUCKET_SIZE_MASK = SHARED_BUCKET_SIZE - 1;

private:
    std::vector<SharedPtr<CacheEntry>> _localTable;
    std::vector<SharedPtr<CacheEntry>> _sharedTable;

public:
    TextKeyedCache() noexcept
        : _localTable(LOCAL_SIZE),
          _sharedTable(SHARED_SIZE)
    {}

    TokenInfo lookupItem(pg_string_view chars,
                         unsigned long hashCode) noexcept;

    void addItem(pg_string_view chars,
                 unsigned long hashCode,
                 TokenInfo item) noexcept;

private:
    inline constexpr unsigned long localIndexFromHash(unsigned long hash) const noexcept { return hash & LOCAL_SIZE_MASK; }
    inline constexpr unsigned long sharedIndexFromHash(unsigned long hash) const noexcept { return (hash ^ (hash >> LOCAL_SIZE_MASK)) & SHARED_SIZE_MASK; }

    inline unsigned long nextRandom() const noexcept
    {
        std::random_device device{};
        std::mt19937 generator{device()};
        return generator();
    }

    SharedPtr<CacheEntry> lookupSharedEntry(pg_string_view chars,
                                            unsigned long hashCode) noexcept;

    void addSharedItem(unsigned long hashCode,
                       const SharedPtr<CacheEntry>& cacheEntry) noexcept;
};

} // end namespace polyglot::Core::Parser

#endif // POLYGLOT_CORE_PARSER_TEXTKEYEDCACHE_H
