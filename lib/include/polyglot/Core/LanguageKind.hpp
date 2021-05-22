#ifndef POLYGLOT_CORE_LANGUAGEKIND_H
#define POLYGLOT_CORE_LANGUAGEKIND_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core
{

enum class LanguageKind : unsigned short
{
    Unknown,
    Delphi
};

pg_string POLYGLOT_API languageKindName(LanguageKind languageKind) noexcept;

} // end namespace polyglot::Core

#endif // POLYGLOT_CORE_LANGUAGEKIND_H
