#include "general_fun.h"
#include "User.h"
#include "Admin.h"
#include "System.h"
// 1200 -> 1600
int main(){
    srand(time(0));

    do {
        system("cls");
        cout << "\n" << string(39, ' ');
        set_color(h, 240);
        cout << " Main Menu ";
        set_color(h, 15);
        cout << "\n";
        cout << string(38, ' ') << "_____________\n\n\t\t";
        cout << string(56, '~') << "\n\t\t";
        cout << "|  "; color_text("[1] User", 6); cout << "  |  "; color_text("[2] Admin", 9);
        cout << "  |  "; color_text("[3] System", 8); cout << "  |  "; color_text("[0] Exit", 4);
        cout << "  |\n\t\t";
        cout << string(56, '~') << "\n";
        cout << "\n\t\tEnter a choice: ";
        int opt;
        cin >> opt;
        if(opt == 1) {
            user_mode();
            continue;
        }
        else if(opt == 2){
            admin_mode();
            continue;
        }
        else if(opt == 3){
            system_mode();
            continue;
        }
        else if(opt == 0) goto end;
        else {
            color_text("\n\t\tInvalid option...\a\n", 12, 12);
            Press_any_key();
        }
    } while(true);
    end:
    count_down(15);
    cout << "\n\n";
    return 0;
}