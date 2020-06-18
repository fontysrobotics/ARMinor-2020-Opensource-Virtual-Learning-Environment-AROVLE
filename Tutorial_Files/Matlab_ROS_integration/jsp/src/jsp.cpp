#include "ros/ros.h"
#include <sensor_msgs/JointState.h>
#include <iostream>
#include <math.h>

/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/
#include "finaldriver.h"
#include "finaldriver_private.h"

void finaldriverModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si)
{
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
  (void)std::memcpy(y, x,
                    static_cast<uint_T>(nXc) * sizeof(real_T));
  rtsiSetdX(si, f0);
  finaldriver_derivatives();
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++)
  {
    x[i] = y[i] + (f0[i] * hB[0]);
  }
  rtsiSetT(si, t + h * rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  finaldriver_derivatives();
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
void finaldriverModelClass::step()
{
  uint8_T rtb_FixPtSwitch;
  boolean_T rtb_AND1;
  boolean_T rtb_AND;
  real_T rtb_mult;
  real_T rtb_Sum1;
  boolean_T rtb_Compare;
  if (rtmIsMajorTimeStep((&finaldriver_M)))
  {
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
  }
  if (rtmIsMinorTimeStep((&finaldriver_M)))
  {
    (&finaldriver_M)->Timing.t[0] = rtsiGetT(&(&finaldriver_M)->solverInfo);
  }
  finaldriver_Y.simTim = (&finaldriver_M)->Timing.t[0];
  rtb_Sum1 = finaldriver_U.INPUT - finaldriver_X.Integrator_CSTATE;
  finaldriver_B.FilterCoefficient = (5.0 * rtb_Sum1 -
                                     finaldriver_X.Filter_CSTATE) *
                                    100.0;
  rtb_mult = (15.0 * rtb_Sum1 + finaldriver_X.Integrator_CSTATE_f) +
             finaldriver_B.FilterCoefficient;
  rtb_Compare = (rtb_mult >= 0.0);
  if (rtmIsMajorTimeStep((&finaldriver_M)))
  {
    finaldriver_B.Output = finaldriver_DW.Output_DSTATE;
  }
  rtb_mult = std::abs(rtb_mult);
  rtb_AND = (finaldriver_B.Output <= rtb_mult);
  rtb_AND1 = (rtb_AND && (!rtb_Compare));
  rtb_AND = (rtb_AND && rtb_Compare);
  finaldriver_B.Add = static_cast<real_T>(rtb_AND) * 120.0 - 120.0 *
                                                                 static_cast<real_T>(rtb_AND1);
  if (rtmIsMajorTimeStep((&finaldriver_M)))
  {
    rtb_FixPtSwitch = static_cast<uint8_T>(static_cast<uint8_T>(finaldriver_B.Output + 1U) & 31);
  }
  finaldriver_B.IntegralGain = 0.0001 * rtb_Sum1;
  finaldriver_Y.MotorOutput = finaldriver_X.Integrator_CSTATE;
  finaldriver_B.TransferFcn1 = 0.0;
  finaldriver_B.TransferFcn1 += 0.0 * finaldriver_X.TransferFcn1_CSTATE[0];
  finaldriver_B.TransferFcn1 += 2.0 * finaldriver_X.TransferFcn1_CSTATE[1];
  if (rtmIsMajorTimeStep((&finaldriver_M)))
  {
    if (rtmIsMajorTimeStep((&finaldriver_M)))
    {
      finaldriver_DW.Output_DSTATE = rtb_FixPtSwitch;
    }
  } /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&finaldriver_M)))
  {
    rt_ertODEUpdateContinuousStates(&(&finaldriver_M)->solverInfo);
    if (!(++(&finaldriver_M)->Timing.clockTick0))
    {
      ++(&finaldriver_M)->Timing.clockTickH0;
    }

    (&finaldriver_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&finaldriver_M)
                                                               ->solverInfo);

    {

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
  (&finaldriver_M)->Timing.stepSize0 = 1.0E-4; //1.0E-5;

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

/*******************************************************************************************************************************************/
/*******************************************************************************************************************************************/
/*******************************************************************************************************************************************/
/*******************************************************************************************************************************************/
/*******************************************************************************************************************************************/
/*******************************************************************************************************************************************/

int main(int argc, char **argv)
{
  ros::init(argc, argv, "jsp");

  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<sensor_msgs::JointState>("joint_states", 1000);
  ros::Rate loop_rate(10000);

  sensor_msgs::JointState msg;
  msg.name.resize(1);
  msg.name[0] = "joint1";
  msg.position.resize(1);

  /**************************************************************/
  finaldriverModelClass driver;
  driver.initialize();
  //driver.finaldriver_U.INPUT = 100; // a command

  for (size_t i = 0; i < 10; i++)
  {
    std::cin >> driver.finaldriver_U.INPUT;
    while (true)
    {
      driver.step();
      printf("%f \n", driver.finaldriver_Y.MotorOutput);
      msg.position[0] = driver.finaldriver_Y.MotorOutput;
      msg.header.stamp = ros::Time::now();

      pub.publish(msg);
      ros::spinOnce();
      loop_rate.sleep();
      if(sqrt((driver.finaldriver_Y.MotorOutput - driver.finaldriver_U.INPUT)*(driver.finaldriver_Y.MotorOutput - driver.finaldriver_U.INPUT)) < 0.001)
      {
        break;
      }
    }
    /**************************************************************/
  }
  return 0;
}