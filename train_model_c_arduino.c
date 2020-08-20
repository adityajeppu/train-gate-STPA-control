#include <Servo.h>

String blenderin;
boolean LN, LS, RN, RS, alarm;
int active_state = 0, STATEPOS = 0, count = 0, count_light = 0, light_state = 0;
boolean exited = false, openall = false, entered = false, CLSRN = false; 
int pos1_out, pos2_out, pos3_out, pos4_out;
int light_out = 1, train_pos = 2500;
boolean statechart1active, statechart2active;
Servo ser1;


void setup()
{
  Serial.begin(115200);
  ser1.attach(3);
}

void loop()
{
  delay(1000);
  
  static int Saturation = 90;
  static int Saturation_m = 90;
  static int Saturation_e = 90;
  static int Saturation_g = 90;
  int qY;
  int tmp1, tmp2, tmp3, tmp4;

  train_pos -= 60;
  if (!(statechart1active)) {
    statechart1active = true;
    active_state = 1;
    LN = true;
    LS = true;
    RN = true;
    RS = true;
    STATEPOS = 1;
    alarm = false;
  } else {
    switch (active_state) {
     case 4:
      LN = false;
      RS = false;
      if (exited) {
        active_state = 5;
        LN = true;
        LS = true;
        RN = true;
        RS = true;
        STATEPOS = 5;
        count = 0;
        alarm = false;
      } else {
        qY = count + 1;
        if (qY > 20) {
          qY = 20;
        }

        count = qY;
      }
      break;

     case 5:
      LN = true;
      LS = true;
      RN = true;
      RS = true;
      if (openall) {
        active_state = 1;
        LN = true;
        LS = true;
        RN = true;
        RS = true;
        STATEPOS = 1;
        alarm = false;
      } else if (count > 12) {
        active_state = -1;
        alarm = true;
      } else {
        qY = count + 1;
        if (qY > 20) {
          qY = 20;
        }

        count = qY;
      }
      break;

     case 1:
      LN = true;
      LS = true;
      RN = true;
      RS = true;
      if (entered) {
        active_state = 2;
        LS = false;
        RN = false;
        STATEPOS = 2;
        count = 0;
        alarm = false;
      }
      break;

     case -1:
      if ((STATEPOS == 2) && CLSRN) {
        active_state = 3;
        count = 0;
        STATEPOS = 3;
        alarm = false;
      } else if ((STATEPOS == 4) && exited) {
        active_state = 5;
        LN = true;
        LS = true;
        RN = true;
        RS = true;
        STATEPOS = 5;
        count = 0;
        alarm = false;
      } else {
        alarm = true;
      }
      break;

     case 3:
      if (count > 4) {
        active_state = 4;
        LN = false;
        RS = false;
        count = 0;
        STATEPOS = 4;
        alarm = false;
      } else {
        qY = count + 1;
        if (qY > 20) {
          qY = 20;
        }

        count = qY;
      }
      break;

     default:
      LS = false;
      RN = false;
      if (count > 12) {
        active_state = -1;
        alarm = true;
      } else if (CLSRN) {
        active_state = 3;
        count = 0;
        STATEPOS = 3;
        alarm = false;
      } else {
        qY = count + 1;
        if (qY > 20) {
          qY = 20;
        }

        count = qY;
      }
      break;
    }
  }

/* 
 *  statechart over
 *  
 */
 
  if (RN) {
    tmp1 = 10;
  } else {
    tmp1 = -10;
  }

  Saturation = Saturation + tmp1;
  if (Saturation > 90.0) {
    Saturation = 90.0;
  } else {
    if (Saturation < 0.0) {
      Saturation = 0.0;
    }
  }
  


  if (RS) {
    tmp2 = 10;
  } else {
    tmp2 = -10;
  }

  Saturation_m = tmp2 + Saturation_m;
  if (Saturation_m > 90.0) {
    Saturation_m = 90.0;
  } else {
    if (Saturation_m < 0.0) {
      Saturation_m = 0.0;
    }
  }

  if (LN) {
    tmp3 = 10;
  } else {
    tmp3 = -10;
  }

  Saturation_e = tmp3 + Saturation_e;
  if (Saturation_e > 90.0) {
    Saturation_e = 90.0;
  } else {
    if (Saturation_e < 0.0) {
      Saturation_e = 0.0;
    }
  }
  
  if (LS) {
    tmp4 = 10;
  } else {
    tmp4 = -10;
  }

  Saturation_g = tmp4 + Saturation_g;
  if (Saturation_g > 90.0) {
    Saturation_g = 90.0;
  } else {
    if (Saturation_g < 0.0) {
      Saturation_g = 0.0;
    }
  }

  if (!(statechart2active)) {
    statechart2active = true;
    light_state = 0;
    light_out = 1;
  } else {
    switch (light_state) {
     case 0:
      light_out = 1;
      if (entered) {
        light_state = 1;
        light_out = 2;
        count_light = 0;
      }
      break;

     case 2:
      light_out = 3;
      if (exited) {
        light_state = 3;
        light_out = 2;
      }
      break;

     case 1:
      light_out = 2;
      if (count_light >= 4) {
        light_state = 2;
        light_out = 3;
      } else {
        count_light++;
      }
      break;

     default:
      light_out = 2.0;
      if ((Saturation >= 80.0) && (Saturation_m >= 80.0) &&
          (Saturation_e >= 80.0) && (Saturation_g >= 80.0)) {
        light_state = 0;
        light_out = 1;
        openall = true;
      }
      break;
    }
  }

  pos4_out = Saturation_g;
  pos3_out = Saturation_e;
  pos2_out = Saturation_m;
  pos1_out = Saturation;
  if(train_pos < -1000)
  {
    exited = true;
  }
  else
    exited = false;

    
  if(train_pos < 2000 && train_pos > 1600)
  {
    entered = true;
  }
  else
    entered = false;
  CLSRN = ((Saturation < 10.0) && (Saturation_g < 10.0));
  Serial.print(pos1_out); Serial.print(" ");
  Serial.print(pos2_out); Serial.print(" ");
  Serial.print(pos3_out); Serial.print(" ");
  Serial.print(pos4_out); Serial.print(" ");
  Serial.print(light_out); Serial.print(" ");
  Serial.print(active_state); Serial.print(" ");
  Serial.print(train_pos); Serial.println();
  ser1.write(pos1_out - 10);
  if(train_pos < -2500){
    Serial.println("STOP\n");
    Serial.end();
  }
}