#ifndef POLYGLOT_CODEANALYSIS_CORE_LEXERBENCHMARK_H
#define POLYGLOT_CODEANALYSIS_CORE_LEXERBENCHMARK_H

#include <ostream>
#include <string>
#include <unordered_map>
#include "polyglot/polyglot_global.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API LexerBenchmark final
{
public:
    LexerBenchmark() noexcept;
    LexerBenchmark(const LexerBenchmark&) noexcept = default;
    LexerBenchmark(LexerBenchmark&&) noexcept = default;
    LexerBenchmark& operator=(const LexerBenchmark&) noexcept = default;
    LexerBenchmark& operator=(LexerBenchmark&&) noexcept = default;
    inline const std::string& filename() const noexcept { return _filename; }
    inline void setFilename(std::string filename) noexcept { _filename = std::move(filename); }
    inline double duration() const noexcept { return _duration; }
    inline void setDuration(double duration) noexcept { _duration = duration; }
    inline int tokenCount() const noexcept { return _tokenCount; }
    inline void setTokenCount(int tokenCount) noexcept { _tokenCount = tokenCount; }
    inline void incrementTokenCount() noexcept { _tokenCount++; }
    inline int cacheMisses() const noexcept { return _cacheMisses; }
    inline void setCacheMisses(int cacheMisses) noexcept { _cacheMisses = cacheMisses; }
    inline void incrementCacheMisses() noexcept { _cacheMisses++; }
    inline int cacheHits() const noexcept { return _cacheHits; }
    inline void setCacheHits(int cacheHits) noexcept { _cacheHits = cacheHits; }
    inline void incrementCacheHits() noexcept { _cacheHits++; }

    friend std::ostream& operator<<(std::ostream& os,
                                    const LexerBenchmark& benchmark) noexcept;

private:
    std::string _filename;
    double _duration;
    int _tokenCount;
    int _cacheMisses;
    int _cacheHits;
};

class POLYGLOT_API LexerBenchmarks final
{
public:
    LexerBenchmarks() noexcept = default;
    LexerBenchmarks(const LexerBenchmarks&) noexcept = default;
    LexerBenchmarks(LexerBenchmarks&&) noexcept = default;
    LexerBenchmarks& operator=(const LexerBenchmarks&) noexcept = default;
    LexerBenchmarks& operator=(LexerBenchmarks&&) noexcept = default;

    inline void addBenchmark(const std::string& name,
                             LexerBenchmark benchmark) noexcept
    {
        _benchmarks[name] = std::move(benchmark);
    }

    inline LexerBenchmark benchmark(const std::string& name) noexcept
    {
        if (_benchmarks.find(name) == std::cend(_benchmarks))
            return LexerBenchmark{};

        return _benchmarks[name];
    }

private:
    std::unordered_map<std::string, LexerBenchmark> _benchmarks;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXERBENCHMARK_H
