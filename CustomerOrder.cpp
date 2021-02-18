#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField = 0;
CustomerOrder::CustomerOrder():m_name("\0"),m_product("\0"), m_cntItem(0) {};
CustomerOrder::CustomerOrder(std::string& line) {
	Utilities u;
	bool check;
	size_t next_pos=0;
	// getting count of delimiters to allocate m_lstItem
	int delim_cnt = std::count(line.begin(), line.end(), u.getDelimiter());
	m_lstItem = new Item * [delim_cnt - 1];
	m_cntItem = delim_cnt - 1;
	// extract token to allocate m_lstItem's element 
	std::string token;
	for (int i = 0; i < delim_cnt + 1; i++) {
		token = u.extractToken(line, next_pos, check);
		if(i == 0) m_name = u.extractToken(line, next_pos, check);
		else if(i == 1) m_product = u.extractToken(line, next_pos, check);
		else m_lstItem[i-2] = new Item(token);
		next_pos = line.find(u.getDelimiter(), next_pos) + 1;
	}
	if (m_widthField < u.getFieldWidth()) m_widthField = u.getFieldWidth();
};
CustomerOrder::CustomerOrder(const CustomerOrder& src) {
	throw "exception thrown - copy constructor is called";
};
CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
	*this = std::move(src);
};
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
	if (m_lstItem) {
		for (auto i = 0u; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	m_lstItem = src.m_lstItem;
	src.m_lstItem = nullptr;
	m_name = src.m_name;
	m_product = src.m_product;
	m_cntItem = src.m_cntItem;
	src.m_name = "";
	src.m_product = "";
	src.m_cntItem = 0;
	return *this;
};
CustomerOrder::~CustomerOrder() {
	for (auto i = 0u; i < m_cntItem; i++) {
		delete m_lstItem[i];
	}
	delete[] m_lstItem;
};
bool CustomerOrder::isOrderFilled() const {
	bool result=true;
	for (auto i = 0u; i < m_cntItem;i++) {
		if (!m_lstItem[i]->m_isFilled) {
			result = false;
			break;
		}
	}
	return result;
	};
bool CustomerOrder::isItemFilled(const std::string& itemName) const {
	bool result;
	bool check = false;
	for (auto i = 0u; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == itemName) {
			result = m_lstItem[i]->m_isFilled;
			check = true;
			break;
		}
	}
	if (!check) result = true;
	return result;
};
void CustomerOrder::fillItem(Station& station, std::ostream& os) {
	for (auto i = 0u; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == station.getItemName()) {
			if (station.getQuantity() > 0) {
				station.updateQuantity();
				m_lstItem[i]->m_isFilled = true;
				m_lstItem[i]->m_serialNumber=station.getNextSerialNumber();
				os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName<< "]" <<std::endl;
			}
			else {
				os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
	}
};
void CustomerOrder::display(std::ostream& os) const {
	os << m_name << " - " << m_product << std::endl;
	for (auto i = 0u; i < m_cntItem; i++) {
		os << "[" << std::setw(6)<< std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING") << std::endl;
	}
};