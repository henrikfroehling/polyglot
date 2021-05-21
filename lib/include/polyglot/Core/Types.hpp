#ifndef POLYGLOT_CORE_TYPES_H
#define POLYGLOT_CORE_TYPES_H

#include <cstddef>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>

using pg_size = std::size_t;

using pg_char = wchar_t;
using pg_string = std::wstring;
using pg_string_view = std::wstring_view;
using pg_ostream = std::wostream;
using pg_stringstream = std::wstringstream;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T>
using SharedPtr = std::shared_ptr<T>;

#endif // POLYGLOT_CORE_TYPES_H
