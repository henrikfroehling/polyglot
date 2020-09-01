#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMHEADINGSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMHEADINGSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiProgramHeadingSyntax : public DelphiSyntaxNode
{
public:
    DelphiProgramHeadingSyntax() noexcept;
    virtual ~DelphiProgramHeadingSyntax() noexcept = default;
};

using DelphiProgramHeadingSyntaxPtr = std::shared_ptr<DelphiProgramHeadingSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMHEADINGSYNTAX_H