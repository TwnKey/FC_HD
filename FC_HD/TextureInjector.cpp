#include "TextureInjector.h"
#include <MinHook/minhook.h>
#include <filesystem>
#include <sys/stat.h>

TextureInjector TexInj;
extern std::string current_DDS_name;

void * memory_pool;
typedef HRESULT(STDMETHODCALLTYPE* D3DXCreateTextureFromFileInMemoryEx_Prototype)
(
	_In_        LPDIRECT3DDEVICE9  pDevice,
	_In_        LPCVOID            pSrcData,
	_In_        UINT               SrcDataSize,
	_In_        UINT               Width,
	_In_        UINT               Height,
	_In_        UINT               MipLevels,
	_In_        DWORD              Usage,
	_In_        D3DFORMAT          Format,
	_In_        D3DPOOL            Pool,
	_In_        DWORD              Filter,
	_In_        DWORD              MipFilter,
	_In_        D3DCOLOR           ColorKey,
	_Inout_opt_ D3DXIMAGE_INFO* pSrcInfo,
	_Out_opt_   PALETTEENTRY* pPalette,
	_Out_       LPDIRECT3DTEXTURE9* ppTexture
	);


D3DXCreateTextureFromFileInMemoryEx_Prototype fp = NULL;

COM_DECLSPEC_NOTHROW
HRESULT
STDMETHODCALLTYPE D3DXCreateTextureFromFileInMemoryEx_Detour
(
	_In_    LPDIRECT3DDEVICE9  pDevice,
	_In_    LPCVOID            pSrcData,
	_In_    UINT               SrcDataSize,
	_In_    UINT               Width,
	_In_    UINT               Height,
	_In_    UINT               MipLevels,
	_In_    DWORD              Usage,
	_In_    D3DFORMAT          Format,
	_In_    D3DPOOL            Pool,
	_In_    DWORD              Filter,
	_In_    DWORD              MipFilter,
	_In_    D3DCOLOR           ColorKey,
	_Inout_ D3DXIMAGE_INFO* pSrcInfo,
	_Out_   PALETTEENTRY* pPalette,
	_Out_   LPDIRECT3DTEXTURE9* ppTexture
) {
	
	HRESULT hr = D3D_OK;
	D3DXIMAGE_INFO img_info = {};
	std::transform(current_DDS_name.begin(), current_DDS_name.end(), current_DDS_name.begin(), ::toupper);
	
	if (((TexInj.injectable_textures.count(current_DDS_name.c_str())) != 0)) {
		wchar_t full_path[MAX_PATH];
		std::wstring wsTmp(current_DDS_name.begin(), current_DDS_name.end());
		swprintf(full_path, L"textures\\%s.dds", wsTmp.c_str());
		
		HANDLE hTexFile =
			CreateFile(full_path,
				GENERIC_READ,
				FILE_SHARE_READ,
				nullptr,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL |
				FILE_FLAG_SEQUENTIAL_SCAN,
				nullptr);

		DWORD read = 0UL;
		if (hTexFile != INVALID_HANDLE_VALUE)
		{
			size_t size = GetFileSize(hTexFile, nullptr);
			if (memory_pool != nullptr)
			{

				ReadFile(hTexFile, memory_pool, (DWORD)size, &read, nullptr);

				DWORD SrcDataSize1 = read;

				if (size > (128 * 1024))
				{
					SetThreadPriority(GetCurrentThread(),
						THREAD_PRIORITY_BELOW_NORMAL |
						THREAD_MODE_BACKGROUND_BEGIN);
				}

				D3DXGetImageInfoFromFileInMemory(
					memory_pool,
					SrcDataSize1,
					&img_info);
				hr = fp(
					pDevice,
					memory_pool, SrcDataSize1,
					D3DX_DEFAULT, D3DX_DEFAULT, img_info.MipLevels,
					0, D3DFMT_FROM_FILE,
					D3DPOOL_DEFAULT,
					D3DX_DEFAULT, D3DX_DEFAULT,
					0,
					&img_info, nullptr,
					ppTexture);
			}

			else {
				// OUT OF MEMORY ?!
			}

			CloseHandle(hTexFile);



		}
		else {
			hr = fp(
				pDevice,
				pSrcData, SrcDataSize,
				Width, Height, MipLevels,
				Usage,
				Format,
				Pool,
				Filter, MipFilter, ColorKey,
				pSrcInfo, pPalette,
				ppTexture
			);
		}
	}
	else {
		hr = fp(
				pDevice,
				pSrcData, SrcDataSize,
				Width, Height, MipLevels,
				Usage,
				Format,
				Pool,
				Filter, MipFilter, ColorKey,
				pSrcInfo, pPalette,
				ppTexture
			);
	}
	
	return hr;

}


bool TextureInjector::listAllTextures() {
	struct stat buffer;
	size_pool = 0;
	std::string path = "textures";
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_FNAME];
	std::unordered_set<std::string> test;
	for (const auto& entry : std::filesystem::directory_iterator(path)) {

		std::string file_path = entry.path().string();
		
		_splitpath_s(file_path.c_str(), drive, dir, fname, ext);
		
		
		stat(file_path.c_str(), &buffer);
		if (buffer.st_size > size_pool)
			size_pool = buffer.st_size;
		std::string key = std::string(fname);
		this->injectable_textures.emplace(key);
		

	}
	
	return true;

}


bool TextureInjector::Init() {
	listAllTextures();
	pool = malloc(size_pool);
	memory_pool = pool;
	if (MH_Initialize() != MH_OK)
	{
		return false;
	}
	HMODULE hMod = nullptr;
	const wchar_t* pwszModule = L"D3DX9_43.DLL";
	const char* pszProcName = "D3DXCreateTextureFromFileInMemoryEx";

	if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_PIN, pwszModule, &hMod))
	{
		if (LoadLibraryW(pwszModule))
			GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_PIN, pwszModule, &hMod);
	}

	MH_STATUS status = MH_OK;

	if (hMod == nullptr)
		status = MH_ERROR_MODULE_NOT_FOUND;

	else
	{

		LPVOID pFuncAddr =
			GetProcAddress(hMod, pszProcName);

		status =
			MH_CreateHook((LPVOID*)pFuncAddr,
				&D3DXCreateTextureFromFileInMemoryEx_Detour,
				reinterpret_cast<LPVOID*>(&fp));
		MH_EnableHook((LPVOID*)pFuncAddr);
	}
}

TextureInjector::TextureInjector()
{
	Init();
}


TextureInjector::~TextureInjector()
{
}
