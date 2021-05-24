#include "Delphi/Parser/DelphiSyntaxFacts.hpp"
#include <algorithm>
#include <unordered_map>

namespace polyglot::Delphi::Parser
{

using polyglot::Core::Syntax::SyntaxKind;

static const std::unordered_map<pg_string, SyntaxKind> SYNTAXKEYWORDS =
{
    { L"and", SyntaxKind::AndKeyword },
    { L"array", SyntaxKind::ArrayKeyword },
    { L"as", SyntaxKind::AsKeyword },
    { L"asm", SyntaxKind::AsmKeyword },
    { L"begin", SyntaxKind::BeginKeyword },
    { L"case", SyntaxKind::CaseKeyword },
    { L"class", SyntaxKind::ClassKeyword },
    { L"const", SyntaxKind::ConstKeyword },
    { L"constructor", SyntaxKind::ConstructorKeyword },
    { L"destructor", SyntaxKind::DestructorKeyword },
    { L"dispinterface", SyntaxKind::DispInterfaceKeyword },
    { L"div", SyntaxKind::DivKeyword },
    { L"do", SyntaxKind::DoKeyword },
    { L"downto", SyntaxKind::DownToKeyword },
    { L"else", SyntaxKind::ElseKeyword },
    { L"end", SyntaxKind::EndKeyword },
    { L"except", SyntaxKind::ExceptKeyword },
    { L"exports", SyntaxKind::ExportsKeyword },
    { L"file", SyntaxKind::FileKeyword },
    { L"finalization", SyntaxKind::FinalizationKeyword },
    { L"finally", SyntaxKind::FinallyKeyword },
    { L"for", SyntaxKind::ForKeyword },
    { L"function", SyntaxKind::FunctionKeyword },
    { L"goto", SyntaxKind::GoToKeyword },
    { L"implementation", SyntaxKind::ImplementationKeyword },
    { L"in", SyntaxKind::InKeyword },
    { L"inherited", SyntaxKind::InheritedKeyword },
    { L"initialization", SyntaxKind::InitializationKeyword },
    { L"inline", SyntaxKind::InlineKeyword },
    { L"interface", SyntaxKind::InterfaceKeyword },
    { L"is", SyntaxKind::IsKeyword },
    { L"label", SyntaxKind::LabelKeyword },
    { L"library", SyntaxKind::LibraryKeyword },
    { L"mod", SyntaxKind::ModKeyword },
    { L"nil", SyntaxKind::NilKeyword },
    { L"not", SyntaxKind::NotKeyword },
    { L"object", SyntaxKind::ObjectKeyword },
    { L"of", SyntaxKind::OfKeyword },
    { L"or", SyntaxKind::OrKeyword },
    { L"packed", SyntaxKind::PackedKeyword },
    { L"procedure", SyntaxKind::ProcedureKeyword },
    { L"program", SyntaxKind::ProgramKeyword },
    { L"property", SyntaxKind::PropertyKeyword },
    { L"raise", SyntaxKind::RaiseKeyword },
    { L"record", SyntaxKind::RecordKeyword },
    { L"repeat", SyntaxKind::RepeatKeyword },
    { L"resourcestring", SyntaxKind::ResourceStringKeyword },
    { L"set", SyntaxKind::SetKeyword },
    { L"shl", SyntaxKind::ShiftLeftKeyword },
    { L"shr", SyntaxKind::ShiftRightKeyword },
    { L"string", SyntaxKind::StringKeyword },
    { L"then", SyntaxKind::ThenKeyword },
    { L"threadvar", SyntaxKind::ThreadVarKeyword },
    { L"to", SyntaxKind::ToKeyword },
    { L"try", SyntaxKind::TryKeyword },
    { L"type", SyntaxKind::TypeKeyword },
    { L"unit", SyntaxKind::UnitKeyword },
    { L"until", SyntaxKind::UntilKeyword },
    { L"uses", SyntaxKind::UsesKeyword },
    { L"var", SyntaxKind::VarKeyword },
    { L"while", SyntaxKind::WhileKeyword },
    { L"with", SyntaxKind::WithKeyword },
    { L"xor", SyntaxKind::XorKeyword },
    { L"absolute", SyntaxKind::AbsoluteKeyword },
    { L"abstract", SyntaxKind::AbstractKeyword },
    { L"assembler", SyntaxKind::AssemblerKeyword },
    { L"automated", SyntaxKind::AutomatedKeyword },
    { L"cdecl", SyntaxKind::CdeclKeyword },
    { L"contains", SyntaxKind::ContainsKeyword },
    { L"default", SyntaxKind::DefaultKeyword },
    { L"delayed", SyntaxKind::DelayedKeyword },
    { L"deprecated", SyntaxKind::DeprecatedKeyword },
    { L"dispid", SyntaxKind::DispIdKeyword },
    { L"dynamic", SyntaxKind::DynamicKeyword },
    { L"experimental", SyntaxKind::ExperimentalKeyword },
    { L"export", SyntaxKind::ExportKeyword },
    { L"external", SyntaxKind::ExternalKeyword },
    { L"far", SyntaxKind::FarKeyword },
    { L"final", SyntaxKind::FinalKeyword },
    { L"forward", SyntaxKind::ForwardKeyword },
    { L"helper", SyntaxKind::HelperKeyword },
    { L"if", SyntaxKind::IfKeyword },
    { L"implements", SyntaxKind::ImplementsKeyword },
    { L"index", SyntaxKind::IndexKeyword },
    { L"local", SyntaxKind::LocalKeyword },
    { L"message", SyntaxKind::MessageKeyword },
    { L"name", SyntaxKind::NameKeyword },
    { L"near", SyntaxKind::NearKeyword },
    { L"nodefault", SyntaxKind::NoDefaultKeyword },
    { L"operator", SyntaxKind::OperatorKeyword },
    { L"out", SyntaxKind::OutKeyword },
    { L"overload", SyntaxKind::OverloadKeyword },
    { L"override", SyntaxKind::OverrideKeyword },
    { L"package", SyntaxKind::PackageKeyword },
    { L"pascal", SyntaxKind::PascalKeyword },
    { L"platform", SyntaxKind::PlatformKeyword },
    { L"private", SyntaxKind::PrivateKeyword },
    { L"protected", SyntaxKind::ProtectedKeyword },
    { L"public", SyntaxKind::PublicKeyword },
    { L"published", SyntaxKind::PublishedKeyword },
    { L"read", SyntaxKind::ReadKeyword },
    { L"readonly", SyntaxKind::ReadOnlyKeyword },
    { L"reference", SyntaxKind::ReferenceKeyword },
    { L"register", SyntaxKind::RegisterKeyword },
    { L"reintroduce", SyntaxKind::ReintroduceKeyword },
    { L"requires", SyntaxKind::RequiresKeyword },
    { L"resident", SyntaxKind::ResidentKeyword },
    { L"safecall", SyntaxKind::SafeCallKeyword },
    { L"sealed", SyntaxKind::SealedKeyword },
    { L"static", SyntaxKind::StaticKeyword },
    { L"stdcall", SyntaxKind::StdCallKeyword },
    { L"strict", SyntaxKind::StrictKeyword },
    { L"stored", SyntaxKind::StoredKeyword },
    { L"unsafe", SyntaxKind::UnsafeKeyword },
    { L"varargs", SyntaxKind::VarArgsKeyword },
    { L"virtual", SyntaxKind::VirtualKeyword },
    { L"winapi", SyntaxKind::WinApiKeyword },
    { L"write", SyntaxKind::WriteKeyword },
    { L"writeonly", SyntaxKind::WriteOnlyKeyword },
    { L"byte", SyntaxKind::ByteKeyword },
    { L"shortint", SyntaxKind::ShortIntKeyword },
    { L"word", SyntaxKind::WordKeyword },
    { L"smallint", SyntaxKind::SmallIntKeyword },
    { L"cardinal", SyntaxKind::CardinalKeyword },
    { L"longword", SyntaxKind::LongWordKeyword },
    { L"fixeduint", SyntaxKind::FixedUIntKeyword },
    { L"integer", SyntaxKind::IntegerKeyword },
    { L"longint", SyntaxKind::LongIntKeyword },
    { L"fixedint", SyntaxKind::FixedIntKeyword },
    { L"uint64", SyntaxKind::UInt64Keyword },
    { L"int64", SyntaxKind::Int64Keyword },
    { L"nativeuint", SyntaxKind::NativeUIntKeyword },
    { L"nativeint", SyntaxKind::NativeIntKeyword },
    { L"pbyte", SyntaxKind::BytePointerKeyword },
    { L"pshortint", SyntaxKind::ShortIntPointerKeyword },
    { L"pword", SyntaxKind::WordPointerKeyword },
    { L"psmallint", SyntaxKind::SmallIntPointerKeyword },
    { L"pcardinal", SyntaxKind::CardinalPointerKeyword },
    { L"plongword", SyntaxKind::LongWordPointerKeyword },
    { L"pfixeduint", SyntaxKind::FixedUIntPointerKeyword },
    { L"pinteger", SyntaxKind::IntegerPointerKeyword },
    { L"plongint", SyntaxKind::LongIntPointerKeyword },
    { L"pfixedint", SyntaxKind::FixedIntPointerKeyword },
    { L"puint64", SyntaxKind::UInt64PointerKeyword },
    { L"pint64", SyntaxKind::Int64PointerKeyword },
    { L"pnativeuint", SyntaxKind::NativeUIntPointerKeyword },
    { L"pnativeint", SyntaxKind::NativeIntPointerKeyword },
    { L"single", SyntaxKind::SingleKeyword },
    { L"double", SyntaxKind::DoubleKeyword },
    { L"extended", SyntaxKind::ExtendedKeyword },
    { L"real", SyntaxKind::RealKeyword },
    { L"psingle", SyntaxKind::SinglePointerKeyword },
    { L"pdouble", SyntaxKind::DoublePointerKeyword },
    { L"pextended", SyntaxKind::ExtendedPointerKeyword },
    { L"ansichar", SyntaxKind::AnsiCharKeyword },
    { L"char", SyntaxKind::CharKeyword },
    { L"widechar", SyntaxKind::WideCharKeyword },
    { L"ansistring", SyntaxKind::AnsiStringKeyword },
    { L"rawbytestring", SyntaxKind::RawByteStringKeyword },
    { L"unicodestring", SyntaxKind::UnicodeStringKeyword },
    { L"shortstring", SyntaxKind::ShortStringKeyword },
    { L"widestring", SyntaxKind::WideStringKeyword },
    { L"pansichar", SyntaxKind::AnsiCharPointerKeyword },
    { L"pchar", SyntaxKind::CharPointerKeyword },
    { L"pwidechar", SyntaxKind::WideCharPointerKeyword },
    { L"pansistring", SyntaxKind::AnsiStringPointerKeyword },
    { L"prawbytestring", SyntaxKind::RawByteStringPointerKeyword },
    { L"punicodestring", SyntaxKind::UnicodeStringPointerKeyword },
    { L"pstring", SyntaxKind::StringPointerKeyword },
    { L"pshortstring", SyntaxKind::ShortStringPointerKeyword },
    { L"pwidestring", SyntaxKind::WideStringPointerKeyword },
    { L"boolean", SyntaxKind::BooleanKeyword },
    { L"bytebool", SyntaxKind::ByteBoolKeyword },
    { L"wordbool", SyntaxKind::WordBoolKeyword },
    { L"longbool", SyntaxKind::LongBoolKeyword },
    { L"pboolean", SyntaxKind::BooleanPointerKeyword },
    { L"pwordbool", SyntaxKind::WordBoolPointerKeyword },
    { L"plongbool", SyntaxKind::LongBoolPointerKeyword },
    { L"pointer", SyntaxKind::PointerKeyword },
    { L"variant", SyntaxKind::VariantKeyword },
    { L"currency", SyntaxKind::CurrencyKeyword },
    { L"ppointer", SyntaxKind::PointerPointerKeyword },
    { L"pvariant", SyntaxKind::VariantPointerKeyword },
    { L"pcurrency", SyntaxKind::CurrencyPointerKeyword },
    { L"real48", SyntaxKind::Real48Keyword },
    { L"utf8string", SyntaxKind::UTF8StringKeyword },
    { L"olevariant", SyntaxKind::OleVariantKeyword },
    { L"polevariant", SyntaxKind::OleVariantPointerKeyword },
    { L"add", SyntaxKind::AddKeyword },
    { L"remove", SyntaxKind::RemoveKeyword },
    { L"assembly", SyntaxKind::AssemblyKeyword },
    { L"break", SyntaxKind::BreakKeyword },
    { L"continue", SyntaxKind::ContinueKeyword },
    { L"endif", SyntaxKind::EndIfDirectiveKeyword },
    { L"ifdef", SyntaxKind::IfDefDirectiveKeyword },
    { L"ifndef", SyntaxKind::IfNDefDirectiveKeyword },
    { L"ifend", SyntaxKind::IfEndDirectiveKeyword },
    { L"elseif", SyntaxKind::ElseIfDirectiveKeyword },
    { L"define", SyntaxKind::DefineDirectiveKeyword },
    { L"undef", SyntaxKind::UndefDirectiveKeyword },
    { L"region", SyntaxKind::RegionDirectiveKeyword },
    { L"endregion", SyntaxKind::EndRegionDirectiveKeyword },
    { L"on", SyntaxKind::OnDirectiveKeyword },
    { L"off", SyntaxKind::OffDirectiveKeyword }
};

bool DelphiSyntaxFacts::isPunctuation(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        case SyntaxKind::DotToken:
        case SyntaxKind::CommaToken:
        case SyntaxKind::SemiColonToken:
        case SyntaxKind::ColonToken:
        case SyntaxKind::EqualToken:
        case SyntaxKind::CaretToken:
        case SyntaxKind::LessThanToken:
        case SyntaxKind::GreaterThanToken:
        case SyntaxKind::OpenParenthesisToken:
        case SyntaxKind::CloseParenthesisToken:
        case SyntaxKind::OpenBracketToken:
        case SyntaxKind::CloseBracketToken:
        case SyntaxKind::OpenBraceToken:
        case SyntaxKind::CloseBraceToken:
        case SyntaxKind::AtToken:
        case SyntaxKind::PlusToken:
        case SyntaxKind::MinusToken:
        case SyntaxKind::AsteriskToken:
        case SyntaxKind::SlashToken:
        case SyntaxKind::AmpersandToken:
        case SyntaxKind::DollarToken:
        case SyntaxKind::UnderscoreToken:
        case SyntaxKind::HashToken:
        case SyntaxKind::SingleQuoteToken:
        case SyntaxKind::DoubleQuoteToken:
            return true;
    }

