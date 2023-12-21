#include <iostream>
#include <fstream>
#include "FtpClient.h"

using std::cout, std::cin;

int main()
{
    try
    {
        FtpClient client("127.0.0.1", 12345);
        cout << client.message() << "\n\n";

        int option;
        bool running = true;
        while (running) {
            cout << "0. Exit" << "\n";
            cout << "1. Login" << "\n";
            cout << "2. List" << "\n";
            cout << "3. Download" << "\n";
            cout << "4. Upload" << "\n";

            cout << "\n" << "Your option: ";
            cin >> option;
            cout << "\n";

            try {
                switch (option) {
                case 0: {
                    cout << "Exiting...";
                    running = false;
                    break;
                }
                case 1: {
                    string user, pass;
                    cout << "Usename: "; cin >> user;
                    cout << "Password: "; cin >> pass;
                    cout << "\n";

                    cout << client.login(user, pass);
                    break;
                }
                case 2: {
                    int d;
                    cout << "Do you want to specify a directory? (0/1)? ";
                    cin >> d;
                    cout << "\n";

                    if (d) {
                        string dir;
                        cin.get();
                        cout << "Directory: "; std::getline(cin, dir);
                        cout << "\n";

                        cout << client.list(dir);
                    }
                    else
                        cout << client.list();
                    break;
                }
                case 3: {
                    string dir;
                    int t;
                    cin.get();
                    cout << "File: "; std::getline(cin, dir);
                    cout << "Is this a text file? (0/1) "; cin >> t;
                    cout << "\n";

                    cout << client.download(dir, t ? text : binary) << "\n";
                    cout << "File downloaded in file.out. Rename and open.";
                    break;
                }
                case 4: {
                    string filepath;
                    int t;
                    cin.get();
                    cout << "File: "; std::getline(cin, filepath);
                    cout << "Is this a text file? (0/1) "; cin >> t;
                    cout << "\n";

                    cout << client.upload(filepath, t ? text : binary);
                    break;
                }
                default:
                    cout << "invalid option" << std::endl;
                }

                cout << "\n\n";
            }
            catch (std::exception e) {
                std::cerr << "Exception caught: " << e.what() << "\n";
            }
        }

        cout << client.disconnect();
    }
    catch (const std::exception e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
