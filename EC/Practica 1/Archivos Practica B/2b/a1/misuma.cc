int suma(int* lista, int n)
{
    int suma = 0;
    for (int i = 0; i < n; ++i)
        suma += lista[i];
    return suma;
}

int main()
{
    const int N = 3;
    int lista[] = {1, 2, 3};
    return suma(lista, N);
}
