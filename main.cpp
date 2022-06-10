#include <math.h>

#include <iostream>

#include "graphics.h"
#define RAZA_CERC_1 35
#define RAZA_CERC_2 65
#define RAZA_CERC_3 100
#define bkgX 1920
#define bkgY 1080
#define BLUE "gobbletBlue1.jpg"
#define ORANGE "gobbletOrange1.jpg"
using namespace std;
int maxim(int a, int b);
int minim(int a, int b);
int player = 1;
struct tabel {
  int mic, mediu, mare;
  int culoare1, culoare2, culoare3;
} t[10];
int player1[7], player2[7];
void place(int i, int player);
int circles[13];
int patrate[3][3][2] = {{{282, 504}, {599, 712}, {944, 945}},
                        {{636, 333}, {952, 510}, {1299, 717}},
                        {{965, 168}, {1274, 338}, {1609, 518}}};

int coordonate[12][4] = {
    {85, 75, 125, 145},     {85, 165, 125, 235},    {65, 255, 145, 385},
    {65, 405, 145, 535},    {35, 555, 175, 755},    {35, 775, 175, 975},
    {1795, 75, 1835, 145},  {1795, 165, 1835, 235}, {1775, 255, 1855, 385},
    {1775, 405, 1855, 535}, {1745, 555, 1865, 755}, {1745, 775, 1865, 975}};

int gobblet[9][4] = {
    {262, 459, 302, 529}, {579, 677, 619, 747},   {924, 870, 964, 940},
    {616, 298, 656, 368}, {932, 475, 972, 545},   {1279, 682, 1319, 752},

    {945, 133, 985, 203}, {1254, 303, 1294, 373}, {1589, 483, 1629, 553}};

int coordPatrate[9][4] = {
    {50, 375, 515, 640},  {295, 557, 860, 890},   {634, 755, 1256, 1061},
    {395, 212, 866, 456}, {698, 370, 1206, 655},  {1208, 556, 1602, 906},
    {722, 34, 1209, 282}, {1024, 214, 1525, 461}, {1375, 378, 1678, 522}};

int check[12];

void player1wins();
void player2wins();

void joc() {
  int ok = 0;
  for (int i = 1; i <= 9; i++) check[i] = 0;

  for (int i = 1; i <= 9; i++)
    if (t[i].mare != 0)
      check[i] = t[i].culoare3;
    else if (t[i].mediu != 0)
      check[i] = t[i].culoare2;
    else if (t[i].mic != 0)
      check[i] = t[i].culoare1;

  for (int k = 0; k <= 2; k++)
    if (check[1 + k * 3] == check[2 + k * 3] &&
        check[2 + k * 3] == check[3 + k * 3])
      if (check[1 + k * 3] == 1) { /*
         cleardevice();
         readimagefile("play1win.jpg", 0, 0, 1920, 1080);
         return;*/
        cleardevice();
        player1wins();
        ok = 1;
      }
      // cout << "Blue";
      else if (check[1 + k * 3] == 2) { /*
         cleardevice();
         readimagefile("play2win.jpg", 0, 0, 1920, 1080);
         return;*/
        cleardevice();
        player2wins();
        ok = 1;
      }
  for (int k = 1; k <= 3; k++)
    if (check[k] == check[k + 3] && check[k + 3] == check[k + 6])
      if (check[k] == 1) { /*
         cleardevice();
         readimagefile("play1win.jpg", 0, 0, 1920, 1080);
         return;*/
        cleardevice();
        player1wins();
        ok = 1;
      }
      // cout << "blue";
      else if (check[k] == 2) { /*
         cleardevice();
         readimagefile("play2win.jpg", 0, 0, 1920, 1080);
         return;*/
        cleardevice();
        player2wins();
        ok = 1;
      }
  // cout << "orange";

  if (check[1] == check[5] && check[5] == check[9])
    if (check[1] == 1) {
      ok = 1;
      cout << "blue";
    } else if (check[1] == 2) {
      cout << "orange";
      ok = 1;
    }

  if (check[3] == check[5] && check[5] == check[7])
    if (check[3] == 1) {
      cout << "blue";
      ok = 1;
    } else if (check[3] == 2) {
      ok = 1;
      cout << "orange";
    }
  if (ok == 0)
    for (int i = 1; i <= 9; i++)
      if (t[i].mare != 0)
        readimagefile(t[i].culoare3 == 1 ? BLUE : ORANGE,
                      (gobblet[i - 1][0] - 50), (gobblet[i - 1][1] - 65),
                      (gobblet[i - 1][2] + 50), (gobblet[i - 1][3] + 65));
      else if (t[i].mediu != 0)
        readimagefile(t[i].culoare2 == 1 ? BLUE : ORANGE,
                      (gobblet[i - 1][0] - 20), (gobblet[i - 1][1] - 30),
                      (gobblet[i - 1][2] + 20), (gobblet[i - 1][3] + 30));
      else if (t[i].mic != 0)
        readimagefile(t[i].culoare1 == 1 ? BLUE : ORANGE, gobblet[i - 1][0],
                      gobblet[i - 1][1], gobblet[i - 1][2], gobblet[i - 1][3]);
}

