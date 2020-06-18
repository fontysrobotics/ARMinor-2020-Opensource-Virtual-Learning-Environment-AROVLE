#include "ros/ros.h"
#include <sensor_msgs/JointState.h>
#include <iostream>

/*
 * finaldriver.cpp
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

#include "finaldriver.h"
#include "finaldriver_private.h"
/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void finaldriverModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si)
{
    /* Solver Matrices */
    static const real_T rt_ODE3_A[3] = {
        1.0 / 2.0, 3.0 / 4.0, 1.0};

    static const real_T rt_ODE3_B[3][3] = {
        {1.0 / 2.0, 0.0, 0.0},

        {0.0, 3.0 / 4.0, 0.0},

        {2.0 / 9.0, 1.0 / 3.0, 4.0 / 9.0}};

    time_T t = rtsiGetT(si);
    time_T tnew = rtsiGetSolverStopTime(si);
    time_T h = rtsiGetStepSize(si);
    real_T *x = rtsiGetContStates(si);
    ODE3_IntgData *id = static_cast<ODE3_IntgData *>(rtsiGetSolverData(si));
    real_T *y = id->y;
    real_T *f0 = id->f[0];
    real_T *f1 = id->f[1];
    real_T *f2 = id->f[2];
    real_T hB[3];
    int_T i;
    int_T nXc = 5;
    rtsiSetSimTimeStep(si, MINOR_TIME_STEP);

    /* Save the state values at time t in y, we'll use x as ynew. */
    (void)std::memcpy(y, x,
                      static_cast<uint_T>(nXc) * sizeof(real_T));

    /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
    /* f0 = f(t,y) */
    rtsiSetdX(si, f0);
    finaldriver_derivatives();

    /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
    hB[0] = h * rt_ODE3_B[0][0];
    for (i = 0; i < nXc; i++)
    {
        x[i] = y[i] + (f0[i] * hB[0]);
    }

    rtsiSetT(si, t + h * rt_ODE3_A[0]);
    rtsiSetdX(si, f1);
    this->step();
    finaldriver_derivatives();

    /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
    for (i = 0; i <= 1; i++)
    {
        hB[i] = h * rt_ODE3_B[1][i];
    }

    for (i = 0; i < nXc; i++)
    {
        x[i] = y[i] + (f0[i] * hB[0] + f1[i] * hB[1]);
    }

    rtsiSetT(si, t + h * rt_ODE3_A[1]);
    rtsiSetdX(si, f2);
    this->step();
    finaldriver_derivatives();

    /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
    for (i = 0; i <= 2; i++)
    {
        hB[i] = h * rt_ODE3_B[2][i];
    }

    for (i = 0; i < nXc; i++)
    {
        x[i] = y[i] + (f0[i] * hB[0] + f1[i] * hB[1] + f2[i] * hB[2]);
    }

    rtsiSetT(si, tnew);
    rtsiSetSimTimeStep(si, MAJOR_TIME_STEP);
}

