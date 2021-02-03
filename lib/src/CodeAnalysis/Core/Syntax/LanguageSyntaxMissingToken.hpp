#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXMISSINGTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXMISSINGTOKEN_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "LanguageSyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxList;

class LanguageSyntaxMissingToken : public LanguageSyntaxToken
{
public:
    LanguageSyntaxMissingToken() noexcept;

    explicit LanguageSyntaxMissingToken(SyntaxKind syntaxKind,
                                        std::string_view text,
                                        pg_size position = 0,
                                        pg_size fullWidth = 0,
                                        LanguageSyntaxList* leadingTrivia = nullptr,
                                        LanguageSyntaxList* trailingTrivia = nullptr) noexcept;

    virtual ~LanguageSyntaxMissingToken() noexcept;

    LanguageSyntaxMissingToken(const LanguageSyntaxMissingToken&) noexcept = default;
    LanguageSyntaxMissingToken(LanguageSyntaxMissingToken&&) noexcept = default;
    LanguageSyntaxMissingToken& operator=(const LanguageSyntaxMissingToken&) noexcept = default;
    LanguageSyntaxMissingToken& operator=(LanguageSyntaxMissingToken&&) noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXMISSINGTOKEN_H
