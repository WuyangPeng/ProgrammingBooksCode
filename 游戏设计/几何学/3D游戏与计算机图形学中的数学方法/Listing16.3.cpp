//============================================================================
//
// Listing 16.3
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


bool LUDecompose(int n, float *m, unsigned short *index, float *detSign)
{
	float *rowNormalizer = new float[n];
	float exchangeParity = 1.0F;
	bool result = false;
	
	// Calculate a normalizer for each row.
	for (int i = 0; i < n; i++)
	{
		const float *entry = m + i;
		float maxvalue = 0.0F;
		
		for (int j = 0; j < n; j++)
		{
			float value = fabs(*entry);
			if (value > maxvalue) maxvalue = value;
			entry += n;
		}
		
		if (maxvalue == 0.0F) goto exit;	// Singular
		rowNormalizer[i] = 1.0F / maxvalue;
		index[i] = i;
	}
	
	// Perform decomposition.
	for (int j = 0; j < n; j++)
	{
		for (int i = 1; i < j; i++)
		{
			// Evaluate Equation (16.18).
			float sum = m[j * n + i];
			for (int k = 0; k < i; k++) sum -= m[k * n + i] * m[j * n + k];
			m[j * n + i] = sum;
		}
		
		// Find pivot element.
		int pivotRow = -1;
		float maxvalue = 0.0F;
		for (int i = j; i < n; i++)
		{
			// Evaluate Equation (16.20).
			float sum = m[j * n + i];
			for (int k = 0; k < j; k++) sum -= m[k * n + i] * m[j * n + k];
			m[j * n + i] = sum;
			
			sum = fabs(sum) * rowNormalizer[i];
			if (sum > maxvalue)
			{
				maxvalue = sum;
				pivotRow = i;
			}
		}
		
		if (pivotRow != j)
		{
			if (pivotRow == -1) goto exit;	// Singular
			
			// Exchange rows.
			for (int k = 0; k < n; k++)
			{
				float temp = m[k * n + j];
				m[k * n + j] = m[k * n + pivotRow];
				m[k * n + pivotRow] = temp;
			}
			
			unsigned short temp = index[j];
			index[j] = index[pivotRow];
			index[pivotRow] = temp;
			
			rowNormalizer[pivotRow] = rowNormalizer[j];
			exchangeParity = -exchangeParity;
		}
		
		// Divide by pivot element.
		if (j != n - 1)
		{
			float denom = 1.0F / m[j * n + j];
			for (int i = j + 1; i < n; i++) m[j * n + i] *= denom;
		}
	}
	
	if (detSign) *detSign = exchangeParity;
	result = true;
	
	exit:
	delete[] rowNormalizer;
	return (result);
}
