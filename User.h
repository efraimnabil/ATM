
char p[8];

bool is_exist(User u, bool check = 1){
    User U;
    ifstream in;
    set_color(h, 12);
    in.open("users.txt", ios::in);
    if(in.is_open())
    {
        in.read((char*)& U, sizeof(U));
        while(!in.eof()){
          if(check){
            if(u.id == U.id){
              in.close();
              return true;
            }
          }
          else {
            if(u.account_no == U.account_no){
              in.close();
              return true;
            }
          }
          in.read((char*)& U, sizeof(U));
        }
    }
    else cout << "\n\t\tCan't open the specified file...\a\n";
    return false;
}

void Welcome(User u){
    system("cls");
	  cout << "\n" << string(40, ' ');
    int col = (u.gender == 'm' ? 14 : 11);
    set_color(h, col);
    cout << "Welcome " << u.name << "\n";
    cout << string(38, ' ') << string(8 + length(u.name) + 4, '_') << "\n\n";
    set_color(h, 15);
    cout << "\t\t" << string(56, '-') << "\n";
    set_color(h, 10);
    cout << "\t\t ID: " << u.id << "   |   " << "Balance: " << u.balance << "$   |   " << "Acc. No.: " << u.account_no << "\n";
    set_color(h, 13);
}

void receipt(User u){
    string date_time = getDate();
	  string g = (u.gender == 'm' ? "Mr. " : "Mrs. ");
    int col = (u.gender == 'm' ? 14 : 11);
	  set_color(h, col);
    cout << "\t\t____________";
    cout << "Receipt";
    cout << string(14, '_');
    cout << "\n\t\t|" << setw(34) << "\\\n";
    cout << "\t\t|      "; set_color(h, 7); cout << date_time; set_color(h, col); cout << setw(29 - sz(date_time)) << "\\\n"
	       << "\t\t|----------------------------------|\n"
		     << "\t\t|ID: "               << setw(12) << "| " << u.id         << setw(16) << "|\n"
         << "\t\t|----------------------------------|\n"
         << "\t\t|Account no.: "      << setw(3)  << "| " << u.account_no << setw(12)  << "|\n"
         << "\t\t|----------------------------------|\n"
         << "\t\t|Name: "             << setw(10) << "| " << g << u.name  << setw(20 - (length(u.name) + sz(g))) << "|\n"
         << "\t\t|----------------------------------|\n"
         << "\t\t|Balance: "          << setw(7)  << "| " << u.balance    << setw(20 - sz(to_string(u.balance))) << "|\n"
         << "\t\t|__________________________________|\n\n";
}

User getUser(User u, bool check = 0){
    User U;
    ifstream in;
    in.open("users.txt", ios::in);
    in.read((char*)& U, sizeof(U));
    while(!in.eof()){
      if(check){
        if(u.id == U.id){
          in.close();
          return U;
        }
      }
      else {
        if(u.account_no == U.account_no){
          in.close();
          return U;
        }
      }
      in.read((char*)& U, sizeof(U));
    }
    return U;
}

User changePassword(User u){
    int cnt1 = 1, cnt2 = 1, cnt3 = 1;
    oldp:
    cout << "\n\t\tEnter your current password: ";
    char old_pass[8], new_pass[8], confirm[8];
    set_password(old_pass, 4);
    if(!strcmp(old_pass, u.password))
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
         strcpy(u.password, new_pass);
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
    return u;
}

void updateUser(User u, bool check = false){
    if(check) u = changePassword(u);
    User U;
    fstream in;
    in.open("users.txt", ios::in | ios::out);
    set_color(h, 4);
    if(in.is_open())
    {
        in.read((char*)& U, sizeof(U));
        while(!in.eof()){
          if(u.id == U.id){
            int curpos = in.tellg();
            in.seekp(curpos - sizeof(U), ios::beg);
            in.write((char*) &u, sizeof(u));
            break;
          }
          in.read((char*)& U, sizeof(U));
        }
        in.close();
    }
    else cout << "Can't open the specified file...\a\n";
    set_color(h, 15);
}

void deleteUser(User u){
    ifstream in("users.txt", ios::in);
    ofstream out("temp.txt", ios::out);
    User U;
    if(in.is_open())
    {
        bool exist = false;
        
        in.read((char*)& U, sizeof(U));
        while(!in.eof()){
          if(U.id != u.id){
            out.write((char*) &U, sizeof(U));
          }
          else exist = true;
          in.read((char*)& U, sizeof(U));
        }
        in.close();
        out.close();
        remove("users.txt");
        rename("temp.txt", "users.txt");
        if(!exist) cout << "Not exist....\n";
    }
    else cout << "Can't open the specified file...\n";
}

