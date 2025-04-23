#pragma once

#include <chrono>
#include <random>

namespace CppUtil
{
	class CRand
	{
	public:
		static CRand& GetInstance()
		{
			static CRand instance;
			return instance;
		}

		// Initialize with a specific seed (useful for testing)
		void Initialize(uint64_t seed) { mGenerator.seed(seed); }

		// Initialize with current time (default behavior)
		void Initialize()
		{
			auto now = std::chrono::system_clock::now();
			auto duration = now.time_since_epoch();
			auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
			Initialize(static_cast<uint64_t>(millis));
		}

		// Generate a random integer in range [min, max]
		int GetRandomInt(int min, int max)
		{
			std::uniform_int_distribution<int> distribution(min, max);
			return distribution(mGenerator);
		}

		// Generate a random float in range [min, max]
		float GetRandomFloat(float min, float max)
		{
			std::uniform_real_distribution<float> distribution(min, max);
			return distribution(mGenerator);
		}

		// Generate a random double in range [min, max]
		double GetRandomDouble(double min, double max)
		{
			std::uniform_real_distribution<double> distribution(min, max);
			return distribution(mGenerator);
		}

		// Generate a random boolean with given probability of true
		bool GetRandomBool(float probabilityOfTrue = 0.5f) { return GetRandomFloat(0.0f, 1.0f) < probabilityOfTrue; }

	private:
		CRand() { Initialize(); }

		~CRand() = default;
		CRand(const CRand&) = delete;
		CRand& operator=(const CRand&) = delete;

		std::mt19937_64 mGenerator;
	};
}
