#pragma once
#include <string>

size_t generate_signature(const std::string& data);
std::string xorEncryptDecrypt(std::string data);
void save_certificate(size_t hash, const std::string& data);
void load_certificate_map();
void validate_certificate();
void write_certificate();
