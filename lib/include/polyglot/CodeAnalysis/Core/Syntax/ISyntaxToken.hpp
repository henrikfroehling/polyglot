#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ISYNTAXTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ISYNTAXTOKEN_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
class ISyntaxTriviaList;

class POLYGLOT_API ISyntaxToken
{
public:
    virtual ~ISyntaxToken() noexcept = default;

    virtual LanguageKind languageKind() const noexcept = 0;
    virtual SyntaxKind syntaxKind() const noexcept = 0;
    virtual std::string_view text() const noexcept = 0;
    virtual pg_size position() const noexcept = 0;
    virtual pg_size endPosition() const noexcept = 0;
    virtual ISyntaxNode* parent() const noexcept = 0;
    virtual pg_size width() const noexcept = 0;
    virtual pg_size fullWidth() const noexcept = 0;
    virtual pg_size spanStart() const noexcept = 0;
    virtual TextSpan span() const noexcept = 0;
    virtual TextSpan fullSpan() const noexcept = 0;

    virtual bool isMissing() const noexcept = 0;
    virtual bool booleanValue() const noexcept = 0;

    virtual bool hasLeadingTrivia() const noexcept = 0;
    virtual bool hasTrailingTrivia() const noexcept = 0;
    virtual pg_size leadingTriviaWidth() const noexcept = 0;
    virtual pg_size trailingTriviaWidth() const noexcept = 0;
    virtual ISyntaxTriviaList* leadingTrivia() const noexcept = 0;
    virtual ISyntaxTriviaList* trailingTrivia() const noexcept = 0;

protected:
    ISyntaxToken() noexcept = default;
    ISyntaxToken(const ISyntaxToken&) noexcept = default;
    ISyntaxToken(ISyntaxToken&&) noexcept = default;
    ISyntaxToken& operator=(const ISyntaxToken&) noexcept = default;
    ISyntaxToken& operator=(ISyntaxToken&&) noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ISYNTAXTOKEN_H
