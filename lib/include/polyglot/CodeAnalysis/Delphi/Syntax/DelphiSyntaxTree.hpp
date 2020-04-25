#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXTREE_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXTREE_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiSyntaxTree : public SyntaxTree
{
public:
    DelphiSyntaxTree() = delete;
    static DelphiSyntaxTree* parseSourceText(std::string sourceText) noexcept;

private:
    explicit DelphiSyntaxTree(std::string sourceText) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISYNTAXTREE_H
