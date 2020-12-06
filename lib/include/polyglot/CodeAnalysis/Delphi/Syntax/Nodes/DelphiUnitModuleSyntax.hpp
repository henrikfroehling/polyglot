#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiUnitModuleSyntax(Ptr<DelphiUnitHeadingSyntax> heading,
                                    Ptr<DelphiUnitInterfaceSectionSyntax> interfaceSection,
                                    Ptr<DelphiUnitImplementationSectionSyntax> implementationSection,
                                    Ptr<SyntaxToken> endKeyword,
                                    Ptr<SyntaxToken> dotToken) noexcept;

    virtual ~DelphiUnitModuleSyntax() noexcept = default;
    inline bool isUnitModule() const noexcept override { return true; }
    inline const Ptr<DelphiUnitHeadingSyntax> heading() const noexcept { return _ptrHeading; }
    inline const Ptr<DelphiUnitInterfaceSectionSyntax> interfaceSection() const noexcept { return _ptrInterfaceSection; }
    inline const Ptr<DelphiUnitImplementationSectionSyntax> implementationSection() const noexcept { return _ptrImplementationSection; }
    inline const Ptr<DelphiUnitInitializationSectionSyntax> initializationSection() const noexcept { return _ptrInitializationSection; }
    inline void setInitializationSection(Ptr<DelphiUnitInitializationSectionSyntax> initializationSection) noexcept { _ptrInitializationSection = initializationSection; }
    inline const Ptr<DelphiUnitFinalizationSectionSyntax> finalizationSection() const noexcept { return _ptrFinalizationSection; }
    inline void setFinalizationSection(Ptr<DelphiUnitFinalizationSectionSyntax> finalizationSection) noexcept { _ptrFinalizationSection = finalizationSection; }
    inline bool hasInitializationSection() const noexcept { return _ptrInitializationSection != nullptr; }
    inline bool hasFinalizationSection() const noexcept { return _ptrFinalizationSection != nullptr; }
    inline const Ptr<SyntaxToken> endKeyword() const noexcept { return _ptrEndKeyword; }
    inline const Ptr<SyntaxToken> dotToken() const noexcept { return _ptrDotToken; }

private:
    Ptr<DelphiUnitHeadingSyntax> _ptrHeading;
    Ptr<DelphiUnitInterfaceSectionSyntax> _ptrInterfaceSection;
    Ptr<DelphiUnitImplementationSectionSyntax> _ptrImplementationSection;
    Ptr<DelphiUnitInitializationSectionSyntax> _ptrInitializationSection; // optional
    Ptr<DelphiUnitFinalizationSectionSyntax> _ptrFinalizationSection; // optional
    Ptr<SyntaxToken> _ptrEndKeyword;
    Ptr<SyntaxToken> _ptrDotToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
