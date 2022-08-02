//============================================================================
//
// Listing 16.2
//
// Mathematics for 3D Game Programming and Computer Graphics, 3rd ed.
// By Eric Lengyel
//
// The code in this file may be freely used in any software. It is provided
// as-is, with no warranty of any kind.
//
//============================================================================


bool SolveLinearSystem(int n, float *m, float *r)
{
	float *rowNormalizer = new float[n];
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
	}
	// Perform elimination one column at a time.
	for (int j = 0; j < n - 1; j++)
	{
		// Find pivot element.
		int pivotRow = -1;
		float maxvalue = 0.0F;
		for (int i = j; i < n; i++)
		{
			float p = fabs(m[j * n + i]) * rowNormalizer[i];
			if (p > maxvalue)
			{
				maxvalue = p;
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
			
			float temp = r[j];
			r[j] = r[pivotRow];
			r[pivotRow] = temp;
			
			rowNormalizer[pivotRow] = rowNormalizer[j];
		}
		
		float denom = 1.0F / m[j * n + j];
		for (int i = j + 1; i < n; i++)
		{
			float factor = m[j * n + i] * denom;
			r[i] -= r[j] * factor;
			for (int k = 0; k < n; k++)
				m[k * n + i] -= m[k * n + j] * factor;
		}
	}
	
	// Perform backward substitution.
	for (int i = n - 1; i >= 0; i--)
	{
		float sum = r[i];
		for (int k = i + 1; k < n; k++) sum -= m[k * n + i] * r[k];
		r[i] = sum / m[i * n + i];
	}
	
	result = true;
	
	exit:
	delete[] rowNormalizer;
	return (result);
}
