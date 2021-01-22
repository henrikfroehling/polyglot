#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxToken;

class SyntaxTrivia : public ISyntaxTrivia
{
public:
    SyntaxTrivia() = delete;

    explicit SyntaxTrivia(LanguageSyntaxNode* underlyingNode,
                          ISyntaxToken* token = nullptr) noexcept;

    virtual ~SyntaxTrivia() noexcept;

    SyntaxTrivia(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia(SyntaxTrivia&&) noexcept = default;
    SyntaxTrivia& operator=(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia& operator=(SyntaxTrivia&&) noexcept = default;

    inline LanguageKind languageKind() const noexcept override { return _pUnderlyingNode->languageKind(); }
    inline SyntaxKind syntaxKind() const noexcept override { return _pUnderlyingNode->syntaxKind(); }
    inline std::string_view text() const noexcept override { return _pUnderlyingNode->text(); }
    inline pg_size position() const noexcept override { return _pUnderlyingNode->position(); }
    inline pg_size endPosition() const noexcept override { return _pUnderlyingNode->endPosition(); }
    inline ISyntaxToken* token() const noexcept override { return _pToken; }
    inline pg_size width() const noexcept override { return _pUnderlyingNode->width(); }
    inline pg_size fullWidth() const noexcept override { return _pUnderlyingNode->fullWidth(); }
    inline pg_size spanStart() const noexcept override { return _pUnderlyingNode->spanStart(); }
    TextSpan span() const noexcept override;
    inline TextSpan fullSpan() const noexcept override { return _pUnderlyingNode->fullSpan(); }
    inline bool isDirective() const noexcept override { return _pUnderlyingNode->isDirective(); }
    inline bool isSkippedTokensTrivia() const noexcept override { return _pUnderlyingNode->isSkippedTokensTrivia(); }

protected:
    LanguageSyntaxNode* _pUnderlyingNode;
    ISyntaxToken* _pToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
