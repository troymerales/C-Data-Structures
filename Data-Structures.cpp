#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <list>
#include <limits>
#include <unordered_map>
#include <vector>
#include <map>
#include <functional>
#include <queue>

using namespace std;

void runBrowserHistory() {
    const int MAX_HISTORY_SIZE = 10;

    // Set cursor position
    auto gotoxy = [](int x, int y) {
        COORD coord;
        coord.X = x;  // X coordinate
        coord.Y = y;  // Y coordinate
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    };

    // Convert string to lowercase
    auto toLowercase = [](const string& str) -> string {
        string lowerStr;
        for (char c : str) {
            lowerStr += tolower(c);
        }
        return lowerStr;
    };

    // Clear first line
    auto clearfirstine = [&gotoxy]() {
        gotoxy(0,0);
        cout << "                                                     ";
    };

    // Browser history data
    string history[MAX_HISTORY_SIZE];
    int top = -1;
    int current = -1;

    // Compare input and display ascii art
    auto compareInput = [&](const string& input) {
        if (input == "youtube") {
            cout << "\t\t\t/-----------------------------\\" << endl;
            cout << "\t\t\t| YOUTUBE                     |" << endl;
            cout << "\t\t\t|            |\\               |" << endl;
            cout << "\t\t\t|            | \\              |" << endl;
            cout << "\t\t\t|            |  \\             |" << endl;
            cout << "\t\t\t|            |   |            |" << endl;
            cout << "\t\t\t|            |  /             |" << endl;
            cout << "\t\t\t|            | /              |" << endl;
            cout << "\t\t\t|            |/               |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t\\-----------------------------/" << endl;
        }
        else if (input == "reddit") {
            cout << "\t\t\t/-----------------------------\\" << endl;
            cout << "\t\t\t| REDDIT         O            |" << endl;
            cout << "\t\t\t|              / /            |" << endl;
            cout << "\t\t\t|       _   __| |__   _       |" << endl;
            cout << "\t\t\t|      / \\ /       \\ / \\      |" << endl;
            cout << "\t\t\t|      \\ /   0   0   \\ /      |" << endl;
            cout << "\t\t\t|       |             |       |" << endl;
            cout << "\t\t\t|        \\    \\-/    /        |" << endl;
            cout << "\t\t\t|          \\_______/          |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t\\-----------------------------/" << endl;
        }
        else if(input=="facebook") {
            cout << "\t\t\t/-----------------------------\\" << endl;
            cout << "\t\t\t| FACEBOOK      __            |" << endl;
            cout << "\t\t\t|              / /            |" << endl;
            cout << "\t\t\t|           __| |__           |" << endl;
            cout << "\t\t\t|          |__   __|          |" << endl;
            cout << "\t\t\t|             | |             |" << endl;
            cout << "\t\t\t|             | |             |" << endl;
            cout << "\t\t\t|             | |             |" << endl;
            cout << "\t\t\t|             |_|             |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t\\-----------------------------/" << endl;
        }
        else if(input=="x") {
            cout << "\t\t\t/-----------------------------\\" << endl;
            cout << "\t\t\t| X        ____               |" << endl;
            cout << "\t\t\t|          \\   \\  //          |" << endl;
            cout << "\t\t\t|           \\   \\//           |" << endl;
            cout << "\t\t\t|            \\   \\            |" << endl;
            cout << "\t\t\t|             //  \\           |" << endl;
            cout << "\t\t\t|            //\\   \\          |" << endl;
            cout << "\t\t\t|           //  \\   \\         |" << endl;
            cout << "\t\t\t|          //    \\___\\        |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t\\-----------------------------/" << endl;
        }
        else if(input=="instagram") {
            cout << "\t\t\t/-----------------------------\\" << endl;
            cout << "\t\t\t| INSTA  _____________        |" << endl;
            cout << "\t\t\t|       |          o  |       |" << endl;
            cout << "\t\t\t|       |     ___     |       |" << endl;
            cout << "\t\t\t|       |    /   \\    |       |" << endl;
            cout << "\t\t\t|       |   |     |   |       |" << endl;
            cout << "\t\t\t|       |    \\___/    |       |" << endl;
            cout << "\t\t\t|       |             |       |" << endl;
            cout << "\t\t\t|       |_____________|       |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t\\-----------------------------/" << endl;
        }
        else if(input=="tiktok") {
            cout << "\t\t\t/-----------------------------\\" << endl;
            cout << "\t\t\t| TIKTOK         ___          |" << endl;
            cout << "\t\t\t|               |   \\         |" << endl;
            cout << "\t\t\t|               | |\\ \\_       |" << endl;
            cout << "\t\t\t|          ____ | | \\__|      |" << endl;
            cout << "\t\t\t|         / __| | |           |" << endl;
            cout << "\t\t\t|        / /    | |           |" << endl;
            cout << "\t\t\t|        \\ \\___/ /            |" << endl;
            cout << "\t\t\t|         \\_____/             |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t\\-----------------------------/" << endl;
        }
        else if(input=="quora") {
            cout << "\t\t\t/-----------------------------\\" << endl;
            cout << "\t\t\t| QUORA     _______           |" << endl;
            cout << "\t\t\t|          / _____ \\          |" << endl;
            cout << "\t\t\t|         / /     \\ \\         |" << endl;
            cout << "\t\t\t|        | |       | |        |" << endl;
            cout << "\t\t\t|        | |    __ | |        |" << endl;
            cout << "\t\t\t|         \\ \\___\\ \\/ /        |" << endl;
            cout << "\t\t\t|          \\_____\\ \\/ __      |" << endl;
            cout << "\t\t\t|                 \\_\\/_/      |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t\\-----------------------------/" << endl;
        }
        else if(input=="shoppee") {
            cout << "\t\t\t/-----------------------------\\" << endl;
            cout << "\t\t\t| SHOPPEE  _________          |" << endl;
            cout << "\t\t\t|         / _______ \\         |" << endl;
            cout << "\t\t\t|        / /       \\_\\        |" << endl;
            cout << "\t\t\t|        \\ \\________          |" << endl;
            cout << "\t\t\t|         \\________ \\         |" << endl;
            cout << "\t\t\t|        __        \\ \\        |" << endl;
            cout << "\t\t\t|        \\ \\_______/ /        |" << endl;
            cout << "\t\t\t|         \\_________/         |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t\\-----------------------------/" << endl;
        }
        else if(input=="netflix") {
            cout << "\t\t\t/-----------------------------\\" << endl;
            cout << "\t\t\t| NETFLIX____       __        |" << endl;
            cout << "\t\t\t|       |    \\     |  |       |" << endl;
            cout << "\t\t\t|       |     \\    |  |       |" << endl;
            cout << "\t\t\t|       |  |\\  \\   |  |       |" << endl;
            cout << "\t\t\t|       |  | \\  \\  |  |       |" << endl;
            cout << "\t\t\t|       |  |  \\  \\ |  |       |" << endl;
            cout << "\t\t\t|       |  |   \\  \\|  |       |" << endl;
            cout << "\t\t\t|       |__|    \\_____|       |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t\\-----------------------------/" << endl;
        }
        else if(input=="google") {
            cout << "\t\t\t/-----------------------------\\" << endl;
            cout << "\t\t\t| GOOGLE    ________          |" << endl;
            cout << "\t\t\t|          /  ______|         |" << endl;
            cout << "\t\t\t|         /  /                |" << endl;
            cout << "\t\t\t|        /  /   ______        |" << endl;
            cout << "\t\t\t|       |  |   |____  |       |" << endl;
            cout << "\t\t\t|        \\  \\       | |       |" << endl;
            cout << "\t\t\t|         \\  \\_____/  |       |" << endl;
            cout << "\t\t\t|          \\_________/        |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t\\-----------------------------/" << endl;
        }
        else {
            cout << "\t\t\t/-----------------------------\\" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t|     E R R O R    4 0 4      |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t|     WEBSITE NOT FOUND.      |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t|                             |" << endl;
            cout << "\t\t\t\\-----------------------------/" << endl;
        }
        cout << "\nTAB - Visit\t H - History\tLEFT - Back\t RIGHT - Forward\tESC - Home";
    };

    // Push (Visit site)
    auto push = [&](const string& site) {
        if (top < MAX_HISTORY_SIZE - 1) {
            history[++top] = site;
            current = top;
        } else {
            cout << "History is full! Cannot visit more websites." << endl;
        }
    };

    // Pop (Clear last entry)
    auto pop = [&]() {
        if (top >= 0) {
            cout << "\nCleared: " << history[top--] << endl;
            if (current > top) current = top;
        } else {
            cout << "\nNo history to clear." << endl;
        }
    };

    // Clear history based on user choice
    function<void()> clearHistory = [&]() {
        cout << "\n\nClear History Options" << endl;
        cout << "1 - Latest\t2 - All\t\t3 - Custom\tESC - Home";

        char choice = getch();

        switch (choice) {
            case '1':
                pop();
                getch();
                break;
            case '2':
                if (top >= 0) {
                    cout << "\nCleared all browsing history." << endl;
                    top = -1;
                    current = -1;
                } else {
                    cout << "\nNo history to clear." << endl;
                }
                getch();
                break;
            case '3': {
                cout << "\n\nEnter the number of entries to clear: ";
                int num;
                cin >> num;
                while (getchar() != '\n');

                if (num <= 0) {
                    cout << "\nInvalid number. Please enter a positive integer." << endl;
                } else if (num > top + 1) {
                    cout << "\nCannot clear more than " << (top + 1) << " entries." << endl;
                } else {
                    cout << "\nCleared the last " << num << " entries." << endl;
                    top -= num;
                    if (top < -1) top = -1;
                    current = (current > top) ? top : current;
                }
                getch();
                break;
            }
            case 27:
                break;
            default:
                cout << "\nInvalid option. Please try again." << endl;
        }
    };

    // Display history
    auto displayHistory = [&]() {
        if (top == -1) {
            cout << "No websites visited yet." << endl;
        } else {
            cout << "Browser History:" << endl;
            for (int i = 0; i <= top; i++) {
                if (i == current) cout << "-> ";
                else cout << "   ";
                cout << i + 1 << ". " << history[i] << endl;
            }
        }
        clearHistory();
    };

    // Back navigation
    auto back = [&]() {
        gotoxy(0,0);
        if (current > 0) {
            current--;
            cout << "Navigated Back to: " << history[current] << endl;
            compareInput(toLowercase(history[current]));
        } else {
            cout << "No more history to go back." << endl;
        }
    };

    // Forward navigation
    auto forward = [&]() {
        gotoxy(0,0);
        if (current < top) {
            current++;
            cout << "Navigated Forward to: " << history[current] << endl;
            compareInput(toLowercase(history[current]));
        } else {
            cout << "No more history to go forward." << endl;
        }
    };

    // Display home menu
    auto displayHomeMenu = []() {
        cout << "Search Bar: " <<endl;
        cout << "\t\t\t/-----------------------------\\" << endl;
        cout << "\t\t\t| HOME             _          |" << endl;
        cout << "\t\t\t|             /\\  | |         |" << endl;
        cout << "\t\t\t|           /    \\| |         |" << endl;
        cout << "\t\t\t|         /        \\|         |" << endl;
        cout << "\t\t\t|       /__  ____ ___\\        |" << endl;
        cout << "\t\t\t|       |   |    |   |        |" << endl;
        cout << "\t\t\t|       |   |   o|   |        |" << endl;
        cout << "\t\t\t|       |___|____|___|        |" << endl;
        cout << "\t\t\t|                             |" << endl;
        cout << "\t\t\t\\-----------------------------/" << endl;
        cout << "\nTAB - Visit\t H - History\tLEFT - Back\t RIGHT - Forward\tESC - Exit";
    };

    bool running = true, flag = false;

    displayHomeMenu();

    while (running) {
        char input = getch();

        switch (input) {
            case 9: {  // TAB: Visit new site
                string siteName;
                if(flag) {
                    clearfirstine();
                    gotoxy(0,0);
                    cout << "Search Bar: " <<endl;
                }
                gotoxy(12,0);
                getline(cin, siteName);
                compareInput(toLowercase(siteName));
                push(siteName);
                flag = true;
                break;
                system("cls");
            }
            case 'h': // Show history
                system("cls");
                displayHistory();
                system("cls");
                displayHomeMenu();
                break;
            case '3': // Clear history menu directly
                clearHistory();
                getch();
                system("cls");
                break;
            case 75:  // LEFT arrow: Back
                clearfirstine();
                back();
                break;
            case 77:  // RIGHT arrow: Forward
                clearfirstine();
                forward();
                break;
            case 27: // ESC
                system("cls");
                if(flag) {
                    flag = false;
                    displayHomeMenu();
                    break;
                } else {
                    cout << "Exiting program..." << endl;
                    running = false;
                    break;
                }
        }
    }
}

