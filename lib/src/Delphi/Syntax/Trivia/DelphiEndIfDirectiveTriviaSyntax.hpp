#ifndef POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIENDIFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIENDIFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiEndIfDirectiveTriviaSyntax : public Core::Syntax::DirectiveTriviaSyntax
{
public:
    explicit DelphiEndIfDirectiveTriviaSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                              Core::Syntax::ISyntaxToken* startToken,
                                              Core::Syntax::ISyntaxToken* endIfKeyword,
                                              Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                              bool isActive) noexcept;

    virtual ~DelphiEndIfDirectiveTriviaSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual Core::Syntax::ISyntaxToken* endIfKeyword() const noexcept { return _pEndIfKeyword; }
    inline virtual Core::Syntax::ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiEndIfDirectiveTriviaSyntax"; }

    static DelphiEndIfDirectiveTriviaSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                    Core::Syntax::ISyntaxToken* startToken,
                                                    Core::Syntax::ISyntaxToken* endIFKeyword,
                                                    Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                                    bool isActive) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pStartToken;
    Core::Syntax::ISyntaxToken* _pEndIfKeyword;
    Core::Syntax::ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIENDIFDIRECTIVETRIVIASYNTAX_H
