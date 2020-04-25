#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"

namespace polyglot::CodeAnalysis
{

DelphiSyntaxTree::DelphiSyntaxTree(std::string sourceText) noexcept
    : SyntaxTree{sourceText}
{}

DelphiSyntaxTree* DelphiSyntaxTree::parseSourceText(std::string sourceText) noexcept
{
    DelphiParser parser{sourceText};
    parser.parse();

    return new DelphiSyntaxTree{sourceText};
}

} // end namespace polyglot::CodeAnalysis