int distances1(int cursorX, int cursorY, int raza, int x, int y, int i) {
  if (sqrt((x - cursorX) * (x - cursorX) + (y - cursorY) * (y - cursorY)) <=
          raza &&
      player1[i] == 0)
    return 1;
  else
    return 0;
}

int distances2(int cursorX, int cursorY, int raza, int x, int y, int i) {
  if (sqrt((x - cursorX) * (x - cursorX) + (y - cursorY) * (y - cursorY)) <=
          raza &&
      player2[i] == 0)
    return 1;
  return 0;
}

void checkCircles() {
  for (int i = 1; i <= 12; i++)
    if (circles[i] == 0)

      readimagefile(i <= 6 ? BLUE : ORANGE, coordonate[i - 1][0],
                    coordonate[i - 1][1], coordonate[i - 1][2],
                    coordonate[i - 1][3]);
}

void findCircle(int &player) {
  if (player % 2 == 1) {
    cleardevice();
    readimagefile("gobbletPS.jpg", 0, 0, 1920, 1080);
    readimagefile("Player1.jpg", 60, 10, 140, 70);
    joc();
    checkCircles();
  }
  while (player % 2 == 1) {
    POINT cursorP;
    GetCursorPos(&cursorP);
    if (ismouseclick(WM_LBUTTONDOWN)) {
      clearmouseclick(WM_LBUTTONDOWN);
      for (int i = 1; i <= 6; i++) {
        int raza;
        if (i == 1 || i == 2)
          raza = 35;
        else if (i == 3 || i == 4)
          raza = 65;
        else if (i == 5 || i == 6)
          raza = 100;
        int coord1 = (coordonate[i - 1][0] + coordonate[i - 1][2]) / 2;
        int coord2 = (coordonate[i - 1][1] + coordonate[i - 1][3]) / 2;
        if (distances1(cursorP.x, cursorP.y, raza, coord1, coord2, i) == 1) {
          place(i, player);
          player++;
          cout << 1 << '\n';
          player1[i] = 1;
        }
      }
      if (player % 2 == 1) {
        int da = 0;
        for (int i = 1; i <= 9; i++)
          if (cursorP.x >= coordPatrate[i - 1][0] &&
              cursorP.y >= coordPatrate[i - 1][1] &&
              cursorP.x <= coordPatrate[i - 1][2] &&
              cursorP.y <= coordPatrate[i - 1][3])
            if (t[i].mare != 0) {
              if (t[i].culoare3 == 1) {
                place(t[i].mare, player);
                t[i].mare = 0;
                t[i].culoare3 = 0;
                circles[t[i].mare] = 0;
                da = 1;
              }
            } else if (t[i].mediu != 0) {
              if (t[i].culoare2 == 1) {
                place(t[i].mediu, player);
                t[i].mediu = 0;
                t[i].culoare2 = 0;
                circles[t[i].mediu] = 0;
                da = 1;
              }
            } else if (t[i].mic != 0) {
              if (t[i].culoare1 == 1) {
                place(t[i].mic, player);
                circles[t[i].mic] = 0;
                t[i].mic = 0;
                t[i].culoare1 = 0;
                da = 1;
              }
            }
        /*if ((t[i].mare == 1 && t[i].culoare3 == 1) ||
            (t[i].mediu == 1 && t[i].culoare2 == 1) ||
            (t[i].mic == 1 && t[i].culoare1 == 1)) {
          place(i);
          cout << "patratul " << i << '\n';
          cout << 2 << '\n';
          da = 1;
        }*/
        if (da == 1) {
          player++;
        }
      }
    }
  }
  if (player % 2 == 0) {
    cleardevice();
    readimagefile("gobbletPS.jpg", 0, 0, 1920, 1080);
    readimagefile("Player2.jpg", 1815, 10, 1895, 70);
    joc();
    checkCircles();
  }
  while (player % 2 == 0) {
    POINT cursorP;
    GetCursorPos(&cursorP);
    if (ismouseclick(WM_LBUTTONDOWN)) {
      clearmouseclick(WM_LBUTTONDOWN);
      for (int i = 7; i <= 12; i++) {
        int raza;
        if (i == 7 || i == 8)
          raza = 35;
        else if (i == 9 || i == 10)
          raza = 65;
        else if (i == 11 || i == 12)
          raza = 100;
        int coord1 = (coordonate[i - 1][0] + coordonate[i - 1][2]) / 2;
        int coord2 = (coordonate[i - 1][1] + coordonate[i - 1][3]) / 2;
        if (distances2(cursorP.x, cursorP.y, raza, coord1, coord2, i) == 1) {
          place(i, player);
          player++;
          cout << 3 << '\n';
          player2[i] = 1;
        }
      }
      if (player % 2 == 0) {
        int da = 0;
        for (int i = 1; i <= 9; i++)
          if (cursorP.x >= coordPatrate[i - 1][0] &&
              cursorP.y >= coordPatrate[i - 1][1] &&
              cursorP.x <= coordPatrate[i - 1][2] &&
              cursorP.y <= coordPatrate[i - 1][3])
            if (t[i].mare != 0) {
              if (t[i].culoare3 == 2) {
                place(t[i].mare, player);
                t[i].mare = 0;
                t[i].culoare3 = 0;
                circles[t[i].mare] = 0;
                da = 1;
              }
            } else if (t[i].mediu != 0) {
              if (t[i].culoare2 == 2) {
                place(t[i].mediu, player);
                t[i].mediu = 0;
                t[i].culoare2 = 0;
                circles[t[i].mediu] = 0;
                da = 1;
              }
            } else if (t[i].mic != 0) {
              if (t[i].culoare1 == 2) {
                place(t[i].mic, player);
                circles[t[i].mic] = 0;
                t[i].mic = 0;
                t[i].culoare1 = 0;
                da = 1;
              }
            }
        /*
                if ((t[i].mare == 1 && t[i].culoare3 == 2) ||
                    (t[i].mediu == 1 && t[i].culoare2 == 2) ||
                    (t[i].mic == 1 && t[i].culoare1 == 2)) {
                  circles[i] = 0;
                  place(i);
                  cout << "patratul " << i << '\n';
                  cout << 4 << '\n';
                  da = 1;
                }*/
        if (da == 1) {
          player++;
        }
      }
    }
  }
}

