#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiParser.hpp"

namespace polyglot::CodeAnalysis
{

DelphiSyntaxTree::DelphiSyntaxTree(SourceTextPtr sourceText,
                                   SyntaxNodePtr root) noexcept
    : SyntaxTree{std::move(sourceText), std::move(root)}
{}

std::shared_ptr<DelphiSyntaxTree> DelphiSyntaxTree::parseSourceText(SourceTextPtr sourceText) noexcept
{
    DelphiParser parser{sourceText};
    SyntaxNodePtr syntaxTreeRoot = parser.parse();
    return std::make_shared<DelphiSyntaxTree>(std::move(sourceText), std::move(syntaxTreeRoot));
}

} // end namespace polyglot::CodeAnalysis