void runNBACardCollection() {
    struct Card {
        string playerName;
        int id;
        int shooting;
        int dribbling;
        int passing;
        int defending;
        Card* prev;
        Card* next;
    };

    // Card pointers for the collection and current display
    Card* cardCollection = nullptr;
    Card* currentCard = nullptr;

    // --- LAMBDA DECLARATIONS (using std::function for proper forward declaration) ---
    // These need to be declared before they are defined or used by other lambdas.

    // createCard does not need std::function as it's not recursive and not called by
    // other lambdas where auto deduction would be an issue.
    auto createCard = [](string name, int id, int shoot, int dribble, int pass, int defend) -> Card* {
        Card* newCard = new Card();
        newCard->playerName = name;
        newCard->id = id;
        newCard->shooting = shoot;
        newCard->dribbling = dribble;
        newCard->passing = pass;
        newCard->defending = defend;
        newCard->prev = nullptr;
        newCard->next = nullptr;
        return newCard;
    };

    // findCardByID is called by addCard, so it needs explicit declaration if addCard is defined later
    std::function<Card*(Card*, int)> findCardByID;

    // addCard calls findCardByID and creates new cards, needs explicit declaration
    std::function<void(string, int, int, int, int, int)> addCard;

    // displayCard, displayAdjacentCards, deleteCard are not recursive and don't call
    // other lambdas in a way that causes issues, so auto is fine.
    auto displayCard = [](Card* card) {
        char x=205,y=201,z=187,a=200,b=188;
        if (card == nullptr) {
            cout << "No card to display." << endl;
            return;
        }
        cout << "\n\n\t\t\t\t\t";
        for(int i=0; i<52; i++) {
            if(i==0) cout << y;
            else if(i==51) cout << z;
            else cout << x;
        }
        cout << "\n";

        cout << "\t\t\t\t\t|\t\t\t\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\t\t\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\tCard ID: " << setw(3) << setfill('0') << card->id << "\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\t\t\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\t" << card->playerName << "\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\t\t\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|--------------------------------------------------|" << endl;
        cout << "\t\t\t\t\t|\t\t\t\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\tShooting\t: " << card->shooting << "\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\t\t\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\tDribbling\t: " << card->dribbling << "\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\t\t\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\tPassing\t\t: " << card->passing << "\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\t\t\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\tDefending\t: " << card->defending << "\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\t\t\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\t\t\t\t\t   |" << endl;
        cout << "\t\t\t\t\t|\t\t\t\t\t\t   |" << endl;
        cout << "\t\t\t\t\t";
        for(int i=0; i<52; i++) {
            if(i==0) cout << a;
            else if(i==51) cout << b;
            else cout << x;
        }
        cout<<endl;
    };

    auto displayAdjacentCards = [](Card* current) {
        if (current == nullptr) {
            cout << "No cards in the collection." << endl;
            return;
        }
        if (current->prev != nullptr) {
            cout << "Previous Card: " << setw(3) << setfill('0') << current->prev->id
                 << " - " << current->prev->playerName;
        } else {
            cout << "Previous Card: None\t\t";
        }
        cout << "\t\t\t\t\t\t\t\t   ";
        if (current->next != nullptr) {
            cout << "Next Card: " << setw(3) << setfill('0') << current->next->id
                 << " - " << current->next->playerName << endl;
        } else {
            cout << "Next Card: None" << endl;
        }
    };

    auto deleteCard = [](Card* card) {
        if (card != nullptr) {
            card->playerName = "E M P T Y";
            card->id = 0;
            card->shooting = 0;
            card->dribbling = 0;
            card->passing = 0;
            card->defending = 0;
        } else {
            cout << "No card to delete." << endl;
        }
    };

    // --- LAMBDA DEFINITIONS ---

    // Define findCardByID
    findCardByID = [&](Card* head, int id) -> Card* {
        Card* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) return temp;
            temp = temp->next;
        }
        return nullptr;
    };

    // Define addCard
    addCard = [&](string name, int id, int shoot, int dribble, int pass, int defend) {
        // Use the explicitly declared findCardByID
        Card* existingCard = findCardByID(cardCollection, id);

        if (existingCard != nullptr) {
            cout << "\n\nCard with ID " << id << " already exists. \n[1]-Replace [2]-Insert with new ID [3]-Cancel: ";
            char choice = getch();
            cout << choice << endl;

            if (choice == '1') {
                existingCard->playerName = name;
                existingCard->shooting = shoot;
                existingCard->dribbling = dribble;
                existingCard->passing = pass;
                existingCard->defending = defend;
                system("cls");
                cout << "C A R D    I D   " << id << "   R E P L A C E D";
            }
            else if (choice == '2') {
                int newID;
                cout << "Enter new ID for the card to be inserted at the end: ";
                cin >> newID;
                system("cls");
                // Use the explicitly declared findCardByID
                if (findCardByID(cardCollection, newID) != nullptr) {
                    cout << "Card with ID " << newID << " already exists. Operation canceled." << endl;
                    return;
                }
                Card* newCard = createCard(name, newID, shoot, dribble, pass, defend);
                if (cardCollection == nullptr) {
                    cardCollection = newCard;
                } else {
                    Card* temp = cardCollection;
                    while (temp->next != nullptr) temp = temp->next;
                    temp->next = newCard;
                    newCard->prev = temp;
                }
                system("cls");
                cout << "C A R D    I D   " << newID << "   I N S E R T E D   A T   T H E   E N D";
            }
            else {
                system("cls");
                cout << "A D D I N G   C A N C E L L E D";
            }
        }
        else {
            Card* newCard = createCard(name, id, shoot, dribble, pass, defend);
            if (cardCollection == nullptr) {
                cardCollection = newCard;
            } else {
                Card* temp = cardCollection;
                while (temp->next != nullptr) temp = temp->next;
                temp->next = newCard;
                newCard->prev = temp;
            }
            system("cls");
            cout << "C A R D   S U C C E S S F U L L Y   A D D E D";
        }
    };


    // Pre-add some NBA cards
    // Calls the addCard lambda
    addCard("LeBron James", 1, 95, 90, 88, 85);
    addCard("Stephen Curry", 2, 98, 92, 85, 75);
    addCard("Kevin Durant", 3, 96, 88, 86, 82);
    addCard("Anthony Davis", 4, 92, 85, 82, 95);
    system("cls");

    currentCard = cardCollection;
    while (true) {
        char choice, ch=196;

        if (currentCard != nullptr) {
            cout << endl;
            for(int i=0; i<140; i++) cout << ch;
            cout << endl;

            displayCard(currentCard);
            displayAdjacentCards(currentCard);

            for(int i=0; i<140; i++) cout << ch;
            cout << endl;
            cout << "\t\t\t\t\t[1]-PREV  [2]-NEXT  [3]-DEL  [4]-ADD  [5]-EXIT" << endl;
            choice = getch();
            system("cls");
        } else {
            cout << endl;
            for(int i=0; i<140; i++) cout << ch;
            for(int i=0; i<22; i++) {
                if(i==11) cout << "\t\t\t\t\t\t   No cards in the collection.";
                cout << "\n";
            }
            for(int i=0; i<140; i++) cout << ch;
            cout << endl;
            cout << "\t\t\t\t\t[1]-PREV  [2]-NEXT  [3]-DEL  [4]-ADD  [5]-EXIT" << endl;
            choice = getch();
            system("cls");
        }

        switch (choice) {
            case '1': // Prev
                if (currentCard != nullptr && currentCard->prev != nullptr) {
                    currentCard = currentCard->prev;
                } else {
                    cout << "Y O U   A R E   A T   T H E   F I R S T   C A R D";
                }
                break;

            case '2': // Next
                if (currentCard != nullptr && currentCard->next != nullptr) {
                    currentCard = currentCard->next;
                } else {
                    cout << "Y O U   A R E   A T   T H E   L A S T   C A R D";
                }
                break;

            case '3': // Delete
                cout << "\n";
                for(int i=0; i<140; i++) cout << ch;
                for(int i=0; i<22; i++) {
                    if(i==11)
                    cout << "\t\t\t\t\t     Are you sure you want to delete this card?\n\n\t\t\t\t\t\t\t      [Y/N]";
                    cout << "\n";
                }
                for(int i=0; i<140; i++) cout << ch;

                if (toupper(getch()) == 'Y') {
                    system("cls");
                    if (currentCard != nullptr) { // Ensure currentCard is not null before accessing its ID
                        cout<< "D E L E T E D   I D   N O   " << currentCard->id;
                        deleteCard(currentCard);
                    } else {
                         cout << "No card selected to delete.";
                    }
                } else {
                    system("cls");
                    cout << "D E L E T E   C A N C E L L E D";
                }
                break;

            case '4': // Add new card
            {
                string name;
                int id, shooting, dribbling, passing, defending;
                cout << "A D D I N G   N E W   C A R D" << endl;
                for(int i=0; i<140; i++) cout << ch;
                cout << endl;
                cout << "\tEnter card ID: ";
                cin >> id;
                cout << "\tEnter player name: ";
                cin.ignore();
                getline(cin, name);
                cout << "\tEnter shooting: ";
                cin >> shooting;
                cout << "\tEnter dribbling: ";
                cin >> dribbling;
                cout << "\tEnter passing: ";
                cin >> passing;
                cout << "\tEnter defending: ";
                cin >> defending;
                addCard(name, id, shooting, dribbling, passing, defending); // Call the addCard lambda
                break;
            }
            case '5': // Exit
                for(int i=0; i<140; i++) cout << ch;
                for(int i=0; i<23; i++) {
                    if(i==11)
                        cout << "\t\t\t\t\t\tAre you sure you want to exit?\n\n\t\t\t\t\t\t            [Y/N]";
                    cout << "\n";
                }
                for(int i=0; i<140; i++) cout << ch;

                if (toupper(getch()) == 'Y') {
                    system("cls");
                    for(int i=0; i<140; i++) cout << ch;
                    for(int i=0; i<25; i++) {
                        if(i==12)
                            cout << "\t\t\t\t\t\t\tE X I T I N G . . .";
                        cout << "\n";
                    }
                    for(int i=0; i<140; i++) cout << ch;
                    getch();
                    return; // Exit the function
                } else {
                    system("cls");
                    cout << "E X I T   C A N C E L L E D";
                }
                break;

            default:
                cout << "I N V A L I D";
                break;
        }
    }
}

