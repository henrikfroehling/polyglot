#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHICASELABELSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHICASELABELSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"
#include "Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiCaseLabelSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiCaseLabelSyntax(DelphiExpressionSyntax* expression,
                                   Core::Syntax::ISyntaxToken* dotDotToken = nullptr,
                                   DelphiExpressionSyntax* secondExpression = nullptr) noexcept;

    virtual ~DelphiCaseLabelSyntax() noexcept {}

    inline DelphiExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline Core::Syntax::ISyntaxToken* dotDotToken() const noexcept { return _pDotDotToken; }
    inline DelphiExpressionSyntax* secondExpression() const noexcept { return _pSecondExpression; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pExpression); }

    inline Core::Syntax::SyntaxVariant last() const noexcept override final
    {
        if (_pSecondExpression != nullptr)
            return Core::Syntax::SyntaxVariant::asNode(_pSecondExpression);

        return Core::Syntax::SyntaxVariant::asNode(_pExpression);
    }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiCaseLabelSyntax"; }

    static DelphiCaseLabelSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                         DelphiExpressionSyntax* expression,
                                         Core::Syntax::ISyntaxToken* dotDotToken = nullptr,
                                         DelphiExpressionSyntax* secondExpression = nullptr) noexcept;

private:
    DelphiExpressionSyntax* _pExpression;
    Core::Syntax::ISyntaxToken* _pDotDotToken; // optional
    DelphiExpressionSyntax* _pSecondExpression; // optional, requires _pDotDotToken
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHICASELABELSYNTAX_H
