#ifndef POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIUNDEFDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIUNDEFDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUndefDirectiveTriviaSyntax : public Core::Syntax::UndefDirectiveTriviaSyntax
{
public:
    explicit DelphiUndefDirectiveTriviaSyntax(Core::Syntax::SyntaxKind syntaxKind,
                                              Core::Syntax::ISyntaxToken* startToken,
                                              Core::Syntax::ISyntaxToken* undefKeyword,
                                              Core::Syntax::ISyntaxToken* name,
                                              Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                              bool isActive) noexcept;

    virtual ~DelphiUndefDirectiveTriviaSyntax() noexcept {}
    inline virtual Core::Syntax::ISyntaxToken* startToken() const noexcept override { return _pStartToken; }
    inline virtual Core::Syntax::ISyntaxToken* undefKeyword() const noexcept { return _pUndefKeyword; }
    inline virtual Core::Syntax::ISyntaxToken* name() const noexcept { return _pName; }
    inline virtual Core::Syntax::ISyntaxToken* endOfDirectiveToken() const noexcept override { return _pEndOfDirectiveToken; }
    inline virtual bool isActive() const noexcept override { return _isActive; }
    inline pg_size childCount() const noexcept override final { return 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline std::string_view definitionName() const noexcept override final { return name()->text(); }

    static DelphiUndefDirectiveTriviaSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                    Core::Syntax::ISyntaxToken* startToken,
                                                    Core::Syntax::ISyntaxToken* undefKeyword,
                                                    Core::Syntax::ISyntaxToken* name,
                                                    Core::Syntax::ISyntaxToken* endOfDirectiveToken,
                                                    bool isActive) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pStartToken;
    Core::Syntax::ISyntaxToken* _pUndefKeyword;
    Core::Syntax::ISyntaxToken* _pName;
    Core::Syntax::ISyntaxToken* _pEndOfDirectiveToken;
    bool _isActive;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_TRIVIA_DELPHIUNDEFDIRECTIVETRIVIASYNTAX_H
