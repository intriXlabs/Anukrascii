#include "../conveyorBelt.cpp"

int main(){
    std::cout << "\033[?25l\033[2J\033[H";

    // ============ MACHINE CHASSIS (background) ============
    // dark industrial background fill
    std::cout << "\033[48;2;15;15;18m";
    for(int r = 1; r <= 50; ++r){
        std::cout << "\033[" << r << ";1H";
        for(int c = 0; c < 210; ++c) std::cout << " ";
    }

    // ============ OUTER FRAME ============
    std::cout << "\033[38;2;120;120;130m\033[48;2;15;15;18m";
    std::cout << "\033[1;1H" << "╔";
    for(int c = 0; c < 208; ++c) std::cout << "═";
    std::cout << "╗";
    std::cout << "\033[50;1H" << "╚";
    for(int c = 0; c < 208; ++c) std::cout << "═";
    std::cout << "╝";
    for(int r = 2; r <= 49; ++r){
        std::cout << "\033[" << r << ";1H║";
        std::cout << "\033[" << r << ";210H║";
    }

    // inner accent frame
    std::cout << "\033[38;2;60;60;70m";
    std::cout << "\033[2;2H" << "┌";
    for(int c = 0; c < 206; ++c) std::cout << "─";
    std::cout << "┐";
    std::cout << "\033[49;2H" << "└";
    for(int c = 0; c < 206; ++c) std::cout << "─";
    std::cout << "┘";
    for(int r = 3; r <= 48; ++r){
        std::cout << "\033[" << r << ";2H│";
        std::cout << "\033[" << r << ";209H│";
    }

    // ============ BOLTS / RIVETS ============
    std::cout << "\033[38;2;180;180;190m";
    std::cout << "\033[1;1H" << "◉";
    std::cout << "\033[1;210H" << "◉";
    std::cout << "\033[50;1H" << "◉";
    std::cout << "\033[50;210H" << "◉";

    // ============ CENTRAL MACHINE PANEL / ARCHITECTURE ============
    // big panel body
    std::cout << "\033[38;2;40;45;55m\033[48;2;20;22;28m";
    std::cout << "\033[4;8H";
    for(int c = 0; c < 194; ++c) std::cout << " ";
    for(int r = 5; r <= 46; ++r){
        std::cout << "\033[" << r << ";8H";
        for(int c = 0; c < 194; ++c) std::cout << " ";
    }

    // panel edges
    std::cout << "\033[38;2;90;95;110m";
    std::cout << "\033[4;8H" << "╭";
    for(int c = 0; c < 192; ++c) std::cout << "─";
    std::cout << "╮";
    std::cout << "\033[46;8H" << "╰";
    for(int c = 0; c < 192; ++c) std::cout << "─";
    std::cout << "╯";
    for(int r = 5; r <= 45; ++r){
        std::cout << "\033[" << r << ";8H│";
        std::cout << "\033[" << r << ";201H│";
    }

    // ============ TITLE BAR ============
    std::cout << "\033[48;2;35;38;48m\033[38;2;220;220;230m";
    std::cout << "\033[5;10H";
    for(int c = 0; c < 188; ++c) std::cout << " ";
    std::cout << "\033[5;10H" << "  ⚙  CONVEYOR MACHINE  ●  MODEL CX-210  ●  ONLINE  ●  RUNTIME ACTIVE  ⚙  ";
    std::cout << "\033[38;2;90;95;110m";
    std::cout << "\033[5;8H├";
    std::cout << "\033[5;201H┤";

    // ============ LAYOUT / BUILD MACHINERY ============
    // ROW 1 - horizontal belts
    conveyorBelt h1(7, 10, 55, conveyorBelt::RIGHT);
    conveyorBelt h2(7, 80, 55, conveyorBelt::LEFT);
    conveyorBelt h3(7, 150, 55, conveyorBelt::RIGHT);

    // ROW 2
    conveyorBelt h4(15, 10, 55, conveyorBelt::LEFT);
    conveyorBelt h5(15, 80, 55, conveyorBelt::RIGHT);
    conveyorBelt h6(15, 150, 55, conveyorBelt::LEFT);

    // ROW 3
    conveyorBelt h7(23, 10, 55, conveyorBelt::RIGHT);
    conveyorBelt h8(23, 80, 55, conveyorBelt::LEFT);
    conveyorBelt h9(23, 150, 55, conveyorBelt::RIGHT);

    // ROW 4
    conveyorBelt h10(31, 10, 55, conveyorBelt::LEFT);
    conveyorBelt h11(31, 80, 55, conveyorBelt::RIGHT);
    conveyorBelt h12(31, 150, 55, conveyorBelt::LEFT);

    // ROW 5
    conveyorBelt h13(39, 10, 55, conveyorBelt::RIGHT);
    conveyorBelt h14(39, 80, 55, conveyorBelt::LEFT);
    conveyorBelt h15(39, 150, 55, conveyorBelt::RIGHT);

    // vertical transfer columns between rows
    conveyorBelt v1(8, 70, 9, conveyorBelt::DOWN);
    conveyorBelt v2(8, 140, 9, conveyorBelt::UP);
    conveyorBelt v3(16, 70, 9, conveyorBelt::UP);
    conveyorBelt v4(16, 140, 9, conveyorBelt::DOWN);
    conveyorBelt v5(24, 70, 9, conveyorBelt::DOWN);
    conveyorBelt v6(24, 140, 9, conveyorBelt::UP);
    conveyorBelt v7(32, 70, 9, conveyorBelt::UP);
    conveyorBelt v8(32, 140, 9, conveyorBelt::DOWN);

    // main feed belts
    conveyorBelt feed1(7, 3, 5, conveyorBelt::RIGHT);
    conveyorBelt feed2(39, 205, 3, conveyorBelt::LEFT);

    // ============ COLOR SCHEMES ============
    auto paint = [](conveyorBelt &b, const char *belt, const char *fang){
        b.setColorBelt(belt);
        b.setColorFangs(fang);
    };

    // hot steel belts - orange glow
    paint(h1,  "#3a3a3a", "#FF8C1A");
    paint(h2,  "#3a3a3a", "#FF8C1A");
    paint(h3,  "#3a3a3a", "#FF8C1A");
    paint(h4,  "#3a3a3a", "#FFB020");
    paint(h5,  "#3a3a3a", "#FFB020");
    paint(h6,  "#3a3a3a", "#FFB020");
    paint(h7,  "#3a3a3a", "#FF8C1A");
    paint(h8,  "#3a3a3a", "#FF8C1A");
    paint(h9,  "#3a3a3a", "#FF8C1A");
    paint(h10, "#3a3a3a", "#FFB020");
    paint(h11, "#3a3a3a", "#FFB020");
    paint(h12, "#3a3a3a", "#FFB020");
    paint(h13, "#3a3a3a", "#FF8C1A");
    paint(h14, "#3a3a3a", "#FF8C1A");
    paint(h15, "#3a3a3a", "#FF8C1A");

    // cyan coolant vertical belts
    paint(v1, "#2c3a42", "#33E0FF");
    paint(v2, "#2c3a42", "#33E0FF");
    paint(v3, "#2c3a42", "#33E0FF");
    paint(v4, "#2c3a42", "#33E0FF");
    paint(v5, "#2c3a42", "#33E0FF");
    paint(v6, "#2c3a42", "#33E0FF");
    paint(v7, "#2c3a42", "#33E0FF");
    paint(v8, "#2c3a42", "#33E0FF");

    // feeds
    paint(feed1, "#3a3a3a", "#FF3A3A");
    paint(feed2, "#3a3a3a", "#FF3A3A");

    // ============ PIPES / HOSES / DECOR ============
    std::cout << "\033[38;2;100;105;120m";
    // left pipe run
    for(int r = 6; r <= 45; ++r){
        if(r % 4 == 0) std::cout << "\033[" << r << ";3H" << "╟";
    }
    // right pipe run
    for(int r = 6; r <= 45; ++r){
        if(r % 4 == 0) std::cout << "\033[" << r << ";207H" << "╢";
    }
    // top pipe
    for(int c = 12; c < 198; ++c){
        if(c % 6 == 0) std::cout << "\033[6;" << c << "H" << "▪";
    }

    // ============ STATUS / TELEMETRY ============
    std::cout << "\033[38;2;90;95;110m";
    std::cout << "\033[47;10H" << "┌─────────────────────────────┬─────────────────────────────┬─────────────────────────────┐";
    std::cout << "\033[48;10H" << "│  LINE-01  ▓▓▓▓▓▓▓▓▓▓  98%   │  LINE-02  ▓▓▓▓▓▓▓▓░░  87%   │  LINE-03  ▓▓▓▓▓▓▓▓▓▓  99%   │";
    std::cout << "\033[49;10H" << "└─────────────────────────────┴─────────────────────────────┴─────────────────────────────┘";

    std::cout << "\033[38;2;120;220;120m\033[48;2;20;22;28m";
    std::cout << "\033[6;12H" << "● FEED";
    std::cout << "\033[38;2;220;220;120m";
    std::cout << "\033[6;90H" << "● TRANSFER";
    std::cout << "\033[38;2;220;120;120m";
    std::cout << "\033[6;170H" << "● OUTPUT";

    // corner "machinery" blocks
    std::cout << "\033[38;2;80;85;100m\033[48;2;30;33;42m";
    std::cout << "\033[3;3H" << "  ENGINE  ";
    std::cout << "\033[3;197H" << "  GEARBOX  ";
    std::cout << "\033[46;3H" << "  MOTOR  ";
    std::cout << "\033[46;197H" << "  PUMP  ";

    // ============ INITIATE ALL BELTS ============
    h1.initiateBelt();  h2.initiateBelt();  h3.initiateBelt();
    h4.initiateBelt();  h5.initiateBelt();  h6.initiateBelt();
    h7.initiateBelt();  h8.initiateBelt();  h9.initiateBelt();
    h10.initiateBelt(); h11.initiateBelt(); h12.initiateBelt();
    h13.initiateBelt(); h14.initiateBelt(); h15.initiateBelt();

    v1.initiateBelt(); v2.initiateBelt(); v3.initiateBelt(); v4.initiateBelt();
    v5.initiateBelt(); v6.initiateBelt(); v7.initiateBelt(); v8.initiateBelt();

    feed1.initiateBelt(); feed2.initiateBelt();

    // ============ ANIMATION LOOP ============
    while(true){
        h1.nextFrame();  h2.nextFrame();  h3.nextFrame();
        h4.nextFrame();  h5.nextFrame();  h6.nextFrame();
        h7.nextFrame();  h8.nextFrame();  h9.nextFrame();
        h10.nextFrame(); h11.nextFrame(); h12.nextFrame();
        h13.nextFrame(); h14.nextFrame(); h15.nextFrame();

        v1.nextFrame(); v2.nextFrame(); v3.nextFrame(); v4.nextFrame();
        v5.nextFrame(); v6.nextFrame(); v7.nextFrame(); v8.nextFrame();

        feed1.nextFrame(); feed2.nextFrame();

        usleep(90000);
    }

    std::cout << "\033[?25h";
    std::cout << "\033[50;1H";
    return 0;
}