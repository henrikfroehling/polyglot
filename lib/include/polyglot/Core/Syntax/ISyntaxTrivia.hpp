#ifndef POLYGLOT_CORE_SYNTAX_ISYNTAXTRIVIA_H
#define POLYGLOT_CORE_SYNTAX_ISYNTAXTRIVIA_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Text/TextSpan.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

class POLYGLOT_API ISyntaxTrivia
{
public:
    virtual ~ISyntaxTrivia() noexcept {}

    virtual ISyntaxToken* token() const noexcept = 0;

    virtual LanguageKind languageKind() const noexcept = 0;
    virtual SyntaxKind syntaxKind() const noexcept = 0;
    virtual std::string_view text() const noexcept = 0;

    virtual pg_size width() const noexcept = 0;
    virtual pg_size position() const noexcept = 0;
    virtual pg_size endPosition() const noexcept = 0;
    virtual pg_size spanStart() const noexcept = 0;
    virtual TextSpan span() const noexcept = 0;

    virtual bool isStructuredTrivia() const noexcept = 0;
    virtual bool isDirective() const noexcept = 0;
    virtual bool isSkippedTokensTrivia() const noexcept = 0;
    virtual bool isWhitespace() const noexcept = 0;
    virtual bool isComment() const noexcept = 0;
    virtual bool isLineEnding() const noexcept = 0;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_ISYNTAXTRIVIA_H
