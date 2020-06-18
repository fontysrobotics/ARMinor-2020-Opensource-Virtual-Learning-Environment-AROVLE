/*
 * finaldriver.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "finaldriver".
 *
 * Model version              : 1.15
 * Simulink Coder version : 9.3 (R2020a) 18-Nov-2019
 * C++ source code generated on : Tue May  5 17:04:35 2020
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_finaldriver_h_
#define RTW_HEADER_finaldriver_h_
#include <cmath>
#include <cstring>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "finaldriver_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T FilterCoefficient;            /* '<S40>/Filter Coefficient' */
  real_T Add;                          /* '<Root>/Add' */
  real_T IntegralGain;                 /* '<S34>/Integral Gain' */
  real_T TransferFcn1;                 /* '<Root>/Transfer Fcn1' */
  uint8_T Output;                      /* '<S2>/Output' */
} B_finaldriver_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint8_T Output_DSTATE;               /* '<S2>/Output' */
} DW_finaldriver_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T Integrator_CSTATE_f;          /* '<S37>/Integrator' */
  real_T Filter_CSTATE;                /* '<S32>/Filter' */
  real_T TransferFcn1_CSTATE[2];       /* '<Root>/Transfer Fcn1' */
} X_finaldriver_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<Root>/Integrator' */
  real_T Integrator_CSTATE_f;          /* '<S37>/Integrator' */
  real_T Filter_CSTATE;                /* '<S32>/Filter' */
  real_T TransferFcn1_CSTATE[2];       /* '<Root>/Transfer Fcn1' */
} XDot_finaldriver_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<Root>/Integrator' */
  boolean_T Integrator_CSTATE_f;       /* '<S37>/Integrator' */
  boolean_T Filter_CSTATE;             /* '<S32>/Filter' */
  boolean_T TransferFcn1_CSTATE[2];    /* '<Root>/Transfer Fcn1' */
} XDis_finaldriver_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T INPUT;                        /* '<Root>/INPUT' */
} ExtU_finaldriver_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T simTim;                       /* '<Root>/simTim' */
  real_T MotorOutput;                  /* '<Root>/MotorOutput' */
} ExtY_finaldriver_T;

/* Real-time Model Data Structure */
struct tag_RTM_finaldriver_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_finaldriver_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[5];
  real_T odeF[3][5];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Class declaration for model finaldriver */
class finaldriverModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_finaldriver_T finaldriver_U;

  /* External outputs */
  ExtY_finaldriver_T finaldriver_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  finaldriverModelClass();

  /* Destructor */
  ~finaldriverModelClass();

  /* Real-Time Model get method */
  RT_MODEL_finaldriver_T * getRTM();

  /* private data and function members */
 private:
  /* Block signals */
  B_finaldriver_T finaldriver_B;

  /* Block states */
  DW_finaldriver_T finaldriver_DW;
  X_finaldriver_T finaldriver_X;       /* Block continuous states */

  /* Real-Time Model */
  RT_MODEL_finaldriver_T finaldriver_M;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void finaldriver_derivatives();
};

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/FixPt Data Type Propagation' : Unused code path elimination
 * Block '<S4>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/FixPt Data Type Duplicate1' : Unused code path elimination
 */

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
 * '<Root>' : 'finaldriver'
 * '<S1>'   : 'finaldriver/Compare To Zero'
 * '<S2>'   : 'finaldriver/Counter Free-Running'
 * '<S3>'   : 'finaldriver/PID Controller1'
 * '<S4>'   : 'finaldriver/Counter Free-Running/Increment Real World'
 * '<S5>'   : 'finaldriver/Counter Free-Running/Wrap To Zero'
 * '<S6>'   : 'finaldriver/PID Controller1/Anti-windup'
 * '<S7>'   : 'finaldriver/PID Controller1/D Gain'
 * '<S8>'   : 'finaldriver/PID Controller1/Filter'
 * '<S9>'   : 'finaldriver/PID Controller1/Filter ICs'
 * '<S10>'  : 'finaldriver/PID Controller1/I Gain'
 * '<S11>'  : 'finaldriver/PID Controller1/Ideal P Gain'
 * '<S12>'  : 'finaldriver/PID Controller1/Ideal P Gain Fdbk'
 * '<S13>'  : 'finaldriver/PID Controller1/Integrator'
 * '<S14>'  : 'finaldriver/PID Controller1/Integrator ICs'
 * '<S15>'  : 'finaldriver/PID Controller1/N Copy'
 * '<S16>'  : 'finaldriver/PID Controller1/N Gain'
 * '<S17>'  : 'finaldriver/PID Controller1/P Copy'
 * '<S18>'  : 'finaldriver/PID Controller1/Parallel P Gain'
 * '<S19>'  : 'finaldriver/PID Controller1/Reset Signal'
 * '<S20>'  : 'finaldriver/PID Controller1/Saturation'
 * '<S21>'  : 'finaldriver/PID Controller1/Saturation Fdbk'
 * '<S22>'  : 'finaldriver/PID Controller1/Sum'
 * '<S23>'  : 'finaldriver/PID Controller1/Sum Fdbk'
 * '<S24>'  : 'finaldriver/PID Controller1/Tracking Mode'
 * '<S25>'  : 'finaldriver/PID Controller1/Tracking Mode Sum'
 * '<S26>'  : 'finaldriver/PID Controller1/Tsamp - Integral'
 * '<S27>'  : 'finaldriver/PID Controller1/Tsamp - Ngain'
 * '<S28>'  : 'finaldriver/PID Controller1/postSat Signal'
 * '<S29>'  : 'finaldriver/PID Controller1/preSat Signal'
 * '<S30>'  : 'finaldriver/PID Controller1/Anti-windup/Passthrough'
 * '<S31>'  : 'finaldriver/PID Controller1/D Gain/Internal Parameters'
 * '<S32>'  : 'finaldriver/PID Controller1/Filter/Cont. Filter'
 * '<S33>'  : 'finaldriver/PID Controller1/Filter ICs/Internal IC - Filter'
 * '<S34>'  : 'finaldriver/PID Controller1/I Gain/Internal Parameters'
 * '<S35>'  : 'finaldriver/PID Controller1/Ideal P Gain/Passthrough'
 * '<S36>'  : 'finaldriver/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S37>'  : 'finaldriver/PID Controller1/Integrator/Continuous'
 * '<S38>'  : 'finaldriver/PID Controller1/Integrator ICs/Internal IC'
 * '<S39>'  : 'finaldriver/PID Controller1/N Copy/Disabled'
 * '<S40>'  : 'finaldriver/PID Controller1/N Gain/Internal Parameters'
 * '<S41>'  : 'finaldriver/PID Controller1/P Copy/Disabled'
 * '<S42>'  : 'finaldriver/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S43>'  : 'finaldriver/PID Controller1/Reset Signal/Disabled'
 * '<S44>'  : 'finaldriver/PID Controller1/Saturation/Passthrough'
 * '<S45>'  : 'finaldriver/PID Controller1/Saturation Fdbk/Disabled'
 * '<S46>'  : 'finaldriver/PID Controller1/Sum/Sum_PID'
 * '<S47>'  : 'finaldriver/PID Controller1/Sum Fdbk/Disabled'
 * '<S48>'  : 'finaldriver/PID Controller1/Tracking Mode/Disabled'
 * '<S49>'  : 'finaldriver/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S50>'  : 'finaldriver/PID Controller1/Tsamp - Integral/Passthrough'
 * '<S51>'  : 'finaldriver/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S52>'  : 'finaldriver/PID Controller1/postSat Signal/Forward_Path'
 * '<S53>'  : 'finaldriver/PID Controller1/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_finaldriver_h_ */
