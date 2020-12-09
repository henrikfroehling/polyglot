#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H

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
    inline DelphiUnitHeadingSyntax* heading() const noexcept { return _ptrHeading; }
    inline DelphiUnitInterfaceSectionSyntax* interfaceSection() const noexcept { return _ptrInterfaceSection; }
    inline DelphiUnitImplementationSectionSyntax* implementationSection() const noexcept { return _ptrImplementationSection; }
    inline DelphiUnitInitializationSectionSyntax* initializationSection() const noexcept { return _ptrInitializationSection; }
    inline void setInitializationSection(DelphiUnitInitializationSectionSyntax* initializationSection) noexcept { _ptrInitializationSection = initializationSection; }
    inline DelphiUnitFinalizationSectionSyntax* finalizationSection() const noexcept { return _ptrFinalizationSection; }
    inline void setFinalizationSection(DelphiUnitFinalizationSectionSyntax* finalizationSection) noexcept { _ptrFinalizationSection = finalizationSection; }
    inline bool hasInitializationSection() const noexcept { return _ptrInitializationSection != nullptr; }
    inline bool hasFinalizationSection() const noexcept { return _ptrFinalizationSection != nullptr; }
    inline SyntaxToken* endKeyword() const noexcept { return _ptrEndKeyword; }
    inline SyntaxToken* dotToken() const noexcept { return _ptrDotToken; }

private:
    DelphiUnitHeadingSyntax* _ptrHeading;
    DelphiUnitInterfaceSectionSyntax* _ptrInterfaceSection;
    DelphiUnitImplementationSectionSyntax* _ptrImplementationSection;
    DelphiUnitInitializationSectionSyntax* _ptrInitializationSection; // optional
    DelphiUnitFinalizationSectionSyntax* _ptrFinalizationSection; // optional
    SyntaxToken* _ptrEndKeyword;
    SyntaxToken* _ptrDotToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