void deposit_to_another_account(User u){
    system("cls");
    set_color(h, 6);
    cout << "\n" << string(32, ' ') << "Deposit To Another Account\n";
    cout << string(30, ' ') << string(30, '_') << "\n\n";
    set_color(h, 15);
    cout << "\t\t" << string(56, '-') << "\n";
    int amount, acc;
    cout << "\n\t\tEnter account number to deposit in: ";
    cin >> acc;
    if(acc == u.account_no){
       set_color(h, 4);
       cout << "\n\t\tThis is your account number :(\a\n";
    }
    else {
        User temp_u;
        temp_u.account_no = acc;
        if(is_exist(temp_u, 0))
        {
            r2:
            set_color(h, 15);
            cout << "\t\tEnter amount of money to transfer: ";
		        cin >> amount;
            if(amount > u.balance){
              set_color(h, 12);
			        cout << "\n\t\tYour balance is less than " << amount << " $\a\n\n";
              set_color(h, 15);
              goto r2;
            }
            else {
              u.balance -= amount;
              updateUser(u);
              User temp_u2 = getUser(temp_u, 0);
              temp_u2.balance += amount;
              updateUser(temp_u2);
              set_color(h, 10);
              cout << "\n\t\tYour operation is done successfully...\n";
              set_color(h, 2);
              cout << "\t\t    Your current balance is " << u.balance << " $\n";
            }
        }
        else {
            set_color(h, 12);
            cout << "\n\t\tSorry, this account number doesn't exist...\a\n";
        }
    }
    Press_any_key();
}

void Switch_User_Options(User u){
  Welcome(u);
	ll opt, amount;
	cout << "\n\t\t1. Deposit\n\t\t2. Withdraw\n\t\t3. Receipt\n\t\t4. Account management\n\t\t5. Deposit to another account\n\t\t";
  color_text("0. Logout", 8); cout << "\n\n\t\tEnter: ";
	cin >> opt;
	switch(opt)
	{
    case 0:
      return;
		case 1:
			cout << "\n\t\tEnter amount of money: ";
			cin >> amount;
			u.balance += amount;
      set_color(h, 10);
			cout << "\n\t\tYour deposit is done successfully...\n";
      updateUser(u);
      set_color(h, 2);
			cout << "\t\t    Your current balance is " << u.balance << " $\n";
      Press_any_key();
			Switch_User_Options(u);
			break;
		case 2:
      r:
      set_color(h, 15);
			cout << "\n\t\tEnter amount of money: ";
			cin >> amount;
			if(amount > u.balance){
        set_color(h, 4);
				cout << "\n\t\tYour balance is less than " << amount << " $\n";
        goto r;
			}
			else {
        set_color(h, 10);
        u.balance -= amount;
        cout << "\n\t\tYour withdraw is done successfully...\n";
        updateUser(u);
      }
      set_color(h, 2);
			cout << "\t\t    Your current balance is " << u.balance << " $\n";
      Press_any_key();
			Switch_User_Options(u);
			break;
    case 3:
      receipt(u);
      Press_any_key();
			Switch_User_Options(u);
			break;
		case 4:
      system("cls");
      set_color(h, 5);
      cout << "\n" << string(38, ' ') << "Manage Account\n";
      cout << string(36, ' ') << "__________________\n\n";
      set_color(h, 15);
      cout << "\t\t" << string(56, '-') << "\n";
      set_color(h, 9);
			cout << "\n\t\t1) Change password  ";
      set_color(h, 4);
      cout << "2) Delete account  ";
      set_color(h, 8);
      cout << "0) Go back";
      set_color(h, 15);
      cout << "\n\n\t\tEnter: ";
      int ch; cin >> ch;
      if(ch == 0) Switch_User_Options(u);
			else if(ch == 1){
        updateUser(u, true);
        return;
      }
      else if(ch == 2){
        set_color(h, 6);
        cout << "\n\t\tYou are about to delete your account... Are you sure?! (Y|N) : ";
        char conf; cin >> conf;
        ll all_money = u.balance;
        if(tolower(conf) == 'y') deleteUser(u);
        else {
          set_color(h, 2);
          cout << "\n\t\tOperation cancelled successfully...\n";
          Press_any_key();
          Switch_User_Options(u);
        }
        set_color(h, 10);
        cout << "\n\t\tYour account has been deleted successfully...\n";
        cout << "\n\t\tAll your money [" << all_money << " $] has been withdrawn successfully...\n";
        Press_any_key();
      }
      else {
        set_color(h, 12);
        cout << "\n\t\tWrong choice...\a\n";
        Press_any_key();
        Switch_User_Options(u);
      }
			break;
		case 5:
      deposit_to_another_account(u);
			Switch_User_Options(u);
      break;
		default:
      set_color(h, 12);
			cout << "\n\t\tInvalid option...\a\n";
      Press_any_key();
			Switch_User_Options(u);
	}
}