void runCoffeeOrderingSystem() {
    struct CoffeeTypeNode {
        string coffeeType;
        CoffeeTypeNode* next;
        CoffeeTypeNode(string type) : coffeeType(type), next(nullptr) {}
    };

    struct CoffeeOrder {
        string name;
        string type;
        string size;
        string customize;
        string dineInOrTakeOut;
        CoffeeOrder* next;
        CoffeeOrder* prev;
        CoffeeOrder() : next(nullptr), prev(nullptr) {}
    };

    struct ServedOrder {
        string name;
        string type;
        string size;
        string customize;
        string dineInOrTakeOut;
        ServedOrder* next;
        ServedOrder() : next(nullptr) {}
    };

    CoffeeTypeNode* coffeeHead = nullptr;
    CoffeeOrder* pendingFront = nullptr;
    CoffeeOrder* pendingRear = nullptr;
    ServedOrder* servedHead = nullptr;

    auto createCoffeeCircularList = [&]() {
        CoffeeTypeNode* caramelMacchiato = new CoffeeTypeNode("Caramel Macchiato");
        CoffeeTypeNode* matchaCoffee = new CoffeeTypeNode("Matcha Coffee");
        CoffeeTypeNode* oreoCoffee = new CoffeeTypeNode("Oreo Coffee");
        CoffeeTypeNode* strawberryCoffee = new CoffeeTypeNode("Strawberry Coffee");
        CoffeeTypeNode* brownSpanishLatte = new CoffeeTypeNode("Brown Spanish Latte");
        CoffeeTypeNode* mochaLatte = new CoffeeTypeNode("Mocha Latte");

        caramelMacchiato->next = matchaCoffee;
        matchaCoffee->next = oreoCoffee;
        oreoCoffee->next = strawberryCoffee;
        strawberryCoffee->next = brownSpanishLatte;
        brownSpanishLatte->next = mochaLatte;
        mochaLatte->next = caramelMacchiato;

        coffeeHead = caramelMacchiato;
    };

    auto addCoffeeToMenu = [&]() {
        string newCoffeeType;
        CoffeeTypeNode* current = coffeeHead;
        CoffeeTypeNode* previous = nullptr;

        system("cls");
        cout << "\nEnter new coffee type: ";
        getline(cin, newCoffeeType);

        CoffeeTypeNode* newCoffee = new CoffeeTypeNode(newCoffeeType);

        do {
            previous = current;
            current = current->next;
        } while (current != coffeeHead);

        previous->next = newCoffee;
        newCoffee->next = coffeeHead;

        cout << "\nNew coffee type '" << newCoffeeType << "' added to the menu!\n";
        getch();
    };

    auto selectCoffeeType = [&](CoffeeOrder* newOrder) {
        CoffeeTypeNode* current = coffeeHead;
        char key;
        bool coffeeChosen = false;

        while (!coffeeChosen) {
            system("cls");
            cout << "\nOrder for " << newOrder->name << "\n\nSelect type of coffee: (Use UP and DOWN to choose, SPACE to select)\n";
            CoffeeTypeNode* temp = current;

            // Display coffee types (exact 6 shown at a time, assumes >=6 types)
            for (int i = 0; i < 6; ++i) {
                if (temp == current) cout << " -> ";
                else cout << "    ";
                cout << temp->coffeeType << "\n";
                temp = temp->next;
            }

            key = _getch();
            if (key == 0 || key == -32) { // arrow keys
                key = _getch();
                if (key == 72) { // up arrow
                    CoffeeTypeNode* prev = current;
                    while (prev->next != current) {
                        prev = prev->next;
                    }
                    current = prev;
                } else if (key == 80) { // down arrow
                    current = current->next;
                }
            } else if (key == 32) { // space to select
                newOrder->type = current->coffeeType;
                coffeeChosen = true;
            }
        }
        cout << "\nYou selected: " << newOrder->type << endl;
    };

    auto createOrder = [&]() -> CoffeeOrder* {
        CoffeeOrder* newOrder = new CoffeeOrder;

        system("cls");

        cout << "\nEnter customer name (max 7 chars): ";
        getline(cin, newOrder->name);

        selectCoffeeType(newOrder);

        cout << "\nSize of Coffee:\n\t1. Small\n\t2. Medium\n\t3. Large\n";
        cout << "Choose (1-3): ";
        char coffeeSize = _getch();
        switch (coffeeSize) {
            case '1': newOrder->size = "Small"; break;
            case '2': newOrder->size = "Medium"; break;
            case '3': newOrder->size = "Large"; break;
            default: newOrder->size = "Unknown"; break;
        }
        cout << newOrder->size << endl;

        cout << "\nCustomize your order (More Coffee, Less Coffee, etc.): ";
        getline(cin, newOrder->customize);

        cout << "\nDine in or Take out:\n\t1. Dine in\n\t2. Take out\n";
        cout << "Choose (1-2): ";
        char dineChoice = _getch();
        switch (dineChoice) {
            case '1': newOrder->dineInOrTakeOut = "Dine in"; break;
            case '2': newOrder->dineInOrTakeOut = "Take out"; break;
            default: newOrder->dineInOrTakeOut = "Unknown"; break;
        }
        cout << newOrder->dineInOrTakeOut << endl;

        return newOrder;
    };

    auto enqueue = [&]() {
        CoffeeOrder* newOrder = createOrder();

        if (pendingFront == nullptr) {
            pendingFront = pendingRear = newOrder;
        } else {
            pendingRear->next = newOrder;
            newOrder->prev = pendingRear;
            pendingRear = newOrder;
        }

        cout << "\nOrder added to queue!\n";
    };

    auto dequeue = [&]() {
        system("cls");

        if (pendingFront == nullptr) {
            cout << "\nQueue is empty!\n";
            getch();
            return;
        }

        CoffeeOrder* temp = pendingFront;

        if (pendingFront == pendingRear) {
            pendingFront = pendingRear = nullptr;
        } else {
            pendingFront = pendingFront->next;
            pendingFront->prev = nullptr;
        }

        ServedOrder* servedOrder = new ServedOrder;
        servedOrder->name = temp->name;
        servedOrder->type = temp->type;
        servedOrder->size = temp->size;
        servedOrder->customize = temp->customize;
        servedOrder->dineInOrTakeOut = temp->dineInOrTakeOut;

        servedOrder->next = servedHead;
        servedHead = servedOrder;

        cout << "\nOrder served for " << temp->name << " (" << temp->type << ", " << temp->size << ", " << temp->customize << ", " << temp->dineInOrTakeOut << ")\n";
        getch();
        delete temp;
    };

    auto displayQueue = [&]() {
        system("cls");
        cout << "________________________________________________________________________" << endl;
        cout << endl;
        cout << "                      P E N D I N G   O R D E R S                       " << endl;
        cout << "________________________________________________________________________" << endl;
        cout << "Last Served Order: ";
        if (servedHead != nullptr) cout << servedHead->name;
        else cout << "None";
        if (pendingFront == nullptr) {
            cout << "\n\n\n\t\t\t   No pending orders.\n\n";
            cout << "________________________________________________________________________" << endl;
            getch();
            return;
        }
        cout << "\n\n";
        CoffeeOrder* current = pendingFront;
        while (current != nullptr) {
            cout << "Name: " << current->name << "\n";
            cout << "Coffee Type: " << current->type << "\n";
            cout << "Size: " << current->size << "\n";
            cout << "Customization: " << current->customize << "\n";
            cout << "Dine in/Take out: " << current->dineInOrTakeOut << "\n\n";
            current = current->next;
        }
        getch();
    };

    auto displayServedOrders = [&]() {
        system("cls");
        cout << "________________________________________________________________________" << endl;
        cout << endl;
        cout << "                      S E R V E D   O R D E R S                         " << endl;
        cout << "________________________________________________________________________" << endl;

        if (servedHead == nullptr) {
            cout << "\n\n\n\t\t\t   No served orders.\n\n";
            cout << "________________________________________________________________________" << endl;
            getch();
            return;
        }

        ServedOrder* current = servedHead;
        while (current != nullptr) {
            cout << "Name: " << current->name << "\n";
            cout << "Coffee Type: " << current->type << "\n";
            cout << "Size: " << current->size << "\n";
            cout << "Customization: " << current->customize << "\n";
            cout << "Dine in/Take out: " << current->dineInOrTakeOut << "\n\n";
            current = current->next;
        }
        getch();
    };

    auto editMenu = [&]() {
        char choice;
        while (true) {
            system("cls");
            cout << "___________ E D I T   M E N U ___________\n\n";
            cout << "1. Add a new coffee type to the menu\n";
            cout << "0. Go back to main menu\n";
            cout << "\nChoose (1 or 0): ";
            choice = _getch();

            if (choice == '1') addCoffeeToMenu();
            else if (choice == '0') return;
            else {
                cout << "\nInvalid choice! Please choose again.\n";
                getch();
            }
        }
    };

    auto mainMenu = [&]() {
        while (true) {
            system("cls");
            cout << "___________________________________________________________" << endl;
            cout << endl;
            cout << "             C O F F E E   O R D E R I N G   S Y S T E M               " << endl;
            cout << "___________________________________________________________" << endl;
            cout << "Last Served Order: ";
            if (servedHead != nullptr) cout << servedHead->name;
            else cout << "None";
            cout << "\n\nChoose an action:\n";
            cout << "\t1. Add Order\n";
            cout << "\t2. Serve Order\n";
            cout << "\t3. View Pending Orders\n";
            cout << "\t4. View Served Orders\n";
            cout << "\t5. Edit Menu\n";
            cout << "\t0. Exit\n";
            cout << "\nChoose (0-5): ";
            char choice = _getch();

            switch (choice) {
                case '1': enqueue(); break;
                case '2': dequeue(); break;
                case '3': displayQueue(); break;
                case '4': displayServedOrders(); break;
                case '5': editMenu(); break;
                case '0': return;
                default:
                    cout << "\nInvalid choice! Press any key to try again.\n";
                    getch();
                    break;
            }
        }
    };

    // Initialize coffee menu
    createCoffeeCircularList();

    // Start main user interface
    mainMenu();
}

