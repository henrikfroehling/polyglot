#include "polyglot/Core/LanguageKind.hpp"

namespace polyglot::Core
{

std::string POLYGLOT_API languageKindName(LanguageKind languageKind) noexcept
{
    switch (languageKind)
    {
        case LanguageKind::Unknown: return "Unknown";
        case LanguageKind::Delphi: return "Delphi";
    }

    return "";
}

} // end namespace polyglot::Core
