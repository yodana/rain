int m()
{
  time_t v0; 

  v0 = time(0);
  return printf("%s - %d\n", c, v0);
}

int __cdecl main(int argc, const char **argv, const char **envp)
{
  FILE *v3; 
  void *v5;
  void *v6; 

  v6 = malloc(8u);
  *(_DWORD *)v6 = 1;
  *((_DWORD *)v6 + 1) = malloc(8u);
  v5 = malloc(8u);
  *(_DWORD *)v5 = 2;
  *((_DWORD *)v5 + 1) = malloc(8u);
  strcpy(*((char **)v6 + 1), argv[1]);
  strcpy(*((char **)v5 + 1), argv[2]);
  v3 = fopen("/home/user/level8/.pass", "r");
  fgets(c, 68, v3);
  puts("~~");
  return 0;
}
