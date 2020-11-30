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
    explicit DelphiUnitModuleSyntax(SharedPtr<DelphiUnitHeadingSyntax> heading,
                                    SharedPtr<DelphiUnitInterfaceSectionSyntax> interfaceSection,
                                    SharedPtr<DelphiUnitImplementationSectionSyntax> implementationSection,
                                    SharedPtr<SyntaxToken> endKeyword,
                                    SharedPtr<SyntaxToken> dotToken) noexcept;

    virtual ~DelphiUnitModuleSyntax() noexcept = default;
    inline bool isUnitModule() const noexcept override { return true; }
    inline const SharedPtr<DelphiUnitHeadingSyntax>& heading() const noexcept { return _ptrHeading; }
    inline const SharedPtr<DelphiUnitInterfaceSectionSyntax>& interfaceSection() const noexcept { return _ptrInterfaceSection; }
    inline const SharedPtr<DelphiUnitImplementationSectionSyntax>& implementationSection() const noexcept { return _ptrImplementationSection; }
    inline const SharedPtr<DelphiUnitInitializationSectionSyntax>& initializationSection() const noexcept { return _ptrInitializationSection; }
    inline void setInitializationSection(SharedPtr<DelphiUnitInitializationSectionSyntax> initializationSection) noexcept { _ptrInitializationSection = std::move(initializationSection); }
    inline const SharedPtr<DelphiUnitFinalizationSectionSyntax>& finalizationSection() const noexcept { return _ptrFinalizationSection; }
    inline void setFinalizationSection(SharedPtr<DelphiUnitFinalizationSectionSyntax> finalizationSection) noexcept { _ptrFinalizationSection = std::move(finalizationSection); }
    inline bool hasInitializationSection() const noexcept { return _ptrInitializationSection != nullptr; }
    inline bool hasFinalizationSection() const noexcept { return _ptrFinalizationSection != nullptr; }
    inline const SharedPtr<SyntaxToken>& endKeyword() const noexcept { return _ptrEndKeyword; }
    inline const SharedPtr<SyntaxToken>& dotToken() const noexcept { return _ptrDotToken; }

private:
    SharedPtr<DelphiUnitHeadingSyntax> _ptrHeading;
    SharedPtr<DelphiUnitInterfaceSectionSyntax> _ptrInterfaceSection;
    SharedPtr<DelphiUnitImplementationSectionSyntax> _ptrImplementationSection;
    SharedPtr<DelphiUnitInitializationSectionSyntax> _ptrInitializationSection; // optional
    SharedPtr<DelphiUnitFinalizationSectionSyntax> _ptrFinalizationSection; // optional
    SharedPtr<SyntaxToken> _ptrEndKeyword;
    SharedPtr<SyntaxToken> _ptrDotToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
