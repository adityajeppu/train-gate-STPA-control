
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define y_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output function
 *
 */
void train_control_Outputs_wrapper(const boolean_T *exited1,
			const boolean_T *entered1,
			int32_T *pos1,
			int32_T *pos2,
			int32_T *pos3,
			int32_T *pos4,
			boolean_T *alarm1,
			int32_T *light)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
bool exited;
exited = exited1[0];
bool entered;
entered = entered1[0];
static bool LN, LS, RN, RS;
static bool alarm = false;

static int active_state = 0, STATEPOS = 0, light_state = 0;
static int count = 0, count_light = 0;
static bool openall = false, CLSRN = false; 
int pos1_out, pos2_out, pos3_out, pos4_out, light_out;

static bool statechart1active = false, statechart2active = false;

  static int Saturation = 90;
  static int Saturation_m = 90;
  static int Saturation_e = 90;
  static int Saturation_g = 90;
  static int qY;
  static int tmp1, tmp2, tmp3, tmp4;

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

  CLSRN = ((Saturation < 10.0) && (Saturation_g < 10.0));
pos1[0] = pos1_out;
pos2[0] = pos2_out;
pos3[0] = pos3_out;
pos4[0] = pos4_out;
light[0] = light_out;
alarm1[0] = alarm;
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


