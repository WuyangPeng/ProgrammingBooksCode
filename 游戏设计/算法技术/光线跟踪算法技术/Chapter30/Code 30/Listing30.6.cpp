void 
Instance::scale(const double sx, const double sy, const double sz) {

	Matrix inv_scaling_matrix;			// temporary inverse scaling matrix
	
	inv_scaling_matrix.m[0][0] = 1.0 / sx;
	inv_scaling_matrix.m[1][1] = 1.0 / sy;
	inv_scaling_matrix.m[2][2] = 1.0 / sz;
	
	inv_matrix = inv_matrix * inv_scaling_matrix;			 	
}