#pragma once

#include <Vector2.hpp>
#include <cstdint>

namespace my
{
	struct Noise_Output;

	class Perlin_Noise
	{
	public:
		/// <summary>
		/// ��� �������
		/// </summary>
		/// <param name="seed">��������� ��������, ������� ����� �������������� ��� ��������� ������</param>
		/// <param name="gridSize">������ �����</param>
		/// <param name="texSize">������ �������� ������</param>
		/// <returns>��������� ������ �������� [dataSize.x, dataSize.y]</returns>
		static Noise_Output* GetNoise(int seed, Vector2I gridSize, Vector2I dataSize);
	};

	struct Noise_Output
	{
	private:
		bool m_isMain;
		Vector2I m_size;
		float** m_data;
	public:
		Noise_Output() = default;
		Noise_Output(Vector2I size);
		Noise_Output(const Noise_Output& other);
		Noise_Output& operator=(const Noise_Output& other);
		~Noise_Output();
		float* operator[](std::size_t idx);

		const Vector2I& getSize();

		friend static Noise_Output* Perlin_Noise::GetNoise(int, Vector2I, Vector2I);
	};
}