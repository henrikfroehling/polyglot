#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxToken;

class SyntaxTrivia : public ISyntaxTrivia
{
public:
    SyntaxTrivia() = delete;

    explicit SyntaxTrivia(LanguageSyntaxTrivia* underlyingTrivia,
                          ISyntaxToken* token = nullptr) noexcept;

    virtual ~SyntaxTrivia() noexcept;

    SyntaxTrivia(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia(SyntaxTrivia&&) noexcept = default;
    SyntaxTrivia& operator=(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia& operator=(SyntaxTrivia&&) noexcept = default;

    inline LanguageKind languageKind() const noexcept override { return _pUnderlyingTrivia->languageKind(); }
    inline SyntaxKind syntaxKind() const noexcept override { return _pUnderlyingTrivia->syntaxKind(); }
    inline std::string_view text() const noexcept override { return _pUnderlyingTrivia->text(); }
    inline pg_size position() const noexcept override { return _pUnderlyingTrivia->position(); }
    inline pg_size endPosition() const noexcept override { return _pUnderlyingTrivia->endPosition(); }
    inline ISyntaxToken* token() const noexcept override { return _pToken; }
    inline pg_size width() const noexcept override { return _pUnderlyingTrivia->width(); }
    inline pg_size fullWidth() const noexcept override { return _pUnderlyingTrivia->fullWidth(); }
    inline pg_size spanStart() const noexcept override { return _pUnderlyingTrivia->spanStart(); }
    TextSpan span() const noexcept override;
    inline TextSpan fullSpan() const noexcept override { return _pUnderlyingTrivia->fullSpan(); }
    inline bool isDirective() const noexcept override { return _pUnderlyingTrivia->isDirective(); }
    inline bool isSkippedTokensTrivia() const noexcept override { return _pUnderlyingTrivia->isSkippedTokensTrivia(); }

protected:
    LanguageSyntaxTrivia* _pUnderlyingTrivia;
    ISyntaxToken* _pToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXTRIVIA_H
