#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H

#include <string_view>
#include <variant>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTriviaList.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;

using TokenValue = std::variant<std::monostate, bool, char, int, float, double, std::string_view>;

class SyntaxToken : public SyntaxNode, public virtual ISyntaxToken
{
public:
    SyntaxToken() noexcept;

    explicit SyntaxToken(SyntaxKind syntaxKind,
                         std::string_view text,
                         pg_size position = 0,
                         pg_size fullWidth = 0,
                         ISyntaxTriviaList* leadingTrivia = nullptr,
                         ISyntaxTriviaList* trailingTrivia = nullptr,
                         ISyntaxNode* parent = nullptr) noexcept;

    virtual ~SyntaxToken() noexcept;

    SyntaxToken(const SyntaxToken&) noexcept = default;
    SyntaxToken(SyntaxToken&&) noexcept = default;
    SyntaxToken& operator=(const SyntaxToken&) noexcept = default;
    SyntaxToken& operator=(SyntaxToken&&) noexcept = default;

    virtual ISyntaxNode* child(pg_size index) const override;
    inline std::string_view text() const noexcept override { return _text; }
    inline bool isToken() const noexcept override final { return true; }
    inline bool hasMissingTokens() const noexcept override final { return false; }
    TokenValue value() const noexcept;
    bool booleanValue() const noexcept override;

    inline bool hasLeadingTrivia() const noexcept override { return _pLeadingTrivia != nullptr && _pLeadingTrivia->childCount() > 0; }
    inline bool hasTrailingTrivia() const noexcept override { return _pTrailingTrivia != nullptr && _pTrailingTrivia->childCount() > 0; }
    inline pg_size leadingTriviaWidth() const noexcept override { return _pLeadingTrivia != nullptr ? static_cast<ISyntaxTriviaList*>(_pLeadingTrivia)->fullWidth() : 0; }
    inline pg_size trailingTriviaWidth() const noexcept override { return _pTrailingTrivia != nullptr ? static_cast<ISyntaxTriviaList*>(_pTrailingTrivia)->fullWidth() : 0; }
    inline ISyntaxTriviaList* leadingTrivia() const noexcept override { return _pLeadingTrivia; }
    inline ISyntaxTriviaList* trailingTrivia() const noexcept override { return _pTrailingTrivia; }

protected:
    std::string_view _text;
    ISyntaxTriviaList* _pLeadingTrivia;
    ISyntaxTriviaList* _pTrailingTrivia;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
