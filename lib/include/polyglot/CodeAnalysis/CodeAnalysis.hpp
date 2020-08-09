#ifndef POLYGLOT_CODEANALYSIS_CODEANALYSIS_H
#define POLYGLOT_CODEANALYSIS_CODEANALYSIS_H

#include <memory>
#include <string>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{
namespace Delphi
{

std::shared_ptr<SyntaxTree> parseSourceText(std::string source) noexcept;

} // end namespace Delphi
} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CODEANALYSIS_H
