#pragma once

#include <Vector2.hpp>
#include <memory>
#include <cstdint>

namespace my
{
	struct Noise_Output;

	class Perlin_Noise
	{
	public:
		/// <summary>
		/// Шум Перлина
		/// </summary>
		/// <param name="seed">Случайное значение, которое будет использоваться для генерации данных</param>
		/// <param name="gridSize">Размер сетки</param>
		/// <param name="texSize">Размер выходных данных</param>
		/// <returns>Возращяет массив размером [dataSize.x, dataSize.y]</returns>
		static Noise_Output& GetNoise(int seed, Vector2 gridSize, Vector2 dataSize);
	};

	struct Noise_Output
	{
	private:
		Vector2 m_size;
		std::shared_ptr<uint8_t*> m_data;
	public:
		Noise_Output() = default;
		Noise_Output(Vector2 size);
		uint8_t* operator[](std::size_t idx);
		
		friend static Noise_Output& Perlin_Noise::GetNoise(int, Vector2, Vector2);
	};
}