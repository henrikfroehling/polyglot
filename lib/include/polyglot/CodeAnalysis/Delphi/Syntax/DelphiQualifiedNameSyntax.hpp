#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiNameSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiQualifiedNameSyntax : public DelphiNameSyntax
{
public:
    explicit DelphiQualifiedNameSyntax(SyntaxKind syntaxKind,
                                       std::unique_ptr<DelphiNameSyntax> left,
                                       std::unique_ptr<SyntaxToken> dotToken,
                                       std::unique_ptr<DelphiSimpleNameSyntax> right) noexcept;

    virtual ~DelphiQualifiedNameSyntax() noexcept = default;
    inline DelphiNameSyntax* left() const noexcept { return _ptrLeft.get(); }
    inline SyntaxToken* dotToken() const noexcept { return _ptrDotToken.get(); }
    inline DelphiSimpleNameSyntax* right() const noexcept { return _ptrRight.get(); }

private:
    std::unique_ptr<DelphiNameSyntax> _ptrLeft;
    std::unique_ptr<SyntaxToken> _ptrDotToken;
    std::unique_ptr<DelphiSimpleNameSyntax> _ptrRight;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H
