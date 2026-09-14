#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/ioctl.h>

class starlet {

private:
    struct rgb {
        int r;
        int g;
        int b;
    };

private:
    int originRow;
    int originCol;

    std::string glyph = "*";

    int totalIterations = 10;

    rgb textColor{
        66, 66, 66
    };
    rgb glowColor{
        255, 255, 255
    };
    rgb currentColorState{
        255, 255, 255
    };

private:
    rgb convertColorCodeToRGB(std::string colorCode) {
        if(colorCode[0] == '#'  && colorCode.length() == 7) {
            int r = std::stoi(colorCode.substr(1, 2), nullptr, 16);
            int g = std::stoi(colorCode.substr(3, 2), nullptr, 16);
            int b = std::stoi(colorCode.substr(5, 2), nullptr, 16);
            return {r, g, b};
        }else if(colorCode[0] == 'r' && colorCode[1] == 'g' && colorCode[2] == 'b') {
            int r, g, b;
            sscanf(colorCode.c_str(), "rgb(%d,%d,%d)", &r, &g, &b);
            return {r, g, b};
        }else {
            std::cerr << "Invalid color code format: " << colorCode << std::endl;
            return {0, 0, 0};
    }
    }

public:
    starlet(int row, int col, std::string textColor, std::string glowColor, std::string glyph, int iterations) : originRow(row), originCol(col) {
        setTextColor(textColor);
        setGlowColor(glowColor);
        setGlyph(glyph);
        setTotalIterations(iterations);
    }

    int setTextColor(int r, int g, int b) {
        textColor.r = r;
        textColor.g = g;
        textColor.b = b;
        return 0;
    }
    int setTextColor(std::string colorCode) {
        rgb color = convertColorCodeToRGB(colorCode);
        setTextColor(color.r, color.g, color.b);
        return 0;
    }

    int setGlowColor(int r, int g, int b) {
        glowColor.r = r;
        glowColor.g = g;
        glowColor.b = b;
        currentColorState = glowColor; // Initialize current color state to glow color
        return 0;
    }
    int setGlowColor(std::string colorCode) {
        rgb color = convertColorCodeToRGB(colorCode);
        setGlowColor(color.r, color.g, color.b);
        return 0;
    }

    int setTotalIterations(int iterations) {
        totalIterations = iterations;
        return 0;
    }

    int setGlyph(std::string newGlyph) {
        glyph = newGlyph;
        return 0;
    }

private:
    int currentIteration = 0;
    bool transitionFinished = false;

private:
    bool nextState() {
        if (transitionFinished) {
            return false; // Transition is finished, no further state changes
        }
        if(currentIteration >= totalIterations) {
            return false; // Transition is finished, no further state changes
        }

        ++currentIteration;

        double progress =
            static_cast<double>(currentIteration) / totalIterations;

        // Prevent progress from exceeding 1.0
        if (progress >= 1.0) {
            progress = 1.0;
            transitionFinished = true;
        }

        currentColorState.r =
            static_cast<int>(
                glowColor.r + (textColor.r - glowColor.r) * progress
            );

        currentColorState.g =
            static_cast<int>(
                glowColor.g + (textColor.g - glowColor.g) * progress
            );

        currentColorState.b =
            static_cast<int>(
                glowColor.b + (textColor.b - glowColor.b) * progress
            );

        return true; // Continue with the next state
    }

    int render(){
        // main code
        std::cout << "\033[" << originRow << ";" << originCol << "H"; // Move cursor to the specified position
        std::cout << "\033[38;2;" << currentColorState.r << ";" << currentColorState.g << ";" << currentColorState.b << "m"; // Set text color
        std::cout << glyph; // Render the star
        std::cout << "\033[0m" << std::flush; // Reset text color

        return 0;
    }

public:
    bool nextStateAndRender(){
        if (!nextState()) {
            return false; // Transition is finished, no further state changes
        }
        render();
        return true; // Continue with the next state
    }

public:
    int hideCursor() {
        std::cout << "\033[?25l"; // Hide cursor
        return 0;
    }

    int showCursor() {
        std::cout << "\033[?25h"; // Show cursor
        return 0;
    }

    void reset() {
        // removing the star from the terminal
        std::cout << "\033[" << originRow << ";" << originCol << "H"; // Move cursor to the specified position
        std::cout << " "; // Clear the star
        std::cout << "\033[0m" << std::flush; // Reset text color

        // Reset the state of the star
        currentIteration = 0;
        transitionFinished = false;
        currentColorState = glowColor; // Reset current color state to glow color
    }

    ~starlet() {
    }

};

// helper class
class starletScene {

private:
    std::vector<starlet> objects;

    int frameDelayMicroseconds = 100000;

public:
    void add(const starlet& object) {
        objects.push_back(object);
    }

    void setFrameDelay(int microseconds) {
        frameDelayMicroseconds =
            std::max(0, microseconds);
    }

private:
    void hideCursor() {
        std::cout << "\033[?25l";
        std::cout.flush();
    }

    void showCursor() {
        std::cout << "\033[?25h";
        std::cout.flush();
    }

public:
    void run() {
        hideCursor();

        bool anyActive = true;

        while (anyActive) {
            anyActive = false;

            for (starlet& object : objects) {
                bool rendered =
                    object.nextStateAndRender();

                if (rendered) {
                    anyActive = true;
                }
            }

            std::cout.flush();

            if (anyActive) {
                usleep(frameDelayMicroseconds);
            }
        }

        showCursor();
    }

    void resetAll() {
        for (starlet& object : objects) {
            object.reset();
        }
    }

    void clearAll() {
        resetAll();
        objects.clear();
    }
};