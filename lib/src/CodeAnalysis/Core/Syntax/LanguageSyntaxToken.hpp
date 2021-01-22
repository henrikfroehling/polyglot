#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXTOKEN_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken : public LanguageSyntaxNode
{
public:
    LanguageSyntaxToken() noexcept;

    explicit LanguageSyntaxToken(SyntaxKind syntaxKind,
                                 std::string_view text,
                                 pg_size position = 0,
                                 pg_size fullWidth = 0) noexcept;

    virtual ~LanguageSyntaxToken() noexcept;

    LanguageSyntaxToken(const LanguageSyntaxToken&) noexcept = default;
    LanguageSyntaxToken(LanguageSyntaxToken&&) noexcept = default;
    LanguageSyntaxToken& operator=(const LanguageSyntaxToken&) noexcept = default;
    LanguageSyntaxToken& operator=(LanguageSyntaxToken&&) noexcept = default;

    std::string_view text() const noexcept { return _text; }
    virtual LanguageSyntaxNode* child(pg_size index) const noexcept override;
    inline bool isToken() const noexcept override final { return true; }

    pg_size leadingTriviaWidth() const noexcept override;
    pg_size trailingTriviaWidth() const noexcept override;

protected:
    std::string_view _text;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXTOKEN_H