/* Model step function */
void finaldriverModelClass::step()
{
    /* local block i/o variables */
    uint8_T rtb_FixPtSwitch;
    boolean_T rtb_AND1;
    boolean_T rtb_AND;
    real_T rtb_mult;
    real_T rtb_Sum1;
    boolean_T rtb_Compare;
    if (rtmIsMajorTimeStep((&finaldriver_M)))
    {
        /* set solver stop time */
        if (!((&finaldriver_M)->Timing.clockTick0 + 1))
        {
            rtsiSetSolverStopTime(&(&finaldriver_M)->solverInfo, (((&finaldriver_M)
                                                                       ->Timing.clockTickH0 +
                                                                   1) *
                                                                  (&finaldriver_M)->Timing.stepSize0 *
                                                                  4294967296.0));
        }
        else
        {
            rtsiSetSolverStopTime(&(&finaldriver_M)->solverInfo, (((&finaldriver_M)
                                                                       ->Timing.clockTick0 +
                                                                   1) *
                                                                      (&finaldriver_M)->Timing.stepSize0 +
                                                                  (&finaldriver_M)->Timing.clockTickH0 * (&finaldriver_M)->Timing.stepSize0 * 4294967296.0));
        }
    } /* end MajorTimeStep */

    /* Update absolute time of base rate at minor time step */
    if (rtmIsMinorTimeStep((&finaldriver_M)))
    {
        (&finaldriver_M)->Timing.t[0] = rtsiGetT(&(&finaldriver_M)->solverInfo);
    }

    /* Outport: '<Root>/simTim' incorporates:
   *  Clock: '<Root>/Clock'
   */
    finaldriver_Y.simTim = (&finaldriver_M)->Timing.t[0];

    /* Sum: '<Root>/Sum1' incorporates:
   *  Inport: '<Root>/INPUT'
   *  Integrator: '<Root>/Integrator'
   */
    rtb_Sum1 = finaldriver_U.INPUT - finaldriver_X.Integrator_CSTATE;

    /* Gain: '<S40>/Filter Coefficient' incorporates:
   *  Gain: '<S31>/Derivative Gain'
   *  Integrator: '<S32>/Filter'
   *  Sum: '<S32>/SumD'
   */
    finaldriver_B.FilterCoefficient = (5.0 * rtb_Sum1 -
                                       finaldriver_X.Filter_CSTATE) *
                                      100.0;

    /* Sum: '<S46>/Sum' incorporates:
   *  Gain: '<S42>/Proportional Gain'
   *  Integrator: '<S37>/Integrator'
   */
    rtb_mult = (15.0 * rtb_Sum1 + finaldriver_X.Integrator_CSTATE_f) +
               finaldriver_B.FilterCoefficient;

    /* RelationalOperator: '<S1>/Compare' incorporates:
   *  Constant: '<S1>/Constant'
   */
    rtb_Compare = (rtb_mult >= 0.0);
    if (rtmIsMajorTimeStep((&finaldriver_M)))
    {
        /* UnitDelay: '<S2>/Output' */
        finaldriver_B.Output = finaldriver_DW.Output_DSTATE;
    }

    /* Abs: '<Root>/Abs' */
    rtb_mult = std::abs(rtb_mult);

    /* RelationalOperator: '<Root>/Relational Operator' */
    rtb_AND = (finaldriver_B.Output <= rtb_mult);

    /* Logic: '<Root>/AND1' incorporates:
   *  Logic: '<Root>/NOT'
   */
    rtb_AND1 = (rtb_AND && (!rtb_Compare));

    /* Logic: '<Root>/AND' */
    rtb_AND = (rtb_AND && rtb_Compare);

    /* Sum: '<Root>/Add' incorporates:
   *  Constant: '<Root>/vIn1'
   *  Product: '<Root>/mult'
   *  Product: '<Root>/mult2'
   */
    finaldriver_B.Add = static_cast<real_T>(rtb_AND) * 120.0 - 120.0 *
                                                                   static_cast<real_T>(rtb_AND1);
    if (rtmIsMajorTimeStep((&finaldriver_M)))
    {
        /* Switch: '<S5>/FixPt Switch' incorporates:
     *  Constant: '<S4>/FixPt Constant'
     *  Sum: '<S4>/FixPt Sum1'
     */
        rtb_FixPtSwitch = static_cast<uint8_T>(static_cast<uint8_T>(finaldriver_B.Output + 1U) & 31);
    }

    /* Gain: '<S34>/Integral Gain' */
    finaldriver_B.IntegralGain = 0.0001 * rtb_Sum1;

    /* Outport: '<Root>/MotorOutput' incorporates:
   *  Integrator: '<Root>/Integrator'
   */
    finaldriver_Y.MotorOutput = finaldriver_X.Integrator_CSTATE;

    /* TransferFcn: '<Root>/Transfer Fcn1' */
    finaldriver_B.TransferFcn1 = 0.0;
    finaldriver_B.TransferFcn1 += 0.0 * finaldriver_X.TransferFcn1_CSTATE[0];
    finaldriver_B.TransferFcn1 += 2.0 * finaldriver_X.TransferFcn1_CSTATE[1];
    if (rtmIsMajorTimeStep((&finaldriver_M)))
    {
        if (rtmIsMajorTimeStep((&finaldriver_M)))
        {
            /* Update for UnitDelay: '<S2>/Output' */
            finaldriver_DW.Output_DSTATE = rtb_FixPtSwitch;
        }
    } /* end MajorTimeStep */

    if (rtmIsMajorTimeStep((&finaldriver_M)))
    {
        rt_ertODEUpdateContinuousStates(&(&finaldriver_M)->solverInfo);

        /* Update absolute time for base rate */
        /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
        if (!(++(&finaldriver_M)->Timing.clockTick0))
        {
            ++(&finaldriver_M)->Timing.clockTickH0;
        }

        (&finaldriver_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&finaldriver_M)
                                                                   ->solverInfo);

        {
            /* Update absolute timer for sample time: [1.0E-5s, 0.0s] */
            /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 1.0E-5, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
            (&finaldriver_M)->Timing.clockTick1++;
            if (!(&finaldriver_M)->Timing.clockTick1)
            {
                (&finaldriver_M)->Timing.clockTickH1++;
            }
        }
    } /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void finaldriverModelClass::finaldriver_derivatives()
{
    XDot_finaldriver_T *_rtXdot;
    _rtXdot = ((XDot_finaldriver_T *)(&finaldriver_M)->derivs);

    /* Derivatives for Integrator: '<Root>/Integrator' */
    _rtXdot->Integrator_CSTATE = finaldriver_B.TransferFcn1;

    /* Derivatives for Integrator: '<S37>/Integrator' */
    _rtXdot->Integrator_CSTATE_f = finaldriver_B.IntegralGain;

    /* Derivatives for Integrator: '<S32>/Filter' */
    _rtXdot->Filter_CSTATE = finaldriver_B.FilterCoefficient;

    /* Derivatives for TransferFcn: '<Root>/Transfer Fcn1' */
    _rtXdot->TransferFcn1_CSTATE[0] = 0.0;
    _rtXdot->TransferFcn1_CSTATE[0] += -12.0 * finaldriver_X.TransferFcn1_CSTATE[0];
    _rtXdot->TransferFcn1_CSTATE[1] = 0.0;
    _rtXdot->TransferFcn1_CSTATE[0] += -20.02 * finaldriver_X.TransferFcn1_CSTATE
                                                    [1];
    _rtXdot->TransferFcn1_CSTATE[1] += finaldriver_X.TransferFcn1_CSTATE[0];
    _rtXdot->TransferFcn1_CSTATE[0] += finaldriver_B.Add;
}