void game();

struct punct {
  int x, y;
};
enum { engleza, romana } limba;
struct dreptunghi {
  int x1, x2, y1, y2;
} Play, Instr, Exit, Back, Ro, Eng, Players1, Players2;

int inauntru(punct P, dreptunghi D);
void instructiuni();
void players();
void bkgMeniuEng();
void bkgMeniuRom();

void meniu() {
  punct click;
  if (limba == engleza)
    bkgMeniuEng();
  else
    bkgMeniuRom();

  while (1) {
    if (ismouseclick(WM_LBUTTONDOWN)) {
      clearmouseclick(WM_LBUTTONDOWN);
      click.x = mousex();
      click.y = mousey();
      if (inauntru(click, Play)) {
        players();
        if (limba == engleza)
          bkgMeniuEng();
        else
          bkgMeniuRom();
      } else if (inauntru(click, Instr)) {
        instructiuni();
        if (limba == engleza)
          bkgMeniuEng();
        else
          bkgMeniuRom();
      } else if (inauntru(click, Exit))
        exit(0);
      else if (limba == engleza && inauntru(click, Ro)) {
        limba = romana;
        bkgMeniuRom();
      } else if (limba == romana && inauntru(click, Eng)) {
        limba = engleza;
        bkgMeniuEng();
      }
    }
  }
}
void bkgMeniuEng() {
  cleardevice();
  readimagefile("meniuEngleza.jpg", 0, 0, bkgX, bkgY);
  readimagefile("romania.jpg", Ro.x1, Ro.y1, Ro.x2, Ro.y2);
  readimagefile("uk.jpg", Eng.x1, Eng.y1, Eng.x2, Eng.y2);
}
void bkgMeniuRom() {
  cleardevice();
  readimagefile("meniuRomana.jpg", 0, 0, bkgX, bkgY);
  readimagefile("romania.jpg", Ro.x1, Ro.y1, Ro.x2, Ro.y2);
  readimagefile("uk.jpg", Eng.x1, Eng.y1, Eng.x2, Eng.y2);
}
void players() {
  punct click;
  cleardevice();
  if (limba == engleza)
    readimagefile("players.jpg", 0, 0, bkgX, bkgY);
  else
    readimagefile("jucatori.jpg", 0, 0, bkgX, bkgY);
  while (1) {
    if (ismouseclick(WM_LBUTTONDOWN)) {
      clearmouseclick(WM_LBUTTONDOWN);
      click.x = mousex();
      click.y = mousey();
      if (inauntru(click, Players1))
        return;  /// JUCATOR VS CALCULATOR
      else if (inauntru(click, Players2))
        game();  /// JUCATOR VS JUCATOR
      else if (inauntru(click, Back))
        break;
    }
  }
}

