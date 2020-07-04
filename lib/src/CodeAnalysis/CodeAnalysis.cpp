#include "polyglot/CodeAnalysis/CodeAnalysis.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{
namespace Delphi
{

SyntaxTree* parseSourceText(std::string sourceText) noexcept
{
    return DelphiSyntaxTree::parseSourceText(std::move(sourceText));
}

} // end namespace Delphi
} // end namespace polyglot::CodeAnalysis
