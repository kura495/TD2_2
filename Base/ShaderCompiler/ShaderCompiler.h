#pragma once

#include "Base/DirectXCommon.h"

class ShaderCompiler
{
public:
	void Initalize();
	static IDxcBlob* CompileShader(const std::wstring& filePath, const wchar_t* profile);

private:

	void MakeDXC();
	
	HRESULT hr;

	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;

};