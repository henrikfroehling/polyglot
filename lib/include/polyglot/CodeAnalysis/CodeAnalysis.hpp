#ifndef POLYGLOT_CODEANALYSIS_CODEANALYSIS_H
#define POLYGLOT_CODEANALYSIS_CODEANALYSIS_H

#include <string>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTree.hpp"

namespace polyglot::CodeAnalysis
{
namespace Delphi
{

SharedPtr<ISyntaxTree> POLYGLOT_API parseSourceText(std::string filename,
                                                    std::string source) noexcept;

} // end namespace Delphi
} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CODEANALYSIS_H
