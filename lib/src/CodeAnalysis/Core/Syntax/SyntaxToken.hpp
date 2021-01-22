#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
class ISyntaxTriviaList;

class SyntaxToken : public ISyntaxToken
{
public:
    SyntaxToken() = delete;

    explicit SyntaxToken(LanguageSyntaxNode* underlyingNode,
                         ISyntaxNode* parent = nullptr) noexcept;

    virtual ~SyntaxToken() noexcept;

    SyntaxToken(const SyntaxToken&) noexcept = default;
    SyntaxToken(SyntaxToken&&) noexcept = default;
    SyntaxToken& operator=(const SyntaxToken&) noexcept = default;
    SyntaxToken& operator=(SyntaxToken&&) noexcept = default;

    inline LanguageKind languageKind() const noexcept override { return _pUnderlyingNode->languageKind(); }
    inline SyntaxKind syntaxKind() const noexcept override { return _pUnderlyingNode->syntaxKind(); }
    inline std::string_view text() const noexcept override { return _pUnderlyingNode->text(); }
    inline pg_size position() const noexcept override { return _pUnderlyingNode->position(); }
    inline pg_size endPosition() const noexcept override { return _pUnderlyingNode->endPosition(); }
    inline ISyntaxNode* parent() const noexcept override { return _pParent; }
    inline pg_size width() const noexcept override { return _pUnderlyingNode->width(); }
    inline pg_size fullWidth() const noexcept override { return _pUnderlyingNode->fullWidth(); }
    inline pg_size spanStart() const noexcept override { return _pUnderlyingNode->spanStart(); }
    TextSpan span() const noexcept override;
    inline TextSpan fullSpan() const noexcept override { return _pUnderlyingNode->fullSpan(); }

    inline bool isMissing() const noexcept override { return _pUnderlyingNode->isMissing(); }
    inline bool value() const noexcept override;

    bool hasLeadingTrivia() const noexcept override;
    bool hasTrailingTrivia() const noexcept override;
    inline pg_size leadingTriviaWidth() const noexcept override { return _pUnderlyingNode->leadingTriviaWidth(); }
    inline pg_size trailingTriviaWidth() const noexcept override { return _pUnderlyingNode->trailingTriviaWidth(); }
    inline ISyntaxTriviaList* leadingTrivia() const noexcept override { return _pLeadingTrivia; }
    inline ISyntaxTriviaList* trailingTrivia() const noexcept override { return _pTrailingTrivia; }

protected:
    LanguageSyntaxNode* _pUnderlyingNode;
    ISyntaxNode* _pParent;
    ISyntaxTriviaList* _pLeadingTrivia;
    ISyntaxTriviaList* _pTrailingTrivia;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
