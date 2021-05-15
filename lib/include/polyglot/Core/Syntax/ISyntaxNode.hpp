#ifndef POLYGLOT_CORE_SYNTAX_ISYNTAXNODE_H
#define POLYGLOT_CORE_SYNTAX_ISYNTAXNODE_H

#include <string>
#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Text/TextSpan.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxTrivia;
class ISyntaxTriviaList;

class POLYGLOT_API ISyntaxNode
{
public:
    virtual ~ISyntaxNode() noexcept {}

    virtual ISyntaxNode* parent() const noexcept = 0;
    virtual ISyntaxTrivia* trivia() const noexcept = 0; // if node is part of structured trivia

    virtual LanguageKind languageKind() const noexcept = 0;
    virtual SyntaxKind syntaxKind() const noexcept = 0;
    virtual std::string_view text() const noexcept = 0;

    virtual pg_size width() const noexcept = 0;
    virtual pg_size fullWidth() const noexcept = 0;
    virtual pg_size position() const noexcept = 0;
    virtual pg_size endPosition() const noexcept = 0;
    virtual pg_size positionIncludingTrivia() const noexcept = 0;
    virtual pg_size endPositionIncludingTrivia() const noexcept = 0;
    virtual Text::TextSpan span() const noexcept = 0;
    virtual Text::TextSpan fullSpan() const noexcept = 0;

    virtual pg_size childCount() const noexcept = 0;
    virtual SyntaxVariant child(pg_size index) const = 0;

    virtual bool hasLeadingTrivia() const noexcept = 0;
    virtual bool hasTrailingTrivia() const noexcept = 0;
    virtual pg_size leadingTriviaWidth() const noexcept = 0;
    virtual pg_size trailingTriviaWidth() const noexcept = 0;
    virtual ISyntaxTriviaList* leadingTrivia() const noexcept = 0;
    virtual ISyntaxTriviaList* trailingTrivia() const noexcept = 0;

    virtual bool isExpression() const noexcept = 0;
    virtual bool isStatement() const noexcept = 0;
    virtual bool isDeclaration() const noexcept = 0;
    virtual bool isClause() const noexcept = 0;
    virtual bool hasMissingTokens() const noexcept = 0;

    virtual std::string toString() const noexcept = 0;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_ISYNTAXNODE_H
