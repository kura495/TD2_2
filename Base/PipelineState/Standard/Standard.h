#pragma once


#include "Base/PipelineState/IPipelineStateObject.h"


class Standard : public IPipelineStateObject
{
public:
	void ShaderCompile() override;
	void CreateRootSignature() override;
	void CreateInputLayOut() override;
	void CreateBlendState() override;
	void CreateRasterizarState() override;
	void CreatePipelineStateObject() override;

private:

};
