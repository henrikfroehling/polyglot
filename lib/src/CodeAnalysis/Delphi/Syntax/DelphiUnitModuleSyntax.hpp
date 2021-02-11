#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiEndOfModuleSyntax;
class DelphiUnitFinalizationSectionSyntax;
class DelphiUnitHeadSyntax;
class DelphiUnitImplementationSectionSyntax;
class DelphiUnitInitializationSectionSyntax;
class DelphiUnitInterfaceSectionSyntax;
class LanguageSyntaxToken;
class SyntaxFactory;

class DelphiUnitModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiUnitModuleSyntax(DelphiUnitHeadSyntax* head,
                                    DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                    DelphiUnitImplementationSectionSyntax* implementationSection,
                                    DelphiEndOfModuleSyntax* endOfModule,
                                    LanguageSyntaxToken* EOFToken,
                                    DelphiUnitInitializationSectionSyntax* initializationSection = nullptr,
                                    DelphiUnitFinalizationSectionSyntax* finalizationSection = nullptr) noexcept;

    virtual ~DelphiUnitModuleSyntax() noexcept = default;
    inline bool isUnitModule() const noexcept override { return true; }
    inline DelphiUnitHeadSyntax* head() const noexcept { return _pHead; }
    inline DelphiUnitInterfaceSectionSyntax* interfaceSection() const noexcept { return _pInterfaceSection; }
    inline DelphiUnitImplementationSectionSyntax* implementationSection() const noexcept { return _pImplementationSection; }
    inline DelphiUnitInitializationSectionSyntax* initializationSection() const noexcept { return _pInitializationSection; }
    inline DelphiUnitFinalizationSectionSyntax* finalizationSection() const noexcept { return _pFinalizationSection; }
    inline bool hasInitializationSection() const noexcept { return _pInitializationSection != nullptr; }
    inline bool hasFinalizationSection() const noexcept { return _pFinalizationSection != nullptr; }
    inline DelphiEndOfModuleSyntax* endOfModule() const noexcept { return _pEndOfModule; }

    static DelphiUnitModuleSyntax* create(SyntaxFactory& syntaxFactory,
                                          DelphiUnitHeadSyntax* head,
                                          DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                          DelphiUnitImplementationSectionSyntax* implementationSection,
                                          DelphiEndOfModuleSyntax* endOfModule,
                                          LanguageSyntaxToken* EOFToken,
                                          DelphiUnitInitializationSectionSyntax* initializationSection = nullptr,
                                          DelphiUnitFinalizationSectionSyntax* finalizationSection = nullptr) noexcept;

private:
    DelphiUnitHeadSyntax* _pHead;
    DelphiUnitInterfaceSectionSyntax* _pInterfaceSection;
    DelphiUnitImplementationSectionSyntax* _pImplementationSection;
    DelphiUnitInitializationSectionSyntax* _pInitializationSection; // optional
    DelphiUnitFinalizationSectionSyntax* _pFinalizationSection; // optional
    DelphiEndOfModuleSyntax* _pEndOfModule;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
