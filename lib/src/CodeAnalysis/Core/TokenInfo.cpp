#include "polyglot/CodeAnalysis/Core/TokenInfo.hpp"

namespace polyglot::CodeAnalysis
{

bool operator==(const TokenInfo& lhs,
                const TokenInfo& rhs) noexcept
{
    return lhs.kind == rhs.kind && lhs.contextualKind == rhs.contextualKind && lhs.text == rhs.text;
}

bool operator!=(const TokenInfo& lhs,
                const TokenInfo& rhs) noexcept
{
    return !(lhs == rhs);
}

} // end namespace polyglot::CodeAnalysis
