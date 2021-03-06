#ifndef BAP_SMC_H
#define BAP_SMC_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "BAP_define.h"

#define BAP_SMC_FORMULA_CONST_D 0.142711519     // 7/(5*g)

typedef struct BAP_SMC_S
{
    float yd_in;
    BAP_DiscreteFunction_S yd;
    BAP_DiscreteFunction_S e;   // yd-y
    BAP_SatFunction_S sat;
    float k1;
    float K;
    float scale;
    int with_limit;
    BAP_SatFunction_S output_limit;
}BAP_SMC_S;

typedef struct BAP_SecondOrderDLF_S  //for discrete low pass filter type: 1/(as + 1)^2
{
    BAP_DiscreteFunction_S input;   //must have more than 2 minus samples
    BAP_DiscreteFunction_S output;   //must have more than 2 minus samples
    float a;
    float T;
    float exp_aT;
}BAP_SecondOrderLF_S;

BAP_RESULT_E BAP_SMCSecondOrderLFInit(BAP_SecondOrderLF_S* lf, float dT, float a);
BAP_RESULT_E BAP_SMCSecondOrderLFGetOutput(BAP_SecondOrderLF_S* lf, float* out);
BAP_RESULT_E BAP_SMCSecondOrderLFAppendInput(BAP_SecondOrderLF_S* lf, float input);

BAP_RESULT_E BAP_SMCInit(BAP_SMC_S* smc, int order, float dT, float sat_upper, float sat_lower, float k1, float K, float yd, float scale);
BAP_RESULT_E BAP_SMCOuputCal(BAP_SMC_S* smc, float* out);
BAP_RESULT_E BAP_SMCChangeSetPoint(BAP_SMC_S* smc, float yd);
BAP_RESULT_E BAP_SMCUpdateParam(BAP_SMC_S* smc, float y);
BAP_RESULT_E BAP_SMCOutputLimitEnable(BAP_SMC_S* smc, float lower, float upper);
BAP_RESULT_E BAP_SMCOutputLimitDisable(BAP_SMC_S* smc);
BAP_RESULT_E BAP_SMCUpdate(BAP_SMC_S* smc, float k1, float K);

#endif