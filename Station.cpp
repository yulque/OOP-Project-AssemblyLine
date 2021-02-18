// Name: Yu Ri Yoon
// Seneca Student ID: 135023190
// Seneca email: yryoon@myseneca.ca
// Date of completion: 2020-Nov-09
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include "Station.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>

size_t Station::m_widthField = 0;
size_t Station::id_generator = 0;
Station::Station(const std::string& line):stnId(++id_generator) {
	//id_generator++;
	Utilities util;
	bool more=true;
	size_t delim_pos;
	for (auto i = 0; i < 4; i++) {
		//in the beginning, delim_pos is 0, after, delim_pos is where next delimiter is and add 1.
		if (i == 0) delim_pos = 0;
		else delim_pos = line.find(util.getDelimiter(),delim_pos) + 1;
		auto token = util.extractToken(line, delim_pos, more);
		if (i == 0) {
			itemName = token;
		}
		else if (i == 1) {
			this->nextSerial = std::stoi(token);
		}//123456
		else if (i == 2) {
			this->numOfStock = std::stoi(token);
			if (Station::m_widthField < util.getFieldWidth()) Station::m_widthField = util.getFieldWidth();
		}
		else if (i == 3) {
			desc = token;}
	}	
};
const std::string& Station::getItemName() const {
	return itemName;
};
unsigned int Station::getNextSerialNumber() {
	return nextSerial++;
};
unsigned int Station::getQuantity() const {
	return numOfStock;
};
void Station::updateQuantity() {
	if (numOfStock > 0) --numOfStock;
};
void Station::display(std::ostream& os, bool full) const {
	if (!full) {
		os << "["<< std::setw(3) << std::setfill('0') << std::right << stnId <<"] Item: " << std::setw(m_widthField) << std::setfill(' ') << std::left << itemName << " [" << std::setw(6) << std::setfill('0') << std::right << nextSerial << "]" << std::endl;
	}
	else {
		os << "[" << std::setw(3) << std::setfill('0') << std::right << stnId << "] Item: " << std::setw(m_widthField) << std::setfill(' ') << std::left << itemName << " [" << std::setw(6) << std::setfill('0') << std::right << nextSerial << "] Quantity: " << std::setw(m_widthField) << std::setfill(' ') << std::left << numOfStock << " Description: "<< desc <<std::endl;
	}
};
