#include <Patch.h>
#include <Utilities.h>
#include <fstream>
#include <iostream>
#include <Patterns.h>
#include <winuser.h>
#include <sys/stat.h>
#include <MinHook/minhook.h>


bool  Patch::ValidateSkyFC() {
	if (start_rsrc_section == -1) return false;
	std::vector<BYTE> signature = { 0x65, 0x00, 0x64, 0x00, 0x36, 0x00, 0x5f, 0x00, 0x77, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x2e, 0x00, 0x65, 0x00, 0x78, 0x00, 0x65 };
	int addr = find_bytes(start_rsrc_section, end_rsrc_section, signature, 1);
	if (addr == -1) return false;
	else return true;
}


bool Patch::FindAllAddr() {
	//HD
	addr1 = find_bytes(start_text_section, end_text_section, pattern1, 1);
	addr2 = find_bytes(start_text_section, end_text_section, pattern2, 1);
	addr3 = find_bytes(start_text_section, end_text_section, pattern3, 1);
	addr4 = find_bytes(start_text_section, end_text_section, pattern4, 1);
	addr5 = find_bytes(start_text_section, end_text_section, pattern5, 1);
	addr6 = find_bytes(addr5 + 1, end_text_section, pattern6, 1);
	addr66 = find_bytes(start_text_section, end_text_section, pattern66, 1);
	addr77 = find_bytes(addr66 + 1, end_text_section, pattern77, 1);
	addr_surface_dest = find_bytes(start_text_section, end_text_section, pattern8, 1);
	addr9 = find_bytes(start_text_section, end_text_section, pattern9, 1);
	addr10 = find_bytes(start_text_section, end_text_section, pattern10, 1);
	addr11 = find_bytes(start_text_section, end_text_section, patternmultiple, 1);
	addr12 = find_bytes(addr11 + 1, end_text_section, patternmultiple, 1);
	addr13 = find_bytes(addr12 + 1, end_text_section, patternmultiple, 1);
	addr14 = find_bytes(addr13 + 1, end_text_section, patternmultiple, 1);
	addr15 = find_bytes(start_text_section, end_text_section, pattern11, 1);
	addr16 = find_bytes(start_text_section, end_text_section, pattern12, 1);
	addr17 = find_bytes(start_text_section, end_text_section, pattern13, 1);
	addr18 = find_bytes(start_text_section, end_text_section, pattern14, 1);
	addr19 = find_bytes(start_text_section, end_text_section, pattern15, 1);
	addr20 = find_bytes(start_text_section, end_text_section, pattern16, 1);
	addr21 = find_bytes(start_text_section, end_text_section, pattern17, 1);
	addr24 = find_bytes(start_text_section, end_text_section, pattern20, 1);
	addr_allocs = find_bytes(start_text_section, end_text_section, pattern21, 1);
	addr1_1 = find_bytes(addr1, end_text_section, pattern1_1, 1);
	addr1_2 = find_bytes(addr1_1, end_text_section, pattern1_2, 1);
	addr1_3 = find_bytes(addr1_2, end_text_section, pattern1_3, 1);
	return true;
}

