#include "PlayerStream.hpp"
#include <stdexcept>

// Not extra credit implementation here
// PlayerStream::~PlayerStream() = default;
VectorPlayerStream::VectorPlayerStream(const std::vector<Player> &players) : players_(players), current_idx_(0) {}

Player VectorPlayerStream::nextPlayer()
{
    if (current_idx_ >= players_.size())
    {
        throw std::runtime_error("No more players");
    }
    return players_[current_idx_++];
}
size_t VectorPlayerStream::remaining() const
{
    return players_.size() - current_idx_;
}

// I'm gonna try the extra credit here
// API implementation
#ifdef API_ENABLED
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

APIPlayerStream::APIPlayerStream(const size_t &expected_length, const size_t &seed, const size_t &batch_size)
    : expected_length_(expected_length), seed_(seed), batch_size_(batch_size), cursor_(1), total_remaining_(expected_length), current_batch_(0) {}

void APIPlayerStream::fetchNextBatch()
{
    // API URL first
    const std::string url = "http://127.0.0.1:5000/api?seed=" + std::to_string(seed_) + "&cursor=" + std::to_string(cursor_) + "&batch=" + std::to_string(batch_size_);
    // API request second
    cpr::Response response = cpr::Get(cpr::Url{url});
    if (response.status_code != 200)
    {
        throw std::runtime_error("API request failed, status: " + std::to_string(response.status_code));
    }
    // Parse Json here
    nlohmann::json json = nlohmann::json::parse(response.text);
    cursor_ = json["cursor"].template get<size_t>();
    std::vector<size_t> levels = json["levels"].template get<std::vector<size_t>>();

    // levels to become player objs
    current_batch_.clear();
    for (size_t level : levels)
    {
        current_batch_.emplace_back("Player_" + std::to_string(level), level);
    }
    current_batch_pos_ = 0;
}
Player APIPlayerStream::nextPlayer()
{
    if (total_remaining_ == 0)
    {
        throw std::runtime_error("No more players streaming");
    }
    if (current_batch_pos_ >= current_batch_.size())
    {
        fetchNextBatch();
    }
    Player p = current_batch_[current_batch_pos_];
    current_batch_pos_++;
    total_remaining_--;
    return p;
}
size_t APIPlayerStream::remaining() const
{
    return total_remaining_;
}

#endif