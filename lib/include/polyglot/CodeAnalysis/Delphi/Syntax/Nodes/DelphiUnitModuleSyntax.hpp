#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITMODULESYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiUnitFinalizationSectionSyntax;
class DelphiUnitHeadingSyntax;
class DelphiUnitImplementationSectionSyntax;
class DelphiUnitInitializationSectionSyntax;
class DelphiUnitInterfaceSectionSyntax;
class SyntaxToken;

class POLYGLOT_API DelphiUnitModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiUnitModuleSyntax(DelphiUnitHeadingSyntax* heading,
                                    DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                    DelphiUnitImplementationSectionSyntax* implementationSection,
                                    SyntaxToken* endKeyword,
                                    SyntaxToken* dotToken) noexcept;

    virtual ~DelphiUnitModuleSyntax() noexcept = default;
    inline bool isUnitModule() const noexcept override { return true; }
    inline DelphiUnitHeadingSyntax* heading() const noexcept { return _pHeading; }
    inline DelphiUnitInterfaceSectionSyntax* interfaceSection() const noexcept { return _pInterfaceSection; }
    inline DelphiUnitImplementationSectionSyntax* implementationSection() const noexcept { return _pImplementationSection; }
    inline DelphiUnitInitializationSectionSyntax* initializationSection() const noexcept { return _pInitializationSection; }
    inline void setInitializationSection(DelphiUnitInitializationSectionSyntax* initializationSection) noexcept { _pInitializationSection = initializationSection; }
    inline DelphiUnitFinalizationSectionSyntax* finalizationSection() const noexcept { return _pFinalizationSection; }
    inline void setFinalizationSection(DelphiUnitFinalizationSectionSyntax* finalizationSection) noexcept { _pFinalizationSection = finalizationSection; }
    inline bool hasInitializationSection() const noexcept { return _pInitializationSection != nullptr; }
    inline bool hasFinalizationSection() const noexcept { return _pFinalizationSection != nullptr; }
    inline SyntaxToken* endKeyword() const noexcept { return _pEndKeyword; }
    inline SyntaxToken* dotToken() const noexcept { return _pDotToken; }

private:
    DelphiUnitHeadingSyntax* _pHeading;
    DelphiUnitInterfaceSectionSyntax* _pInterfaceSection;
    DelphiUnitImplementationSectionSyntax* _pImplementationSection;
    DelphiUnitInitializationSectionSyntax* _pInitializationSection; // optional
    DelphiUnitFinalizationSectionSyntax* _pFinalizationSection; // optional
    SyntaxToken* _pEndKeyword;
    SyntaxToken* _pDotToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITMODULESYNTAX_H
