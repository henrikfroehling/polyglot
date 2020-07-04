#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H

#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis {

class POLYGLOT_API DelphiParser final : public Parser
{
public:
    DelphiParser() = delete;
    explicit DelphiParser(std::string_view code) noexcept;
    void parse() noexcept override;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
