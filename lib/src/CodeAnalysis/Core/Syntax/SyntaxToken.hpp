#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
class ISyntaxTrivia;

class SyntaxToken : public ISyntaxToken
{
public:
    explicit SyntaxToken(LanguageSyntaxToken* underlyingToken = nullptr,
                         ISyntaxNode* parent = nullptr) noexcept;

    virtual ~SyntaxToken() noexcept;

    SyntaxToken(const SyntaxToken&) noexcept = default;
    SyntaxToken(SyntaxToken&&) noexcept = default;
    SyntaxToken& operator=(const SyntaxToken&) noexcept = default;
    SyntaxToken& operator=(SyntaxToken&&) noexcept = default;

    inline LanguageKind languageKind() const noexcept override { return _pUnderlyingToken->languageKind(); }
    inline SyntaxKind syntaxKind() const noexcept override { return _pUnderlyingToken->syntaxKind(); }
    inline std::string_view text() const noexcept override { return _pUnderlyingToken->text(); }
    inline pg_size position() const noexcept override { return _pUnderlyingToken->position(); }
    inline pg_size endPosition() const noexcept override { return _pUnderlyingToken->endPosition(); }
    inline ISyntaxNode* parent() const noexcept override { return _pParent; }
    inline pg_size width() const noexcept override { return _pUnderlyingToken->width(); }
    inline pg_size fullWidth() const noexcept override { return _pUnderlyingToken->fullWidth(); }
    inline pg_size spanStart() const noexcept override { return _pUnderlyingToken->spanStart(); }
    inline TextSpan span() const noexcept override;
    inline TextSpan fullSpan() const noexcept override { return _pUnderlyingToken->fullSpan(); }

    inline bool isMissing() const noexcept override { return _pUnderlyingToken->isMissing(); }
    inline bool value() const noexcept override;

    inline bool hasLeadingTrivia() const noexcept override { return leadingTrivia().size() != 0; }
    inline bool hasTrailingTrivia() const noexcept override { return trailingTrivia().size() != 0; }
    inline pg_size leadingTriviaWidth() const noexcept override { return _pUnderlyingToken->leadingTriviaWidth(); }
    inline pg_size trailingTriviaWidth() const noexcept override { return _pUnderlyingToken->trailingTriviaWidth(); }
    inline std::vector<ISyntaxTrivia*> leadingTrivia() const noexcept override { return _pUnderlyingToken->leadingTriviaCore(); }
    inline std::vector<ISyntaxTrivia*> trailingTrivia() const noexcept override { return _pUnderlyingToken->trailingTriviaCore(); }

protected:
    LanguageSyntaxToken* _pUnderlyingToken;
    ISyntaxNode* _pParent;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTOKEN_H
