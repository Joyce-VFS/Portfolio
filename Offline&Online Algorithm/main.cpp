#include "Leaderboard.hpp"
#include "PlayerStream.hpp"
#include <iostream>
#include <random>
// MAIN TO TEST
//  Generate random players for testing
std::vector<Player> generate_random_players(size_t count)
{
    std::vector<Player> players;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> level_dist(1, 1000);

    for (size_t i = 0; i < count; ++i)
    {
        players.emplace_back("Player_" + std::to_string(i), level_dist(gen));
    }
    return players;
}

void test_offline_algorithms()
{
    std::cout << "=== TESTING OFFLINE ALGORITHMS ===\n";
    auto players = generate_random_players(100); // 100 players (10% = top 10)

    // Test heapRank
    auto heap_result = Offline::heapRank(players);
    std::cout << "HeapRank top 10%:\n";
    for (const auto &p : heap_result.top_)
    {
        std::cout << p.name_ << " (Level: " << p.level_ << ")\n";
    }
    std::cout << "Time: " << heap_result.elapsed_ << " ms\n\n";

    // Test quickSelectRank
    auto qs_result = Offline::quickSelectRank(players);
    std::cout << "QuickSelectRank top 10%:\n";
    for (const auto &p : qs_result.top_)
    {
        std::cout << p.name_ << " (Level: " << p.level_ << ")\n";
    }
    std::cout << "Time: " << qs_result.elapsed_ << " ms\n";
}

void test_online_algorithm()
{
    std::cout << "\n=== TESTING ONLINE ALGORITHM ===\n";
    auto players = generate_random_players(132); // 132 players (reporting_interval=50)
    VectorPlayerStream stream(players);

    auto online_result = Online::rankIncoming(stream, 50);

    std::cout << "Top 50 players:\n";
    for (const auto &p : online_result.top_)
    {
        std::cout << p.name_ << " (Level: " << p.level_ << ")\n";
    }

    std::cout << "\nCutoffs:\n";
    for (const auto &[count, level] : online_result.cutoffs_)
    {
        std::cout << "After " << count << " players: Level " << level << "\n";
    }
    std::cout << "Time: " << online_result.elapsed_ << " ms\n";
}

int main()
{
    test_offline_algorithms();
    test_online_algorithm();
    return 0;
}