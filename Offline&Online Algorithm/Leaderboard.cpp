#include "Leaderboard.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>

/**
 * @brief Constructor for RankingResult with top players, cutoffs, and elapsed time.
 *
 * @param top Vector of top-ranked Player objects, in sorted order.
 * @param cutoffs Map of player count thresholds to minimum level cutoffs.
 *   NOTE: This is only ever non-empty for Online::rankIncoming().
 *         This parameter & the corresponding member should be empty
 *         for all Offline algorithms.
 * @param elapsed Time taken to calculate the ranking, in seconds.
 */
RankingResult::RankingResult(const std::vector<Player> &top, const std::unordered_map<size_t, size_t> &cutoffs, double elapsed)
    : top_{top}, cutoffs_{cutoffs}, elapsed_{elapsed}
{
}
// Task 1 (Offline)
// HeapRank 1 (A)
RankingResult Offline::heapRank(std::vector<Player> &players)
{
    auto start = std::chrono::steady_clock::now();
    size_t k = std::floor(0.1 * players.size());
    if (k == 0 || players.empty())
    {
        return RankingResult({}, {}, 0);
    }
    // Make heap here(max-heap)
    std::make_heap(players.begin(), players.end());
    // top k elements
    for (size_t i = 0; i < k; i++)
    {
        std::pop_heap(players.begin(), players.end() - i);
    }
    std::vector<Player> top(players.end() - k, players.end());
    auto end = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
    return RankingResult(top, {}, elapsed);
}
// QuickSelectRank (B)
namespace Offline
{
    template <typename It>
    It partition(It begin, It end)
    {
        It pivot = end - 1;
        It i = begin;
        for (It j = begin; j != pivot; ++j)
        {
            if (j->level_ >= pivot->level_)
            {
                std::iter_swap(i, j);
                ++i;
            }
        }
        std::iter_swap(i, pivot);
        return i;
    }
    template <typename It>
    void quickselect(It begin, It end, size_t k)
    {
        while (end - begin > 1)
        {
            It pivot = partition(begin, end);
            size_t dist = pivot - begin;

            if (dist == k)
                return;
            else if (dist < k)
            {
                begin = pivot + 1;
                k -= dist + 1;
            }
            else
            {
                end = pivot;
            }
        }
    }
}
RankingResult Offline::quickSelectRank(std::vector<Player> &players)
{
    auto start = std::chrono::steady_clock::now();
    size_t k = std::floor(0.1 * players.size());
    if (k == 0 || players.empty())
    {
        return RankingResult({}, {}, 0);
    }
    size_t topIndex = k - 1;
    Offline::quickselect(players.begin(), players.end(), topIndex);
    // top elements in ascending order
    std::sort(players.begin(), players.begin() + k, [](const Player &a, const Player &b)
              { return a.level_ < b.level_; });
    std::vector<Player> top(players.begin(), players.begin() + k);
    auto end = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
    return RankingResult(top, {}, elapsed);
}

// TASK 2 (Online)
// replaceMin (B)
void Online::replaceMin(PlayerIt first, PlayerIt last, Player &target)
{
    if (first == last)
        return;
    *first = std::move(target);
    auto heap_end = last;
    auto parent = first;
    while (true)
    {
        auto left = parent + (parent - first) + 1;
        auto right = left + 1;
        if (left >= heap_end)
            break;

        auto minChild = left;
        if (right < heap_end && *right < *left)
        {
            minChild = right;
        }
        if (*minChild < *parent)
        {
            std::iter_swap(parent, minChild);
            parent = minChild;
        }
        else
        {
            break;
        }
    }
}
/**
 * @brief Exhausts a stream of Players (ie. until there are none left) such that we:
 * 1) Maintain a running collection of the <reporting_interval> highest leveled players
 * 2) Record the Player level after reading every <reporting_interval> players
 * representing the minimum level required to be in the leaderboard at that point.
 *
 * @note You should use NOT use a priority-queue.
 * Instead, use a vector, the STL heap operations, & `replaceMin()`
 *
 * @param stream A stream providing Player objects
 * @param reporting_interval The frequency at which to record cutoff levels
 * @return A RankingResult in which:
 * - top_ -> Contains the top <reporting_interval> Players read in the stream in
 * sorted (least to greatest) order
 * - cutoffs_ -> Maps player count milestones to minimum level required at that point
 * including the minimum level after ALL players have been read, regardless
 * of being a multiple of the reporting interval
 * - elapsed_ -> Contains the duration (ms) of the selection/sorting operation
 * excluding fetching the next player in the stream
 *
 * @post All elements of the stream are read until there are none remaining.
 *
 * @example Suppose we have:
 * 1) A stream with 132 players
 * 2) A reporting interval of 50
 *
 * Then our resulting RankingResult might contain something like:
 * top_ = { Player("RECLUSE", 994), Player("WYLDER", 1002), ..., Player("DUCHESS", 1399) }, wi
 * cutoffs_ = { 50: 239, 100: 992, 132: 994 } (see RankingResult explanation)
 * elapsed_ = 0.003 (Your runtime will vary based on hardware)
 */

// rankIncoming (C)
RankingResult Online::rankIncoming(PlayerStream &stream, const size_t &reporting_interval)
{
    auto start = std::chrono::steady_clock::now();
    std::vector<Player> heap;
    std::unordered_map<size_t, size_t> cutoffs;
    size_t count = 0;
    while (stream.remaining() > 0)
    {
        Player p = stream.nextPlayer();
        ++count;
        if (heap.size() < reporting_interval)
        {
            heap.push_back(p);
            std::push_heap(heap.begin(), heap.end(), std::greater<>{});
        }
        else if (p.level_ > heap.front().level_)
        {
            replaceMin(heap.begin(), heap.end(), p);
            std::make_heap(heap.begin(), heap.end(), std::greater<>{});
        }
        if (count % reporting_interval == 0)
        {
            cutoffs[count] = heap.front().level_;
        }
    }
    if (count % reporting_interval != 0)
    {
        cutoffs[count] = heap.front().level_;
    }
    std::sort(heap.begin(), heap.end());
    auto end = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
    return RankingResult(heap, cutoffs, elapsed);
}
