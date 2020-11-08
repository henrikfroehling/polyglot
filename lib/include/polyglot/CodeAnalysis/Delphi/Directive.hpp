#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DIRECTIVE_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DIRECTIVE_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API Directive
{
public:
    explicit Directive(DelphiDirectiveTriviaSyntaxPtr node) noexcept;
    virtual ~Directive() noexcept = default;
    inline SyntaxKind syntaxKind() const noexcept { return _node->syntaxKind(); }
    bool isActive() const noexcept;
    bool isBranchTaken() const noexcept;

private:
    DelphiDirectiveTriviaSyntaxPtr _node;
};

using DirectivePtr = std::shared_ptr<Directive>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DIRECTIVE_H
