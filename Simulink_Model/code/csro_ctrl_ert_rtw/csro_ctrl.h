/*
 * File: csro_ctrl.h
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

#ifndef RTW_HEADER_csro_ctrl_h_
#define RTW_HEADER_csro_ctrl_h_
#include "mb_config.h"
#ifndef csro_ctrl_COMMON_INCLUDES_
#define csro_ctrl_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* csro_ctrl_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Includes for objects with custom storage classes. */
#include "fnd_com.h"

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
 */
#endif                                 /* RTW_HEADER_csro_ctrl_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
