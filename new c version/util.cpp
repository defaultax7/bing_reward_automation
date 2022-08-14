#define WINVER 0x0500
#include <windows.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

INPUT ip;

char tab = 0x09;
char a = 0x41;
char e = 0x45;
char m = 0x4D;
char enter = 0x0D;
char control = VK_CONTROL;
char l_control = 0xA2;
char right_arrow = 0x27;
char down_arrow = 0x28;
string word_list[10000];

void load_word_list()
{
    string line;
    int i = 0;
    ifstream myfile("list.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            word_list[i++] = line;
        }
        myfile.close();
    }
}

void init()
{
    // set the seed using system time
    srand(time(0));

    load_word_list();

    while (!(GetKeyState(enter) & 0x8000))
    {
    }

    Sleep(500);
}

void key_press(char code)
{
    ip.ki.wVk = code;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));

    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &ip, sizeof(INPUT));

    // get a random intervel between 0 to 150
    Sleep(rand() % 150 + 30);
}

void call_bing_search()
{
    INPUT bing_ip;
    bing_ip.type = INPUT_KEYBOARD;
    bing_ip.ki.wScan = 0;
    bing_ip.ki.time = 0;
    bing_ip.ki.dwExtraInfo = 0;

    bing_ip.ki.wVk = control;
    bing_ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &bing_ip, sizeof(INPUT));
    bing_ip.ki.wVk = e;
    SendInput(1, &bing_ip, sizeof(INPUT));

    bing_ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &bing_ip, sizeof(INPUT));
    bing_ip.ki.wVk = control;
    SendInput(1, &bing_ip, sizeof(INPUT));

    // get a random intervel between 0 to 150
    Sleep(rand() % 150 + 30);
}

void toggle_mobile_view()
{
    INPUT mobile_ip;
    mobile_ip.type = INPUT_KEYBOARD;
    mobile_ip.ki.wScan = 0;
    mobile_ip.ki.time = 0;
    mobile_ip.ki.dwExtraInfo = 0;

    mobile_ip.ki.wVk = control;
    mobile_ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &mobile_ip, sizeof(INPUT));
    mobile_ip.ki.wVk = VK_SHIFT;
    SendInput(1, &mobile_ip, sizeof(INPUT));
    mobile_ip.ki.wVk = m;
    SendInput(1, &mobile_ip, sizeof(INPUT));

    mobile_ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
    SendInput(1, &mobile_ip, sizeof(INPUT));
    mobile_ip.ki.wVk = VK_SHIFT;
    SendInput(1, &mobile_ip, sizeof(INPUT));
    mobile_ip.ki.wVk = control;
    SendInput(1, &mobile_ip, sizeof(INPUT));

    Sleep(400);
}

void type_word(string word)
{

    for (int i = 0; i < word.length(); ++i)
    {
        key_press(toupper(word.at(i)));
        cout << word.at(i);
    }
    cout << "\n";
}

void select_from_suggestion(int count)
{
    for (int i = 0; i < count; ++i)
    {
        key_press(down_arrow);
    }
}

void open_dev_mode()
{
    key_press(VK_F12);

    Sleep(200);
}

void do_desktop_search(int require)
{
    int count = 0;
    while (count < require)
    {
        // Set up a generic keyboard event.
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0; // hardware scan code for key
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        // Set up a generic keyboard event.
        ip.type = INPUT_KEYBOARD;
        ip.ki.wScan = 0; // hardware scan code for key
        ip.ki.time = 0;
        ip.ki.dwExtraInfo = 0;

        call_bing_search();
        type_word(word_list[rand() % 10000]);
        select_from_suggestion(rand() % 8);
        Sleep(500);
        key_press(enter);

        Sleep(rand() % 1000 + 100);
        ++count;
    }
}

void search_for_me()
{
    do_desktop_search(30);
    open_dev_mode();
    toggle_mobile_view();
    do_desktop_search(20);
    open_dev_mode();
    open_dev_mode();
    toggle_mobile_view();
}

int main()
{
    init();

    search_for_me();

    // Exit normally
    return 0;
}