// Created by: Cian McNamara, December 28th 2024

#pragma once

#include <vector>
#include <string>

namespace SuperIntW64 {
	class superint {
		// Properties
	public:
		const bool IsNegative(); // The sign of the number
		const bool IsReady(); // The state of the number

	protected:
		std::vector<int> vNumber; // Holds the vector form of the number

	private:
		bool _isNegative; // The sign of the number
		bool _isReady; // The state of the number

		// Methods
	public:
		/// <summary>
		/// Creates a new super integer object.
		/// </summary>
		superint();
		/// <summary>
		/// Creates a new super integer object.
		/// </summary>
		superint(std::string sNumber);
		/// <summary>
		/// Creates a new super integer object.
		/// </summary>
		superint(std::vector<int> vNumber);
		/// <summary>
		/// Creates a new super integer object.
		/// </summary>
		superint(std::vector<int> vNumber, bool isNegative);

		/// <summary>
		/// Adds two super integers together.
		/// </summary>
		/// <param name="siNumber"></param>
		/// <returns></returns>
		static superint* Add(superint siNumber1, superint siNumber2);
		/// <summary>
		/// Subtracts two super integers from eachother.
		/// </summary>
		/// <param name="siNumber"></param>
		/// <returns></returns>
		static superint* Sub(superint siNumber1, superint siNumber2);
		/// <summary>
		/// Multiplies two super integers together
		/// </summary>
		/// <param name="siNumber1"></param>
		/// <param name="siNumber2"></param>
		/// <returns></returns>
		static superint* Mult(superint siNumber1, superint siNumber2);
		/// <summary>
		/// Divides two super integers from eachother.
		/// </summary>
		/// <param name="siNumber1"></param>
		/// <param name="siNumber2"></param>
		/// <returns></returns>
		static superint* Div(superint siNumber1, superint siNumber2);

		/// <summary>
		/// Checks if a super integer is greater than another super integer.
		/// </summary>
		/// <param name="siNumber1"></param>
		/// <param name="siNumber2"></param>
		/// <returns></returns>
		static bool IsGreater(superint siNumber1, superint siNumber2);
		/// <summary>
		/// Checks if a super integer is lesser than another super integer.
		/// </summary>
		/// <param name="siNumber1"></param>
		/// <param name="siNumber2"></param>
		/// <returns></returns>
		static bool IsLesser(superint siNumber1, superint siNumber2);
		/// <summary>
		/// Checks if a super integer is equal to another super integer.
		/// </summary>
		/// <param name="siNumber1"></param>
		/// <param name="siNumber2"></param>
		/// <returns></returns>
		static bool IsEqual(superint siNumber1, superint siNumber2);

		/// <summary>
		/// Converts the super integer to a string.
		/// </summary>
		std::string ToString();
		/// <summary>
		/// Gets the super integers vector.
		/// </summary>
		std::vector<int> GetVector();
	private:
		/// <summary>
		/// Ignores the sign when doing addition operations.
		/// </summary>
		/// <param name="usiNumber1"></param>
		/// <param name="usiNumber2"></param>
		/// <returns></returns>
		static superint* _uAdd(superint usiNumber1, superint usiNumber2);
		/// <summary>
		/// Ignores the sign when doing subtraction operations.
		/// </summary>
		/// <param name="usiNumber1"></param>
		/// <param name="usiNumber2"></param>
		/// <returns></returns>
		static superint* _uSub(superint usiNumber1, superint usiNumber2);
		/// <summary>
		/// Ignores the sign when doing multiplication operations.
		/// </summary>
		/// <param name="usiNumber1"></param>
		/// <param name="usiNumber2"></param>
		/// <returns></returns>
		static superint* _uMult(superint usiNumber1, superint usiNumber2);
		/// <summary>
		/// Ignores the sign when doing division operations.
		/// </summary>
		/// <param name="usiNumber1"></param>
		/// <param name="usiNumber2"></param>
		/// <returns></returns>
		static superint* _uDiv(superint usiNumber1, superint usiNumber2);

		/// <summary>
		/// Formats vNumber if it is in the incorrect format.
		/// </summary>
		void format();
		/// <summary>
		/// Passes any multiple of 10 or higher in the current index to the next highest index.
		/// </summary>
		/// <param name="currentEntry"></param>
		/// <param name="i"></param>
		void passToHigherIndex(int currentEntry, int i);
		/// <summary>
		/// Decrements the current index and puts the correct value into the lower index in vNumber.
		/// </summary>
		/// <param name="currentEntry"></param>
		/// <param name="i"></param>
		void borrowFromHigherIndex(int currentEntry, int i);
		/// <summary>
		/// Checks if the number is formatted correctly.
		/// </summary>
		/// <returns></returns>
		bool isFormattedCorrectly();
		/// <summary>
		/// Checks if vNumber has leading zeroes.
		/// </summary>
		/// <returns></returns>
		bool hasLeadingZeroes();
		/// <summary>
		/// Removes the leading zeroes from vNumber.
		/// </summary>
		void removeLeadingZeroes();

		/// <summary>
		/// Checks if the string is a valid number.
		/// </summary>
		static bool isValidNumber(std::string sNumber);
		/// <summary>
		/// Checks if the string is a negative number.
		/// </summary>
		static bool isNumberNegative(std::string sNumber);
	};
}