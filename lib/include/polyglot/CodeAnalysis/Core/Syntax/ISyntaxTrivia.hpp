#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ISYNTAXTRIVIA_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ISYNTAXTRIVIA_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxToken;

class POLYGLOT_API ISyntaxTrivia
{
public:
    virtual ~ISyntaxTrivia() noexcept = default;

    virtual LanguageKind languageKind() const noexcept = 0;
    virtual SyntaxKind syntaxKind() const noexcept = 0;
    virtual std::string_view text() const noexcept = 0;
    virtual pg_size position() const noexcept = 0;
    virtual pg_size endPosition() const noexcept = 0;
    virtual ISyntaxToken* token() const noexcept = 0;
    virtual pg_size width() const noexcept = 0;
    virtual pg_size fullWidth() const noexcept = 0;
    virtual pg_size spanStart() const noexcept = 0;
    virtual TextSpan span() const noexcept = 0;
    virtual TextSpan fullSpan() const noexcept = 0;
    virtual bool isDirective() const noexcept = 0;
    virtual bool isSkippedTokensTrivia() const noexcept = 0;

protected:
    ISyntaxTrivia() noexcept = default;
    ISyntaxTrivia(const ISyntaxTrivia&) noexcept = default;
    ISyntaxTrivia(ISyntaxTrivia&&) noexcept = default;
    ISyntaxTrivia& operator=(const ISyntaxTrivia&) noexcept = default;
    ISyntaxTrivia& operator=(ISyntaxTrivia&&) noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ISYNTAXTRIVIA_H
