#include "polyglot/CodeAnalysis/Delphi/Directive.hpp"

namespace polyglot::CodeAnalysis
{

Directive::Directive(DelphiDirectiveTriviaSyntaxPtr node) noexcept
    : _node{std::move(node)}
{}

} // end namespace polyglot::CodeAnalysis
