/*
 * File: csro_ctrl.h
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

#ifndef RTW_HEADER_csro_ctrl_h_
#define RTW_HEADER_csro_ctrl_h_
#include "fund_modbus_rtu.h"
#ifndef csro_ctrl_COMMON_INCLUDES_
#define csro_ctrl_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* csro_ctrl_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */

/* Model entry point functions */
extern void csro_ctrl_initialize(void);
extern void csro_ctrl_step(void);
extern void csro_ctrl_terminate(void);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'csro_ctrl'
 * '<S1>'   : 'csro_ctrl/Subsystem'
 * '<S2>'   : 'csro_ctrl/Subsystem/direct_out'
 * '<S3>'   : 'csro_ctrl/Subsystem/direct_out/Compare To Constant'
 */
#endif                                 /* RTW_HEADER_csro_ctrl_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
