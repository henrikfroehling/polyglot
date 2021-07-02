### Delphi - Statements
##### `if` Statement
###### **EBNF:** `"if" , Expression , "then" , Statement , [ "else" , Statement ]`
---
##### `switch` Statement
###### **EBNF:** `"case" , Expression , "of" , { CaseItem } , [ "else" , StatementList , [ ";" ] ] , "end"`
###### **_CaseItem_ -> EBNF:**: `CaseLabel , { "," , CaseLabel } , ":" , Statement , [ ";" ]`
###### **_CaseLabel_ -> EBNF:** `Expression , [ ".." , Expression ]`
---
##### `for` Statement
###### **EBNF:** 
```
  "for" , Designator , ":=" , Expression , "to" , Expression , "do" , Statement
| "for" , Designator , ":=" , Expression , "downto" , Expression , "do" , Statement
| "for" , Designator , "in" , Expression , "do" , Statement
```
---
##### `for-to` Statement
###### **EBNF:**
```
  "for" , Designator , ":=" , Expression , "to" , Expression , "do" , Statement
| "for" , Designator , ":=" , Expression , "downto" , Expression , "do" , Statement
```
---
##### `for-in` Statement
###### **EBNF:** `"for" , Designator , "in" , Expression , "do" , Statement`
---
##### `while` Statement
###### **EBNF:** `"while" , Expression , "do" , Statement`
---
##### `repeat` Statement
###### **EBNF:** `"repeat" , [ StatementList ] , "until" , Expression`
---
##### `continue` Statement
###### **EBNF:** `"continue"`
---
##### `break` Statement
###### **EBNF:** `"break"`
---
##### `with` Statement
###### **EBNF:** `"with" , Designator , { "," , Designator } , "do" , Statement`
---
##### `try` Statement
###### **EBNF:** 
```
  "try" , StatementList , "except" , HandlerList , "end"
| "try" , StatementList , "finally" , StatementList , "end"
```
###### **_HandlerList_ -> EBNF:** `{ Handler } , [ "else" , StatementList ] | StatementList`
###### **_Handler_ -> EBNF:** `"on" , Ident , ":" , TypeID , "do" , Statement , ";"`
---
##### `raise` Statement
###### **EBNF:** `"raise" , [ Designator ] , [ "at" , Designator ]`
---
##### `exit` Statement
###### **EBNF:** `"exit" , [ "(" , Expression , ")" ]`
---
##### `goto` Statement
###### **EBNF:** `"goto" , Label`
---
##### Block Statement
###### **EBNF:** `"begin" , [ StatementList ] , "end"`
---
##### Statement List
###### **EBNF:** `[ Statement ] , { ";" , [ Statement ] }`
---
##### `asm` Statement
###### **EBNF:** `"asm" , { AssemblyStatement } , "end"`
###### **_AssemblyStatement_ -> EBNF:** `[ AssemblyLabel , ":" ] , [ AssemblyPrefix ] , AssemblyOpcode , [ AssemblyOperand , { "," , AssemblyOperand } ]`
###### **_AssemblyLabel_ -> EBNF:** `Label | LocalLabelPart , { LocalLabelPart }`
###### **_LocalLabelPart_ -> EBNF:** `"@" , Label | tkAsmHexLabel`
###### **_AssemblyPrefix_ -> EBNF:** `LockAndRepeatPrefix , [ SegmentOverridePrefix ] | SegmentOverridePrefix , [ LockAndRepeatPrefix ]`
###### **_LockAndRepeatPrefix_ -> EBNF:** `"lock" | "repne" | "repnz" | "rep" | "repe" | "repz"`
###### **_SegmentOverridePrefix_ -> EBNF:** `"cs" | "ds" | "es" | "fs" | "gs" | "ss"`
###### **_AssemblyOpcode_ -> EBNF:** `PentiumOpcode | [ Ident ] , AssemblyDirective`
###### **_AssemblyOperand_ -> EBNF:**
```
  "[" , Idx16Offset , "]" , [ "+" , ( Disp8 | Disp16 ) ]
| "[" , "bx" , "]" , [ "+" , ( Disp8 | Disp16 ) ]
| [ Disp8 | Disp32 ] , "[" , IdxReg32 , "]"
| ( Disp8 | Disp32 ) , "[" , "ebp" , "]"
| [ Disp8 | Disp32 ] , "[" , "--" , "]" , "[" , "--" , "]"
| "[" , IdxReg32 , "*" , RegMul , "]"
| "[" , "ebp" , "*" , RegMul , "]"
| Reg32 | Reg16 | Reg8H | Reg8L | RegMM | RegXMM | FloatReg | Disp16
```
###### **_AssemblyDirective_ -> EBNF:** `"db" | "dw" | "dd" | "dq"`
###### **_Idx16Offset_ -> EBNF:** `[ ( "bx" | "bp" ) , "+" ] , ( "si" | "di" )`
###### **_IdxReg32_ -> EBNF:** `"eax" | "ebx" | "ecx" | "edx" | "esi" | "edi"`
###### **_Disp8_ -> EBNF:** `ConstExpression`
###### **_Disp16_ -> EBNF:** `ConstExpression`
###### **_Disp32_ -> EBNF:** `ConstExpression`
###### **_RegMul_ -> EBNF:** `"2" | "4" | "8"`
###### **_Reg8L_ -> EBNF:** `"al" | "bl" | "cl" | "dl"`
###### **_Reg8H_ -> EBNF:** `"ah" | "bh" | "ch" | "dh"`
###### **_Reg16_ -> EBNF:** `"ax" | "bx" | "cx" | "dx" | "si" | "di" | "sp" | "bp"`
###### **_Reg32_ -> EBNF:** `IdxReg32 | RegDebug | RegControl | "esp" | "ebp"`
###### **_RegMM_ -> EBNF:** `"mm0" | "mm1" | "mm2" | "mm3" | "mm4" | "mm5" | "mm6" | "mm7"`
###### **_RegXMM_ -> EBNF:** `"xmm0" | "xmm1" | "xmm2" | "xmm3" | "xmm4" | "xmm5" | "xmm6" | "xmm7"`
###### **_FloatReg_ -> EBNF:** `"st" , [ "(" , FloatRegIndex , ")" ]`
###### **_FloatRegIndex_ -> EBNF:** `"0" | "1" | "2" | "3" | "4" | "5" | "6" | "7"`
###### **_RegDebug_ -> EBNF:** `"dr0" | "dr1" | "dr2" | "dr3" | "dr4" | "dr5" | "dr6" | "dr7"`
###### **_RegControl_ -> EBNF:** `"cr0" | "cr1" | "cr2" | "cr3" | "cr4"`
###### **_PentiumOpcode_ -> EBNF:**
```
  "aaa" | "aad" | "aam" | "aas" | "adc" | "add" | "addps" | "addss" | "and" | "andnps" | "andps" | "arpl"
| "bound" | "bsf" | "bsr" | "bswap" | "bt" | "btc" | "btr" | "bts"
| "call" | "cbw" | "cdq" | "clc" | "cld" | "cli" | "clts" | "cmc" | "cmova" | "cmovae" | "cmovb" | "cmovbe" | "cmovc" | "cmove" | "cmovg" | "cmovge"
| "cmovl" | "cmovle" | "cmovna" | "cmovnae" | "cmovnb" | "cmovnbe" | "cmovnc" | "cmovne" | "cmovng" | "cmovnge" | "cmovnl" | "cmovnle" | "cmp"
| "cmpps" | "cmps" | "cmpsd" | "cmpsb" | "cmpsw" | "cmpss" | "cmpxchg" | "cmpxchg8b" | "comiss" | "cpuid" | "cvtpi2ps" | "cvtsi2ss" | "cvtss2si"
| "cvttps2pi" | "cvttss2si" | "cwd" | "cwde"
| "daa" | "das" | "dec" | "div" | "divps" | "divss"
| "emms" | "enter"
| "f2xm1" | "fabs" | "fadd" | "faddp" | "fbld" | "fbstp" | "fchs" | "fclex" | "fcmovb" | "fcmovbe" | "fcmove" | "fcmovnb" | "fcmovnbe" | "fcmovne"
| "fcmovnu" | "fcmovu" | "fcom" | "fcomi" | "fcomip" | "fcomp" | "fcompp" | "fcos" | "fdecstp" | "fdiv" | "fdivp" | "fdivr" | "fdivrp" | "ffree"
| "fiadd" | "ficom" | "ficomp" | "fidiv" | "fidivr" | "fild" | "fimul" | "fincstp" | "finit" | "fist" | "fistp" | "fisub" | "fisubr" | "fld"
| "fld1" | "fldcw" | "fldenv" | "fldl2e" | "fldl2t" | "fldlg2" | "fldln2" | "fldpi" | "fldz" | "fmul" | "fmulp" | "fnclex" | "fninit" | "fnop"
| "fnsave" | "fnstcw" | "fnstenv" | "fnstsw" | "fpatan" | "fprem" | "fprem1" | "fptan" | "frndint" | "frstor" | "fsave" | "fscale" | "fsin"
| "fsincos" | "fsqrt" | "fst" | "fstcw" | "fstenv" | "fstp" | "fstsw" | "fsub" | "fsubp" | "fsubr" | "fsubrp" | "ftst" | "fucom" | "fucomi"
| "fucomip" | "fucomp" | "fucompp" | "fwait" | "fxam" | "fxch" | "fxrstor" | "fxsave" | "fxtract" | "fyl2x" | "fyl2xp1"
| "hlt"
| "idiv" | "imul" | "in" | "inc" | "ins" | "insd" | "insb" | "insw" | "int" | "into" | "invd" | "invlpg" | "iret" | "iretd"
| "ja" | "jae" | "jb" | "jbe" | "jc" | "jcxz" | "je" | "jecxz" | "jg" | "jge" | "jl" | "jle" | "jmp" | "jna" | "jnae" | "jn" | "jnbe" | "jnc"
| "jne" | "jng" | "jnge" | "jnl" | "jnle" | "jno" | "jnp" | "jns" | "jnz" | "jo" | "jp" | "jpe" | "jpo" | "js" | "jz"
| "lahf" | "lar" | "ldmxcsr" | "lds" | "les" | "lfs" | "lgs" | "lss" | "lea" | "leave" | "lgdt" | "lidt" | "lldt" | "lmsw" | "lods" | "lodsb"
| "lodsd" | "lodsw" | "loop" | "loope" | "loopne" | "loopnz" | "loopz" | "lsl" | "ltr"
| "maskmovq" | "maxps" | "maxss" | "minps" | "minss" | "mov" | "movaps" | "movd" | "movhlps" | "movhps" | "movlhps" | "movlps" | "movmskps"
| "movntps" | "movntq" | "movq" | "movs" | "movsb" | "movsd" | "movss" | "movsw" | "movsx" | "movups" | "movzx" | "mul" | "mulps" | "mulss"
| "neg" | "nop" | "not"
| "or" | "orps" | "out" | "outs" | "outsb" | "outsd" | "outsw"
| "packssdw" | "packsswb" | "packuswb" | "paddb" | "paddd" | "paddsb" | "paddusb" | "passusw" | "paddsw" | "paddw" | "pand" | "pandn"
| "pavgb" | "pavgw" | "pcmpeqb" | "pcmpeqd" | "pcmpeqw" | "pcmpgtb" | "pcmpgtd" | "pcmpgtw" | "pextrw" | "pinsrw" | "pmaddwd" | "pmaxsw"
| "pmaxub" | "pminsw" | "pminub" | "pmovmskb" | "pmulhuw" | "pmulhw" | "pmullw" | "pop" | "popa" | "popad" | "popf" | "popfd" | "por"
| "prefetch" | "psadbw" | "pshufw" | "pslld" | "psllq" | "psllw" | "psrad" | "psraw" | "psrld" | "psrlq" | "psrlw" | "psubb" | "psubd"
| "psubw" | "psubsb" | "psubsw" | "psubusb" | "psubusw" | "punpcklbw" | "push" | "pusha" | "pushad" | "pushf" | "pushfd" | "pxor"
| "rcl" | "rcpps" | "rcpss" | "rcr" | "rdmsr" | "rdpmc" | "rdtsc" | "ret" | "rol" | "ror" | "rsm" | "rsqrtps" | "rsqrtss"
| "sahf" | "sal" | "sar" | "sbb" | "scas" | "scasb" | "scasd" | "scasw" | "seta" | "setae" | "setb" | "setbe" | "setc" | "sete" | "setg"
| "setge" | "setl" | "setle" | "setna" | "setnae" | "setnb" | "setnbe" | "setnc" | "setne" | "setng" | "setnge" | "setnl" | "setnle"
| "setno" | "setnp" | "setns" | "setnz" | "seto" | "setp" | "setpe" | "setpo" | "sets" | "setz" | "sfence" | "sgdt" | "shl" | "shld"
| "shr" | "shrd" | "shufps" | "sidt" | "sldt" | "smsw" | "sqrtps" | "sqrtss" | "stc" | "std" | "sti" | "stmxcsr" | "stos" | "stosb"
| "stosd" | "stosw" | "str" | "sub" | "subps" | "subss" | "sysenter" | "sysexit"
| "test"
| "ucomiss" | "ud2" | "unpckhps" | "unpcklps"
| "verr" | "verw"
| "wait" | "wbinvd" | "wrmsr"
| "xadd" | "xchg" | "xlat" | "xlatb" | "xor" | "xorps"
```
