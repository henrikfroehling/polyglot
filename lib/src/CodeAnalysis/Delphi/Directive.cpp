#include "polyglot/CodeAnalysis/Delphi/Directive.hpp"

namespace polyglot::CodeAnalysis
{

Directive::Directive(DelphiDirectiveTriviaSyntaxPtr node) noexcept
    : _node{std::move(node)}
{}

bool Directive::isActive() const noexcept
{
    return false; // TODO
}

bool Directive::isBranchTaken() const noexcept
{
    return false; // TODO
}

} // end namespace polyglot::CodeAnalysis
