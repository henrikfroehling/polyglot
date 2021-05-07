#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIA_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIA_H

#include <string_view>
#include "polyglot/CodeAnalysis/Text/TextSpan.hpp"
#include "polyglot/Core/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

class SyntaxTrivia : public ISyntaxTrivia
{
public:
    virtual ~SyntaxTrivia() noexcept {}

    inline virtual ISyntaxToken* token() const noexcept override { return nullptr; }

    inline virtual LanguageKind languageKind() const noexcept override { return LanguageKind::Unknown; }
    inline virtual SyntaxKind syntaxKind() const noexcept override { return SyntaxKind::None; }
    inline virtual std::string_view text() const noexcept override { return std::string_view{}; }

    inline virtual pg_size width() const noexcept override { return 0; }
    inline virtual pg_size position() const noexcept override { return 0; }
    inline virtual pg_size endPosition() const noexcept override { return 0; }
    inline virtual pg_size spanStart() const noexcept override { return 0; }
    inline virtual CodeAnalysis::TextSpan span() const noexcept override { return CodeAnalysis::TextSpan{}; }

    inline virtual bool isStructuredTrivia() const noexcept override { return false; }
    inline virtual bool isDirective() const noexcept override { return false; }
    inline virtual bool isSkippedTokensTrivia() const noexcept override { return false; }
    inline virtual bool isWhitespace() const noexcept override { return false; }
    inline virtual bool isComment() const noexcept override { return false; }
    inline virtual bool isLineEnding() const noexcept override { return false; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIA_H
