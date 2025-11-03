#include <benchmark/benchmark.h>
#include <numeric>
#include <vector>

template<typename T> static void test(benchmark::State &state)
{
    std::vector<T> v(1'000'000);
    std::iota(v.begin(), v.end(), T{0});
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(
            std::accumulate(v.begin(), v.end(), T{0}));
    }
}

BENCHMARK(test<uint8_t>);
BENCHMARK(test<int8_t>);
BENCHMARK(test<uint16_t>);
BENCHMARK(test<int16_t>);
BENCHMARK(test<uint32_t>);
BENCHMARK(test<int32_t>);
BENCHMARK(test<uint64_t>);
BENCHMARK(test<int64_t>);

BENCHMARK_MAIN();
