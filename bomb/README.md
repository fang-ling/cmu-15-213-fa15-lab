This is an x86-64 bomb for self-study students. 

## TL;DR

- Phase 1: Border relations with Canada have never been better.

## Phase 1

Set breakpoint at phase_1() and explode_bomb():

```shell
(gdb) b phase_1
Breakpoint 1 at 0x400ee0
(gdb) b explode_bomb 
Breakpoint 2 at 0x40143a
```

Run! (Start program):

```shell
(gdb) run
```

The program will print:

```shell
Welcome to my fiendish little bomb. You have 6 phases with
which to blow yourself up. Have a nice day!
```

After entering some random characters we can apply gdb command `disassemble` to dump assembler code for function phase_1:

```shell
Breakpoint 1, 0x0000000000400ee0 in phase_1 ()
(gdb) disassemble 
Dump of assembler code for function phase_1:
=> 0x0000000000400ee0 <+0>:	sub    $0x8,%rsp
   0x0000000000400ee4 <+4>:	mov    $0x402400,%esi
   0x0000000000400ee9 <+9>:	call   0x401338 <strings_not_equal>
   0x0000000000400eee <+14>:	test   %eax,%eax
   0x0000000000400ef0 <+16>:	je     0x400ef7 <phase_1+23>
   0x0000000000400ef2 <+18>:	call   0x40143a <explode_bomb>
   0x0000000000400ef7 <+23>:	add    $0x8,%rsp
   0x0000000000400efb <+27>:	ret    
End of assembler dump.
```

Recall that given the arguments in left-to-right order, the order of registers used is: %rdi, %rsi, %rdx, %rcx, %r8, and %r9. It's obvious that the address of our input string is stored in %rdi.

Step at `0x0000000000400ee4 <+4>` and `0x0000000000400ee9 <+9>`, there is a function named `strings_not_equal`, thus the other string (or phase 1) is stored at address `$0x402400`. Since we don't know the length of it, just try a large number with gdb command `p`:

```shell
(gdb) si
0x0000000000400ee4 in phase_1 ()
(gdb) si
0x0000000000400ee9 in phase_1 ()
(gdb) si
0x0000000000401338 in strings_not_equal ()
(gdb) p (char[60])*$rsi
$4 = "Border relations with Canada have never been better.\000\000\000\000Wow!"
```

Answer: Border relations with Canada have never been better.
