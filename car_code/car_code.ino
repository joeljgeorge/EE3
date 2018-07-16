int left_wheel;
int right_wheel;
int left_detector;
int middle_detector;
int right_detector;
int led_green;
int led_red;
int led_blue;
char current_motion;
bool has_stopped = false;
int ld_state;
int md_state;
int rd_state;
int ld_lower;
int ld_higher;
int md_lower;
int md_higher;
int rd_lower;
int rd_higher;
//TODO: switch thresholds
void setup() {
  // put your setup code here, to run once:
  left_wheel = 3;
  right_wheel = 9;
  left_detector = A7;
  middle_detector = A0;
  right_detector = A1;
  led_green = 8;
  led_red = 4;
  led_blue = 6;
  pinMode(left_detector, INPUT);
  pinMode(middle_detector, INPUT);
  pinMode(right_detector, INPUT);
  pinMode(left_wheel, OUTPUT);
  pinMode(right_wheel, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_blue, OUTPUT);
  digitalWrite(led_red, LOW);
  digitalWrite(led_blue, LOW);
  digitalWrite(led_green, LOW);
  Serial.begin(9600);
  ld_state = analogRead(left_detector);
  md_state = analogRead(middle_detector);
  rd_state = analogRead(right_detector);
  ld_lower = ld_state - 100;
  ld_higher = ld_state + 100;
  md_lower = md_state - 50;
  md_higher = md_state + 50;
  rd_lower = rd_state - 50;
  rd_higher = rd_state + 50;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(has_stopped){
    digitalWrite(led_blue, HIGH);
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, HIGH);
  }
  else{
    int current_l_d_state = analogRead(left_detector);
    int current_m_d_state = analogRead(middle_detector);
    int current_r_d_state = analogRead(right_detector);
    Serial.println("This is the left state: ");
    Serial.println(current_l_d_state);
    Serial.println(ld_state);
    Serial.println("This is the middle state: ");
    Serial.println(current_m_d_state);
    Serial.println(md_state);
    Serial.println("This is the right state: ");
    Serial.println(current_r_d_state);
    Serial.println(rd_state);
    Serial.println(current_motion);
  
  if((current_l_d_state <= (ld_state - 300)) && ((current_m_d_state >= md_lower) && (current_m_d_state <= md_higher))  && ((current_r_d_state >= rd_lower) && (current_r_d_state <= rd_higher))){//turning left
    current_motion = 'l';
    digitalWrite(led_blue, HIGH);
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, LOW);
    analogWrite(right_wheel, 110);
    analogWrite(left_wheel, 40);
//    analogWrite(left_wheel, 0);
//    analogWrite(right_wheel, 120);
//    analogWrite(right_wheel, 0);
  }
  else if(((current_l_d_state >= ld_lower) && (current_l_d_state <= ld_higher)) && ((current_m_d_state >= md_lower) && (current_m_d_state <= md_higher)) && (current_r_d_state <= (rd_state - 300))){//turning right
    current_motion = 'r';
    digitalWrite(led_blue, LOW);
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, HIGH);
    analogWrite(left_wheel, 110);
    analogWrite(right_wheel, 40);
//     analogWrite(right_wheel, 0);
//     analogWrite(left_wheel, 110);
//     analogWrite(left_wheel, 0);
  }
  else if(((current_l_d_state >= ld_lower) && (current_l_d_state <= ld_higher)) && (current_m_d_state <= (md_state - 300)) && ((current_r_d_state >= rd_lower) && (current_r_d_state <= rd_higher))){//going straight
    current_motion = 's';
    digitalWrite(led_blue, LOW);
    digitalWrite(led_green, HIGH);
    digitalWrite(led_red, LOW);
    analogWrite(right_wheel, 80);
    analogWrite(left_wheel, 70);
  }
  else if(current_l_d_state <= (ld_state - 300) && current_m_d_state <= (md_state - 300) && (current_r_d_state <= (rd_state - 300))){//stopped
    current_motion = 'n';
    //TODO: put counter in to check for multiple intersections 
    digitalWrite(led_blue, HIGH);
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, HIGH);
    analogWrite(right_wheel, 0);
    analogWrite(left_wheel, 0);//delay maybe?
    has_stopped = true;
  }
  else{
    digitalWrite(led_blue, LOW);
    digitalWrite(led_green, HIGH);
    digitalWrite(led_red, LOW);
    analogWrite(right_wheel, 110);
    analogWrite(right_wheel, 80);
    analogWrite(left_wheel, 120);
    analogWrite(left_wheel, 80); 
    }
//  else{//maintain direction
//    if(current_motion == 'l'){
//      current_motion = 'l';
//      analogWrite(right_wheel, 110);
//      analogWrite(left_wheel, 80);
////      analogWrite(left_wheel, 0);
////      analogWrite(right_wheel, 120);
////      analogWrite(right_wheel, 0);
//    }
//    else if(current_motion == 'r'){
//      current_motion = 'r';
//     current_motion = 'r';
//    digitalWrite(led_blue, LOW);
//    digitalWrite(led_green, LOW);
//    digitalWrite(led_red, HIGH);
//    analogWrite(right_wheel, 80);
//    analogWrite(left_wheel, 120);
////      analogWrite(right_wheel, 0);
////      analogWrite(left_wheel, 110);
////      analogWrite(left_wheel, 0);
//    }
//    else if(current_motion == 's'){
//      current_motion = 's';
//         digitalWrite(led_blue, LOW);
//    digitalWrite(led_green, HIGH);
//    digitalWrite(led_red, LOW);
//  analogWrite(right_wheel, 110);
//    analogWrite(right_wheel, 80);
//    analogWrite(left_wheel, 120);
//    analogWrite(left_wheel, 80); 
////      analogWrite(right_wheel, 120);
////      analogWrite(left_wheel, 110);
////      analogWrite(left_wheel, 0);
////      analogWrite(right_wheel, 0);
//    }
//    }
  }
 }


