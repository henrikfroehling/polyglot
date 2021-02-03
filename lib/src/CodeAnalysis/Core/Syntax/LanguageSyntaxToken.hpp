#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXTOKEN_H

#include <string_view>
#include <variant>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Text/TextSpan.hpp"
#include "LanguageSyntaxList.hpp"
#include "LanguageSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

using TokenValue = std::variant<std::monostate, bool, char, int, float, double, std::string_view>;

class LanguageSyntaxToken : public LanguageSyntaxNode
{
public:
    LanguageSyntaxToken() noexcept;

    explicit LanguageSyntaxToken(SyntaxKind syntaxKind,
                                 std::string_view text,
                                 pg_size position = 0,
                                 pg_size fullWidth = 0,
                                 LanguageSyntaxList* leadingTrivia = nullptr,
                                 LanguageSyntaxList* trailingTrivia = nullptr) noexcept;

    virtual ~LanguageSyntaxToken() noexcept;

    LanguageSyntaxToken(const LanguageSyntaxToken&) noexcept = default;
    LanguageSyntaxToken(LanguageSyntaxToken&&) noexcept = default;
    LanguageSyntaxToken& operator=(const LanguageSyntaxToken&) noexcept = default;
    LanguageSyntaxToken& operator=(LanguageSyntaxToken&&) noexcept = default;

    virtual LanguageSyntaxNode* child(pg_size index) const override;
    inline std::string_view text() const noexcept override { return _text; }
    TokenValue value() const noexcept;
    bool booleanValue() const noexcept;
    inline bool isToken() const noexcept override final { return true; }

    inline pg_size leadingTriviaWidth() const noexcept override { return _pLeadingTrivia != nullptr ? _pLeadingTrivia->fullWidth() : 0; }
    inline pg_size trailingTriviaWidth() const noexcept override { return _pTrailingTrivia != nullptr ? _pTrailingTrivia->fullWidth() : 0; }
    inline LanguageSyntaxNode* leadingTrivia() const noexcept override { return _pLeadingTrivia; }
    inline LanguageSyntaxNode* trailingTrivia() const noexcept override { return _pTrailingTrivia; }

protected:
    std::string_view _text;
    LanguageSyntaxList* _pLeadingTrivia;
    LanguageSyntaxList* _pTrailingTrivia;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXTOKEN_H
