// Name: Yu Ri Yoon
// Seneca Student ID: 135023190
// Seneca email: yryoon@myseneca.ca
// Date of completion: 2020-Nov-09
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
#include <iostream>

class Station
{
	int stnId;
	std::string itemName;
	std::string desc;
	int nextSerial;
	int numOfStock;
	static size_t m_widthField;
	static size_t id_generator;
public : 
	Station(const std::string& line);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
		
};

#endif