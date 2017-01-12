#define DATA_BUS_SIZE 4

#define LCD_4_BIT_OPERATION 0x02
#define LCD_8_BIT_FUNCTION 0x28

#define LCD_DISPLAY_ON 0x0F
#define LCD_CLEAR_DISPLAY 0x01

int rs = 12;
int en = 11;

int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;

int d_bus[DATA_BUS_SIZE] = {d4, d5, d6, d7};

void setup() {
  pinMode(rs, OUTPUT);
  pinMode(en, OUTPUT);

  for (int i = 0; i < DATA_BUS_SIZE; i++) {
    pinMode(d_bus[i], OUTPUT);
  }

  set_4_bit_mode();
  set_8_bit_function_mode();
  set_display_on();

  set_entry_mode_increment_cursor_no_shift();
  clear_display();
  
  write_str("Hello world");
}

void loop() {

}

void set_4_bit_mode() {
  digitalWrite(rs, LOW);
  write4(LCD_4_BIT_OPERATION);
  delay(1);
}

void set_8_bit_function_mode() {
  digitalWrite(rs, LOW);
  write8(LCD_8_BIT_FUNCTION);
}

void set_display_on() {
  digitalWrite(rs, LOW);
  write8(LCD_DISPLAY_ON);
}

void set_entry_mode_increment_cursor_no_shift() {
  digitalWrite(rs, LOW);
  write8(0x06);
}

void clear_display() {
  write8(LCD_CLEAR_DISPLAY);
  delay(1);
}

void pulse_enable() {
  digitalWrite(en, LOW);
  delay(1);
  digitalWrite(en, HIGH);
  delay(1);
  digitalWrite(en, LOW);
  delay(1);
}

void write_str(String val){
  for(int i = 0; i < val.length(); i++){
    write_char(val.charAt(i));  
  }
}

void write_char(char val) {
  digitalWrite(rs, HIGH);
  write8(val);
}

void write8(byte value) {
  write4(value >> 4);
  delay(1);
  write4(value);
  delay(1);
}

void write4(byte value) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(d_bus[i], (value >> i) & 0x01);
  }
  pulse_enable();
}
