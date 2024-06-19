bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fscanf, fprintf, printf          ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fclose msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fprintf msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    filename db "fisier.txt", 0
    accesmode db "r", 0
    filedescripter dd 0
    numere resd 100
    format db "%x", 0
    lungime db 0
    formatprint db "%x ", 0

; our code starts here
;A string of doublewords is given. Order in decreasing order the string of the 
;low words (least significant) from these doublewords. The high words (most significant) remain unchanged.
segment code use32 class=code
    start:
        ; ...
        ;fopen(filename, "r")
        push dword accesmode
        push dword filename
        call [fopen]
        add esp, 4*2
        
        mov dword [filedescripter], eax
        cmp eax, 0
        je end_program
        
        mov edi, dword numere
        mov ebx, 0
        while_citit:
        push ebx
        push edi
        ;fscanf(filedescripter, format, variabila) 
            push dword edi
            push dword format
            push dword [filedescripter]
            call [fscanf]
            add esp, 4*3
            pop edi
            pop ebx
            
            cmp eax, -1
            je end_while
            
            add edi, 4
            add ebx, 4
            
            jmp while_citit
        end_while:
        mov [lungime], ebx
        ;fclose(filedescripter)
        push dword [filedescripter]
        call [fclose]
        add esp, 4
        
        mov esi, 0
        mov edi, dword numere
        while_sortare:
            cmp [lungime], esi
            je end_sortare
        
            mov eax, [edi+esi]
            push esi
            add esi, 4
            while_parcurgere:
                cmp [lungime], esi
                je end_parcurgere
                
                mov ebx, [edi+esi]
                cmp eax, ebx
                jl higher
                    mov ecx, eax
                    mov eax, ebx
                    mov ebx, ecx   
                higher:
                mov [edi+esi], ebx
                
                add esi, 4
                jmp while_parcurgere
                end_parcurgere:
            pop esi
            mov [edi+esi], eax
           
            add esi, 4
            jmp while_sortare
            end_sortare:
        end_program:
        
        mov esi, 0
        while_afisare:
            cmp [lungime], esi
            je end_afisare
        
            mov eax, [edi+esi]
            add esi, 4
            push esi
            ;printf(format, variabila)
            push dword eax
            push dword formatprint
            call [printf]
            add esp, 4*2
            
            pop esi
            jmp while_afisare
        end_afisare:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
