#include "../conveyorBelt.cpp"

int main(){
    std::cout << "\033[?25l\033[2J\033[H";

    // ============ MACHINE CHASSIS (background) ============
    std::cout << "\033[48;2;12;13;16m";
    for(int r = 1; r <= 50; ++r){
        std::cout << "\033[" << r << ";1H";
        for(int c = 0; c < 210; ++c) std::cout << " ";
    }

    // ============ OUTER FRAME ============
    std::cout << "\033[38;2;120;120;130m\033[48;2;12;13;16m";
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
    std::cout << "\033[38;2;55;58;68m";
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

    // bolts
    std::cout << "\033[38;2;170;170;180m";
    std::cout << "\033[1;1H◉" << "\033[1;210H◉";
    std::cout << "\033[50;1H◉" << "\033[50;210H◉";

    // ============ CENTRAL PANEL ============
    std::cout << "\033[48;2;18;20;26m";
    for(int r = 4; r <= 46; ++r){
        std::cout << "\033[" << r << ";8H";
        for(int c = 0; c < 194; ++c) std::cout << " ";
    }
    std::cout << "\033[38;2;85;90;105m";
    std::cout << "\033[4;8H╭";
    for(int c = 0; c < 192; ++c) std::cout << "─";
    std::cout << "╮";
    std::cout << "\033[46;8H╰";
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
    std::cout << "\033[5;10H  ⚙  ASSEMBLY LINE CX-210  ●  PRODUCTION RUNNING  ●  ▓▓▓▓▓▓▓░░░  72%  ⚙  ";
    std::cout << "\033[38;2;85;90;105m";
    std::cout << "\033[5;8H├" << "\033[5;201H┤";

    // ================================================================
    //  LOGICAL ASSEMBLY FLOW
    //  RAW MATERIAL enters left (row 7)
    //  -> processing row 7 (RIGHT) -> drops down column at x=72
    //  -> row 15 (LEFT) -> rises at x=72? no, at x=140... let's make a
    //     serpentine: R7 -> v@72 DOWN -> R15 LEFT -> v@10 ... hmm
    //  Simpler clean serpentine:
    //   R7  : x10..145  RIGHT  feed-> right
    //   V   : x147      DOWN   at right edge
    //   R15 : x10..145  LEFT   back
    //   V   : x8        DOWN   at left edge
    //   R23 : x10..145  RIGHT
    //   V   : x147      DOWN
    //   R31 : x10..145  LEFT
    //   V   : x8        DOWN
    //   R39 : x10..145  RIGHT  -> OUTPUT right
    //  Extra parallel "inspection" lane at x=155..200 (RIGHT on top rows,
    //  LEFT on bottom rows, joined by verticals) representing finished goods
    //  rework loop.
    // ================================================================

    // ---- MAIN ASSEMBLY SERPENTINE ----
    conveyorBelt r1(7,  10, 137, conveyorBelt::RIGHT);   // feed -> right
    conveyorBelt r2(15, 10, 137, conveyorBelt::LEFT);    // return <- left
    conveyorBelt r3(23, 10, 137, conveyorBelt::RIGHT);   // feed -> right
    conveyorBelt r4(31, 10, 137, conveyorBelt::LEFT);    // return <- left
    conveyorBelt r5(39, 10, 137, conveyorBelt::RIGHT);   // final -> output

    // vertical connectors between serpentine rows (drop-downs)
    // right edge drop: from row7 end -> row15 (DOWN)
    conveyorBelt d1(8, 147, 8, conveyorBelt::DOWN);
    // left edge drop: row15 start -> row23 (DOWN)
    conveyorBelt d2(16, 8, 8, conveyorBelt::DOWN);
    // right edge drop: row23 end -> row31 (DOWN)
    conveyorBelt d3(24, 147, 8, conveyorBelt::DOWN);
    // left edge drop: row31 start -> row39 (DOWN)
    conveyorBelt d4(32, 8, 8, conveyorBelt::DOWN);

    // ---- INSPECTION / REWORK LANE (right side, x=155..200) ----
    conveyorBelt i1(7,  155, 45, conveyorBelt::LEFT);    // top -> back
    conveyorBelt i2(15, 155, 45, conveyorBelt::RIGHT);   // bottom -> fwd
    conveyorBelt i3(23, 155, 45, conveyorBelt::LEFT);
    conveyorBelt i4(31, 155, 45, conveyorBelt::RIGHT);
    conveyorBelt i5(39, 155, 45, conveyorBelt::LEFT);

    // inspect lane verticals
    conveyorBelt iv1(8,  153, 8, conveyorBelt::UP);
    conveyorBelt iv2(16, 198, 8, conveyorBelt::DOWN);
    conveyorBelt iv3(24, 153, 8, conveyorBelt::UP);
    conveyorBelt iv4(32, 198, 8, conveyorBelt::DOWN);

    // ---- FEED (raw material IN) at far left ----
    conveyorBelt feed(39, 3, 5, conveyorBelt::UP);       // rising feed

    // ---- OUTPUT chute at far right ----
    conveyorBelt out(39, 202, 5, conveyorBelt::DOWN);    // dropping output

    // ============ COLORS ============
    auto paint = [](conveyorBelt &b, const char *belt, const char *fang){
        b.setColorBelt(belt);
        b.setColorFangs(fang);
    };

    // main serpentine: hot orange (processing)
    paint(r1, "#3a3a3a", "#FF8C1A");
    paint(r2, "#3a3a3a", "#FF8C1A");
    paint(r3, "#3a3a3a", "#FF8C1A");
    paint(r4, "#3a3a3a", "#FF8C1A");
    paint(r5, "#3a3a3a", "#FF8C1A");

    // drops: amber transition
    paint(d1, "#3a3a3a", "#FFB020");
    paint(d2, "#3a3a3a", "#FFB020");
    paint(d3, "#3a3a3a", "#FFB020");
    paint(d4, "#3a3a3a", "#FFB020");

    // inspection lane: cool cyan (QC)
    paint(i1, "#2c3a42", "#33E0FF");
    paint(i2, "#2c3a42", "#33E0FF");
    paint(i3, "#2c3a42", "#33E0FF");
    paint(i4, "#2c3a42", "#33E0FF");
    paint(i5, "#2c3a42", "#33E0FF");

    paint(iv1, "#2c3a42", "#33E0FF");
    paint(iv2, "#2c3a42", "#33E0FF");
    paint(iv3, "#2c3a42", "#33E0FF");
    paint(iv4, "#2c3a42", "#33E0FF");

    // feed / output: red
    paint(feed, "#3a3a3a", "#FF3A3A");
    paint(out,  "#3a3a3a", "#33FF57");

    // ============ FLOW ARROWS / LABELS ============
    std::cout << "\033[38;2;255;140;26m\033[48;2;18;20;26m";
    std::cout << "\033[6;12H" << "▶ STAGE 1  INTAKE";
    std::cout << "\033[14;12H" << "◀ STAGE 2  HEAT";
    std::cout << "\033[22;12H" << "▶ STAGE 3  PRESS";
    std::cout << "\033[30;12H" << "◀ STAGE 4  COOL";
    std::cout << "\033[38;12H" << "▶ STAGE 5  FINAL";

    std::cout << "\033[38;2;51;224;255m";
    std::cout << "\033[6;157H" << "◀ QC";
    std::cout << "\033[14;157H" << "QC ▶";
    std::cout << "\033[22;157H" << "◀ QC";
    std::cout << "\033[30;157H" << "QC ▶";
    std::cout << "\033[38;157H" << "◀ QC";

    std::cout << "\033[38;2;255;58;58m";
    std::cout << "\033[46;3H" << "▲ FEED";
    std::cout << "\033[38;2;51;255;87m";
    std::cout << "\033[46;203H" << "▼ OUT";

    // ============ PIPES / DECOR ============
    std::cout << "\033[38;2;95;100;115m";
    for(int r = 6; r <= 45; ++r){
        if(r % 4 == 0) std::cout << "\033[" << r << ";3H╟";
        if(r % 4 == 0) std::cout << "\033[" << r << ";207H╢";
    }

    // ============ STATUS BAR ============
    std::cout << "\033[38;2;85;90;105m";
    std::cout << "\033[47;10H" << "┌─────────────────────────────┬─────────────────────────────┬─────────────────────────────┐";
    std::cout << "\033[38;2;120;220;120m";
    std::cout << "\033[48;10H" << "│  FEED      ▓▓▓▓▓▓▓▓▓▓  99%  │  PROCESS   ▓▓▓▓▓▓▓▓░░  84%  │  QC        ▓▓▓▓▓▓▓▓▓░  92%  │";
    std::cout << "\033[38;2;85;90;105m";
    std::cout << "\033[49;10H" << "└─────────────────────────────┴─────────────────────────────┴─────────────────────────────┘";

    // ============ INITIATE ============
    r1.initiateBelt(); r2.initiateBelt(); r3.initiateBelt(); r4.initiateBelt(); r5.initiateBelt();
    d1.initiateBelt(); d2.initiateBelt(); d3.initiateBelt(); d4.initiateBelt();
    i1.initiateBelt(); i2.initiateBelt(); i3.initiateBelt(); i4.initiateBelt(); i5.initiateBelt();
    iv1.initiateBelt(); iv2.initiateBelt(); iv3.initiateBelt(); iv4.initiateBelt();
    feed.initiateBelt(); out.initiateBelt();

    // ============ ANIMATION LOOP ============
    while(true){
        r1.nextFrame(); r2.nextFrame(); r3.nextFrame(); r4.nextFrame(); r5.nextFrame();
        d1.nextFrame(); d2.nextFrame(); d3.nextFrame(); d4.nextFrame();
        i1.nextFrame(); i2.nextFrame(); i3.nextFrame(); i4.nextFrame(); i5.nextFrame();
        iv1.nextFrame(); iv2.nextFrame(); iv3.nextFrame(); iv4.nextFrame();
        feed.nextFrame(); out.nextFrame();
        usleep(90000);
    }

    std::cout << "\033[?25h";
    std::cout << "\033[50;1H";
    return 0;
}