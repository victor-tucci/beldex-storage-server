#pragma once

#include <functional>
#include <string>
#include <vector>

namespace beldex {

struct message;

inline constexpr size_t SERIALIZATION_BATCH_SIZE = 9'000'000;

// Old serialization format; deprecated and to be removed after 2.2.0 is univeral.
inline constexpr uint8_t SERIALIZATION_VERSION_OLD = 0;

// Newer serialization version based on bt-encoding.
inline constexpr uint8_t SERIALIZATION_VERSION_BT = 1;

std::vector<std::string> serialize_messages(std::function<const message*()> next_msg, uint8_t version);

template <typename It>
std::vector<std::string> serialize_messages(It begin, It end, uint8_t version) {
    return serialize_messages([&begin, &end]() mutable -> const message* {
        return begin == end ? nullptr : &*begin++;
    }, version);
}

std::vector<message> deserialize_messages(std::string_view blob);

} // namespace beldex
