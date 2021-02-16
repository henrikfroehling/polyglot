#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXMISSINGTOKEN_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXMISSINGTOKEN_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
class ISyntaxTriviaList;

class SyntaxMissingToken : public SyntaxToken
{
public:
    SyntaxMissingToken() noexcept;

    explicit SyntaxMissingToken(SyntaxKind syntaxKind,
                                std::string_view text,
                                pg_size position = 0,
                                pg_size fullWidth = 0,
                                ISyntaxTriviaList* leadingTrivia = nullptr,
                                ISyntaxTriviaList* trailingTrivia = nullptr,
                                ISyntaxNode* parent = nullptr) noexcept;

    virtual ~SyntaxMissingToken() noexcept;

    SyntaxMissingToken(const SyntaxMissingToken&) noexcept = default;
    SyntaxMissingToken(SyntaxMissingToken&&) noexcept = default;
    SyntaxMissingToken& operator=(const SyntaxMissingToken&) noexcept = default;
    SyntaxMissingToken& operator=(SyntaxMissingToken&&) noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXMISSINGTOKEN_H
