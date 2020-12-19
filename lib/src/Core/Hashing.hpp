#ifndef POLYGLOT_CORE_HASHING_H
#define POLYGLOT_CORE_HASHING_H

namespace polyglot
{

class Hashing
{
public:
    static constexpr long FNV_OFFSET_BIAS = 2166136261;
    static constexpr long FNV_PRIME = 16777619;

    inline static constexpr long combineFNVHash(long hashCode, char character) noexcept
    {
        return (hashCode ^ character) * Hashing::FNV_PRIME;
    }
};

} // end namespace polyglot

#endif // POLYGLOT_CORE_HASHING_H
