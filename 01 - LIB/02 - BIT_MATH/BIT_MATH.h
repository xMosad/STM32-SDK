/************************************************************/
/* Author         : A . MOSAD                               */
/* Date           : 4 / 8 / 2020                            */
/* version        : V01                                     */
/************************************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG,BIT) (REG |= (1 << BIT))
#define CLEAR_BIT(REG,BIT) (REG &= ~(1 << BIT))
#define TOGGLE_BIT(REG,BIT) (REG ^= ( 1 << BIT))
#define CLEAR_REG(REG) (REG &= ~(255 << 0))
#define SET_REG(REG) (REG |= ~(255 << 0))
#define IS_SET(REG,BIT)(REG & (1<<BIT))
#define GIT_BIT(REG,BIT)((REG>>BIT) & 1)

#endif
