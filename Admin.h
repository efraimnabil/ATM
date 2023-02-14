using namespace std;

bool A_is_exist(ll id){
    Admin A;
    ifstream in;
    set_color(h, 12);
    in.open("admins.txt", ios::in);
    if(in.is_open())
    {
        in.read((char*)& A, sizeof(A));
        while(!in.eof()){
          if(id == A.id){
            in.close();
            return true;
          }
          in.read((char*)& A, sizeof(A));
        }
    }
    else cout << "\n\t\tCan't open the specified file...\n";
    return false;
}

void Welcome_Admin(Admin a){
    system("cls");
    set_color(h, 9);
	  cout << "\n" << string(40, ' ') << "Welcome " << a.name << "\n";
    cout << string(38, ' ') << string(8 + length(a.name) + 4, '_') << "\n\n";
    set_color(h, 15);
    cout << "\t\t" << string(56, '-') << "\n";
}

Admin A_changePassword(Admin a){
    int cnt1 = 1, cnt2 = 1, cnt3 = 1;
    oldp:
    cout << "\n\t\tEnter your current password: ";
    char old_pass[8], new_pass[8], confirm[8];
    set_password(old_pass, 4);
    if(!strcmp(old_pass, a.password))
    {
       newp:
       cout << "\n\t\tEnter your new password [4 charcters]: ";
       set_password(new_pass, 4);
       if(length(new_pass) != 4){
          if(cnt1++ == 3){
             set_color(h, 12);
             cout << "\n\t\tYou have entered wrong password 3 times...\n\t\t\tYou can't change password now :(\a\n";
             goto end;
          }
          set_color(h, 12);
          cout << "\n\t\tYour password must contain <4 charcters>\n";
          set_color(h, 15);
          goto newp;
       }
       confp:
       cout << "\n\t\tConfirm your new password [4 charcters]: ";
       set_password(confirm, 4);
       if(!strcmp(new_pass, confirm)){
         strcpy(a.password, new_pass);
         set_color(h, 10);
         cout << "\n\t\tYour password has been changed successfully...\n";
         goto end;
       }
       else {
         if(cnt3++ == 3){
            set_color(h, 12);
            cout << "\n\t\tYou have entered wrong password 3 times...\n\t\t\tYou can't change password now :(\a\n";
            goto end;
         }
         set_color(h, 12);
         cout << "\n\t\tYour confirm password doesn't match!\n";
         set_color(h, 15);
         goto confp;
       }
    }
    else {
      if(cnt2++ == 3){
         set_color(h, 12);
         cout << "\n\t\tYou have entered wrong password 3 times...\n\t\t\tYou can't change password now :(\a\n";
         goto end;
      }
      set_color(h, 12);
      cout << "\n\t\tYour current password isn't correct!\n";
      set_color(h, 15);
      goto oldp;
    }
    end:
    Press_any_key();
    return a;
}

void updateAdmin(Admin a, bool check = false){
    if(check) a = A_changePassword(a);
    Admin A;
    fstream in;
    in.open("admins.txt", ios::in | ios::out);
    set_color(h, 4);
    if(in.is_open())
    {
        in.read((char*)& A, sizeof(A));
        while(!in.eof()){
          if(a.id == A.id){
            int curpos = in.tellg();
            in.seekp(curpos - sizeof(A), ios::beg);
            in.write((char*) &a, sizeof(a));
            break;
          }
          in.read((char*)& A, sizeof(A));
        }
        in.close();
    }
    else cout << "Can't open the specified file...\a\n";
    set_color(h, 15);
}

void deleteAllUsers(){
    ifstream in("users.txt", ios::in);
    ofstream out("temp.txt", ios::out);
    in.close();
    out.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
}

