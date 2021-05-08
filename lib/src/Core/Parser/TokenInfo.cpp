#include "TokenInfo.hpp"

namespace polyglot::Core::Parser
{

bool operator==(const TokenInfo& lhs,
                const TokenInfo& rhs) noexcept
{
    return lhs.kind == rhs.kind && lhs.text == rhs.text;
}

bool operator!=(const TokenInfo& lhs,
                const TokenInfo& rhs) noexcept
{
    return !(lhs == rhs);
}

} // end namespace polyglot::Core::Parser
