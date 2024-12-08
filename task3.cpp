#include<bits/stdc++.h>
using namespace std;

class Contact {
public:

    // private:
    string name;
    string phone_number;
    string email;

    Contact(string name,string phone_number,string email) {
        this->name = name;
        this->phone_number = phone_number;
        this->email = email;
    }

    friend ostream& operator<<(ostream& os, const Contact& contact) {
        os << contact.name << ": " << contact.phone_number << " (" << contact.email << ")";
        return os;
    }
};



class ContactManager {
public:
    vector<Contact> contacts; //stores objects of type 'Contact'.
    string filename;

    ContactManager(string filename) {
        this->filename = filename;
        load_contacts();
    }

    void add_contact(string name, string phone_number, string email) {
        Contact contact(name, phone_number, email); //This line creates a new `Contact` object, passing these parameters to its constructor.

        contacts.push_back(contact); //This method adds a new element to the end of the vector.
    }

    void view_contacts() {
        for (const auto& contact : contacts) {
            cout << contact << endl;
        }
    }

    void edit_contact(string name, string phone_number = "", string email = "") {
        for (auto& contact : contacts) {
            if (contact.name == name) {
                if (!phone_number.empty()) {
                    contact.phone_number = phone_number;
                }
                if (!email.empty()) {
                    contact.email = email;
                }
                cout<<"Contact updated successfully"<<endl;
                return;
            }
        }
        cout << "Contact not found" << endl;
    }

    void delete_contact(string name) {
        // remove_if algorithm in C++ is a powerful tool for removing elements from a container, which takes three arguments:beginning of the range,end of the range ,and A lambda function that defines the condition for removal. 
        contacts.erase(remove_if(contacts.begin(), contacts.end(),
            [&](const Contact& contact) { return contact.name == name; }), contacts.end()); // a lamda fncn
            cout<<"Contact deleted successfully"<<endl;
    }

    void save_contacts() {
        // ofstream: This is an output file stream, which is used to write data to a file.

        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& contact : contacts) {
                file << contact.name << "," << contact.phone_number << "," << contact.email << endl;
            }
            file.close();
        }
    }

    void load_contacts() {
        // ifstream: This is an input file stream, which is used to read data from a file

        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                // Finds the position of the first comma in the line.
                size_t pos1 = line.find(",");

                // Finds the position of the second comma in the line, starting from the position after the first comma
                size_t pos2 = line.find(",", pos1 + 1);

                // Extracts the name from the line, from the beginning to the first comma.
                string name = line.substr(0, pos1);

                // Extracts the phone number from the line, from the position after the first comma to the position before the second comma.
                string phone_number = line.substr(pos1 + 1, pos2 - pos1 - 1);

                // Extracts the email from the line, from the position after the second comma to the end of the line
                string email = line.substr(pos2 + 1);

                add_contact(name, phone_number, email);
            }
            file.close();
        }
    }
};

int main() {
    ContactManager manager("contacts.txt");

    while (true) {
        cout << "!!!Contact Manager!!!" << endl;
        cout<<endl;
        cout << "1. Add Contact" << endl;
        cout << "2. View Contacts" << endl;
        cout << "3. Edit Contact" << endl;
        cout << "4. Delete Contact" <<endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, phone_number, email;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter phone number: ";
            cin >> phone_number;
            cout << "Enter email: ";
            cin >> email;
            manager.add_contact(name, phone_number, email);
            break;
        }

        case 2:
            manager.view_contacts();
            break;

        case 3: {
            string name, phone_number, email;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter new phone number (optional): ";
            cin >> phone_number;
            cout << "Enter new email (optional): ";
            cin >> email;
            manager.edit_contact(name, phone_number, email);
            break;
        }

        case 4: {
            string name;
            cout << "Enter name: ";
            cin >> name;
            manager.delete_contact(name);
            break;
        }
        case 5:
            manager.save_contacts();
            return 0;
        default:
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}