void instructiuni() {
  punct click;
  cleardevice();
  readimagefile("instructiuni.jpg", 0, 0, bkgX, bkgY);
  while (1) {
    if (ismouseclick(WM_LBUTTONDOWN)) {
      clearmouseclick(WM_LBUTTONDOWN);
      click.x = mousex();
      click.y = mousey();
      if (inauntru(click, Back)) break;
    }
  }
}

void definitii() {
  Play.x1 = 780;
  Play.y1 = 522;
  Play.x2 = 1132;
  Play.y2 = 637;
  Instr.x1 = 600;
  Instr.y1 = 670;
  Instr.x2 = 1318;
  Instr.y2 = 784;
  Exit.x1 = 856;
  Exit.y1 = 823;
  Exit.x2 = 1074;
  Exit.y2 = 936;
  Back.x1 = 1650;
  Back.y1 = 849;
  Back.x2 = 1888;
  Back.y2 = 1048;
  Ro.x1 = 75;
  Ro.y1 = 75;
  Ro.x2 = 150;
  Ro.y2 = 150;
  Eng.x1 = 75;
  Eng.y1 = 187;
  Eng.x2 = 150;
  Eng.y2 = 262;
  Players1.x1 = 727;
  Players1.y1 = 511;
  Players1.x2 = 1191;
  Players1.y2 = 625;
  Players2.x1 = 694;
  Players2.y1 = 670;
  Players2.x2 = 1224;
  Players2.y2 = 783;
}

int inauntru(punct P, dreptunghi D) {
  if (P.x > D.x1 && P.x < D.x2 && P.y > D.y1 && P.y < D.y2)
    return 1;
  else
    return 0;
}

