#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXNODE_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXNODE_H

#include <string_view>
#include "polyglot/CodeAnalysis/Text/TextSpan.hpp"
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxNodeOrToken.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxTriviaList;

class SyntaxNode : public ISyntaxNode
{
public:
    virtual ~SyntaxNode() noexcept {}

    inline virtual ISyntaxNode* parent() const noexcept override { return nullptr; }

    inline virtual LanguageKind languageKind() const noexcept override { return LanguageKind::Unknown; }
    inline virtual SyntaxKind syntaxKind() const noexcept override { return SyntaxKind::None; }
    inline virtual std::string_view text() const noexcept override { return std::string_view{}; }

    inline virtual pg_size width() const noexcept override { return 0; }
    inline virtual pg_size fullWidth() const noexcept override { return 0; }
    inline virtual pg_size position() const noexcept override { return 0; }
    inline virtual pg_size endPosition() const noexcept override { return 0; }
    inline virtual pg_size spanStart() const noexcept override { return 0; }
    inline virtual CodeAnalysis::TextSpan span() const noexcept override { return CodeAnalysis::TextSpan{}; }
    inline virtual CodeAnalysis::TextSpan fullSpan() const noexcept override { return CodeAnalysis::TextSpan{}; }

    inline virtual pg_size childCount() const noexcept override { return 0; }
    inline virtual SyntaxNodeOrToken child(pg_size index) const override { return SyntaxNodeOrToken{nullptr, nullptr}; }

    inline virtual bool hasLeadingTrivia() const noexcept override { return false; }
    inline virtual bool hasTrailingTrivia() const noexcept override { return false; }
    inline virtual pg_size leadingTriviaWidth() const noexcept override { return 0; }
    inline virtual pg_size trailingTriviaWidth() const noexcept override { return 0; }
    inline virtual ISyntaxTriviaList* leadingTrivia() const noexcept override { return nullptr; }
    inline virtual ISyntaxTriviaList* trailingTrivia() const noexcept override { return nullptr; }

    inline virtual bool isExpression() const noexcept override { return false; }
    inline virtual bool isStatement() const noexcept override { return false; }
    inline virtual bool isDeclaration() const noexcept override { return false; }
    inline virtual bool isClause() const noexcept override { return false; }
    inline virtual bool hasMissingTokens() const noexcept override { return false; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXNODE_H