void runCorleoneFamilyTree() {
    struct FamilyMember {
        string name;
        FamilyMember* spouse;
        vector<FamilyMember*> children;
        FamilyMember(string n) : name(n), spouse(nullptr) {}
    };

    // Forward declarations with std::function for recursive lambdas
    std::function<void(FamilyMember*, const string&, const string&)> addChild;
    std::function<void(FamilyMember*, const string&, const string&)> addSpouse;
    std::function<FamilyMember*(FamilyMember*, const string&)> postorderSearch;
    std::function<void(FamilyMember*)> preorderTraversal;
    std::function<void(FamilyMember*, int)> displayFamilyTree;
    std::function<void(FamilyMember*)> breadthTraversal;

    // Define addChild
    addChild = [&](FamilyMember* root, const string& parentName, const string& childName) {
        if (!root) return;
        if (root->name == parentName) {
            root->children.push_back(new FamilyMember(childName));
            cout << "Added child " << childName << " under " << parentName << endl;
            return;
        }
        for (FamilyMember* child : root->children) {
            addChild(child, parentName, childName);
        }
    };

    // Define addSpouse
    addSpouse = [&](FamilyMember* root, const string& memberName, const string& spouseName) {
        if (!root) return;
        if (root->name == memberName) {
            if (!root->spouse) {
                root->spouse = new FamilyMember(spouseName);
                cout << "Added spouse " << spouseName << " to " << memberName << endl;
            } else {
                cout << memberName << " already has a spouse." << endl;
            }
            return;
        }
        for (FamilyMember* child : root->children) {
            addSpouse(child, memberName, spouseName);
        }
    };

    // Define postorderSearch
    postorderSearch = [&](FamilyMember* root, const string& name) -> FamilyMember* {
        if (!root) return nullptr;
        for (FamilyMember* child : root->children) {
            FamilyMember* result = postorderSearch(child, name);
            if (result) return result;
        }
        if (root->name == name) return root;
        return nullptr;
    };

    // Define preorderTraversal
    preorderTraversal = [&](FamilyMember* root) {
        if (!root) return;
        cout << root->name;
        if (root->spouse) cout << " (Spouse: " << root->spouse->name << ")";
        cout << endl;
        for (FamilyMember* child : root->children) {
            preorderTraversal(child);
        }
    };

    // Define displayFamilyTree with indentation level
    displayFamilyTree = [&](FamilyMember* root, int level) {
        if (!root) return;
        for (int i = 0; i < level; ++i)
            cout << "   ";
        cout << root->name;
        if (root->spouse) cout << " (Spouse: " << root->spouse->name << ")";
        cout << endl;
        for (FamilyMember* child : root->children) {
            displayFamilyTree(child, level + 1);
        }
    };

    // Define breadthTraversal
    breadthTraversal = [&](FamilyMember* root) {
        if (!root) return;
        queue<FamilyMember*> q;
        q.push(root);
        while (!q.empty()) {
            FamilyMember* current = q.front();
            q.pop();
            cout << current->name;
            if (current->spouse)
                cout << " (Spouse: " << current->spouse->name << ")";
            cout << endl;
            for (FamilyMember* child : current->children) {
                q.push(child);
            }
        }
    };

    FamilyMember* root = new FamilyMember("Antonio Andolini");

    // Pre-add family members
    addChild(root, "Antonio Andolini", "Paolo Andolini");
    addChild(root, "Antonio Andolini", "Vito Andolini Corleone");

    addChild(root, "Vito Andolini Corleone", "Sonny Corleone");
    addSpouse(root, "Sonny Corleone", "Sandra Colombo");
    addChild(root, "Sonny Corleone", "Francesca Corleone");
    addChild(root, "Sonny Corleone", "Kathryn Corleone");
    addChild(root, "Sonny Corleone", "Frank Corleone");
    addChild(root, "Sonny Corleone", "Santino Corleone, Jr.");

    addChild(root, "Vito Andolini Corleone", "Tom Hagen");
    addSpouse(root, "Tom Hagen", "Theresa");
    addChild(root, "Tom Hagen", "Frank Hagen");
    addChild(root, "Tom Hagen", "Andrew Hagen");
    addChild(root, "Tom Hagen", "Christina Hagen");
    addChild(root, "Tom Hagen", "Gianna Hagen");

    addChild(root, "Vito Andolini Corleone", "Michael Corleone");
    addSpouse(root, "Michael Corleone", "Kay Adams");
    addChild(root, "Michael Corleone", "Anthony Vito Corleone");
    addChild(root, "Michael Corleone", "Mary Corleone");

    addChild(root, "Vito Andolini Corleone", "Connie Corleone");
    addSpouse(root, "Connie Corleone", "Carlo Rizzi");
    addChild(root, "Connie Corleone", "Victor Rizzi");
    addChild(root, "Connie Corleone", "Michael Francis Rizzi");

    addChild(root, "Vito Andolini Corleone", "Fredo Corleone");
    addSpouse(root, "Fredo Corleone", "Deanna Dunn");

    system("cls");

    cout << "Imagine stepping into a world of power, secrecy, and whispered menace - this is the world of the \n";
    cout << "Corleone family. Founded in the shadows of Sicily and later entrenched in New York's criminal \n";
    cout << "underworld, the Corleones have built an empire that stretches from the alleyways of Little \n";
    cout << "Italy to the corridors of Wall Street.\n";
    cout << "\nThey are no ordinary family; they are bound by blood, not just in lineage, but in the violence\n";
    cout << "that defines their legacy.\n\n";

    int choice;
    while (true) {
        cout << "The Corleone Family\n\n";
        displayFamilyTree(root, 0);
        cout << "\nMenu:\n";
        cout << "1. Add Child\n";
        cout << "2. Add Spouse\n";
        cout << "3. Search Member\n";
        cout << "4. Display Family\n";
        cout << "5. Display Family (by level of power)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string parentName, childName;
                cout << "Enter parent's name: ";
                cin.ignore();
                getline(cin, parentName);
                cout << "Enter child's name: ";
                getline(cin, childName);
                addChild(root, parentName, childName);
                getch();
                system("cls");
                break;
            }
            case 2: {
                string memberName, spouseName;
                cout << "Enter family member's name: ";
                cin.ignore();
                getline(cin, memberName);
                cout << "Enter spouse's name: ";
                getline(cin, spouseName);
                addSpouse(root, memberName, spouseName);
                getch();
                system("cls");
                break;
            }
            case 3: {
                string searchName;
                cout << "Enter name to search: ";
                cin.ignore();
                getline(cin, searchName);
                FamilyMember* result = postorderSearch(root, searchName);
                if (result) {
                    cout << "Found: " << result->name << endl;
                    if (result->spouse) {
                        cout << "Spouse: " << result->spouse->name << endl;
                    }
                } else {
                    cout << searchName << " not found in the family tree." << endl;
                }
                getch();
                system("cls");
                break;
            }
            case 4:
                system("cls");
                cout << "\nFamily Tree:\n";
                preorderTraversal(root);
                getch();
                system("cls");
                break;
            case 5:
                system("cls");
                cout << "\nFamily Tree (By level of power):\n";
                breadthTraversal(root);
                getch();
                system("cls");
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice, try again.\n";
                break;
        }
    }
}