void Add_User(){
    ofstream fout("users.txt", ios::out | ios::app);
    User u;
    cout << "\n\t\tEnter user name: ";
    cin >> u.name;
    cout << "\t\tEnter user age: ";
    cin >> u.age;
    g:
    cout << "\t\tChoose user gender(M/F): ";
    cin >> u.gender;
    u.gender = tolower(u.gender);
    if(u.gender != 'f' && u.gender != 'm') goto g;
    cout << "\t\tEnter User initial balance  \n\t\t\tat least 100$ to create account : ";
    b:
    cin >> u.balance;
    if(u.balance < 100){
        set_color(h, 6);
        cout << "\t\tPlease Enter initial balance at least 100$: ";
        set_color(h, 15);
        goto b;
    }
    char pass[8]; 
    cout << "\t\tEnter user password: ";
    set_password(pass, 4);
    if(length(pass) != 4){
        set_color(h, 12);
        cout << "\n\t\tPassword must contain <4 charcters>\n\n";
        goto end2;
    }
    cout << "\t\tConfirm password: ";
    char confirm[8];
    set_password(confirm, 4);
    if(strcmp(pass, confirm) == 0){
        strcpy(u.password, pass);
        u.id = generate_id();
        u.account_no = generate_acc_no();
        set_color(h, 10);
        cout << "\n\t\tUser account has been created successfully...\n";
        set_color(h, 2);
        cout << "\n\t\tUser ID is: " << u.id << "  &  User Acc. No. is: " << u.account_no << "\n";
        goto end1;
    }
    else {
        set_color(h, 12);
        cout << "\n\t\tconfirm password doesn't match!\n\n";
        goto end2;
    }
    end1:
    fout.write((char*)&u, sizeof(u));
    fout.close();
    end2:
    return;
}

void print_user(User u, int n = 0){
	  string g = (u.gender == 'm' ? "Mr. " : "Mrs. ");
    int col = (u.gender == 'm' ? 14 : 11);
	  set_color(h, col);
    cout << "\t\t\t_____________";
    cout << "User #" << n;     //User #1
    cout << string(16, '_');
    cout << "\n\t\t\t|" << setw(36) << "|\n";
    cout << "\t\t\t|Name: "             << setw(10) << "| " << g << u.name  << setw(20 - (length(u.name) + sz(g))) << "|\n"
         << "\t\t\t|----------------------------------|\n"
		     << "\t\t\t|ID: "               << setw(12) << "| " << u.id         << setw(16) << "|\n"
         << "\t\t\t|----------------------------------|\n"
         << "\t\t\t|Account no.: "      << setw(3)  << "| " << u.account_no << setw(12) << "|\n"
         << "\t\t\t|----------------------------------|\n"
         << "\t\t\t|Balance: "          << setw(7)  << "| " << u.balance    << " $" << setw(18 - sz(to_string(u.balance))) << "|\n"
         << "\t\t\t|----------------------------------|\n"
		     << "\t\t\t|Password: "         << setw(6) << "| "  << u.password   << setw(16) << "|\n"
         << "\t\t\t|__________________________________|\n\n";
}

void PrintAllUsers(){
    ifstream in;
    User u;
	  int n = 1;
    in.open("users.txt", ios::in);
    in.read((char*)&u, sizeof(u));
    while(!in.eof()){
	     print_user(u, n++);
       in.read((char*)&u, sizeof(u)); 
    }
    in.close();
}

