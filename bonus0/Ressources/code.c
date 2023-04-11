char *__cdecl pp(char *dest)
{
  char src[20];
  char v3[28]; 

  p(src, " - ");
  p(v3, " - ");
  strcpy(dest, src);
  *(_WORD *)&dest[strlen(dest)] = unk_80486A4;
  return strcat(dest, v3);
}

int __cdecl main(int argc, const char **argv, const char **envp)
{
  char s[42]; 

  pp(s);
  puts(s);
  return 0;
}