void checkSquare(int mX, int mY, int raza, int color, int &ok, int i) {
  cout << "am intrat " << '\n';
  if (mX >= 50 && mY >= 375 && mX <= 515 && mY <= 640) {
    // patratul1
    if (raza == RAZA_CERC_1 && t[1].mic == 0 && t[1].mediu == 0 &&
        t[1].mare == 0) {
      t[1].mic = i;
      t[1].culoare1 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 262, 459, 302, 529);
      ok = 1;

    } else if (raza == RAZA_CERC_2 && t[1].mediu == 0 && t[1].mare == 0) {
      t[1].mediu == i;
      t[1].culoare2 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 242, 429, 322, 559);
      ok = 1;
    } else if (raza == RAZA_CERC_3 && t[1].mare == 0) {
      t[1].mare = i;
      t[1].culoare3 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 212, 394, 352, 594);
      ok = 1;
    }
  }
  if (mX >= 295 && mY >= 557 && mX <= 860 && mY <= 890) {
    // patratul2
    if (raza == RAZA_CERC_1 && t[2].mic == 0 && t[2].mediu == 0 &&
        t[2].mare == 0) {
      t[2].mic = i;
      t[2].culoare1 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 579, 677, 619, 747);
      ok = 1;
    } else if (raza == RAZA_CERC_2 && t[2].mediu == 0 && t[2].mare == 0) {
      t[2].mediu = i;
      t[2].culoare2 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 559, 647, 639, 777);
      ok = 1;
    } else if (raza == RAZA_CERC_3 && t[2].mare == 0) {
      t[2].mare = i;
      t[2].culoare3 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 529, 612, 669, 812);
      ok = 1;
    }
  }
  if (mX >= 634 && mY >= 755 && mX <= 1256 && mY <= 1061) {
    // patratul3
    if (raza == RAZA_CERC_1 && t[3].mic == 0 && t[3].mediu == 0 &&
        t[3].mare == 0) {
      t[3].mic = i;
      t[3].culoare1 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 924, 870, 964, 940);
      ok = 1;
    } else if (raza == RAZA_CERC_2 && t[3].mediu == 0 && t[3].mare == 0) {
      t[3].mediu = i;
      t[3].culoare2 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 904, 840, 984, 970);
      ok = 1;
    } else if (raza == RAZA_CERC_3 && t[3].mare == 0) {
      t[3].mare = i;
      t[3].culoare3 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 874, 805, 1014, 1015);
      ok = 1;
    }
  }
  if (mX >= 395 && mY >= 212 && mX <= 866 && mY <= 456) {
    // patratul4
    if (raza == RAZA_CERC_1 && t[4].mic == 0 && t[4].mediu == 0 &&
        t[4].mare == 0) {
      t[4].mic = i;
      t[4].culoare1 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 616, 298, 656, 368);
      ok = 1;
    } else if (raza == RAZA_CERC_2 && t[4].mediu == 0 && t[4].mare == 0) {
      t[4].mediu = i;
      t[4].culoare2 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 596, 268, 676, 398);
      ok = 1;
    } else if (raza == RAZA_CERC_3 && t[4].mare == 0) {
      t[4].mare = i;
      t[4].culoare3 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 566, 233, 706, 433);
      ok = 1;
    }
  }
  if (mX >= 698 && mY >= 370 && mX <= 1206 && mY <= 655) {
    // patratul5
    if (raza == RAZA_CERC_1 && t[5].mic == 0 && t[5].mediu == 0 &&
        t[5].mare == 0) {
      t[5].mic = i;
      t[5].culoare1 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 932, 475, 972, 545);
      ok = 1;
    } else if (raza == RAZA_CERC_2 && t[5].mediu == 0 && t[5].mare == 0) {
      t[5].mediu = i;
      t[5].culoare2 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 912, 445, 992, 575);
      ok = 1;
    } else if (raza == RAZA_CERC_3 && t[5].mare == 0) {
      t[5].mare = i;
      t[5].culoare3 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 882, 410, 1022, 610);
      ok = 1;
    }
  }
  if (mX >= 1208 && mY >= 556 && mX <= 1602 && mY <= 906) {
    // patratul6
    cout << "patrat6" << '\n';
    cout << raza << ' ' << t[6].mic << ' ' << t[6].mediu << ' ' << t[6].mare
         << '\n';
    if (raza == RAZA_CERC_1 && t[6].mic == 0 && t[6].mediu == 0 &&
        t[6].mare == 0) {
      t[6].mic = i;
      t[6].culoare1 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 1279, 682, 1319, 752);
      ok = 1;
    } else if (raza == RAZA_CERC_2 && t[6].mediu == 0 && t[6].mare == 0) {
      t[6].mediu = i;
      t[6].culoare2 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 1259, 652, 1339, 782);
      ok = 1;
    } else if (raza == RAZA_CERC_3 && t[6].mare == 0) {
      t[6].mare = i;
      t[6].culoare3 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 1229, 617, 1369, 817);
      ok = 1;
    }
  }
  if (mX >= 722 && mY >= 34 && mX <= 1209 && mY <= 282) {
    // patratul7
    if (raza == RAZA_CERC_1 && t[7].mic == 0 && t[7].mediu == 0 &&
        t[7].mare == 0) {
      t[7].mic = i;
      t[7].culoare1 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 945, 133, 985, 203);
      ok = 1;
    } else if (raza == RAZA_CERC_2 && t[7].mediu == 0 && t[7].mare == 0) {
      t[7].mediu = i;
      t[7].culoare2 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 925, 103, 1005, 233);
      ok = 1;
    } else if (raza == RAZA_CERC_3 && t[7].mare == 0) {
      t[7].mare = i;
      t[7].culoare3 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 895, 68, 1035, 268);
      ok = 1;
    }
  }
  if (mX >= 1024 && mY >= 214 && mX <= 1525 && mY <= 461) {
    // patratul8
    if (raza == RAZA_CERC_1 && t[8].mic == 0 && t[8].mediu == 0 &&
        t[8].mare == 0) {
      t[8].mic = i;
      t[8].culoare1 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 1254, 303, 1294, 373);
      ok = 1;
    } else if (raza == RAZA_CERC_2 && t[8].mediu == 0 && t[8].mare == 0) {
      t[8].mediu = i;
      t[8].culoare2 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 1234, 273, 1314, 403);
      ok = 1;
    } else if (raza == RAZA_CERC_3 && t[8].mare == 0) {
      t[8].mare = i;
      t[8].culoare3 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 1204, 238, 1344, 438);
      ok = 1;
    }
  }
  if (mX >= 1375 && mY >= 378 && mX <= 1822 && mY <= 694) {
    // patratul9
    if (raza == RAZA_CERC_1 && t[9].mic == 0 && t[9].mediu == 0 &&
        t[9].mare == 0) {
      t[9].mic = i;
      t[9].culoare1 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 1589, 483, 1629, 553);
      ok = 1;
    } else if (raza == RAZA_CERC_2 && t[9].mediu == 0 && t[9].mare == 0) {
      t[9].mediu = i;
      t[9].culoare2 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 1569, 453, 1649, 583);
      ok = 1;
    } else if (raza == RAZA_CERC_3 && t[9].mare == 0) {
      t[9].mare = i;
      t[9].culoare3 = color;
      readimagefile(color == 1 ? BLUE : ORANGE, 1539, 418, 1679, 618);
      ok = 1;
    }
  }
}

