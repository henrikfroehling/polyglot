#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"
#include "Delphi/Syntax/DelphiEndOfModuleExpressionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitHeadSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiUnitFinalizationSectionSyntax;
class DelphiUnitImplementationSectionSyntax;
class DelphiUnitInitializationSectionSyntax;
class DelphiUnitInterfaceSectionSyntax;

class DelphiUnitModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiUnitModuleSyntax(DelphiUnitHeadSyntax* head,
                                    DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                    DelphiUnitImplementationSectionSyntax* implementationSection,
                                    DelphiEndOfModuleExpressionSyntax* endOfModule,
                                    Core::Syntax::ISyntaxToken* EOFToken,
                                    DelphiUnitInitializationSectionSyntax* initializationSection = nullptr,
                                    DelphiUnitFinalizationSectionSyntax* finalizationSection = nullptr) noexcept;

    virtual ~DelphiUnitModuleSyntax() noexcept {}
    inline bool isUnitModule() const noexcept override { return true; }
    inline DelphiUnitHeadSyntax* head() const noexcept { return _pHead; }
    inline DelphiUnitInterfaceSectionSyntax* interfaceSection() const noexcept { return _pInterfaceSection; }
    inline DelphiUnitImplementationSectionSyntax* implementationSection() const noexcept { return _pImplementationSection; }
    inline DelphiUnitInitializationSectionSyntax* initializationSection() const noexcept { return _pInitializationSection; }
    inline DelphiUnitFinalizationSectionSyntax* finalizationSection() const noexcept { return _pFinalizationSection; }
    inline bool hasInitializationSection() const noexcept { return _pInitializationSection != nullptr; }
    inline bool hasFinalizationSection() const noexcept { return _pFinalizationSection != nullptr; }
    inline DelphiEndOfModuleExpressionSyntax* endOfModule() const noexcept { return _pEndOfModule; }
    pg_size childCount() const noexcept override final;
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;
    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pHead); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pEndOfModule); }

    virtual pg_string toString() const noexcept override;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiUnitModuleSyntax"; }

    static DelphiUnitModuleSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                          DelphiUnitHeadSyntax* head,
                                          DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                          DelphiUnitImplementationSectionSyntax* implementationSection,
                                          DelphiEndOfModuleExpressionSyntax* endOfModule,
                                          Core::Syntax::ISyntaxToken* EOFToken,
                                          DelphiUnitInitializationSectionSyntax* initializationSection = nullptr,
                                          DelphiUnitFinalizationSectionSyntax* finalizationSection = nullptr) noexcept;

private:
    DelphiUnitHeadSyntax* _pHead;
    DelphiUnitInterfaceSectionSyntax* _pInterfaceSection;
    DelphiUnitImplementationSectionSyntax* _pImplementationSection;
    DelphiUnitInitializationSectionSyntax* _pInitializationSection; // optional
    DelphiUnitFinalizationSectionSyntax* _pFinalizationSection; // optional
    DelphiEndOfModuleExpressionSyntax* _pEndOfModule;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIUNITMODULESYNTAX_H
