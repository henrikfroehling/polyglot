#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDIFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDIFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API EndIfDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit EndIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                        Ptr<SyntaxToken> startToken,
                                        Ptr<SyntaxToken> endIfKeyword,
                                        Ptr<SyntaxToken> endOfDirectiveToken,
                                        bool isActive) noexcept;

    virtual ~EndIfDirectiveTriviaSyntax() noexcept = default;
    inline virtual const Ptr<SyntaxToken> startToken() const noexcept override { return _ptrStartToken; }
    inline virtual const Ptr<SyntaxToken> endIfKeyword() const noexcept { return _ptrEndIfKeyword; }
    inline virtual const Ptr<SyntaxToken> endOfDirectiveToken() const noexcept override { return _ptrEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }

    static Ptr<EndIfDirectiveTriviaSyntax> create(Ptr<SyntaxToken> startToken,
                                                  Ptr<SyntaxToken> endIFKeyword,
                                                  Ptr<SyntaxToken> endOfDirectiveToken,
                                                  bool isActive) noexcept;

private:
    Ptr<SyntaxToken> _ptrStartToken;
    Ptr<SyntaxToken> _ptrEndIfKeyword;
    Ptr<SyntaxToken> _ptrEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ENDIFDIRECTIVETRIVIASYNTAX_H
