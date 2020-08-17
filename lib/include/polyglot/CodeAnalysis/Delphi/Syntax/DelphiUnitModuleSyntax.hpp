#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitInitializationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiUnitModuleSyntax(DelphiUnitHeadingSyntaxPtr heading,
                                    DelphiUnitInterfaceSectionSyntaxPtr interfaceSection,
                                    DelphiUnitImplementationSectionSyntaxPtr implementationSection) noexcept;

    virtual ~DelphiUnitModuleSyntax() noexcept = default;
    inline bool isUnitModule() const noexcept override { return true; }
    inline const DelphiUnitHeadingSyntaxPtr& heading() const noexcept { return _ptrHeading; }
    inline void setHeading(DelphiUnitHeadingSyntaxPtr heading) noexcept { _ptrHeading = heading; }
    inline const DelphiUnitInterfaceSectionSyntaxPtr& interfaceSection() const noexcept { return _ptrInterfaceSection; }
    inline void setInterfaceSection(DelphiUnitInterfaceSectionSyntaxPtr interfaceSection) noexcept { _ptrInterfaceSection = interfaceSection; }
    inline const DelphiUnitImplementationSectionSyntaxPtr& implementationSection() const noexcept { return _ptrImplementationSection; }
    inline void setImplementationSection(DelphiUnitImplementationSectionSyntaxPtr implementationSection) noexcept { _ptrImplementationSection = implementationSection; }
    inline const DelphiUnitInitializationSectionSyntaxPtr& initializationSection() const noexcept { return _ptrInitializationSection; }
    inline void setInitializationSection(DelphiUnitInitializationSectionSyntaxPtr initializationSection) noexcept { _ptrInitializationSection = initializationSection; }
    inline const DelphiUnitFinalizationSectionSyntaxPtr& finalizationSection() const noexcept { return _ptrFinalizationSection; }
    inline void setFinalizationSection(DelphiUnitFinalizationSectionSyntaxPtr finalizationSection) noexcept { _ptrFinalizationSection = finalizationSection; }
    inline bool hasInitializationSection() const noexcept { return _ptrInitializationSection != nullptr; }
    inline bool hasFinalizationSection() const noexcept { return _ptrFinalizationSection != nullptr; }

private:
    DelphiUnitHeadingSyntaxPtr _ptrHeading;
    DelphiUnitInterfaceSectionSyntaxPtr _ptrInterfaceSection;
    DelphiUnitImplementationSectionSyntaxPtr _ptrImplementationSection;
    DelphiUnitInitializationSectionSyntaxPtr _ptrInitializationSection;
    DelphiUnitFinalizationSectionSyntaxPtr _ptrFinalizationSection;
};

using DelphiUnitModuleSyntaxPtr = std::shared_ptr<DelphiUnitModuleSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
