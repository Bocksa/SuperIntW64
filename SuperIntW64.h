#pragma once

#include <vector>
#include <string>

namespace SuperIntW64 {
	class superint {
		// Properties
	public:
		const bool isNegative(); // The sign of the number
		const bool isReady(); // The state of the number

	private:
		std::vector<int> vNumber; // Holds the vector form of the number
		bool _isNegative; // The sign of the number
		bool _isReady; // The state of the number

		// Methods
	public:
		superint();
		superint(std::string sNumber);

		std::string toString();

	private:
		static bool isValidNumber(std::string sNumber);
		static bool isNumberNegative(std::string sNumber);
	};
}