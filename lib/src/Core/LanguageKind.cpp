#include "polyglot/Core/LanguageKind.hpp"

namespace polyglot::Core
{

pg_string POLYGLOT_API languageKindName(LanguageKind languageKind) noexcept
{
    switch (languageKind)
    {
        case LanguageKind::Unknown: return L"Unknown";
        case LanguageKind::Delphi: return L"Delphi";
    }

    return L"";
}

} // end namespace polyglot::Core
