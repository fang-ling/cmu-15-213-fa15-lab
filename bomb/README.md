This is an x86-64 bomb for self-study students. 

## TL;DR

- Phase 1: Border relations with Canada have never been better.
- Phase 2: 1 2 4 8 16 32
- Phase 3: 

| Input 1 | Input 2 | Input 1 | Input 2 |
|:-------:|:-------:|:-------:|:-------:|
| 0 | 207 | 4 | 389 |
| 1 | 311 | 5 | 206 |
| 2 | 707 | 6 | 682 |
| 3 | 256 | 7 | 327 |

- Phase 4: 1 0 or 3 0 (maybe more).
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

## Phase 2

Set breakpoint at phase_2() and explode_bomb():

```shell
(gdb) b phase_2
Breakpoint 1 at 0x400efc
(gdb) b explode_bomb 
Breakpoint 2 at 0x40143a
```

Start the program with phase 1:

```shell
(gdb) run
Starting program: ...
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
Welcome to my fiendish little bomb. You have 6 phases with
which to blow yourself up. Have a nice day!
Border relations with Canada have never been better.
Phase 1 defused. How about the next one?
```

After entering some random characters we can apply gdb command `disassemble` to dump assembler code for function phase_2:

```shell
Breakpoint 1, 0x0000000000400efc in phase_2 ()
(gdb) disassemble 
Dump of assembler code for function phase_2:
=> 0x0000000000400efc <+0>:	push   %rbp
   0x0000000000400efd <+1>:	push   %rbx
   0x0000000000400efe <+2>:	sub    $0x28,%rsp
   0x0000000000400f02 <+6>:	mov    %rsp,%rsi
   0x0000000000400f05 <+9>:	call   0x40145c <read_six_numbers>
   0x0000000000400f0a <+14>:	cmpl   $0x1,(%rsp)
   0x0000000000400f0e <+18>:	je     0x400f30 <phase_2+52>
   0x0000000000400f10 <+20>:	call   0x40143a <explode_bomb>
   0x0000000000400f15 <+25>:	jmp    0x400f30 <phase_2+52>
   0x0000000000400f17 <+27>:	mov    -0x4(%rbx),%eax
   0x0000000000400f1a <+30>:	add    %eax,%eax
   0x0000000000400f1c <+32>:	cmp    %eax,(%rbx)
   0x0000000000400f1e <+34>:	je     0x400f25 <phase_2+41>
   0x0000000000400f20 <+36>:	call   0x40143a <explode_bomb>
   0x0000000000400f25 <+41>:	add    $0x4,%rbx
   0x0000000000400f29 <+45>:	cmp    %rbp,%rbx
   0x0000000000400f2c <+48>:	jne    0x400f17 <phase_2+27>
   0x0000000000400f2e <+50>:	jmp    0x400f3c <phase_2+64>
   0x0000000000400f30 <+52>:	lea    0x4(%rsp),%rbx
   0x0000000000400f35 <+57>:	lea    0x18(%rsp),%rbp
   0x0000000000400f3a <+62>:	jmp    0x400f17 <phase_2+27>
   0x0000000000400f3c <+64>:	add    $0x28,%rsp
   0x0000000000400f40 <+68>:	pop    %rbx
   0x0000000000400f41 <+69>:	pop    %rbp
   0x0000000000400f42 <+70>:	ret    
End of assembler dump.
```

Instruction `0x400f05 <+9>` shows us that phase 2 should be six numbers. We can confirm this by looking inside the function read_six_numbers():

```shell
(gdb) disassemble read_six_numbers
Dump of assembler code for function read_six_numbers:
   0x000000000040145c <+0>:	sub    $0x18,%rsp
   0x0000000000401460 <+4>:	mov    %rsi,%rdx
   0x0000000000401463 <+7>:	lea    0x4(%rsi),%rcx
   0x0000000000401467 <+11>:	lea    0x14(%rsi),%rax
   0x000000000040146b <+15>:	mov    %rax,0x8(%rsp)
   0x0000000000401470 <+20>:	lea    0x10(%rsi),%rax
   0x0000000000401474 <+24>:	mov    %rax,(%rsp)
   0x0000000000401478 <+28>:	lea    0xc(%rsi),%r9
   0x000000000040147c <+32>:	lea    0x8(%rsi),%r8
   0x0000000000401480 <+36>:	mov    $0x4025c3,%esi
   0x0000000000401485 <+41>:	mov    $0x0,%eax
   0x000000000040148a <+46>:	call   0x400bf0 <__isoc99_sscanf@plt>
   0x000000000040148f <+51>:	cmp    $0x5,%eax
   0x0000000000401492 <+54>:	jg     0x401499 <read_six_numbers+61>
   0x0000000000401494 <+56>:	call   0x40143a <explode_bomb>
   0x0000000000401499 <+61>:	add    $0x18,%rsp
   0x000000000040149d <+65>:	ret    
End of assembler dump.
(gdb) x/s 0x4025c3
0x4025c3:	"%d %d %d %d %d %d"
```

