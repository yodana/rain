int32_t main(int32_t argc, char** argv, char** envp)
{
    if (argc > 1)
    {
        int32_t* eax = operator new(0x6c);
        N::N(eax, 5);
        int32_t* eax_1 = operator new(0x6c);
        N::N(eax_1, 6);
        N::setAnnotation(eax, argv[1]);
        return **eax_1(eax_1, eax);
    }
    _exit(1);
    /* no return */
}


int32_t* N::N(int32_t* arg1, int32_t arg2)
{
    *arg1 = 0x8048848;
    arg1[0x1a] = arg2;
    return arg1;
}

int32_t N::setAnnotation(int32_t arg1, size_t arg2)
{
    return memcpy((arg1 + 4), arg2, strlen(arg2));
}

int32_t N::operator+(void* arg1, void* arg2)
{
    return (*(arg2 + 0x68) + *(arg1 + 0x68));
}

int32_t N::operator-(void* arg1, void* arg2)
{
    return (*(arg1 + 0x68) - *(arg2 + 0x68));
}