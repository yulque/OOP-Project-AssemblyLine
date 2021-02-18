// Name: Yu Ri Yoon
// Seneca Student ID: 135023190
// Seneca email: yryoon@myseneca.ca
// Date of completion: 2020-Nov-28
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <string>
#include <iostream>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"
class Workstation : public Station
{
	std::deque<CustomerOrder> m_orders;
	Station* m_pNextStation;
public : 
	Workstation(const std::string&);
	// copy & move constructor deleted
	Workstation(const Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	Workstation& operator=(const Workstation&) = delete;
	Workstation& operator=(Workstation&&) = delete;
	void runProcess(std::ostream&);
	bool moveOrder();
	void setNextStation(Station& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder&& order);
	void display(std::ostream&) const ;
	Workstation& operator+=(CustomerOrder&&);

};


#endif
