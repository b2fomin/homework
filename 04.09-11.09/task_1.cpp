#include <iostream>
#include <iomanip>

const int NUMBER_WIDTH = 8;
const int LINE_WIDTH = 25;

int main() {

	using namespace std;

	std::string name;
	int price, temperature;
	bool hasCashback;

	cout << "Product's name: ";
	cin >> name;
	cout << "Product's price: ";
	cin >> price;
	cout << "Is cash-back available for this product? (true/false) ";
	cin >> boolalpha >> hasCashback;
	cout << "Maximum storing temperature: ";
	cin >> temperature;

	cout << '\n' << "*************** OUTPUT ***************" << "\n\n";

	cout << name << '\n';

	cout << left << setw(LINE_WIDTH - NUMBER_WIDTH) << setfill('.') << "Price:" << hex << right << setw(NUMBER_WIDTH) << setfill('0') << price << endl;
	
	cout.fill('.');
	cout.setf(ios::boolalpha);

	cout << left << setw(hasCashback ? LINE_WIDTH - 4 : LINE_WIDTH - 5) << "Has cash-back:" << hasCashback << endl;

	return 0;
}