void render() {
  joc();
  // cleardevice();
  // table();
}

void update() { findCircle(player); }

int maxim(int a, int b) {
  if (a > b) return a;
  return b;
}

int minim(int a, int b) {
  if (a < b) return a;
  return b;
}

void game() {
  readimagefile("gobbletPS.jpg", 0, 0, 1920, 1080);

  checkCircles();
  while (1) {
    render();
    update();
  }
}

int main() {
  initwindow(1920, 1080, "Gobblet Gobblers");
  definitii();
  meniu();
  getch();
  closegraph();
}

void place(int i, int player) {
  int ok = 0;
  circles[i] = 1;
  clearmouseclick(WM_LBUTTONDOWN);
  cleardevice();
  readimagefile("gobbletPS.jpg", 0, 0, 1920, 1080);
  if (player % 2 == 1)
    readimagefile("Player1.jpg", 60, 10, 140, 70);
  else
    readimagefile("Player2.jpg", 1815, 10, 1895, 70);
  while (ok == 0) {
    POINT cursorPosition;
    int mX, mY;
    joc();
    checkCircles();
    GetCursorPos(&cursorPosition);
    if (ismouseclick(WM_LBUTTONDBLCLK)) {
      mX = cursorPosition.x;
      mY = cursorPosition.y;
      cout << mX << ' ' << mY << ' ' << i << '\n';

      if (i == 1 || i == 2) {
        checkSquare(mX, mY, RAZA_CERC_1, 1, ok, i);
      }
      if (i == 3 || i == 4) {
        checkSquare(mX, mY, RAZA_CERC_2, 1, ok, i);
      }
      if (i == 5 || i == 6) {
        checkSquare(mX, mY, RAZA_CERC_3, 1, ok, i);
      }

      if (i == 7 || i == 8) {
        checkSquare(mX, mY, RAZA_CERC_1, 2, ok, i);
      }
      if (i == 9 || i == 10) {
        checkSquare(mX, mY, RAZA_CERC_2, 2, ok, i);
      }
      if (i == 11 || i == 12) {
        checkSquare(mX, mY, RAZA_CERC_3, 2, ok, i);
      }

      cout << "ok : " << ok << '\n';
      joc();
      checkCircles();
      circles[i] = ok;
      clearmouseclick(WM_LBUTTONDBLCLK);
    }
  }
}

void player1wins() {
  readimagefile("play1win.jpg", 0, 0, 1920, 1080);
  meniu();
}
void player2wins() {
  readimagefile("play2win.jpg", 0, 0, 1920, 1080);
  meniu();
}
