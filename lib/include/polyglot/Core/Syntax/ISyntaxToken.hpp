#ifndef POLYGLOT_CORE_SYNTAX_ISYNTAXTOKEN_H
#define POLYGLOT_CORE_SYNTAX_ISYNTAXTOKEN_H

#include <string_view>
#include <variant>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Text/TextSpan.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxTriviaList;

using TokenValue = std::variant<std::monostate, bool, char, int, float, double, std::string_view>;

class POLYGLOT_API ISyntaxToken
{
public:
    virtual ~ISyntaxToken() noexcept {}

    virtual ISyntaxNode* parent() const noexcept = 0;

    virtual LanguageKind languageKind() const noexcept = 0;
    virtual SyntaxKind syntaxKind() const noexcept = 0;
    virtual std::string_view text() const noexcept = 0;
    virtual std::string_view textIncludingTrivia() const noexcept = 0;

    virtual pg_size width() const noexcept = 0;
    virtual pg_size fullWidth() const noexcept = 0;
    virtual pg_size position() const noexcept = 0;
    virtual pg_size endPosition() const noexcept = 0;
    virtual pg_size positionIncludingTrivia() const noexcept = 0;
    virtual pg_size endPositionIncludingTrivia() const noexcept = 0;
    virtual Text::TextSpan span() const noexcept = 0;
    virtual Text::TextSpan fullSpan() const noexcept = 0;

    virtual bool hasLeadingTrivia() const noexcept = 0;
    virtual bool hasTrailingTrivia() const noexcept = 0;
    virtual pg_size leadingTriviaWidth() const noexcept = 0;
    virtual pg_size trailingTriviaWidth() const noexcept = 0;
    virtual ISyntaxTriviaList* leadingTrivia() const noexcept = 0;
    virtual ISyntaxTriviaList* trailingTrivia() const noexcept = 0;

    virtual bool isKeyword() const noexcept = 0;
    virtual bool isIdentifier() const noexcept = 0;
    virtual bool isLiteral() const noexcept = 0;
    virtual bool isPunctuation() const noexcept = 0;
    virtual bool isMissing() const noexcept = 0;

    virtual TokenValue value() const noexcept = 0;
    virtual bool booleanValue() const noexcept = 0;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_ISYNTAXTOKEN_H