The second argument of libc function sscanf() is "%d %d %d %d %d %d". 

Instruction `0x400f0a <+14>` checks if array[0] equals 1. The rest of phase_2 are a loop that check if array[i] is twice as big as array[i - 1].

Answer: 1 2 4 8 16 32

## Phase 3

Use gdb command `disassemble` to dump assembler code for function phase_3:

```shell
(gdb) disassemble phase_3
Dump of assembler code for function phase_3:
   0x0000000000400f43 <+0>:	sub    $0x18,%rsp
   0x0000000000400f47 <+4>:	lea    0xc(%rsp),%rcx
   0x0000000000400f4c <+9>:	lea    0x8(%rsp),%rdx
   0x0000000000400f51 <+14>:	mov    $0x4025cf,%esi
   0x0000000000400f56 <+19>:	mov    $0x0,%eax
   0x0000000000400f5b <+24>:	call   0x400bf0 <__isoc99_sscanf@plt>
   0x0000000000400f60 <+29>:	cmp    $0x1,%eax
   0x0000000000400f63 <+32>:	jg     0x400f6a <phase_3+39>
   0x0000000000400f65 <+34>:	call   0x40143a <explode_bomb>
   0x0000000000400f6a <+39>:	cmpl   $0x7,0x8(%rsp)
   0x0000000000400f6f <+44>:	ja     0x400fad <phase_3+106>
   0x0000000000400f71 <+46>:	mov    0x8(%rsp),%eax
   0x0000000000400f75 <+50>:	jmp    *0x402470(,%rax,8)
   0x0000000000400f7c <+57>:	mov    $0xcf,%eax
   0x0000000000400f81 <+62>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f83 <+64>:	mov    $0x2c3,%eax
   0x0000000000400f88 <+69>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f8a <+71>:	mov    $0x100,%eax
   0x0000000000400f8f <+76>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f91 <+78>:	mov    $0x185,%eax
   0x0000000000400f96 <+83>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f98 <+85>:	mov    $0xce,%eax
   0x0000000000400f9d <+90>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400f9f <+92>:	mov    $0x2aa,%eax
   0x0000000000400fa4 <+97>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400fa6 <+99>:	mov    $0x147,%eax
   0x0000000000400fab <+104>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400fad <+106>:	call   0x40143a <explode_bomb>
   0x0000000000400fb2 <+111>:	mov    $0x0,%eax
   0x0000000000400fb7 <+116>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400fb9 <+118>:	mov    $0x137,%eax
   0x0000000000400fbe <+123>:	cmp    0xc(%rsp),%eax
   0x0000000000400fc2 <+127>:	je     0x400fc9 <phase_3+134>
   0x0000000000400fc4 <+129>:	call   0x40143a <explode_bomb>
   0x0000000000400fc9 <+134>:	add    $0x18,%rsp
   0x0000000000400fcd <+138>:	ret    
End of assembler dump.
```

Phase 3 use sscanf() to retrieve user input, by looking at $0x4025cf (-- format, the second argument of sscanf()) we know that our input should have the form "%d %d":

```shell
(gdb) x /s 0x4025cf
0x4025cf:	"%d %d"
```

Then followed by a switch statement with its jump table stored at 0x402470:

```shell
(gdb) x /8gx 0x402470
0x402470:	0x0000000000400f7c	0x0000000000400fb9
0x402480:	0x0000000000400f83	0x0000000000400f8a
0x402490:	0x0000000000400f91	0x0000000000400f98
0x4024a0:	0x0000000000400f9f	0x0000000000400fa6
```
- If %rax == 0, then it will jump to 0x400f7c, which checks if the second user input equals $0xcf (207);
- If %rax == 1, then it wiil jump to 0x400fb9, which checks if the second user input equals $0x137 (311).

So on and so forth.

Answer: (any of them is ok.)

| Input 1 | Input 2 | Input 1 | Input 2 |
|:-------:|:-------:|:-------:|:-------:|
| 0 | 207 | 4 | 389 |
| 1 | 311 | 5 | 206 |
| 2 | 707 | 6 | 682 |
| 3 | 256 | 7 | 327 |

## Phase 4

Use gdb command `disassemble` to dump assembler code for function phase_4:

