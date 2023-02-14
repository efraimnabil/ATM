#include <bits/stdc++.h>
#include <fstream>
#include <conio.h>
#include <windows.h>
#define set_color SetConsoleTextAttribute
#define h GetStdHandle(STD_OUTPUT_HANDLE)
#define ll long long
#define sz(s) int(s.size())
#define Digits(n) ((int)log10(n)+1
using namespace std;

struct User {
	ll id, age, balance, account_no;
	char name[10], password[8], gender;
};

struct Admin {
   ll id, age;
   char name[10], password[20], reason[200], gender;
   bool resignation = false;
};

struct ATM {
   ll amount_of_money;
   char password[8];
};

void color_text(string t, int h1, int h2 = 15){
  set_color(h, h1);
  cout << t;
  set_color(h, h2);
}

void printing(string s){
  for(auto& i : s){
    cout << i;
    Sleep(75);
  }
}

void Press_any_key(){
    set_color(h, 7);
    cout << "\n\t\tPress any key to continue... ";
    getch();
}

string getDate(){
  time_t now = time(0);      //current date and time 
  tm* lt = localtime(&now);
  // Date
  int cur_d = lt->tm_mday;
  int cur_m  = 1 + lt->tm_mon;
  int cur_y = 1900 + lt->tm_year;
  string date = to_string(cur_d) + "-" + to_string(cur_m) + "-" + to_string(cur_y);
  // Time
  int hour = (lt->tm_hour % 12 ? : 12);
  string hr = to_string(hour) + ":";
  string m = (lt->tm_min > 9 ? "" : "0") + to_string(lt->tm_min) + ":";
  string s = (lt->tm_sec > 9 ? "" : "0") + to_string(lt->tm_sec) + " ";
  string time = hr + m + s + (lt->tm_hour < 12 ? "AM" : "PM");
  
  return date + "  " + time;
}

void count_down(int n){
  cout << "\t\twait :)  ";
  for(int i = n; i >= 0; i--){
    if(i < 10) cout << ' ';
    cout << i;
    Sleep(250);
    cout << "\b\b";
  }
}

int length(char* a){
    return strlen(a);
}

void set_password(char* passw, int len){
    for(int i = 0; i < len; ){
        char ch = getch();
        if(ch == 13 || ch == 32){ //char p[12]  4
            passw[i] = '\0';
            break;
        }
        else if(ch != 8){
            passw[i++] = ch;
            putch('*');
        }
        else if(i > 0)
            cout << "\b \b", passw[i--] = '\0';
    }
    passw[len] = '\0';
    cout << "\n";
}

void set_text(char* text){
    set_color(h, 6);
    for(int i = 0; ; ){
        char ch = getch();
        if(ch == 13){
            text[i] = '\0';
            break;
        }
        else if(ch != 8){
            text[i++] = ch;
            putch(text[i - 1]);
        }
        else if(i > 0)
            cout << "\b \b", text[i--] = '\0';
    }
    cout << "\n";
}

ll generate_id(){
    ifstream in;
    User u;
    in.open("users.txt", ios::in);
    vector < ll > v;
    in.read((char*)&u, sizeof(u));
    
    while(!in.eof()){
    v.push_back(u.id);
    in.read((char*)&u, sizeof(u)); 
    }
    int real_id = 1001;
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++){
        if(real_id == v[i]){
            real_id++;
        }
        else break;
    }
    
    in.close();
    return real_id;
}

ll generate_acc_no(){
    ll l = 11111111, r = 1e7 * 9;
    ll acc_no =  rand() % (r - l + 1) + l;
    ifstream in;
    User u;
    in.open("users.txt", ios::in);
    vector < ll > v;
    in.read((char*)&u, sizeof(u));
    
    while(!in.eof()){
      v.push_back(u.account_no);
      in.read((char*)&u, sizeof(u)); 
    }
    
    sort(v.begin(), v.end());
    while(binary_search(v.begin(), v.end(), acc_no)){
        acc_no =  rand() % (r - l + 1) + l;
    }
    in.close();
    return acc_no;
}
