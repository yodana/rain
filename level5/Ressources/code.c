void __noreturn o()
{
  system("/bin/sh");
  _exit(1);
}

void __noreturn n()
{
  char s[520]; 

  fgets(s, 512, stdin);
  printf(s);
  exit(1);
}

int __cdecl __noreturn main(int argc, const char **argv, const char **envp)
{
  n();
}
