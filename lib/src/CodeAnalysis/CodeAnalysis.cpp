#include "polyglot/CodeAnalysis/CodeAnalysis.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{
namespace Delphi
{

std::shared_ptr<SyntaxTree> parseSourceText(std::string source) noexcept
{
    SourceText sourceText{std::move(source)};
    sourceText.parseLineStarts();
    return DelphiSyntaxTree::parseSourceText(std::move(sourceText));
}

} // end namespace Delphi
} // end namespace polyglot::CodeAnalysis
