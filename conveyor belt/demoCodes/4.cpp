#include "../conveyorBelt.cpp"

int main(){
    std::cout << "\033[?25l\033[2J\033[H";

    // ============ DEEP MACHINE BACKGROUND ============
    std::cout << "\033[48;2;8;9;12m";
    for(int r = 1; r <= 50; ++r){
        std::cout << "\033[" << r << ";1H";
        for(int c = 0; c < 210; ++c) std::cout << " ";
    }

    // ============ OUTER ARMOR FRAME ============
    std::cout << "\033[38;2;140;145;160m\033[48;2;8;9;12m";
    std::cout << "\033[1;1H╔";
    for(int c = 0; c < 208; ++c) std::cout << "═";
    std::cout << "╗";
    std::cout << "\033[50;1H╚";
    for(int c = 0; c < 208; ++c) std::cout << "═";
    std::cout << "╝";
    for(int r = 2; r <= 49; ++r){
        std::cout << "\033[" << r << ";1H║";
        std::cout << "\033[" << r << ";210H║";
    }

    // inner frame
    std::cout << "\033[38;2;70;75;90m";
    std::cout << "\033[2;2H╔";
    for(int c = 0; c < 206; ++c) std::cout << "═";
    std::cout << "╗";
    std::cout << "\033[49;2H╚";
    for(int c = 0; c < 206; ++c) std::cout << "═";
    std::cout << "╝";
    for(int r = 3; r <= 48; ++r){
        std::cout << "\033[" << r << ";2H║";
        std::cout << "\033[" << r << ";209H║";
    }

    // rivets
    std::cout << "\033[38;2;200;200;210m";
    std::cout << "\033[1;1H◉" << "\033[1;210H◉";
    std::cout << "\033[50;1H◉" << "\033[50;210H◉";
    std::cout << "\033[38;2;120;125;140m";
    std::cout << "\033[2;2H◉" << "\033[2;209H◉";
    std::cout << "\033[49;2H◉" << "\033[49;209H◉";

    // ============ CENTRAL BULKHEAD ============
    std::cout << "\033[48;2;14;16;22m";
    for(int r = 4; r <= 46; ++r){
        std::cout << "\033[" << r << ";10H";
        for(int c = 0; c < 190; ++c) std::cout << " ";
    }
    std::cout << "\033[38;2;75;80;95m";
    std::cout << "\033[4;10H╭";
    for(int c = 0; c < 188; ++c) std::cout << "─";
    std::cout << "╮";
    std::cout << "\033[46;10H╰";
    for(int c = 0; c < 188; ++c) std::cout << "─";
    std::cout << "╯";
    for(int r = 5; r <= 45; ++r){
        std::cout << "\033[" << r << ";10H│";
        std::cout << "\033[" << r << ";199H│";
    }

    // ============ TITLE BAR ============
    std::cout << "\033[48;2;30;33;44m\033[38;2;230;230;240m";
    std::cout << "\033[5;12H";
    for(int c = 0; c < 184; ++c) std::cout << " ";
    std::cout << "\033[5;12H ⚙ ASSEMBLY LINE · CX-210 · UNIT-07 ⚙   ● ONLINE ●   TEMP 487°C   RPM 2400   ▓▓▓▓▓▓▓▓░░ 78% ";
    std::cout << "\033[38;2;75;80;95m";
    std::cout << "\033[5;10H├" << "\033[5;199H┤";

    // ================================================================
    //  ASSEMBLY SERPENTINE using ONLY the conveyorBelt class API:
    //    - constructor (row, col, length, direction)
    //    - setColorBelt(hex) / setColorFangs(hex)
    //    - initiateBelt()   -> draws frame + first frame
    //    - nextFrame()      -> rotates one step
    //
    //  Row 7  : RIGHT  x=14..130
    //  Drop   : DOWN   x=132
    //  Row 15 : LEFT   x=14..130
    //  Drop   : DOWN   x=11
    //  Row 23 : RIGHT  x=14..130
    //  Drop   : DOWN   x=132
    //  Row 31 : LEFT   x=14..130
    //  Drop   : DOWN   x=11
    //  Row 39 : RIGHT  x=14..130  -> output
    //  QC lane x=142..196 alternating with verticals at edges.
    //  Feed (UP) left; Out (DOWN) right.
    // ================================================================

    // ---- MAIN SERPENTINE ----
    conveyorBelt m1(7,  14, 117, conveyorBelt::RIGHT);
    conveyorBelt m2(15, 14, 117, conveyorBelt::LEFT);
    conveyorBelt m3(23, 14, 117, conveyorBelt::RIGHT);
    conveyorBelt m4(31, 14, 117, conveyorBelt::LEFT);
    conveyorBelt m5(39, 14, 117, conveyorBelt::RIGHT);

    // ---- DROPS ----
    conveyorBelt md1(8,  132, 8, conveyorBelt::DOWN);
    conveyorBelt md2(16, 11,  8, conveyorBelt::DOWN);
    conveyorBelt md3(24, 132, 8, conveyorBelt::DOWN);
    conveyorBelt md4(32, 11,  8, conveyorBelt::DOWN);

    // ---- QC REWORK LANE ----
    conveyorBelt q1(7,  142, 55, conveyorBelt::LEFT);
    conveyorBelt q2(15, 142, 55, conveyorBelt::RIGHT);
    conveyorBelt q3(23, 142, 55, conveyorBelt::LEFT);
    conveyorBelt q4(31, 142, 55, conveyorBelt::RIGHT);
    conveyorBelt q5(39, 142, 55, conveyorBelt::LEFT);

    conveyorBelt qv1(8,  140, 8, conveyorBelt::UP);
    conveyorBelt qv2(16, 195, 8, conveyorBelt::DOWN);
    conveyorBelt qv3(24, 140, 8, conveyorBelt::UP);
    conveyorBelt qv4(32, 195, 8, conveyorBelt::DOWN);

    // ---- FEED & OUTPUT ----
    conveyorBelt feed(7, 4, 9, conveyorBelt::UP);
    conveyorBelt out (39, 200, 9, conveyorBelt::DOWN);

    // ============ COLORS ============
    auto paint = [](conveyorBelt &b, const char *belt, const char *fang){
        b.setColorBelt(belt);
        b.setColorFangs(fang);
    };

    paint(m1, "#2e2e2e", "#FF7A10");
    paint(m2, "#2e2e2e", "#FF7A10");
    paint(m3, "#2e2e2e", "#FFA020");
    paint(m4, "#2e2e2e", "#FFC040");
    paint(m5, "#2e2e2e", "#FFE060");

    paint(md1, "#2e2e2e", "#FFB030");
    paint(md2, "#2e2e2e", "#FFB030");
    paint(md3, "#2e2e2e", "#FFB030");
    paint(md4, "#2e2e2e", "#FFB030");

    paint(q1, "#20323a", "#22D8FF");
    paint(q2, "#20323a", "#22D8FF");
    paint(q3, "#20323a", "#22D8FF");
    paint(q4, "#20323a", "#22D8FF");
    paint(q5, "#20323a", "#22D8FF");

    paint(qv1, "#20323a", "#22D8FF");
    paint(qv2, "#20323a", "#22D8FF");
    paint(qv3, "#20323a", "#22D8FF");
    paint(qv4, "#20323a", "#22D8FF");

    paint(feed, "#2e2e2e", "#FF2020");
    paint(out,  "#2e2e2e", "#20FF60");

    // ============ STATION LABELS ============
    std::cout << "\033[38;2;255;140;26m\033[48;2;14;16;22m";
    std::cout << "\033[6;16H"  << "[01] INTAKE   ▶▶▶";
    std::cout << "\033[14;16H" << "[02] HEAT     ◀◀◀";
    std::cout << "\033[22;16H" << "[03] PRESS    ▶▶▶";
    std::cout << "\033[30;16H" << "[04] COOL     ◀◀◀";
    std::cout << "\033[38;16H" << "[05] FINISH   ▶▶▶";

    std::cout << "\033[38;2;34;216;255m";
    std::cout << "\033[6;144H"  << "◀◀◀  QC-A";
    std::cout << "\033[14;144H" << "QC-B  ▶▶▶";
    std::cout << "\033[22;144H" << "◀◀◀  QC-C";
    std::cout << "\033[30;144H" << "QC-D  ▶▶▶";
    std::cout << "\033[38;144H" << "◀◀◀  QC-E";

    std::cout << "\033[38;2;255;40;40m\033[48;2;14;16;22m";
    std::cout << "\033[8;5H▲\033[9;5H▲\033[10;5H▲\033[11;5H▲";
    std::cout << "\033[12;4HIN";
    std::cout << "\033[38;2;40;255;100m";
    std::cout << "\033[40;201H▼\033[41;201H▼\033[42;201H▼\033[43;201H▼";
    std::cout << "\033[44;200HOUT";

    // ============ CONDUIT PIPES ============
    std::cout << "\033[38;2;110;115;130m";
    for(int c = 12; c <= 197; ++c){
        if(c == 12)       std::cout << "\033[6;"  << c << "H╭";
        else if(c == 197) std::cout << "\033[6;"  << c << "H╮";
        else if(c % 8 == 0) std::cout << "\033[6;" << c << "H╪";
        else              std::cout << "\033[6;"  << c << "H─";
    }
    for(int c = 12; c <= 197; ++c){
        if(c == 12)       std::cout << "\033[45;" << c << "H╰";
        else if(c == 197) std::cout << "\033[45;" << c << "H╯";
        else if(c % 8 == 0) std::cout << "\033[45;" << c << "H╪";
        else              std::cout << "\033[45;" << c << "H─";
    }

    // ============ STATUS PANEL ============
    std::cout << "\033[38;2;75;80;95m";
    std::cout << "\033[47;12H┌──────────────────────────────┬──────────────────────────────┬──────────────────────────────┬──────────────────────────────┐";
    std::cout << "\033[38;2;120;230;120m";
    std::cout << "\033[48;12H│  INTAKE  ▓▓▓▓▓▓▓▓▓▓ 99%    │  PROCESS ▓▓▓▓▓▓▓▓░░ 84%    │  QC      ▓▓▓▓▓▓▓▓▓░ 92%    │  OUTPUT  ▓▓▓▓▓▓▓▓▓▓ 98%    │";
    std::cout << "\033[38;2;75;80;95m";
    std::cout << "\033[49;12H└──────────────────────────────┴──────────────────────────────┴──────────────────────────────┴──────────────────────────────┘";

    // ============ INITIATE (only library API) ============
    feed.initiateBelt();

    m1.initiateBelt(); m2.initiateBelt(); m3.initiateBelt(); m4.initiateBelt(); m5.initiateBelt();
    md1.initiateBelt(); md2.initiateBelt(); md3.initiateBelt(); md4.initiateBelt();

    q1.initiateBelt(); q2.initiateBelt(); q3.initiateBelt(); q4.initiateBelt(); q5.initiateBelt();
    qv1.initiateBelt(); qv2.initiateBelt(); qv3.initiateBelt(); qv4.initiateBelt();

    out.initiateBelt();

    // ============ ANIMATION (only nextFrame()) ============
    while(true){
        m1.nextFrame(); m2.nextFrame(); m3.nextFrame(); m4.nextFrame(); m5.nextFrame();
        md1.nextFrame(); md2.nextFrame(); md3.nextFrame(); md4.nextFrame();

        q1.nextFrame(); q2.nextFrame(); q3.nextFrame(); q4.nextFrame(); q5.nextFrame();
        qv1.nextFrame(); qv2.nextFrame(); qv3.nextFrame(); qv4.nextFrame();

        feed.nextFrame(); out.nextFrame();

        usleep(80000);
    }

    std::cout << "\033[?25h";
    std::cout << "\033[50;1H";
    return 0;
}