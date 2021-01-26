#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_TEXTKEYEDCACHE_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_TEXTKEYEDCACHE_H

#include <random>
#include <string_view>
#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "CodeAnalysis/Core/Parser/TokenInfo.hpp"

namespace polyglot::CodeAnalysis
{

struct CacheEntry final
{
    CacheEntry() noexcept
        : hashCode{-1},
          item{},
          text{}
    {}

    explicit CacheEntry(int hashCode,
                        TokenInfo item,
                        std::string_view text) noexcept
        : hashCode{hashCode},
          item{std::move(item)},
          text{text}
    {}

    CacheEntry(const CacheEntry&) noexcept = default;
    CacheEntry(CacheEntry&&) noexcept = default;
    CacheEntry& operator=(const CacheEntry&) noexcept = default;
    CacheEntry& operator=(CacheEntry&&) noexcept = default;

    int hashCode;
    TokenInfo item;
    std::string_view text;
};

class TextKeyedCache final
{
private:
    static constexpr long LOCAL_SIZE_BITS = 11;
    static constexpr long LOCAL_SIZE = (1 << LOCAL_SIZE_BITS);
    static constexpr long LOCAL_SIZE_MASK = LOCAL_SIZE - 1;

    static constexpr long SHARED_SIZE_BITS = 16;
    static constexpr long SHARED_SIZE = (1 << SHARED_SIZE_BITS);
    static constexpr long SHARED_SIZE_MASK = SHARED_SIZE - 1;

    static constexpr long SHARED_BUCKET_BITS = 4;
    static constexpr long SHARED_BUCKET_SIZE = (1 << SHARED_BUCKET_BITS);
    static constexpr long SHARED_BUCKET_SIZE_MASK = SHARED_BUCKET_SIZE - 1;

private:
    std::vector<SharedPtr<CacheEntry>> _localTable;
    std::vector<SharedPtr<CacheEntry>> _sharedTable;

public:
    TextKeyedCache() noexcept
        : _localTable(LOCAL_SIZE),
          _sharedTable(SHARED_SIZE)
    {}

    TokenInfo lookupItem(std::string_view chars,
                         long hashCode) noexcept;

    void addItem(std::string_view chars,
                 long hashCode,
                 TokenInfo item) noexcept;

private:
    inline constexpr long localIndexFromHash(long hash) const noexcept { return hash & LOCAL_SIZE_MASK; }
    inline constexpr long sharedIndexFromHash(long hash) const noexcept { return (hash ^ (hash >> LOCAL_SIZE_MASK)) & SHARED_SIZE_MASK; }

    inline int nextRandom() const noexcept
    {
        std::random_device device{};
        std::mt19937 generator{device()};
        return generator();
    }

    SharedPtr<CacheEntry> lookupSharedEntry(std::string_view chars,
                                            long hashCode) noexcept;

    void addSharedItem(long hashCode,
                       const SharedPtr<CacheEntry>& cacheEntry) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_TEXTKEYEDCACHE_H