/* Model initialize function */
void finaldriverModelClass::initialize()
{
    /* Registration code */
    {
        /* Setup solver object */
        rtsiSetSimTimeStepPtr(&(&finaldriver_M)->solverInfo, &(&finaldriver_M)
                                                                  ->Timing.simTimeStep);
        rtsiSetTPtr(&(&finaldriver_M)->solverInfo, &rtmGetTPtr((&finaldriver_M)));
        rtsiSetStepSizePtr(&(&finaldriver_M)->solverInfo, &(&finaldriver_M)
                                                               ->Timing.stepSize0);
        rtsiSetdXPtr(&(&finaldriver_M)->solverInfo, &(&finaldriver_M)->derivs);
        rtsiSetContStatesPtr(&(&finaldriver_M)->solverInfo, (real_T **)&(&finaldriver_M)->contStates);
        rtsiSetNumContStatesPtr(&(&finaldriver_M)->solverInfo, &(&finaldriver_M)
                                                                    ->Sizes.numContStates);
        rtsiSetNumPeriodicContStatesPtr(&(&finaldriver_M)->solverInfo,
                                        &(&finaldriver_M)->Sizes.numPeriodicContStates);
        rtsiSetPeriodicContStateIndicesPtr(&(&finaldriver_M)->solverInfo,
                                           &(&finaldriver_M)->periodicContStateIndices);
        rtsiSetPeriodicContStateRangesPtr(&(&finaldriver_M)->solverInfo,
                                          &(&finaldriver_M)->periodicContStateRanges);
        rtsiSetErrorStatusPtr(&(&finaldriver_M)->solverInfo, (&rtmGetErrorStatus((&finaldriver_M))));
        rtsiSetRTModelPtr(&(&finaldriver_M)->solverInfo, (&finaldriver_M));
    }

    rtsiSetSimTimeStep(&(&finaldriver_M)->solverInfo, MAJOR_TIME_STEP);
    (&finaldriver_M)->intgData.y = (&finaldriver_M)->odeY;
    (&finaldriver_M)->intgData.f[0] = (&finaldriver_M)->odeF[0];
    (&finaldriver_M)->intgData.f[1] = (&finaldriver_M)->odeF[1];
    (&finaldriver_M)->intgData.f[2] = (&finaldriver_M)->odeF[2];
    (&finaldriver_M)->contStates = ((X_finaldriver_T *)&finaldriver_X);
    rtsiSetSolverData(&(&finaldriver_M)->solverInfo, static_cast<void *>(&(&finaldriver_M)->intgData));
    rtsiSetSolverName(&(&finaldriver_M)->solverInfo, "ode3");
    rtmSetTPtr((&finaldriver_M), &(&finaldriver_M)->Timing.tArray[0]);
    (&finaldriver_M)->Timing.stepSize0 = 1.0E-5;

    /* InitializeConditions for Integrator: '<Root>/Integrator' */
    finaldriver_X.Integrator_CSTATE = 0.0;

    /* InitializeConditions for Integrator: '<S37>/Integrator' */
    finaldriver_X.Integrator_CSTATE_f = 0.0;

    /* InitializeConditions for Integrator: '<S32>/Filter' */
    finaldriver_X.Filter_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn1' */
    finaldriver_X.TransferFcn1_CSTATE[0] = 0.0;
    finaldriver_X.TransferFcn1_CSTATE[1] = 0.0;
}

