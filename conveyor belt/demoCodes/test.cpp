#include "../conveyorBelt.cpp"

int main(){
    std::cout << "\033[?25l\033[2J\033[H";
    std::cout << "\033[48;2;10;11;15m";
    for(int r = 1; r <= 50; ++r){
        std::cout << "\033[" << r << ";1H";
        for(int c = 0; c < 210; ++c) std::cout << " ";
    }

    // title
    std::cout << "\033[38;2;230;230;240m\033[48;2;10;11;15m";
    std::cout << "\033[1;3H ⚙ conveyorBelt  ·  showcase gallery ⚙ ";

    // ---- 1. horizontal RIGHT, green ----
    conveyorBelt a(3, 5, 60, conveyorBelt::RIGHT);
    a.setColorBelt("#2a2a2a"); a.setColorFangs("#22FF66");
    a.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[2;5H  RIGHT · green";

    // ---- 2. horizontal LEFT, cyan ----
    conveyorBelt b(3, 75, 60, conveyorBelt::LEFT);
    b.setColorBelt("#2a2a2a"); b.setColorFangs("#22D8FF");
    b.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[2;75H  LEFT · cyan";

    // ---- 3. horizontal RIGHT, magenta ----
    conveyorBelt c(3, 145, 60, conveyorBelt::RIGHT);
    c.setColorBelt("#2a2a2a"); c.setColorFangs("#FF44CC");
    c.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[2;145H  RIGHT · magenta";

    // ---- 4. DOWN, orange ----
    conveyorBelt d(8, 5, 30, conveyorBelt::DOWN);
    d.setColorBelt("#2a2a2a"); d.setColorFangs("#FF8C1A");
    d.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[7;3H DOWN\n\033[8;3H orange";

    // ---- 5. UP, gold ----
    conveyorBelt e(8, 25, 30, conveyorBelt::UP);
    e.setColorBelt("#2a2a2a"); e.setColorFangs("#FFD700");
    e.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[7;23H UP\n\033[8;23H gold";

    // ---- 6. DOWN, red ----
    conveyorBelt f(8, 45, 30, conveyorBelt::DOWN);
    f.setColorBelt("#2a2a2a"); f.setColorFangs("#FF3030");
    f.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[7;43H DOWN\n\033[8;43H red";

    // ---- 7. UP, violet ----
    conveyorBelt g(8, 65, 30, conveyorBelt::UP);
    g.setColorBelt("#2a2a2a"); g.setColorFangs("#B060FF");
    g.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[7;63H UP\n\033[8;63H violet";

    // ---- 8. DOWN, lime ----
    conveyorBelt h(8, 85, 30, conveyorBelt::DOWN);
    h.setColorBelt("#2a2a2a"); h.setColorFangs("#AAFF22");
    h.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[7;83H DOWN\n\033[8;83H lime";

    // ---- 9. UP, sky ----
    conveyorBelt i(8, 105, 30, conveyorBelt::UP);
    i.setColorBelt("#2a2a2a"); i.setColorFangs("#66CCFF");
    i.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[7;103H UP\n\033[8;103H sky";

    // ---- 10. DOWN, coral ----
    conveyorBelt j(8, 125, 30, conveyorBelt::DOWN);
    j.setColorBelt("#2a2a2a"); j.setColorFangs("#FF7A66");
    j.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[7;123H DOWN\n\033[8;123H coral";

    // ---- 11. UP, teal ----
    conveyorBelt k(8, 145, 30, conveyorBelt::UP);
    k.setColorBelt("#2a2a2a"); k.setColorFangs("#22DDAA");
    k.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[7;143H UP\n\033[8;143H teal";

    // ---- 12. DOWN, hotpink ----
    conveyorBelt l(8, 165, 30, conveyorBelt::DOWN);
    l.setColorBelt("#2a2a2a"); l.setColorFangs("#FF69B4");
    l.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[7;163H DOWN\n\033[8;163H pink";

    // ---- 13. UP, ice ----
    conveyorBelt m(8, 185, 30, conveyorBelt::UP);
    m.setColorBelt("#2a2a2a"); m.setColorFangs("#D0F0FF");
    m.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[7;183H UP\n\033[8;183H ice";

    // ---- long panorama rows ----
    conveyorBelt n(42, 5, 60, conveyorBelt::RIGHT);
    n.setColorBelt("#333333"); n.setColorFangs("#FF5577");
    n.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[41;5H  RIGHT · rose";

    conveyorBelt o(42, 75, 60, conveyorBelt::LEFT);
    o.setColorBelt("#333333"); o.setColorFangs("#77FFAA");
    o.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[41;75H  LEFT · mint";

    conveyorBelt p(42, 145, 60, conveyorBelt::RIGHT);
    p.setColorBelt("#333333"); p.setColorFangs("#FFAA33");
    p.initiateBelt();
    std::cout << "\033[38;2;200;200;210m\033[41;145H  RIGHT · amber";

    while(true){
        a.nextFrame(); b.nextFrame(); c.nextFrame();
        d.nextFrame(); e.nextFrame(); f.nextFrame(); g.nextFrame();
        h.nextFrame(); i.nextFrame(); j.nextFrame(); k.nextFrame();
        l.nextFrame(); m.nextFrame();
        n.nextFrame(); o.nextFrame(); p.nextFrame();
        usleep(90000);
    }

    std::cout << "\033[?25h\033[50;1H";
    return 0;
}