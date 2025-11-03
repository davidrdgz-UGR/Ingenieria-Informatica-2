#include <cstdio>
#include <tuple>

long long suma1(int *lista, int longlista)
{
    long long total = 0;
    for (int i = 0; i < longlista; ++i)
        total += lista[i];
    return total;
}

long long suma2(int *begin, int *end)
{
    long long total = 0;
    while (begin != end)
        total += *begin++;
    return total;
}

std::tuple<int, int> cociente_y_resto(long long dividendo, int divisor)
{
    return {dividendo / divisor, dividendo % divisor};
}

int main()
{
    // int lista[] = {-1, -1};                 // -1 = 0xffffffff
    int lista[] = {2147483647, 2147483647}; // 2147483647 = 0x7fffffff
    // int lista[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(lista) / sizeof(int);

    printf("lista[%i] = {", n);
    for (auto i: lista)
        printf("%i, ", i);
    printf("\b\b}\n");

    long long s1 = suma1(lista, n), s2 = suma2(lista, lista + n);

    auto [c1, r1] = cociente_y_resto(s1, n);
    auto [c2, r2] = cociente_y_resto(s2, n);

    printf("suma1=%lli/0x%016llx media=%i resto=%i\n", s1, s1, c1, r1);
    printf("suma2=%lli/0x%016llx media=%i resto=%i\n", s2, s2, c2, r2);
}
