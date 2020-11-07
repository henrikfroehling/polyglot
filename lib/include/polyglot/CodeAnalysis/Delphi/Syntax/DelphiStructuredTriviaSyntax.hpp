#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISTRUCTUREDTRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISTRUCTUREDTRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiStructuredTriviaSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiStructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiStructuredTriviaSyntax() noexcept = default;
};

using DelphiStructuredTriviaSyntaxPtr = std::shared_ptr<DelphiStructuredTriviaSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISTRUCTUREDTRIVIASYNTAX_H
