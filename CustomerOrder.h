// Name: Yu Ri Yoon
// Seneca Student ID: 135023190
// Seneca email: yryoon@myseneca.ca
// Date of completion: 2020-Nov-09
//
// I confirm that I am the only author of this file and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <string>
#include <iostream>
#include "Station.h"
struct Item
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_isFilled = false;
	Item(const std::string& src) : m_itemName(src) {};
};
class CustomerOrder
{
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	Item** m_lstItem = nullptr;
	static size_t m_widthField;
public : 
	CustomerOrder();
	CustomerOrder(std::string& line);
	CustomerOrder(const CustomerOrder& src) ;
	CustomerOrder& operator=(const CustomerOrder& ) = delete;
	CustomerOrder(CustomerOrder&& src) noexcept;
	CustomerOrder& operator=(CustomerOrder&& src) noexcept;
	~CustomerOrder();
	bool isOrderFilled() const; // returns true if all the items in the order have been filled; 
	bool isItemFilled(const std::string& itemNae) const; //returns if a certain item is filled with the specified as a parameter.
	void fillItem(Station& station, std::ostream& os);
	void display(std::ostream& os) const;
};
#endif