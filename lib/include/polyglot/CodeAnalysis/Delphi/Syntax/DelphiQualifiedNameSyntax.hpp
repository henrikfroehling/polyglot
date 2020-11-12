#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiNameSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiQualifiedNameSyntax : public DelphiNameSyntax
{
public:
    explicit DelphiQualifiedNameSyntax(DelphiNameSyntaxPtr left,
                                       SyntaxTokenPtr dotToken,
                                       DelphiSimpleNameSyntaxPtr right) noexcept;

    virtual ~DelphiQualifiedNameSyntax() noexcept = default;

private:
    DelphiNameSyntaxPtr _ptrLeft;
    SyntaxTokenPtr _ptrDotToken;
    DelphiSimpleNameSyntaxPtr _ptrRight;
};

using DelphiQualifiedNameSyntaxPtr = std::shared_ptr<DelphiQualifiedNameSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H
