
; Put comment home
extrn ExitProcess:proc

.CODE

main PROC 
  xor rcx, rcx
  call ExitProcess
main ENDP

END

; compile with:
; ml64 /c hello.asm
;
; link with:
; LINK hello.obj kernel32.lib user32.lib /OUT:hello.exe /ENTRY:main
