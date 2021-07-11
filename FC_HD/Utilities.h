#ifndef UTILITIES_H
#define UTILITIES_H
#define ANYTHING 0xFFFF

#include <windows.h>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <Ini/ini.h>


extern std::string current_DDS_name;

struct config {
	
	config(bool sprites,
		bool textures,
		size_t upscale_factor)
	{
		HD_sprites = sprites;
		texture_mod = textures;
		upscaling_factor = upscale_factor;
	}
	config() :config(false, false, 1) {
	}
	bool HD_sprites;
	bool texture_mod;
	size_t upscaling_factor;
};


struct Section {
	unsigned long VirtualAddrStart;
	unsigned long PhysicalAddrStart;
	unsigned long VirtualAddrEnd;
	unsigned long PhysicalAddrEnd;
	std::string name;

	std::vector<BYTE> ToBytes() {
		std::vector<BYTE> result;
		return result;
	}
};
bool exists(const std::string& name);
std::vector<BYTE> number_to_bytes(int c, int nb_bytes); 
int find_section_by_name(std::string name, std::vector<Section> sects);
bool check_at_index(const uint8_t* text, size_t text_size, std::vector<uint16_t> pattern);
ULONG_PTR find_chunk(ULONG_PTR addr, ULONG_PTR end, std::vector<uint16_t> pattern, int number);
ULONG_PTR find_bytes(ULONG_PTR addr, ULONG_PTR end, std::vector<BYTE> pattern, int number);
bool RewriteMemory(ULONG_PTR addr, std::vector<BYTE> BytesToWrite);
bool RewriteMemoryEx(ULONG_PTR addr, std::vector<BYTE> BytesToWrite);
int read_int(void* addr);
BYTE read_byte(void* addr);
std::vector<BYTE> read_bytes_string(ULONG_PTR addr);
std::vector<BYTE> read_array_of_bytes(void* addr, size_t size);
bool LoadConfig(config& parameters);




#endif