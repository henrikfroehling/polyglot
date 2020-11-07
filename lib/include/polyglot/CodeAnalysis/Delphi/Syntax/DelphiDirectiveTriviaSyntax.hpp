#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIDIRECTIVETRIVIASYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiStructuredTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiDirectiveTriviaSyntax : public DelphiStructuredTriviaSyntax
{
public:
    explicit DelphiDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiDirectiveTriviaSyntax() noexcept = default;
};

using DelphiDirectiveTriviaSyntaxPtr = std::shared_ptr<DelphiDirectiveTriviaSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIDIRECTIVETRIVIASYNTAX_H
