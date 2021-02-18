// Name: Yu Ri Yoon
// Seneca Student ID: 135023190
// Seneca email: yryoon@myseneca.ca
// Date of completion: 2020-Nov-28
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"

Workstation::Workstation(const std::string& src) : Station(src) {

	m_pNextStation = nullptr;
};
void Workstation::runProcess(std::ostream& os) {
	// it's already checked that we need to run the process. so don't double check. 
	if(!m_orders.empty()) m_orders.front().fillItem(*this, os);
	// remove the first order if it's all filled.
};
bool Workstation::moveOrder() {
	bool result = false;
	if (!m_orders.empty()) {
		if (m_orders.front().isItemFilled(getItemName()) && m_pNextStation) { 
			// they don't need me! & move this order to next workstation
			auto nextStation = static_cast<Workstation*>(m_pNextStation);
			nextStation->m_orders.push_back(std::move(m_orders.front()));
			m_orders.pop_front();
			result = true;
		} 
		// they need me. so no need to move. let's return false
	} 
	return result;
	};
void Workstation::setNextStation(Station& station) {
	m_pNextStation = &station;
};
const Workstation* Workstation::getNextStation() const {
	return static_cast<Workstation*>(m_pNextStation);
};
bool Workstation::getIfCompleted(CustomerOrder&& order) {
	bool result = false;
	if (!m_orders.empty()) {
		if (m_orders.front().isOrderFilled()) {
			order = std::move(m_orders.front());
			m_orders.pop_front();
			result = true;
		}
	}
	return result;
};
void Workstation::display(std::ostream& os) const {
	os << getItemName() << " --> " << (m_pNextStation? m_pNextStation->getItemName() : "END OF LINE") << std::endl; 	
};
Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
	m_orders.push_back(std::move(newOrder));
	return *this;
};