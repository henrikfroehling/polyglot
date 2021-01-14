#ifndef POLYGLOT_CODEANALYSIS_CORE_TOKENINFO_H
#define POLYGLOT_CODEANALYSIS_CORE_TOKENINFO_H

#include <string_view>
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
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

    SyntaxKind kind;
    std::string_view text;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_TOKENINFO_H
