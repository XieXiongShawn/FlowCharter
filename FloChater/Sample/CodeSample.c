#include "stdio.h"


#define STATE_3_4_2_2_0 0   /*!< State 0 */
#define STATE_3_4_2_2_1 1   /*!< State 1 */
#define STATE_3_4_2_2_2 2   /*!< State 2 */
#define STATE_3_4_2_2_3 3   /*!< State 3 */

#define NEXTSTATE_3_4_2_2(state) (CodeSample_State = state)

static byte_u CodeSample_State = STATE_3_4_2_2_0;

static void CodeSample_f_3_4_2_2_0(void);
static void CodeSample_f_3_4_2_2_1(void);
 

static void CodeSample_f_3_4_2_2_0(void)
{
    /* Annotation_01 */
    Statement_00;
    Statement_00_01;
    Statement_00_02;
    /* Annotation_01 Annotation_01 */
    NEXTSTATE_3_4_2_2(STATE_3_4_2_2_1);
}

static void CodeSample_f_3_4_2_2_1(void)
{
    /* IF Annotation_01 Annotation_01 */
    if(g_Var_01 && !g_Var_02)
    {
        /* Annotation_01 */S
        Statement_01;
        Statement_02;   // Annotation_02
        /* Annotation_01 */
        NEXTSTATE_3_4_2_2(STATE_3_4_2_2_0);
    }
    else if(g_Var_03 || g_Var_04 || g_Var_05 || g_Var_06)
    {
        /* Annotation_01 */
        Statement_03;
        /* Annotation_01 */
        NEXTSTATE_3_4_2_2(STATE_3_4_2_2_0);
    }
    else
    {
        /* Do nothing */
    }
    /* ENDIF */
}

void CodeSample_f_Call(void)
{
    /* SWITCH */
    switch(CodeSample_State)
    {
        /*State 3_4_2_2_0 0*/
        case STATE_3_4_2_2_0:
            CodeSample_f_3_4_2_2_0();
            break;
        /*State 3_4_2_2_1 1*/
        case STATE_3_4_2_2_1:
            CodeSample_f_3_4_2_2_1();
            break;
        /*State unknown */ 
        default:
            break;
    }
}

void CodeSample_f_Reset(void)
{
    /* Annotation_01 */
    Statement_06;
    /* Annotation_01 */
    NEXTSTATE_3_4_2_2(STATE_3_4_2_2_0);
} 
