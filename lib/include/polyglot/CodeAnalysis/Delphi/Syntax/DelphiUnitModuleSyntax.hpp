#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
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
                                    DelphiUnitImplementationSectionSyntaxPtr implementationSection,
                                    SyntaxTokenPtr endKeyword,
                                    SyntaxTokenPtr dotToken) noexcept;

    virtual ~DelphiUnitModuleSyntax() noexcept = default;
    inline bool isUnitModule() const noexcept override { return true; }
    inline const DelphiUnitHeadingSyntaxPtr& heading() const noexcept { return _ptrHeading; }
    inline const DelphiUnitInterfaceSectionSyntaxPtr& interfaceSection() const noexcept { return _ptrInterfaceSection; }
    inline const DelphiUnitImplementationSectionSyntaxPtr& implementationSection() const noexcept { return _ptrImplementationSection; }
    inline const DelphiUnitInitializationSectionSyntaxPtr& initializationSection() const noexcept { return _ptrInitializationSection; }
    inline void setInitializationSection(DelphiUnitInitializationSectionSyntaxPtr initializationSection) noexcept { _ptrInitializationSection = std::move(initializationSection); }
    inline const DelphiUnitFinalizationSectionSyntaxPtr& finalizationSection() const noexcept { return _ptrFinalizationSection; }
    inline void setFinalizationSection(DelphiUnitFinalizationSectionSyntaxPtr finalizationSection) noexcept { _ptrFinalizationSection = std::move(finalizationSection); }
    inline bool hasInitializationSection() const noexcept { return _ptrInitializationSection != nullptr; }
    inline bool hasFinalizationSection() const noexcept { return _ptrFinalizationSection != nullptr; }
    inline const SyntaxTokenPtr& endKeyword() const noexcept { return _ptrEndKeyword; }
    inline const SyntaxTokenPtr& dotToken() const noexcept { return _ptrDotToken; }

private:
    DelphiUnitHeadingSyntaxPtr _ptrHeading;
    DelphiUnitInterfaceSectionSyntaxPtr _ptrInterfaceSection;
    DelphiUnitImplementationSectionSyntaxPtr _ptrImplementationSection;
    DelphiUnitInitializationSectionSyntaxPtr _ptrInitializationSection; // optional
    DelphiUnitFinalizationSectionSyntaxPtr _ptrFinalizationSection; // optional
    SyntaxTokenPtr _ptrEndKeyword;
    SyntaxTokenPtr _ptrDotToken;
};

using DelphiUnitModuleSyntaxPtr = std::shared_ptr<DelphiUnitModuleSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
