#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H

#include <string>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis {

class POLYGLOT_API DelphiParser final : public Parser
{
public:
    DelphiParser() = delete;
    explicit DelphiParser(std::string code) noexcept;
    void parse() noexcept override;
    inline pg_size tokenCount() const noexcept { return _tokens.size(); }
    inline double lexingDuration() const noexcept { return _lexingDuration; }

private:
    double _lexingDuration;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
