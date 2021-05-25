#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Core::Syntax
{

pg_string syntaxKindName(SyntaxKind syntaxKind) noexcept
{
    switch (syntaxKind)
    {
        // special tokens
        case SyntaxKind::None: return L"None";
        case SyntaxKind::BadToken: return L"BadToken";
        case SyntaxKind::EndOfFileToken: return L"EndOfFileToken";
        case SyntaxKind::WhitespaceToken: return L"WhitespaceToken";

        // punctuation
        case SyntaxKind::DotToken: return L"DotToken";
        case SyntaxKind::CommaToken: return L"CommaToken";
        case SyntaxKind::SemiColonToken: return L"SemiColonToken";
        case SyntaxKind::ColonToken: return L"ColonToken";
        case SyntaxKind::EqualToken: return L"EqualToken";
        case SyntaxKind::CaretToken: return L"CaretToken";
        case SyntaxKind::LessThanToken: return L"LessThanToken";
        case SyntaxKind::GreaterThanToken: return L"GreaterThanToken";
        case SyntaxKind::OpenParenthesisToken: return L"OpenParenthesisToken";
        case SyntaxKind::CloseParenthesisToken: return L"CloseParenthesisToken";
        case SyntaxKind::OpenBracketToken: return L"OpenBracketToken";
        case SyntaxKind::CloseBracketToken: return L"CloseBracketToken";
        case SyntaxKind::OpenBraceToken: return L"OpenBraceToken";
        case SyntaxKind::CloseBraceToken: return L"CloseBraceToken";
        case SyntaxKind::AtToken: return L"AtToken";
        case SyntaxKind::PlusToken: return L"PlusToken";
        case SyntaxKind::MinusToken: return L"MinusToken";
        case SyntaxKind::AsteriskToken: return L"AsteriskToken";
        case SyntaxKind::SlashToken: return L"SlashToken";
        case SyntaxKind::AmpersandToken: return L"AmpersandToken";
        case SyntaxKind::DollarToken: return L"DollarToken";
        case SyntaxKind::UnderscoreToken: return L"UnderscoreToken";
        case SyntaxKind::HashToken: return L"HashToken";
        case SyntaxKind::SingleQuoteToken: return L"SingleQuoteToken";
        case SyntaxKind::DoubleQuoteToken: return L"DoubleQuoteToken";
        case SyntaxKind::ExclamationMarkToken: return L"ExclamationMarkToken";

        // compound punctuation
        case SyntaxKind::DotDotToken: return L"DotDotToken";
        case SyntaxKind::CaretDotToken: return L"CaretDotToken";
        case SyntaxKind::ColonEqualToken: return L"ColonEqualToken";
        case SyntaxKind::SlashSlashToken: return L"SlashSlashToken";
        case SyntaxKind::LessThanEqualToken: return L"LessThanEqualToken";
        case SyntaxKind::GreaterThanEqualToken: return L"GreaterThanEqualToken";
        case SyntaxKind::LessThanGreaterThanToken: return L"LessThanGreaterThanToken";
        case SyntaxKind::MinusMinusToken: return L"MinusMinusToken";
        case SyntaxKind::OpenParenthesisAsteriskToken: return L"OpenParenthesisAsteriskToken";
        case SyntaxKind::AsteriskCloseParenthesisToken: return L"AsteriskCloseParenthesisToken";
        case SyntaxKind::OpenParenthesisDotToken: return L"OpenParenthesisDotToken";
        case SyntaxKind::DotCloseParenthesisToken: return L"DotCloseParenthesisToken";
        case SyntaxKind::OpenBraceDollarToken: return L"OpenBraceDollarToken";
        case SyntaxKind::OpenParenthesisDollarToken: return L"OpenParenthesisDollarToken";
        case SyntaxKind::AtAtToken: return L"AtAtToken";

        // keywords
        case SyntaxKind::AndKeyword: return L"AndKeyword";
        case SyntaxKind::ArrayKeyword: return L"ArrayKeyword";
        case SyntaxKind::AsKeyword: return L"AsKeyword";
        case SyntaxKind::AsmKeyword: return L"AsmKeyword";
        case SyntaxKind::BeginKeyword: return L"BeginKeyword";
        case SyntaxKind::CaseKeyword: return L"CaseKeyword";
        case SyntaxKind::ClassKeyword: return L"ClassKeyword";
        case SyntaxKind::ConstKeyword: return L"ConstKeyword";
        case SyntaxKind::ConstructorKeyword: return L"ConstructorKeyword";
        case SyntaxKind::DestructorKeyword: return L"DestructorKeyword";
        case SyntaxKind::DispInterfaceKeyword: return L"DispInterfaceKeyword";
        case SyntaxKind::DivKeyword: return L"DivKeyword";
        case SyntaxKind::DoKeyword: return L"DoKeyword";
        case SyntaxKind::DownToKeyword: return L"DownToKeyword";
        case SyntaxKind::ElseKeyword: return L"ElseKeyword";
        case SyntaxKind::EndKeyword: return L"EndKeyword";
        case SyntaxKind::ExceptKeyword: return L"ExceptKeyword";
        case SyntaxKind::ExportsKeyword: return L"ExportsKeyword";
        case SyntaxKind::FileKeyword: return L"FileKeyword";
        case SyntaxKind::FinalizationKeyword: return L"FinalizationKeyword";
        case SyntaxKind::FinallyKeyword: return L"FinallyKeyword";
        case SyntaxKind::ForKeyword: return L"ForKeyword";
        case SyntaxKind::FunctionKeyword: return L"FunctionKeyword";
        case SyntaxKind::GoToKeyword: return L"GoToKeyword";
        case SyntaxKind::IfKeyword: return L"IfKeyword";
        case SyntaxKind::ImplementationKeyword: return L"ImplementationKeyword";
        case SyntaxKind::InKeyword: return L"InKeyword";
        case SyntaxKind::InheritedKeyword: return L"InheritedKeyword";
        case SyntaxKind::InitializationKeyword: return L"InitializationKeyword";
        case SyntaxKind::InlineKeyword: return L"InlineKeyword";
        case SyntaxKind::InterfaceKeyword: return L"InterfaceKeyword";
        case SyntaxKind::IsKeyword: return L"IsKeyword";
        case SyntaxKind::LabelKeyword: return L"LabelKeyword";
        case SyntaxKind::LibraryKeyword: return L"LibraryKeyword";
        case SyntaxKind::ModKeyword: return L"ModKeyword";
        case SyntaxKind::NilKeyword: return L"NilKeyword";
        case SyntaxKind::NotKeyword: return L"NotKeyword";
        case SyntaxKind::ObjectKeyword: return L"ObjectKeyword";
        case SyntaxKind::OfKeyword: return L"OfKeyword";
        case SyntaxKind::OrKeyword: return L"OrKeyword";
        case SyntaxKind::PackedKeyword: return L"PackedKeyword";
        case SyntaxKind::ProcedureKeyword: return L"ProcedureKeyword";
        case SyntaxKind::ProgramKeyword: return L"ProgramKeyword";
        case SyntaxKind::PropertyKeyword: return L"PropertyKeyword";
        case SyntaxKind::RaiseKeyword: return L"RaiseKeyword";
        case SyntaxKind::RecordKeyword: return L"RecordKeyword";
        case SyntaxKind::RepeatKeyword: return L"RepeatKeyword";
        case SyntaxKind::ResourceStringKeyword: return L"ResourceStringKeyword";
        case SyntaxKind::SetKeyword: return L"SetKeyword";
        case SyntaxKind::ShiftLeftKeyword: return L"ShiftLeftKeyword";
        case SyntaxKind::ShiftRightKeyword: return L"ShiftRightKeyword";
        case SyntaxKind::StringKeyword: return L"StringKeyword";
        case SyntaxKind::ThenKeyword: return L"ThenKeyword";
        case SyntaxKind::ThreadVarKeyword: return L"ThreadVarKeyword";
        case SyntaxKind::ToKeyword: return L"ToKeyword";
        case SyntaxKind::TryKeyword: return L"TryKeyword";
        case SyntaxKind::TypeKeyword: return L"TypeKeyword";
        case SyntaxKind::UnitKeyword: return L"UnitKeyword";
        case SyntaxKind::UntilKeyword: return L"UntilKeyword";
        case SyntaxKind::UsesKeyword: return L"UsesKeyword";
        case SyntaxKind::VarKeyword: return L"VarKeyword";
        case SyntaxKind::WhileKeyword: return L"WhileKeyword";
        case SyntaxKind::WithKeyword: return L"WithKeyword";
        case SyntaxKind::XorKeyword: return L"XorKeyword";
        case SyntaxKind::AbsoluteKeyword: return L"AbsoluteKeyword";
        case SyntaxKind::AbstractKeyword: return L"AbstractKeyword";
        case SyntaxKind::AssemblerKeyword: return L"AssemblerKeyword";
        case SyntaxKind::AutomatedKeyword: return L"AutomatedKeyword";
        case SyntaxKind::CdeclKeyword: return L"CdeclKeyword";
        case SyntaxKind::ContainsKeyword: return L"ContainsKeyword";
        case SyntaxKind::DefaultKeyword: return L"DefaultKeyword";
        case SyntaxKind::DelayedKeyword: return L"DelayedKeyword";
        case SyntaxKind::DeprecatedKeyword: return L"DeprecatedKeyword";
        case SyntaxKind::DispIdKeyword: return L"DispIdKeyword";
        case SyntaxKind::DynamicKeyword: return L"DynamicKeyword";
        case SyntaxKind::ExperimentalKeyword: return L"ExperimentalKeyword";
        case SyntaxKind::ExportKeyword: return L"ExportKeyword";
        case SyntaxKind::ExternalKeyword: return L"ExternalKeyword";
        case SyntaxKind::FarKeyword: return L"FarKeyword";
        case SyntaxKind::FinalKeyword: return L"FinalKeyword";
        case SyntaxKind::ForwardKeyword: return L"ForwardKeyword";
        case SyntaxKind::HelperKeyword: return L"HelperKeyword";
        case SyntaxKind::ImplementsKeyword: return L"ImplementsKeyword";
        case SyntaxKind::IndexKeyword: return L"IndexKeyword";
        case SyntaxKind::LocalKeyword: return L"LocalKeyword";
        case SyntaxKind::MessageKeyword: return L"MessageKeyword";
        case SyntaxKind::NameKeyword: return L"NameKeyword";
        case SyntaxKind::NearKeyword: return L"NearKeyword";
        case SyntaxKind::NoDefaultKeyword: return L"NoDefaultKeyword";
        case SyntaxKind::OperatorKeyword: return L"OperatorKeyword";
        case SyntaxKind::OutKeyword: return L"OutKeyword";
        case SyntaxKind::OverloadKeyword: return L"OverloadKeyword";
        case SyntaxKind::OverrideKeyword: return L"OverrideKeyword";
        case SyntaxKind::PackageKeyword: return L"PackageKeyword";
        case SyntaxKind::PascalKeyword: return L"PascalKeyword";
        case SyntaxKind::PlatformKeyword: return L"PlatformKeyword";
        case SyntaxKind::PrivateKeyword: return L"PrivateKeyword";
        case SyntaxKind::ProtectedKeyword: return L"ProtectedKeyword";
        case SyntaxKind::PublicKeyword: return L"PublicKeyword";
        case SyntaxKind::PublishedKeyword: return L"PublishedKeyword";
        case SyntaxKind::ReadKeyword: return L"ReadKeyword";
        case SyntaxKind::ReadOnlyKeyword: return L"ReadOnlyKeyword";
        case SyntaxKind::ReferenceKeyword: return L"ReferenceKeyword";
        case SyntaxKind::RegisterKeyword: return L"RegisterKeyword";
        case SyntaxKind::ReintroduceKeyword: return L"ReintroduceKeyword";
        case SyntaxKind::RequiresKeyword: return L"RequiresKeyword";
        case SyntaxKind::ResidentKeyword: return L"ResidentKeyword";
        case SyntaxKind::SafeCallKeyword: return L"SafeCallKeyword";
        case SyntaxKind::SealedKeyword: return L"SealedKeyword";
        case SyntaxKind::StaticKeyword: return L"StaticKeyword";
        case SyntaxKind::StdCallKeyword: return L"StdCallKeyword";
        case SyntaxKind::StrictKeyword: return L"StrictKeyword";
        case SyntaxKind::StoredKeyword: return L"StoredKeyword";
        case SyntaxKind::UnsafeKeyword: return L"UnsafeKeyword";
        case SyntaxKind::VarArgsKeyword: return L"VarArgsKeyword";
        case SyntaxKind::VirtualKeyword: return L"VirtualKeyword";
        case SyntaxKind::WinApiKeyword: return L"WinApiKeyword";
        case SyntaxKind::WriteKeyword: return L"WriteKeyword";
        case SyntaxKind::WriteOnlyKeyword: return L"WriteOnlyKeyword";
        case SyntaxKind::ByteKeyword: return L"ByteKeyword";
        case SyntaxKind::ShortIntKeyword: return L"ShortIntKeyword";
        case SyntaxKind::WordKeyword: return L"WordKeyword";
        case SyntaxKind::SmallIntKeyword: return L"SmallIntKeyword";
        case SyntaxKind::CardinalKeyword: return L"CardinalKeyword";
        case SyntaxKind::LongWordKeyword: return L"LongWordKeyword";
        case SyntaxKind::FixedUIntKeyword: return L"FixedUIntKeyword";
        case SyntaxKind::IntegerKeyword: return L"IntegerKeyword";
        case SyntaxKind::LongIntKeyword: return L"LongIntKeyword";
        case SyntaxKind::FixedIntKeyword: return L"FixedIntKeyword";
        case SyntaxKind::UInt64Keyword: return L"UInt64Keyword";
        case SyntaxKind::Int64Keyword: return L"Int64Keyword";
        case SyntaxKind::NativeUIntKeyword: return L"NativeUIntKeyword";
        case SyntaxKind::NativeIntKeyword: return L"NativeIntKeyword";
        case SyntaxKind::BytePointerKeyword: return L"BytePointerKeyword";
        case SyntaxKind::ShortIntPointerKeyword: return L"ShortIntPointerKeyword";
        case SyntaxKind::WordPointerKeyword: return L"WordPointerKeyword";
        case SyntaxKind::SmallIntPointerKeyword: return L"SmallIntPointerKeyword";
        case SyntaxKind::CardinalPointerKeyword: return L"CardinalPointerKeyword";
        case SyntaxKind::LongWordPointerKeyword: return L"LongWordPointerKeyword";
        case SyntaxKind::FixedUIntPointerKeyword: return L"FixedUIntPointerKeyword";
        case SyntaxKind::IntegerPointerKeyword: return L"IntegerPointerKeyword";
        case SyntaxKind::LongIntPointerKeyword: return L"LongIntPointerKeyword";
        case SyntaxKind::FixedIntPointerKeyword: return L"FixedIntPointerKeyword";
        case SyntaxKind::UInt64PointerKeyword: return L"UInt64PointerKeyword";
        case SyntaxKind::Int64PointerKeyword: return L"Int64PointerKeyword";
        case SyntaxKind::NativeUIntPointerKeyword: return L"NativeUIntPointerKeyword";
        case SyntaxKind::NativeIntPointerKeyword: return L"NativeIntPointerKeyword";
        case SyntaxKind::SingleKeyword: return L"SingleKeyword";
        case SyntaxKind::DoubleKeyword: return L"DoubleKeyword";
        case SyntaxKind::ExtendedKeyword: return L"ExtendedKeyword";
        case SyntaxKind::RealKeyword: return L"RealKeyword";
        case SyntaxKind::SinglePointerKeyword: return L"SinglePointerKeyword";
        case SyntaxKind::DoublePointerKeyword: return L"DoublePointerKeyword";
        case SyntaxKind::ExtendedPointerKeyword: return L"ExtendedPointerKeyword";
        case SyntaxKind::AnsiCharKeyword: return L"AnsiCharKeyword";
        case SyntaxKind::CharKeyword: return L"CharKeyword";
        case SyntaxKind::WideCharKeyword: return L"WideCharKeyword";
        case SyntaxKind::AnsiStringKeyword: return L"AnsiStringKeyword";
        case SyntaxKind::RawByteStringKeyword: return L"RawByteStringKeyword";
        case SyntaxKind::UnicodeStringKeyword: return L"UnicodeStringKeyword";
        case SyntaxKind::ShortStringKeyword: return L"ShortStringKeyword";
        case SyntaxKind::WideStringKeyword: return L"WideStringKeyword";
        case SyntaxKind::AnsiCharPointerKeyword: return L"AnsiCharPointerKeyword";
        case SyntaxKind::CharPointerKeyword: return L"CharPointerKeyword";
        case SyntaxKind::WideCharPointerKeyword: return L"WideCharPointerKeyword";
        case SyntaxKind::AnsiStringPointerKeyword: return L"AnsiStringPointerKeyword";
        case SyntaxKind::RawByteStringPointerKeyword: return L"RawByteStringPointerKeyword";
        case SyntaxKind::UnicodeStringPointerKeyword: return L"UnicodeStringPointerKeyword";
        case SyntaxKind::StringPointerKeyword: return L"StringPointerKeyword";
        case SyntaxKind::ShortStringPointerKeyword: return L"ShortStringPointerKeyword";
        case SyntaxKind::WideStringPointerKeyword: return L"WideStringPointerKeyword";
        case SyntaxKind::BooleanKeyword: return L"BooleanKeyword";
        case SyntaxKind::ByteBoolKeyword: return L"ByteBoolKeyword";
        case SyntaxKind::WordBoolKeyword: return L"WordBoolKeyword";
        case SyntaxKind::LongBoolKeyword: return L"LongBoolKeyword";
        case SyntaxKind::BooleanPointerKeyword: return L"BooleanPointerKeyword";
        case SyntaxKind::WordBoolPointerKeyword: return L"WordBoolPointerKeyword";
        case SyntaxKind::LongBoolPointerKeyword: return L"LongBoolPointerKeyword";
        case SyntaxKind::PointerKeyword: return L"PointerKeyword";
        case SyntaxKind::VariantKeyword: return L"VariantKeyword";
        case SyntaxKind::CurrencyKeyword: return L"CurrencyKeyword";
        case SyntaxKind::PointerPointerKeyword: return L"PointerPointerKeyword";
        case SyntaxKind::VariantPointerKeyword: return L"VariantPointerKeyword";
        case SyntaxKind::CurrencyPointerKeyword: return L"CurrencyPointerKeyword";
        case SyntaxKind::Real48Keyword: return L"Real48Keyword";
        case SyntaxKind::UTF8StringKeyword: return L"UTF8StringKeyword";
        case SyntaxKind::OleVariantKeyword: return L"OleVariantKeyword";
        case SyntaxKind::OleVariantPointerKeyword: return L"OleVariantPointerKeyword";
        case SyntaxKind::AddKeyword: return L"AddKeyword";
        case SyntaxKind::RemoveKeyword: return L"RemoveKeyword";
        case SyntaxKind::AssemblyKeyword: return L"AssemblyKeyword";
        case SyntaxKind::BreakKeyword: return L"BreakKeyword";
        case SyntaxKind::ContinueKeyword: return L"ContinueKeyword";
        case SyntaxKind::TrueKeyword: return L"TrueKeyword";
        case SyntaxKind::FalseKeyword: return L"FalseKeyword";

        case SyntaxKind::SingleQuotationStringLiteralToken: return L"SingleQuotationStringLiteralToken";
        case SyntaxKind::DoubleQuotationStringLiteralToken: return L"DoubleQuotationStringLiteralToken";
        case SyntaxKind::SingleQuotationSingleCharLiteralToken: return L"SingleQuotationSingleCharLiteralToken";
        case SyntaxKind::NumberLiteralToken: return L"NumberLiteralToken";
        case SyntaxKind::IntegerNumberLiteralToken: return L"IntegerNumberLiteralToken";
        case SyntaxKind::RealNumberLiteralToken: return L"RealNumberLiteralToken";
        case SyntaxKind::ControlCharacterLiteral: return L"ControlCharacterLiteral";
        case SyntaxKind::IdentifierToken: return L"IdentifierToken";

        // trivia
        case SyntaxKind::WhitespaceTrivia: return L"WhitespaceTrivia";
        case SyntaxKind::SingleLineCommentTrivia: return L"SingleLineCommentTrivia";
        case SyntaxKind::MultiLineCommentTrivia: return L"MultiLineCommentTrivia";
        case SyntaxKind::EndOfLineTrivia: return L"EndOfLineTrivia";
        case SyntaxKind::BadDirectiveTrivia: return L"BadDirectiveTrivia";
        case SyntaxKind::IfDirectiveTrivia: return L"IfDirectiveTrivia";
        case SyntaxKind::IfDefDirectiveTrivia: return L"IfDefDirectiveTrivia";
        case SyntaxKind::IfNDefDirectiveTrivia: return L"IfNDefDirectiveTrivia";
        case SyntaxKind::IfEndDirectiveTrivia: return L"IfEndDirectiveTrivia";
        case SyntaxKind::ElseIfDirectiveTrivia: return L"ElseIfDirectiveTrivia";
        case SyntaxKind::ElseDirectiveTrivia: return L"ElseDirectiveTrivia";
        case SyntaxKind::EndIfDirectiveTrivia: return L"EndIfDirectiveTrivia";
        case SyntaxKind::DefineDirectiveTrivia: return L"DefineDirectiveTrivia";
        case SyntaxKind::UndefDirectiveTrivia: return L"UndefDirectiveTrivia";
        case SyntaxKind::RegionDirectiveTrivia: return L"RegionDirectiveTrivia";
        case SyntaxKind::EndRegionDirectiveTrivia: return L"EndRegionDirectiveTrivia";
        case SyntaxKind::MessageDirectiveTrivia: return L"MessageDirectiveTrivia";
        case SyntaxKind::SwitchDirectiveTrivia: return L"SwitchDirectiveTrivia";
        case SyntaxKind::SkippedTokensTrivia: return L"SkippedTokensTrivia";

        // directives
        case SyntaxKind::IfDirectiveKeyword: return L"IfDirectiveKeyword";
        case SyntaxKind::IfDefDirectiveKeyword: return L"IfDefDirectiveKeyword";
        case SyntaxKind::IfNDefDirectiveKeyword: return L"IfNDefDirectiveKeyword";
        case SyntaxKind::IfEndDirectiveKeyword: return L"IfEndDirectiveKeyword";
        case SyntaxKind::ElseIfDirectiveKeyword: return L"ElseIfDirectiveKeyword";
        case SyntaxKind::ElseDirectiveKeyword: return L"ElseDirectiveKeyword";
        case SyntaxKind::EndIfDirectiveKeyword: return L"EndIfDirectiveKeyword";
        case SyntaxKind::DefineDirectiveKeyword: return L"DefineDirectiveKeyword";
        case SyntaxKind::UndefDirectiveKeyword: return L"UndefDirectiveKeyword";
        case SyntaxKind::RegionDirectiveKeyword: return L"RegionDirectiveKeyword";
        case SyntaxKind::EndRegionDirectiveKeyword: return L"EndRegionDirectiveKeyword";
        case SyntaxKind::MessageDirectiveKeyword: return L"MessageDirectiveKeyword";
        case SyntaxKind::OnDirectiveKeyword: return L"OnDirectiveKeyword";
        case SyntaxKind::OffDirectiveKeyword: return L"OffDirectiveKeyword";
        case SyntaxKind::EndOfDirectiveToken: return L"EndOfDirectiveToken";

        case SyntaxKind::SyntaxList: return L"SyntaxList";
        case SyntaxKind::CompilationUnit: return L"CompilationUnit";
        case SyntaxKind::UnitModule: return L"UnitModule";
        case SyntaxKind::UnitHead: return L"UnitHead";
        case SyntaxKind::UnitInterfaceSection: return L"UnitInterfaceSection";
        case SyntaxKind::UnitImplementationSection: return L"UnitImplementationSection";
        case SyntaxKind::UnitInitializationSection: return L"UnitInitializationSection";
        case SyntaxKind::UnitFinalizationSection: return L"UnitFinalizationSection";
        case SyntaxKind::UnitReferencesList: return L"UnitReferencesList";
        case SyntaxKind::PackageModule: return L"PackageModule";
        case SyntaxKind::PackageHead: return L"PackageHead";
        case SyntaxKind::ProgramModule: return L"ProgramModule";
        case SyntaxKind::ProgramHead: return L"ProgramHead";
        case SyntaxKind::PackageRequiresClause: return L"PackageRequiresClause";
        case SyntaxKind::PackageContainsClause: return L"PackageContainsClause";
        case SyntaxKind::UsesClause: return L"UsesClause";
        case SyntaxKind::UnitReference: return L"UnitReference";
        case SyntaxKind::StatementList: return L"StatementList";
        case SyntaxKind::CompoundStatement: return L"CompoundStatement";
        case SyntaxKind::IfStatement: return L"IfStatement";
        case SyntaxKind::CaseStatement: return L"CaseStatement";
        case SyntaxKind::RepeatStatement: return L"RepeatStatement";
        case SyntaxKind::WhileStatement: return L"WhileStatement";
        case SyntaxKind::ForStatement: return L"ForStatement";
        case SyntaxKind::WithStatement: return L"WithStatement";
        case SyntaxKind::TryStatement: return L"TryStatement";
        case SyntaxKind::RaiseStatement: return L"RaiseStatement";
        case SyntaxKind::AssemblerStatement: return L"AssemblerStatement";

        // expressions
        case SyntaxKind::LogicalNotExpression: return L"LogicalNotExpression";
        case SyntaxKind::LogicalOrExpression: return L"LogicalOrExpression";
        case SyntaxKind::LogicalAndExpression: return L"LogicalAndExpression";
        case SyntaxKind::EqualsExpression: return L"EqualsExpression";
        case SyntaxKind::NotEqualsExpression: return L"NotEqualsExpression";
        case SyntaxKind::ParenthesizedExpression: return L"ParenthesizedExpression";
        case SyntaxKind::StringLiteralExpression: return L"StringLiteralExpression";
        case SyntaxKind::NumericLiteralExpression: return L"NumericLiteralExpression";
        case SyntaxKind::TrueLiteralExpression: return L"TrueLiteralExpression";
        case SyntaxKind::FalseLiteralExpression: return L"FalseLiteralExpression";
        case SyntaxKind::IdentifierNameExpression: return L"IdentifierNameExpression";
        case SyntaxKind::QualifiedNameExpression: return L"QualifiedNameExpression";
        case SyntaxKind::CallExpression: return L"CallExpression";
        case SyntaxKind::EndOfModule: return L"EndOfModule";
    }

    return L"";
}

} // end namespace polyglot::Core::Syntax
