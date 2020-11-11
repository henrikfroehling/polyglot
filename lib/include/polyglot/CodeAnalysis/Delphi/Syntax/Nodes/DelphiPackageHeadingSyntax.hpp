#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEHEADINGSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEHEADINGSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiPackageHeadingSyntax : public DelphiSyntaxNode
{
public:
    DelphiPackageHeadingSyntax() noexcept;
    virtual ~DelphiPackageHeadingSyntax() noexcept = default;
};

using DelphiPackageHeadingSyntaxPtr = std::shared_ptr<DelphiPackageHeadingSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEHEADINGSYNTAX_H