    return false;
}

bool DelphiSyntaxFacts::isCompoundPunctuation(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        case SyntaxKind::DotDotToken:
        case SyntaxKind::CaretDotToken:
        case SyntaxKind::ColonEqualToken:
        case SyntaxKind::SlashSlashToken:
        case SyntaxKind::LessThanEqualToken:
        case SyntaxKind::GreaterThanEqualToken:
        case SyntaxKind::LessThanGreaterThanToken:
        case SyntaxKind::MinusMinusToken:
        case SyntaxKind::OpenParenthesisAsteriskToken:
        case SyntaxKind::AsteriskCloseParenthesisToken:
        case SyntaxKind::OpenParenthesisDotToken:
        case SyntaxKind::DotCloseParenthesisToken:
        case SyntaxKind::OpenBraceDollarToken:
        case SyntaxKind::OpenParenthesisDollarToken:
        case SyntaxKind::AtAtToken:
        return true;
    }

    return false;
}

SyntaxKind DelphiSyntaxFacts::binaryExpressionKind(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        case SyntaxKind::AndKeyword:
            return SyntaxKind::LogicalAndExpression;
        case SyntaxKind::OrKeyword:
            return SyntaxKind::LogicalOrExpression;
        case SyntaxKind::EqualToken:
            return SyntaxKind::EqualsExpression;
        case SyntaxKind::LessThanEqualToken:
        case SyntaxKind::GreaterThanEqualToken:
        case SyntaxKind::LessThanGreaterThanToken:
            return SyntaxKind::NotEqualsExpression;
    }

    return SyntaxKind::None;
}

