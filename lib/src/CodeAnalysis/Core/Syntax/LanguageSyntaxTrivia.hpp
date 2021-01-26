#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXTRIVIA_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXTRIVIA_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include "LanguageSyntaxNode.hpp"
#include "../Parser/DirectiveStack.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxTrivia : public LanguageSyntaxNode
{
public:
    LanguageSyntaxTrivia() noexcept;

    explicit LanguageSyntaxTrivia(SyntaxKind syntaxKind,
                                  std::string_view text,
                                  pg_size position = 0,
                                  pg_size fullWidth = 0) noexcept;

    virtual ~LanguageSyntaxTrivia() noexcept;

    LanguageSyntaxTrivia(const LanguageSyntaxTrivia&) noexcept = default;
    LanguageSyntaxTrivia(LanguageSyntaxTrivia&&) noexcept = default;
    LanguageSyntaxTrivia& operator=(const LanguageSyntaxTrivia&) noexcept = default;
    LanguageSyntaxTrivia& operator=(LanguageSyntaxTrivia&&) noexcept = default;

    inline virtual pg_size width() const noexcept override { return _fullWidth; }
    inline std::string_view text() const noexcept override { return _text; }
    virtual LanguageSyntaxNode* child(pg_size index) const noexcept override;
    inline bool isTrivia() const noexcept override final { return true; }

    inline pg_size leadingTriviaWidth() const noexcept override { return 0; }
    inline pg_size trailingTriviaWidth() const noexcept override { return 0; }

    inline virtual DirectiveStack applyDirectives(DirectiveStack stack) const noexcept { return std::move(stack); }

protected:
    std::string_view _text;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXTRIVIA_H
