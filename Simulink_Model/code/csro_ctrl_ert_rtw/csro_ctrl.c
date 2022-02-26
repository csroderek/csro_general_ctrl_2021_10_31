/*
 * File: csro_ctrl.c
 *
 * Code generated for Simulink model 'csro_ctrl'.
 *
 * Model version                  : 1.7
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Sat Feb 26 19:47:11 2022
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
    /* DataStoreWrite: '<Root>/Data Store Write' incorporates:
     *  DataStoreRead: '<Root>/Data Store Read'
     */
    sys_regs.inputs[100] = sys_regs.holdings[0];
    sys_regs.inputs[101] = sys_regs.holdings[1];
    sys_regs.inputs[102] = sys_regs.holdings[2];
    sys_regs.inputs[103] = sys_regs.holdings[3];
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