SyntaxKind DelphiSyntaxFacts::literalExpressionKind(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        case SyntaxKind::DoubleQuotationStringLiteralToken:
        case SyntaxKind::SingleQuotationStringLiteralToken:
            return SyntaxKind::StringLiteralExpression;
        case SyntaxKind::NumberLiteralToken:
            return SyntaxKind::NumericLiteralExpression;
        case SyntaxKind::TrueKeyword:
            return SyntaxKind::TrueLiteralExpression;
        case SyntaxKind::FalseKeyword:
            return SyntaxKind::FalseLiteralExpression;
    }

    return SyntaxKind::None;
}

bool DelphiSyntaxFacts::isComparisonSyntaxKind(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        case SyntaxKind::EqualToken:
        case SyntaxKind::LessThanEqualToken:
        case SyntaxKind::GreaterThanEqualToken:
        case SyntaxKind::LessThanGreaterThanToken:
            return true;
    }

    return false;
}

bool DelphiSyntaxFacts::isKeyword(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        case SyntaxKind::AndKeyword:
        case SyntaxKind::ArrayKeyword:
        case SyntaxKind::AsKeyword:
        case SyntaxKind::AsmKeyword:
        case SyntaxKind::BeginKeyword:
        case SyntaxKind::CaseKeyword:
        case SyntaxKind::ClassKeyword:
        case SyntaxKind::ConstKeyword:
        case SyntaxKind::ConstructorKeyword:
        case SyntaxKind::DestructorKeyword:
        case SyntaxKind::DispInterfaceKeyword:
        case SyntaxKind::DivKeyword:
        case SyntaxKind::DoKeyword:
        case SyntaxKind::DownToKeyword:
        case SyntaxKind::ElseKeyword:
        case SyntaxKind::EndKeyword:
        case SyntaxKind::ExceptKeyword:
        case SyntaxKind::ExportsKeyword:
        case SyntaxKind::FileKeyword:
        case SyntaxKind::FinalizationKeyword:
        case SyntaxKind::FinallyKeyword:
        case SyntaxKind::ForKeyword:
        case SyntaxKind::FunctionKeyword:
        case SyntaxKind::GoToKeyword:
        case SyntaxKind::IfKeyword:
        case SyntaxKind::ImplementationKeyword:
        case SyntaxKind::InKeyword:
        case SyntaxKind::InheritedKeyword:
        case SyntaxKind::InitializationKeyword:
        case SyntaxKind::InlineKeyword:
        case SyntaxKind::InterfaceKeyword:
        case SyntaxKind::IsKeyword:
        case SyntaxKind::LabelKeyword:
        case SyntaxKind::LibraryKeyword:
        case SyntaxKind::ModKeyword:
        case SyntaxKind::NilKeyword:
        case SyntaxKind::NotKeyword:
        case SyntaxKind::ObjectKeyword:
        case SyntaxKind::OfKeyword:
        case SyntaxKind::OrKeyword:
        case SyntaxKind::PackedKeyword:
        case SyntaxKind::ProcedureKeyword:
        case SyntaxKind::ProgramKeyword:
        case SyntaxKind::PropertyKeyword:
        case SyntaxKind::RaiseKeyword:
        case SyntaxKind::RecordKeyword:
        case SyntaxKind::RepeatKeyword:
        case SyntaxKind::ResourceStringKeyword:
        case SyntaxKind::SetKeyword:
        case SyntaxKind::ShiftLeftKeyword:
        case SyntaxKind::ShiftRightKeyword:
        case SyntaxKind::StringKeyword:
        case SyntaxKind::ThenKeyword:
        case SyntaxKind::ThreadVarKeyword:
        case SyntaxKind::ToKeyword:
        case SyntaxKind::TryKeyword:
        case SyntaxKind::TypeKeyword:
        case SyntaxKind::UnitKeyword:
        case SyntaxKind::UntilKeyword:
        case SyntaxKind::UsesKeyword:
        case SyntaxKind::VarKeyword:
        case SyntaxKind::WhileKeyword:
        case SyntaxKind::WithKeyword:
        case SyntaxKind::XorKeyword:
        case SyntaxKind::AbsoluteKeyword:
        case SyntaxKind::AbstractKeyword:
        case SyntaxKind::AssemblerKeyword:
        case SyntaxKind::AutomatedKeyword:
        case SyntaxKind::CdeclKeyword:
        case SyntaxKind::ContainsKeyword:
        case SyntaxKind::DefaultKeyword:
        case SyntaxKind::DelayedKeyword:
        case SyntaxKind::DeprecatedKeyword:
        case SyntaxKind::DispIdKeyword:
        case SyntaxKind::DynamicKeyword:
        case SyntaxKind::ExperimentalKeyword:
        case SyntaxKind::ExportKeyword:
        case SyntaxKind::ExternalKeyword:
        case SyntaxKind::FarKeyword:
        case SyntaxKind::FinalKeyword:
        case SyntaxKind::ForwardKeyword:
        case SyntaxKind::HelperKeyword:
        case SyntaxKind::ImplementsKeyword:
        case SyntaxKind::IndexKeyword:
        case SyntaxKind::LocalKeyword:
        case SyntaxKind::MessageKeyword:
        case SyntaxKind::NameKeyword:
        case SyntaxKind::NearKeyword:
        case SyntaxKind::NoDefaultKeyword:
        case SyntaxKind::OperatorKeyword:
        case SyntaxKind::OutKeyword:
        case SyntaxKind::OverloadKeyword:
        case SyntaxKind::OverrideKeyword:
        case SyntaxKind::PackageKeyword:
        case SyntaxKind::PascalKeyword:
        case SyntaxKind::PlatformKeyword:
        case SyntaxKind::PrivateKeyword:
        case SyntaxKind::ProtectedKeyword:
        case SyntaxKind::PublicKeyword:
        case SyntaxKind::PublishedKeyword:
        case SyntaxKind::ReadKeyword:
        case SyntaxKind::ReadOnlyKeyword:
        case SyntaxKind::ReferenceKeyword:
        case SyntaxKind::RegisterKeyword:
        case SyntaxKind::ReintroduceKeyword:
        case SyntaxKind::RequiresKeyword:
        case SyntaxKind::ResidentKeyword:
        case SyntaxKind::SafeCallKeyword:
        case SyntaxKind::SealedKeyword:
        case SyntaxKind::StaticKeyword:
        case SyntaxKind::StdCallKeyword:
        case SyntaxKind::StrictKeyword:
        case SyntaxKind::StoredKeyword:
        case SyntaxKind::UnsafeKeyword:
        case SyntaxKind::VarArgsKeyword:
        case SyntaxKind::VirtualKeyword:
        case SyntaxKind::WinApiKeyword:
        case SyntaxKind::WriteKeyword:
        case SyntaxKind::WriteOnlyKeyword:
        case SyntaxKind::ByteKeyword:
        case SyntaxKind::ShortIntKeyword:
        case SyntaxKind::WordKeyword:
        case SyntaxKind::SmallIntKeyword:
        case SyntaxKind::CardinalKeyword:
        case SyntaxKind::LongWordKeyword:
        case SyntaxKind::FixedUIntKeyword:
        case SyntaxKind::IntegerKeyword:
        case SyntaxKind::LongIntKeyword:
        case SyntaxKind::FixedIntKeyword:
        case SyntaxKind::UInt64Keyword:
        case SyntaxKind::Int64Keyword:
        case SyntaxKind::NativeUIntKeyword:
        case SyntaxKind::NativeIntKeyword:
        case SyntaxKind::BytePointerKeyword:
        case SyntaxKind::ShortIntPointerKeyword:
        case SyntaxKind::WordPointerKeyword:
        case SyntaxKind::SmallIntPointerKeyword:
        case SyntaxKind::CardinalPointerKeyword:
        case SyntaxKind::LongWordPointerKeyword:
        case SyntaxKind::FixedUIntPointerKeyword:
        case SyntaxKind::IntegerPointerKeyword:
        case SyntaxKind::LongIntPointerKeyword:
        case SyntaxKind::FixedIntPointerKeyword:
        case SyntaxKind::UInt64PointerKeyword:
        case SyntaxKind::Int64PointerKeyword:
        case SyntaxKind::NativeUIntPointerKeyword:
        case SyntaxKind::NativeIntPointerKeyword:
        case SyntaxKind::SingleKeyword:
        case SyntaxKind::DoubleKeyword:
        case SyntaxKind::ExtendedKeyword:
        case SyntaxKind::RealKeyword:
        case SyntaxKind::SinglePointerKeyword:
        case SyntaxKind::DoublePointerKeyword:
        case SyntaxKind::ExtendedPointerKeyword:
        case SyntaxKind::AnsiCharKeyword:
        case SyntaxKind::CharKeyword:
        case SyntaxKind::WideCharKeyword:
        case SyntaxKind::AnsiStringKeyword:
        case SyntaxKind::RawByteStringKeyword:
        case SyntaxKind::UnicodeStringKeyword:
        case SyntaxKind::ShortStringKeyword:
        case SyntaxKind::WideStringKeyword:
        case SyntaxKind::AnsiCharPointerKeyword:
        case SyntaxKind::CharPointerKeyword:
        case SyntaxKind::WideCharPointerKeyword:
        case SyntaxKind::AnsiStringPointerKeyword:
        case SyntaxKind::RawByteStringPointerKeyword:
        case SyntaxKind::UnicodeStringPointerKeyword:
        case SyntaxKind::StringPointerKeyword:
        case SyntaxKind::ShortStringPointerKeyword:
        case SyntaxKind::WideStringPointerKeyword:
        case SyntaxKind::BooleanKeyword:
        case SyntaxKind::ByteBoolKeyword:
        case SyntaxKind::WordBoolKeyword:
        case SyntaxKind::LongBoolKeyword:
        case SyntaxKind::BooleanPointerKeyword:
        case SyntaxKind::WordBoolPointerKeyword:
        case SyntaxKind::LongBoolPointerKeyword:
        case SyntaxKind::PointerKeyword:
        case SyntaxKind::VariantKeyword:
        case SyntaxKind::CurrencyKeyword:
        case SyntaxKind::PointerPointerKeyword:
        case SyntaxKind::VariantPointerKeyword:
        case SyntaxKind::CurrencyPointerKeyword:
        case SyntaxKind::Real48Keyword:
        case SyntaxKind::UTF8StringKeyword:
        case SyntaxKind::OleVariantKeyword:
        case SyntaxKind::OleVariantPointerKeyword:
        case SyntaxKind::AddKeyword:
        case SyntaxKind::RemoveKeyword:
        case SyntaxKind::AssemblyKeyword:
        case SyntaxKind::BreakKeyword:
        case SyntaxKind::ContinueKeyword:
            return true;
    }

    return false;
}