void Switch_Admin_Options(Admin a){
    system("cls");
    Welcome_Admin(a);
	  ll opt, id;
	  User temp;
	  s:
	  cout << "\n\t\t1. Show all users\n\t\t2. find user\n\t\t3. Add user\n\t\t4. Delete user\n\t\t5. Delete all users\n\t\t6. Account management";
    color_text("\n\t\t0. Logout", 8); cout << "\n\n\t\tEnter: ";
	  cin >> opt;
	  switch(opt)
	  {
        case 0:
          return;
	      case 1:
          system("cls");
          cout << "\n" << string(38, ' ') << "All Users\n";
          cout << string(36, ' ') << "_____________\n\n";
          cout << "\t\t" << string(56, '-') << "\n";
	        PrintAllUsers();
          Press_any_key();
          Switch_Admin_Options(a);
	        break;
	      case 2:
	        cout << "\t\tEnter ID to find: ";
	        cin >> id;
          temp.id = id;
	        if(is_exist(temp, true)){
	        	print_user(getUser(temp, true));
	        }
	        else {
              set_color(h, 12);
	        	  cout << "\n\t\tThere is no user with id = " << temp.id << " :(\a\n";
          }
          Press_any_key();
	        Switch_Admin_Options(a);
	        break;
          case 3:
	        Add_User();
          Press_any_key();
	        Switch_Admin_Options(a);
	        break;
	      case 4:
	        cout << "\n\t\tEnter ID to delete: ";
          cin >> temp.id;
          set_color(h, 12);
          if(is_exist(temp)){
              set_color(h, 6);
              cout << "\n\t\tYou are about to delete this user account... Are you sure?! (Y|N) : ";
              char conf; cin >> conf;
              set_color(h, 10);
              if(tolower(conf) == 'y'){
                  deleteUser(temp);
                  cout << "\n\t\tUser has been deleted successfully...\n";
              }
              else cout << "\n\t\tOperation cancelled successfully...\n";
          }
          else cout << "\n\t\tThere is no user with id = " << temp.id << " :(\a\n";
          Press_any_key();
          Switch_Admin_Options(a);
          break;
	      case 5:
          {
            set_color(h, 6);
	          cout << "\n\t\tYou are about to delete all users... Are you sure?! (Y|N) : ";
            char conf; cin >> conf;
            set_color(h, 10);
            if(tolower(conf) == 'y'){
                deleteAllUsers();
                cout << "\n\t\tAll users have been deleted successfully...\n";
            }
            else cout << "\n\t\tOperation cancelled successfully...\n";
            Press_any_key();
            Switch_Admin_Options(a);
	        break;
          }
          case 6:
          {
            system("cls");
            set_color(h, 13);
            cout << "\n" << string(38, ' ') << "Manage Account\n";
            cout << string(36, ' ') << "__________________\n\n";
            set_color(h, 15);
            cout << "\t\t" << string(56, '-') << "\n";
            set_color(h, 9);
	          cout << "\n\t\t1) Change password";
            set_color(h, 4);
            cout << "\n\t\t2) Request for resignation";
            set_color(h, 8);
            cout << "\n\t\t0) Go back";
            set_color(h, 15);
            cout << "\n\n\t\tEnter: ";
            int ch; cin >> ch;
            if(ch == 0) Switch_Admin_Options(a);
	          else if(ch == 1){
              updateAdmin(a, true);
              //Switch_Admin_Options(a);
              return;
            }
            else if(ch == 2) {
                w:              
                set_color(h, 15);
                cout << "\n\t\tWrite your reason for resignation:\n\t\t> ";
                set_color(h, 6); set_text(a.reason);
                if(length(a.reason) == 0){
                    set_color(h, 12);
                    cout << "\n\t\tYou should write a reason!\n";
                    goto w;
                }
                a.resignation = true;
                updateAdmin(a);
                set_color(h, 10);
                cout << "\n\t\tYour request has been sent successfully...\n";
                set_color(h, 2);
                cout << "\n\t\tWait for the manager's review :)\n";
            }
            else {
              set_color(h, 12);
	            cout << "\n\t\tWrong choice!\a\n";
            }
            Press_any_key();
            Switch_Admin_Options(a);
            break;
          }
	      default:
          set_color(h, 12);
	        cout << "\n\t\tInvalid option...\a\n";
	        Press_any_key();
          Switch_Admin_Options(a);
	  }
}

void admin_loged_in(Admin a){
	Switch_Admin_Options(a);
}

Admin getAdmin(ll id){
    Admin A;
    ifstream in;
    in.open("admins.txt", ios::in);
    in.read((char*)& A, sizeof(A));
    while(!in.eof()){
      if(id == A.id){
        in.close();
        return A;
      }
      in.read((char*)& A, sizeof(A));
    }
    return A;
}

void admin_mode(){
	  ll id;
    set_color(h, 15);
	  cout << "\t\tEnter your ID: ";
	  cin >> id;
	  if(!A_is_exist(id)) {
      set_color(h, 12);
	  	cout << "\n\t\tThere is no Admin with id = " << id << " login failed :(\a\n";
      Press_any_key();
	  	return;
	  }
    set_color(h, 15);
	  cout << "\t\tEnter your password: ";
    char pass[8];
    set_password(pass, 4);
	  if(!strcmp(pass, getAdmin(id).password)){
	  	admin_loged_in(getAdmin(id));
	  }
	  else {
      set_color(h, 12);
	  	cout << "\n\t\tIncorrect password... login failed :(\a\n";
      Press_any_key();
	  }
}
