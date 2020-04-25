#ifndef POLYGLOT_CODEANALYSIS_CODEANALYSIS_H
#define POLYGLOT_CODEANALYSIS_CODEANALYSIS_H

#include <string>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{
namespace Delphi
{

SyntaxTree* parseSourceText(std::string sourceText) noexcept;

} // end namespace Delphi
} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CODEANALYSIS_H