void runStudentDirectoryHash() {
    const int TABLE_SIZE = 10;

    class Student {
    public:
        string familyName;
        string firstName;
        string middleName;
        int age;
        char gender;
        int idNumber;
        string contactNumber;
        string address;

        Student(string family, string first, string middle, int a, char g, int id, string contact, string addr)
            : familyName(family), firstName(first), middleName(middle), age(a), gender(g), idNumber(id), contactNumber(contact), address(addr) {}
    };

    class HashTable {
    private:
        list<Student> table[TABLE_SIZE];

    public:
        int hashFunction(int id) {
            return id % TABLE_SIZE;
        }

        void enrollStudent(const Student& student) {
            int index = hashFunction(student.idNumber);
            table[index].push_back(student);
        }

        void displayStudents() {
            cout << "\n\n";
            cout << "Index\t" << "ID Number\t" << "Student Name\t\t" << "Age\t" << "Gender\t" << "Contact Number\t" << "Address\n";
            cout << "--------------------------------------------------------------------------------------------------------\n";

            for (int i = 0; i < TABLE_SIZE; ++i) {
                for (const auto& student : table[i]) {
                    cout << i << "\t[" << student.idNumber << "]\t"
                         << student.firstName << " " << student.middleName[0] << ". " << student.familyName << "\t"
                         << student.age << "\t" << student.gender << "\t"
                         << student.contactNumber << "\t" << student.address << "\n";
                }
            }

            cout << "--------------------------------------------------------------------------------------------------------\n";
            getch();
            system("cls");
        }

        void searchById() {
            int id;
            cout << "Enter ID Number to search: ";
            cin >> id;

            int index = hashFunction(id);
            bool found = false;

            for (const auto& student : table[index]) {
                if (student.idNumber == id) {
                    cout << "Student found: " << student.firstName << " " << student.middleName[0] << ". " << student.familyName << "\n";
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Student not found\n";
            }
            getch();
            system("cls");
        }
    };

    auto enrollStudent = [](HashTable& studentTable) {
        string family, first, middle, contact, addr;
        int age, id;
        char gender;

        cout << "\nEnter the following details:\n";
        cout << "Last Name: ";
        cin.ignore();
        getline(cin, family);

        cout << "First Name: ";
        getline(cin, first);

        cout << "Middle Name: ";
        getline(cin, middle);

        cout << "Age: ";
        cin >> age;

        cout << "Gender (M/F): ";
        cin >> gender;

        cout << "ID Number: ";
        cin >> id;

        cout << "Enter Contact Number: ";
        cin >> contact;

        cout << "Address: ";
        cin.ignore();
        getline(cin, addr);

        Student newStudent(family, first, middle, age, gender, id, contact, addr);
        studentTable.enrollStudent(newStudent);
        cout << "Succesfully enrolled.\n";
        getch();
        system("cls");
    };

    auto menu = [&](HashTable& studentTable) {
        int choice;
        do {
            cout << "\nMain Menu:\n";
            cout << "1. Enroll\n";
            cout << "2. View Directory\n";
            cout << "3. Search by ID\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            system("cls");
            switch (choice) {
                case 1:
                    enrollStudent(studentTable);
                    break;
                case 2:
                    studentTable.displayStudents();
                    break;
                case 3:
                    studentTable.searchById();
                    break;
                case 4:
                    cout << "Thank you for using!\n";
                    break;
                default:
                    cout << "Invalid choice\n";
            }
        } while (choice != 4);
    };

    HashTable studentTable;
    menu(studentTable);
}

void runAncestralBreathingTechniques() {
    class Node {
    public:
        string name;
        vector<Node*> children;
        Node(string name) : name(name) {}
    };

    class Graph {
    private:
        unordered_map<string, Node*> nodes;

    public:
        void addNode(const string& name) {
            if (nodes.find(name) == nodes.end()) {
                nodes[name] = new Node(name);
            }
        } //O(1)

        void addEdge(const string& parent, const string& child) {
            addNode(parent);
            addNode(child);
            nodes[parent]->children.push_back(nodes[child]);
        }

        void findAncestors(const string& technique, vector<string>& ancestors) {
            for (const auto& pair : nodes) {
                const string& name = pair.first;
                Node* node = pair.second;

                for (Node* child : node->children) {
                    if (child->name == technique) {
                        ancestors.push_back(name);
                        findAncestors(name, ancestors);
                    }
                }
            }
        } //O(V+E)
    };

    class RecruitManager {
    private:
        struct Recruit {
            string name;
            string rank;
            string innateTechnique;
        };
        vector<Recruit> recruits;

    public:
        void addRecruit(const string& name, const string& rank, const string& innateTechnique) {
            recruits.push_back({name, rank, innateTechnique});
        } //O(1)

        void viewRecruits() const {
            if (recruits.empty()) {
                cout << "No recruits found.\n";
                return;
            }

            cout << "\nList of Recruits:\n";
            cout << "NAME\t\tRANK\t\tBREATHING TECHNIQUE\n";
            for (const auto& recruit : recruits) {
                cout << recruit.name << "\t\t" << recruit.rank << "\t\t" << recruit.innateTechnique << endl;
            }
        } //O(x)
    };

    auto printHeader = []() {
        cout << "______                             _____                             \n";
        cout << "|  _  \\                           /  __ \\                          \n";
        cout << "| | | |___ _ __ ___   ___  _ __   | /  \\/ ___  _ __ _ __  ___       \n";
        cout << "| | | / _ \\ '_ ` _ \\ / _ \\| '_ \\  | |    / _ \\| '__| '_ \\/ __| \n";
        cout << "| |/ /  __/ | | | | | (_) | | | | | \\__/\\ (_) | |  | |_) \\__\\    \n";
        cout << "|___/ \\___|_| |_| |_|\\___/|_| |_|  \\____/\\___/|_|  | .__/|___/   \n";
        cout << "                                                   | |               \n";
        cout << "                                                   |_|               \n";
        cout << ",_._._._._._._._._|__________________________________________________________,\n";
        cout << "|_|_|_|_|_|_|_|_|_|_________________________________________________________/\n";
        cout << "                  !\n";
    };

    Graph breathingGraph;
    RecruitManager recruitManager;

    // Build the breathing technique graph
    breathingGraph.addEdge("Sun", "Thunder");
    breathingGraph.addEdge("Sun", "Flame");
    breathingGraph.addEdge("Sun", "Wind");
    breathingGraph.addEdge("Sun", "Water");
    breathingGraph.addEdge("Sun", "Stone");
    breathingGraph.addEdge("Thunder", "Storm");
    breathingGraph.addEdge("Thunder", "Sound");
    breathingGraph.addEdge("Sound", "Speech");
    breathingGraph.addEdge("Flame", "Cursed");
    breathingGraph.addEdge("Cursed", "Love");
    breathingGraph.addEdge("Wind", "Sand");
    breathingGraph.addEdge("Sand", "Blind");
    breathingGraph.addEdge("Water", "Mist");
    breathingGraph.addEdge("Water", "Flower");
    breathingGraph.addEdge("Flower", "Insect");
    breathingGraph.addEdge("Flower", "Beast");
    breathingGraph.addEdge("Beast", "Serpent");
    breathingGraph.addEdge("Stone", "Mountain");

    // Pre-add some recruits
    recruitManager.addRecruit("Tanjiro", "Hinoe", "Sun");
    recruitManager.addRecruit("Zenitsu", "Mizunoe", "Thunder");
    recruitManager.addRecruit("Shinobu", "Hashira", "Insect");

    int choice;

    do {
        system("cls");

        printHeader();
        cout << "\n\nMenu:\n";
        cout << "   1. Enter new recruit\n";
        cout << "   2. View list of recruits\n";
        cout << "   3. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1: {
                string name, rank, innateTechnique;

                system("cls");
                printHeader();
                cout << "\nCongratulations on passing the Final Selection.\n";

                cout << "\nBased on your innate breathing technique, you can still learn other techniques\nif they are an ancestor of your technique. Enter the following details to find out.";
                // Get user input

                cout << "\n\nEnter recruit's details:\n";
                cout << "Name: ";
                cin >> name;
                cout << "Rank: ";
                cin >> rank;
                cout << "Innate breathing technique: ";
                cin >> innateTechnique;

                recruitManager.addRecruit(name, rank, innateTechnique);

                vector<string> ancestors;
                breathingGraph.findAncestors(innateTechnique, ancestors);

                cout << "\nBreathing Techniques You Can Learn:\n";
                for (const string& ancestor : ancestors) {
                    cout << "\t" << ancestor << endl;
                }

                cout << "\nPress enter to continue...";
                getch();
                break;
            }
            case 2:
                system("cls");
                printHeader();
                recruitManager.viewRecruits();
                getch();
                break;
            case 3:
                system("cls");
                printHeader();
                cout << "\nGood luck on your journey, warrior.\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 3);
}


int main() {
    int choice;
    do {
        system("cls");
        cout << "=== Data Structure and Algorithms Main Menu ===\n\n";
        cout << "1. NBA Card Collection (Doubly Linked List)\n";
        cout << "2. Browser History (Stack)\n";
        cout << "3. Coffee Ordering System (Queue)\n";
        cout << "4. Corleone Family Tree (Tree)\n";
        cout << "5. Student Directory (Hash)\n";
        cout << "6. Ancestral Breathing Techniques (Graph)\n";
        cout << "7. Exit\n";
        cout << "\nEnter your choice (1-7): ";
        cin >> choice;

        switch (choice) {
            case 1:
                runNBACardCollection();
                break;
            case 2:
                runBrowserHistory();
                break;
            case 3:
                runCoffeeOrderingSystem();
                break;
            case 4:
                runCorleoneFamilyTree();
                break;
            case 5:
                runStudentDirectoryHash();
                break;
            case 6:
                runAncestralBreathingTechniques();
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice, please enter a number from 1 to 7.\n";
                system("pause");
                break;
        }
    } while (choice != 7);

    return 0;
}