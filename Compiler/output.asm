.data 
x dw 0
.code 
func0: 
push ebp
mov ebp, esp
sub esp, 0ffh
push ebx
push esi
push edi
lea edi, [ebp-0ffh]
mov eax, d [ebp+08h]
add eax, d [ebp+04h]
mov d [ebp-04h], eax
mov eax, d [ebp-04h]
pop edi
pop esi
pop ebx
add esp, 0ffh
pop ebp
ret
start: 
push ebp
mov ebp, esp
sub esp, 0ffh
push ebx
push esi
push edi
lea edi, [ebp-0ffh]
mov d [ebp-01ch], 10
mov d [ebp-020h], 5
mov ebx, d [ebp-028h]
imul ebx, d [ebp-01ch]
mov d [ebp-02ch], ebx
add ebx, 5
mov d [ebp-030h], ebx
mov d [ebp-0ch], 1
mov eax, d [ebp-024h]
and eax, eax
jz >label0
add ebx, 1
mov d [ebp-034h], ebx
label0: 
push 1
push 2
jmp func0
add esp, 8
mov d [ebp-038h], eax
mov eax, d [ebp-038h]
mov d [ebp-018h], eax
mov eax, d [ebp-03ch]
pop edi
pop esi
pop ebx
add esp, 0ffh
pop ebp
ret
