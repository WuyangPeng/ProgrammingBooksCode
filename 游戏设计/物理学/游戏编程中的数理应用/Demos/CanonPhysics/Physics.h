/**********************************************************************************************/
/* The naming convention for your equations of motion is as follows:						  */
/* Eqn_return	Eq		- stands for equation												  */
/*				n		- Which equation of motion it is 1-5 based on you math/physics manual */
/*				return	- What attribute are you looking for								  */
/* 																							  */
/* i.e. Eq1_Vf	Is the name of the function when we want to use equation 1 and we don't 	  */
/*				know the final velocity														  */
/**********************************************************************************************/
#ifndef PHYSICS_H
#define PHYSICS_H

#include <cmath>

#pragma warning(disable : 4244)

#define PI	3.141593f
#define DEGTORAD(deg) ((deg) * (PI / 180.0f))
#define GETX_COMPONENT(angle, value) ((float)cos(angle) * value)
#define GETY_COMPONENT(angle, value) ((float)sin(angle) * value)
#define COMBINE_COMPONENTS(x_com, y_com) (sqrt((x_com* x_com) + (y_com * y_com)))

namespace Physics
{
	// Used to multiply a value by 1/2
	static const float Halve = 0.5f;
	// Used to multiply a value by 2
	static const float Double = 2.0f;
}

class Physics_Util
{
public:
	inline static Physics_Util &instance(void)
	{
		static Physics_Util inst;
		return inst;
	}

	/***************/
	/*	EQUATION 1 */
	/***************/
	// Use Equation 1 to find the final velocity
	inline float Eq1_vf(float time, float i_velocity, float acceleration)
	{
		return (i_velocity + (acceleration * time));
	};

	// Use Equation 1 to find the initial velocity
	inline float Eq1_vi(float time, float f_velocity, float acceleration)
	{
		return (f_velocity - (acceleration * time));
	};

	// Use Equation 1 to find the acceleration
	inline float Eq1_a(float time, float i_velocity, float f_velocity)
	{
		return ((f_velocity - i_velocity) / time);
	};

	// Use Equation 1 to find time
	inline float Eq1_t(float i_velocity, float f_velocity, float acceleration)
	{
		return ((f_velocity - i_velocity) / acceleration);
	};

	/***************/
	/*	EQUATION 2 */
	/***************/
	// Use Equation 2 to find the average velocity
	inline float Eq2_va(float i_velocity, float f_velocity)
	{
		return ((i_velocity + f_velocity) * Physics::Halve);
	};

	// Use Equation 2 to find the initial velocity
	inline float Eq2_vi(float a_velocity, float f_velocity)
	{
		return ((a_velocity * Physics::Double) - f_velocity);
	};

	// Use Equation 2 to find the final velocity
	inline float Eq2_vf(float a_velocity, float i_velocity)
	{
		return ((a_velocity * Physics::Double) - i_velocity);
	};
	
	/***************/
	/*	EQUATION 3 */
	/***************/
	// Use Equation 3 to find the change in distance
	inline float Eq3_deltax(float i_velocity, float f_velocity, float time)
	{
		return ((f_velocity + i_velocity) * time * Physics::Halve);
	};
	
	// Use Equation 3 to find the final velocity
	inline float Eq3_vf(float i_velocity, float delta_x, float time)
	{
		return (((Physics::Double * delta_x)/time) - i_velocity);
	};
	
	// Use Equation 3 to find the initial velocity
	inline float Eq3_vi(float f_velocity, float delta_x, float time)
	{
		return (((Physics::Double * delta_x)/time) - f_velocity);
	};

	// Use Equation 3 to find the time
	inline float Eq3_t(float f_velocity, float delta_x, float i_velocity)
	{
		return ((Physics::Double * delta_x)/(i_velocity + f_velocity));
	};

	/***************/
	/*	EQUATION 4 */
	/***************/
	// Use Equation 4 to find the change in distance
	inline float Eq4_deltax(float time, float i_velocity, float acceleration)
	{
		return ((i_velocity * time) + (Physics::Halve * acceleration * time * time));
		//return 0;
	};
	
	// Use Equation 4 to find the initial velocity
	inline float Eq4_vi(float time, float delta_x, float acceleration)
	{
		return ((delta_x - (Physics::Halve * acceleration * time * time)) / time);
	};

	// Use Equation 4 to find the acceleration
	inline float Eq4_a(float time, float i_velocity, float delta_x)
	{
		return (((Physics::Double * delta_x) - (i_velocity * time)) / (time * time));
	};

	/***************/
	/*	EQUATION 5 */
	/***************/
	// Use Equation 5 to find the final velocity
	inline float Eq5_vf(float i_velocity, float delta_x, float acceleration)
	{
		return (float)sqrt((i_velocity * i_velocity) + (Physics::Double * acceleration * delta_x));
	};

	// Use Equation 5 to find the initial velocity
	inline float Eq5_vi(float f_velocity, float delta_x, float acceleration)
	{
		return (float)sqrt((f_velocity * f_velocity) - (Physics::Double * acceleration * delta_x));
	};

	// Use Equation 5 to find the acceleration
	inline float Eq5_a(float f_velocity, float delta_x, float i_velocity)
	{
		return (float)((sqrt(f_velocity) - sqrt(i_velocity)) / (Physics::Double * delta_x));
	};
	
	// Use Equation 5 to find the change in distance
	inline float Eq5_deltax(float f_velocity, float acceleration, float i_velocity)
	{
		return (float)((sqrt(f_velocity) - sqrt(i_velocity)) / (Physics::Double * acceleration));
	};

	/******************/
	/*	NEWTON'S LAWS */
	/******************/
	// F = ma
	inline float Newton2(float mass, float force)
	{
		return force/mass;
	};

	/**************************************/
	/*	Conservation Of Mechanical Energy */
	/**************************************/
	// KEi + PEi = KEf + PEf
	// 1/2m(Vi)^2 + mgYi = 1/2m(Vf)^2 + mg(Yf)^2
	// we will change this formula slightly:
	// KEi + PEi = (a)KEf + PEf
	//
	// In this new variation a = the elasticity of the object being collided into
	// This value should range between 0 - 1, an object with and elasticity of 1.0 
	// is considered perfectly inelastic, likewise an elasticity of 0.0 is considered
	// perfectly elastic.
	
	// Used to get Vi, this instance of the formula is a special case where Yf and Yi are 0.0f
	// Also when we solve for Vi, the masses cancel out on each side so you basically end up with
	// (Vi)^2 = elasticity * (Vf)^2
	inline float ConMecEn_vi(float elasticity, float f_velocity)
	{
		return sqrt(elasticity * f_velocity * f_velocity);
	};
/*
	inline float ConMecEn_vi(float elasticity, float f_velocity, float mass, 
								float i_velocity, float gravity, float ypos_i, float ypos_f)
	{
		return 0;
	};
*/
private:
	Physics_Util(void) { }
	~Physics_Util(void) { }
};

#endif
