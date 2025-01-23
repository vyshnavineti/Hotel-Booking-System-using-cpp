#include <iostream>
#include <cstring>
using namespace std;

class Customer {
public:
    char name[100];
    char address[100];
    char phone[12];
    char from_date[20];
    char to_date[20];
    float payment_advance;
    int booking_id;
};

class Room {
public:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;
    Customer cust;
    Room* next; // Pointer to the next room

    Room(int rno); // Constructor
};

class HotelMgnt {
private:
    Room* roomsHead; // Pointer to the head of the linked list

public:
    HotelMgnt();
    ~HotelMgnt(); // Destructor to free memory
    void addRoom(int);
    void searchRoom(int);
    void checkIn();
    void getAvailRoom();
    void searchCustomer(const char*);
    void checkOut(int);
    void guestSummaryReport();
};

// Room class constructor to initialize room number and next pointer
Room::Room(int rno) : roomNumber(rno), status(0), next(nullptr) {
    // Additional constructor logic if needed
}

// HotelMgnt class constructor to initialize the roomsHead pointer
HotelMgnt::HotelMgnt() {
    roomsHead = nullptr;
}

// HotelMgnt class destructor to free memory allocated for the linked list
HotelMgnt::~HotelMgnt() {
    Room* current = roomsHead;
    while (current) {
        Room* temp = current;
        current = current->next;
        delete temp;
    }
}

void HotelMgnt::addRoom(int rno) {
    Room* room = new Room(rno);
    cout << "\nType AC/Non-AC (A/N) : ";
    cin >> room->ac;
    cout << "\nType Comfort (S/N) : ";
    cin >> room->type;
    cout << "\nType Size (B/S) : ";
    cin >> room->stype;
    cout << "\nDaily Rent : ";
    cin >> room->rent;

    if (!roomsHead) {
        roomsHead = room;
    } else {
        Room* current = roomsHead;
        while (current->next) {
            current = current->next;
        }
        current->next = room;
    }

    cout << "\n Room Added Successfully!";
}

void HotelMgnt::searchRoom(int rno) {
    Room* current = roomsHead;
    int found = 0;
    while (current) {
        if (current->roomNumber == rno) {
            found = 1;
            break;
        }
        current = current->next;
    }

    if (found == 1) {
        cout << "Room Details\n";
        if (current->status == 1) {
            cout << "\nRoom is Reserved";
        } else {
            cout << "\nRoom is available";
        }

        cout << "\nRoom Number: \t" << current->roomNumber;
        cout << "\nType AC/Non-AC (A/N) " << current->ac;
        cout << "\nType Comfort (S/N) " << current->type;
        cout << "\nType Size (B/S) " << current->stype;
        cout << "\nRent: " << current->rent;
    } else {
        cout << "\nRoom not found";
    }
}

void HotelMgnt::guestSummaryReport() {
    Room* current = roomsHead;
    int found = 0;

    if (!current) {
        cout << "\n No Guest in Hotel !!";
    }

    while (current) {
        if (current->status == 1) {
            cout << "\n Customer First Name : " << current->cust.name;
            cout << "\n Room Number : " << current->roomNumber;
            cout << "\n Address (only city) : " << current->cust.address;
            cout << "\n Phone : " << current->cust.phone;
            cout << "\n---------------------------------------";
            found = 1;
        }
        current = current->next;
    }

    if (found == 0) {
        cout << "\n No guests currently checked-in.";
    }
}

