#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <array>
#include <optional>
#include <vector>
#include <algorithm>

// ---------------------------------------------------------------------------
const std::string currentTime() {
	std::time_t time_now = std::time(nullptr);
	std::stringstream ss;
	ss << std::put_time(std::localtime(&time_now), "[%H:%M:%S]");
	return ss.str();
}

std::string AddrToHexString(uintptr_t addr) {
	std::stringstream ss;
	ss << "0x" << std::uppercase << std::hex << addr;
	return ss.str();
}

template <std::size_t N>
uint8_t* find_signature(const char(&signature)[N], uint8_t* start, std::size_t size) {
	auto split_fn = [](const std::string& to_split, char delim = ' ') -> std::vector<std::string> {
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream token_stream{ to_split };
		while (std::getline(token_stream, token, delim))
			tokens.push_back(token);
		return tokens;
	};
	std::array<std::optional<uint8_t>, N> bytes{};
	auto split_signature = split_fn(signature);
	static constexpr auto wildcard = '?';
	std::transform(split_signature.cbegin(), split_signature.cend(), bytes.begin(),
		[](const std::string& str_hex_val) -> std::optional<uint8_t> {
			return str_hex_val.find(wildcard) == std::string::npos ? std::optional{ std::stoi(str_hex_val, 0, 16) } : std::nullopt;
		});
	auto end = start + size;
	auto found = std::search(start, end, bytes.cbegin(), bytes.cend(),
		[](uint8_t memory_byte, std::optional<uint8_t> signature_byte) -> bool {
			return signature_byte.value_or(memory_byte) == memory_byte;
		});
	uint8_t* result = (found != end ? found : nullptr);
	return result;
}

MODULEINFO GetModuleInfo(const char* szModule) {
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandle(szModule);
	if (hModule == 0)
		return modinfo;
	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}