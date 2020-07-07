#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"

namespace polyglot::CodeAnalysis
{

DelphiSyntaxTree::DelphiSyntaxTree(SourceText sourceText) noexcept
    : SyntaxTree{std::move(sourceText)}
{}

DelphiSyntaxTree* DelphiSyntaxTree::parseSourceText(SourceText sourceText) noexcept
{
    DelphiParser parser{sourceText};
    parser.parse();
    return new DelphiSyntaxTree{std::move(sourceText)};
}

} // end namespace polyglot::CodeAnalysis
