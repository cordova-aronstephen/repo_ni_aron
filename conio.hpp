#pragma once
#include <iostream>
#include <sys/ioctl.h> // for ioctl()
#include <unistd.h>    // for STDOUT_FILENO
#include <termios.h>   // for struct winsize
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>


using namespace std;

void get() {
    cin.ignore();
    cin.get();
}
void clear() {
    system("clear");
}

void gotoxy(int x, int y) {
    std::cout << "\033[" << y + 1 << ";" << x + 1 << "H";
    std::cout.flush();
}
int getWindowWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void centerText(const std::string& text) {
    int windowWidth = getWindowWidth();
    int textWidth = text.length();
    int x = (windowWidth - textWidth) / 2;
    gotoxy(x, 1); 
    cout << text;
}

void setColor(int color) {
    cout << "\033[" << color << "m";
}

void resetColor() {
    const std::string ANSI_RESET = "\033[0m";
    std::cout << ANSI_RESET;
    cout.flush();
}

/*
30-37: Standard colors
30: Black
31: Red
32: Green
33: Yellow
34: Blue
35: Magenta
36: Cyan
37: White
90-97: Bright (high intensity) colors
90: Bright Black
91: Bright Red
92: Bright Green
93: Bright Yellow
94: Bright Blue
95: Bright Magenta
96: Bright Cyan
97: Bright White

40-47: Standard background colors
40: Black
41: Red
42: Green
43: Yellow
44: Blue
45: Magenta
46: Cyan
47: White
100-107: Bright (high intensity) background colors
100: Bright Black
101: Bright Red
102: Bright Green
103: Bright Yellow
104: Bright Blue
105: Bright Magenta
106: Bright Cyan
107: Bright White

*/

void drawHorizontalLine(int x, int y, int length) {
    gotoxy(x, y);
    std::cout << std::string(length, '-') << std::endl;
}

void drawVerticalLine(int x, int y, int height) {
    for (int i = 1; i < height - 1; ++i) {
        gotoxy(x, y + i);
        std::cout << "|" << std::endl;
    }
}

void wrap(const std::string& text, int x, int y, bool center = false) {
    std::vector<std::string> lines;
    std::istringstream iss(text);
    std::string line;

    while (std::getline(iss, line, '\n')) {
        lines.push_back(line);
    }

    int maxLineLength = 0;
    for (size_t i = 0; i < lines.size(); ++i) {
        const std::string& l = lines[i];
        maxLineLength = std::max(maxLineLength, static_cast<int>(l.length()));
    }

    int width = maxLineLength + 2; 
    int height = static_cast<int>(lines.size()) + 2; 

    
    if (center) {
        x -= width / 2;
        y -= height / 2;
    }

    drawHorizontalLine(x, y, width);
    drawVerticalLine(x, y, height);
    drawVerticalLine(x + width - 1, y, height);
    drawHorizontalLine(x, y + height - 1, width);

    
    int currentY = y + 1;
    for (size_t i = 0; i < lines.size(); ++i) {
        gotoxy(x + 1, currentY);
        std::cout << lines[i];
        currentY++;
    }
}

int intLength(int value) {
    string valueString = to_string(value);
    return valueString.length();
}

int read() {
    struct termios oldt, newt;
    int ch;
    // Save the current terminal attributes
    tcgetattr(STDIN_FILENO, &oldt);
    // Set the terminal to raw mode
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    // Read a single character from the input without echoing
    ch = getchar();
    // Restore the original terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}