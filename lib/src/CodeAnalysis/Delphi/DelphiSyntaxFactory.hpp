#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHISYNTAXFACTORY_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHISYNTAXFACTORY_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;
class SyntaxTrivia;
class TokenInfo;

class DelphiSyntaxFactory final
{
public:
    static SyntaxToken* createToken(TokenInfo& tokenInfo,
                                    pg_size position) noexcept;

    static SyntaxToken* createTokenWithTrivia(TokenInfo& tokenInfo,
                                              pg_size position,
                                              std::vector<SyntaxTrivia*>&& leadingTrivia,
                                              std::vector<SyntaxTrivia*>&& trailingTrivia) noexcept;

    static SyntaxToken* createTokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                                     pg_size position,
                                                     std::vector<SyntaxTrivia*>&& leadingTrivia) noexcept;

    static SyntaxToken* createTokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                      pg_size position,
                                                      std::vector<SyntaxTrivia*>&& trailingTrivia) noexcept;

    static SyntaxTrivia* createTrivia(SyntaxKind syntaxKind,
                                      std::string_view text,
                                      pg_size position) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHISYNTAXFACTORY_H
