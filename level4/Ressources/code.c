int __cdecl p(char *format)
{
  return printf(format);
}

int n()
{
  int result; 
  char s[520]; 

  fgets(s, 512, stdin);
  p(s);
  result = m;
  if ( m == 16930116 )
    return system("/bin/cat /home/user/level5/.pass");
  return result;
}

int __cdecl main(int argc, const char **argv, const char **envp)
{
  return n();
}