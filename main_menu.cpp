#include<iostream>
using namespace std;

void print_name();
void swap_value();
void getch();
void clrscr();

int main() {
    int CHOICE_CONST = -1;
    int choice = CHOICE_CONST;

    do {
        clrscr();
        cout << "MAIN MENU" << endl;
        cout << "(1) - print name" << endl;
        cout << "(2) - swap variable" << endl;
        cout << "(3) - exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        clrscr();

        switch (choice) {
            case 1:
                print_name();
                getch();
                break;
            case 2:
                swap_value();
                getch();
                break;
            case 3:
                return 0;    
            default:
                cout << "Invalid input";
                getch();
            
        }
        getch();
    }while (choice != 3);

    return 0;
}

void print_name() {
    cout << "Stephen" << endl;
    cout << "Stephen" << endl;
    cout << "Stephen" << endl;
    cout << "Stephen" << endl;
    cout << "Stephen" << endl;
}
void swap_value() {
    int a = 6;
    int b = 5;

    cout << "unswapped:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl << endl;

    int temp = a;
    a = b;
    b = temp;

    cout << "swapped:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b;
}

void getch() {
    cin.ignore();
    cin.clear();
}

void clrscr() {
    system("clear");
}