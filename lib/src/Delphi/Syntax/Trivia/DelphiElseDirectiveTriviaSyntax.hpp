#ifndef POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIELSEDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIELSEDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiElseDirectiveTriviaSyntax : public Core::Syntax::BranchingDirectiveTriviaSyntax
{
public:
    explicit DelphiElseDirectiveTriviaSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                             Core::Syntax::ISyntaxToken* startToken,
                                             Core::Syntax::ISyntaxToken* elseKeyword,
                                             Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                             bool isActive,
                                             bool isBranchTaken) noexcept;

    virtual ~DelphiElseDirectiveTriviaSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual Core::Syntax::ISyntaxToken* elseKeyword() const noexcept { return _pElseKeyword; }
    inline virtual Core::Syntax::ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline virtual bool isBranchTaken() const noexcept override { return _isBranchTaken; }
    inline pg_size childCount() const noexcept override final { return 3; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiElseDirectiveTriviaSyntax"; }

    static DelphiElseDirectiveTriviaSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                   Core::Syntax::ISyntaxToken* startToken,
                                                   Core::Syntax::ISyntaxToken* elseKeyword,
                                                   Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                                   bool isActive,
                                                   bool isBranchTaken) noexcept;
    
private:
    Core::Syntax::ISyntaxToken* _pStartToken;
    Core::Syntax::ISyntaxToken* _pElseKeyword;
    Core::Syntax::ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
    bool _isBranchTaken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIELSEDIRECTIVETRIVIASYNTAX_H
