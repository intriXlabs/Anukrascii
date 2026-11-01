#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/ioctl.h>

class conveyorBelt{
private:
    std::string ColorBelt;
    std::string ColorFangs;

private:
    int startingRow;
    int startingCol;

    int terminalRows;
    int terminalCols;

    int length;

public:
    enum conveyorBeltDirection{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

private:
    conveyorBeltDirection conveyorDirection;

private:
    void refreshTerminalSize(){
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);
        terminalRows = w.ws_row;
        terminalCols = w.ws_col;
    }

private:
    // this section is for make a box or sat frame for the conveyor belt
    void drawBox(int row1, int col1, int row2, int col2){
        std::string boxCornerLeft = "┌";
        std::string boxCornerRight = "┐";
        std::string boxHorizontal = "─";
        std::string boxVertical = "│";
        std::string boxBottomLeft = "└";
        std::string boxBottomRight = "┘";

        int height = row2 - row1 + 1;
        int width = col2 - col1 + 1;

        // setting color for belt
        std::cout << ColorBelt;

        // Draw top border
        std::cout << "\033[" << row1 << ";" << col1 << "H" << boxCornerLeft;
        for(int i = 0; i < width - 2; ++i) {
            std::cout << boxHorizontal;
        }
        std::cout << boxCornerRight << std::endl;

        // Draw side borders
        for(int i = 1; i < height - 1; ++i) {
            std::cout << "\033[" << row1 + i << ";" << col1 << "H" << boxVertical;
            std::cout << "\033[" << row1 + i << ";" << col2 << "H" << boxVertical;
        }

        // Draw bottom border
        std::cout << "\033[" << row2 << ";" << col1 << "H" << boxBottomLeft;
        for(int i = 0; i < width - 2; ++i) {
            std::cout << boxHorizontal;
        }
        std::cout << boxBottomRight << "\033[0m" << std::endl;
    }

private:
    // it is to build and make a belt properly - and it is complex
    std::vector<std::string> beltCells;

    void buildBeltString() {

        beltCells.clear();

        std::string beltFangs;

        if(conveyorDirection == RIGHT){
                beltFangs = "▶";
        } else if(conveyorDirection == LEFT){   
                beltFangs = "◀";
        } else if(conveyorDirection == UP){
                beltFangs = "▲";
        } else if(conveyorDirection == DOWN){
                beltFangs = "▼";
        }

        // Build the belt string based on the direction and length
        for(int i = 0; i < length - 2; ++i) {
            if(i%3 == 0) {
                beltCells.push_back(beltFangs);
            } else {
                beltCells.push_back(" ");
            }
        }
    }

    void drawBelt() {
        std::string temporaryBeltString;

        if(conveyorDirection == RIGHT || conveyorDirection == LEFT) {
            for(size_t i = 0; i < beltCells.size(); ++i) {
                temporaryBeltString += ColorFangs + "\033[" + std::to_string(startingRow + 1) + ";" + std::to_string(startingCol + 1 + static_cast<int>(i)) + "H"
                          + beltCells[i];
            }
        } else if(conveyorDirection == UP || conveyorDirection == DOWN) {
            for(size_t i = 0; i < beltCells.size(); ++i) {
                temporaryBeltString += ColorFangs + "\033[" + std::to_string(startingRow + i + 1) + ";" + std::to_string(startingCol + 1) + "H"
                          + beltCells[i];
            }
        }

        std::cout << temporaryBeltString << std::flush;
    }

    void rotateBelt() {
        if (beltCells.empty()) return;

        if(conveyorDirection == RIGHT || conveyorDirection == DOWN){
            std::string last = beltCells.back();
            for (int i = static_cast<int>(beltCells.size()) - 1; i > 0; --i) {
                beltCells[i] = beltCells[i - 1];
            }
            beltCells[0] = last;
        }else{
            std::string first = beltCells.front();
            for (size_t i = 0; i < beltCells.size() - 1; ++i) {
                beltCells[i] = beltCells[i + 1];
            }
            beltCells.back() = first;
        }

        drawBelt();
    }


public:
    conveyorBelt(int startRow, int startCol, int len, conveyorBeltDirection dir=RIGHT)
        : startingRow(startRow), startingCol(startCol), length(len), conveyorDirection(dir) {
        refreshTerminalSize();
    }

    int initiateBelt() {
        if(startingRow < 0 || startingRow >= terminalRows || startingCol < 0 || startingCol >= terminalCols) {
            throw std::out_of_range("Starting position is out of terminal bounds.");
        }

        if(conveyorDirection == RIGHT || conveyorDirection == LEFT) {
            drawBox(startingRow, startingCol, startingRow + 2, startingCol + length - 1);
        } else if(conveyorDirection == UP || conveyorDirection == DOWN) {
            drawBox(startingRow, startingCol, startingRow + length - 1, startingCol + 2);
        }

        buildBeltString();
        drawBelt();
        return 0;
    }

    int nextFrame() {
        rotateBelt();
        return 0;
    }

    int setColorBelt(std::string hexCode) {
        // setting color for the belt
        ColorBelt = "\033[38;2;" 
                  + std::to_string(std::stoi(hexCode.substr(1, 2), nullptr, 16)) + ";"
                  + std::to_string(std::stoi(hexCode.substr(3, 2), nullptr, 16)) + ";"
                  + std::to_string(std::stoi(hexCode.substr(5, 2), nullptr, 16)) + "m";
        return 0;
    }

    int setColorFangs(std::string hexCode) {
        //setting color for the fangs
        ColorFangs = "\033[38;2;" 
                  + std::to_string(std::stoi(hexCode.substr(1, 2), nullptr, 16)) + ";"
                  + std::to_string(std::stoi(hexCode.substr(3, 2), nullptr, 16)) + ";"
                  + std::to_string(std::stoi(hexCode.substr(5, 2), nullptr, 16)) + "m";
        return 0;
    }

};