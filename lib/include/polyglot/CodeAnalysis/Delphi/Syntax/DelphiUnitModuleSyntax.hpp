#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitInitializationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiUnitModuleSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiUnitModuleSyntax() noexcept = default;
    inline bool isUnitModule() const noexcept override { return true; }
    inline const std::shared_ptr<DelphiUnitInterfaceSectionSyntax>& interfaceSection() const noexcept { return _ptrInterfaceSection; }
    inline void setInterfaceSection(std::shared_ptr<DelphiUnitInterfaceSectionSyntax> interfaceSection) noexcept { _ptrInterfaceSection = interfaceSection; }
    inline const std::shared_ptr<DelphiUnitImplementationSectionSyntax>& implementationSection() const noexcept { return _ptrImplementationSection; }
    inline void setImplementationSection(std::shared_ptr<DelphiUnitImplementationSectionSyntax> implementationSection) noexcept { _ptrImplementationSection = implementationSection; }
    inline const std::shared_ptr<DelphiUnitInitializationSectionSyntax>& initializationSection() const noexcept { return _ptrInitializationSection; }
    inline void setInitializationSection(std::shared_ptr<DelphiUnitInitializationSectionSyntax> initializationSection) noexcept { _ptrInitializationSection = initializationSection; }
    inline const std::shared_ptr<DelphiUnitFinalizationSectionSyntax>& finalizationSection() const noexcept { return _ptrFinalizationSection; }
    inline void setFinalizationSection(std::shared_ptr<DelphiUnitFinalizationSectionSyntax> finalizationSection) noexcept { _ptrFinalizationSection = finalizationSection; }
    inline bool hasInitializationSection() const noexcept { return _ptrInitializationSection != nullptr; }
    inline bool hasFinalizationSection() const noexcept { return _ptrFinalizationSection != nullptr; }

private:
    std::shared_ptr<DelphiUnitInterfaceSectionSyntax> _ptrInterfaceSection;
    std::shared_ptr<DelphiUnitImplementationSectionSyntax> _ptrImplementationSection;
    std::shared_ptr<DelphiUnitInitializationSectionSyntax> _ptrInitializationSection;
    std::shared_ptr<DelphiUnitFinalizationSectionSyntax> _ptrFinalizationSection;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
