#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXNODE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXNODE_H

#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/SyntaxNodeFlags.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;

class LanguageSyntaxNode
{
public:
    LanguageSyntaxNode() noexcept;

    explicit LanguageSyntaxNode(SyntaxKind syntaxKind,
                                pg_size position = 0,
                                pg_size fullWidth = 0) noexcept;

    virtual ~LanguageSyntaxNode() noexcept;

    LanguageSyntaxNode(const LanguageSyntaxNode&) noexcept = default;
    LanguageSyntaxNode(LanguageSyntaxNode&&) noexcept = default;
    LanguageSyntaxNode& operator=(const LanguageSyntaxNode&) noexcept = default;
    LanguageSyntaxNode& operator=(LanguageSyntaxNode&&) noexcept = default;

    virtual LanguageKind languageKind() const noexcept { return LanguageKind::Unknown; }
    inline SyntaxKind syntaxKind() const noexcept { return _syntaxKind; }
    inline SyntaxNodeFlags flags() const noexcept { return _flags; }
    inline virtual pg_size width() const noexcept { return _fullWidth - leadingTriviaWidth() - trailingTriviaWidth(); }
    inline pg_size fullWidth() const noexcept { return _fullWidth; }
    virtual LanguageSyntaxNode* child(pg_size index) const noexcept = 0;
    inline pg_size childCount() const noexcept { return _childCount; }
    inline pg_size position() const noexcept { return _position; }
    inline pg_size endPosition() const noexcept { return _position + _fullWidth; }
    inline pg_size spanStart() const noexcept { return _position + leadingTriviaWidth(); }
    inline TextSpan fullSpan() const noexcept { return TextSpan{_position, _fullWidth}; }

    inline bool containsTrivia() const noexcept { return (_flags & SyntaxNodeFlags::ContainsTrivia) != SyntaxNodeFlags::None; }
    inline bool containsStructuredTrivia() const noexcept { return (_flags & SyntaxNodeFlags::ContainsStructuredTrivia) != SyntaxNodeFlags::None; }
    inline bool containsSkippedText() const noexcept { return (_flags & SyntaxNodeFlags::ContainsSkippedText) != SyntaxNodeFlags::None; }
    inline bool containsDirectives() const noexcept { return (_flags & SyntaxNodeFlags::ContainsDirectives) != SyntaxNodeFlags::None; }
    inline virtual bool isToken() const noexcept { return false; }
    inline virtual bool isTrivia() const noexcept { return false; }
    inline virtual bool isStructuredTrivia() const noexcept { return false; }
    inline virtual bool isDirective() const noexcept { return false; }
    inline virtual bool isSkippedTokensTrivia() const noexcept { return false; }
    inline bool isMissing() const noexcept { return (_flags & SyntaxNodeFlags::IsMissing) != SyntaxNodeFlags::None; }

    inline bool hasLeadingTrivia() const noexcept { return leadingTriviaWidth() != 0; }
    inline bool hasTrailingTrivia() const noexcept { return trailingTriviaWidth() != 0; }
    virtual pg_size leadingTriviaWidth() const noexcept;
    virtual pg_size trailingTriviaWidth() const noexcept;
    inline virtual LanguageSyntaxNode* leadingTrivia() const noexcept { return nullptr; }
    inline virtual LanguageSyntaxNode* trailingTrivia() const noexcept { return nullptr; }

    LanguageSyntaxToken* firstToken() const noexcept;
    LanguageSyntaxToken* lastToken() const noexcept;

protected:
    pg_size _position;
    pg_size _fullWidth;
    pg_size _childCount;
    SyntaxKind _syntaxKind;
    SyntaxNodeFlags _flags;

private:
    LanguageSyntaxNode* firstTerminal() const noexcept;
    LanguageSyntaxNode* lastTerminal() const noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_LANGUAGESYNTAXNODE_H
