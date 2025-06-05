#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <unordered_set>
#include <typeinfo>
#include "Inventory.hpp"
#include "ItemGenerator.hpp"
#include "Compare.hpp"
#include "ItemAVL.hpp"

using namespace std;

// Type alias for Tree implementation
template <class Comparator>
using Tree = ItemAVL<Comparator>;
// ========================
// Timing Functions
// ========================

template <class Comparator, class Container>
float timeContains(Inventory<Comparator, Container> &inv,
                   const vector<string> &names)
{
    auto start = chrono::high_resolution_clock::now();
    for (const auto &name : names)
    {
        inv.contains(name);
    }
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<float, milli>(end - start).count();
}

template <class Comparator, class Container>
float timeQuery(Inventory<Comparator, Container> &inv,
                const Item &start, const Item &end)
{
    auto start_time = chrono::high_resolution_clock::now();
    inv.query(start, end);
    auto end_time = chrono::high_resolution_clock::now();
    return chrono::duration<float, milli>(end_time - start_time).count();
}

// ========================
// Test Helpers
// ========================

template <class Comparator, class Container>
void testContains(size_t n, ItemGenerator &generator,
                  const vector<string> &contained,
                  const vector<string> &missing,
                  const string &label)
{
    // Create and fill inventory
    Inventory<Comparator, Container> inv;
    for (size_t i = 0; i < n; i++)
    {
        inv.pickup(generator.randomItem());
    }

    // Time executions
    float timeContained = timeContains(inv, contained);
    float timeMissing = timeContains(inv, missing);
    float avgTime = (timeContained + timeMissing) / 200.0f;

    // Output results
    cout << "CONTAINS," << label << "," << n << "," << avgTime << endl;
}

template <class Comparator, class Container>
void testQuery(size_t n, ItemGenerator &generator, const string &label)
{
    Inventory<Comparator, Container> inv;
    for (size_t i = 0; i < n; i++)
    {
        inv.pickup(generator.randomItem());
    }

    float totalTime = 0;
    const int numQueries = 10;

    for (int i = 0; i < numQueries; i++)
    {
        if constexpr (is_same_v<Comparator, CompareItemName>)
        {
            // Name query
            auto name1 = generator.randomUsedName();
            auto name2 = generator.randomUsedName();
            Item start(name1, 0.0f, ItemType::None);
            Item end(name2, 0.0f, ItemType::None);
            if (!Comparator::leq(start, end))
                swap(start, end);
            totalTime += timeQuery(inv, start, end);
        }
        else
        {
            // Weight query
            float weight = generator.randomFloat(0.1f, 10.0f);
            Item start("query_start", weight, ItemType::None);
            Item end("query_end", weight + 0.1f, ItemType::None);
            totalTime += timeQuery(inv, start, end);
        }
    }

    cout << "QUERY," << label << "," << n << ","
         << (totalTime / numQueries) << endl;
}

// ========================
// Main Test Runner
// ========================

void runPerformanceTests()
{
    const vector<size_t> test_sizes = {1000, 2000, 4000, 8000};
    const int seed = 42;

    // CSV header
    cout << "TEST_TYPE,CONTAINER_TYPE,N,AVG_TIME_MS" << endl;

    // Part A: contains() tests
    for (auto n : test_sizes)
    {
        ItemGenerator generator(seed);
        vector<string> contained, missing;

        // Generate test data
        for (int i = 0; i < 100; i++)
        {
            contained.push_back(generator.randomUsedName());
            missing.push_back(ItemGenerator(seed + 1).randomUsedName());
        }

        // Test each container type
        testContains<CompareItemName, vector<Item>>(n, generator, contained, missing, "VECTOR");
        testContains<CompareItemName, list<Item>>(n, generator, contained, missing, "LIST");
        testContains<CompareItemName, unordered_set<Item>>(n, generator, contained, missing, "HASH");
        testContains<CompareItemName, Tree>(n, generator, contained, missing, "TREE");
    }

    // Part B: query() tests
    for (auto n : test_sizes)
    {
        ItemGenerator generator(seed);

        // Name queries
        testQuery<CompareItemName, vector<Item>>(n, generator, "VECTOR_NAME");
        testQuery<CompareItemName, list<Item>>(n, generator, "LIST_NAME");
        testQuery<CompareItemName, unordered_set<Item>>(n, generator, "HASH_NAME");
        testQuery<CompareItemName, Tree>(n, generator, "TREE_NAME");

        // Weight queries
        testQuery<CompareItemWeight, vector<Item>>(n, generator, "VECTOR_WEIGHT");
        testQuery<CompareItemWeight, list<Item>>(n, generator, "LIST_WEIGHT");
        testQuery<CompareItemWeight, unordered_set<Item>>(n, generator, "HASH_WEIGHT");
        testQuery<CompareItemWeight, Tree>(n, generator, "TREE_WEIGHT");
    }
}

int main()
{
    runPerformanceTests();
    return 0;
}