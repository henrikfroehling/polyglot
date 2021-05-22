#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXMISSINGTOKEN_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXMISSINGTOKEN_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxTriviaList;

class SyntaxMissingToken : public SyntaxToken
{
public:
    explicit SyntaxMissingToken(SyntaxKind syntaxKind,
                                pg_string_view text,
                                pg_size position = 0,
                                pg_size fullWidth = 0,
                                ISyntaxTriviaList* leadingTrivia = nullptr,
                                ISyntaxTriviaList* trailingTrivia = nullptr,
                                ISyntaxNode* parent = nullptr) noexcept;

    virtual ~SyntaxMissingToken() noexcept {}

    SyntaxMissingToken(const SyntaxMissingToken&) noexcept = default;
    SyntaxMissingToken(SyntaxMissingToken&&) noexcept = default;
    SyntaxMissingToken& operator=(const SyntaxMissingToken&) noexcept = default;
    SyntaxMissingToken& operator=(SyntaxMissingToken&&) noexcept = default;

    pg_string toString() const noexcept override;
    pg_string toShortString() const noexcept override;
    virtual pg_string typeName() const noexcept override { return L"SyntaxMissingToken"; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXMISSINGTOKEN_H
