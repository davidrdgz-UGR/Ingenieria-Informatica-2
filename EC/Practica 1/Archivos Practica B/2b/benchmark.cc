#include <benchmark/benchmark.h>
#include <numeric>
#include <vector>

#if __cplusplus > 202002L
#include <execution>
#include <ranges>
#endif // __cplusplus > 202002L

const std::size_t N = 1'000;
std::vector<int> lista(N, std::numeric_limits<int>::max());

long suma1(int *lista, int longlista)
{
    long total = 0;
    for (int i = 0; i < longlista; ++i)
        total += lista[i];
    return total;
}

template<typename Iterator> long suma2(Iterator begin, Iterator end)
{
    long total = 0;
    while (begin != end)
        total += *begin++;
    return total;
}

template<typename Iterator> long suma3(Iterator begin, Iterator end)
{
    return std::accumulate(begin, end, 0LL);
}

#if __cplusplus > 202002L
template<typename Iterator> long suma4(Iterator begin, Iterator end)
{
    return std::reduce(std::execution::seq, begin, end, 0LL);
}

template<typename Range> long suma5(const Range &range)
{
    return std::ranges::fold_left(range, 0LL, std::plus<long>());
}
#endif // __cplusplus > 202002L

template<auto f> static void test_pointer(benchmark::State &state)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(f(lista.data(), lista.size()));
}

template<auto f> static void test_iterator(benchmark::State &state)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(f(lista.begin(), lista.end()));
}

template<auto f> static void test_range(benchmark::State &state)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(f(lista));
}

BENCHMARK(test_pointer<suma1>);
BENCHMARK(test_iterator<suma2<std::vector<int>::iterator>>);
BENCHMARK(test_iterator<suma3<std::vector<int>::iterator>>);
#if __cplusplus > 202002L
BENCHMARK(test_iterator<suma4<std::vector<int>::iterator>>);
BENCHMARK(test_range<suma5<std::vector<int>>>);
#endif // __cplusplus > 202002L

BENCHMARK_MAIN();