bool Patch::CheckAllAddr() {
	
	std::vector<BYTE> pattern1x1 = read_array_of_bytes((void*)addr1, pattern1.size());
	std::vector<BYTE> pattern2x1 = read_array_of_bytes((void*)addr2, pattern2.size());
	std::vector<BYTE> pattern3x1 = read_array_of_bytes((void*)addr3, pattern3.size());
	std::vector<BYTE> pattern4_1 = read_array_of_bytes((void*)addr4, pattern4.size());
	std::vector<BYTE> pattern5_1 = read_array_of_bytes((void*)addr5, pattern5.size());
	std::vector<BYTE> pattern6_1 = read_array_of_bytes((void*)addr6, pattern6.size());
	std::vector<BYTE> pattern66_1 = read_array_of_bytes((void*)addr66, pattern66.size());
	std::vector<BYTE> pattern77_1 = read_array_of_bytes((void*)addr77, pattern77.size());
	std::vector<BYTE> pattern8_1 = read_array_of_bytes((void*)addr_surface_dest, pattern8.size());
	std::vector<BYTE> pattern9_1 = read_array_of_bytes((void*)addr9, pattern9.size());
	std::vector<BYTE> pattern10_1 = read_array_of_bytes((void*)addr10, pattern10.size());
	std::vector<BYTE> patternmultiple_1 = read_array_of_bytes((void*)addr11, patternmultiple.size());
	std::vector<BYTE> pattern11_1 = read_array_of_bytes((void*)addr15, pattern11.size());
	std::vector<BYTE> pattern12_1 = read_array_of_bytes((void*)addr16, pattern12.size());
	std::vector<BYTE> pattern13_1 = read_array_of_bytes((void*)addr17, pattern13.size());
	std::vector<BYTE> pattern14_1 = read_array_of_bytes((void*)addr18, pattern14.size());
	std::vector<BYTE> pattern15_1 = read_array_of_bytes((void*)addr19, pattern15.size());
	std::vector<BYTE> pattern16_1 = read_array_of_bytes((void*)addr20, pattern16.size());
	std::vector<BYTE> pattern17_1 = read_array_of_bytes((void*)addr21, pattern17.size());
	std::vector<BYTE> pattern20_1 = read_array_of_bytes((void*)addr24, pattern20.size());
	std::vector<BYTE> pattern21_1 = read_array_of_bytes((void*)addr_allocs, pattern21.size());
	std::vector<BYTE> pattern1_1_1 = read_array_of_bytes((void*)addr1_1, pattern1_1.size());
	std::vector<BYTE> pattern1_2_1 = read_array_of_bytes((void*)addr1_2, pattern1_2.size());
	std::vector<BYTE> pattern1_3_1 = read_array_of_bytes((void*)addr1_3, pattern1_3.size());
	
	bool success = true;

	success = success && (pattern1x1 == pattern1);
	success = success && (pattern2x1 == pattern2);
	success = success && (pattern3x1 == pattern3);
	success = success && (pattern4_1 == pattern4);
	success = success && (pattern5_1 == pattern5);
	success = success && (pattern6_1 == pattern6);
	success = success && (pattern66_1 == pattern66);
	success = success && (pattern77_1 == pattern77);
	success = success && (pattern8_1 == pattern8);
	success = success && (pattern9_1 == pattern9);
	success = success && (pattern10_1 == pattern10);
	success = success && (patternmultiple_1 == patternmultiple);
	success = success && (pattern11_1 == pattern11);
	success = success && (pattern12_1 == pattern12);
	success = success && (pattern13_1 == pattern13);
	success = success && (pattern14_1 == pattern14);
	success = success && (pattern15_1 == pattern15);
	success = success && (pattern16_1 == pattern16);
	success = success && (pattern17_1 == pattern17);
	success = success && (pattern20_1 == pattern20);
	success = success && (pattern21_1 == pattern21);
	success = success && (pattern1_1_1 == pattern1_1);
	success = success && (pattern1_2_1 == pattern1_2);
	success = success && (pattern1_3_1 == pattern1_3);
	return success;

}

