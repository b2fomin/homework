#include <iostream>
#include <iomanip>

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

    cout << left << setw(25) << setfill('.') << "Price:" << hex << right << setfill('0') << price;
    return 0;
}