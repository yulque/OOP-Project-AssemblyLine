// Name: Yu Ri Yoon
// Seneca Student ID: 135023190
// Seneca email: yryoon@myseneca.ca
// Date of completion: 2020-Nov-09
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"
char Utilities::m_delimiter = ' ';
void Utilities::setFieldWidth(size_t newWidth) {
	m_widthField = newWidth;
};
size_t Utilities::getFieldWidth() const {
	return m_widthField;
};
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	std::string token,result;
	//token starts at next_pos until meeting next delimiter
	token = str.substr(next_pos, str.find(m_delimiter,next_pos)-next_pos); //4,7-4
	std::string t(2, m_delimiter);
	if (token != "") {
		more = true;
		result = token;
	}
	else if (token == t) {
		throw "no token found";
	}
	else more = false;
	//update widthField if needed
	if (m_widthField < token.size()) {
		m_widthField = token.size();
	}
	return result;
};
void Utilities::setDelimiter(char newDelimiter) {
	m_delimiter = newDelimiter;
};
char Utilities::getDelimiter() {
	return m_delimiter;
};