bool DelphiSyntaxFacts::isModuleStart(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        case SyntaxKind::UnitKeyword:
        case SyntaxKind::PackageKeyword:
        case SyntaxKind::ProgramKeyword:
            return true;
    }

    return false;
}

bool DelphiSyntaxFacts::isStatementStart(Core::Syntax::SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        case SyntaxKind::IfKeyword:
        case SyntaxKind::CaseKeyword:
        case SyntaxKind::RepeatKeyword:
        case SyntaxKind::WhileKeyword:
        case SyntaxKind::ForKeyword:
        case SyntaxKind::WithKeyword:
        case SyntaxKind::TryKeyword:
        case SyntaxKind::RaiseKeyword:
        case SyntaxKind::AssemblerKeyword:
        case SyntaxKind::BeginKeyword:
            return true;
    }

    return false;
}

SyntaxKind DelphiSyntaxFacts::keywordKind(pg_string_view text,
                                          Core::Parser::LexerMode mode) noexcept
{
    pg_string lowerCaseText{text};
    std::transform(std::begin(lowerCaseText), std::end(lowerCaseText), std::begin(lowerCaseText), static_cast<int(*)(int)>(std::tolower));

    if (SYNTAXKEYWORDS.find(lowerCaseText) != SYNTAXKEYWORDS.end())
    {
        SyntaxKind syntaxKind = SYNTAXKEYWORDS.at(lowerCaseText);

        if (mode == Core::Parser::LexerMode::Directive)
        {
            switch (syntaxKind)
            {
                case SyntaxKind::IfKeyword:
                    syntaxKind = SyntaxKind::IfDirectiveKeyword;
                    break;
                case SyntaxKind::ElseKeyword:
                    syntaxKind = SyntaxKind::ElseDirectiveKeyword;
                    break;
                case SyntaxKind::MessageKeyword:
                    syntaxKind = SyntaxKind::MessageDirectiveKeyword;
                    break;
                case SyntaxKind::AssemblerKeyword:
                case SyntaxKind::ByteKeyword:
                case SyntaxKind::ShortIntKeyword:
                case SyntaxKind::WordKeyword:
                case SyntaxKind::SmallIntKeyword:
                case SyntaxKind::CardinalKeyword:
                case SyntaxKind::LongWordKeyword:
                case SyntaxKind::FixedUIntKeyword:
                case SyntaxKind::IntegerKeyword:
                case SyntaxKind::LongIntKeyword:
                case SyntaxKind::FixedIntKeyword:
                case SyntaxKind::UInt64Keyword:
                case SyntaxKind::Int64Keyword:
                case SyntaxKind::NativeUIntKeyword:
                case SyntaxKind::NativeIntKeyword:
                case SyntaxKind::BytePointerKeyword:
                case SyntaxKind::ShortIntPointerKeyword:
                case SyntaxKind::WordPointerKeyword:
                case SyntaxKind::SmallIntPointerKeyword:
                case SyntaxKind::CardinalPointerKeyword:
                case SyntaxKind::LongWordPointerKeyword:
                case SyntaxKind::FixedUIntPointerKeyword:
                case SyntaxKind::IntegerPointerKeyword:
                case SyntaxKind::LongIntPointerKeyword:
                case SyntaxKind::FixedIntPointerKeyword:
                case SyntaxKind::UInt64PointerKeyword:
                case SyntaxKind::Int64PointerKeyword:
                case SyntaxKind::NativeUIntPointerKeyword:
                case SyntaxKind::NativeIntPointerKeyword:
                case SyntaxKind::SingleKeyword:
                case SyntaxKind::DoubleKeyword:
                case SyntaxKind::ExtendedKeyword:
                case SyntaxKind::RealKeyword:
                case SyntaxKind::SinglePointerKeyword:
                case SyntaxKind::DoublePointerKeyword:
                case SyntaxKind::ExtendedPointerKeyword:
                case SyntaxKind::AnsiCharKeyword:
                case SyntaxKind::CharKeyword:
                case SyntaxKind::WideCharKeyword:
                case SyntaxKind::AnsiStringKeyword:
                case SyntaxKind::RawByteStringKeyword:
                case SyntaxKind::UnicodeStringKeyword:
                case SyntaxKind::ShortStringKeyword:
                case SyntaxKind::WideStringKeyword:
                case SyntaxKind::AnsiCharPointerKeyword:
                case SyntaxKind::CharPointerKeyword:
                case SyntaxKind::WideCharPointerKeyword:
                case SyntaxKind::AnsiStringPointerKeyword:
                case SyntaxKind::RawByteStringPointerKeyword:
                case SyntaxKind::UnicodeStringPointerKeyword:
                case SyntaxKind::StringPointerKeyword:
                case SyntaxKind::ShortStringPointerKeyword:
                case SyntaxKind::WideStringPointerKeyword:
                case SyntaxKind::BooleanKeyword:
                case SyntaxKind::ByteBoolKeyword:
                case SyntaxKind::WordBoolKeyword:
                case SyntaxKind::LongBoolKeyword:
                case SyntaxKind::BooleanPointerKeyword:
                case SyntaxKind::WordBoolPointerKeyword:
                case SyntaxKind::LongBoolPointerKeyword:
                case SyntaxKind::PointerKeyword:
                case SyntaxKind::VariantKeyword:
                case SyntaxKind::CurrencyKeyword:
                case SyntaxKind::PointerPointerKeyword:
                case SyntaxKind::VariantPointerKeyword:
                case SyntaxKind::CurrencyPointerKeyword:
                case SyntaxKind::Real48Keyword:
                case SyntaxKind::UTF8StringKeyword:
                case SyntaxKind::OleVariantKeyword:
                case SyntaxKind::OleVariantPointerKeyword:
                    syntaxKind = SyntaxKind::IdentifierToken;
                    break;
            }
        }

        return syntaxKind;
    }

    return SyntaxKind::None;
}

} // end namespace polyglot::Delphi::Parser
