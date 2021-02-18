// Name: Yu Ri Yoon
// Seneca Student ID: 135023190
// Seneca email: yryoon@myseneca.ca
// Date of completion: 2020-Nov-28
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "LineManager.h"

LineManager::LineManager(const std::string file, std::vector<Workstation*>& workStation, std::vector<CustomerOrder>& customerOrder) {
	std::string line, token1, token2;
	std::ifstream read(file);
	while (read) {
		getline(read, line);
		token1 = line.substr(0, line.find("|"));
		token2 = line.substr(line.find("|") + 1);
		if (token1 != token2) {
			for_each(workStation.begin(), workStation.end(), [token1, token2, &workStation](auto stn) {if (stn->getItemName() == token1) {
				for_each(workStation.begin(), workStation.end(), [token2, &stn](auto stnInside) {if (stnInside->getItemName() == token2) {
					stn->setNextStation(*stnInside);
				}});
			}});
		}
	}
	std::move(customerOrder.begin(), customerOrder.end(), back_inserter(ToBeFilled));
	AssemblyLine = workStation;
	m_cntCustomerOrder = ToBeFilled.size();
};
bool LineManager::run(std::ostream& os) {
	static size_t cnt = 1;
	bool result = false;
	
	os << "Line Manager Iteration: " << cnt++ << std::endl;
	auto thisStation = AssemblyLine[5];

	// move the one at front onto starting point of assembly line
	if (!ToBeFilled.empty()) {
		*thisStation += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	// loop through all stations, and run process. 
	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->runProcess(std::cout);
		
	}

	// loop through all stations, and move order. 
	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->moveOrder();

		// if an order is completed, remove it from the assembly line
		CustomerOrder plzWork;
		if (AssemblyLine[i]->getIfCompleted(std::move(plzWork))) {
			Completed.push_back(std::move(plzWork));
		}
	}
	
	if (Completed.size() == m_cntCustomerOrder) result = true;
	return result;
};
void LineManager::displayCompletedOrders(std::ostream& os) const {
	std::for_each(Completed.begin(), Completed.end(), [&os](auto&& line) { line.display(os); });
};
// in the order they were received from the client
void LineManager::displayStations() const {
	std::for_each(AssemblyLine.begin(), AssemblyLine.end(), [](auto line) {line->display(std::cout); });
};
// in the order they are linked
void LineManager::displayStationsSorted() const {
	auto next = AssemblyLine[5];
	do {
		next->display(std::cout);
		next = const_cast<Workstation*>(next->getNextStation());
	} while (next);
};