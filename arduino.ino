// comment these out during prod
//#include <./LCD_I2C.h>
//#define delay

#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2); 
//LCD_I2C lcd(0x3F, 16, 2);

#define BUTTON_RIGHT 8
#define BUTTON_LEFT 9

uint8_t bitmap[32][8] = {{0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}, {0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000}};

struct charpos {
  int x;
  int y;
  int id;
  charpos(int x, int y, int id) {
    this->x = x;
    this->y = y;
    this->id = id;
  }
};

struct linkedEl {
  linkedEl *next = nullptr;
  linkedEl *prev = nullptr;
  charpos *value;
  linkedEl(charpos *val) {
    this->value = val;
  }
};

void destroy(linkedEl *el) {
  delete el->value;
  delete el;
}

struct linkedList {
  int length = 0;
  linkedEl *head = nullptr;
  linkedEl *tail = nullptr;
  void prepend(linkedEl *element) {
    element->next = this->head;
    if (this->head != nullptr) {
      this->head->prev = element;
    }
    if (this->tail == nullptr) {
      this->tail = element;
    }
    this->head = element;
    this->length += 1;
  }
  void append(linkedEl *element) {
    element->prev = this->tail;
    if (this->tail != nullptr) {
      this->tail->next = element;
    }
    if (this->head == nullptr) {
      this->head = element;
    }
    this->tail = element;
    this->length += 1;
  }
  linkedEl *deleteTail() {
    if (this->tail == nullptr) {
      return nullptr;
    }
    linkedEl *tmp = this->tail;
    if (tmp->prev != nullptr) {
      tmp->prev->next = nullptr;
    }
    if (tmp == this->head) {
      this->head = nullptr;
    }
    this->tail = tmp->prev;
    tmp->prev = nullptr;
    tmp->next = nullptr;
    this->length -= 1;
    return tmp;
  }
  linkedEl *popvalue(int x, int y) {
    linkedEl *tmp = this->head;
    while (tmp) {
      if (tmp->value->x == x && tmp->value->y == y) {
        if (tmp->next != nullptr) {
          tmp->next->prev = tmp->prev;
        }
        if (tmp->prev != nullptr) {
          tmp->prev->next = tmp->next;
        }
        this->length -= 1;
        if (tmp == this->head) {
          this->head = tmp->next;
        }
        if (tmp == this->tail) {
          this->tail = tmp->prev;
        }
        tmp->next = nullptr;
        tmp->prev = nullptr;
        break;
      }
      tmp = tmp->next;
    }
    return tmp;
  }
};

linkedList *usedchars = new linkedList;

// get unused char for the given coordinate, or refresh a previously char [7 custom char limit, out of 32 possible chars to display]
int getavailcharid(int x, int y) {
  // find existing char with X and Y
  linkedEl *reused = usedchars->popvalue(x, y);
  if (reused == nullptr) {
    // find next avail empty position, or dump last avail position
    if (usedchars->length == 7) {
      linkedEl *tmp = usedchars->deleteTail();
      lcd.setCursor(tmp->value->x, tmp->value->y);
      lcd.write(' ');
      tmp->value->x = x;
      tmp->value->y = y;
      usedchars->prepend(tmp);
      return tmp->value->id;

    } else {
      charpos *newchar = new charpos(x, y, usedchars->length);
      linkedEl *newel = new linkedEl(newchar);
      usedchars->prepend(newel);
      return newchar->id;
    }
  } else {
    usedchars->prepend(reused);
    return reused->value->id;
  }
}

void setBit(uint8_t &v, int n, bool state) {
  n = 4 - n;
  v = (v & ~(1 << n)) | ((state ? 1 : 0) << n);
}

bool getBit(uint8_t v, int n) {
  n = 4 - n;
  return v & (1 << n);
}

void writeat(int x, int y, bool value, bool isfood) {
  int charxpos = x / 5;
  int pixelxpos = x % 5;
  int charypos = y / 8;
  int pixelypos = y % 8;
  setBit(bitmap[charxpos + (charypos * 16)][pixelypos], pixelxpos, value);

  int charid = isfood == true ? 7 : getavailcharid(charxpos, charypos);
  lcd.createChar(charid, bitmap[charxpos + (charypos * 16)]);
  lcd.setCursor(charxpos, charypos);
  lcd.write(charid);
}

bool getat(int x, int y) {
  int charxpos = x / 5;
  int pixelxpos = x % 5;
  int charypos = y / 8;
  int pixelypos = y % 8;
  return getBit(bitmap[charxpos + (charypos * 16)][pixelypos], pixelxpos);
}

int xlimit = 50;
int ylimit = 16;

struct game {
  linkedList *parts = new linkedList;
  int x = 0;
  int y = 0;
  int dir = 1; // 0 right, 1 down, 2 left, 3 up
  int foodx = 0;
  int foody = 0;
  bool running = true;
  game() {
    this->randomfood();
  }
  void randomfood() {
    this->foodx = random(0, xlimit);
    this->foody = random(0, ylimit);
    bool exists = getat(this->foodx, this->foody);
    if (exists) {
      randomfood(); // try repeatedly until the game randomly finds an empty slot, insanely slow!
    } else {
      writeat(this->foodx, this->foody, 1, true);
    }
  }
  void redrawfood(){
    writeat(this->foodx, this->foody, 1, true);
  }
  bool grow() {
    if (dir & 0x1 == 1) {
      this->y += dir == 3 ? -1 : 1;
      this->y = (this->y + ylimit) % ylimit;
    } else {
      this->x += dir == 0 ? 1 : -1;
      this->x = (this->x + xlimit) % xlimit;
    }
    bool ate = getat(this->x, this->y);
    charpos *newheadpixel = new charpos(this->x, this->y, 0);
    linkedEl *newhead = new linkedEl(newheadpixel);
    parts->prepend(newhead);
    writeat(this->x, this->y, 1, false);
    return ate;
  }
  void tick() {
    if (running) {
      bool ate = this->grow();
      if (ate) {
        if (this->parts->length == 35) {
          this->finish();
          lcd.print("YOU WIN");
          return;
        }
        if (this->x == this->foodx && this->y == this->foody) {
          lcd.setCursor(13, 1);
          lcd.print(this->parts->length - 3);
          this->randomfood();
        } else {
          running = false;
          this->finish();
          lcd.print("YOU LOOSE");
          return;
        }
      } else {
        this->shrink();
      }
      this->redrawfood();
    }
  }
  void finish() {
    running = false;
    lcd.clear();
    lcd.setCursor(0, 0);
  }
  void shrink() {
    linkedEl *tail = parts->deleteTail();
    writeat(tail->value->x, tail->value->y, 0, false);
    destroy(tail);
  }
  void turnleft() {
    this->dir = (this->dir + 3) % 4;
  }
  void turnright() {
    this->dir = (this->dir + 1) % 4;
  }
};

game *snake;

void setup() {
  randomSeed(analogRead(0));
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  lcd.begin();
  lcd.backlight();
  lcd.noAutoscroll();
  lcd.setCursor(10, 0);
  lcd.write(255);
  lcd.print("Score");
  lcd.setCursor(10, 1);
  lcd.write(255);
  lcd.setCursor(13, 1);
  lcd.print(0);

  snake = new game();

  snake->grow();
  snake->grow();
  snake->grow();
}


void loop() {
  int right = digitalRead(BUTTON_RIGHT);
  if (right) {
    snake->turnright();
  }
  int left = digitalRead(BUTTON_LEFT);
  if (left) {
    snake->turnleft();
  }
  snake->tick();
  delay(200);
}
