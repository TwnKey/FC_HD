#include "utilities.h"
#include <iostream>


int find_section_by_name(std::string name, std::vector<Section> sects) {
	for (size_t idx_sect = 0; idx_sect < sects.size(); idx_sect++) {
		if (sects[idx_sect].name == name) {
			return idx_sect;
		}
	}
	return -1;

}

std::vector<BYTE> number_to_bytes(int c, int nb_bytes) {
	std::vector<BYTE> res;
	for (int i = 0; i < nb_bytes; i++) {
		res.push_back((c & (0xff << (8 * i))) >> (8 * i));
	}
	return res;

}


bool check_at_index(const uint8_t* text, size_t text_size, std::vector<uint16_t> pattern)
{
	size_t pattern_index = 0;

	for (size_t i = 0; i < text_size; i++)
	{
		if (pattern[pattern_index] == ANYTHING)
		{
			pattern_index++;
			continue;
		}

		if (text[i] != pattern[pattern_index]) return false;

		pattern_index++;
	}

	return true;
}

bool check_at_index_byte(const uint8_t* text, size_t text_size, std::vector<BYTE> pattern)
{
	size_t pattern_index = 0;
	
	for (size_t i = 0; i < text_size; i++)
	{
		
		if (text[i] != pattern[pattern_index]) return false;

		pattern_index++;
	}

	return true;
}

ULONG_PTR find_chunk(ULONG_PTR addr, ULONG_PTR end, std::vector<uint16_t> pattern, int number)
{
	int size = pattern.size();
	int cnt = 1;
	ULONG_PTR addr_patt = addr;
	for (addr_patt = addr; addr_patt < end - size; addr_patt++) {
		if (check_at_index((const uint8_t*)addr_patt, size, pattern)) {
			if (cnt == number) {
				return addr_patt;
			}
			cnt++;
		}
	}
	return -1;
}
ULONG_PTR find_bytes(ULONG_PTR addr, ULONG_PTR end, std::vector<BYTE> pattern, int number) {
	int size = pattern.size();
	int cnt = 1;
	ULONG_PTR addr_patt = addr;
	
	for (addr_patt = addr; addr_patt < end - size; addr_patt++) {
		
		if (check_at_index_byte((const uint8_t*)addr_patt, size, pattern)) {
			if (cnt == number) {
				return addr_patt;
			}
			cnt++;
		}
	}
	return -1;
}

bool RewriteMemoryEx(ULONG_PTR addr, std::vector<BYTE> BytesToWrite) {
	DWORD dwProtect, dwProtect2;
	//std::cout << std::hex << "Writing at : " << addr << std::endl;
	if (VirtualProtect((LPVOID)addr, BytesToWrite.size(), PAGE_EXECUTE_READWRITE, &dwProtect)) {
		unsigned char * addr_bytes_to_write = BytesToWrite.data();
		memcpy((void*)addr, addr_bytes_to_write, BytesToWrite.size());
		VirtualProtect((LPVOID) addr, BytesToWrite.size(), dwProtect, &dwProtect2);
		return true;
	}
	else return false;
}
bool RewriteMemory(ULONG_PTR addr, std::vector<BYTE> BytesToWrite) {
	unsigned char* addr_bytes_to_write = BytesToWrite.data();
	memcpy((void*)addr, addr_bytes_to_write, BytesToWrite.size());
		
	return true;
	
}



int read_int(void * addr) {
	int res;
	memcpy(&res, addr, 4);
	return res;
}
std::vector<BYTE> read_bytes_string(ULONG_PTR addr) {
	std::vector<BYTE> res;
	BYTE b;
	memcpy(&b, (void*)addr, 1);
	int cnt = 0;
	while (b != 0) {
		res.push_back(b);
		cnt++;
		memcpy(&b, (void*)(addr + cnt), 1);
	}
	res.push_back(0);
	return res;
}

BYTE read_byte(void* addr) {
	BYTE res;
	memcpy(&res, addr, 1);
	return res;
}

std::vector<BYTE> read_array_of_bytes(void* addr, size_t size) {
	std::vector<BYTE> res;
	for (size_t idx_b = 0; idx_b < size; idx_b++) {
		res.push_back(read_byte((void *) ((ULONG_PTR)addr + idx_b)));
	}
	return res;
}
inline bool exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

bool LoadConfig(config& parameters) {
	mINI::INIStructure ini;
	mINI::INIFile file("config.ini");
	if (exists("config.ini")) {
		file.read(ini);
		std::string& value = ini["Mods"]["HDSprites"];
		if (value == "true")
			parameters.HD_sprites = true;
		else
			parameters.HD_sprites = false;
		value = ini["Mods"]["TextureInjection"];
		if (value == "true")
			parameters.texture_mod = true;
		else
			parameters.texture_mod = false;
		value = ini["Mods"]["Upscaling Factor"];
		parameters.upscaling_factor = atoi(value.c_str());
		return true;
	}
		
	else {
		parameters.HD_sprites = false;
		parameters.texture_mod = false;
		ini["Mods"]["HDSprites"] = "false";
		ini["Mods"]["TextureInjection"] = "false";
		ini["Mods"]["Upscaling Factor"] = "1";
		file.write(ini);
	}
	
	return true;

}