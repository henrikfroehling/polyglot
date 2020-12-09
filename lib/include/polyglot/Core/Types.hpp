#ifndef POLYGLOT_CORE_TYPES_H
#define POLYGLOT_CORE_TYPES_H

#include <cstddef>
#include <memory>

using pg_size = std::size_t;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T>
using SharedPtr = std::shared_ptr<T>;

#endif // POLYGLOT_CORE_TYPES_H
