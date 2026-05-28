#include <benchmark/benchmark.h>
#include <vector>
#include <random>
#include <algorithm>
#include "segment_tree.hpp"

using namespace std;

//algortm Kadane
long long naiveKadane(const vector<long long>& arr) {
    long long max_so_far = MIN_INF;
    long long max_ending_here = 0;
    
    for (long long val : arr) {
        max_ending_here = max(val, max_ending_here + val);
        max_so_far = max(max_so_far, max_ending_here);
    }
    return max_so_far;
}
//segment_tree
static void BM_SegmentTreeDynamic(benchmark::State& state) {
    int n = state.range(0);
    SegmentTree st(n);
    
    //genrator liczb losowych 
    mt19937 gen(42);
    uniform_int_distribution<long long> val_dist(-1000, 1000);
    uniform_int_distribution<int> idx_dist(0, n - 1);

    for (int i = 0; i < n; ++i) {
        st.addElement(val_dist(gen));
    }
    //pomiar
    for (auto _ : state) {
        state.PauseTiming(); 
        int random_idx = idx_dist(gen);
        long long random_val = val_dist(gen);
        state.ResumeTiming(); 

        st.updateElement(random_idx, random_val);
        benchmark::DoNotOptimize(st.queryMaxSubarray(0, n - 1));
    }
    
    state.SetComplexityN(state.range(0));
}
// klasyczny Kadane
static void BM_NaiveKadaneDynamic(benchmark::State& state) {
    int n = state.range(0);
    vector<long long> arr(n);
    //losowe wartosci 
    mt19937 gen(42);
    uniform_int_distribution<long long> val_dist(-1000, 1000);
    uniform_int_distribution<int> idx_dist(0, n - 1);

    for (int i = 0; i < n; ++i) {
        arr[i] = val_dist(gen);
    }

    // Pętla pomiarowa
    for (auto _ : state) {
        state.PauseTiming();
        int random_idx = idx_dist(gen);
        long long random_val = val_dist(gen);
        state.ResumeTiming();
        //podmiana losowego elementu + ponowne przeliczenie
        arr[random_idx] = random_val;
        benchmark::DoNotOptimize(naiveKadane(arr));
    }
    
    state.SetComplexityN(state.range(0));
}
// rozmiary 1000, 10000 ... 1000000 po 10 testow 
BENCHMARK(BM_SegmentTreeDynamic)->RangeMultiplier(10)->Range(1000, 1000000)->Complexity();
BENCHMARK(BM_NaiveKadaneDynamic)->RangeMultiplier(10)->Range(1000, 1000000)->Complexity();

BENCHMARK_MAIN();
