#ifndef PATCH_H
#define PATCH_H
#include "utilities.h"

class Patch {
	
	public:
		Patch(HMODULE h, LPSTR name, config params) {
			this->filename = name;
			this->h = h;
			GetSectionsData();
			CreateExtraSections();
			char drive[_MAX_DRIVE];
			char dir[_MAX_DIR];
			char fname[_MAX_FNAME];
			char ext[_MAX_FNAME];
			_splitpath_s(name, drive, dir, fname, ext);
			this->game_folder = std::string(drive) + std::string(dir);
			
			this->parameters = params;
		}
		~Patch() {
			
			VirtualFree((LPVOID)extra_text_section_start, 0, MEM_RELEASE);
			VirtualFree((LPVOID)extra_rdata_section_start, 0, MEM_RELEASE);
		}
		
		bool ApplyHDSprites();
		bool GetSectionsData();
		bool CreateExtraSections();
		bool FindAllAddr();
		bool CheckAllAddr();
		bool Patching();
		bool ValidateSkyFC();
		bool ApplyGetDDSNameHook();

		HMODULE h;
		ULONG_PTR VirtualToRaw(ULONG_PTR virtualAddr);
		ULONG_PTR RawToVirtual(ULONG_PTR rawAddr);

		size_t sectionAlignment;
		std::vector<Section> sects;
		

		ULONG_PTR start_text_section;
		ULONG_PTR end_text_section;
		ULONG_PTR start_rdata_section;
		ULONG_PTR end_rdata_section;
		ULONG_PTR start_data_section;
		ULONG_PTR end_data_section;
		ULONG_PTR start_rsrc_section;
		ULONG_PTR end_rsrc_section;

		ULONG_PTR extra_text_section_start = NULL;
		ULONG_PTR extra_text_section_end;
		ULONG_PTR extra_rdata_section_start = NULL;
		ULONG_PTR extra_rdata_section_end;


		ULONG_PTR next_available_addr_text;
		ULONG_PTR next_available_addr_rdata;

		LPSTR filename;
		std::string game_folder;
	
		ULONG_PTR addr1;
		ULONG_PTR addr2;
		ULONG_PTR addr3;
		ULONG_PTR addr4;
		ULONG_PTR addr5;
		ULONG_PTR addr6;
		ULONG_PTR addr66;
		ULONG_PTR addr77;
		ULONG_PTR addr_surface_dest;
		ULONG_PTR addr9;
		ULONG_PTR addr10;
		ULONG_PTR addr11;
		ULONG_PTR addr12;
		ULONG_PTR addr13;
		ULONG_PTR addr14;
		ULONG_PTR addr15;
		ULONG_PTR addr16;
		ULONG_PTR addr17;
		ULONG_PTR addr18;
		ULONG_PTR addr19;
		ULONG_PTR addr20;
		ULONG_PTR addr21;
		ULONG_PTR addr24;
		ULONG_PTR addr_allocs;
		ULONG_PTR addr1_1;
		ULONG_PTR addr1_2;
		ULONG_PTR addr1_3;
		//DDS name
		ULONG_PTR addrDDS;

		//Config settings (faire une structure plus tard !!)
		config parameters;
};

#endif