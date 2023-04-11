int __cdecl greetuser(char src)
{
  __int128 dest; 
  __int16 v3; 
  char v4; 

  switch ( language )
  {
    case 1:
      dest = xmmword_8048717;
      v3 = *((_WORD *)&xmmword_8048717 + 8);
      v4 = *((_BYTE *)&xmmword_8048717 + 18);
      break;
    case 2:
      strcpy((char *)&dest, "Goedemiddag! ");
      break;
    case 0:
      strcpy((char *)&dest, "Hello ");
      break;
  }
  strcat((char *)&dest, &src);
  return puts((const char *)&dest);
}

int __cdecl main(int argc, const char **argv, const char **envp)
{
  char v4[76]; 
  char dest[76];
  char *v6; 

  if ( argc != 3 )
    return 1;
  memset(dest, 0, sizeof(dest));
  strncpy(dest, argv[1], 0x28u);
  strncpy(&dest[40], argv[2], 0x20u);
  v6 = getenv("LANG");
  if ( v6 )
  {
    if ( !memcmp(v6, "fi", 2u) )
    {
      language = 1;
    }
    else if ( !memcmp(v6, "nl", 2u) )
    {
      language = 2;
    }
  }
  qmemcpy(v4, dest, sizeof(v4));
  return greetuser(v4[0]);
}