void user_loged_in(User u){
  Welcome(u);
	Switch_User_Options(u);
}

void userLogin(){
    system("cls");
    cout << "\n" << string(40, ' ');
    color_text("Login Page\n", 2); cout << string(38, ' '); color_text("______________\n\n", 2);
    cout << "\t\t" << string(56, '-') << "\n";
	  int cntId = 1, cntPass = 1;
    User temp;
	  f:
	  cout << "\n\t\tEnter your ID: ";
	  cin >> temp.id;
	  if(!is_exist(temp)) {
      set_color(h, 12);
	  	cout << "\n\t\tThere is no user with id: " << temp.id << " :(\a\n";
      Press_any_key();
      return;
	  }
	  s:
    set_color(h, 15);
	  cout << "\t\tEnter your password: ";
    char pass[8];
    set_password(pass, 4);
	  if(!strcmp(pass, getUser(temp, 1).password)){
	  	user_loged_in(getUser(temp, 1));
	  }
	  else {
      set_color(h, 12);
	  	cout << "\n\t\tIncorrect password...\a\n\n";
	  	if(cntPass++ == 3){
        set_color(h, 12);
        cout << "\n\t\tlogin failed... You entered wrong password 3 times :(\a\n";
        Press_any_key();
        return;
      }
	  	goto s;
	  }
}

void userSignUp(){
    system("cls");
    cout << "\n" << string(40, ' ');
    color_text("SignUp Page\n", 1); cout << string(38, ' '); color_text("_______________\n\n", 1);
    cout << "\t\t" << string(56, '-') << "\n";
    int cnt1 = 1, cnt2 = 1;
    ofstream fout("users.txt", ios::out | ios::app);
    User u;
    cout << "\n\t\tEnter your name: ";
    cin >> u.name;
    cout << "\t\tEnter your age: ";
    cin >> u.age;
    g:
    cout << "\t\tChoose your gender(M/F): ";
    cin >> u.gender;
    u.gender = tolower(u.gender);
    if(u.gender != 'f' && u.gender != 'm') goto g;
    cout << "\t\tYou should enter initial balance \n\t\t\tat least 100$ to create account : ";
    b:
    cin >> u.balance;
    if(u.balance < 100){
        set_color(h, 6);
        cout << "\t\tPlease enter initial balance at least 100$: ";
        set_color(h, 15);
        goto b;
    }
    p:
    char pass[8];
    cout << "\t\tEnter your password [4 charctars]: ";
	  set_password(pass, 4);
    if(length(pass) != 4){
        if(cnt2++ == 3){
           set_color(h, 12);
           cout << "\n\t\tYou have entered wrong password 3 times... You can't create account :(\a\n";
           goto end2;
        }
        set_color(h, 12);
        cout << "\n\t\tYour password must contain <4 charcters>\n\n";
        set_color(h, 15);
        goto p;
    }
    conf:
    cout << "\t\tConfirm your password: ";
    char confirm[8];
    set_password(confirm, 4);
    if(!strcmp(pass, confirm)){
        strcpy(u.password, pass);
        u.id = generate_id();
        u.account_no = generate_acc_no();
        set_color(h, 10);
        cout << "\n\t\tYour account has been created successfully...\n";
        set_color(h, 2);
        cout << "\n\t\tYour ID is: " << u.id << "  &  Your Acc. No. is: " << u.account_no << " :)\n";
        goto end1;
    }
    else {
        if(cnt1++ == 3){
           set_color(h, 12);
           cout << "\t\tYou have entered wrong password 3 times... You can't create account :(\a\n";
           goto end2;
        }
        set_color(h, 12);
        cout << "\n\t\tYour confirm password doesn't match!\n\n";
        set_color(h, 15);
        goto conf;
    }
    end1:
    fout.write((char*)&u, sizeof(u));
    fout.close();
    Press_any_key();
    user_loged_in(u);
    return;
    end2:
    Press_any_key();
}

void user_mode(){
	  int ch;
    system("cls");
    cout << "\n" << string(40, ' ');
    color_text("User Mode\n", 6);
    cout << string(38, ' ');
    color_text("_____________\n", 6);
    cout << "\n\t\t" << string(56, '-') << "\n";
    color_text("\n\t\t[1] Log in", 2);
    color_text("\t[2] Sign up", 1);
    color_text("\n\n\t\t[0] Go back", 8);
	  cout << "\n\n\t\tEnter: ";
	  cin >> ch;
    if(ch == 0) return;
	  if(ch == 1) {
      userLogin();
      user_mode();
    }
	  else if(ch == 2){
      userSignUp();
      user_mode();
    }
	  else {
	  	color_text("\n\t\tWrong choice...\a\n", 12);
      Press_any_key();
	  	user_mode();
	  }
}