bool Patch::GetSectionsData() {

	ULONG_PTR base = (ULONG_PTR) h;

	int starting_point = base + read_int((void*)(base + 0x3C));
	
	int imageBase = read_int((void*) (starting_point + 0x34));

	BYTE nbSections = read_byte((void*)(starting_point + 0x6));
	int image_size = read_int((void*)(starting_point + 0x50));
	sectionAlignment = read_int((void*)(starting_point + 0x38));
	unsigned char sizeBytes[4];


	for (int idx_sec = 0; idx_sec < nbSections; idx_sec++) {
		int depart_header_section = starting_point + 0xF8 + 0x28 * (idx_sec);
		
		int section_raw_pointer = read_int((void*)(depart_header_section + 0x14));
		int raw_size = read_int((void*)(depart_header_section + 0x10));
		int section_virt_pointer = read_int((void*)(depart_header_section + 0xc));

		std::string name = std::string((const char *)depart_header_section);
		
		Section sect;
		sect.name = name;
		sect.PhysicalAddrStart = section_raw_pointer;
		sect.PhysicalAddrEnd = section_raw_pointer + raw_size;
		sect.VirtualAddrStart = base + section_virt_pointer;
		sect.VirtualAddrEnd = ((int)ceil(((float)base + section_virt_pointer + raw_size) / sectionAlignment)) * sectionAlignment;
		sects.push_back(sect);
		
	}

	int text_section = find_section_by_name(".text", sects);
	Section TextSection = sects[text_section];
	start_text_section = TextSection.VirtualAddrStart;
	end_text_section = TextSection.VirtualAddrEnd;

	int rdata_section = find_section_by_name(".rdata", sects);
	Section rDataSection = sects[rdata_section];
	start_rdata_section = rDataSection.VirtualAddrStart;
	end_rdata_section = rDataSection.VirtualAddrEnd;

	int data_section = find_section_by_name(".data", sects);
	Section DataSection = sects[data_section];
	start_data_section = DataSection.VirtualAddrStart;
	end_data_section = DataSection.VirtualAddrEnd;

	int rsrc_section = find_section_by_name(".rsrc", sects);
	Section RSRCSection = sects[rsrc_section];
	start_rsrc_section = RSRCSection.VirtualAddrStart;
	end_rsrc_section = RSRCSection.VirtualAddrEnd;
	
	return true;
}

bool Patch::CreateExtraSections() {
	size_t size_rdata = sectionAlignment * ceil((float)0x2394 / sectionAlignment); 
	size_t size_text = 2 * sectionAlignment;

	extra_rdata_section_start = (ULONG_PTR) VirtualAlloc(nullptr, size_rdata, MEM_COMMIT, PAGE_READONLY);
	extra_text_section_start = (ULONG_PTR)VirtualAlloc(nullptr, size_text, MEM_COMMIT, PAGE_EXECUTE_READ);
	extra_text_section_end = extra_text_section_start + size_text;
	extra_rdata_section_end = extra_rdata_section_start + size_rdata;
	
	next_available_addr_text = extra_text_section_start;
	next_available_addr_rdata = extra_rdata_section_start;
	return true;
}


ULONG_PTR Patch::VirtualToRaw(ULONG_PTR virtualAddr) {
	for (size_t i = 0; i < sects.size() - 1; i++) {

		if ((virtualAddr >= sects[i].VirtualAddrStart) && (virtualAddr < sects[i + 1].VirtualAddrStart)) {
			int offset = virtualAddr - sects[i].VirtualAddrStart;

			return sects[i].PhysicalAddrStart + offset;
		}
	}
	return -1;
}
ULONG_PTR Patch::RawToVirtual(ULONG_PTR rawAddr) {
	for (size_t i = 0; i < sects.size() - 1; i++) {
		if ((rawAddr >= sects[i].PhysicalAddrStart) && (rawAddr < sects[i + 1].PhysicalAddrStart)) {
			int offset = rawAddr - sects[i].PhysicalAddrStart;
			return sects[i].VirtualAddrStart + offset;
		}
	}
	return -1;
}


bool Patch::Patching() {

	bool isItSkyFC = ValidateSkyFC();
	if (!isItSkyFC) {
		std::cout << "This is not Sky FC!!" << std::endl;
		return false;
	}

	if (parameters.texture_mod)
	{
		addrDDS = find_bytes(start_text_section, end_text_section, patternDDS, 1);
		ApplyGetDDSNameHook();
	}

	FindAllAddr();
	if (parameters.HD_sprites) ApplyHDSprites();
	
	return true;
}




