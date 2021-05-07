#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXTOKEN_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXTOKEN_H

#include <string_view>x
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Text/TextSpan.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxTriviaList;

class SyntaxToken : public ISyntaxToken
{
public:
    virtual ~SyntaxToken() noexcept {}

    inline virtual ISyntaxNode* parent() const noexcept override { return nullptr; }

    inline virtual LanguageKind languageKind() const noexcept override { return LanguageKind::Unknown; }
    inline virtual SyntaxKind syntaxKind() const noexcept override { return SyntaxKind::None; }
    inline virtual std::string_view text() const noexcept override { return std::string_view{}; }

    inline virtual pg_size width() const noexcept override { return 0; }
    inline virtual pg_size fullWidth() const noexcept override { return 0; }
    inline virtual pg_size position() const noexcept override { return 0; }
    inline virtual pg_size endPosition() const noexcept override { return 0; }
    inline virtual pg_size spanStart() const noexcept override { return 0; }
    inline virtual TextSpan span() const noexcept override { return TextSpan{}; }
    inline virtual TextSpan fullSpan() const noexcept override { return TextSpan{}; }

    inline virtual bool hasLeadingTrivia() const noexcept override { return false; }
    inline virtual bool hasTrailingTrivia() const noexcept override { return false; }
    inline virtual pg_size leadingTriviaWidth() const noexcept override { return 0; }
    inline virtual pg_size trailingTriviaWidth() const noexcept override { return 0; }
    inline virtual ISyntaxTriviaList* leadingTrivia() const noexcept override { return nullptr; }
    inline virtual ISyntaxTriviaList* trailingTrivia() const noexcept override { return nullptr; }

    inline virtual bool isKeyword() const noexcept override { return false; }
    inline virtual bool isIdentifier() const noexcept override { return false; }
    inline virtual bool isLiteral() const noexcept override { return false; }
    inline virtual bool isPunctuation() const noexcept override { return false; }
    inline virtual bool isMissing() const noexcept override { return false; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXTOKEN_H
