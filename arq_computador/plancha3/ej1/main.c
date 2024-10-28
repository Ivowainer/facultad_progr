int b()
{
    return 255;
}

int a()
{
    unsigned char al = 0xFE;
    signed char bl = -1;
    al = al + bl;
    bl = bl + 1;
    return al;
}

int main()
{
    a();
    b();
    return 0;
}