/* Model terminate function */
void finaldriverModelClass::terminate()
{
    /* (no terminate code required) */
}

/* Constructor */
finaldriverModelClass::finaldriverModelClass() : finaldriver_U(), finaldriver_Y(), finaldriver_B(), finaldriver_DW(), finaldriver_X(), finaldriver_M()
{
    /* Currently there is no constructor body generated.*/
}

/* Destructor */
finaldriverModelClass::~finaldriverModelClass()
{
    /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_finaldriver_T *finaldriverModelClass::getRTM()
{
    return (&finaldriver_M);
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "joint_state_publisher_node");
    ros::NodeHandle nh;
    ros::Publisher joint_state_pub_ = nh.advertise<sensor_msgs::JointState>("/joint_states", 5);
    sensor_msgs::JointState out_joint_state_;
    out_joint_state_.name.resize(1);
    out_joint_state_.position.resize(1);

    out_joint_state_.name[0] = "joint1";
    finaldriverModelClass driver;
    driver.initialize();
    driver.finaldriver_U.INPUT = 10;
    driver.step();
    out_joint_state_.position[0] = driver.finaldriver_Y.MotorOutput;
    out_joint_state_.header.stamp.sec = int(driver.finaldriver_Y.simTim + 158869477);
    out_joint_state_.header.stamp.nsec = driver.finaldriver_Y.simTim * 0.1;
    joint_state_pub_.publish(out_joint_state_);

    ros::spin();

    return 0;
}