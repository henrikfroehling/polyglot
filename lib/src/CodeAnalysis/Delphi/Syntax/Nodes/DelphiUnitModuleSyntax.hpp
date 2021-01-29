#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITMODULESYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiUnitFinalizationSectionSyntax;
class DelphiUnitHeadingSyntax;
class DelphiUnitImplementationSectionSyntax;
class DelphiUnitInitializationSectionSyntax;
class DelphiUnitInterfaceSectionSyntax;
class LanguageSyntaxToken;

class DelphiUnitModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiUnitModuleSyntax(DelphiUnitHeadingSyntax* heading,
                                    DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                    DelphiUnitImplementationSectionSyntax* implementationSection,
                                    LanguageSyntaxToken* endKeyword,
                                    LanguageSyntaxToken* dotToken,
                                    LanguageSyntaxToken* EOFToken,
                                    DelphiUnitInitializationSectionSyntax* initializationSection = nullptr,
                                    DelphiUnitFinalizationSectionSyntax* finalizationSection = nullptr) noexcept;

    virtual ~DelphiUnitModuleSyntax() noexcept = default;
    inline bool isUnitModule() const noexcept override { return true; }
    inline DelphiUnitHeadingSyntax* heading() const noexcept { return _pHeading; }
    inline DelphiUnitInterfaceSectionSyntax* interfaceSection() const noexcept { return _pInterfaceSection; }
    inline DelphiUnitImplementationSectionSyntax* implementationSection() const noexcept { return _pImplementationSection; }
    inline DelphiUnitInitializationSectionSyntax* initializationSection() const noexcept { return _pInitializationSection; }
    inline DelphiUnitFinalizationSectionSyntax* finalizationSection() const noexcept { return _pFinalizationSection; }
    inline bool hasInitializationSection() const noexcept { return _pInitializationSection != nullptr; }
    inline bool hasFinalizationSection() const noexcept { return _pFinalizationSection != nullptr; }
    inline LanguageSyntaxToken* endKeyword() const noexcept { return _pEndKeyword; }
    inline LanguageSyntaxToken* dotToken() const noexcept { return _pDotToken; }

    static DelphiUnitModuleSyntax* create(DelphiUnitHeadingSyntax* heading,
                                          DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                          DelphiUnitImplementationSectionSyntax* implementationSection,
                                          LanguageSyntaxToken* endKeyword,
                                          LanguageSyntaxToken* dotToken,
                                          LanguageSyntaxToken* EOFToken,
                                          DelphiUnitInitializationSectionSyntax* initializationSection = nullptr,
                                          DelphiUnitFinalizationSectionSyntax* finalizationSection = nullptr) noexcept;

private:
    DelphiUnitHeadingSyntax* _pHeading;
    DelphiUnitInterfaceSectionSyntax* _pInterfaceSection;
    DelphiUnitImplementationSectionSyntax* _pImplementationSection;
    DelphiUnitInitializationSectionSyntax* _pInitializationSection; // optional
    DelphiUnitFinalizationSectionSyntax* _pFinalizationSection; // optional
    LanguageSyntaxToken* _pEndKeyword;
    LanguageSyntaxToken* _pDotToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITMODULESYNTAX_H