bool Patch::ApplyHDSprites() {

	size_t size;
	std::vector<BYTE> size_vector;
	size_t size2;
	std::vector<BYTE> size2_vector;

	int first_addr_offset = 0x2; 

	BYTE size_b;

	size = read_int((void*)(addr1 + first_addr_offset + 1)); //0x100
	size = size * parameters.upscaling_factor;
	size_vector = number_to_bytes(size, 4);

	size_b = parameters.upscaling_factor * read_byte((void*)(addr1_1+2));

	std::vector<BYTE> first_modif = { 0x68, size_vector[0], size_vector[1], size_vector[2], size_vector[3], 0x68, size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	std::vector<BYTE> second_modif = { 0x8d, 0x48, size_b };

	size = read_int((void*)(addr1_2 + 4)); //0x100
	size = size * parameters.upscaling_factor;
	size_vector = number_to_bytes(size, 4);

	std::vector<BYTE> third_modif = { 0xc7, 0x44, 0x24, 0x20, size_vector[0], size_vector[1], size_vector[2], size_vector[3], 0xc7, 0x44, 0x24, 0x1c, size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	
	size = read_int((void*)(addr1_3 + 1)); //0x100
	size = size * parameters.upscaling_factor;
	size_vector = number_to_bytes(size, 4);
	std::vector<BYTE> fourth_modif = { 0xb8, size_vector[0], size_vector[1], size_vector[2], size_vector[3]};

	RewriteMemoryEx(addr1 + first_addr_offset, first_modif);
	RewriteMemoryEx(addr1_1, second_modif);
	RewriteMemoryEx(addr1_2, third_modif);
	RewriteMemoryEx(addr1_3, fourth_modif);
	
	int fifth_addr_offset = 0x1A;
	size_b = (parameters.upscaling_factor) + read_byte((void*)(addr2 + fifth_addr_offset + 2));
	std::vector<BYTE> fifth_modif = { 0xc1, 0xe3, size_b};
	RewriteMemoryEx(addr2 + fifth_addr_offset, fifth_modif);


	int sixth_addr_offset = 0x88;
	int seventh_addr_offset = 0xD6;
	std::vector<BYTE> sixseventh_modif = { 0xc1, 0xe0, size_b };
	RewriteMemoryEx(addr3 + seventh_addr_offset, sixseventh_modif);

	int eighth_addr_offset = 0x5;
	std::vector<BYTE> eighth_modif = { 0xc1, 0xe1, size_b };
	RewriteMemoryEx(addr4 + eighth_addr_offset, eighth_modif);

	
	int ninth_addr_offset = -0xD;
	std::vector<BYTE> ninth_modif = { 0xc1, 0xe0, size_b };
	RewriteMemoryEx(addr5 + ninth_addr_offset, ninth_modif);

	int tenth_addr_offset = -0xD;
	std::vector<BYTE> tenth_modif = { 0xc1, 0xe0, size_b };
	RewriteMemoryEx(addr6 + tenth_addr_offset, tenth_modif);

	int bisbis_addr_offset = -0xE;
	std::vector<BYTE> bisbis_modif = { 0xc1, 0xe0, size_b };
	RewriteMemoryEx(addr77 + bisbis_addr_offset, bisbis_modif);
	
	int thirteenth1_addr_offset = 0x0;
	int thirteenth_addr_offset = 0x18;

	size = read_int((void*)(addr9 + thirteenth_addr_offset + 1));
	size = 2 * size * parameters.upscaling_factor;
	size_vector = number_to_bytes(size, 4);

	size2 = read_int((void*)(addr9 + thirteenth1_addr_offset + 1));
	size2 = size2 * parameters.upscaling_factor;
	size2_vector = number_to_bytes(size2, 4);

	std::vector<BYTE> thirteenth_modif = { 0x05, size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	std::vector<BYTE> thirteenth1_modif = { 0x05, size2_vector[0], size2_vector[1], size2_vector[2], size2_vector[3] };
	RewriteMemoryEx(addr9 + thirteenth_addr_offset, thirteenth_modif);
	RewriteMemoryEx(addr9 + thirteenth1_addr_offset, thirteenth1_modif);

	int fourteenth1_addr_offset = 0x0;
	int fourteenth_addr_offset = 0x9;
	std::vector<BYTE> fourteenth_modif = {size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	std::vector<BYTE> fourteenth1_modif = { 0x55, 0x05,  size2_vector[0], size2_vector[1], size2_vector[2], size2_vector[3] };
	RewriteMemoryEx(addr10 + fourteenth_addr_offset, fourteenth_modif);
	RewriteMemoryEx(addr10 + fourteenth1_addr_offset, fourteenth1_modif);

	int fifteenth_addr_offset = 0x7;
	int fifteenth1_addr_offset = 0x0;
	

	std::vector<BYTE> fifteenth_modif = { size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	std::vector<BYTE> fifteenth1_modif = { 0x05,  size2_vector[0], size2_vector[1], size2_vector[2], size2_vector[3] };
	RewriteMemoryEx(addr11 + fifteenth_addr_offset, fifteenth_modif);
	RewriteMemoryEx(addr12 + fifteenth_addr_offset, fifteenth_modif);
	RewriteMemoryEx(addr13 + fifteenth_addr_offset, fifteenth_modif);
	RewriteMemoryEx(addr14 + fifteenth_addr_offset, fifteenth_modif);
	RewriteMemoryEx(addr11 + fifteenth1_addr_offset, fifteenth1_modif);
	RewriteMemoryEx(addr12 + fifteenth1_addr_offset, fifteenth1_modif);
	RewriteMemoryEx(addr13 + fifteenth1_addr_offset, fifteenth1_modif);
	RewriteMemoryEx(addr14 + fifteenth1_addr_offset, fifteenth1_modif);

	
	int sixteenth1_addr_offset = 0x0;
	int sixteenth_addr_offset = 0x8;
	std::vector<BYTE> sixteenth1_modif = { 0x05,  size2_vector[0], size2_vector[1], size2_vector[2], size2_vector[3] };
	std::vector<BYTE> sixteenth_modif = { size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	RewriteMemoryEx(addr15 + sixteenth1_addr_offset, sixteenth1_modif);
	RewriteMemoryEx(addr15 + sixteenth_addr_offset, sixteenth_modif);
	

	int seventeenth_addr_offset = 0x2;
	int seventeenth2_addr_offset = -0x23;
	std::vector<BYTE> seventeenth_modif = { size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	std::vector<BYTE> seventeenth2_modif = { 0x05, size2_vector[0], size2_vector[1], size2_vector[2], size2_vector[3] };
	RewriteMemoryEx(addr16 + seventeenth_addr_offset, seventeenth_modif);
	RewriteMemoryEx(addr16 + seventeenth2_addr_offset, seventeenth2_modif);

	int eighteenth_addr_offset = 0x2;
	int eighteenth1_addr_offset = -0x4;
	std::vector<BYTE> eighteenth_modif = { size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	std::vector<BYTE> eighteenth1_modif = { size2_vector[0], size2_vector[1], size2_vector[2], size2_vector[3] };
	RewriteMemoryEx(addr17 + eighteenth_addr_offset, eighteenth_modif);
	RewriteMemoryEx(addr17 + eighteenth1_addr_offset, eighteenth1_modif);

	
	int nineteenth_addr_offset = -0x4;
	int nineteenth1_addr_offset = 0x2;
	std::vector<BYTE>  nineteenth_modif = { size2_vector[0], size2_vector[1], size2_vector[2], size2_vector[3] };
	std::vector<BYTE> nineteenth1_modif = { size_vector[0], size_vector[1], size_vector[2], size_vector[3] };;
	RewriteMemoryEx(addr18 + nineteenth_addr_offset, nineteenth_modif);
	RewriteMemoryEx(addr18 + nineteenth1_addr_offset, nineteenth1_modif);
	

	int addr_offset_alloc1 = 0xA6;
	int addr_offset_alloc2 = 0xE8;
	std::vector<BYTE> alloc1_modif = { 0xbd,  size2_vector[0], size2_vector[1], size2_vector[2], size2_vector[3] };
	std::vector<BYTE> alloc2_modif = { 0xbf, size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	RewriteMemoryEx(addr_allocs + addr_offset_alloc1, alloc1_modif);
	RewriteMemoryEx(addr_allocs + addr_offset_alloc2, alloc2_modif);

	int twentieth_addr_offset = -0x18;
	int twentyfirst_addr_offset = -0x6;

	size = read_int((void*)(addr19 + twentieth_addr_offset + 1));
	size = size * parameters.upscaling_factor;
	size_vector = number_to_bytes(size, 4);

	size2 = read_int((void*)(addr19 + twentieth_addr_offset + 6));
	size2 = size2 * parameters.upscaling_factor;
	size2_vector = number_to_bytes(size2, 4);


	
	std::vector<BYTE> twentieth_modif = { 0xbe, size_vector[0], size_vector[1], size_vector[2], size_vector[3], 0xbf, size2_vector[0], size2_vector[1], size2_vector[2], size2_vector[3] };
	
	size = read_int((void*)(addr19 + twentyfirst_addr_offset + 1));
	size = size * parameters.upscaling_factor;
	size_vector = number_to_bytes(size, 4);

	std::vector<BYTE> twentyfirst_modif = { 0xb8, size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	RewriteMemoryEx(addr19 + twentieth_addr_offset, twentieth_modif);
	RewriteMemoryEx(addr19 + twentyfirst_addr_offset, twentyfirst_modif);

	size = read_int((void*)(addr20 + 1));
	size = size * parameters.upscaling_factor;
	size_vector = number_to_bytes(size, 4);

	size2 = read_int((void*)(addr20 + 6));
	size2 = size2 * parameters.upscaling_factor;
	size2_vector = number_to_bytes(size2, 4);

	int twentysecond_addr_offset = 0;
	std::vector<BYTE> twentysecond_modif = { 0xb8, size_vector[0], size_vector[1], size_vector[2], size_vector[3], 0xb9, size2_vector[0], size2_vector[1], size2_vector[2], size2_vector[3] };
	RewriteMemoryEx(addr20, twentysecond_modif);

	size = read_int((void*)(addr20 - 0xc + 1));
	size = size * parameters.upscaling_factor;
	size_vector = number_to_bytes(size, 4);
	size2 = read_int((void*)(addr20 - 0xc + 6));
	size2 = size2 * parameters.upscaling_factor;
	size2_vector = number_to_bytes(size2, 4);

	std::vector<BYTE> twentysecond1_modif = { 0xBE, size_vector[0], size_vector[1], size_vector[2], size_vector[3], 0xBF, size2_vector[0], size2_vector[1], size2_vector[2], size2_vector[3] };
	RewriteMemoryEx(addr20 - 0xc, twentysecond1_modif);
	

	int twentythird_addr_offset = 0x1;
	size = read_int((void*)(addr21 + twentythird_addr_offset));
	size = size * parameters.upscaling_factor;
	size_vector = number_to_bytes(size, 4);
	std::vector<BYTE> twentythird_modif = {size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	RewriteMemoryEx(addr21 + twentythird_addr_offset, twentythird_modif);


	int twentysixth_addr_offset = 0x1;
	size = read_int((void*)(addr24 + twentysixth_addr_offset));
	size = size * parameters.upscaling_factor;
	size_vector = number_to_bytes(size, 4);
	std::vector<BYTE> twentysixth_modif = { size_vector[0], size_vector[1], size_vector[2], size_vector[3] };
	RewriteMemoryEx(addr24 + twentysixth_addr_offset, twentysixth_modif);
	
	
	int addr_jump = addr_surface_dest - 0xC; 
	int addr_where_cpr_are_inserted = next_available_addr_text;
	int addr_as_offset = addr_where_cpr_are_inserted - (addr_jump + 0x10 + 0x5);
	
	size = read_int((void*)(addr_surface_dest + 7));
	size = size * parameters.upscaling_factor;
	size_vector = number_to_bytes(size, 4);

	std::vector<BYTE> addr_offset_function3 = number_to_bytes(addr_as_offset, 4);
	std::vector<BYTE> twentyseventh_modif = { 0x8d, 0xbe, 0x4b, 0xff, 0xff, 0xff, 0xb8, size_vector[0], size_vector[1], size_vector[2], size_vector[3], 0xba, 0x1a, 0x00, 0x00, 0x00, 0xe9, addr_offset_function3[0], addr_offset_function3[1], addr_offset_function3[2], addr_offset_function3[3], 0x01 };
	RewriteMemoryEx(addr_jump, twentyseventh_modif);

	int addr_one_random_jump_to_fix = addr_jump + 0x173;
	std::vector<BYTE> addr_offset_random_jump = number_to_bytes(-0x179, 4);
	std::vector<BYTE> twentyeighth_modif = {0x0f, 0x8c, addr_offset_random_jump[0],addr_offset_random_jump[1],addr_offset_random_jump[2],addr_offset_random_jump[3] };
	RewriteMemoryEx(addr_one_random_jump_to_fix, twentyeighth_modif);
	
	int addr_raw_comparisons = next_available_addr_text;
	int addr_to_jump_if_false_comparisons = addr_jump + 0x1C;
	int offset_jump_false_comparisons1 = addr_to_jump_if_false_comparisons - (addr_where_cpr_are_inserted + 0xF + 0x6);
	
	std::vector<BYTE> offset1 = number_to_bytes(offset_jump_false_comparisons1, 4);
	

	int offset_jump_false_comparisons2 = addr_to_jump_if_false_comparisons - (addr_where_cpr_are_inserted + 0x18 + 0x5);
	size_b = parameters.upscaling_factor/2;
	std::vector<BYTE> offset2 = number_to_bytes(offset_jump_false_comparisons2, 4);
	std::vector<BYTE> twentyninth_modif = {0x83, 0xfe, 0x02, 0x0f, 0x84, 0x0c, 0x00, 0x00, 0x00, 0x81, 0xfe, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x85, offset1[0], offset1[1], offset1[2], offset1[3], 0xc1, 0xf8, size_b, 0xe9, offset2[0], offset2[1], offset2[2], offset2[3] };
	RewriteMemoryEx(addr_raw_comparisons, twentyninth_modif);
	next_available_addr_text += twentyninth_modif.size();
	
	return true;

}


typedef DWORD(WINAPI* DDS_NAME_FUN_Prototype)
(
	LPCSTR file_name
	);

DDS_NAME_FUN_Prototype fpDDS = NULL;
std::string current_DDS_name;

DWORD WINAPI DDS_NAME_FUN_detour
(
	LPCSTR file_name
) {
	

	std::string str(file_name); 
	size_t idx = str.find("._DS");
	if (idx != std::string::npos)
		{
			str.erase(idx, 4);
			current_DDS_name = str;
		}

	
	return fpDDS(file_name);
}


bool Patch::ApplyGetDDSNameHook() {
	
	ULONG_PTR offset_to_function_reading_str = read_int((void*)(addrDDS + 10));
	ULONG_PTR addr_fun = addrDDS + 14 + offset_to_function_reading_str;
	
	MH_STATUS status = MH_OK;
	

	
	
	status =
			MH_CreateHook((LPVOID*)addr_fun,
				&DDS_NAME_FUN_detour,
				reinterpret_cast<LPVOID*>(&fpDDS));
	
	MH_EnableHook((LPVOID*)addr_fun);
	
	return true;
}