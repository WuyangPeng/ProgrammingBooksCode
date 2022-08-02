// Frame.h
// Implementation of the Orthonormal Frame Class

#include "gltools.h"

#ifndef _GLFRAME_H_
#define _GLFRAME_H_


// The OrthonormalFrame class. Possibly the most useful little piece of 3D graphics
// code for OpenGL immersive environments.
// Richard S. Wright Jr.
class OrthonormalFrame
    {
	protected:
        GLT_POINT3 vOrigin;		// Where am I?
        GLT_VECTOR3 vForward;	// Where am I going?
        GLT_VECTOR3 vUp;		// Which way is up?

    public:
		// Default position and orientation. At the origin, looking
		// down the negative Z axis. This matches the default OpenGL
		// ModelView matrix view. Note that in essense, positive Z now is
		// considered in front of the viewpoint in local coordinates
        OrthonormalFrame(void) {
            vOrigin[0] = 0.0f; vOrigin[1] = 0.0f; vOrigin[2] = 0.0f; 
            vUp[0] = 0.0f; vUp[1] = 1.0f; vUp[2] = 0.0f;
            vForward[0] = 0.0f; vForward[1] = 0.0f; vForward[2] = 1.0f;
            }


        /////////////////////////////////////////////////////////////
        // Set Location
        inline void SetOrigin(GLT_VECTOR3 vPoint) {
            memcpy(vOrigin, vPoint, sizeof(float)*3); }
        
        inline void SetOrigin(float x, float y, float z) { 
			vOrigin[0] = x; vOrigin[1] = y; vOrigin[2] = z; }

		inline void GetOrigin(GLT_POINT3 point) {
			memcpy(point, vOrigin, sizeof(float)*3); }

		inline float GetX(void) { return vOrigin[0]; }
		inline float GetY(void) { return vOrigin[1]; }
		inline float GetZ(void) { return vOrigin[2]; }

        inline GLT_POINT3* GetOrigin(void) { return &vOrigin; }

        /////////////////////////////////////////////////////////////
        // Set Up Direction
        inline void SetForwardDirection(GLT_VECTOR3 vDirection)  {
                memcpy(vForward, vDirection, sizeof(float)*3);   }

        inline void SetForwardDirection(float x, float y, float z)
            { vForward[0] = x; vForward[1] = y; vForward[2] = z; }

        /////////////////////////////////////////////////////////////
        // Set Up Direction
        inline void SetUpDirection(GLT_VECTOR3 vDirection)	{
			memcpy(vUp, vDirection, sizeof(float)*3);		}

        inline void SetUpDirection(float x, float y, float z)
			{ vUp[0] = x; vUp[1] = y; vUp[2] = z; }

		/////////////////////////////////////////////////////////////
        // Queries
        inline void GetOriginPoint(GLT_POINT3 vPoint) { memcpy(vPoint, vOrigin, sizeof(float)*3); }
        inline void GetForwardVector(GLT_VECTOR3 vVector) { memcpy(vVector, vForward, sizeof(float)*3); }
        inline void GetUpVector(GLT_VECTOR3 vVector) { memcpy(vVector, vUp, sizeof(float)*3); }


		inline void GetZVector(GLT_VECTOR3 vVector) { GetForwardVector(vVector); }
		inline void GetYVector(GLT_VECTOR3 vVector) { GetUpVector(vVector); }
		inline void GetXVector(GLT_VECTOR3 vVector) { gltCrossProduct(vUp, vForward, vVector); }


		/////////////////////////////////////////////////////////////
        // Translate along orthonormal axis... world or local
        void TranslateWorld(float x, float y, float z)
			{ vOrigin[0] += x; vOrigin[1] += y; vOrigin[2] += z; }

        inline void TranslateLocal(float x, float y, float z)
			{ MoveForward(z); MoveUp(y); MoveRight(x);	}


		/////////////////////////////////////////////////////////////
		// Move Forward (along Z axis)
		inline void MoveForward(float fDelta)
			{
		    // Move along direction of front direction
			vOrigin[0] += vForward[0] * fDelta;
			vOrigin[1] += vForward[1] * fDelta;
			vOrigin[2] += vForward[2] * fDelta;
			}

		inline void MoveUp(float fDelta)
			{
		    // Move along direction of up direction
			vOrigin[0] += vUp[0] * fDelta;
			vOrigin[1] += vUp[1] * fDelta;
			vOrigin[2] += vUp[2] * fDelta;
			}

		inline void MoveRight(float fDelta)
			{
			// Move along direction of right vector
			GLT_VECTOR3 vCross;
			gltCrossProduct(vUp, vForward, vCross);

			vOrigin[0] += vCross[0] * fDelta;
			vOrigin[1] += vCross[1] * fDelta;
			vOrigin[2] += vCross[2] * fDelta;
			}


		/////////////////////////////////////////////////////////////
		// Perform viewing or modeling transformations
		// Position as the camera (for viewing). Apply this transformation
		// first as your viewing transformation
		// The default implementation of gluLookAt can be considerably sped up.
		// Some additional optimization can be done with this
        void ApplyCameraTransform(void)    
			{
		    gluLookAt(vOrigin[0], vOrigin[1], vOrigin[2],
						vOrigin[0] + vForward[0], 
						vOrigin[1] + vForward[1], 
						vOrigin[2] + vForward[2], 
						vUp[0], vUp[1], vUp[2]);
			}


		// Position as an object in the scene. This places and orients a
		// coordinate frame for other objects (besides the camera)
		// There is ample room for optimization here... 
        void ApplyActorTransform(void)
			{
			GLT_MATRIX4 rotMat;

			GLT_VECTOR3 vCross;
			
            // Do the translation directly on the curren matrix
//			glTranslatef(vOrigin[0], vOrigin[1], vOrigin[2]);

			// Calculate the right side (x) vector
            gltCrossProduct(vUp, vForward, vCross);

			// X Column
			memcpy(rotMat, vCross, sizeof(float)*3);
            rotMat[3] = 0.0f;
           
            // Y Column
			memcpy(&rotMat[4], vUp, sizeof(float)*3);
            rotMat[7] = 0.0f;       
                                    

            // Z Column
			memcpy(&rotMat[8], vForward, sizeof(float)*3);
            //rotMat[8] = vForward[0];
            //rotMat[9] = vForward[1];
            //rotMat[10] = vForward[2];
            rotMat[11] = 0.0f;

            // Translation (already done)... can't we combine these?
			rotMat[12] = vOrigin[0]; //0.0f;
            rotMat[13] = vOrigin[1]; //0.0f;
            rotMat[14] = vOrigin[2]; //0.0f;
//			rotMat[12] = 0.0f;
//            rotMat[13] = 0.0f;
//            rotMat[14] = 0.0f;
            
            rotMat[15] = 1.0f;

			// Apply rotation to the current matrix
			glMultMatrixf(rotMat);
			}


        // Rotate around local X Axes
        void RotateLocalX(float fAngle)
			{
			GLT_MATRIX4 rotMat;
			GLT_VECTOR3 vCross;
			gltCrossProduct(vUp, vForward, vCross);
			gltRotationMatrix(fAngle,
							vCross[0], vCross[1], vCross[2], rotMat);

			GLT_VECTOR3 newVect;
			// Inline 3x3 matrix multiply for rotation only
			newVect[0] = rotMat[0] * vForward[0] + rotMat[4] * vForward[1] + rotMat[8] *  vForward[2];	
			newVect[1] = rotMat[1] * vForward[0] + rotMat[5] * vForward[1] + rotMat[9] *  vForward[2];	
			newVect[2] = rotMat[2] * vForward[0] + rotMat[6] * vForward[1] + rotMat[10] * vForward[2];	

			// Update forward pointing vector
			memcpy(vForward, newVect, sizeof(float)*3);
			//vForward[0] = newVect[0];
			//vForward[1] = newVect[1];
			//vForward[2] = newVect[2];

			// Update pointing up vector
			newVect[0] = rotMat[0] * vUp[0] + rotMat[4] * vUp[1] + rotMat[8] *  vUp[2];	
			newVect[1] = rotMat[1] * vUp[0] + rotMat[5] * vUp[1] + rotMat[9] *  vUp[2];	
			newVect[2] = rotMat[2] * vUp[0] + rotMat[6] * vUp[1] + rotMat[10] * vUp[2];	

			memcpy(vUp, newVect, sizeof(float)*3);
			//vUp[0] = newVect[0];
			//vUp[1] = newVect[1];
			//vUp[2] = newVect[2];
			}

		// Rotate around local Y
        void RotateLocalY(float fAngle)
			{
	        GLT_MATRIX4 rotMat;

			// Just Rotate around the up vector
			// Create a rotation matrix around my Up (Y) vector
			gltRotationMatrix(fAngle,
                         vUp[0], vUp[1], vUp[2], rotMat);

			GLT_VECTOR3 newVect;

	        // Rotate forward pointing vector (inlined 3x3 transform)
			newVect[0] = rotMat[0] * vForward[0] + rotMat[4] * vForward[1] + rotMat[8] *  vForward[2];	
			newVect[1] = rotMat[1] * vForward[0] + rotMat[5] * vForward[1] + rotMat[9] *  vForward[2];	
			newVect[2] = rotMat[2] * vForward[0] + rotMat[6] * vForward[1] + rotMat[10] * vForward[2];	

			// Update forward pointing vector
			memcpy(vForward, newVect, sizeof(float)*3);
			//vForward[0] = newVect[0];
			//vForward[1] = newVect[1];
			//vForward[2] = newVect[2];
			}


		// Rotate around local Z
        void RotateLocalZ(float fAngle)
			{
			GLT_MATRIX4 rotMat;

			// Only the up vector needs to be rotated
			gltRotationMatrix(fAngle,
							vForward[0], vForward[1], vForward[2], rotMat);

			GLT_VECTOR3 newVect;
			newVect[0] = rotMat[0] * vUp[0] + rotMat[4] * vUp[1] + rotMat[8] *  vUp[2];	
			newVect[1] = rotMat[1] * vUp[0] + rotMat[5] * vUp[1] + rotMat[9] *  vUp[2];	
			newVect[2] = rotMat[2] * vUp[0] + rotMat[6] * vUp[1] + rotMat[10] * vUp[2];	

			// Update forward pointing vector
			memcpy(vUp, newVect, sizeof(float)*3);
			//vUp[0] = newVect[0];
			//vUp[1] = newVect[1];
			//vUp[2] = newVect[2];
			}

		// Reset axes to make sure they are orthonormal
		// This should be called on occasion along with Normalize()
		// to prevent rounding drift.
        void EnforceOrtho(void)
			{
			GLT_VECTOR3 vCross;

			// Calculate cross product of up and forward vectors
			gltCrossProduct(vUp, vForward, vCross);

			// Use result to recalculate forward vector
			gltCrossProduct(vCross, vUp, vForward);	
			}

		// Rescales frame normals to unit length
		void Normalize(void)
			{
			gltNormalize(vUp);
			gltNormalize(vForward);
			}


		void RotateWorld(float fAngle, float x, float y, float z)
			{
			GLT_VECTOR3 vector;
			vector[0] = x;
			vector[1] = y;
			vector[2] = z;
			RotateWorld(fAngle, vector);
			}

		/////////////////////////////////////////////////////////////
		// Rotate around arbitrary axes in world coordinates
        void RotateWorld(float fAngle, GLT_VECTOR3 vAxis) // Simple Rotation
            {
            GLT_MATRIX4 rotMat;

			// Create the Rotation matrix
			gltRotationMatrix(fAngle,
							vAxis[0], vAxis[1], vAxis[2], rotMat);

			GLT_VECTOR3 newVect;
			
			// Transform the up axis (inlined 3x3 rotation)
			newVect[0] = rotMat[0] * vUp[0] + rotMat[4] * vUp[1] + rotMat[8] *  vUp[2];	
			newVect[1] = rotMat[1] * vUp[0] + rotMat[5] * vUp[1] + rotMat[9] *  vUp[2];	
			newVect[2] = rotMat[2] * vUp[0] + rotMat[6] * vUp[1] + rotMat[10] * vUp[2];	

			memcpy(vUp, newVect, sizeof(float)*3);
            //vUp[0] = newVect[0];
            //vUp[1] = newVect[1];
            //vUp[2] = newVect[2];

			// Transform the forward axis
			newVect[0] = rotMat[0] * vForward[0] + rotMat[4] * vForward[1] + rotMat[8] *  vForward[2];	
			newVect[1] = rotMat[1] * vForward[0] + rotMat[5] * vForward[1] + rotMat[9] *  vForward[2];	
			newVect[2] = rotMat[2] * vForward[0] + rotMat[6] * vForward[1] + rotMat[10] * vForward[2];	

			memcpy(vForward, newVect, sizeof(float)*3);
            //vForward[0] = newVect[0];
            //vForward[1] = newVect[1];
            //vForward[2] = newVect[2];
            }


        // convert local to world, then above
        void RotateLocal(float fAngle, GLT_VECTOR3 vAxis) 
            {
            GLT_VECTOR3 vWorldVect;

            LocalToWorld(vAxis, vWorldVect);
            RotateWorld(fAngle, vWorldVect);
			memcpy(vAxis, vWorldVect, sizeof(float)*3);
            //vAxis[0] = vWorldVect[0];
            //vAxis[1] = vWorldVect[1];
            //vAxis[2] = vWorldVect[2];
            }
    

		// Convert Coordinate Systems
        // This is pretty much, do the transformation represented by the rotation
        // and position on the point
        void LocalToWorld(GLT_POINT3 vLocal, GLT_POINT3 vWorld)
            {
            // Create the rotation matrix based on the vectors
			GLT_MATRIX4 rotMat;
			GLT_VECTOR3 vCross;
			
			// Compose the rotation matrix
            gltCrossProduct(vUp, vForward, vCross);

			// X Column
			memcpy(rotMat, vCross, sizeof(float)*3);
            //rotMat[0] = vCross[0];
            //rotMat[1] = vCross[1];
            //rotMat[2] = vCross[2];
            //rotMat[3] = 0.0f;
           
            // Y Column
			memcpy(&rotMat[4], vUp, sizeof(float)*3);
            //rotMat[4] = vUp[0];
            //rotMat[5] = vUp[1];
            //rotMat[6] = vUp[2];
            //rotMat[7] = 0.0f;  // Is it slower because it's a lookup, or faster
                                    // because it's in cache?

            // Z Column
			memcpy(&rotMat[8], vForward, sizeof(float)*3);
            //rotMat[8] = vForward[0];
            //rotMat[9] = vForward[1];
            //rotMat[10] = vForward[2];
            //rotMat[11] = 0.0f;

            // Translation
			//rotMat[12] = 0.0f;
            //rotMat[13] = 0.0f;
            //rotMat[14] = 0.0f;
            //rotMat[15] = 1.0f;

			// Do the rotation (inline it)
			//gltTransformPointf(vLocal, rotMat, vWorld);
			vWorld[0] = rotMat[0] * vLocal[0] + rotMat[4] * vLocal[1] + rotMat[8] *  vLocal[2];	
			vWorld[1] = rotMat[1] * vLocal[0] + rotMat[5] * vLocal[1] + rotMat[9] *  vLocal[2];	
			vWorld[2] = rotMat[2] * vLocal[0] + rotMat[6] * vLocal[1] + rotMat[10] * vLocal[2];	

            // Translate the point
            vWorld[0] += vOrigin[0];
            vWorld[1] += vOrigin[1];
            vWorld[2] += vOrigin[2];
            }

        void WorldToLocal(GLT_POINT3 vWorld, GLT_POINT3 vLocal)
            {
			////////////////////////////////////////////////
            // Translate the origin
            vWorld[0] = vOrigin[0] - vLocal[0];
            vWorld[1] = vOrigin[1] - vLocal[1];
            vWorld[2] = vOrigin[2] - vLocal[2];

            // Create the rotation matrix based on the vectors
			GLT_MATRIX4 rotMat;
            GLT_MATRIX4 invMat;
			GLT_VECTOR3 vCross;
			
			// Compose the rotation matrix
            gltCrossProduct(vUp, vForward, vCross);

			// X Column
			memcpy(rotMat, vCross, sizeof(float)*3);
            //rotMat[0] = vCross[0];
            //rotMat[1] = vCross[1];
            //rotMat[2] = vCross[2];
            rotMat[3] = 0.0f;
           
            // Y Column
			memcpy(&rotMat[4], vUp, sizeof(float)*3);
            //rotMat[4] = vUp[0];
            //rotMat[5] = vUp[1];
            //rotMat[6] = vUp[2];
            rotMat[7] = 0.0f; 
                              

            // Z Column
			memcpy(&rotMat[8], vForward, sizeof(float)*3);
            //rotMat[8] = vForward[0];
            //rotMat[9] = vForward[1];
            //rotMat[10] = vForward[2];
            rotMat[11] = 0.0f;

            // Translation
			rotMat[12] = 0.0f;
            rotMat[13] = 0.0f;
            rotMat[14] = 0.0f;
            rotMat[15] = 1.0f;


			// Do the rotation
			GLT_VECTOR3 vNewVect;
            gltInvertMatrix(rotMat, invMat);
			//gltTransformPointf(vWorld, invMat, vNewVect);
			vNewVect[0] = rotMat[0] * vWorld[0] + rotMat[4] * vWorld[1] + rotMat[8] *  vWorld[2];	
			vNewVect[1] = rotMat[1] * vWorld[0] + rotMat[5] * vWorld[1] + rotMat[9] *  vWorld[2];	
			vNewVect[2] = rotMat[2] * vWorld[0] + rotMat[6] * vWorld[1] + rotMat[10] * vWorld[2];	

			
			memcpy(vWorld, vNewVect, sizeof(float)*3);
			//vWorld[0] = vNewVect[0];
			//vWorld[1] = vNewVect[1];
			//vWorld[2] = vNewVect[2];
            }
        };

#endif
