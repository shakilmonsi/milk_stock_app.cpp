#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Milk {
public:
    string type;
    double pricePerLiter;
    double quantity;

    Milk(string t, double p, double q) : type(t), pricePerLiter(p), quantity(q) {}
};

class Customer {
public:
    string name;
    string phoneNumber;
    vector<string> purchaseHistory;

    Customer(string n, string p) : name(n), phoneNumber(p) {}

    void addPurchaseRecord(const string& record) {
        purchaseHistory.push_back(record);
    }

    void displayHistory() const {
        cout << "\nTransaction History for " << name << ":\n";
        for (const auto& record : purchaseHistory) {
            cout << "- " << record << endl;
        }
    }
};

class MilkCompany {
private:
    vector<Milk> stock;
    vector<Customer> customers;
    double totalSales;

public:
    MilkCompany() : totalSales(0) {}

    void addStock(const string& type, double price, double quantity) {
        for (auto& milk : stock) {
            if (milk.type == type) {
                milk.quantity += quantity;
                milk.pricePerLiter = price;
                return;
            }
        }
        stock.emplace_back(type, price, quantity);
    }

    void displayStock() {
        cout << "\nCurrent Stock:\n";
        cout << left << setw(15) << "Milk Type" << setw(15) << "Price/Liter" << setw(15) << "Quantity" << endl;
        for (const auto& milk : stock) {
            cout << left << setw(15) << milk.type << setw(15) << milk.pricePerLiter << setw(15) << milk.quantity << endl;
        }
    }

    void purchaseMilk(const string& customerName, const string& phoneNumber, const string& milkType, double quantity) {
        for (auto& milk : stock) {
            if (milk.type == milkType) {
                if (milk.quantity >= quantity) {
                    double cost = milk.pricePerLiter * quantity;
                    milk.quantity -= quantity;
                    totalSales += cost;

                    // Find or create customer
                    Customer* customer = nullptr;
                    for (auto& c : customers) {
                        if (c.phoneNumber == phoneNumber) {
                            customer = &c;
                            break;
                        }
                    }

                    if (!customer) {
                        customers.emplace_back(customerName, phoneNumber);
                        customer = &customers.back();
                    }

                    string record = "Bought " + to_string(quantity) + "L of " + milkType + " for " + to_string(cost) + " BDT";
                    customer->addPurchaseRecord(record);

                    cout << "\nInvoice:\n";
                    cout << "Customer: " << customerName << endl;
                    cout << "Phone: " << phoneNumber << endl;
                    cout << "Milk Type: " << milkType << endl;
                    cout << "Quantity: " << quantity << "L\n";
                    cout << "Total Cost: " << cost << " BDT\n";
                    return;
                } else {
                    cout << "\nInsufficient stock for " << milkType << ".\n";
                    return;
                }
            }
        }
        cout << "\nMilk type " << milkType << " not found in stock.\n";
    }

    void generateReport() {
        cout << "\nEnd of Day Report:\n";
        cout << "Total Sales: " << totalSales << " BDT\n";
        displayStock();
    }

    void displayCustomerHistory(const string& phoneNumber) {
        for (const auto& customer : customers) {
            if (customer.phoneNumber == phoneNumber) {
                customer.displayHistory();
                return;
            }
        }
        cout << "\nNo customer found with phone number " << phoneNumber << ".\n";
    }
};

int main() {
    MilkCompany company;
    int choice;

    do {
        cout << "\nMilk Company Management:\n";
        cout << "1. Add Stock\n";
        cout << "2. Display Stock\n";
        cout << "3. Purchase Milk\n";
        cout << "4. Display Customer History\n";
        cout << "5. Generate End of Day Report\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string type;
            double price, quantity;
            cout << "Enter milk type: ";
            cin >> type;
            cout << "Enter price per liter: ";
            cin >> price;
            cout << "Enter quantity: ";
            cin >> quantity;
            company.addStock(type, price, quantity);
            break;
        }
        case 2:
            company.displayStock();
            break;
        case 3: {
            string name, phone, type;
            double quantity;
            cout << "Enter customer name: ";
            cin >> name;
            cout << "Enter phone number: ";
            cin >> phone;
            cout << "Enter milk type: ";
            cin >> type;
            cout << "Enter quantity: ";
            cin >> quantity;
            company.purchaseMilk(name, phone, type, quantity);
            break;
        }
        case 4: {
            string phone;
            cout << "Enter customer phone number: ";
            cin >> phone;
            company.displayCustomerHistory(phone);
            break;
        }
        case 5:
            company.generateReport();
            break;
        case 6:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