```shell
(gdb) disassemble phase_4
Dump of assembler code for function phase_4:
   0x000000000040100c <+0>:	sub    $0x18,%rsp
   0x0000000000401010 <+4>:	lea    0xc(%rsp),%rcx
   0x0000000000401015 <+9>:	lea    0x8(%rsp),%rdx
   0x000000000040101a <+14>:	mov    $0x4025cf,%esi
   0x000000000040101f <+19>:	mov    $0x0,%eax
   0x0000000000401024 <+24>:	call   0x400bf0 <__isoc99_sscanf@plt>
   0x0000000000401029 <+29>:	cmp    $0x2,%eax
   0x000000000040102c <+32>:	jne    0x401035 <phase_4+41>
   0x000000000040102e <+34>:	cmpl   $0xe,0x8(%rsp)
   0x0000000000401033 <+39>:	jbe    0x40103a <phase_4+46>
   0x0000000000401035 <+41>:	call   0x40143a <explode_bomb>
   0x000000000040103a <+46>:	mov    $0xe,%edx
   0x000000000040103f <+51>:	mov    $0x0,%esi
   0x0000000000401044 <+56>:	mov    0x8(%rsp),%edi
   0x0000000000401048 <+60>:	call   0x400fce <func4>
   0x000000000040104d <+65>:	test   %eax,%eax
   0x000000000040104f <+67>:	jne    0x401058 <phase_4+76>
   0x0000000000401051 <+69>:	cmpl   $0x0,0xc(%rsp)
   0x0000000000401056 <+74>:	je     0x40105d <phase_4+81>
   0x0000000000401058 <+76>:	call   0x40143a <explode_bomb>
   0x000000000040105d <+81>:	add    $0x18,%rsp
   0x0000000000401061 <+85>:	ret    
End of assembler dump.
```

Phase 4 use sscanf() to retrieve user input, by looking at $0x4025cf (-- format, the second argument of sscanf()) we know that our input should have the form "%d %d", denoted by `num1` and `num2`:

```shell
(gdb) x /s 0x4025cf
0x4025cf:	"%d %d"
```

We know these two numbers are stored on stack by looking:

```shell
0x401010 <+4>:	lea    0xc(%rsp),%rcx
0x401015 <+9>:	lea    0x8(%rsp),%rdx
```

Then the program compare `num1` to $0xe (at inst `0x40102e <+34>`). If `num1` is less than or equal to 14 ($0xe), then `func4` is called.

The function `func4` has three arguments: num1 (%rdi), 0 (%rsi), 14, (%rdx). The code of `func4` is as follows:

```shell
Dump of assembler code for function func4:
   0x0000000000400fce <+0>:	sub    $0x8,%rsp
   0x0000000000400fd2 <+4>:	mov    %edx,%eax
   0x0000000000400fd4 <+6>:	sub    %esi,%eax
   0x0000000000400fd6 <+8>:	mov    %eax,%ecx
   0x0000000000400fd8 <+10>:	shr    $0x1f,%ecx
   0x0000000000400fdb <+13>:	add    %ecx,%eax
   0x0000000000400fdd <+15>:	sar    %eax
   0x0000000000400fdf <+17>:	lea    (%rax,%rsi,1),%ecx
   0x0000000000400fe2 <+20>:	cmp    %edi,%ecx
   0x0000000000400fe4 <+22>:	jle    0x400ff2 <func4+36>
   0x0000000000400fe6 <+24>:	lea    -0x1(%rcx),%edx
   0x0000000000400fe9 <+27>:	call   0x400fce <func4>
   0x0000000000400fee <+32>:	add    %eax,%eax
   0x0000000000400ff0 <+34>:	jmp    0x401007 <func4+57>
   0x0000000000400ff2 <+36>:	mov    $0x0,%eax
   0x0000000000400ff7 <+41>:	cmp    %edi,%ecx
   0x0000000000400ff9 <+43>:	jge    0x401007 <func4+57>
   0x0000000000400ffb <+45>:	lea    0x1(%rcx),%esi
   0x0000000000400ffe <+48>:	call   0x400fce <func4>
   0x0000000000401003 <+53>:	lea    0x1(%rax,%rax,1),%eax
   0x0000000000401007 <+57>:	add    $0x8,%rsp
   0x000000000040100b <+61>:	ret    
End of assembler dump.
```

It's quite hard to reverse engineer the recursive function `func4`. Instead of doing so, let's look the rest of the `phase4` code. Inst `0x401051 <+69>` requires `num2` to be zero, and as mentioned before, `num1` is less than or equal to 14. It's quite obvious that we can try all 14 possible non-negative number of `num1`.

Answer: 1 0 or 3 0 and maybe more.
