/*
 * File: csro_ctrl.c
 *
 * Code generated for Simulink model 'csro_ctrl'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Mon Nov  8 17:03:38 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "csro_ctrl.h"

/* Model step function */
void csro_ctrl_step(void)
{
    /* DataStoreWrite: '<S1>/Data Store Write' incorporates:
     *  Constant: '<S3>/Constant'
     *  DataStoreRead: '<S1>/Data Store Read'
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     *  RelationalOperator: '<S3>/Compare'
     */
    sys_regs.inputs[0] = (int16_T)(sys_regs.holdings[0] >= 0);
}

/* Model initialize function */
void csro_ctrl_initialize(void)
{
    /* (no initialization code required) */
}

/* Model terminate function */
void csro_ctrl_terminate(void)
{
    /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
