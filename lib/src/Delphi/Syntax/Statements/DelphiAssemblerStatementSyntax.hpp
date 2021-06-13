#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIASSEMBLERSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIASSEMBLERSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiAssemblerStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiAssemblerStatementSyntax(Core::Syntax::ISyntaxToken* asmKeyword,
                                            Core::Syntax::ISyntaxToken* endKeyword,
                                            Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiAssemblerStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* asmKeyword() const noexcept { return _pAsmKeyword; }
    inline Core::Syntax::ISyntaxToken* endKeyword() const noexcept { return _pEndKeyword; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pAsmKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pSemiColonToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiAssemblerStatementSyntax"; }

    inline bool isAssemblerStatement() const noexcept override final { return true; }

    static DelphiAssemblerStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                  Core::Syntax::ISyntaxToken* asmKeyword,
                                                  Core::Syntax::ISyntaxToken* endKeyword,
                                                  Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pAsmKeyword;
    Core::Syntax::ISyntaxToken* _pEndKeyword;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIASSEMBLERSTATEMENTSYNTAX_H
