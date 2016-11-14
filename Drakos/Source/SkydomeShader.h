#pragma once

#include <d3d11_2.h>
#include "DXMath.h"

class SkydomeShader
{
	struct MatrixBufferType
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	struct ColorBufferType
	{
		Color apexColor;
		Color centerColor;
	};

public:
	SkydomeShader();		
	~SkydomeShader();

	bool Initialize(ID3D11Device*, HWND);
	bool Render(ID3D11DeviceContext*, int, Matrix, Matrix, Matrix, Color, Color) const;

private:
	SkydomeShader(const SkydomeShader&);

	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	bool SetShaderParameters(ID3D11DeviceContext*, Matrix, Matrix, Matrix, Color, Color) const;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_layout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_matrixBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_colorBuffer;

};
