#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"

namespace polyglot::CodeAnalysis
{

DelphiSyntaxTree::DelphiSyntaxTree(SourceText sourceText) noexcept
    : SyntaxTree{std::move(sourceText)}
{}

std::unique_ptr<DelphiSyntaxTree> DelphiSyntaxTree::parseSourceText(SourceText sourceText) noexcept
{
    DelphiParser parser{&sourceText};
    parser.parse();
    return std::make_unique<DelphiSyntaxTree>(std::move(sourceText));
}

} // end namespace polyglot::CodeAnalysis
