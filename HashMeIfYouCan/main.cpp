#include "Compare.hpp"
#include "Inventory.hpp"
#include "ItemGenerator.hpp"
#include "TreeInventory.hpp"
#include <chrono>
#include <iomanip>
#include <vector>
#include <iostream>
#include <list>

// Task 4 Part A
// Going to use template function to measure the contains() time
template <typename InventoryType>
float measureTimeofContains(size_t n)
{
    ItemGenerator gen(42);
    InventoryType invent;
    for (size_t i = 0; i < n; ++i)
    {
        invent.pickup(gen.randomItem());
    }
    std::vector<std::string> contained, missing;
    for (int i = 0; i < 100; ++i)
    {
        contained.push_back(gen.randomUsedName());
    }
    for (int i = 0; i < 100; ++i)
    {
        missing.push_back(gen.randomItem().name_);
    }

    std::vector<std::string> testNames(contained);
    testNames.insert(testNames.end(), missing.begin(), missing.end());
    float total = 0.0f;
    for (const auto &name : testNames)
    {
        auto start = std::chrono::high_resolution_clock::now();
        invent.contains(name);
        auto end = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<float, std::milli>(end - start).count();
    }
    return total / 200.0f;
}
// Part B
// CompareItemName test
// Now going to do the template for the query() with CompareItemName
template <typename InventoryType>
float queryMeasure_TimeName(size_t n)
{
    ItemGenerator gen(42);
    InventoryType invent;
    for (size_t i = 0; i < n; ++i)
    {
        invent.pickup(gen.randomItem());
    }
    float total = 0.0f;
    for (int i = 0; i < 10; ++i)
    {
        std::string firstName = gen.randomUsedName();
        std::string secondName = gen.randomUsedName();
        if (firstName > secondName)
            std::swap(firstName, secondName);
        Item start(firstName, 0.0f, NONE);
        Item end(secondName, 0.0f, NONE);
        auto start_time = std::chrono::high_resolution_clock::now();
        invent.query(start, end);
        auto end_time = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<float, std::milli>(end_time - start_time).count();
    }
    return total / 10.0f;
}

// COmpareItemWeight test
// And the template for query() with COmpareItemWeight goes here
template <typename InventoryType>
float queryMeasure_TimeWeight(size_t n)
{
    ItemGenerator gen(42);
    InventoryType invent;
    for (size_t i = 0; i < n; ++i)
    {
        invent.pickup(gen.randomItem());
    }
    float total = 0.0f;
    for (int i = 0; i < 10; ++i)
    {
        float someWeight = gen.randomFloat(ItemGenerator::MIN_WEIGHT, ItemGenerator::MAX_WEIGHT);
        Item start("Start", someWeight, NONE);
        Item end("End", someWeight + 0.1f, NONE);
        auto start_time = std::chrono::high_resolution_clock::now();
        invent.query(start, end);
        auto end_time = std::chrono::high_resolution_clock::now();
        total += std::chrono::duration<float, std::milli>(end_time - start_time).count();
    }
    return total / 10.0f;
}

// Now lets get everything in tables
int main()
{

    std::vector<size_t> ns = {1000, 2000, 4000, 8000};
    std::cout << std::fixed << std::setprecision(4); // 4 decimals place
    // Part A
    std::cout << "Part A: Contains Timing:\n";
    std::cout << "| n      |  Vectors |  List  |  Hash  |  Tree  |\n";
    std::cout << "|________|__________|________|________|________|\n";
    for (size_t n : ns)
    {
        float vec = measureTimeofContains<Inventory<CompareItemName>>(n);
        float lis = measureTimeofContains<Inventory<CompareItemName, std::list<Item>>>(n);
        float hash = measureTimeofContains<Inventory<CompareItemName, std::unordered_set<Item>>>(n);
        float tree = measureTimeofContains<Inventory<CompareItemName, Tree>>(n);
        std::cout << "| " << n << " | " << vec << " | " << lis << " | " << hash << " | " << tree << " |\n";
    }

    // Part B

    std::cout << "Part B: Query Timing (name):\n";
    std::cout << "| n      |  Vectors |  List  |  Hash  |  Tree  |\n";
    std::cout << "|________|__________|________|________|________|\n";
    for (size_t n : ns)
    {
        float vec = queryMeasure_TimeName<Inventory<CompareItemName>>(n);
        float lis = queryMeasure_TimeName<Inventory<CompareItemName, std::list<Item>>>(n);
        float hash = queryMeasure_TimeName<Inventory<CompareItemName, std::unordered_set<Item>>>(n);
        float tree = queryMeasure_TimeName<Inventory<CompareItemName, Tree>>(n);
        std::cout << "| " << n << " | " << vec << " | " << lis << " | " << hash << " | " << tree << " |\n";
    }

    std::cout << "Part B: Query Timing (weight):\n";
    std::cout << "| n      |  Vectors |  List  |  Hash  |  Tree  |\n";
    std::cout << "|________|__________|________|________|________|\n";
    for (size_t n : ns)
    {
        float vec = queryMeasure_TimeWeight<Inventory<CompareItemWeight>>(n);
        float lis = queryMeasure_TimeWeight<Inventory<CompareItemWeight, std::list<Item>>>(n);
        float hash = queryMeasure_TimeWeight<Inventory<CompareItemWeight, std::unordered_set<Item>>>(n);
        float tree = queryMeasure_TimeWeight<Inventory<CompareItemWeight, Tree>>(n);
        std::cout << "| " << n << " | " << vec << " | " << lis << " | " << hash << " | " << tree << " |\n";
    }

    return 0;
}
