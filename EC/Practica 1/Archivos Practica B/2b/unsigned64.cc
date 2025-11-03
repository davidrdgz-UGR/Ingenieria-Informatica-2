#include <cstdio>
#include <tuple>

unsigned long long suma1(unsigned *lista, unsigned longlista)
{
    unsigned long long total = 0;
    for (unsigned i = 0; i < longlista; ++i)
        total += lista[i];
    return total;
}

unsigned long long suma2(unsigned *begin, unsigned *end)
{
    unsigned long long total = 0;
    while (begin != end)
        total += *begin++;
    return total;
}

std::tuple<unsigned long long, unsigned long long>
cociente_y_resto(unsigned long long dividendo, unsigned long long divisor)
{
    return {dividendo / divisor, dividendo % divisor};
}

int main()
{
    unsigned lista[] = {0xffffffff, 0xffffffff};
    unsigned n = sizeof(lista) / sizeof(unsigned);

    printf("lista[%i] = {", n);
    for (auto i: lista)
        printf("%u, ", i);
    printf("\b\b}\n");

    unsigned long long s1 = suma1(lista, n), s2 = suma2(lista, lista + n);

    auto [c1, r1] = cociente_y_resto(s1, n);
    auto [c2, r2] = cociente_y_resto(s2, n);

    printf("suma1=%llu/0x%016llx media=%llu resto=%llu\n", s1, s1, c1, r1);
    printf("suma2=%llu/0x%016llx media=%llu resto=%llu\n", s2, s2, c2, r2);
}