void HotelMgnt::checkIn() {
    int rno;
    cout << "\nEnter Room number : ";
    cin >> rno;

    Room* current = roomsHead;
    int found = 0;

    while (current) {
        if (current->roomNumber == rno) {
            found = 1;
            break;
        }
        current = current->next;
    }

    if (found == 1) {
        if (current->status == 1) {
            cout << "\nRoom is already Booked";
            return;
        }
        cout << "\nEnter booking id: ";
        cin >> current->cust.booking_id;
        cout << "\nEnter Customer Name (First Name): ";
        cin >> current->cust.name;
        cout << "\nEnter Address (only city): ";
        cin >> current->cust.address;
        cout << "\nEnter Phone: ";
        cin >> current->cust.phone;
        cout << "\nEnter From Date: ";
        cin >> current->cust.from_date;
        cout << "\nEnter to  Date: ";
        cin >> current->cust.to_date;
        cout << "\nEnter Advance Payment: ";
        cin >> current->cust.payment_advance;
        current->status = 1;
        cout << "\n Customer Checked-in Successfully..";
    } else {
        cout << "\nRoom not found";
    }
}

void HotelMgnt::getAvailRoom() {
    Room* current = roomsHead;
    int found = 0;

    while (current) {
        if (current->status == 0) {
            cout << "Room Number: \t" << current->roomNumber;
            cout << "\nType AC/Non-AC (A/N) " << current->ac;
            cout << "\nType Comfort (S/N) " << current->type;
            cout << "\nType Size (B/S) " << current->stype;
            cout << "\nRent: " << current->rent;
            cout << "\n\nPress enter for next room";
            found = 1;
        }
        current = current->next;
    }

    if (found == 0) {
        cout << "\nAll rooms are reserved";
    }
}

void HotelMgnt::searchCustomer(const char* pname) {
    Room* current = roomsHead;
    int found = 0;

    while (current) {
        if (current->status == 1 && strcmp(current->cust.name, pname) == 0) {
            cout << "\nCustomer Name: " << current->cust.name;
            cout << "\nRoom Number: " << current->roomNumber;
            cout << "\n\nPress enter for next record\n";
            found = 1;
        }
        current = current->next;
    }

    if (found == 0) {
        cout << "\nPerson not found.\n";
    }
}

void manageRooms(HotelMgnt& hm) {
    int opt, rno;
    int flag = 0;
    char ch;
    do {
        cout << "\n### Manage Rooms ###";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Back to Main Menu";
        cout << "\n\nEnter Option: ";
        cin >> opt;
        switch (opt) {
            case 1:
                cout << "\nEnter Room Number: ";
                cin >> rno;
                flag = 0;
                Room* current = hm.roomsHead;
                while (current) {
                    if (current->roomNumber == rno) {
                        flag = 1;
                        break;
                    }
                    current = current->next;
                }
                if (flag == 1) {
                    cout << "\nRoom Number is Present.\nPlease enter a unique Number";
                } else {
                    hm.addRoom(rno);
                }
                break;
            case 2:
                cout << "\nEnter room number: ";
                cin >> rno;
                hm.searchRoom(rno);
                break;
            case 3:
                // nothing to do
                break;
            default:
                cout << "\nPlease Enter the correct option";
                break;
        }
    } while (opt != 3);
}

int main() {
    HotelMgnt hm;
    int opt;
    char pname[100];
    do {
        cout << "######## Hotel Management #########\n";
        cout << "\n1. Manage Rooms";
        cout << "\n2. Check-In Room";
        cout << "\n3. Available Rooms";
        cout << "\n4. Search Customer";
        cout << "\n5. Check-Out Room";
        cout << "\n6. Guest Summary Report";
        cout << "\n7. Exit";
        cout << "\n\nEnter Option: ";
        cin >> opt;
        switch (opt) {
            case 1:
                manageRooms(hm);
                break;
            case 2:
                hm.checkIn();
                break;
            case 3:
                hm.getAvailRoom();
                break;
            case 4:
                cout << "Enter Customer Name: ";
                cin >> pname;
                hm.searchCustomer(pname);
                break;
            case 5:
                cout << "Enter Room Number : ";
                cin >> rno;
                hm.checkOut(rno);
                break;
            case 6:
                hm.guestSummaryReport();
                break;
            case 7:
                cout << "\nTHANK YOU! FOR USING SOFTWARE\n";
                break;
            default:
                cout << "\nPlease Enter the correct option";
                break;
        }
    } while (opt != 7);

    return 0;
}
