char *p()
{
  char s[64]; 
  const void *v2; 
  unsigned int retaddr; 

  fflush(stdout);
  gets(s);
  v2 = (const void *)retaddr;
  if ( (retaddr & 0xB0000000) == -1342177280 )
  {
    printf("(%p)\n", v2);
    _exit(1);
  }
  puts(s);
  return strdup(s);
}

//----- (0804853F) --------------------------------------------------------
int main(int argc, const char **argv, const char **envp)
{
  return (int)p();
}
