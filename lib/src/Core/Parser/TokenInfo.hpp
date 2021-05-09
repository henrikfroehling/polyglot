#ifndef POLYGLOT_CORE_PARSER_TOKENINFO_H
#define POLYGLOT_CORE_PARSER_TOKENINFO_H

#include <string_view>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Core::Parser
{

struct TokenInfo final
{
    TokenInfo() noexcept = default;

    TokenInfo(const TokenInfo&) noexcept = default;
    TokenInfo(TokenInfo&&) noexcept = default;
    TokenInfo& operator=(const TokenInfo&) noexcept = default;
    TokenInfo& operator=(TokenInfo&&) noexcept = default;

    friend bool operator==(const TokenInfo& lhs,
                           const TokenInfo& rhs) noexcept;

    friend bool operator!=(const TokenInfo& lhs,
                           const TokenInfo& rhs) noexcept;

    Syntax::SyntaxKind kind = Syntax::SyntaxKind::None;
    std::string_view text{};
};

} // end namespace polyglot::Core::Parser

#endif // POLYGLOT_CORE_PARSER_TOKENINFO_H
