#include <Noise.hpp>

my::Noise_Output::Noise_Output(Vector2I size) : m_isMain{ true }, m_size{ size }, m_data{ new float * [size.x] }
{	
	for (int i = 0; i < size.x; ++i)
	{
		m_data[i] = new float[size.y];
	}
}

my::Noise_Output::Noise_Output(const Noise_Output& other) :
	m_data{ other.m_data }, m_size{ other.m_size }, m_isMain{ false } { }

my::Noise_Output& my::Noise_Output::operator=(const Noise_Output& other)
{
	m_data = other.m_data; 
	m_size = other.m_size; 
	m_isMain = false;
	return *this;
}

my::Noise_Output::~Noise_Output()
{
	if(m_isMain)
	{
		for (int x = 0; x < m_size.x; ++x)
		{
			delete[] m_data[x];
		}
	}
}

float* my::Noise_Output::operator[](std::size_t idx)
{
	return m_data[idx];
}

my::Noise_Output* my::Perlin_Noise::GetNoise(int seed, Vector2I gridSize, Vector2I dataSize)
{
	Noise_Output* result = new Noise_Output(dataSize);
	std::srand(seed);

	Vector2* r_vectors = new Vector2[(gridSize.x + 1) * (gridSize.y + 1)];

	for (int y = 0; y <= gridSize.y; ++y)
	{
		for (int x = 0; x <= gridSize.x; ++x)
		{
			int current = x + y * gridSize.x;
			float r_x = (std::rand() % 10000 - 5000) / 10000.f;
			float r_y = (std::rand() % 10000 - 5000) / 10000.f;

			Vector2 vec(r_x, r_y);
			vec.Normalize();

			r_vectors[current] = vec;
		}
	}

	float dx = (int)(dataSize.x / gridSize.x);
	float dy = (int)(dataSize.y / gridSize.y);

	auto interpolation{ [](float x) {return x * x * x * (10 + x * (6 * x - 15)); } };
	/*if (use7equation)
		auto interpolation{ [](float x) {return x * x * x * x * (35 + x * (-84 + x * (70 - 20 * x))); } };*/

	auto mix{ [](float x, float y, float a) {return (1 - a) * x + a * y; } };

	for (int y_s = 0; y_s < gridSize.y; ++y_s)
	{
		for (int x_s = 0; x_s < gridSize.x; ++x_s)
		{
			for (int y = 0; y < dy; ++y)
			{
				for (int x = 0; x < dx; ++x)
				{
					Vector2 v_lt(x / dx, y / dy);
					Vector2 v_rt(x / dx - 1.f, y / dy);
					Vector2 v_lb(x / dx, y / dy - 1.f);
					Vector2 v_rb(x / dx - 1.f, y / dy - 1.f);

					int indexLeftTop = x_s + y_s * gridSize.x;

					float dot1 = Vector2::Dot(r_vectors[indexLeftTop], v_lt);
					float dot2 = Vector2::Dot(r_vectors[indexLeftTop + 1], v_rt);
					float dot3 = Vector2::Dot(r_vectors[indexLeftTop + (int)gridSize.x], v_lb);
					float dot4 = Vector2::Dot(r_vectors[indexLeftTop + (int)gridSize.x + 1], v_rb);

					float int_x = interpolation(x / dx);
					float int_y = interpolation(y / dy);
					float st = mix(dot3, dot4, int_x);
					float uv = mix(dot1, dot2, int_x);
					float noise = mix(uv, st, int_y) * 0.5f + 0.5f;

					result->m_data[x + x_s * (int)dx][y + y_s * (int)dy] = noise;
				}
			}
		}
	}

	delete[] r_vectors;

	return result;
}

const Vector2I& my::Noise_Output::getSize()
{
	return m_size;
}

//Вынесение алгоритма в отдельный файл