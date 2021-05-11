#ifndef POLYGLOT_CORE_HASHING_H
#define POLYGLOT_CORE_HASHING_H

namespace polyglot
{

class Hashing
{
public:
    static constexpr unsigned long FNV_OFFSET_BIAS = 2166136261;
    static constexpr unsigned long FNV_PRIME = 16777619;

    inline static constexpr unsigned long combineFNVHash(unsigned long hashCode, char character) noexcept
    {
        return (hashCode ^ character) * Hashing::FNV_PRIME;
    }
};

} // end namespace polyglot

#endif // POLYGLOT_CORE_HASHING_H
