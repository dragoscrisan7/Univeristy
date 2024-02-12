bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit , printf, scanf, fopen, fclose, fprintf, fread              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
import scanf msvcrt.dll

import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fread msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    formatfo db "w", 0
    file_name db "LeFisier.txt", 0
    file_descriptor dd -1
    cuvant times 20 db 0
    formatcuv db "%s", 0
    formatw db "%u", 0
    msg db "mesaj", 0
    ent db " ", 0

;A file name (defined in data segment) is given. Create a file with the given name, then read words from the keyboard until character '$' is read from the keyboard. 
;Write only the words that contain at least one digit to file.
; our code starts here
segment code use32 class=code
    start:   
        ;fopen("LeFisier.txt", "w")
        push dword formatfo
        push file_name
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax
        
        cmp eax, 0
        je final
        
        repeta:
        
        ;scanf("%d", &n)
        push dword cuvant
        push dword formatcuv
        call [scanf]
        add esp, 4*2
        
        mov cl, byte [cuvant]
        cmp cl, '$'
        je dupa
        
        mov ebx, 0
        mov ecx, 20
        
        parcuv:
        mov al, byte [cuvant + ebx]
        inc ebx
        
        cmp al, 0
        je repeta
        
        cmp al, '0'
        jl next_char
        
        cmp al, '9'
        jg next_char
        
        ; display the number of chars we've read and the text
        ; printf(file_descriptor, format, eax)
        push dword cuvant
        push dword formatcuv
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3
        
        push dword ent 
        push dword formatcuv
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3
        
        jmp repeta
        
        next_char:
        
        
        
        loop parcuv
        
        jmp repeta
        dupa:
        

        
        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        
        final:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
